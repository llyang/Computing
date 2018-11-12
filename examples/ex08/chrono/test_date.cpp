#include <iostream>

#include "Chrono.h"

using std::cout;

int main()
{
  cout << "The default date is " << Chrono::default_date() << '\n';

  Chrono::Date d1 { 1900, Chrono::Month::Feb, 28 };
  cout << "d1 = " << d1 << '\n';
  Chrono::Date d2 { 2000, Chrono::Month::Feb, 29 };
  cout << "d2 = " << d2 << '\n';

  Chrono::Date d3 { d1 };
  cout << "Testing copy constructor: d3 = " << d3 << '\n';

  d3 = d2;
  cout << "Testing copy assignment: d3 = " << d3 << '\n';

  cout << std::boolalpha;
  cout << "Testing == operator: d3 == d1? " << (d3 == d1) << '\n';
  cout << "Testing != operator: d3 != d1? " << (d3 != d1) << '\n';

  d3.add_year(5);
  cout << "Testing add_year: d3 = " << d3 << '\n';

  d3.add_month(100);
  cout << "Testing add_month: d3 = " << d3 << '\n';

  d3.add_day(1000);
  cout << "Testing add_day: d3 = " << d3 << '\n';

  Chrono::Day dow = Chrono::day_of_week(Chrono::default_date());
  cout << "Testing day_of_week: " << dow << '\n';

  dow = Chrono::day_of_week(Chrono::Date { 2017, Chrono::Month::Nov, 16 });
  cout << "Testing day_of_week: " << dow << '\n';
}
