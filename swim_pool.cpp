#include "swim_pool.h"

void Swimming_Pool::set_value(int basket, int bathroom){
	this->basket = basket;
	this->bathroom = bathroom;
	this->swimming_person = 0;
}

int Swimming_Pool::return_basket_number () {
  return basket;
}

int Swimming_Pool::return_bathroom_number () {
  return bathroom;
}

void Swimming_Pool::add_swimmer () {
  swimming_person++;
}

void Swimming_Pool::delete_swimmer () {
  swimming_person--;
}

int Swimming_Pool::get_swimmer () {
  return swimming_person;
}


void Swimming_Pool::take_basket () {
	std::unique_lock<std::mutex> l(lock);
	
	notify_has_basket.wait(l, [this](){return basket > 0; });
	
	basket--;
	
	notify_empty_basket.notify_one();
}

void Swimming_Pool::take_bathroom () {
	std::unique_lock<std::mutex> l(lock);
	notify_has_bathroom.wait(l, [this](){return bathroom > 0; });
	
	bathroom--;
	
	notify_empty_bathroom.notify_one();
}

void Swimming_Pool::release_basket () {
	std::unique_lock<std::mutex> l(lock);
	
	notify_empty_basket.wait(l, [this](){return true; });
	
	basket++;
	
	notify_has_basket.notify_one();
}

void Swimming_Pool::release_bathroom () {
	std::unique_lock<std::mutex> l(lock);
	notify_empty_bathroom.wait(l, [this](){return true; });
	
	bathroom++;
	
	notify_has_bathroom.notify_one();
}

