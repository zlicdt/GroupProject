#include <stdio.h>
#include <stdbool.h>
#include "structs.h"
typedef struct {
    int year;
    int month;
    int day;
} dateFormatInClear;
typedef struct {
    int year;
    int month;
    int day;
    int hour;
    char name[256];
} tempStruct;
bool isDateEarlierThanCurrent(dateFormatInClear dateInFile, struct outputDate currentTime) {
    if (dateInFile.year < currentTime.year) {
        return true;
    } else if (dateInFile.year == currentTime.year) {
        if (dateInFile.month < currentTime.month) {
            return true;
        } else if (dateInFile.month == currentTime.month) {
            if (dateInFile.day < currentTime.day) {
                return true;
            }
        }
    }
    return false;
}
// Look if the date is earlier than the current date
bool clearPreviousData(struct outputDate currenTime) {
    char classroomName[256] = {0};
    int classroomSize;
    FILE *file_ClassroomInfo = fopen("Classroom_info.txt", "r");
    if (file_ClassroomInfo == NULL) {
        return false;
    }
    dateFormatInClear dateInFile;
    tempStruct temp;
    while(true) {
        if (fscanf(file_ClassroomInfo, "%s %d", classroomName, &classroomSize) == EOF) break;
        char path[256];
        sprintf(path, "bookinfo/%s", classroomName);
        FILE *file_bookinfo = fopen(path, "r");
        if (file_bookinfo == NULL) {
            fclose(file_ClassroomInfo);
            return false;
        }
        FILE *file_temp = fopen("temp.txt", "w");
        if (file_temp == NULL) {
            fclose(file_ClassroomInfo);
            fclose(file_bookinfo);
            return false;
        }
        // Read the data from the file
        // Copy the date after currentTime to the temp file
        // and replace the original file with the temp file
        
        while (true) {
            if (fscanf(file_bookinfo, "%d %d %d %d %s", &temp.year, &temp.month, &temp.day, &temp.hour, temp.name) == EOF) break;
            dateInFile.year = temp.year;
            dateInFile.month = temp.month;
            dateInFile.day = temp.day;
            if (!isDateEarlierThanCurrent(dateInFile, currenTime)) {
                fprintf(file_temp, "%d %d %d %d %s\n", temp.year, temp.month, temp.day, temp.hour, temp.name);
            }
        }
        fclose(file_bookinfo);
        fclose(file_temp);
        remove(path);
        rename("temp.txt", path);
    }
    fclose(file_ClassroomInfo);
    return true;
}