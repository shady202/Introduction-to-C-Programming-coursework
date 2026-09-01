#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>  // Include ctype.h for isdigit function

// Colors for syntax highlighting (Note: This won't work in all editors)
#define COLOR_RESET "\033[0m"
#define COLOR_KEYWORD "\033[1;32m"
#define COLOR_TYPE "\033[1;35m"
#define COLOR_STRING "\033[1;36m"
#define COLOR_COMMENT "\033[1;90m"

#define MAX_STUDENTS 100
#define MAX_ACTIVITIES 20
#define MAX_STUDENT_NAME 50
#define MAX_ACTIVITY_NAME 50

// Define activity types
enum ActivityType {
    ELECTIVE,
    TALK_WORKSHOP,
    CLUB_SOCIETY,
    COMPETITION
};

// Define a structure to represent an activity
struct Activity {
    char name[MAX_ACTIVITY_NAME];
    enum ActivityType type;
    int credits;
};

// Define a structure to represent a student
struct Student {
    char name[MAX_STUDENT_NAME];
    int studentID;
    struct Activity activities[MAX_ACTIVITIES];
    int numActivities;
};


// Function to read student data from a file
void readStudentDataFromFile(struct Student *students, int *numStudents, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    while (fscanf(file, "%d %s", &students[*numStudents].studentID, students[*numStudents].name) == 2) {
        int numActivities;
        fscanf(file, "%d", &numActivities);

        for (int i = 0; i < numActivities; i++) {
            fscanf(file, "%s %d %d",
                   students[*numStudents].activities[i].name,
                   (int*)&students[*numStudents].activities[i].type,
                   &students[*numStudents].activities[i].credits);
        }

        (*numStudents)++;
        if (*numStudents >= MAX_STUDENTS) {
            break;  // Stop reading if the maximum number of students is reached
        }
    }

    fclose(file);
}

// Function to track student activities
void trackStudentActivities(struct Student *students, int *numStudents) {
    char inputBuffer[20];  // Buffer to read input

    // Read student ID as a string
    printf(COLOR_STRING "Enter student ID: " COLOR_RESET);
    if (scanf("%19s", inputBuffer) != 1) {
        printf("Invalid input. Please enter a numeric student ID.\n");
        // Clear the input buffer
        while (getchar() != '\n');
        return;
    }

    // Validate that the entered string contains only digits
    for (int i = 0; i < strlen(inputBuffer); i++) {
        if (!isdigit(inputBuffer[i])) {
            printf("Invalid input. Please enter a numeric student ID.\n");
            return;
        }
    }

    // Convert the valid string to an integer
    int studentID = atoi(inputBuffer);
    printf("Entered student ID: %d\n", studentID);

    // Check if the student already exists
    struct Student *student = NULL;
    for (int i = 0; i < *numStudents; i++) {
        if (students[i].studentID == studentID) {
            student = &students[i];
            break;
        }
    }

    if (student != NULL) {
        // If the student already exists, print a message and return
        printf("Student already exists with ID %d. Returning...\n", studentID);
        return;
    }

    // If the student does not exist and the maximum number of students is not reached, add a new student
    if (*numStudents < MAX_STUDENTS) {
        student = &students[*numStudents];
        student->studentID = studentID;
        (*numStudents)++;
    } else {
        // If the maximum number of students is reached, print a message and return
        printf("Maximum number of students reached. Cannot add a new student.\n");
        return;
    }

    // Continue with the rest of the function to add activity for the new student
        printf(COLOR_STRING "Enter student name: " COLOR_RESET);
    scanf("%s", student->name);
    printf(COLOR_STRING "Enter activity name: " COLOR_RESET);
    scanf("%s", student->activities[student->numActivities].name);

    // Add a check for activity type
    int activityType;
    printf(COLOR_STRING "Enter activity type (0 - Elective, 1 - Talk/Workshop, 2 - Club/Society, 3 - Competition): " COLOR_RESET);
    scanf("%d", &activityType);

    if (activityType > 3) {
        printf("Choice is not available. Going back...\n");
        return;
    }

    student->activities[student->numActivities].type = (enum ActivityType)activityType;

    printf(COLOR_STRING "Enter activity credits: " COLOR_RESET);
    scanf("%d", &student->activities[student->numActivities].credits);

    student->numActivities++;
    printf("Activity added successfully.\n");
}

// Function to generate reports
void generateReports(const struct Student *students, int numStudents) {
    printf(COLOR_TYPE "===== Student Progress Report =====\n" COLOR_RESET);
    for (int i = 0; i < numStudents; i++) {
        printf(COLOR_TYPE "Student ID: %d\n" COLOR_RESET, students[i].studentID);
        printf(COLOR_TYPE "Name: %s\n" COLOR_RESET, students[i].name);
        printf(COLOR_TYPE "Activities:\n" COLOR_RESET);
        for (int j = 0; j < students[i].numActivities; j++) {
            printf(COLOR_COMMENT "  - %s (Type: %d, Credits: %d)\n" COLOR_RESET, students[i].activities[j].name,
                   students[i].activities[j].type, students[i].activities[j].credits);
        }
        printf(COLOR_TYPE "==================================\n" COLOR_RESET);
    }
}