#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PASSPORT_LENGTH 7
#define MAX_NAME_LENGTH 20
#define MAX_EMAIL_LENGTH 20
#define MAX_SOURCE_LENGTH 20
#define MAX_DESTINATION_LENGTH 20
#define MAX_SEATS 15

struct Passenger {
    char passport[MAX_PASSPORT_LENGTH];
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char source[MAX_EMAIL_LENGTH];
    char destination[MAX_DESTINATION_LENGTH];
    int seat_num;
    int fare;
    int distance;
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

int countPassengers();

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
    printf("\t\t4. Save Passenger Records to File\n");
    printf("\t\t5. Exit\n");
}

void printSeatAvailability() {
    printf("\n\t\tSeats Available: %d/%d\n", MAX_SEATS - countPassengers(), MAX_SEATS);
}

void printPassengerDetails(struct Passenger* passenger) {
    printf("\n\t\tPassport Number: %s\n", passenger->passport);
    printf("\t\tName: %s\n", passenger->name);
    printf("\t\tSource: %s\n",passenger->source);
    printf("\t\tEmail: %s\n", passenger->email);
    printf("\t\tDestination: %s\n", passenger->destination);
    printf("\t\tSeat Number: A-%d\n", passenger->seat_num);
}

void reserveSeat() {
    if (countPassengers() >= MAX_SEATS) {
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
    int source_serial;
    scanf("%d", &source_serial);
    if (source_serial < 1 || source_serial > sizeof(countries) / sizeof(countries[0])) {
        printf("\n\t\tInvalid serial number for the source country!\n");
        free(passenger);
        return;
    }
    strcpy(passenger->source, countries[source_serial - 1]);

    printf("\nEnter the destination (by serial number): \n");
    print_countries();
    printf("\nEnter the serial number of the destination country: ");
    int destination_serial;
    scanf("%d", &destination_serial);
    if (destination_serial < 1 || destination_serial > sizeof(countries) / sizeof(countries[0])) {
        printf("\n\t\tInvalid serial number for the destination country!\n");
        free(passenger);
        return;
    }
    strcpy(passenger->destination, countries[destination_serial - 1]);

    printf("\n\t\tEnter Passport Number: ");
    scanf("%6s", passenger->passport);

    printf("\n\t\tEnter Name: ");
    scanf("%19s", passenger->name);

    printf("\n\t\tEnter Email: ");
    scanf("%19s", passenger->email);

    printf("\n\t\tEnter the distance you want to travel (in km): ");
    scanf("%d", &passenger->distance);

    // Define fare rates based on distance
    int fare = 0;
    if (passenger->distance >= 50 && passenger->distance < 100) {
        fare = 200;
    } else if (passenger->distance >= 100 && passenger->distance < 200) {
        fare = 450;
    } else if (passenger->distance >= 200 && passenger->distance <= 500) {
        fare = 700;
    } else {
        printf("\n\t\tInvalid distance!\n");
        free(passenger);
        return;
    }

    passenger->fare = fare;
    passenger->seat_num = countPassengers() + 1;
    passenger->next = NULL;

    printf("\n\t\tThe fare for your journey is: Rs. %d\n", passenger->fare);
    printf("\n\t\tEnter the payment amount: Rs. ");
    int payment;
    scanf("%d", &payment);

    if (payment == passenger->fare) {
        printf("\n\t\tPayment successful! Your reservation is confirmed.\n");
        if (head == NULL) {
            head = tail = passenger;
        } else {
            tail->next = passenger;
            tail = passenger;
        }
    } else {
        printf("\n\t\tPayment failed! Amount does not match the fare.\n");
        free(passenger);
    }
}

void cancelReservation() {
    char passport[MAX_PASSPORT_LENGTH];
    printf("\n\t\tEnter Passport Number to cancel reservation: ");
    scanf("%6s", passport);

    struct Passenger* prev = NULL;
    struct Passenger* curr = head;

    while (curr != NULL) {
        if (strcmp(curr->passport, passport) == 0) {
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
            printf("\n\t\tYour ticket has been cancelled.\n");
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    printf("\n\t\tNo reservation found with the provided passport number!\n");
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

void savePassengerRecords() {
    FILE* file = fopen("passenger_records.txt", "w");
    if (file == NULL) {
        printf("\n\t\tFailed to open file for writing!\n");
        return;
    }

    struct Passenger* passenger = head;
    while (passenger != NULL) {
        fprintf(file, "%s,%s,%s,%s,%s,%d\n", passenger->passport, passenger->name, passenger->email,
        passenger->source,
        passenger->destination, passenger->seat_num);
        passenger = passenger->next;
    }

    fclose(file);
    printf("\n\t\tPassenger records saved to file successfully!\n");
    printf("\n\t\tplease enter->choice 3 to check your saved details!\n");
    
}

int countPassengers() {
    int count = 0;
    struct Passenger* passenger = head;
    while (passenger != NULL) {
        count++;
        passenger = passenger->next;
    }
    return count;
}

void c_print(char* country, int serial) {
    printf("%d. %s\n", serial, country);
}

//printing of countries
void print_countries() {
    int num_countries = sizeof(countries) / sizeof(countries[0]);
    
    for (int i = 0; i < num_countries; ++i) {
        c_print(countries[i], i + 1);
    }
}

int main() {
    int choice;
    do {
        clearScreen();
        printHeader();
        printMainMenu();
        printSeatAvailability();
        printf("\n\t\tEnter your choice (1-5): ");
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
                clearScreen();
                savePassengerRecords();
                break;
            case 5:
                printf("\n\t\tExiting the program...\n");
                break;
            default:
                printf("\n\t\tInvalid choice! Please enter a number from 1 to 5.\n");
        }

        if (choice != 5) {
            printf("\n\t\tPress Enter key to continue...");
            while (getchar() != '\n');
            getchar(); // Wait for user input before continuing
        }
    } while (choice != 5);

    // Free allocated memory for passenger nodes
    struct Passenger* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
