#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "structs.h"
struct verifyInfo verify(void) {
    char username[256], password[256];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    FILE *file = fopen("account.txt", "r");
    if (file == NULL) {
        perror("Failed to open file");
        return (struct verifyInfo) {"Account invalid", false};
    }

    char file_username[256];
    char file_password[256];
    bool result = false;

    while (fscanf(file, "%255s %255s", file_username, file_password) == 2) {
        if (strcmp(username, file_username) == 0 && strcmp(password, file_password) == 0) {
            result = true;
            break;
        }
    }
    fclose(file);
    struct verifyInfo verifyInfoInstance;
    strcpy(verifyInfoInstance.username, username);
    verifyInfoInstance.isVerified = result;
    return verifyInfoInstance;
}
struct verifyInfo isVerified(void) {
    struct verifyInfo verifyInstance;
    for (int i = 0; i < 3; i++) {
        verifyInstance = verify();
        if (verifyInstance.isVerified) {
            return verifyInstance;
        }
        printf("Invalid account name or password!\n");
    }
    printf("You have failed three times!\n");
    return verifyInstance;
}