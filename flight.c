#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 20
#define MAX_EMAIL_LENGTH 50 // Adjusted maximum email length
#define MAX_SOURCE_LENGTH 20
#define MAX_DESTINATION_LENGTH 20
#define MAX_MOBILE_LENGTH 11 // Considering the null terminator
#define MAX_SEATS_PER_ROUTE 50

struct Passenger {
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char source[MAX_SOURCE_LENGTH];
    char destination[MAX_DESTINATION_LENGTH];
    char mobile[MAX_MOBILE_LENGTH];
    int seat_num;
    char pnr[7];
    struct Passenger* next;
};

char* countries[] = {
    "Australia", "Brazil", "Canada", "China", "France",
    "Germany", "India", "Indonesia", "Italy", "Japan",
    "Mexico", "Netherlands", "Russia", "Saudi Arabia",
    "South Korea", "Spain", "Switzerland", "Turkey",
    "United Kingdom", "United States"
};

struct Passenger* head = NULL;
struct Passenger* tail = NULL;

void print_countries();
bool isPNRUsed(const char* pnr);

int countPassengers(char* source, char* destination);

void clearScreen() {
    printf("\033[H\033[J"); // ANSI escape code to clear the screen
}

void printHeader() {
    printf("\n\t\t**");
    printf("\n\t\t                Airline Reservation System                   ");
    printf("\n\t\t**\n\n");
}

void printMainMenu() {
    printf("\t\t1. Reserve a Seat\n");
    printf("\t\t2. Cancel Reservation\n");
    printf("\t\t3. Display Passenger List\n");
    printf("\t\t4. Go to Main Menu\n");
}

void savePassengerRecords() {
    FILE* file = fopen("passenger_records.txt", "w"); // Open file in write mode to overwrite existing content
    if (file == NULL) {
        printf("\n\t\tFailed to open file for writing!\n");
        return;
    }

    struct Passenger* passenger = head;
    while (passenger != NULL) {
        // Check if any fields are empty or invalid
        if (passenger->name[0] != '\0' && passenger->email[0] != '\0' && passenger->source[0] != '\0' && 
            passenger->destination[0] != '\0' && passenger->mobile[0] != '\0' && passenger->seat_num != 0) {
            fprintf(file, "%s,%s,%s,%s,%s,%d\n", passenger->pnr, passenger->name, passenger->email,
            passenger->source, passenger->destination, passenger->seat_num);
        }
        passenger = passenger->next;
    }

    fclose(file);
}

void loadPassengerRecords() {
    FILE* file = fopen("passenger_records.txt", "r");
    if (file == NULL) {
        printf("\n\t\tNo passenger records found!\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        struct Passenger* passenger = (struct Passenger*)malloc(sizeof(struct Passenger));
        if (passenger == NULL) {
            printf("\n\t\tMemory allocation error!\n");
            fclose(file);
            return;
        }
        sscanf(line, "%6s,%19s,%49s,%19s,%19s,%d\n", passenger->pnr, passenger->name, passenger->email,
        passenger->source, passenger->destination, &passenger->seat_num);
        passenger->next = NULL;

        if (head == NULL) {
            head = tail = passenger;
        } else {
            tail->next = passenger;
            tail = passenger;
        }
    }

    fclose(file);
}

void removeLineFromFile(const char* filename, const char* lineToRemove) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("\n\t\tError opening file for reading!\n");
        return;
    }

    FILE* tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        fclose(file);
        printf("\n\t\tError opening temporary file for writing!\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, lineToRemove) == NULL) {
            fputs(line, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(filename);
    rename("temp.txt", filename);
}

void printSeatAvailability() {
    printf("\n\t\tSeats Available for Each Route:\n");
    for (int i = 0; i < sizeof(countries) / sizeof(countries[0]); ++i) {
        for (int j = 0; j < sizeof(countries) / sizeof(countries[0]); ++j) {
            if (i != j) {
                printf("\t\tFrom %s to %s: %d/%d\n", countries[i], countries[j], MAX_SEATS_PER_ROUTE - countPassengers(countries[i], countries[j]), MAX_SEATS_PER_ROUTE);
            }
        }
    }
}

void printPassengerDetails(struct Passenger* passenger) {
    printf("\n\t\tPNR: %s\n", passenger->pnr);
    printf("\t\tName: %s\n", passenger->name);
    printf("\t\tSource: %s\n", passenger->source);
    printf("\t\tDestination: %s\n", passenger->destination);
    printf("\t\tMobile: %s\n", passenger->mobile);
    printf("\t\tSeat Number: A-%d\n", passenger->seat_num);
}

void reserveSeat() {
    char pnr[7];
    int choice;

    if (countPassengers(NULL, NULL) >= (sizeof(countries) / sizeof(countries[0]) - 1) * MAX_SEATS_PER_ROUTE) {
        printf("\n\t\tSorry, all seats are occupied!\n");
        return;
    }

    struct Passenger* passenger = (struct Passenger*)malloc(sizeof(struct Passenger));
    if (passenger == NULL) {
        printf("\n\t\tFailed to reserve seat. Memory allocation error!\n");
        return;
    }

    printf("\nEnter the source (by serial number): \n");
    print_countries();
    printf("\nEnter the serial number of the source country: ");
    scanf("%d", &choice);
    if (choice < 1 || choice > sizeof(countries) / sizeof(countries[0])) {
        printf("\n\t\tInvalid serial number for the source country!\n");
        free(passenger);
        return;
    }
    strcpy(passenger->source, countries[choice - 1]);

    printf("\nEnter the destination (by serial number): \n");
    print_countries();
    printf("\nEnter the serial number of the destination country: ");
    scanf("%d", &choice);
    if (choice < 1 || choice > sizeof(countries) / sizeof(countries[0])) {
        printf("\n\t\tInvalid serial number for the destination country!\n");
        free(passenger);
        return;
    }
    strcpy(passenger->destination, countries[choice - 1]);

    printf("\n\t\tEnter Name: ");
    scanf("%19s", passenger->name);

    // Enter Email (valid format required)
    bool isValid;
    do {
        isValid = true; // Reset isValid for each iteration
        printf("\n\t\tEnter Email: ");
        scanf("%49s", passenger->email);
        // Email validation
        char* atSymbol = strchr(passenger->email, '@');
        char* dotSymbol = strchr(passenger->email, '.');
        if (atSymbol == NULL || dotSymbol == NULL || atSymbol > dotSymbol) {
            printf("\n\t\tPlease enter a valid email address.\n");
            isValid = false;
        }
    } while (!isValid);

    // Enter Mobile Number (10 digits only)
    do {
        isValid = true; // Reset isValid for each iteration
        printf("\n\t\tEnter Mobile Number: ");
        scanf("%s", passenger->mobile);
        if (strlen(passenger->mobile) != 10) {
            printf("\n\t\tPlease enter a 10-digit mobile number.\n");
            isValid = false;
        } else {
            // Validate if the input is numeric
            for (int i = 0; i < strlen(passenger->mobile); i++) {
                if (!isdigit(passenger->mobile[i])) {
                    isValid = false;
                    break;
                }
            }
            if (!isValid) {
                printf("\n\t\tMobile number must contain only digits.\n");
            }
        }
    } while (strlen(passenger->mobile) != 10 || !isValid);

    // Generating unique PNR
    do {
        srand(time(NULL));
        sprintf(pnr, "%06d", rand() % 1000000);
    } while (isPNRUsed(pnr)); // Check if PNR is already used

    strcpy(passenger->pnr, pnr);

    passenger->seat_num = countPassengers(passenger->source, passenger->destination) + 1;
    passenger->next = NULL;

    printf("\n\t\tYour reservation is successful! Your PNR is: %s\n", passenger->pnr);

    if (head == NULL) {
        head = tail = passenger;
    } else {
        tail->next = passenger;
        tail = passenger;
    }

    savePassengerRecords();
}

bool isPNRUsed(const char* pnr) {
    struct Passenger* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->pnr, pnr) == 0) {
            return true; // PNR already used
        }
        temp = temp->next;
    }
    return false; // PNR is unique
}

