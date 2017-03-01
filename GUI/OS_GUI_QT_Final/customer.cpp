#include "customer.h"

Customer::Customer()
{
    has_basket = false;
    swim_time = 0;
    change_suit_time = 0;
}

void Customer::set_values (bool has_basket, int swim_time) {
  this->has_basket = has_basket;
  this->swim_time = swim_time;
}

void Customer::set_has_basket (bool has_basket) {
  this->has_basket = has_basket;
}

int Customer::get_swim_time () {
  return swim_time;
}
