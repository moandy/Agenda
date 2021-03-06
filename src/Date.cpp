#include"Date.hpp"
#include<iostream>
#include<sstream>
#include<string>
using namespace std;
Date::Date() {
	m_year = m_month = m_day = m_hour = m_minute = 0;
}
Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute) {
	m_year = t_year;
	m_month = t_month;
	m_day = t_day;
	m_hour = t_hour;
	m_minute = t_minute;
}
Date::Date(std::string dateString) {
	*this = stringToDate(dateString);
}
int Date::getYear(void) const {
	return m_year;
}
void Date::setYear(const int t_year) {
	m_year = t_year;
}
int Date::getMonth(void) const {
	return m_month;
}
void Date::setMonth(const int t_month) {
	m_month = t_month;
}
int Date::getDay(void) const {
	return m_day;
}
void Date::setDay(const int t_day) {
	m_day = t_day;
}
int Date::getHour(void) const {
	return m_hour;
}
void Date::setHour(const int t_hour) {
	m_hour = t_hour;
}
int Date::getMinute(void) const {
	return m_minute;
}
void Date::setMinute(const int t_minute) {
	m_minute = t_minute;
}
bool Date::isValid(const Date t_date) {
	if (t_date.m_year >= 1000&&t_date.m_year <= 9999&&
		t_date.m_month >= 1&&t_date.m_month <= 12&&
		t_date.m_day >= 1&&t_date.m_day <= 31&&
		t_date.m_hour >= 0&&t_date.m_hour <= 23&&
		t_date.m_minute >=0&&t_date.m_minute <= 59) {
		int a[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		if (t_date.m_year % 400 == 0||t_date.m_year % 4 == 0&&t_date.m_year % 100 != 0) {
			a[1] = 29;
		}
		if (t_date.m_day > a[t_date.m_month - 1]) {
			return false;
		}
		return true;
	}
	return false;
}
Date Date::stringToDate(const std::string t_dateString) {
	Date temp1;
	if (t_dateString.length() != 16)
		return temp1;
	if (t_dateString[4] != '-'||t_dateString[7] != '-'||t_dateString[10] != '/'||t_dateString[13] != ':')
		return temp1;
	string year = "", month = "", day = "", hour = "", minute = "";
	year = t_dateString.substr(0, 4);
	month = t_dateString.substr(5, 2);
	day = t_dateString.substr(8, 2);
	hour = t_dateString.substr(11, 2);
	minute = t_dateString.substr(14, 2);
	int y = atoi(year.c_str());
	int mo = atoi(month.c_str());
	int d = atoi(day.c_str());
	int h = atoi(hour.c_str());
	int m = atoi(minute.c_str());
	Date temp(y, mo, d, h, m);
	if (!isValid(temp))
		return temp1;
	return temp;
}
string change(int a) {
	stringstream ss;
	string result = "", n = "";
	ss << a;
	ss >> n;
	if (n.length() == 0) {
		result = "00";
	} else if (n.length() == 1) {
		result = '0';
		result+=n;
	} else if (n.length() == 2) {
		result = n;
	} else if (n.length() == 3) {
		result = n;
	} else if (n.length() == 4) {
		result = n;
	}
	return result;
}
std::string Date::dateToString(Date t_date) {
	if (!isValid(t_date)) {
		string ss = "0000-00-00/00:00";
		t_date.setMinute(0);
		t_date.setHour(0);
		t_date.setDay(0);
		t_date.setMonth(0);
		t_date.setYear(0);
		return ss;
	}
	string str = "";
	str += change(t_date.m_year) + "-" + change(t_date.m_month);
	str += "-" + change(t_date.m_day) + "/" + change(t_date.m_hour) + ":" + change(t_date.m_minute);
	return str;
}
Date& Date::operator=(const Date &t_date) {
	m_year = t_date.m_year;
	m_month = t_date.m_month;
	m_day = t_date.m_day;
	m_hour = t_date.m_hour;
	m_minute = t_date.m_minute;
	return *this;
}
bool Date::operator==(const Date &t_date) const {
	if (m_year == t_date.m_year&&m_month == t_date.m_month&&m_day == t_date.m_day&&
		m_hour == t_date.m_hour&&m_minute == t_date.m_minute) {
		return true;
	} else {
		return false;
	}
}
bool Date::operator>(const Date &t_date) const {
	return dateToString(*this) > dateToString(t_date);
}
bool Date::operator<(const Date &t_date) const {
	return dateToString(*this) < dateToString(t_date);
}
bool Date::operator>=(const Date &t_date) const {
	return (dateToString(*this) > dateToString(t_date))||((*this) == t_date);
}
bool Date::operator<=(const Date &t_date) const {
	return (dateToString(*this) < dateToString(t_date))||((*this) == t_date);
}
