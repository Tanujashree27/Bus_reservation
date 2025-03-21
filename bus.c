#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEATS 30
#define MAX_NAME_LENGTH 50

struct Booking {
    char name[MAX_NAME_LENGTH];
    int seatNo;
    char source[MAX_NAME_LENGTH];
    char destination[MAX_NAME_LENGTH];
};

struct Booking *bookings;
int bookedSeats = 0;

// Function to save bookings to a file
void saveBookings() {
    FILE *file = fopen("bookings.dat", "wb");
    if (file) {
        fwrite(&bookedSeats, sizeof(int), 1, file);
        fwrite(bookings, sizeof(struct Booking), bookedSeats, file);
        fclose(file);
    }
}

// Function to load bookings from a file
void loadBookings() {
    FILE *file = fopen("bookings.dat", "rb");
    if (file) {
        fread(&bookedSeats, sizeof(int), 1, file);
        fread(bookings, sizeof(struct Booking), bookedSeats, file);
        fclose(file);
    }
}

void bookSeat() {
    if (bookedSeats >= MAX_SEATS) {
        printf("No more seats available.\n");
        return;
    }

    struct Booking newBooking;
    printf("Enter name: ");
    getchar(); // Clear newline
    fgets(newBooking.name, MAX_NAME_LENGTH, stdin);
    strtok(newBooking.name, "\n");

    printf("Enter seat number (1-%d): ", MAX_SEATS);
    scanf("%d", &newBooking.seatNo);
    
    if (newBooking.seatNo < 1 || newBooking.seatNo > MAX_SEATS) {
        printf("Error: Invalid seat number.\n");
        return;
    }

    for (int i = 0; i < bookedSeats; i++) {
        if (bookings[i].seatNo == newBooking.seatNo) {
            printf("Error: Seat number %d is already booked.\n", newBooking.seatNo);
            return;
        }
    }

    printf("Enter source: ");
    getchar();
    fgets(newBooking.source, MAX_NAME_LENGTH, stdin);
    strtok(newBooking.source, "\n");

    printf("Enter destination: ");
    fgets(newBooking.destination, MAX_NAME_LENGTH, stdin);
    strtok(newBooking.destination, "\n");

    bookings[bookedSeats++] = newBooking;
    saveBookings();
    printf("Seat booked successfully!\n");
}

void viewReservation() {
    if (bookedSeats == 0) {
        printf("No reservations made yet.\n");
        return;
    }

    printf("\nAll Reservations:\n");
    printf("-------------------------------------------------------------\n");
    printf("%-10s %-20s %-20s %-20s\n", "Seat No.", "Name", "Source", "Destination");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < bookedSeats; i++) {
        printf("%-10d %-20s %-20s %-20s\n",
               bookings[i].seatNo, bookings[i].name, bookings[i].source, bookings[i].destination);
    }
    printf("-------------------------------------------------------------\n");
}

void editReservation() {
    int seatToEdit;
    printf("Enter seat number to edit: ");
    scanf("%d", &seatToEdit);

    for (int i = 0; i < bookedSeats; i++) {
        if (bookings[i].seatNo == seatToEdit) {
            printf("Enter new name: ");
            getchar();
            fgets(bookings[i].name, MAX_NAME_LENGTH, stdin);
            strtok(bookings[i].name, "\n");

            printf("Enter new source: ");
            fgets(bookings[i].source, MAX_NAME_LENGTH, stdin);
            strtok(bookings[i].source, "\n");

            printf("Enter new destination: ");
            fgets(bookings[i].destination, MAX_NAME_LENGTH, stdin);
            strtok(bookings[i].destination, "\n");

            saveBookings();
            printf("Reservation edited successfully!\n");
            return;
        }
    }
    printf("Reservation not found.\n");
}

void printTicket() {
    int seatToPrint;
    printf("Enter seat number to print ticket: ");
    scanf("%d", &seatToPrint);

    for (int i = 0; i < bookedSeats; i++) {
        if (bookings[i].seatNo == seatToPrint) {
            printf("\n------------------ TICKET ------------------\n");
            printf("Seat No.       : %d\n", bookings[i].seatNo);
            printf("Passenger Name : %s\n", bookings[i].name);
            printf("Source         : %s\n", bookings[i].source);
            printf("Destination    : %s\n", bookings[i].destination);
            printf("-------------------------------------------\n");
            return;
        }
    }
    printf("Reservation Not Found!!\n");
}

int main() {
    bookings = (struct Booking *)malloc(MAX_SEATS * sizeof(struct Booking));
    loadBookings();
    int choice;
    do {
        printf("\n===== BUS BOOKING SYSTEM =====\n");
        printf("1. Book a Seat\n");
        printf("2. View Reservations\n");
        printf("3. Edit a Reservation\n");
        printf("4. Print Ticket\n");
        printf("5. Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                bookSeat();
                break;
            case 2:
                viewReservation();
                break;
            case 3:
                editReservation();
                break;
            case 4:
                printTicket();
                break;
            case 5:
                printf("Exiting...\n");
                saveBookings();
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 5);

    free(bookings);
    return 0;
}