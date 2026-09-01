typedef struct {
   char student_code[8]; 
   char core_moudle1[30];
   char core_moudle2[30];
   char core_moudle3[30];
   char core_moudle4[30];
} student;

#define MAX_ACTIVITIES 4096

typedef struct {
   char student_code[8]; 
   char name[50];
   char type[30];
   char points[4];
} StudentExtraActivity;

typedef struct {
    char name[50];
    char points[4];
    char type[30];
} Activity;


// Function to calculate and return the total credits
int calculateTotalCredits(StudentExtraActivity StudentsExtraActivity[], int ExtraActivityNum, char StudentCode[]){
   // Initialize the variables to store the number of points for each activity and the total points
   int NumberOfPoint = 0, totalpoint = 0;
   // Loop through all extra-curricular activities
   for (int i = 0; i < ExtraActivityNum ; i++){
      // Check if the current activity belongs to the student with the given StudentCode
      if (strcmp(StudentsExtraActivity[i].student_code, StudentCode) == 0){
         // Convert the points from string to integer and store them in NumberOfPoint
         NumberOfPoint  = atoi(StudentsExtraActivity[i].points);
         // Add the points from the current activity to the total points
         totalpoint += NumberOfPoint;
      }
   }
   // Return the total points earned by the student
   return totalpoint;
}



// Function to register for an activity
void registerForCoreActivity(student studens[], Activity activities[], int numActivities,int studnetsnum, char student_code[]){
    // Variables to track the number of core modules and the number of spaces for formatting
   int CoreModuleNum = 0, NumberOfSpace;
   char CoreModules[4096][30];
   system("cls||clear");
   printf("+----------------------------------------------+"
        "\n|           Register For Core Module           |"
        "\n+----------------------------------------------+"
        "\n| Available core modules:                      |"
        "\n+---+------------------------------------------+");
   // Loop through all activities to find core modules
   for (int i = 0; i < numActivities; i++){
      if (strcmp(activities[i].type, "core") == 0){
         // Copy the name of the core module to the CoreModules array
         strcpy(CoreModules[CoreModuleNum], activities[i].name);
         CoreModuleNum++;
         // Calculate spaces for formatting
         NumberOfSpace = 30 - strlen((CoreModules)[i]);
         printf("\n| %d | %s%*s           |", CoreModuleNum, activities[i].name, NumberOfSpace, "");
         if (numActivities - 1 > 0)
            printf("\n+---+------------------------------------------+");
         }
      }

   int registerChoice;
   printf("\n|    Enter the activity number to register     |"
          "\n|                                              |"
          "\n+----------------------------------------------+");
   move_cusor (2,0,0,45);
   int UserChoice = enter_number_in_range(CoreModuleNum,1 );
   // Loop through all students to find the one matching the provided student_code
   for (int i = 0; i < studnetsnum; i++){
      if (strcmp(studens[i].student_code, student_code) == 0) {
         if(strcmp(studens[i].core_moudle1,"NA") == 0)
            strcpy(studens[i].core_moudle1,CoreModules[UserChoice - 1]);
         else if(strcmp(studens[i].core_moudle2,"NA") == 0)
            strcpy(studens[i].core_moudle2,CoreModules[UserChoice - 1]);
         else if(strcmp(studens[i].core_moudle3,"NA") == 0)
            strcpy(studens[i].core_moudle3,CoreModules[UserChoice - 1]);
         else if(strcmp(studens[i].core_moudle4,"NA") == 0)
            strcpy(studens[i].core_moudle4,CoreModules[UserChoice - 1]);
         else 
            system("cls||clear");
            printf("+-------------------------------------------------------------+"
                 "\n|  you are registered to 4 core modules you can't to another  |"
                 "\n+-------------------------------------------------------------+");
            Sleep(4000);
      }
   }
   FILE* file;
   file = fopen("data/sample_students.txt","w");
   // Loop through all students and write their updated information to the file
   for (int i = 0; i < studnetsnum; i++){
      fprintf(file,"%s,%s,%s,%s,%s",studens[i].student_code,studens[i].core_moudle1,studens[i].core_moudle2,
            studens[i].core_moudle3,studens[i].core_moudle4);
      if(studnetsnum - i > 0){
         fprintf(file,"\n");
      }
   }
   fclose(file);
}

