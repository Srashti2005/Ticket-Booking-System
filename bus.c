#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

// Define a structure to store bus information 
struct Bus {
    int busNumber;
    char source[50];
    char destination[50];
    int totalSeats;
    int availableSeats;
    float fare;
};

// Define a structure to store BusPassenger information 
struct BusPassenger {
    char name[50];
    int age;
    int seatNumber;
    int busNumber;
};

// Function to display the main menu 
void displayMainMenu()
{
    printf("\n=== Bus Reservation System ===\n");
    printf("\n1. Book a Ticket\n");
    printf("2. Cancel a Ticket\n");
    printf("3. Check Bus Status and Bus List\n");
    printf("4. Show Reserved Tickets\n");
    printf("5. Go to Main Page\n");
    printf("Enter your choice: ");
}

// Function to book a ticket 
void bookTicket(struct Bus buses[], int numBuses,
    struct BusPassenger BusPassengers[],
    int* numBusPassengers)
{
    printf("\nEnter Bus Number: ");
    int busNumber;
    scanf("%d", &busNumber);

    // Find the bus with the given busNumber 
    int busIndex = -1;
    for (int i = 0; i < numBuses; i++) {
        if (buses[i].busNumber == busNumber) {
            busIndex = i;
            break;
        }
    }

    if (busIndex == -1) {
        printf("Bus with Bus Number %d not found.\n",
            busNumber);
    }
    else if (buses[busIndex].availableSeats == 0) {
        printf("Sorry, the bus is fully booked.\n");
    }
    else {
        printf("Enter BusPassenger Name: ");
        scanf(" %[^\n]s", BusPassengers[*numBusPassengers].name);

        printf("Enter BusPassenger Age: ");
        scanf("%d", &BusPassengers[*numBusPassengers].age);

        // Assign a seat number to the BusPassenger 
        BusPassengers[*numBusPassengers].seatNumber
            = buses[busIndex].totalSeats
            - buses[busIndex].availableSeats + 1;

        // Update the BusPassenger's bus number 
        BusPassengers[*numBusPassengers].busNumber = busNumber;

        // Update available seats 
        buses[busIndex].availableSeats--;

        // Open file to append
        FILE* file = fopen("bus_reservation_data.txt", "a");
        if (file == NULL) {
            printf("Error opening file.\n");
            return;
        }

        // Write passenger data to file
        fprintf(file, "%s,%d,%d,%d\n", BusPassengers[*numBusPassengers].name, BusPassengers[*numBusPassengers].age,
            BusPassengers[*numBusPassengers].seatNumber, BusPassengers[*numBusPassengers].busNumber);

        fclose(file);

        printf("Ticket booked successfully!\n");
        (*numBusPassengers)++;
    }
}

// Function to cancel a ticket 
void cancelTicket(struct Bus buses[], int numBuses,
    struct BusPassenger BusPassengers[],
    int* numBusPassengers)
{
    printf("\nEnter BusPassenger Name: ");
    char name[50];
    scanf(" %[^\n]s", name);

    int found = 0;
    for (int i = 0; i < *numBusPassengers; i++) {
        if (strcmp(BusPassengers[i].name, name) == 0) {
            // Increase available seats 
            int busIndex = -1;
            for (int j = 0; j < numBuses; j++) {
                if (buses[j].busNumber
                    == BusPassengers[i].busNumber) {
                    busIndex = j;
                    break;
                }
            }
            buses[busIndex].availableSeats++;

            // Remove the BusPassenger entry 
            for (int j = i; j < (*numBusPassengers) - 1; j++) {
                BusPassengers[j] = BusPassengers[j + 1];
            }
            (*numBusPassengers)--;

            // Update file data after cancellation
            FILE* file = fopen("bus_reservation_data.txt", "w");
            if (file == NULL) {
                printf("Error opening file.\n");
                return;
            }

            for (int k = 0; k < *numBusPassengers; k++) {
                fprintf(file, "%s,%d,%d,%d\n", BusPassengers[k].name, BusPassengers[k].age,
                    BusPassengers[k].seatNumber, BusPassengers[k].busNumber);
            }

            fclose(file);

            found = 1;
            printf("Ticket canceled successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("BusPassenger with name %s not found.\n",
            name);
    }
}

// Function to check bus status 
void checkBusStatus(struct Bus buses[], int numBuses)
{
    printf("\n=== Bus Status ===\n");
    printf("\nNo.   Source       Destination   Fare    Total Seats   Available Seats\n");
    for (int i = 0; i < numBuses; i++) {
        printf("%d     %-11s %-13s %.2f      %-12d %-15d\n",
            buses[i].busNumber, buses[i].source, buses[i].destination,
            buses[i].fare, buses[i].totalSeats, buses[i].availableSeats);
    }
}

// Function to load reserved ticket data from file
void loadReservedTickets(struct BusPassenger BusPassengers[], int* numBusPassengers)
{
    FILE* file = fopen("bus_reservation_data.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fscanf(file, "%[^,],%d,%d,%d\n", BusPassengers[*numBusPassengers].name, &BusPassengers[*numBusPassengers].age,
        &BusPassengers[*numBusPassengers].seatNumber, &BusPassengers[*numBusPassengers].busNumber) != EOF) {
        (*numBusPassengers)++;
    }

    fclose(file);
}

