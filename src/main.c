#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#define Sleep(ms) sleep(((ms) + 999) / 1000)
#endif
#include "headers/admin.h"
#include "headers/student.h"
#include "headers/programme_coordinator.h"
#include "headers/programme_leader.h"


/**
 * Displays the programme leader menu and routes selected actions.
 */
void Programme_Leader_menu();

/**
 * Displays the programme coordinator menu.
 */
void Programme_Coordinator_menu();

/**
 * Displays the administrator menu for user management operations.
 *
 * @param users Pointer to the in-memory user array.
 * @param number_of_line Number of users loaded from the login file.
 * @param user_type Authenticated user type.
 * @param user_name Authenticated user name.
 */
void Administrator_menu (user **users, int number_of_line, char user_type[], char user_name[]);

/**
 * Displays the student menu and handles student activity actions.
 *
 * @param studentCode The authenticated student ID.
 */
void student_menu(char studentCode[]);

/**
 * Application entry point that authenticates users and dispatches role menus.
 *
 * @return 0 when the application exits.
 */
int main(void){
   while(1){
   char user_type[28],user_id[8], user_name[32];
   FILE *login_data_file;
   login_data_file = fopen("data/sample_login_data.txt","r");

   int number_of_line = get_how_many_line_in_file(login_data_file);
   user *users = calloc(number_of_line, sizeof(user));
   student *students;
   read_login_file(&users, number_of_line);
   login_function(&users, number_of_line, user_type, user_id, user_name);
   if (strcmp (user_type ,"student") == 0 ) student_menu(user_id);
   else if (strcmp(user_type , "administrator") == 0) Administrator_menu(&users,number_of_line, user_type, user_name);
   else if (strcmp(user_type , "programme leader") == 0)  Programme_Leader_menu();
   else if (strcmp(user_type , "programme coordinator") == 0 ) Programme_Coordinator_menu();

   fclose(login_data_file);
   free(users);}
   return 0;
}

//_______________________________________________________________________________________________________________________________
//ABDULRAHMAN ABDALLA TP068014
//_______________________________________________________________________________________________________________________________

void student_menu(char studentCode[]) {
   FILE *studnet_data_file ;
   FILE* extra_activity_file;
   studnet_data_file = fopen("data/sample_students.txt","r");
   extra_activity_file = fopen("data/sample_extra_activities.txt","r");

   int numStudents = get_how_many_line_in_file(studnet_data_file);
   int ExtraActivitieNum = get_how_many_line_in_file(extra_activity_file);
   // Initialize activities and numActivities
   Activity activities[MAX_ACTIVITIES];
   student students[numStudents];
   StudentExtraActivity StudentsExtraActivity[ExtraActivitieNum];

   int numActivities = 0;
    
   // Read existing activities from the file

   int choice = 0;
   while (choice != 8) {
      system("cls||clear");
      printf(  "+---------------------------------------+");
      printf("\n|             Student Menu:             |"
             "\n|---+-----------------------------------|"
             "\n| 1 | View Core Modules                 |"
             "\n|---+-----------------------------------|"
             "\n| 2 | View Extra Activities             |"
             "\n|---+-----------------------------------|"
             "\n| 3 | Register for an core modules      |"
             "\n|---+-----------------------------------|"
             "\n| 4 | Register for an extra activity    |"
             "\n|---+-----------------------------------|"
             "\n| 5 | Unregister from an core module    |"
             "\n|---+-----------------------------------|"
             "\n| 6 | Unregister from an Activity       |"
             "\n|---+-----------------------------------|"
             "\n| 7 | View progress report              |"
             "\n|---+-----------------------------------|"
             "\n| 8 | logout                            |"
             "\n+---+-----------------------------------+"
             "\n|                                       |"
             "\n+---------------------------------------+");
      move_cusor(2,0,0,40);
      printf("Enter your choice: ");
      scanf("%d", &choice);

      readActivities(activities, &numActivities);
      readstudentActivities(students, &numStudents);
      readstudentExta_Activities(StudentsExtraActivity, &ExtraActivitieNum);

      switch (choice) {
         case 1:
            viewCoreModules(students, numStudents, studentCode);
            break;
         case 2:
            viewExtraActivities(StudentsExtraActivity, ExtraActivitieNum, studentCode);
            break;
         case 3:
            registerForCoreActivity(students,activities, numActivities, numStudents, studentCode);
            break;
         case 4:
            registerForExtraActivity(StudentsExtraActivity, activities, numActivities, ExtraActivitieNum, studentCode);
            break;
         case 5:
            unregisterFromcoremodule(students, activities, numActivities, numStudents, studentCode);
            break;
         case 6:
            unregisterForExtraActivity(StudentsExtraActivity, ExtraActivitieNum, studentCode);
            break;
         case 7:
            View_progress_report(StudentsExtraActivity,students,numStudents,ExtraActivitieNum,studentCode);
            break;
         case 8:
            break;
         default:
            system("cls||clear");
            printf("+--------------------------------------+"
                 "\n|  Invalid choice. Please try again.   |"
                 "\n+--------------------------------------+");
            Sleep(2500);
            break;
         }
   }
}
//_______________________________________________________________________________________________________________________________
//AMJAD ALRIFAAI TP072985
//_______________________________________________________________________________________________________________________________



