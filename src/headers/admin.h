
// Define maximum lengths for user attributes
#define MAX_LENGHT_FOR_USER_NAME  32
#define MAX_LENGHT_FOR_PASSWORD  16
#define MAX_LENGHT_FOR_USER_TYPE  28
#define MAX_LENGHT_FOR_USER_ID  8

// Define a structure to represent a user
typedef struct{
   char user_name[MAX_LENGHT_FOR_USER_NAME];
   char user_password[MAX_LENGHT_FOR_PASSWORD];
   char user_type[MAX_LENGHT_FOR_USER_TYPE];
   char user_id[MAX_LENGHT_FOR_USER_ID];
}user;

// Function to move the cursor in the console
void move_cusor(int UP, int DOWN, int RIGHT, int LEFT){
   printf("\033[%dA", UP); // Move up X lines;
   printf("\033[%dB", DOWN); // Move down X lines;
   printf("\033[%dC", RIGHT); // Move right X column;
   printf("\033[%dD", LEFT); // Move left X column; 
}

// Function to count the number of lines in a file
int get_how_many_line_in_file(FILE *FILE){
   int number_of_line = 1;
   char charcter;
   do {
      charcter = fgetc(FILE);
      if (charcter == '\n') number_of_line++;
   }while(charcter != EOF);
   rewind(FILE);
   return number_of_line;
}

// Function to read user data from a file
void read_login_file(user **users, int number_of_line){
   FILE *login_data_file;
   login_data_file = fopen("data/sample_login_data.txt","r");
   // Check if the file is opened successfully
   if (login_data_file == NULL) {
      perror("Error opening file");
   }

   int number_of_data = 0,number_of_users = 0;
   *users = realloc(*users, sizeof(user) * number_of_line);
   do{
      // Read user data from the file using fscanf
      number_of_data = fscanf(login_data_file,
                  "%[^,],%[^,],%[^,],%[^\n]\n",
                   (*users)[number_of_users].user_name, 
                   (*users)[number_of_users].user_password, 
                   (*users)[number_of_users].user_type, 
                   (*users)[number_of_users].user_id); 
   // Check if the correct number of data is read (four fields)
   if (number_of_data == 4) number_of_users++;
   
   if (number_of_data != 4 && !feof(login_data_file))
   {
      printf("File format incorrect.\n");
   }
   }while(!feof(login_data_file));


   fclose(login_data_file);
}

// Function to sort users based on their user type
void sorting_users(user **users, int number_of_line){
   user temp;
   for (int i = 0; i < (number_of_line); i++){
   int min = i;
      for (int j = i + 1; j < number_of_line; j++)
         // Compare user types and swap if necessary
         if (strcmp((*users)[j].user_type, (*users)[min].user_type) < 0)
            min = j;
      if (min != i){
         // Swap users if necessary
         temp = ((*users)[i]);
         ((*users)[i]) = ((*users)[min]);
         ((*users)[min]) = temp;
         }
      }
}

// Function to update the login file after sorting users
void update_login_file(user **users, int number_of_line) {
   FILE *login_data_file;
   sorting_users(users, number_of_line);
   login_data_file = fopen("data/sample_login_data.txt", "w");
      // Write sorted user data to the file
      for (int i = 0; i < number_of_line + 1; i++) {
         fprintf(login_data_file,
               "%s,%s,%s,%s",
               (*users)[i].user_name,
               (*users)[i].user_password,
               (*users)[i].user_type,
               (*users)[i].user_id);
         if(number_of_line - i > 0){
            fprintf(login_data_file,"\n");
         }
      }

   fclose(login_data_file);
}

