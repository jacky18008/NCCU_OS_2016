#include"open.h"

#include <thread>
using std::thread;

#include <mutex>
using std::mutex;

#include <exception> // terminate thread
#include <condition_variable>

#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <cmath>
#include <deque>
using std::deque;

#include <vector>
using std::vector;

#include <assert.h>

#include "swim_pool.h"
#include "customer.h"
#include "Utility.h"

std::deque<Customer> wait_queue;
std::vector<std::thread> swimThreads;


int basket, bathroom;
std::condition_variable notify_empty;
std::condition_variable notify_has_basket;


void business();
void check_queue();
void generate_customer();
void customer_swim(int duration);
bool is_business_time = true;

std::mutex mtx;
Swimming_Pool swim_pool;

void change_swim_suit();
void change_street_suit();

float generateTiming(float lumbda);
float lumbdaCome = 0.001;//global viable
float lumbdaSwim = 0.01;





void Open(int Num_of_Basket, int Num_of_Bathroom, double Arriving_Rate) {
    //input later
    //scanf("%d", &bathroom);
    //scanf("%d", &basket);

    //input by gui
    basket = Num_of_Basket;
    bathroom = Num_of_Bathroom;

    swim_pool.set_value(basket, bathroom);

    thread operation_time(business);
    thread monitor_queue(check_queue);
    thread poission_process(generate_customer);


    poission_process.join();
    monitor_queue.join();
    operation_time.join();

    printf("total | bathroom: %d basket: %d\n",swim_pool.return_bathroom_number (),swim_pool.return_basket_number () );


}

void business(){
    printf("operation\n");
    usleep(100000000);
    is_business_time = false;
}

void check_queue(){

    while(is_business_time){

        mtx.lock();
        printf("check_queue size = %d \n", wait_queue.size());
        mtx.unlock();

        if(!wait_queue.empty()){
            Customer C = wait_queue.front();
            if(C.is_handle_basket() && swim_pool.return_bathroom_number () > 0)
                wait_queue.pop_front();

            if(!C.is_handle_basket() && swim_pool.return_basket_number () > 0){
                C.set_has_basket(true);
                wait_queue.pop_front();
                if(swim_pool.return_bathroom_number () <= 0 ){
                    wait_queue.push_front(C);
                }
                continue;
            }

            int duration = C.get_swim_time ();
            thread swim(customer_swim,duration);
        //	swimThreads.push_back(swim);
            swim.detach();
        }
        usleep(1000000);
    }

    //TODO release basket & bathroom here
    while(swim_pool.get_swimmer() > 0);

    mtx.lock();
    printf("clean up!\n");
    mtx.unlock();

}

void generate_customer(){

    while(is_business_time){
        Customer C;

        //set_value(has_basket , duration);
        //add poission variable here
        C.set_values(false,4000);

        mtx.lock();
        printf("check = %d %d\n", swim_pool.return_basket_number (), swim_pool.return_bathroom_number ());
        mtx.unlock();

        assert(swim_pool.return_basket_number () >= 0);
        assert(swim_pool.return_bathroom_number () >= 0);

        if(swim_pool.return_basket_number () <= 0){
            C.set_has_basket(false);
            wait_queue.push_back(C);
        }
        else{
            C.set_has_basket(true);
            if(swim_pool.return_bathroom_number () <= 0)
                wait_queue.push_front(C);
            else{
                int duration = C.get_swim_time ();
                thread swim(customer_swim,duration);
            //	swimThreads.push_back(swim);
                swim.detach();
            }
        }
        float timing = generateTiming(lumbdaCome);
        usleep(((int)(timing))*1000);
    }

    //TODO release basket & bathroom here
}

void customer_swim(int duration){

    mtx.lock();
    swim_pool.add_swimmer();
    mtx.unlock();

    //change to swim_suit
    change_swim_suit();



//	if(!is_business_time){
//		std::terminate();
//	}
    //swim
    float timing = generateTiming(lumbdaSwim);
    //printf("timing = %f\n", timing*100);
    int i = 0;
    while(i < (int)(timing*100)){
        if(is_business_time)
            usleep(1000000);
        else
         break;
        i++;
    }




    //change to street_suit
    change_street_suit();

}

void change_swim_suit(){//deadlock happen before.
    swim_pool.take_basket();
    swim_pool.take_bathroom();
    //TODO phase2
    //Sleep()
    swim_pool.release_bathroom();

    mtx.lock();
    printf("swim!\n");
    mtx.unlock();

}

void change_street_suit(){

    swim_pool.take_bathroom();
    //TODO phase2
    //Sleep()
    swim_pool.release_basket();
    swim_pool.release_bathroom();
    mtx.lock();
    printf("leave swim!\n");
    mtx.unlock();

    mtx.lock();
    swim_pool.delete_swimmer();
    mtx.unlock();
}


float generateTiming(float lumbda){
    float g = ( (-1.0)*(float)log(1.0 - (float)rand()/(float)RAND_MAX))/lumbda;
    return g;
}