// Function to register a student for an extra activity
void registerForExtraActivity(StudentExtraActivity StudensExtraActivities[], Activity activities[], int numActivities,int ExtraActivitiesnum, char student_code[]){
   int ExtraActivitiesNum = 0, registered = 0 , UserChoice, SpaceNum ;
   Activity ExtraActivities[4096];
   // Continue looping until a valid activity is registered or the user chooses to exit
   do{
      system("cls||clear");
      // Reset registered flag and the counter for extra activities
      registered = 0, ExtraActivitiesNum= 0;
      printf("+------------------------------------------------+"
           "\n|         Register For Extra Activities          |"
           "\n|------------------------------------------------|"
           "\n|          Available Extra Activities:           |"
           "\n|---+------------------------------+-------------|"
           "\n|   | Name:                        | Points:     |");
      // Loop through all activities to list non-core (extra) activities
      for (int i = 0; i < numActivities; i++){
         if (strcmp(activities[i].type, "core") != 0){
            printf("\n|---+------------------------------+-------------|"
                   "\n|   |                              |             |");
            move_cusor(1,0,0,49);
            ExtraActivities[ExtraActivitiesNum] =  activities[i];
            ExtraActivitiesNum++;
            printf("%d",ExtraActivitiesNum);
            move_cusor(0,0,4,0);
            printf("%s",activities[i].name);
            SpaceNum = 32 -  strlen(activities[i].name);
            move_cusor(0,0,SpaceNum,0);
            printf("%s",activities[i].points);
         }
         }printf("%d. Exit", ExtraActivitiesNum + 1);
       // Calculate the total points the student already has
      int totalpoint = calculateTotalCredits(StudensExtraActivities, ExtraActivitiesnum, student_code);
      int registerChoice;
      printf("This is the amount of point you are free to: %d\nEnter the activity number to register", 60 - totalpoint );
      UserChoice = enter_number_in_range(ExtraActivitiesnum,1);
      // Check if the chosen activity is within the credit limit
      if (UserChoice != ExtraActivitiesNum +1){
         int points = atoi(ExtraActivities[UserChoice - 1].points);
         if(totalpoint + points <= 60 )
            registered = 1;
         else 
            printf("you cant sign to this extra activities cause you are exeding your credit limit");
      }
   }while(registered == 0 || UserChoice  == ExtraActivitiesNum +1);
   FILE* file;
   if (registered == 1){
      file = fopen("data/sample_extra_activities.txt","a");
      fprintf(file,"\n%s,%s,%s,%s",student_code,ExtraActivities[UserChoice - 1].name,
      ExtraActivities[UserChoice - 1].type, ExtraActivities[UserChoice - 1].points);
      fclose(file);
   }
}

