// Name: Plamen Velkov

#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

	class Utilities 
	{
	private:
		int m_widthField = 1;
		static char m_delimiter;

	public:
		void setFieldWidth(size_t field_width);
		size_t getFieldWidth() const;
		const std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(const char delim);
		const char getDelimiter() const;
	};

#endif // !UTILITIES_H
