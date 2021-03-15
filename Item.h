// Name: Plamen Velkov

#ifndef ITEM_H
#define ITEM_H

#include <ostream>
#include <string>
#include <iomanip>

	class Item 
	{
	private:
		std::string m_name;
		std::string m_description;
		int m_serialNumber;
		int m_quantity;
		unsigned static int m_widthField;

	public:
		Item();
		Item(const std::string& item);

		const std::string& getName() const;
		const unsigned int getSerialNumber();
		const unsigned int getQuantity();
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
#endif // !ITEM_H
