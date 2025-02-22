/**********************************************PREPROCESSORS**********************************************************/
//Train Reservation System 
//including all libraries 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

/*******************************************GLOBAL VARIABLES**********************************************************/
//The composite data type declared here
typedef struct{
	char name[50];
	int train_num;
	int num_of_seats;
}pd;

/*******************************************FUNCTION PROTOTYPE**********************************************************/
//function prototypes to be used
void reservation(void);							//main reservation function
void viewdetails(void);							//view details of all the trains
void cancel(void);								//cancel ticket
void printticket(char name[],int,int,float);	//print ticket 
void specifictrain(int);						//print data related to specific train
float charge(int,int);							//charge automatically w.r.t number of seats and train
void show();                                    //reserved tickets

/******************************************FUNCTION DECLARATION**********************************************************/

/*********************************************MAIN()*************************************************/

int main_train()

{
	system("cls"); 													//Decoration
	printf("\t\t=================================================\n");
	printf("\t\t|                                               |\n");
	printf("\t\t|                                               |\n");
	printf("\t\t|                                               |\n");
	printf("\t\t|        -----------------------------          |\n");
	printf("\t\t|        BV TRAIN TICKET RERS. SYSTEM           |\n");
	printf("\t\t|        -----------------------------          |\n");
	printf("\t\t|    FOR STUDENTS AND STAFF OF UNIVERSITY       |\n");
	printf("\t\t|                                               |\n");
	printf("\t\t|                                               |\n");
	printf("\t\t|                                               |\n");
	printf("\t\t=================================================\n\n\n");
		
	    
	printf(" \n Press any key to continue:");
	
	getch();	
    system("cls");
	
	int menu_choice,choice_return;
	while(true){
		system("cls");
		printf("\n=================================\n");
		printf("    TRAIN RESERVATION SYSTEM");
		printf("\n=================================");

		printf("\n1>> Reserve A Ticket");
		printf("\n------------------------");

		printf("\n2>> View All Available Trains");
		printf("\n------------------------");

		printf("\n3>> Cancel Reservation");
		printf("\n------------------------");

		printf("\n4>> Show Reserved Tickets");
		printf("\n------------------------");

		printf("\n5>> Go to Main Page");
		printf("\n------------------------");

		printf("\n\n-->");
		scanf("%d",&menu_choice);
		switch(menu_choice)
		{
			case 1:
				reservation();
				continue;
			case 2:
				viewdetails();
				printf("\n\nPress any key to go to Main Menu..");
				getch();
				continue;
			case 3:
				cancel();
				printf("\n\nPress any key to go to Main Menu..");
				getch();
				continue;
			case 4:
				show();
				printf("\n\nPress any key to go to Main Menu..");
				getch();
				continue;
			case 5:
				return(0);
			default:
				printf("\nInvalid choice");
				printf("\n\nPress any key to retry..");
				getch();
				continue;
		}
	}
}

//ANSH_PREM
/*********************************************VIEWDETAILS()*************************************************/

void viewdetails(void)
{
	system("cls");
	printf("-----------------------------------------------------------------------------");	
	printf("\nTr.No\tName\t\t\tDestinations\t\t\t\t\tCharges\t\t\tTime\n");
	printf("-----------------------------------------------------------------------------");
	printf("\n12365\tRnc Janshatabdi Express    Ranchi(Jharkhand)                      \tRs.1000 \t\t05:40am");
	printf("\n13330\tGangadamodar Express       Dhanbad(Jharkhand)                     \tRs.5000 \t\t06:00am");
	printf("\n13239\tPnbe Kota Express          Kota Junction(Rajasthan)               \tRs.1200 \t\t06:30am");
	printf("\n12985\tJaipur Double Decker       Jaipur Junction(Rajasthan)             \tRs.1600 \t\t07:00am");
	printf("\n15014\tRanikhet Express           Jaipur Junction(Rajasthan)             \tRs.1700 \t\t07:45am");
	printf("\n12215\tGarib Rath Express         Jaipur Junction(Rajasthan)             \tRs.1400 \t\t08:30am");
	printf("\n15126\tJanshatabdi Express        Banaras(Uttar Pradesh)                 \tRs.3000 \t\t08:00am");
	printf("\n19409\tGorakhpur Express          Gorakhpur Junction(Uttar Pradesh)      \tRs.1800 \t\t09:00am");
	printf("\n12303\tPoorva Express             Patna Junction(Bihar)                  \tRs.2200 \t\t09:45am");
	printf("\n12333\tVibhuti Express            Prayagraj Junction(Uttar Pradesh)      \tRs.1500 \t\t10:30am");
	printf("\n12391\tShramjeevi Express         New Delhi                              \tRs.4000 \t\t12:00pm");
	printf("\n12024\tJanshatabdi Express        Howrah Junction(West Bengal)           \tRs.3500 \t\t01:30pm");
	printf("\n12332\tHimgiri Express            Asansol Junction(West Bengal)          \tRs.1200 \t\t02:15pm");
	printf("\n15658\tBrahmaputra Mail           Barauni Junction(Bihar)                \tRs.2000 \t\t03:00pm");
	printf("\n12355\tArchana Express            Jammu Tawi(Jammu & Kashmir)            \tRs.1000 \t\t04:15pm");
	printf("\n19314\tIndore Express             Indore Junction(Madhya Pradesh)        \tRs.2500 \t\t04:35pm");
	printf("\n19436\tAhmedabad Weekly Express   Pt. Deendayal Jn(Uttar Pradesh)        \tRs.2000 \t\t05:15pm");

}