// Function to show reserved tickets loaded previously
void showReservedTickets(struct BusPassenger BusPassengers[], int numBusPassengers)
{
    printf("\n=== Reserved Tickets ===\n");
    printf("\nBusPassenger Name     Age     Seat Number     Bus Number\n");
    for (int i = 0; i < numBusPassengers; i++) {
        printf("%-20s %-8d %-14d %d\n",
            BusPassengers[i].name, BusPassengers[i].age,
            BusPassengers[i].seatNumber, BusPassengers[i].busNumber);
    }
}

int main_bus()
{
    // Define and initialize buses
    struct Bus buses[] = {
        { 101, "Patna", "Varanasi", 50, 50, 599.0 },
        { 102, "Varanasi", "Patna", 50, 50, 599.0 },
        { 103, "Patna", "Gaya", 30, 30, 299.0 },
        { 104, "Gaya", "Patna", 30, 30, 299.0 },
        { 105, "Patna", "Motihari", 40, 40, 255.0 },
        { 106, "Motihari", "Patna", 40, 40, 255.0 },
        { 107, "Patna", "Bhagalpur", 60, 60, 449.0},
        { 108, "Bhagalpur", "Patna", 60, 60, 449.0},
        { 109, "Patna", "Deogarh", 50, 50, 255.0 },
        { 110, "Deogarh", "Patna", 40, 40, 255.0},
        { 111, "Patna", "Rajgir", 30, 30, 199.0},
        { 112, "Rajgir", "Patna", 30, 30, 199.0},
        { 113, "Patna", "Muzaffarpur", 40, 40, 149.0},
        { 114, "Muzaffarpur", "Patna", 40, 40, 149.0},
        { 115, "Patna", "Ranchi", 50, 50, 549.0},
        { 116, "Ranchi", "Patna", 50, 50, 549.0},
        { 117, "Patna", "Madhubani", 40, 40, 359.0},
        { 118, "Madhubani", "Patna", 40, 40, 359.0},
        { 119, "Patna", "Aurangabad", 30, 30, 279.0},
        { 120, "Aurangabad", "Patna", 30, 30, 279.0}
    };
    int numBuses = sizeof(buses) / sizeof(buses[0]);

    struct BusPassenger BusPassengers[500]; // Array to store passenger information
    int numBusPassengers = 0; // Number of passengers

    // Load reserved tickets data from file
    loadReservedTickets(BusPassengers, &numBusPassengers);

    int userChoice;
    while (1) {
        displayMainMenu();
        scanf("%d", &userChoice);

        switch (userChoice) {
        case 1:
            bookTicket(buses, numBuses, BusPassengers,
                &numBusPassengers);
            break;
        case 2:
            cancelTicket(buses, numBuses, BusPassengers,
                &numBusPassengers);
            break;
        case 3:
            checkBusStatus(buses, numBuses);
            break;
        case 4:
            showReservedTickets(BusPassengers, numBusPassengers);
            break;
        case 5:
            printf("Exiting the program.\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
