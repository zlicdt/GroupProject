#include <stdbool.h>
struct outputDate {
    int year;
    int month;
    int day;
    int hour;
};
struct userChoiceDate {
    int choice;
    int availableTimeCount;
    int startHour;
};
struct userChoiceInfo {
    struct outputDate userChoiceDate;
    int roomSize;
};
struct DatePack {
    struct outputDate Today;
    struct outputDate Tomorrow;
    struct outputDate dayAfterTomorrow;
};
struct verifyInfo {
    char username[256];
    bool isVerified;
};