// Function for user login
void login_function(user **users, int number_of_users, char user_type[], char user_id[], char username[]){
   char UsreName[MAX_LENGHT_FOR_USER_NAME],password[MAX_LENGHT_FOR_PASSWORD];
   int login_status = 0;
   while(1){ 
         do{
            system("cls||clear");
            // Get user input for username and password
            printf("+-------------------------------------------------+"
                 "\n|         welcome to student tracker app          |");
            printf("\n+-------------------------------------------------+"
                   "\n| enter username:                                 |"
                   "\n+-------------------------------------------------+");
            move_cusor(2,0,0,34);
            scanf(" %[^\n]*s",UsreName);
         }while(strlen(UsreName) > MAX_LENGHT_FOR_USER_NAME);
         do{
            printf("\n| enter password:                                 |"
                   "\n+-------------------------------------------------+");
            move_cusor(2,0,0,34);
            scanf(" %[^\n]*s",password);
         }while(strlen(password) > MAX_LENGHT_FOR_PASSWORD);
         for (int i = 0; i < number_of_users;i++){
            // Check if the entered credentials match any user in the system
            if(strcmp((*users)[i].user_name ,UsreName) == 0 && strcmp((*users)[i].user_password,password) == 0 ){
               login_status = 1; 
               // Set user_type, user_id, and username if login is successful

               strcpy(user_type,(*users)[i].user_type);
               strcpy(user_id,(*users)[i].user_id);
               strcpy(username,(*users)[i].user_name);
               break;
            } 
         }
         if (login_status == 1){
            system("cls||clear");
            move_cusor(0,5,0,0);
            printf("\n+----------------------------------------------------+"
                   "\n|                   Login succesful                  |"
                   "\n+----------------------------------------------------+");
            Sleep(1750);
            break;}
         else{
            system("cls||clear");
            printf("\n+----------------------------------------------------+"
                   "\n|           user name or password is wrong           |"
                   "\n+----------------------------------------------------+");
            Sleep(2500);
            continue;
      }
   }
}

// Function to get a number as input within a specified range
int number_input(char question_asked[]){
   char string[4096], number[4096], final_number;
   int i = 0, number_count = 0, lenght;
   do{
      strcpy(number , " ");
      printf ("%s",question_asked);
      // Get a number input from the user, validating against non-numeric character
      scanf(" %[^\n]*s", number);
      lenght = strlen(string);
      while (i < lenght){
         if (string[i] == ' ') i++;
         else if(string[i] == '-'){
            number[number_count] = '-';
            number_count ++;
            i++; 
         }
         else if (isdigit(string[i]) == 0){ 
            break;
         }
         else if(isdigit(string[i]) == 1){
            number[number_count] = string[i];
            number_count ++;
            i++;
         }
      }
      move_cusor(2,0,3,0);
  }while(string[i] != '\0');
  final_number = atoi(number);
  return final_number;
}

// Function to enter a number within a specified range
int enter_number_in_range(int max_value, int min_value){
   int number, correct_value = 0;;
   
   char question_asked[40];
   sprintf(question_asked, "Please enter a number from (%i) to (%i): ", min_value, max_value); 
   do{
      int number = number_input(question_asked);
      // Get a number input within the specified range
      if (min_value <= number && number <= max_value){
         correct_value = 1;
         return number;
         }
   }while(correct_value == 0);
}

// Function to get a valid username input
void username_input(char user_name[32]){
   int comma_found;
   do{
      comma_found = 0;
      strcpy(user_name , " ");
      printf("+------------------------------------------------------+"
           "\n| please enter user name:                              |(user name should be less than 33 letters) "
           "\n+------------------------------------------------------+");
      move_cusor (2,0,0,31);
      // Get a valid username input from the user
      scanf(" %[^\n]*s", user_name);
      for(int i = 0; i < strlen(user_name); i++){
         // Validate length and check for the presence of a comma
         if(user_name[i] == ','){
            comma_found = 1;
            system("cls||clear");
            printf("+------------------------------------------------------+"
                 "\n|          username can't contain a comma (,)          |"
                 "\n+------------------------------------------------------+");
            Sleep(2500);
            system("cls||clear");
         }
      }
   }while(strlen(user_name) > 32 || strlen(user_name) <= 0 || comma_found == 1);
}

