 //**********************************************PREPROCESSORS**********************************************************//

#include <stdio.h>            // Include standard input/output library
#include <string.h>           // Include string manipulation library
#include <stdlib.h>           // Include standard library functions
#include <math.h>             // Include mathematical functions library
#include "flight.c"           // Include flight booking functions
#include "bus.c"              // Include bus booking functions
#include "train.c"            // Include train booking functions

//Define maximum number of users, maximum username length, maximum password length, and user data file name

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define USER_DATA_FILE "login_data.txt"

// Function Prototypes

void screenheader();           // Function to display header
void intro();                  // Function to introduce the platform
void displayMenu();            // Function to display menu
void saveUserData();           // Function to save user data
void loadUserData();           // Function to load user data
void captchaVerification();    // Function to verify captcha

// Define User structure to store username and password

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

// Initialize users array and number of users

User users[MAX_USERS];
int num_users = 0;

// Main functon or Driver Code 

int main() {

    loadUserData();                                // Load user data from file when the program starts

    int choice;

    do {
        system("cls");                             // Clear the screen                      
        screenheader(); 
        printf("\n1. Signup\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                signup();
                break;
            case 2:
                if (login()) {
                    displayMenu();                  // After successful login, display the menu
                } else {
                    continue;                       // If login fails, continue the loop to display options again
                }
                break;
            case 3:
                printf("Exiting...\n");
                saveUserData();                     // Save user data before exiting
                return 0;
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (1);                                    // Loop indefinitely until the user chooses to exit

    return 0;
}

// Function to display Header 

void screenheader() {
    printf("\n               ******************************************************");
    printf("\n               *                                                    *");
    printf("\n               *                                                    *");
    printf("\n               *             WELCOME TO OUR PRESTIGIOUS             *");
    printf("\n               *                     PLATFORM                       *");
    printf("\n               *            BANASTHALI VIDYAPEETH JAIPUR            *");
    printf("\n               *               TICKET BOOKING SYSTEM                *");
    printf("\n               *                                                    *");
    printf("\n               ****************************************************** \n");
}

// Function to display the services on the platform 

void intro() {
    printf("\n\n\n\t ALL THE SERVICE AVAILABLE ");
    printf("\n");
    printf("\n\t\t\t1. TRAIN BOOKING \n");
    printf("\t\t\t2. FLIGHT BOOKING \n");
    printf("\t\t\t3. BUS BOOKING\n");
    printf("\nPress any character to continue:");
    getch();
}

// Function to display the current available services 

void displayMenu() {
    int choice;
    do {
        system("cls");                                   // Clear the screen before displaying menu
        printf("\n\n\n\t CURRENT SERVICE AVAILABLE ");
        printf("\n");
        printf("\n\t\t\t1. TRAIN BOOKING \n");
        printf("\t\t\t2. FLIGHT BOOKING \n");
        printf("\t\t\t3. BUS BOOKING\n");
        printf("\t\t\t4. LOGOUT\n");
        printf("\n\t\t\tPlease choose the service you want to access: ");
        scanf("%i", &choice);
        
        switch (choice) {
            case 1:
                main_train();
                break;
            case 2:
                main_flight();
                break;
            case 3:
                main_bus();
                break;
            case 4:
                printf("Logout Successful!\n");
                exit(0);                                // Return from the function to go back to main menu
            default:
                printf("Invalid choice. Please try again.\n");
        } 
    } while (1);                                        // Loop until a valid choice is made
}

// Function to sign up on the platform 

void signup() {
    if (num_users >= MAX_USERS) {
        printf("Error: Maximum number of users reached.\n");
        return;
    }

    printf("Enter username: ");
    scanf("%s", users[num_users].username);

    printf("Enter password: ");
    scanf("%s", users[num_users].password);

    captchaVerification();

    num_users++;
    printf("Signup successful!\n");
    saveUserData();                                       // Save user data to file after signup
}

//  Function to login on the platform 

int login() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    //scanf("%s", password);
    int i=0, c;
    while(i<10)
	{
	    password[i]=getch();
	    c=password[i];
	    if(c==13) break;
	    else printf("*");
	    i++;
	}
	password[i]='\0';

    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            captchaVerification();
            printf("\nLogin successful!\n");
            system("cls");
            screenheader();
            intro();
            displayMenu();
            return 1;                                      // Return 1 to indicate successful login
        }
    }

    printf("Invalid username or password.\n");
    printf("Retry!");
    getch();
    return 0;                                              // Login failed
}

// Function to save user data 

void saveUserData() {
    FILE *fp = fopen(USER_DATA_FILE, "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < num_users; i++) {
        fprintf(fp, "%s %s\n", users[i].username, users[i].password);
    }

    fclose(fp);
}

// Function to load user data 

void loadUserData() {
    FILE *fp = fopen(USER_DATA_FILE, "r");
    if (fp == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    while (fscanf(fp, "%s %s", users[num_users].username, users[num_users].password) != EOF) {
        num_users++;
    }

    fclose(fp);
}

// Function to generate captcha for human verification 

void captchaVerification() {

    // Generate a random captcha code
    srand(time(NULL));
    int captchaCode = rand() % 9000 + 1000;
    int userCode;
    printf("\n\nCaptcha Code : %d",captchaCode);
    printf("\nEnter the captcha code displayed on the screen: ");
    scanf("%d", &userCode);

    while (userCode!= captchaCode) {
        printf("\nInvalid captcha code.\n Please try again: ");
        scanf("%d", &userCode);
    }
}
