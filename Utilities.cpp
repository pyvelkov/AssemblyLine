// Name: Plamen Velkov

#include "Utilities.h"

char Utilities::m_delimiter;

	void Utilities::setFieldWidth(size_t field_width) 
	{
		m_widthField = field_width;
	}

	size_t Utilities::getFieldWidth() const 
	{
		return m_widthField;
	}

	const std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) 
	{
		size_t init_pos = next_pos;
		std::string token = str.substr(next_pos, str.find(m_delimiter, next_pos) - init_pos);

		if (getFieldWidth() < token.size()) setFieldWidth(token.size() + 1);

		next_pos = str.find(m_delimiter, next_pos) + 1;
		more = true;

		return token;
	}

	void Utilities::setDelimiter(const char delim) 
	{
		m_delimiter = delim;
	}

	const char Utilities::getDelimiter() const 
	{
		return m_delimiter;
	}