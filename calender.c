// Calendar Management System in C (dayName direct from daysOfWeek)

#include <stdio.h>
#include <string.h>

struct Note {
    int day;
    int month;
    int year;
    char note[100];
};

struct Note notes[100]; // Store up to 100 notes
int totalNotes = 0;

// Function declarations
void addNote();
void findDay();
void printMonth();

// Zeller's Congruence function
int getDayOfWeek(int d, int m, int y) {
    if (m < 3) {
        m += 12;
        y -= 1;
    }
    int k = y % 100;
    int j = y / 100;
    int f = d + 13 * (m + 1) / 5 + k + k / 4 + j / 4 + 5 * j;
    return f % 7;  // 0 = Saturday, 1 = Sunday, ..., 6 = Friday
}

// Add a note
void addNote() {
    struct Note n;
    printf("Enter date (day month year): ");
    scanf("%d %d %d", &n.day, &n.month, &n.year);

    printf("Enter your note: ");
    getchar(); // clear newline
    scanf("%[^\n]", n.note);

    notes[totalNotes] = n;
    totalNotes++;

    printf("Note added successfully!\n");
}

// Find the day using array lookup
void findDay() {
    int d, m, y;
    printf("Enter date (day month year): ");
    scanf("%d %d %d", &d, &m, &y);

    int dayIndex = getDayOfWeek(d, m, y);

    char *daysOfWeek[] = {
        "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"
    };

    if (dayIndex >= 0 && dayIndex <= 6)
        printf("The day is: %s\n", daysOfWeek[dayIndex]);
    else
        printf("Invalid day\n");
}

// Print all days in a month with notes (dayName directly from array)
void printMonth() {
    int month, year;
    printf("Enter month and year: ");
    scanf("%d %d", &month, &year);

    int daysInMonth;

    if (month == 2) {
         if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
            daysInMonth = 29;
        else
            daysInMonth = 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11)
        daysInMonth = 30;
    else
        daysInMonth = 31;

    // Day names array
    char *daysOfWeek[] = {
        "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"
    };

    printf("\nDate\t\tDay\t\tNote\n");
    printf("---------------------------------------------\n");

    for (int i = 1; i <= daysInMonth; i++) {
        int dayIndex = getDayOfWeek(i, month, year);

        // Directly get dayName from array
        char *dayName;
        if (dayIndex >= 0 && dayIndex <= 6)
            dayName = daysOfWeek[dayIndex];
        else
            dayName = "Invalid";

        // Check if there is a note
        int found = 0;
        for (int j = 0; j < totalNotes; j++) {
            if (notes[j].day == i && notes[j].month == month && notes[j].year == year) {
                printf("%02d/%02d/%04d\t%s\t%s\n", i, month, year, dayName, notes[j].note);
                found = 1;
                break;
            }
        }
        if (!found)
            printf("%02d/%02d/%04d\t%s\t-\n", i, month, year, dayName);
    }
}

// Main menu
int main() {
    int choice;
    while (1) {
        printf("\n=== Calendar Management System ===\n");
        printf("1. Add Note\n");
        printf("2. Find Out the Day\n");
        printf("3. Print Every Day of the Month\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addNote(); break;
            case 2: findDay(); break;
            case 3: printMonth(); break;
            case 4:
                printf("Exiting calendar. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
