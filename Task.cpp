// Name: Plamen Velkov

#include "Task.h"

Task::Task(const std::string& str_in_file) : Item(str_in_file)
{
	m_pNextTask = nullptr;
}

void Task::runProcess(std::ostream& os)
{
	if (m_orders.size() > 0)
	{
		if (m_orders.back().getOrderFillState() == false) m_orders.back().fillItem(std::ref(*this), os);
	}
}

bool Task::moveTask()
{
	if (m_orders.size() == 0) return false;

	if (m_orders.size() > 0 && m_orders.back().getItemFillState(getName()) == true)
	{
		if (m_pNextTask != nullptr)
		{
			*m_pNextTask += std::move(m_orders.back());
			m_orders.pop_back();
		}
	}
	return true;
}

void Task::setNextTask(Task& set_n_task)
{
	m_pNextTask = &set_n_task;
}

bool Task::getCompleted(CustomerOrder& cust_order)
{
	if (m_orders.size() == 0) return false;
	else
	{
		if (m_orders.size() > 0 && m_orders.back().getOrderFillState())
		{
			cust_order = std::move(m_orders.back());
			m_orders.pop_back();
			return true;
		}
		else return false;
	}
}

void Task::validate(std::ostream& os)
{
	os << getName() << " --> ";
	if (m_pNextTask)
	{
		os << m_pNextTask->getName();
		os << std::endl;
	}
	else
	{
		os << "END OF LINE";
		os << std::endl;
	}
}

Task& Task::operator+=(CustomerOrder&& cust_order)
{
	m_orders.push_front(std::move(cust_order));
	return *this;
}