void Administrator_menu (user **users, int number_of_line, char user_type[], char user_name[]){
      int user_choice;
      do{
      system("cls||clear");
      read_login_file(users, number_of_line);
      char admin_menu[5][20] = {{"Add user"},{"Delete user"},{"Edit user"},{"Show all users"},{"Logout"}};
      printf("+------------------------------------------+"
         "\n|      Welcome to Administrator menu       |");
      for(int i = 0; i < 5; i++){
         printf("\n+---+--------------------------------------+"
               "\n|   |                                      |");
         move_cusor(1,0,0,43);
         printf("%d",i+1);
         move_cusor(0,0,4,0);
         printf("%s",admin_menu[i]);
      }
      printf("\n+---+--------------------------------------+"
            "\n|                                          |"
            "\n+------------------------------------------+");
      move_cusor(2,0,0,43);
      user_choice = enter_number_in_range(5,1);
      switch (user_choice)
      {
      case 1:
         add_user(users, &number_of_line);
         break;
      case 2:
         delete_user(users,&number_of_line);
         break;
      case 3:
         edit_user(users, number_of_line);
      case 4:
         show_all_users(users,number_of_line,0);
      case 5:
         break;
      }
   }while(user_choice < 5);
}

//_______________________________________________________________________________________________________________________________
//MOHAMED ABDURRAZAG JABER SEKLANI(TP073802)
//_______________________________________________________________________________________________________________________________
void Programme_Coordinator_menu(){
   ProgrammeCoordinatorMenu();
}

//_______________________________________________________________________________________________________________________________
//SHADY EHAB TP073549
//_______________________________________________________________________________________________________________________________
void Programme_Leader_menu()
{
    struct Student students[MAX_STUDENTS];
    int numStudents = 0;

    int choice;
    printf("\n");
    printf(COLOR_TYPE "=== Program Leader System ===\n" COLOR_RESET);

    // Read student data from the file
    readStudentDataFromFile(students, &numStudents, "data/sample_students.txt");

    // Read extra activity data from the file
    readStudentDataFromFile(students, &numStudents, "data/sample_extra_activities.txt");

    while (1) {
                printf(COLOR_TYPE "\n===== Menu =====\n" COLOR_RESET);
                printf(COLOR_KEYWORD "1. Track student activities\n");
                printf("2. Generate reports\n");
                printf("3. Logout\n" COLOR_RESET);
                printf(COLOR_KEYWORD "Enter your choice: " COLOR_RESET);
                scanf("%d", &choice);

                switch (choice) {
                case 1:
                    trackStudentActivities(students, &numStudents);
                    break;
                case 2:
                    generateReports(students, numStudents);
                    break;
                case 3:
                    printf("Logging out.\n");
                    return;
                default:
                    printf("Invalid choice. Please try again.\n");
                    break;
                }
        }
            
        }