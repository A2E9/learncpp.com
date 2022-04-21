#ifndef SOURCE_H
#define SOURCE_H


class Date
{
private:
	int m_date{};
	int m_month{};
	int m_year{};

public:
	Date(int date, int month, int year);

	void setDate(int date, int month, int year);

	int getYear() const { return m_year; }
	int getMonth() { return m_month; }
	int getDay() { return m_month; }


};






#endif // !SOURCE_H