void cancelReservation() {
    char pnr[7];
    printf("\n\t\tEnter PNR Number to cancel reservation: ");
    scanf("%6s", pnr);

    struct Passenger* prev = NULL;
    struct Passenger* curr = head;

    while (curr != NULL) {
        if (strcmp(curr->pnr, pnr) == 0) {
            if (prev == NULL) {
                head = curr->next;
                if (head == NULL) {
                    tail = NULL;
                }
            } else {
                prev->next = curr->next;
                if (prev->next == NULL) {
                    tail = prev;
                }
            }
            free(curr);
            printf("\n\t\tYour ticket with PNR %s has been cancelled.\n", pnr);
            removeLineFromFile("passenger_records.txt", pnr); // Remove canceled ticket from file
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    printf("\n\t\tNo reservation found with the provided PNR number!\n");
}

void displayPassengerList() {
    struct Passenger* passenger = head;

    if (passenger == NULL) {
        printf("\n\t\tPassenger list is empty!\n");
        return;
    }

    printf("\n\t\tPassenger List:\n");
    while (passenger != NULL) {
        printPassengerDetails(passenger);
        passenger = passenger->next;
    }
}

int countPassengers(char* source, char* destination) {
    int count = 0;
    struct Passenger* passenger = head;
    while (passenger != NULL) {
        if (source == NULL && destination == NULL) {
            count++;
        } else if (strcmp(passenger->source, source) == 0 && strcmp(passenger->destination, destination) == 0) {
            count++;
        }
        passenger = passenger->next;
    }
    return count;
}

void c_print(char* country, int serial) {
    printf("%d. %s\n", serial, country);
}

// Printing of countries
void print_countries() {
    int num_countries = sizeof(countries) / sizeof(countries[0]);

    for (int i = 0; i < num_countries; ++i) {
        c_print(countries[i], i + 1);
    }
}

int main_flight() {
    loadPassengerRecords(); // Load existing passenger records from file
    int choice;
    do {
        clearScreen();
        printHeader();
        printMainMenu();
        printf("\n\t\tEnter your choice (1-4): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                reserveSeat();
                break;
            case 2:
                clearScreen();
                cancelReservation();
                break;
            case 3:
                clearScreen();
                displayPassengerList();
                break;
            case 4:
                printf("\n\t\tExiting the program...\n");
                choice = 4;
                break;
            default:
                printf("\n\t\tInvalid choice! Please enter a number from 1 to 4.\n");
        }

        if (choice != 4) {
            printf("\n\t\tPress Enter key to continue...");
            while (getchar() != '\n');
            getchar(); // Wait for user input before continuing
        }
    } while (choice != 4);

    // Free allocated memory for passenger nodes
    struct Passenger* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
