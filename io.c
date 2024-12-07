#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "structs.h"

int find(struct userChoiceInfo choice, char username[256]) {
    FILE *classroomInfo = fopen("Classroom_info.txt", "r");
    if (classroomInfo == NULL) {
        perror("Failed to open file\nPlease add Classroom_info.txt to the directory");
        return 0;
    }
    
    
    char room[256];
    int capacity;
    bool roomIsOK = false;
    bool roomIsBooked = false;
    struct outputDate date;
    char dataRoom[256];
    char dataUsername[256];
    char filepath[256];
    while (fscanf(classroomInfo, "%s %d", room, &capacity) != EOF) {
        if (capacity >= choice.roomSize) {
            roomIsOK = true;
            printf("One room that is suite for your requirement is: %s, the capacity is %d.\n", room, capacity);
            snprintf(filepath, sizeof(filepath), "bookinfo/%s", room);
            FILE *dataFile = fopen(filepath, "r");
            if (dataFile == NULL) {
                perror("Failed to open data file");
                return 0;
            }
            while (fscanf(dataFile, "%d%d%d%d%s", &date.year, &date.month, &date.day, &date.hour, dataUsername) != EOF) {
                if ((date.year == choice.userChoiceDate.year) && (date.month == choice.userChoiceDate.month) && (date.day == choice.userChoiceDate.day) && (date.hour == choice.userChoiceDate.hour)) {
                    fclose(dataFile);
                    roomIsBooked = true;
                }
                if (roomIsBooked) {
                    printf("Room %s is booked by %s at %d/%d/%d %d\n", room, dataUsername, date.year, date.month, date.day, date.hour);
                    break;
                }
            }
            if (roomIsBooked) {
                roomIsBooked = false;
                continue;
            } else {
                FILE *dataFileWrite = fopen(filepath, "a");
                if (dataFileWrite == NULL) {
                    perror("Failed to open data filen");
                    return 0;
                }
                fprintf(dataFileWrite, "%d %d %d %d %s\n", choice.userChoiceDate.year, choice.userChoiceDate.month, choice.userChoiceDate.day, choice.userChoiceDate.hour, username);
                fclose(dataFileWrite);
                printf("Room booked successfully!\n");
                break;
            }
            fclose(dataFile);
        }
    }
    fclose(classroomInfo);
    if (!roomIsOK) {
        printf("No room available for your choice!\n");
        printf("You have not booked one room in this case.\n");
        return 0;
    }
    return 0;
}