// Function to get a valid password input
void password_input(char password[]){
   int number_found, special_characters_found, char_found, comma_found ;
   do{
   number_found = 0; special_characters_found = 0; char_found = 0,comma_found = 0;
   strcpy(password , "");
   printf("+------------------------------------------------------+"
        "\n| please enter user password:                          |"
        "\n+------------------------------------------------------+");
   move_cusor (2,0,0,27);
   // Get a valid password input from the user
   scanf(" %[^\n]*s", password);
   for (int i = 0; i < strlen(password); i++){
      if(ispunct(password[i]) != 0)
         special_characters_found = 1;
      if(isdigit(password[i]) != 0)
         number_found = 1;
      if(isalpha(password[i] ) != 0)
         char_found = 1;
      if(password[i] == ',')
         comma_found = 1;
      }
   // Validate length, presence of letters, numbers, and special characters
   if (special_characters_found + number_found + char_found + comma_found != 3 ){
      system("cls||clear");
      if (special_characters_found == 0){
         printf("+------------------------------------------------------+"
              "\n|       password should contain special charcter       |"
              "\n+------------------------------------------------------+");
      }if(number_found == 0){
         printf("\n+------------------------------------------------------+"
               "\n|           password should contain numbers            |"
               "\n+------------------------------------------------------+");
      }if(char_found == 0){
         printf("\n+------------------------------------------------------+"
                "\n|           password should contain letters            |"
                "\n+------------------------------------------------------+");
      }
      if(comma_found == 1){
         printf("\n+------------------------------------------------------+"
                "\n|         password should not contain comma (,)        |"
                "\n+------------------------------------------------------+");
      }
      if(strlen(password) > 16 || strlen(password) < 8){
         printf("\n+------------------------------------------------------+"
                "\n|        password should be from 8 to 16 letters       |"
                "\n+------------------------------------------------------+");    
      }
      Sleep(3000);
      system("cls||clear");  
   } 
   }while(strlen(password) >= 16 || strlen(password) < 8 || number_found == 0 ||
    special_characters_found == 0 || char_found == 0 || comma_found == 1);
}

// Function to choose a user type
void user_type_choosing(char user_type[]){
   printf("+------------------------------------------------------+"
        "\n|                Please chose user type                |");
   char user_type_choosing[4][MAX_LENGHT_FOR_USER_TYPE] = {{"student"} ,{"administrator"} ,{"programme leader"},{"programme coordinator"}};
   for(int i = 0; i < 4; i++){
      printf("\n+---+--------------------------------------------------+"
             "\n|   |                                                  |");
      move_cusor(1,0,0,55);
      // Display user types and allow the user to choose one
      printf("%d | %s", i + 1, user_type_choosing[i]);
   }
   printf("\n+---+--------------------------------------------------+"
          "\n|                                                      |"
          "\n+------------------------------------------------------+");
   move_cusor(2,0,0,53);
   int User_choice = enter_number_in_range(4,1);
   // Set the user_type based on the user's choice
   switch (User_choice)
   {
   case 1:
      strcpy(user_type,"student");
      break;
   case 2 :
      strcpy(user_type,"administrator");
      break;
   case 3:
      strcpy(user_type,"programme leader");
      break;
   case 4:
      strcpy(user_type,"programme coordinator");
      break;   
   }
}

// Function to generate a user ID based on user attributes
void user_id_genrator(user ** users, int number_of_line, char id_number[],char user_name[],char user_type[]){
   int temp_num_holder, found = 0;
   char charter, temp_string[8];
   if (strlen(user_name) <= 9)
      temp_num_holder = strlen(user_name) * 100000; 
   else if (strlen(user_name) > 9) 
      temp_num_holder = strlen(user_name) * 10000;
   
   charter = user_name[0];
   // Generate a unique user ID based on user attributes
   if (charter >= 'a' && charter <= 'i')
      temp_num_holder += (charter - 96) * 1000;
   else if(charter >= 'j' && charter <= 'z')
      temp_num_holder += (charter - 96) * 100;
   else if(charter >= 'A' && charter <= 'I')
      temp_num_holder += (charter - 64) * 1000;
   else if(charter >= 'J' && charter <= 'Z')
      temp_num_holder += (charter - 64) * 100;

   if (strcmp(user_type,"student") == 0) 
      id_number[0] = 'S';
   else 
      id_number[0] = 'A';

   do{
   found = 0;
   // Check for existing IDs to ensure uniqueness
   sprintf(temp_string,"%d",temp_num_holder);
   for(int i = 0; i < 7;i++){
      id_number[i+1] = temp_string[i];
   }
      for (int i = 0; i < number_of_line;i++){
         if(strcmp((*users)[i].user_id ,id_number) == 0)
            found = 1;
      }
      temp_num_holder++;
   }while(found == 1);

}

