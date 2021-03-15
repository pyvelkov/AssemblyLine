// Name: Plamen Velkov

#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
#include <fstream>
#include "Task.h"
#include "CustomerOrder.h"
#include "Utilities.h"

#ifndef LINEMANAGER_H
#define LINEMANAGER_H

class LineManager
{
private:
	std::vector<Task*> AssemblyLine;
	std::deque<CustomerOrder> ToBeFilled;
	std::deque<CustomerOrder> Completed;
	unsigned int m_cntCustomerOrder = 0;
	Utilities util_temp;

public:
	LineManager(const std::string& file_name, std::vector<Task*>& task, std::vector<CustomerOrder>& cust_order);
	bool run(std::ostream& os);
	void displayCompleted(std::ostream& os) const;
	void validateTasks() const;

};
#endif // !LINEMANAGER_H