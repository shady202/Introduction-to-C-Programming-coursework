
void addActivity(int numActivities) {
    char name[50],type[30];
    int points;
    FILE *file = fopen("data/sample_modules.txt", "a");
    if (file == NULL) {
        printf("Error opening activity file!\n");
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        if (numActivities >= MAX_ACTIVITIES) {
            printf("Maximum number of activities reached.\n");
            break;
        }

        Activity newActivity;
        char studentId[20], type[20];
        printf("enter activity name: ");
        scanf("%s",name);
        printf("enter activity type: ");
        points = enter_number_in_range (30,0);
        printf("enter activity points: ");
        scanf("%s",type);   
    }
    fprintf(file,"%s,%d,%s",name,points,type);
    fclose(file);
}


void displayActivities() {
    FILE *file = fopen("data/sample_modules.txt", "r");
    if (file == NULL) {
        printf("Error opening modules file!\n");
    }

    char line[100], moduleName[50], type[20];
    int points,counter = 1;

    printf("Modules:\n");
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%d,%s", moduleName, &points, type);
        printf("%d. Name: %s, Duration: %d, Type: %s\n",counter, moduleName, points, type);
        counter++;
    }

    fclose(file);
}

void editActivity (Activity activities[], int numActivities) {
    displayActivities();
    printf("\nEnter the index of the activity you want to edit : ");
    int index;
    char name[30], type[30], point[4];
    index = enter_number_in_range(numActivities, 1);
    //if logic
    if (index >= 1 && index <= numActivities) {
        printf("\nEnter the new name of the activity: ");
        scanf("%s", name);
        printf("Enter the new point: ");
        scanf("%s", point);
        printf("Enter the new type: ");
        scanf("%s", type);
        printf("Activity edited successfully.\n");
    } 
    
    strcpy(activities[index - 1].name, name);
    strcpy(activities[index - 1].points, point);
    strcpy(activities[index - 1].type, type);
    
    FILE *file = fopen("data/sample_modules.txt", "w");
    if (file == NULL) {
        printf("Error opening activity file!\n");
    }
    for (int i = 0; i < numActivities;i++){
        fprintf(file,"%s,%s,%s",activities[i].name,activities[i].points,activities[i].type);
        if(numActivities - i > 0)
            fprintf(file,"\n");
    }
    fclose(file);
}

void Delete_Activities(Activity activities[], int numActivities){
    displayActivities();
    printf("\nEnter the index of the activity you want to delete : ");
    int index;
    char name[30], type[30], point[4];
    index = enter_number_in_range(numActivities, 1);
    //if logic
    for (int i = index - 1; i < numActivities; i++){
        activities[i] = activities[i + 1];
    }
    FILE *file = fopen("data/sample_modules.txt", "w");
    if (file == NULL) {
        printf("Error opening activity file!\n");
    }
    for (int i = 0; i < numActivities - 1 ;i++){
        printf("im hreerer: %d\n",(numActivities - 1) - i);
        fprintf(file,"%s,%s,%s",activities[i].name,activities[i].points,activities[i].type);
        if((numActivities - 1) - i > 1)
            fprintf(file,"\n");
    }
    fclose(file);
}


int ProgrammeCoordinatorMenu() {
    system("cls||clear");
    char username[20], password[20];
    int choice;
    Activity activities[MAX_ACTIVITIES];
    int numActivities = 0;
    readActivities(activities, &numActivities);
    do {
        choice = 0;
        printf("\nProgramme Coordinator Menu:\n");
        printf("1. Add Activity\n");
        printf("2. Edit Activity\n");
        printf("3. Display Activities\n");
        printf("4. Delete Activities\n");
        printf("5. Back\n");
        printf("Enter your choice: ");
        choice = enter_number_in_range(5,1);
        switch (choice) {
            case 1:
                addActivity(numActivities);
                break;
            case 2:
                editActivity(activities, numActivities) ;
                break;
            case 3:
                displayActivities();
                break;
            case 4:
                Delete_Activities(activities, numActivities);
                break;
            case 5:
                break;
            default:
                printf("Invalid choice. Try again.\n");
                }
    }while (choice < 5);
    return 0;
}