// Function to add a new user
void add_user(user **users, int *number_of_line){
   
   char user_name[MAX_LENGHT_FOR_USER_NAME],password[MAX_LENGHT_FOR_PASSWORD]
   ,user_type[MAX_LENGHT_FOR_USER_TYPE],user_id[MAX_LENGHT_FOR_USER_ID];

   if ((*users = realloc(*users, sizeof(user) * (*number_of_line + 1))) != NULL){
      system("cls||clear");
      // Get user input for username, password, and user type
      username_input(user_name);
      password_input(password);
      user_type_choosing(user_type);
      // Generate a unique user ID based on the entered information
      user_id_genrator(users,*number_of_line,user_id,user_name, user_type);
      // Add the new user to the users array and update the login file
      strcpy((*users)[(*number_of_line)].user_name,user_name);
      strcpy((*users)[(*number_of_line)].user_password,password);
      strcpy((*users)[(*number_of_line)].user_type,user_type);
      strcpy((*users)[(*number_of_line)].user_id,user_id);
      update_login_file(users,*number_of_line);
   }
   (*number_of_line)++;
   //adding student to the system
   if (strcmp(user_type, "student") == 0){
      FILE * Student_file;
      Student_file = fopen("data/sample_students.txt","a");
      fprintf(Student_file, "\n%s,NA,NA,NA,NA",user_id);
      fclose(Student_file);
   }
}

// Function to display all users or specific types of users
void show_all_users(user **users,int number_of_line, int printing_type){
   int user_choice, number_of_space;
   do{
      system("cls||clear");
      char user_type_to_search[MAX_LENGHT_FOR_USER_TYPE], temp[20];
      if (printing_type == 0){
         // Display a menu to show different types of users
         printf( "+-------------------------------------------+"
               "\n|             show users menu               |"
               "\n|---+---------------------------------------|"
               "\n| 1 | Show all students                     |"
               "\n|---+---------------------------------------|"
               "\n| 2 | Show all administrators               |"
               "\n|---+---------------------------------------|"
               "\n| 3 | Show all programme leaders            |"
               "\n|---+---------------------------------------|"
               "\n| 4 | Show all programme coordinators       |"
               "\n|---+---------------------------------------|"
               "\n| 5 | Show all users                        |"
               "\n|---+---------------------------------------|"
               "\n| 6 | Exit                                  |"
               "\n|---+---------------------------------------|"
               "\n|                                           |"
               "\n+-------------------------------------------+");
         move_cusor(2,0,0,44);
         user_choice = enter_number_in_range(6, 1);
         
         }else user_choice = 5;
      switch (user_choice){
      case 1:
         strcpy(user_type_to_search, "student");
         break;
      case 2:
         strcpy(user_type_to_search, "administrator");
         break;
      case 3:
         strcpy(user_type_to_search, "programme leader");
         break;
      case 4:
         strcpy(user_type_to_search, "programme coordinator" );
         break;
      case 5:
         strcpy(user_type_to_search, "user" );
         break;
      }
      

      system("cls||clear");
      number_of_space = 86 - strlen(user_type_to_search);
      if (number_of_space % 2 == 1) number_of_space--; 
         if (user_choice < 6 ){
            if (printing_type == 0){
               printf("\n+-----------------------------------------------------------------------------------------------+"
                      "\n|%*sshow all %ss%*s|", number_of_space/2 , "", user_type_to_search, number_of_space/2 - 1 , "");
            }else if (printing_type == 1){
               printf("\n+-----------------------------------------------------------------------------------------------+"
                      "\n|                                      Choose user to delete                                    |");
            }else if (printing_type == 2){
               printf("\n+-----------------------------------------------------------------------------------------------+"
                      "\n|                                      Choose user to edit                                      |");
            }
            printf("\n|-----------------------------------------------------------------------------------------------|"
                   "\n|   | User Name                       | User Password   | User Type                   | User Id |"
                   "\n|---+---------------------------------+-----------------------------+-----------------+---------|");
         
            for (int i = 0; i < number_of_line; i++){
               // Print the users based on the chosen option
               if (strcmp(user_type_to_search,(*users)[i].user_type) == 0 || user_choice == 5){
                  printf("\n| %d |",i+1);
                  number_of_space = 32 - strlen((*users)[i].user_name);
                  printf(" %s%*s|",(*users)[i].user_name, number_of_space , "");
                  number_of_space = 16 - strlen((*users)[i].user_password);
                  printf(" %s%*s|",(*users)[i].user_password, number_of_space , "");
                  number_of_space = 28 - strlen((*users)[i].user_type);
                  printf(" %s%*s|",(*users)[i].user_type, number_of_space , "");
                  printf(" %s |",(*users)[i].user_id);
                  }
               if(number_of_line - i > 1) 
                  printf("\n|---+---------------------------------+-----------------------------+-----------------+---------|");
               }
            printf("\n|---+---------------------------------+-----------------------------+-----------------+---------|"
                   "\n|                                                                                               |"
                   "\n+-----------------------------------------------------------------------------------------------+"
                  );
            if (printing_type > 0)
               user_choice = 6;
            else{
               // Optionally allow the user to go back to the main menu
               printf("Type anything to go back to menu: ");
               scanf(" %[^\n]*s");
               }
            }
   }while(user_choice != 6);
}

