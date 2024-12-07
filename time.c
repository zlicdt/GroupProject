#include <stdio.h>
#include <time.h>
#include "structs.h"

struct outputDate getDate(void)
{
	struct tm *tblock;
	time_t current_time;
  
	time(&current_time);
  	tblock = localtime(&current_time);
    struct outputDate returnValue = {
        tblock -> tm_year + 1900,
        tblock -> tm_mon + 1,
        tblock -> tm_mday,
        tblock -> tm_hour + 1
    };
  	return returnValue;
}

// Next part is L11T2
struct date {
    int month;
    int day;
    int year;
};
int isLeapYear(unsigned year) {
    return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}
int isLongMonth(unsigned month) {
    unsigned LongMonth[7] = {1, 3, 5, 7, 8, 10, 12};
    for (int i = 0; i < 7; i++) {
        if (month == LongMonth[i]) return 1;
    }
    return 0;
}
struct outputDate findNextDay(int month, int day, int year) {
    if(isLongMonth(month)) {
        if (day == 31) {
            if (month == 12) {
                month       = 1;
                year       += 1;
                day         = 1;
            } else {
                month      += 1;
                day         = 1;
            }
        } else {
            day            += 1;
        }
    } else {
        if (day == 30) {
            day             = 1;
            month          += 1;
        } else if (day == 29) {
            if (month == 2) {
                month      += 1;
                day         = 1;
            } else {
                day        += 1;
            }
        } else if (day == 28) {
            if (month == 2) {
                if (isLeapYear(year)) {
                    day    += 1;
                } else {
                    month  += 1;
                    day     = 1;
                }
            } else {
                day        += 1;
            }
        } else day         += 1;
    }
    struct outputDate nextDay = {year, month, day, 8};
    return nextDay;
}
struct outputDate getNextDay(struct outputDate Today) {
    // For leap year, month 2 has 29 days
    struct outputDate res = findNextDay(Today.month, Today.day, Today.year);
    // Just use pointer to deliver the result
    return res;
}