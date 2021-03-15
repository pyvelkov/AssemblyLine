// Name: Plamen Velkov
#include "CustomerOrder.h"

size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder() : m_name{ "" }, m_product{ "" }, m_cntItem{ 0 }, m_lstItem{ nullptr }
{
	//default constructor init
}

CustomerOrder::CustomerOrder(std::string& str_in_file) {
	size_t pos = 0;
	size_t temp_pos;
	bool more_tkf = true;

	m_name = util_temp.extractToken(str_in_file, pos, more_tkf);
	m_product = util_temp.extractToken(str_in_file, pos, more_tkf);
	temp_pos = pos;
	do 
	{
		std::string temp = util_temp.extractToken(str_in_file, pos, more_tkf);
		m_cntItem++;
	} while (pos > 0);

	pos = temp_pos;
	m_lstItem = new ItemInfo * [m_cntItem];

	for (size_t i = 0; i < m_cntItem; ++i) 
	{
		std::string temp = util_temp.extractToken(str_in_file, pos, more_tkf);
		m_lstItem[i] = new ItemInfo(temp);
	}

	//update field width for display to use later
	if (m_widthField < m_name.length()) m_widthField = m_name.length() + 1;
}

CustomerOrder::CustomerOrder(CustomerOrder&& cust_order) noexcept
{
	*this = std::move(cust_order);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& cust_order)
{
	if (this != &cust_order)
	{
		m_lstItem = cust_order.m_lstItem;
		m_cntItem = cust_order.m_cntItem;
		m_product = cust_order.m_product;
		m_name = cust_order.m_name;

		cust_order.m_lstItem = nullptr;
		cust_order.m_cntItem = 0;
	}
	return *this;
}

CustomerOrder::~CustomerOrder()
{
	delete[] m_lstItem;
	m_lstItem = { nullptr };
}

bool CustomerOrder::getItemFillState(std::string item_name) const
{
	for (size_t i = 0; i < m_cntItem; ++i)
	{
		if (m_lstItem[i]->m_itemName == item_name) return m_lstItem[i]->m_fillState;
	}
	return true;
}

bool CustomerOrder::getOrderFillState() const
{
	for (size_t i = 0; i < m_cntItem; i++)
	{
		if (m_lstItem[i]->m_fillState == false) return false;
	}
	return true;
}

void CustomerOrder::fillItem(Item& item, std::ostream& os)
{
	for (size_t i = 0; i < m_cntItem; i++)
	{
		if (item.getName() == m_lstItem[i]->m_itemName)
		{
			if (item.getQuantity() > 0)
			{
				//might need an if nested.
				item.updateQuantity();
				m_lstItem[i]->m_serialNumber = item.getSerialNumber();
				m_lstItem[i]->m_fillState = true;
				os << "Filled " << m_name << ", " << m_product << "[" << m_lstItem[i]->m_itemName << "]" << std::endl;
			}
			else
			{
				if (m_lstItem[i]->m_fillState == true) os << " Unable to fill " << m_name << ", " << m_product << "[" << m_lstItem[i]->m_itemName << "]" << std::endl;
			}
		}
	}
}

void CustomerOrder::display(std::ostream& os) const 
{
	os << m_name << " - " << m_product << std::endl;
	for (unsigned int i = 0; i < m_cntItem; i++) 
	{
		os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << std::setfill(' ') << "] "
			<< std::setw(m_widthField) << m_lstItem[i]->m_itemName << " - " << (m_lstItem[i]->m_fillState ? "FILLED" : "MISSING")
			<< std::endl;
	}
}