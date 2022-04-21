#include "Source.h"


Date::Date(int date, int month, int year)
{
	setDate(date, month, year);
}

void Date::setDate(int date, int month, int year)
{
	m_date = date;
	m_month = month;
	m_year = year;
}