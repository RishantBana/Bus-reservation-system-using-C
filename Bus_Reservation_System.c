#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUSES 5
#define MAX_PASSENGERS 32
#define MAX_NAME_LENGTH 100
#define SEAT_PRICE 200

char busList[MAX_BUSES][130] = {
    "Delhi Express",
    "Agra Express",
    "Lucknow Express",
    "Jaipur Express",
    "Chandigarhh Express"
};

char passengerNames[MAX_PASSENGERS][MAX_NAME_LENGTH] = {'\0'};
int bookedSeats[MAX_PASSENGERS] = {0};
int availableSeats[MAX_BUSES] = {32,32,32,32,32};
int selectedBusIndex;

void showBusList();
void bookTickets();
void cancelBooking();
void displayStatus();

int main() {
    int userChoice;

    do {
        system("cls");
        printf("\n\n\n");
        printf("====================================== WELCOME TO BUS RESERVATION SYSTEM ======================================\n\n\n");
        printf("\t\t\t\t\t[1]=> View Bus List\n");
        printf("\t\t\t\t\t[2]=> Book Tickets\n");
        printf("\t\t\t\t\t[3]=> Cancel Booking\n");
        printf("\t\t\t\t\t[4]=> Display Bus Status\n");
        printf("\t\t\t\t\t[5]=> Exit\n\n");
        printf("===============================================================================================================\n\n");
        printf("\t\t\tEnter Your Choice:: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                showBusList();
                break;
            case 2:
                bookTickets();
                break;
            case 3:
                cancelBooking();
                break;
            case 4:
                displayStatus();
                break;
            case 5:
                printf("Thank you for using the system!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
        getch();
    } while (userChoice != 5);

    return 0;
}

void showBusList() {
    system("cls");
    printf("\n\n\n");
    printf("=========================================== BUS RESERVATION SYSTEM ============================================\n\n\n");
    for (int i = 0; i < MAX_BUSES; i++) {
        printf("\t\t\t\t\t[%d]  =>  %s\n", i + 1, busList[i]);
    }
}

void bookTickets() {
    system("cls");
    printf("=========================================== BUS RESERVATION SYSTEM ============================================\n\n\n");
    showBusList();
    
    printf("Select Bus Number: ");
    scanf("%d", &selectedBusIndex);
    selectedBusIndex--; 

    if (selectedBusIndex < 0 || selectedBusIndex >= MAX_BUSES) {
        printf("Invalid bus number.\n");
        return;
    }

    printf("Your Bus: %s\n", busList[selectedBusIndex]);
    printf("Available Seats: %d\n", availableSeats[selectedBusIndex]);

    int ticketsToBook;
    printf("Number of Tickets to Book: ");
    scanf("%d", &ticketsToBook);

    if (ticketsToBook > availableSeats[selectedBusIndex]) {
        printf("Not enough seats available!\n");
        return;
    }

    for (int i = 0; i < ticketsToBook; i++) {
        int seatNumber;
        printf("Enter Seat Number (1 to 32): ");
        scanf("%d", &seatNumber);
        seatNumber--;

        if (seatNumber < 0 || seatNumber >= MAX_PASSENGERS || bookedSeats[seatNumber] != 0) {
            printf("Invalid seat number or already booked.\n");
            i--; // Retry this ticket
            continue;
        }

        printf("Enter Passenger Name: ");
        scanf("%s", passengerNames[seatNumber]);
        bookedSeats[seatNumber] = seatNumber + 1;
    }

    availableSeats[selectedBusIndex] -= ticketsToBook;
    printf("Total booking amount: %d\n", SEAT_PRICE * ticketsToBook);
}

void cancelBooking() {
    int seatNumber;
    printf("Enter Bus Number to Cancel: ");
    scanf("%d", &selectedBusIndex);
    selectedBusIndex--;

    printf("Enter Seat Number to Cancel: ");
    scanf("%d", &seatNumber);
    seatNumber--;

    if (bookedSeats[seatNumber] == 0) {
        printf("Seat not booked.\n");
        return;
    }

    bookedSeats[seatNumber] = 0;
    availableSeats[selectedBusIndex]++;
    printf("Your booking has been canceled. Rs. %d has been refunded.\n", SEAT_PRICE);
}

void displayStatus() {
    system("cls");
    printf("=========================================== BUS RESERVATION SYSTEM ============================================\n\n\n");
    printf("Enter Bus Number: ");
    scanf("%d", &selectedBusIndex);
    selectedBusIndex--;

    printf("Bus: %s\n", busList[selectedBusIndex]);
    printf("Booking Status:\n");

    for (int i = 0; i < MAX_PASSENGERS; i++) {
        if (bookedSeats[i] != 0) {
            printf("Seat %d: %s\n", bookedSeats[i], passengerNames[i]);
        } else {
            printf("Seat %d: Empty\n", i + 1);
        }
    }
}
