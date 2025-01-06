#include <stdio.h>
#include <string.h>

#define MAX_ROOMS 50
#define MAX_NAME_LEN 50

typedef struct {
    int roomNumber;
    char customerName[MAX_NAME_LEN];
    char contactNumber[15];
    int isBooked;
    int daysStayed;
    float billAmount;
} Room;

Room rooms[MAX_ROOMS];

// Initialize rooms
void initializeRooms() {
    for (int i = 0; i < MAX_ROOMS; i++) {
        rooms[i].roomNumber = i + 1;
        rooms[i].isBooked = 0;
        strcpy(rooms[i].customerName, "");
        strcpy(rooms[i].contactNumber, "");
        rooms[i].daysStayed = 0;
        rooms[i].billAmount = 0.0;
    }
}

// Save room data to a file
void saveDataToFile() {
    FILE *file = fopen("hotel_data.txt", "w");
    if (file == NULL) {
        printf("Error saving data to file.\n");
        return;
    }
    for (int i = 0; i < MAX_ROOMS; i++) {
        fprintf(file, "%d %d %s %s %d %.2f\n", 
                rooms[i].roomNumber, 
                rooms[i].isBooked, 
                rooms[i].customerName, 
                rooms[i].contactNumber, 
                rooms[i].daysStayed, 
                rooms[i].billAmount);
    }
    fclose(file);
    printf("Data saved successfully.\n");
}

// Load room data from a file
void loadDataFromFile() {
    FILE *file = fopen("hotel_data.txt", "r");
    if (file == NULL) {
        printf("No saved data found. Starting fresh.\n");
        return;
    }
    for (int i = 0; i < MAX_ROOMS; i++) {
        fscanf(file, "%d %d %[^\n] %[^\n] %d %f", 
               &rooms[i].roomNumber, 
               &rooms[i].isBooked, 
               rooms[i].customerName, 
               rooms[i].contactNumber, 
               &rooms[i].daysStayed, 
               &rooms[i].billAmount);
    }
    fclose(file);
    printf("Data loaded successfully.\n");
}

// Display available rooms
void displayAvailableRooms() {
    printf("Available Rooms:\n");
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (!rooms[i].isBooked) {
            printf("Room %d\n", rooms[i].roomNumber);
        }
    }
}

// Book a room
void bookRoom() {
    int roomNumber;
    char customerName[MAX_NAME_LEN];
    char contactNumber[15];
    int daysStayed;

    printf("Enter room number to book: ");
    scanf("%d", &roomNumber);

    if (roomNumber < 1 || roomNumber > MAX_ROOMS) {
        printf("Invalid room number.\n");
        return;
    }

    if (rooms[roomNumber - 1].isBooked) {
        printf("Room %d is already booked.\n", roomNumber);
        return;
    }

    printf("Enter customer name: ");
    scanf(" %[^\n]s", customerName);
    printf("Enter contact number: ");
    scanf("%s", contactNumber);
    printf("Enter number of days to stay: ");
    scanf("%d", &daysStayed);

    rooms[roomNumber - 1].isBooked = 1;
    strcpy(rooms[roomNumber - 1].customerName, customerName);
    strcpy(rooms[roomNumber - 1].contactNumber, contactNumber);
    rooms[roomNumber - 1].daysStayed = daysStayed;
    rooms[roomNumber - 1].billAmount = daysStayed * 100.0;  // Example rate: $100 per day

    printf("Room %d successfully booked for %s.\n", roomNumber, customerName);
}

// Check out a room
void checkOutRoom() {
    int roomNumber;

    printf("Enter room number to check out: ");
    scanf("%d", &roomNumber);

    if (roomNumber < 1 || roomNumber > MAX_ROOMS) {
        printf("Invalid room number.\n");
        return;
    }

    if (!rooms[roomNumber - 1].isBooked) {
        printf("Room %d is not currently booked.\n", roomNumber);
        return;
    }

    printf("Customer: %s\n", rooms[roomNumber - 1].customerName);
    printf("Contact: %s\n", rooms[roomNumber - 1].contactNumber);
    printf("Days Stayed: %d\n", rooms[roomNumber - 1].daysStayed);
    printf("Total Bill: $%.2f\n", rooms[roomNumber - 1].billAmount);

    rooms[roomNumber - 1].isBooked = 0;
    strcpy(rooms[roomNumber - 1].customerName, "");
    strcpy(rooms[roomNumber - 1].contactNumber, "");
    rooms[roomNumber - 1].daysStayed = 0;
    rooms[roomNumber - 1].billAmount = 0.0;

    printf("Room %d successfully checked out.\n", roomNumber);
}

// Display booked rooms
void displayBookedRooms() {
    printf("Booked Rooms:\n");
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (rooms[i].isBooked) {
            printf("Room %d: %s, Contact: %s, Days: %d, Bill: $%.2f\n", 
                   rooms[i].roomNumber, 
                   rooms[i].customerName, 
                   rooms[i].contactNumber, 
                   rooms[i].daysStayed, 
                   rooms[i].billAmount);
        }
    }
}

int main() {
    int choice;

    initializeRooms();
    loadDataFromFile();

    while (1) {
        printf("\nHotel Management System\n");
        printf("1. Display Available Rooms\n");
        printf("2. Book Room\n");
        printf("3. Check Out Room\n");
        printf("4. Display Booked Rooms\n");
        printf("5. Save Data\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayAvailableRooms();
                break;
            case 2:
                bookRoom();
                break;
            case 3:
                checkOutRoom();
                break;
            case 4:
                displayBookedRooms();
                break;
            case 5:
                saveDataToFile();
                break;
            case 6:
                saveDataToFile();
                printf("Exiting the system.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