void unregisterForExtraActivity(StudentExtraActivity StudensExtraActivities[],int ExtraActivitiesnum, char student_code[]){
   int ExtraActivitiesNum = 0, UserChoice;
   StudentExtraActivity temp_ExtraActivities[4096];
   do{
      system("cls||clear");
      ExtraActivitiesNum= 0;
      printf("+---------------------------------------------+"
           "\n|       Unregister From Extra Activities      |"
           "\n|---------------------------------------------|"
           "\n|         Registered Extra Activities:        |"
           "\n|---+-----------------------------------------|"
           "\n|   | Name:                                   |");
      for (int i = 0; i < ExtraActivitiesnum; i++){         
         if (strcmp(StudensExtraActivities[i].student_code, student_code) == 0){
            printf("\n|---+-----------------------------------------|"
                   "\n|   |                                         |");
            move_cusor(1,0,0,46);            
            temp_ExtraActivities[ExtraActivitiesNum] =  StudensExtraActivities[i];
            ExtraActivitiesNum++;
            printf("%d",ExtraActivitiesNum);
            move_cusor(0,0,4,0);
            printf("%s",StudensExtraActivities[i].name);
         }
      }printf("\n|---+-----------------------------------------|"
              "\n| %d | Exit                                    |"
              "\n|---+-----------------------------------------|", ExtraActivitiesNum + 1);
      printf("\n| what activity you want to unregister from   |"
             "\n|                                             |"
             "\n+---------------------------------------------+");
      move_cusor(2,0,0,45);
      UserChoice = enter_number_in_range(ExtraActivitiesNum + 1,1);
      int registerChoice;

      for (int i = 0 ; i < ExtraActivitiesnum ; i++){
         if (strcmp(temp_ExtraActivities[UserChoice - 1].name, StudensExtraActivities[i].name) == 0 &&
            strcmp(temp_ExtraActivities[UserChoice - 1].student_code, StudensExtraActivities[i].student_code) == 0 ){
            for (int j = i ; j < ExtraActivitiesnum - 1; j++){
               (StudensExtraActivities)[j] = (StudensExtraActivities)[j+1];
               }
            }
        }ExtraActivitiesnum--;
   }while(UserChoice  != ExtraActivitiesNum + 1);
   FILE* file;
   file = fopen("data/sample_extra_activities.txt","w");
   for (int i = 0 ; i < ExtraActivitiesnum + 1; i++){
      printf("%s,%s,%s,%s\n",StudensExtraActivities[i].student_code,StudensExtraActivities[i].name,
      StudensExtraActivities[i].type, StudensExtraActivities[i].points);
      fprintf(file,"%s,%s,%s,%s",StudensExtraActivities[i].student_code,StudensExtraActivities[i].name,
      StudensExtraActivities[i].type, StudensExtraActivities[i].points);
      if(ExtraActivitiesnum - i > 0){
         fprintf(file,"\n");
         }
      }
      fclose(file);
}

// Function to unregister a student from an extra activity
void unregisterFromcoremodule(student studens[],Activity activities[], int numActivities, int studnetsnum, char student_code[]) {
   int CoreModuleNum = 0;
   char CoreModules[4096][30];
   system("cls||clear");
   printf("\n+----------------------------------------------+"
          "\n|       Unregister For Extra Activities        |"
          "\n|----------------------------------------------|"
          "\n|           Registered core module:            |"
          "\n|---+------------------------------------------|"
          "\n|   | Name:                                    |");
   // Loop through all registered extra activities for the student
   for (int i = 0; i < numActivities; i++){
      if (strcmp(studens[i].student_code, student_code) == 0){
         CoreModuleNum = 0;
         strcpy(CoreModules[CoreModuleNum], studens[i].core_moudle1);
            CoreModuleNum++;
         strcpy(CoreModules[CoreModuleNum], studens[i].core_moudle2);
            CoreModuleNum++;
         strcpy(CoreModules[CoreModuleNum], studens[i].core_moudle3);
            CoreModuleNum++;
         strcpy(CoreModules[CoreModuleNum], studens[i].core_moudle4);
            CoreModuleNum++;
         for (int j =0;j < 4; j++){ 
            printf("\n|---+------------------------------------------|"
                   "\n|   |                                         |");         
            move_cusor(1,0,0,46);
            printf("%d", j  + 1);
            move_cusor(0,0,3,0);
            printf("%s",CoreModules[j]);
            }
        }
   }

   int registerChoice;
   printf("|  Enter the core module number to unregister  |"
        "\n|                                              |"
        "\n+----------------------------------------------+");
   
   int UserChoice = enter_number_in_range(CoreModuleNum,1 );
   // Remove the selected activity from the student's records
   for (int i = 0; i < studnetsnum; i++){
      if (strcmp(studens[i].student_code, student_code) == 0) {
         if (strcmp(CoreModules[UserChoice - 1], studens[i].core_moudle1) == 0){
            strcpy(studens[i].core_moudle1,"NA");
         }else if (strcmp(CoreModules[UserChoice-1], studens[i].core_moudle2) == 0){
            strcpy(studens[i].core_moudle2,"NA");
         }else if (strcmp(CoreModules[UserChoice-1], studens[i].core_moudle3) == 0){
            strcpy(studens[i].core_moudle3,"NA");
         }else if (strcmp(CoreModules[UserChoice-1], studens[i].core_moudle4) == 0)
            strcpy(studens[i].core_moudle4,"NA");
        }
    }
   FILE* file;
   file = fopen("data/sample_students.txt","w");
   for (int i = 0; i < studnetsnum; i++){
      fprintf(file,"%s,%s,%s,%s,%s",studens[i].student_code,studens[i].core_moudle1,studens[i].core_moudle2,
            studens[i].core_moudle3,studens[i].core_moudle4);
      if(studnetsnum - i > 0){
         fprintf(file,"\n");
      }
   }
   fclose(file);
}

