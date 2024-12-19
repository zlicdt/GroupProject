#include <stdio.h>
#include "define.h"
#include "structs.h"
struct userChoiceInfo displayTimeChoiceMenu(struct userChoiceDate userChoice, struct DatePack datePack);
struct outputDate getNextDay(struct outputDate);
struct userChoiceInfo displayDateChoiceMenu(void) {
    struct outputDate Today = getDate();
    struct outputDate Tomorrow = getNextDay(Today);
    struct outputDate dayAfterTomorrow = getNextDay(Tomorrow);
    unsigned short choice;
    printf("1. %d/%d/%d (today)\n", Today.year, Today.month, Today.day);
    printf("2. %d/%d/%d (tomorrow)\n", Tomorrow.year, Tomorrow.month, Tomorrow.day);
    printf("3. %d/%d/%d (the day after tomorrow)\n", dayAfterTomorrow.year, dayAfterTomorrow.month, dayAfterTomorrow.day);
    printf("4. Exit\n");
    dayChoiceFailureFallback:
    printf("Please enter your choice: ");
    scanf("%d", &choice);
    int availableTimeCount = 8;
    if (!(choice >= 1 && choice <= 4)) {
        printf("You enterd a wrong number!\n");
        goto dayChoiceFailureFallback;
    }
    if (choice == 1) {
        Today.hour += 1;
        availableTimeCount = 17 - Today.hour;
    }
    if (choice == 4) {
        return (struct userChoiceInfo) {
            {0, 0, 0, 0},
            0
        };
    }
    if (availableTimeCount <= 0) availableTimeCount = 0;
    struct userChoiceDate userChoice = {choice, availableTimeCount, Today.hour - 1};
    // In this case res.hour is same as availableTimeCount
    struct DatePack datePack = {
        Today,
        Tomorrow,
        dayAfterTomorrow
    };
    struct userChoiceInfo returnOfDisplayTimeChoiceMenu = displayTimeChoiceMenu(userChoice, datePack);
    return returnOfDisplayTimeChoiceMenu;
}

struct userChoiceInfo displayTimeChoiceMenu(struct userChoiceDate userChoice, struct DatePack datePack) {
    int startHour = 9;
    if (userChoice.choice == 1) {
        startHour = userChoice.startHour > 9 ? userChoice.startHour : 9;
        startHour = userChoice.startHour > 17 ? 17 : startHour;
        userChoice.availableTimeCount = 17 - startHour;
    }
    int startHourUseInNext = startHour;
    int i;
    for (i = 0; i < userChoice.availableTimeCount; i++) {
        printf("%d. %d:00 %s - %d:50 %s\n", i + 1,
                                            startHour + i > 12 ? startHour + i - 12 : startHour + i,
                                            startHour + i >= 12 ? "pm" : "am",
                                            startHour + i > 12 ? startHour + i - 12 : startHour + i,
                                            startHour + i >= 12 ? "pm" : "am");
    }
    printf("%d. Exit\n", userChoice.availableTimeCount + 1);
    unsigned short userChoiceTime;
    int userExpectRoomSize;
    hourChoiceFailureFallback:
    printf("Please enter your choice: ");
    scanf("%d", &userChoiceTime);
    if (!(userChoiceTime >= 1 && userChoiceTime <= userChoice.availableTimeCount + 1)) {
        printf("You enterd a wrong number!\n");
        goto hourChoiceFailureFallback;
    }
    if (userChoiceTime == userChoice.availableTimeCount + 1) {
        struct userChoiceInfo returnOfDisplayTimeChoiceMenu = {
            {0, 0, 0, 0},
            0
        };
        return returnOfDisplayTimeChoiceMenu;
    }
    printf("Input the size of classroom: ");
    scanf("%d", &userExpectRoomSize);
    switch (userChoice.choice) {
        case 1:
            return (struct userChoiceInfo) {
                {
                    datePack.Today.year,
                    datePack.Today.month,
                    datePack.Today.day,
                    startHourUseInNext + userChoiceTime - 1
                },
                userExpectRoomSize
            };
        case 2:
            return (struct userChoiceInfo) {
                {
                    datePack.Tomorrow.year,
                    datePack.Tomorrow.month,
                    datePack.Tomorrow.day,
                    userChoiceTime + 8
                },
                userExpectRoomSize
            };
        case 3:
            return (struct userChoiceInfo) {
                {
                    datePack.dayAfterTomorrow.year,
                    datePack.dayAfterTomorrow.month,
                    datePack.dayAfterTomorrow.day,
                    userChoiceTime + 8
                },
                userExpectRoomSize
            };
    }
}
