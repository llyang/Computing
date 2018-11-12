#include <iostream>
#include <vector>

#include "Chrono.h"

using std::ostream;
using std::string;
using std::vector;

namespace Chrono {

ostream& operator<<(ostream& os, Month m)
{
  const vector<string> month_tbl { "Jan", "Feb", "Mar", "Apr",
    "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

  return os << month_tbl[int(m) - 1];
}

ostream& operator<<(ostream& os, Day d)
{
  const vector<string> day_tbl { "Sun",
    "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

  return os << day_tbl[int(d)];
}

Month operator++(Month& m)
{
  m = (m == Month::Dec) ? Month::Jan : Month(int(m) + 1);
  return m;
}

Date::Date(int yy, Month mm, int dd)
    : y { yy }
    , m { mm }
    , d { dd }
{
  if (!is_date(yy, mm, dd))
    throw Invalid {};
}

const Date& default_date()
{
  static const Date dd { 2017, Month::Nov, 14 };
  return dd;
}

Date::Date()
    : y { default_date().year() }
    , m { default_date().month() }
    , d { default_date().day() }
{
}

Date& Date::operator=(const Date& dd)
{
  y = dd.y;
  m = dd.m;
  d = dd.d;
  return (*this);
}

void Date::add_day(int n)
{
  std::cerr << "The function Date::add_day is not implemented\n";
}

void Date::add_month(int n)
{
  std::cerr << "The function Date::add_month is not implemented\n";
}

void Date::add_year(int n)
{
  y += n;
  // 如果加之前是闰年的2月29日，加完之后不是闰年了，就用2月28日来代替
  if (d > days_in_month(y, m))
    d = days_in_month(y, m);
}

int days_in_month(int y, Month m)
{
  int days { 31 };

  switch (m) {
  case Month::Feb:
    days = (leapyear(y)) ? 29 : 28;
    break;
  case Month::Apr:
  case Month::Jun:
  case Month::Sep:
  case Month::Nov:
    days = 30;
    break;
  default:
    days = 31;
  }

  return days;
}

bool is_date(int y, Month m, int d)
{
  if (d <= 0)
    return false;
  if (m < Month::Jan || Month::Dec < m)
    return false;

  if (days_in_month(y, m) < d)
    return false;

  return true;
}

bool leapyear(int y)
{
  std::cerr << "The function leapyear is not implemented\n";
  return false;
}

Day day_of_week(const Date& dd)
{
  std::cerr << "The function day_of_week is not implemented\n";
  return Day::Sun;
}

bool operator==(const Date& a, const Date& b)
{
  return a.year() == b.year()
      && a.month() == b.month()
      && a.day() == b.day();
}

bool operator!=(const Date& a, const Date& b)
{
  return !(a == b);
}

ostream& operator<<(ostream& os, const Date& d)
{
  return os << '(' << d.year()
            << ',' << d.month()
            << ',' << d.day() << ')';
}

}