// Function to view core modules for a specific student
void viewCoreModules(student students[], int numStudents, char StudentCode[]){
   printf("+------------------------------------+"
        "\n|           Core Modules:            |");
   // Loop through all students
   for (int i = 0; i < numStudents; i++) {
      if (strcmp(students[i].student_code, StudentCode) == 0) {
         printf("\n+---+--------------------------------+");
         printf("\n|   |                                |");
         move_cusor(1,0,0,40);
         printf("| 1 | %s", students[i].core_moudle1);
         printf("\n+---+--------------------------------+");
         printf("\n|   |                                |");
         move_cusor(1,0,0,40);
         printf("| 2 | %s", students[i].core_moudle2);
         printf("\n+---+--------------------------------+");
         printf("\n|   |                                |");
         move_cusor(1,0,0,40);
         printf("| 3 | %s", students[i].core_moudle3);
         printf("\n+---+--------------------------------+");
         printf("\n|   |                                |");
         move_cusor(1,0,0,40);
         printf("| 4 | %s", students[i].core_moudle4);
      }
   }printf("\n+---+--------------------------------+");
   Sleep(4000);
}

// Function to view extra activities for a specific student
void viewExtraActivities(StudentExtraActivity StudentsExtraActivity[], int ExtraActivitieNum, char StudentCode[]) {
   int counter = 0;
   printf("+------------------------------------+"
        "\n|          Extra activities:         |");
   // Loop through all extra activities
   for (int i = 0; i < ExtraActivitieNum; i++) {
      if (strcmp(StudentsExtraActivity[i].student_code, StudentCode) == 0) {
         printf("\n+---+--------------------------------+");
         printf("\n|   |                                |");
         move_cusor(1,0,0,40);
         counter++;
         printf("| %d | %s",counter, StudentsExtraActivity[i].name);
      }
   }
   printf("\n+---+--------------------------------+");
   Sleep(4000);
}

// Function to read student extra activities from a file
void readstudentExta_Activities(StudentExtraActivity StudentsExtraActivity[], int *ExtraActivityNum){
   int NumberOfData = 0, NumberOfActivities = 0;
   FILE* file = fopen("data/sample_extra_activities.txt", "r"); 
   // Check if the file was opened successfully
   if (file == NULL) {
      perror("Error opening file");
   }
   // Read data from the file until the end of file is reached
   do{
      NumberOfData = fscanf(file,"%[^,],%[^,],%[^,],%[^\n]\n",
      (StudentsExtraActivity)[NumberOfActivities].student_code, 
      (StudentsExtraActivity)[NumberOfActivities].name, 
      (StudentsExtraActivity)[NumberOfActivities].type, 
      (StudentsExtraActivity)[NumberOfActivities].points); 
   if (NumberOfData == 4) NumberOfActivities++;

   if (NumberOfData != 4 && !feof(file))
   {
      printf("File format incorrect.\n");
   }
   }while(!feof(file));
   // Update the total number of extra activities
   *ExtraActivityNum = NumberOfActivities;
   fclose(file);
}

// Function to read student activities from a file
void readstudentActivities(student students[], int *studentnum){
   int NumberOfData = 0, NumberOfActivities = 0;// Variables to keep track of data read and number of activities
   FILE* file = fopen("data/sample_students.txt", "r"); 

   if (file == NULL) {
      perror("Error opening file");
   }
   // Read data from the file until the end of file is reached
   do{
      // Read a line from the file and store the data in the students array
      NumberOfData = fscanf(file,"%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
      (students)[NumberOfActivities].student_code, 
      (students)[NumberOfActivities].core_moudle1, 
      (students)[NumberOfActivities].core_moudle2, 
      (students)[NumberOfActivities].core_moudle3, 
      (students)[NumberOfActivities].core_moudle4 );
   // Increment the number of activities if all five fields were successfully read 
   if (NumberOfData == 5) NumberOfActivities++;
   // Check for file format errors (not reaching end of file but data is incorrect)
   if (NumberOfData != 5 && !feof(file))
   {
      printf("File format incorrect.\n");
   }
   }while(!feof(file)); // Continue until the end of the file is reached
   *studentnum = NumberOfActivities; 
   fclose(file);
}

