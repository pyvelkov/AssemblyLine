// Name: Plamen Velkov

#include <iostream>
#include <functional>
#include <deque>
#include <string>
#include "Item.h"
#include "CustomerOrder.h"

#ifndef TASK_H
#define TASK_H


class Task : public Item
{
private:
	std::deque<CustomerOrder> m_orders;
	Task* m_pNextTask = nullptr;

public:
	Task(const std::string& str_in_file);
	Task(const Task&) = delete;
	Task& operator=(const Task&) = delete;
	Task(Task&&) = delete;
	Task& operator=(Task&&) = delete;

	void runProcess(std::ostream& os);
	bool moveTask();
	void setNextTask(Task&);
	bool getCompleted(CustomerOrder&);
	void validate(std::ostream& os);
	Task& operator+=(CustomerOrder&&);

};
#endif // !TASK_H