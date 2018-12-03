#ifndef _CHRONO_H
#define _CHRONO_H

#include <iostream>

namespace Chrono {

enum class Month {
  Jan = 1,
  Feb,
  Mar,
  Apr,
  May,
  Jun,
  Jul,
  Aug,
  Sep,
  Oct,
  Nov,
  Dec
};

enum class Day {
  Sun,
  Mon,
  Tue,
  Wed,
  Thu,
  Fri,
  Sat
};

std::ostream& operator<<(std::ostream& os, Month m);
std::ostream& operator<<(std::ostream& os, Day d);

Month& operator++(Month& m);

class Date {
public:
  class Invalid {
  };
  Date(int y, Month m, int d);
  Date();
  Date(const Date& dd)
      : y { dd.y }
      , m { dd.m }
      , d { dd.d }
  {
  }

  Date& operator=(const Date& dd);

  int day() const { return d; }
  Month month() const { return m; }
  int year() const { return y; }

  void add_day(int n);
  void add_month(int n);
  void add_year(int n);

private:
  int y; // year
  Month m; // month
  int d; // day of month
};

const Date& default_date();

int days_in_month(int y, Month m);
bool is_date(int y, Month m, int d);
bool leapyear(int y);

Day day_of_week(const Date& dd);

bool operator==(const Date& a, const Date& b);
bool operator!=(const Date& a, const Date& b);

std::ostream& operator<<(std::ostream& os, const Date& d);
}

#endif

