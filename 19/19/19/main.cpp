#include <cstdio>
#include <cstdlib>
#include <iostream>

#define FYEAR 2001 //finishing year

using namespace std;

enum dayNames { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };
enum monthNames { January = 1, February, March, April, May, June, July, August, September,
				  October, November, December };

class Day
{
	public:
		Day()
		{
			numberOfDay = -1;
			dayOfWeek = Monday;
		}
	
		Day(int n, dayNames d)
		{
			numberOfDay = n;
			dayOfWeek = d;
		}
		
		~Day()
		{
		
		}
		
		int init(int n, dayNames d)
		{
			numberOfDay = n;
			dayOfWeek = d;
		}
		
		int nDay()
		{
			return numberOfDay;
		}
		
		dayNames dWeek()
		{
			return dayOfWeek;
		}
		
	protected:
		int numberOfDay;
		dayNames dayOfWeek; //Monday is 0, through
		
};

class Month 
{
	public:
		static int numSundays;
		Month()
		{
			numDays = 0;
	//		cout << "Making Month." << endl;
		}
		
		Day init(monthNames m, dayNames startDay, int y)
		{
//			cout << "Initializing Month " << m 
//				 << " starting with day " << startDay 
//				 << " of year " << y;
			monthOfYear = m;
			year = y;
			switch(monthOfYear) 
			{
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
					numDays = 31;
					break;
				case 4:
				case 6:
				case 9:
				case 11:
					numDays = 30;
					break;
				case 2:
					if(year % 400 == 0)
					{
						numDays = 29;
					} 
					else if (year % 4 == 0 && year % 100 != 0)
					{
						numDays = 29;
					}
					else
					{
						numDays = 28;
					}
					break;
			}
//			cout << " with " << numDays << " days." << endl;
			dayNames d = startDay;
			for (int i = 1; i <= numDays; i++)
			{
				days[i-1].init(i, d);
				if(d == 6)
				{
//					cout << " <---- d == 6, i == " << i << "." << endl;
					d = (dayNames)0;
					if(i == 1 && year >= 1901 && year <= 2000)
					{
//						cout << "Incrementing numSundays" << endl;
						numSundays++;
					}
				}
				else
				{
					d = (dayNames)(d + 1);
				}
			}
			return days[numDays-1];
		}
		
		~Month()
		{
//			cout << "Destructing Month" << endl;
		}
		
		
		
	protected:
		Month(Month& m){}
		Day days[32];
		int numDays;
		int year;
		
		monthNames monthOfYear;
};
int Month::numSundays = 0;

class Calendar
{
	public:
		Calendar(int initNDay, dayNames initDay, monthNames initMonth, int initYear)
		{
//			cout << "Making Calendar." << endl;
			int numYears = FYEAR - initYear;
			numMonths = numYears * 12;
			month = new Month[numMonths];
			
			Day previousLastDay;
			previousLastDay = month[0].init(initMonth, initDay, initYear);
			
			int year = initYear;
			dayNames nd;
			for(int i = 1; i < numMonths; i++)
			{
				if (previousLastDay.dWeek() == 6)
				{
					nd = (dayNames)0;
				}
				else
				{
					nd = (dayNames)(previousLastDay.dWeek() + 1);
				}
					
				previousLastDay = month[i].init((monthNames)((i % 12)+1), nd, year);
				if ((i + 1) % 12 == 0)
				{
					year++;
				}
			}
				
		}
		
	protected:
		Month* month;
		int numMonths;
};

int main (int argc, char *argv[])
{
	
	Calendar(1,(dayNames)0,(monthNames)1,1900);
	
	cout << "There are " << Month::numSundays << " Sundays." << endl;
	
	
	return 0;
}

