// Name: Plamen Velkov

#include "LineManager.h"

LineManager::LineManager(const std::string& str_in_file, std::vector<Task*>& tasks, std::vector<CustomerOrder>& cust_order)
{
	std::fstream file(str_in_file);
	std::string temp, token;

	//push to front and back
	for (size_t i = 0; i < tasks.size(); i++)
	{
		AssemblyLine.push_back(std::move(tasks[i]));
	}
	for (size_t i = 0; i < cust_order.size(); i++)
	{
		ToBeFilled.push_front(std::move(cust_order[i]));
		m_cntCustomerOrder++;
	}

	//until reaching EOF
	while (getline(file, temp))
	{
		size_t pos = 0;
		bool more_tkr = true;

		token = util_temp.extractToken(temp, pos, more_tkr);
		for (size_t i = 0; i < tasks.size(); i++)
		{
			if (tasks[i]->getName() == token && pos > 0)
			{
				token = util_temp.extractToken(temp, pos, more_tkr);
				for (size_t j = 0; j < tasks.size(); j++)
				{
					if (tasks[j]->getName() == token)
					{
						tasks[i]->setNextTask(*AssemblyLine[j]);
						j = tasks.size();
					}
				}
				i = tasks.size();
			}
		}
	}
}

bool LineManager::run(std::ostream& os)
{
	if (ToBeFilled.size() > 0)
	{
		*(AssemblyLine.at(4)) += std::move(ToBeFilled.back());
		ToBeFilled.pop_back();
	}

	for (size_t i = 0; i < AssemblyLine.size(); i++)
	{
		AssemblyLine.at(i)->runProcess(os);
	}

	for (size_t i = 0; i < AssemblyLine.size(); i++)
	{
		if (AssemblyLine[i]->moveTask())
		{
			CustomerOrder order;
			if (AssemblyLine[i]->getCompleted(order) == true) Completed.push_back(std::move(order));
		}
	}

	if (Completed.size() == m_cntCustomerOrder) return true;
	return false;
}

void LineManager::displayCompleted(std::ostream& os) const
{
	if (Completed.empty() == false)
	{
		for (int i = 0; i < Completed.size(); i++)
		{
			Completed[i].display(os);
		}
	}
}

void LineManager::validateTasks() const
{
	if (AssemblyLine.empty() == false)
	{
		for (unsigned int i = 0; i < AssemblyLine.size(); i++)
		{
			AssemblyLine[i]->validate(std::cout);
		}
	}
}