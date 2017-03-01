#ifndef CUSTOMER_H
#define CUSTOMER_H

class Customer{
    private:
        bool has_basket;
        int swim_time;
        int change_suit_time;
    public:
        void set_values (bool,int);
        void set_has_basket(bool);
        int get_swim_time();
        bool is_handle_basket(){
            return has_basket;
        }


};

#endif // CUSTOMER_H
