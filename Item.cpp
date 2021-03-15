// Name: Plamen Velkov

#include "Utilities.h"
#include "Item.h"

unsigned int Item::m_widthField = 0;

Item::Item()
{
	m_name = "";
	m_description = "";
	m_serialNumber = 0;
	m_quantity = 0;
	m_widthField = 0;
}

Item::Item(const std::string& item)
{
	Utilities object;
	size_t pos = 0;
	bool more_tkf = false;

	//name extraction
	m_name = object.extractToken(item, pos, more_tkf);

	//Serial num extraction
	m_serialNumber = stoi(object.extractToken(item, pos, more_tkf));
	//quantity extraction
	m_quantity = stoi(object.extractToken(item, pos, more_tkf));
	//description extraction
	m_description = object.extractToken(item, pos, more_tkf);

	//update field width for display to use later
	if (m_widthField < m_name.length()) m_widthField = m_name.length() + 1;
}

const std::string& Item::getName() const
{
	return m_name;
}

const unsigned int Item::getSerialNumber()
{
	return m_serialNumber++;
}

const unsigned int Item::getQuantity()
{
	return m_quantity;
}

void Item::updateQuantity()
{
	if (m_quantity > 0) m_quantity--;
}

void Item::display(std::ostream& os, bool full) const
{
	if (full == false) 
	{
		os << std::left << std::setw(m_widthField) << getName() << "[" << std::right << std::setw(6) << std::setfill('0') << m_serialNumber << std::setfill(' ') << "]" << std::setfill(' ') << std::endl;
	}
	else 
	{
		os << std::left << std::setw(m_widthField) << getName() << "[" << std::right << std::setw(6) << std::setfill('0') << m_serialNumber << std::setfill(' ') << "] " << "Quantity: " << std::left << std::setw(m_widthField) << m_quantity << "Description: " << m_description << std::endl;
	}
}