// Function to read activities from a file
void readActivities(Activity activities[], int* numActivities) {
   int NumberOfData = 0, NumberOfActivities = 0;// Variables to keep track of data read and number of activities
   FILE* file = fopen("data/sample_modules.txt", "r");  // Fix the typo in the file name

   if (file == NULL) {
      perror("Error opening file");
   } 
   // Read data from the file until the end of file is reached
   do{
      // Read a line from the file and store the data in the activities array
      NumberOfData = fscanf(file,"%[^,],%[^,],%[^\n]\n",
      (activities)[NumberOfActivities].name, 
      (activities)[NumberOfActivities].points, 
      (activities)[NumberOfActivities].type); 
   // Check for file format errors (not reaching end of file but data is incorrect)
   if (NumberOfData == 3) NumberOfActivities++;
   // Check for file format errors (not reaching end of file but data is incorrect)
   if (NumberOfData != 3 && !feof(file))
   {
      printf("File format incorrect.\n");
   }
   }while(!feof(file));
   
   fclose(file);
   *numActivities = NumberOfActivities;
}


// Function to view the progress report of a specific student
void View_progress_report(StudentExtraActivity StudentsExtraActivity[], student students[], int numStudents, int ExtraActivityNum,char StudentCode[]){
   int NumberOfPoint = 0, NumberOfCore = 0, MinToFulFill = 0, NumberOfAllCredits = 0;
   char c[20];// Buffer to hold user input
   system("cls||clear");
   NumberOfPoint = calculateTotalCredits (StudentsExtraActivity, ExtraActivityNum, StudentCode) ;
   // Loop through students to find the matching student code and calculate core module credits
   for (int i = 0; i < ExtraActivityNum; i++){
      if (strcmp(students[i].student_code,StudentCode) == 0){
         // Increment NumberOfCore for each non-NA (i.e., registered) core module
         if(strcmp(students[i].core_moudle1,"NA") != 0)
            NumberOfCore++;
         if(strcmp(students[i].core_moudle2,"NA") != 0)
            NumberOfCore++;
         if(strcmp(students[i].core_moudle3,"NA") != 0)
            NumberOfCore++;
         if(strcmp(students[i].core_moudle4,"NA") != 0)
            NumberOfCore++;
      }
   }
   printf("\n+----------------------------------------------------------------+");
   printf("\n|                         progress report                        |");
   printf("\n+----------------------------------------------------------------+");
   // Calculate total credits (from core modules and extra activities)
   NumberOfAllCredits =  NumberOfPoint + (NumberOfCore * 30);
   // Calculate the minimum points to fulfill (if any)
   if (NumberOfAllCredits >= 160) MinToFulFill = 0;
   else MinToFulFill = 160 - NumberOfPoint;
   printf("\n+------------------------------------------------------+---------+");
   printf("\n|  number of credits you getiing from core modules:    |     /12 |");
   printf("\n+------------------------------------------------------+---------+");
   printf("\n|  number of points left to fulfil the minimum point:  |         |");
   printf("\n+------------------------------------------------------+---------+");
   printf("\n|  number of credit you registered to:                 |     /20 |");
   printf("\n+------------------------------------------------------+---------+");
   printf("\n|  number of points from extra activites:         credit:        |");
   printf("\n+----------------------------------------------------------------+");
   move_cusor(8,0,0,8);
   printf("%d", NumberOfCore * 3 );
   move_cusor(0,3,0,0);
   printf("%d", MinToFulFill);
   move_cusor(0,3,0,4);
   printf("%d", NumberOfAllCredits / 10);
   move_cusor(0,3,0,20);
   printf("%d", NumberOfPoint);
   move_cusor(0,0,16,0);
   printf("%d", NumberOfPoint / 10);
   move_cusor(0,3,0,63);
   // Prompt the user to press any key when they are done viewing the report
   printf("|  Press anything when you are done:                             |");
   printf("\n+----------------------------------------------------------------+");
   move_cusor(2,0,0,30);
   scanf("%s",&c);
}