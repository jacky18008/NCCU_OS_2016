#ifndef SWIM_H
#define SWIM_H
#include <atomic>
#include <mutex>
#include <condition_variable>

class Swimming_Pool{
	private:
		std::atomic<int>  basket;
		std::atomic<int>  bathroom;
		int swimming_person;
	public:
		void set_value(int,int);
		int return_basket_number();
		int return_bathroom_number();
		void add_swimmer();
		void delete_swimmer();
		int get_swimmer();
		void take_basket();
		void take_bathroom();
		void release_basket();
		void release_bathroom();
		
	std::mutex lock;
	std::condition_variable notify_empty_basket;
	std::condition_variable notify_has_basket;
	
	std::condition_variable notify_empty_bathroom;
	std::condition_variable notify_has_bathroom;
};

#endif
