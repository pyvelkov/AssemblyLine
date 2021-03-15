// Name: Plamen Velkov

#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H

#include <iostream>
#include <string>
#include <algorithm>
#include "Item.h"
#include "Utilities.h"

struct ItemInfo
{
	std::string m_itemName;
	unsigned int m_serialNumber = 0;
	bool m_fillState = false;

	ItemInfo(std::string src) : m_itemName(src) {};
};

class CustomerOrder
{
private:
	Utilities util_temp;
	std::string m_name;
	std::string m_product;
	unsigned int m_cntItem;
	ItemInfo** m_lstItem;
	static size_t m_widthField;

public:
	CustomerOrder();
	CustomerOrder(std::string& str_in_file);
	//DO NOT ALLOW COPYING - MIGHT HAVE TO CHANGE TO THROW STATEMENT
	CustomerOrder(const CustomerOrder&)
	{
		throw "ERROR: Cannot make copies.";
	}
	CustomerOrder& operator=(const CustomerOrder&) = delete;
	CustomerOrder(CustomerOrder&&) noexcept;
	CustomerOrder& operator=(CustomerOrder&&);
	~CustomerOrder();

	bool getItemFillState(std::string) const;
	bool getOrderFillState() const;
	void fillItem(Item& item, std::ostream&);
	void display(std::ostream&) const;

};

#endif // !CUSTOMERORDER_H