/*********************************************RESERVATION()*************************************************/

void reservation(void)
{
	char confirm;
	int i=0;
	float charges;
	pd passdetails;
	FILE *fp;
	fp=fopen("train_data.txt","a");
	system("cls");
	
	printf("\nEnter Your Name:> ");
	fflush(stdin);
	gets(passdetails.name);
	printf("\nEnter Number of seats:> ");
	scanf("%d",&passdetails.num_of_seats);
	printf("\n\n>>Press Enter To View Available Trains<< ");
	getch();
	system("cls");
	viewdetails();
	printf("\n\nEnter train number:> ");
	start1:
	scanf("%d",&passdetails.train_num);
	if(passdetails.train_num>=12000 && passdetails.train_num<=20000)
	{
		charges=charge(passdetails.train_num,passdetails.num_of_seats);
		printticket(passdetails.name,passdetails.num_of_seats,passdetails.train_num,charges);		
	}
	else
	{
		printf("\nInvalid train Number! Enter again--> ");
		goto start1;
	}
	
	printf("\n\nConfirm Ticket (y/n):>");
	start:
	scanf(" %c",&confirm);
	
	if(confirm == 'y')
	{
		fprintf(fp,"%s\t\t%d\t\t%d\t\t%.2f\n",&passdetails.name,passdetails.num_of_seats,passdetails.train_num,charges);
		printf("==================");
		printf("\n Reservation Done\n");
		printf("==================\n");
		int ch =0;
		printf("Wamt to print the ticket? (1) or any other key for (n)\n");
		scanf("%d",&ch);
		if(ch){
			printticket(passdetails.name,passdetails.num_of_seats,passdetails.train_num,charges);
		}
		printf("\nPress any key to go back to Main menu");
	}
	else
	{
		if(confirm=='n'){
			printf("\nReservation Not Done!\nPress any key to go back to  Main menu!");
		}
		else
		{
			printf("\nInvalid choice entered! Enter again-----> ");
			goto start;
		}
	}
	fclose(fp);
	getch();
}

//ARTI
/*********************************************CHARGE()*************************************************/

float charge(int train_num,int num_of_seats)
{
		if (train_num==12365)
	{
		return(1000.0*num_of_seats);
	}
	if (train_num==13330)
	{
		return(5000.0*num_of_seats);
	}
	if (train_num==13239)
	{
		return(1200.0*num_of_seats);
	}
	if (train_num==15634)
	{
		return(1500.0*num_of_seats);
	}
	if (train_num==15126)
	{
		return(3000.0*num_of_seats);
	}
	if (train_num==12948)
	{
		return(2800.0*num_of_seats);
	}
	if (train_num==12361)
	{
		return(4500.0*num_of_seats);
	}
	if (train_num==12391)
	{
		return(4000.0*num_of_seats);
	}
	if (train_num==12024)
	{
		return(3500.0*num_of_seats);
	}
	if (train_num==12332)
	{
		return(1200.0*num_of_seats);
	}
	if (train_num==12142)
	{
		return(800.0*num_of_seats);
	}
	if (train_num==82355)
	{
		return(2000.0*num_of_seats);
	}
	if (train_num==12355)
	{
		return(1000.0*num_of_seats);
	}
	if (train_num==19314)
	{
		return(2500.0*num_of_seats);
	}
	if (train_num==19436)
	{
		return(2000.0*num_of_seats);
	}
}

