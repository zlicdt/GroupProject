/*
    Copy right (C) 2024, Group KiraNeko
    Members: 
        ZHU Haoming 2430026302@mail.uic.edu.cn

    This file is the main file of the program.
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "structs.h"
#include "define.h"
int find(struct userChoiceInfo choice, char username[256]);
bool clearPreviousData(struct outputDate currenTime);
int main() {
    struct verifyInfo verifyInstance = isVerified();
    if (!verifyInstance.isVerified) return 0;
    FILE *classroomInfo = fopen("Classroom_info.txt", "r");
    if (classroomInfo == NULL) {
        perror("Failed to open file");
        return 0;
    }
    char room[256];
    while (fscanf(classroomInfo, "%s %*d", room) != EOF)
    {
        char filepath[512];
        snprintf(filepath, sizeof(filepath), "bookinfo/%s", room);
        if (access(filepath, F_OK) == -1) {
            FILE *newFile = fopen(filepath, "w");
            if (newFile == NULL) {
                perror("Failed to create file");
                continue;
            }
            fclose(newFile);
        }
    }
    
    while (true) {
        struct userChoiceInfo choice = displayDateChoiceMenu();
        if (choice.roomSize != 0) {
            printf("Your choice is: %d/%d/%d %d:00 %s - %d:50 %s\nRequired room capacity: %d\n",  choice.userChoiceDate.year, 
                                                        choice.userChoiceDate.month,
                                                        choice.userChoiceDate.day,
                                                        choice.userChoiceDate.hour > 12 ? choice.userChoiceDate.hour - 12 : choice.userChoiceDate.hour,
                                                        choice.userChoiceDate.hour >= 12 ? "pm" : "am",
                                                        choice.userChoiceDate.hour > 12 ? choice.userChoiceDate.hour - 12 : choice.userChoiceDate.hour,
                                                        choice.userChoiceDate.hour >= 12 ? "pm" : "am",
                                                        choice.roomSize);
            find(choice, verifyInstance.username);
        } else 
        {
            printf("You have not booked one room in this case.\n");
        }
        
        printf("Continue? (y/n): ");
        char c;
        scanf(" %c", &c);
        if (c == 'n') {
            printf("Bye!\n");
            clearPreviousData(getDate());
            return 0;
        }
    }
}