// Function to delete a user
void delete_user(user **users, int *number_of_line){
   char user_id [MAX_LENGHT_FOR_USER_ID];
   // Display all users and prompt the user to choose a user to delete
   show_all_users(users, *number_of_line,1); 
   move_cusor(2,0,0,95);
   printf("Enter user number to delete ");
   int user_choice = enter_number_in_range( *number_of_line, 1);
   // Delete the chosen user and update the user list and login file
   for (int i = user_choice - 1; i < *number_of_line; i++){
      (*users)[i] = (*users)[i+1];
   }
   show_all_users(users, *number_of_line - 1, 1);
   update_login_file(users, *number_of_line - 2);
   *number_of_line--;
   move_cusor(2,0,0,62);
   printf("user deleted successfully"
          "\n|                                  Type anything to continue:                                   |"
          "\n+-----------------------------------------------------------------------------------------------+");
   move_cusor(2,0,0,36);
   char temp_c[20];
   scanf(" %[^\n]*s",temp_c);
}

// Function to edit user information
void edit_user(user **users, int number_of_line){
   char user_id [MAX_LENGHT_FOR_USER_ID];
   int edited, number_of_space = 0,user_choice_for_editing;
   // Display all users and prompt the user to choose a user to edit
   show_all_users(users, number_of_line,2); 
   move_cusor(2,0,0,95);
   printf("Enter user number to edit");
   int user_choice = enter_number_in_range( number_of_line , 1);
   
   do{
      edited = 0;
      system("cls||clear");
      number_of_space = 42 - (strlen((*users)[user_choice - 1].user_name));
      if (number_of_space % 2 == 1) number_of_space--;

      printf("+--------------------------------------------------------+"
      "\n|%*sEditing %s's info%*s|\n",number_of_space / 2   , "",(*users)[user_choice - 1].user_name,number_of_space / 2 , "");
      printf("+---+----------------------------------------------------+\n");
      // Display options for editing user information and apply changes
      number_of_space = 40 - strlen((*users)[user_choice - 1].user_name);
         printf("| 1 |");
         printf(" User Name: %s%*s|\n",(*users)[user_choice - 1].user_name, number_of_space , "");
         printf("+---+----------------------------------------------------+\n");
      number_of_space = 36 - strlen((*users)[user_choice - 1].user_password);
         printf("| 2 |");
         printf(" User Password: %s%*s|\n",(*users)[user_choice - 1].user_password, number_of_space , "");
         printf("+---+----------------------------------------------------+\n");
      number_of_space = 40 - strlen((*users)[user_choice - 1].user_type);
         printf("| 3 |");
         printf(" User Type: %s%*s|\n",(*users)[user_choice - 1].user_type, number_of_space , "");
         printf("+---+----------------------------------------------------+\n");
      printf("| 4 | Exit                                               |");
      printf("\n+---+----------------------------------------------------+");
      printf("\n|                                                        |");
      printf("\n+--------------------------------------------------------+");
      move_cusor (2,0,0,57);
      user_choice_for_editing = enter_number_in_range(4,1);
      if (user_choice_for_editing == 1){
         char username[32];
         username_input(username);
         strcpy((*users)[user_choice - 1].user_name, username);
         edited = 1;
      }else if (user_choice_for_editing == 2){
         char password[16];
         password_input(password);
         strcpy((*users)[user_choice - 1].user_password, password);
         edited = 1;
      }else if (user_choice_for_editing == 3){
         char user_type[28], id_number[8];
         user_type_choosing(user_type);
         strcpy((*users)[user_choice - 1].user_type, user_type);
         edited = 1;
         user_id_genrator(users, number_of_line, id_number, (*users)[user_choice].user_name, user_type);
         }
   }while(user_choice_for_editing < 4 );
   // Update the user list and login file
   update_login_file(users,number_of_line - 1);
}