/*********************************************SPECIFICTRAIN()*************************************************/

void specifictrain(int train_num)
{
	
	if (train_num==12365)
	{
		printf("\nTrain:\t\t\tRnc Janshatabdi Express");
		printf("\nDestination:\t\tRanchi(Jharkhand)");
		printf("\nDeparture:\t\t05:40am ");
	}
	if (train_num==13330)
	{
		printf("\nTrain:\t\t\tGangadamodar Express");
		printf("\nDestination:\t\tDhanbad(Jharkhand)");
		printf("\nDeparture:\t\t06:00am");
	}
	if (train_num==13239)
	{
		printf("\nTrain:\t\t\tPnbe kota Express");
		printf("\nDestination:\t\tKota Junction(Rajsthan)");
		printf("\nDeparture:\t\t06:30am");
	}
	if (train_num==15634)
	{
		printf("\nTrain:\t\t\tBikaner Express");
		printf("\nDestination:\t\tJaipur Junction(Rajasthan)");
		printf("\nDeparture:\t\t07:00am");
	}
	if (train_num==15126)
	{
		printf("\nTrain:\t\t\tJanshatabdi Express");
		printf("\nDestination:\t\tBanars(Uttar pradesh)");
		printf("\nDeparture:\t\t08:00am");
	}
	if (train_num==12948)
	{
		printf("\ntrain:\t\t\tAzimabad Express");
		printf("\nDestination:\t\tAhemdabad(Gujarat)");
		printf("\nDeparture:\t\t09.30am ");
	}
	if (train_num==12361)
	{
		printf("\ntrain:\t\t\tMumbai CSMT SF Express");
		printf("\nDestination:\t\tMumbai CSMT(Mumbai)");
		printf("\nDeparture:\t\t11:00am ");
	}
	if (train_num==12391)
	{
		printf("\ntrain:\t\t\tShramjeevi Express");
		printf("\n Destination:\t\tNew Delhi");
		printf("\nDeparture:\t\t12:00am ");
	}
	if (train_num==12024)
	{
		printf("\ntrain:\t\t\tJanshatabdi Express");
		printf("\nDestination:\t\tHowrah Junction(West Benagl)");
		printf("\nDeparture:\t\t01:30pm ");
	}
	if (train_num==12332)
	{
		printf("\ntrain:\t\t\tHimgiri Express");
		printf("\nDestination:\t\tAasansol Junction(West Bengal)");
		printf("\nDeparture:\t\t02.15pm");
	}
	if (train_num==12142)
	{
		printf("\ntrain:\t\t\tMumbai LTT SF Express");
		printf("\nDestination:\t\tLokmanya Tilak(Mumbai)");
		printf("\nDeparture:\t\t03.00pm");
	}
	if (train_num==82355)
	{
		printf("\ntrain:\t\t\tSuvidha Express");
		printf("\nDestination:\t\tC Shivaji Mah T(Mumbai)");
		printf("\nDeparture:\t\t03.35pm");
	}
	if (train_num==12355)
	{
		printf("\ntrain:\t\t\tArchana Express");
		printf("\nDestination:\t\tJammu Tawwi(Jammu kashmir)");
		printf("\nDeparture:\t\t04.15pm");
	}
	if (train_num==19314)
	{
		printf("\ntrain:\t\t\tIndore Express");
		printf("\nDestination:\t\tIndore Junction");
		printf("\nDeparture:\t\t04.35pm");
	}
	if (train_num==19436)
	{
		printf("\ntrain:\t\t\tAhemdabad Express");
		printf("\nDestination:\t\tPt.Deendayal Junction");
		printf("\nDeparture:\t\t05.15pm");
	}
}

typedef struct {
    char name[50];
    int num_of_seats;
    int train_num;
    float charges;
} PassengerDetails;

//ADITYA_PRAKASH
/*********************************************RESERVED_TICKETS_SHOW()*************************************************/

