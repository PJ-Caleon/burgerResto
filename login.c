#include <stdio.h>
#include <string.h>

int login() {
    //defiing lenght
    #define MAX_USERS 10
    #define USERNAME 20
    #define PASSWORD 20

    //defining boolean for access granted
    typedef int bool;
    bool granted;

    //structure to store variable
    typedef struct {
        char username[USERNAME];
        char password[PASSWORD];
    } User;

    //list of acceptable usernames and password
    User users[MAX_USERS] = {
        {"user1", "pass1"},
        {"user2", "pass2"},
        {"PJ", " "},
        {"Genshin","Impact"}
    };

    //initialize variables
    char username[USERNAME];
    char password[PASSWORD];

    //input of username
    printf("Enter username: ");
    scanf("%s", username);

    //input of password and outputting **** in terminal 
    printf("Enter password: ");
    int i = 0;
    char c;
    while (i < PASSWORD - 1) {
        c = getch();
        if (c == '\r' || c == '\n') {
            break;
        }
        password[i++] = c;
        printf("*");
    }
    password[i] = '\0'; // Null-terminate the password string

    //compares input username and password if matching or not
    int found = 0;
    for (i = 0; i < MAX_USERS; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("\nLogin successful!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        //if username and password does not match, do not give access for further functions
        printf("\nLogin failed. Please check your username and password.\n");
        granted = 0;
    }
    else{
        //if username and password match, give access for further functions
        granted = 1;
    }
    return granted;
}