void show() {
    pd passdetails;
    pd passdetails1;
    FILE *fp;
    char name[50];
    int num_of_seats, train_num;
    float charges;
	typedef struct {
    char name[50];
    int num_of_seats;
    int train_num;
    float charges;
	} pd;

    // Open the file in read mode
    fp = fopen("train_data.txt", "r");
    if (fp == NULL) {
        printf("No reservations found!\n");
        return;
    }

    // Print header
    printf("=============================================\n");
    printf("    Name\t\tSeats\t\tTrain Number\tCharges\n");
    printf("=============================================\n");

    // Read and print each reservation entry
    while (fscanf(fp, "%s%d%d%f", name, &num_of_seats, &train_num, &charges) != EOF) {
        printf("%10s\t\t%2d\t\t%4d\t\t%.2f\n", name, num_of_seats, train_num, charges);
    }

    printf("\nFurther details of any of the tickets?\n");
    printf("Choice (y) or (for n press any key): ");
    char choice = 'n';
    scanf(" %c", &choice); // Corrected scanf format specifier

    if (choice == 'y') {
        printf("\nEnter the name on the ticket: ");
        scanf("%s", passdetails.name);

        // Rewind the file pointer to the beginning
        rewind(fp);
        bool flag=false;
        // Read and print the ticket if found
        while (fscanf(fp, "%s%d%d%f", passdetails1.name, &passdetails1.num_of_seats, &passdetails1.train_num, &charges) != EOF) {
            if (strcmp(passdetails1.name, passdetails.name) == 0) {
				flag = true;
                printticket(passdetails1.name, passdetails1.num_of_seats, passdetails1.train_num, charges);
                break;
            }
        }
		if(flag!=true){
			printf("Name enetered is incorrect!");
		}

    }

    // Close the file
    fclose(fp);
}

/*********************************************PRINTTICKET()*************************************************/

void printticket(char name[],int num_of_seats,int train_num,float charges)
{
	system("cls");
	printf("-------------------\n");
	printf("\tTICKET\n");
	printf("-------------------\n\n");
	printf("Name:\t\t\t%s",name);
	printf("\nNumber Of Seats:\t%d",num_of_seats);
	printf("\nTrain Number:\t\t%d",train_num);
	specifictrain(train_num);
	printf("\nCharges:\t\t%.2f",charges);
}

/*********************************************CANCELTICKET()*************************************************/

void cancel() {
    FILE *fp, *temp;
    char confirm;
    PassengerDetails passdetails;
    PassengerDetails passdetails1; // New variable for comparison
    float charges;
    int found = 0;

    // Display all available tickets
    printf("Available Tickets:\n");
    show();

    // Open the original file in read mode
    fp = fopen("train_data.txt", "r");
    if (fp == NULL) {
        printf("No reservations found!\n");
        return;
    }

    // Open temporary file in write mode
    temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Unable to process cancellation!\n");
        fclose(fp);
        return;
    }

    // Prompt for ticket details to cancel
    printf("\nEnter the name on the ticket to cancel: ");
    scanf("%s", passdetails.name);
    printf("Enter the number of seats on the ticket to cancel: ");
    scanf("%d", &passdetails.num_of_seats);
    printf("Enter the train number on the ticket to cancel: ");
    scanf("%d", &passdetails.train_num);

    // Copy reservations to temporary file, excluding the one to cancel
    while (fscanf(fp, "%s%d%d%f", passdetails1.name, &passdetails1.num_of_seats, &passdetails1.train_num, &charges) != EOF) {
        if (strcmp(passdetails1.name, passdetails.name) == 0 && passdetails1.num_of_seats == passdetails.num_of_seats && passdetails1.train_num == passdetails.train_num) {
            found = 1;
            printf("\nTicket Details:\n");
            printf("Name: %s\n", passdetails1.name);
            printf("Number of Seats: %d\n", passdetails1.num_of_seats);
            printf("Train Number: %d\n", passdetails1.train_num);
            printf("Charges: %.2f\n", charges);
            printf("\nConfirm cancellation (y) for yes, (n) for no: ");
            scanf(" %c", &confirm);
            if (confirm == 'y') {
                printf("Ticket cancelled successfully.\n");
                continue; // Move to the next reservation
            } else {
                printf("Cancellation aborted.\n");
            }
        }
        fprintf(temp, "%s\t\t%d\t\t%d\t\t%.2f\n", passdetails1.name, passdetails1.num_of_seats, passdetails1.train_num, charges);
    }
    
    // Close both files
    fclose(fp);
    fclose(temp);

    // Remove the original file
    remove("train_data.txt");

    // Rename the temporary file to original
    rename("temp.txt", "train_data.txt");

    // If ticket is not found and cancelled
    if (!found) {
        printf("Ticket not found.\n");
    }
}

/*********************************************END_OF_TRAIN_PART*************************************************/