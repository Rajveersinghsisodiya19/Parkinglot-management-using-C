#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

void welcome();
int content();
void choice1();
void choice2();
void choice3();
void choice4();
void checkPreviousParkingLot();

int slotbus = 300, slotcar = 300, slotbike = 300;
int busprice = 200, carprice = 100, bikeprice = 50;
int prebus = 0, precar = 0, prebike = 0;

int randomnumberbus = 0;
int randomnumbercar = 0;
int randomnumberbike = 0;

time_t busStartTime;
time_t carStartTime;
time_t bikeStartTime;

int main()
{

    welcome();
    return 0;
}

void checkPreviousParkingLot()
{
    system("clear"); // use system("cls") if on windows;
    int f;
    char customerName[50];
    int vehicleNo;
    char name[50], vehicleType[20], timeStr[50], action[20];
    int parkingNo, fee;
    int found = 0;
    int fileVehicleNo;

    printf("\nEnter your Name: ");
    scanf("%s", customerName);
    for (int i = 0; customerName[i] != '\0'; i++)
    {
        if (!isalpha(customerName[i]))
        {
            printf("Invalid name! Please enter only letters (A-Z, a-z).\n");
            printf("Enter to Retry ");
            scanf("%d", &f);
            checkPreviousParkingLot();
        }
    }

    printf("\nEnter your Vehicle Number: ");
    scanf("%d", &vehicleNo);

    if (vehicleNo < 0)
    {
        printf("Invalid Car No!\n");
        printf("Enter 1 to continue. Enter 0 to Exit.");
        scanf("%d", &f);
        if (f == 0)
        {
            content();
        }
        if (f == 1)
        {
            choice1();
        }
    }

    int temp = vehicleNo;
    int n = 0;
    int count = 0;
    while (temp != 0)
    {
        n = temp % 10;
        temp = temp / 10;
        count++;
    }
    if (count < 4 || count > 4)
    {
        printf("Invalid Car No!\n");
        printf("Enter 1 to continue. Enter 0 to Exit.");
        scanf("%d", &f);
        if (f == 0)
        {
            content();
        }
        if (f == 1)
        {
            checkPreviousParkingLot();
        }
    }

    FILE *file = fopen("customers.csv", "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    while (fscanf(file, "%[^,],%d,%[^,],%d,%[^,],%d,%s\n", name, &fileVehicleNo, vehicleType, &parkingNo, timeStr, &fee, action) != EOF)
    {
        if (strcmp(name, customerName) == 0 && fileVehicleNo == vehicleNo && strcmp(action, "Parked") == 0)
        {
            found = 1;
            printf("\nVehicle Details:\n");
            printf("Name: %s\n", name);
            printf("Vehicle No: %d\n", vehicleNo);
            printf("Vehicle Type: %s\n", vehicleType);
            printf("Parking Lot No: %d\n", parkingNo);
            printf("Last Parked At: %s\n", timeStr);
            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("\nNo previous parking record found");
    }

    int key;
    printf("\n\nPress any key to Exit....");
    scanf("%d", &key);
    system("clear"); // use system("cls") if on windows;
    content();
}

void welcome()
{
    system("clear"); // use system("cls") if on windows;
    int key;
    char password[20];
    int password1;
    char User[20];
    char ch;
    int i = 0;

    printf("\n\n                                                      -----------> Welcome To Car Management System <-----------                                      ");
    printf("\n\n\n                                                                 Car Parking Reservation System Login \n\n");
    printf("\n                                                                      Enter your UserName : ");
    scanf("%s", User);

    printf("\n                                                                      Enter your Password : ");

    // To get Passord in star(Password:*******) comment out this part. getch does not work on mac
    // while (1) {
    //     ch = getch();

    //     if (ch == 13) {
    //         password[i] = '\0';
    //         break;
    //     } else if (ch == 8) {
    //         if (i > 0) {
    //             i--;
    //             printf("\b \b");
    //     } else {
    //         password[i] = ch;
    //         i++;
    //         printf("*");
    //     }
    // }

    scanf("%d", &password1);

    if (password1 == 1)
    {
        printf("\n\n                                                                Login Successful! Welcome To Our System \n\n\n");
        printf("Press any key to continue....");
        scanf("%d", &key);
        system("clear"); // use system("cls") if on windows;
        content();
    }
    else
    {
        printf("\n\n                                                                Login Unsuccessful... Please Try Again!! \n\n\n");
    }
}

void displayParkingGraphics()
{
    system("clear"); // use system("cls") if on windows;
    printf("\n\n\t\t\t\t\t-----------> Welcome to the Parking Lot <-----------\n\n");

    printf("   Bus Parking Slots:\n");
    for (int i = 1; i <= slotbus; i++)
    {
        if (i <= prebus)
            printf("[X] ");
        else
            printf("[ ] ");
        if (i % 30 == 0)
            printf("\n");
    }

    printf("\n\n   Car Parking Slots:\n");
    for (int i = 1; i <= slotcar; i++)
    {
        if (i <= precar)
            printf("[X] ");
        else
            printf("[ ] ");

        if (i % 30 == 0)
            printf("\n");
    }

    printf("\n\n   Bike Parking Slots:\n");
    for (int i = 1; i <= slotbike; i++)
    {
        if (i <= prebike)
            printf("[X] ");
        else
            printf("[ ] ");

        if (i % 30 == 0)
            printf("\n");
    }

    printf("\n\nLegend: [X] Occupied, [ ] Empty\n");
    int key;
    printf("\n\nPress any key to Exit....");
    scanf("%d", &key);
    system("clear"); // use system("cls") if on windows;
    content();
}

void saveCustomerDetails(char *name, int vehicleNo, char *vehicleType, int parkingNo, int fee, char *action)
{
    FILE *file = fopen("customers.csv", "a");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    time_t now = time(NULL);
    char *timeStr = ctime(&now);
    timeStr[strcspn(timeStr, "\n")] = '\0';

    fprintf(file, "%s,%d,%s,%d,%s,%d,%s\n", name, vehicleNo, vehicleType, parkingNo, timeStr, fee, action);
    fclose(file);
    printf("Customer details saved successfully.\n");
}

void showCustomerData()
{
    system("clear"); // use system("cls") if on windows;
    FILE *file = fopen("customers.csv", "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    char name[50], vehicleType[20], timeStr[50], action[20];
    int vehicleNo, parkingNo, fee;

    printf("---------------------------------------------------------------------------------------------------\n");
    printf("| %-15s | %-10s | %-10s | %-10s | %-25s | %-10s | %-10s |\n",
           "Name", "Vehicle No", "Type", "Parking No", "Time & Date", "Fee", "Action");
    printf("---------------------------------------------------------------------------------------------------\n");

    while (fscanf(file, "%[^,],%d,%[^,],%d,%[^,],%d,%s\n",
                  name, &vehicleNo, vehicleType, &parkingNo, timeStr, &fee, action) != EOF)
    {
        printf("| %-15s | %-10d | %-10s | %-10d | %-25s | %-10d | %-10s |\n",
               name, vehicleNo, vehicleType, parkingNo, timeStr, fee, action);
    }

    printf("---------------------------------------------------------------------------------------------------\n");

    fclose(file);
    int key;
    printf("\n\nPress any key to Exit....");
    scanf("%d", &key);
    system("clear"); // use system("cls") if on windows;
    content();
}

int content()
{
    system("clear"); // use system("cls") if on windows;
    int choice;
    printf("\n\n                                                      ----------->Welcome To Car Management System<-----------                                      ");
    printf("\n\n-------------------------------------------------------------- \n");
    printf("1. Park Vehicle \n");
    printf("-------------------------------------------------------------- \n");
    printf("2. Check Empty Spots in Parking-lot \n");
    printf("-------------------------------------------------------------- \n");
    printf("3. Check Time when your Vehicle was Parked in the Parking lot \n");
    printf("-------------------------------------------------------------- \n");
    printf("4. Instructions \n");
    printf("-------------------------------------------------------------- \n");
    printf("5. View All Customer Records\n");
    printf("-------------------------------------------------------------- \n");
    printf("6. Display Parking Slots (Graphics) \n");
    printf("-------------------------------------------------------------- \n");
    printf("7. Check Parking Lot Number of Previously Parked Vehicle\n");
    printf("-------------------------------------------------------------- \n");
    printf("8. Exit\n");
    printf("-------------------------------------------------------------- \n");

    printf("\n\n Enter Your Choice : ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        choice1();
    }
    else if (choice == 2)
    {
        choice2();
    }
    else if (choice == 3)
    {
        choice3();
    }
    else if (choice == 4)
    {
        choice4();
    }
    else if (choice == 5)
    {
        showCustomerData();
    }
    else if (choice == 6)
    {
        displayParkingGraphics();
    }
    else if (choice == 7)
    {
        checkPreviousParkingLot();
    }
    if (choice == 8)
    {
        system("clear"); // use system("cls") if on windows;
        return 0;
    }
    else
    {
        int key;
        printf(" \n Invalid Input! \n");
        printf(" Enter 1 to continue. Enter 0 to Exit. ");
        scanf("%d", &key);
        if (key == 1)
        {
            content();
        }
        if (key == 0)
        {
            system("clear"); // use system("cls") if on windows;
            return 0;
        }
    }
    return 0;
}

void choice1()
{
    int carNo;
    int stateno;
    char customerName[20];
    char another[3];
    char stateCode[3];
    char vehicleNumber[20];
    int key;
    int VC;

    system("clear"); // use system("cls") if on windows;

    if (prebus >= 25)
    {
        busprice = 200 + 200;
    }
    if (precar >= 50 && 100 > precar)
    {
        carprice = 100 + 50;
    }
    if (precar >= 100 && 150 >= precar)
    {
        carprice = 150 + 150;
    }
    if (prebike >= 50 && 100 > prebike)
    {
        bikeprice = 50 + 50;
    }
    if (prebike > 100 && 200 > prebike)
    {
        bikeprice = 100 + 50;
    }
    if (prebike > 200 && 300 >= prebike)
    {
        bikeprice = 150 + 50;
    }

    printf("\n\n                                                      ----------->Welcome To Car Management System<-----------                                      ");
    printf("\n\n                                                                    This is the Vehicle Fees Chart\n");
    printf("\n\n                                      Bus fees %dRs                        Car fees %dRs                        Bike fees %dRs \n", busprice, carprice, bikeprice);
    int f;
    printf("Enter your Name: ");
    scanf("%s", customerName);

    for (int i = 0; customerName[i] != '\0'; i++)
    {
        if (!isalpha(customerName[i]))
        {
            printf("Invalid name! Please enter only letters (A-Z, a-z).\n");
            printf("Enter 1 to continue. Enter 0 to Exit.");
            scanf("%d", &f);
            if (f == 0)
            {
                content();
            }
            if (f == 1)
            {
                choice1();
            }
        }
    }

    printf("\nEnter Vehicle State Code: ");
    scanf("%s", stateCode);
    for (int i = 0; stateCode[i] != '\0'; i++)
    {
        if (!isalpha(stateCode[i]))
        {
            printf("Invalid StateCode!\n");
            printf("Enter 1 to continue. Enter 0 to Exit.");
            scanf("%d", &f);
            if (f == 0)
            {
                content();
            }
            if (f == 1)
            {
                choice1();
            }
            choice1();
        }
    }

    printf("\nEnter Vehicle district Code: ");
    scanf("%d", &stateno);

    if (stateno < 0)
    {
        printf("Invalid state No!\n");
        printf("Enter 1 to continue. Enter 0 to Exit.");
        scanf("%d", &f);
        if (f == 0)
        {
            content();
        }
        if (f == 1)
        {
            choice1();
        }
    }
    int temp1 = stateno;
    int a = 0;
    int count1 = 0;
    while (temp1 != 0)
    {
        a = temp1 % 10;
        temp1 = temp1 / 10;
        count1++;
    }
    if (count1 < 2 || count1 > 2)
    {
        printf("Invalid StateNo! StateNo Should have 2 digits\n");
        printf("Enter 1 to continue. Enter 0 to Exit.");
        scanf("%d", &f);
        if (f == 0)
        {
            content();
        }
        if (f == 1)
        {
            choice1();
        }
    }

    printf("\nEnter Vehicle series Code: ");
    scanf("%s", another);

    for (int i = 0; another[i] != '\0'; i++)
    {
        if (!isalpha(another[i]))
        {
            printf("Invalid Vehicle Series code!\n");
            printf("Enter 1 to continue. Enter 0 to Exit.");
            scanf("%d", &f);
            if (f == 0)
            {
                content();
            }
            if (f == 1)
            {
                choice1();
            }
        }
    }

    printf("\nEnter Vehicle Number: ");
    scanf("%d", &carNo);

    if (carNo < 0)
    {
        printf("Invalid Car No!\n");
        printf("Enter 1 to continue. Enter 0 to Exit.");
        scanf("%d", &f);
        if (f == 0)
        {
            content();
        }
        if (f == 1)
        {
            choice1();
        }
    }

    int temp = carNo;
    int n = 0;
    int count = 0;
    while (temp != 0)
    {
        n = temp % 10;
        temp = temp / 10;
        count++;
    }
    if (count < 4 || count > 4)
    {
        printf("Invalid Car No!\n");
        printf("Enter 1 to continue. Enter 0 to Exit.");
        scanf("%d", &f);
        if (f == 0)
        {
            content();
        }
        if (f == 1)
        {
            choice1();
        }
    }

    snprintf(vehicleNumber, sizeof(vehicleNumber), "%s %d %s %d", stateCode, stateno, another, carNo);

    printf("\n---->Vehicle type<----\n");
    printf("1.Bus     2.Car     3.Bike \n");
    printf("\nEnter Vehicle type :");
    scanf("%d", &VC);

    if (VC > 3 || VC < 0)
    {
        printf("Invalid Input\n");
        printf("Enter 1 to continue. Enter 0 to Exit.");
        scanf("%d", &f);
        if (f == 0)
        {
            content();
        }
        if (f == 1)
        {
            choice1();
        }
    }

    if (VC == 1)
    {
        if (prebus == slotbus)
        {
            printf(" \n\n No Parking Space is available for Bus \n");
            printf("\n\n Try again Later !!! \n");
        }
        else
        {
            busStartTime = time(NULL);
            printf("\nYou need to pay Rs %d", busprice);
            printf("\n\nPress any key to get receipt....");
            scanf("%d", &key);
            system("clear"); // use system("cls") if on windows;
            printf("\n\n\n\nYour Payment is Successfully Done\n");
            printf("\n\nHere is Your Receipt!!!\n");
            printf("*****************\n");
            printf("Name :%s \n", customerName);
            printf("Vehicle Number : %s\n", vehicleNumber);
            time_t t;
            time(&t);
            time_t exitTime = t + 3600;
            struct tm *exit_tm = localtime(&exitTime);
            char exitTimeStr[30];
            strftime(exitTimeStr, sizeof(exitTimeStr), "%Y-%m-%d %H:%M:%S", exit_tm);
            printf("Current Time&Date : %s", ctime(&t));
            printf("Exit Time: %s\n", exitTimeStr);
            printf("Your Fees : %d \n", busprice);
            prebus++;
            randomnumberbus++;
            printf("Parking no: %d\n", randomnumberbus);
            printf("Ticket Validity : 1hr \n");
            printf("Vehicle type : Bus \n");
            printf("*****************\n");
            saveCustomerDetails(customerName, carNo, "Bus", randomnumberbus, busprice, "Parked");
            printf("\n\nPress any key to Exit....");
            scanf("%d", &key);
            system("clear"); // use system("cls") if on windows;
        }
    }

    if (VC == 2)
    {
        if (precar == slotcar)
        {
            printf("\n\n No Parking Space is available for Car \n");
            printf("\n\n Try again Later !!! \n");
        }
        else
        {
            carStartTime = time(NULL);
            printf("\nYou need to pay Rs %d", carprice);
            printf("\n\nPress any key to get receipt....");
            scanf("%d", &key);
            system("clear"); // use system("cls") if on windows;
            printf("\n\n\n\nYour Payment is Successfully Done\n");
            printf("\n\nHere is Your Receipt!!!\n");
            printf("*****************\n");
            printf("Name :%s \n", customerName);
            printf("Vehicle Number : %s\n", vehicleNumber);
            time_t t;
            time(&t);
            time_t exitTime = t + 3600;
            struct tm *exit_tm = localtime(&exitTime);
            char exitTimeStr[30];
            strftime(exitTimeStr, sizeof(exitTimeStr), "%Y-%m-%d %H:%M:%S", exit_tm);
            printf("Current Time&Date : %s", ctime(&t));
            printf("Exit Time: %s\n", exitTimeStr);
            printf("Your Fees : %d \n", carprice);
            randomnumbercar++;
            printf("Parking no: %d\n", randomnumbercar);
            printf("Ticket Validity : 1hr \n");
            printf("Vehicle type : Car \n");
            printf("*****************\n");
            saveCustomerDetails(customerName, carNo, "Car", randomnumbercar, carprice, "Parked");
            precar++;
            printf("\n\nPress any key to Exit....");
            scanf("%d", &key);
            system("clear"); // use system("cls") if on windows;
        }
    }

    if (VC == 3)
    {
        if (prebike == slotbike)
        {
            printf("\n\n No Parking Space is available for Bike \n");
            printf("\n\n Try again Later !!! \n");
        }
        else
        {
            bikeStartTime = time(NULL);
            printf("\nYou need to pay Rs %d", bikeprice);
            printf("\n\nPress any key to get receipt....");
            scanf("%d", &key);
            system("clear"); // use system("cls") if on windows;
            printf("\n\n\n\nYour Payment is Successfully Done\n");
            printf("\n\nHere is Your Receipt!!!\n");
            printf("*****************\n");
            printf("Name :%s \n", customerName);
            printf("Vehicle Number : %s\n", vehicleNumber);
            time_t t;
            time(&t);
            time_t exitTime = t + 3600;
            struct tm *exit_tm = localtime(&exitTime);
            char exitTimeStr[30];
            strftime(exitTimeStr, sizeof(exitTimeStr), "%Y-%m-%d %H:%M:%S", exit_tm);
            printf("Current Time&Date : %s", ctime(&t));
            printf("Exit Time: %s\n", exitTimeStr);
            printf("Your Fees : %d \n", bikeprice);
            randomnumberbike++;
            printf("Parking no: %d\n", randomnumberbike);
            printf("Ticket Validity : 1hr \n");
            printf("Vehicle type : Bike \n");
            printf("*****************\n");
            saveCustomerDetails(customerName, carNo, "Bike", randomnumberbike, bikeprice, "Parked");
            prebike++;
            printf("\n\nPress any key to Exit....");
            scanf("%d", &key);
            system("clear"); // use system("cls") if on windows;
        }
    }

    content();
}

void choice2()
{
    system("clear"); // use system("cls") if on windows;

    printf("\n\n\nNumber of Empty Parking Spots for Bus :%d \n\n", slotbus - prebus);
    printf("Number of Empty Parking Spots for Car :%d \n\n", slotcar - precar);
    printf("Number of Empty Parking Spots for Bike :%d \n\n", slotbike - prebike);

    int key;
    printf("\n\nPress any key to Exit....");
    scanf("%d", &key);
    system("clear"); // use system("cls") if on windows;
    content();
}

void choice3()
{
    system("clear"); // use system("cls") if on windows;
    int vehicleType;
    char customerName[10];
    int vehicleNo;
    char vehicleTypeStr[10];
    int parkingNo;
    double seconds;
    time_t currentTime = time(NULL);

    int f;
    printf("\nEnter your Name: ");
    scanf("%s", customerName);
    for (int i = 0; customerName[i] != '\0'; i++)
    {
        if (!isalpha(customerName[i]))
        {
            printf("Invalid name! Please enter only letters (A-Z, a-z).\n");
            printf("Enter 1 to continue. Enter 0 to Exit.");
            scanf("%d", &f);
            if (f == 0)
            {
                content();
            }
            if (f == 1)
            {
                choice3();
            }
        }
    }
    printf("\nEnter your Vehicle Number: ");
    scanf("%d", &vehicleNo);

    if (vehicleNo < 0)
    {
        printf("Invalid state No!\n");
        printf("Enter 1 to continue. Enter 0 to Exit.");
        scanf("%d", &f);
        if (f == 0)
        {
            content();
        }
        if (f == 1)
        {
            choice3();
        }
    }
    int temp1 = vehicleNo;
    int a = 0;
    int count1 = 0;
    while (temp1 != 0)
    {
        a = temp1 % 10;
        temp1 = temp1 / 10;
        count1++;
    }
    if (count1 < 4 || count1 > 4)
    {
        printf("Invalid Vechicle Number! StateNo Should have 4 digits\n");
        printf("Enter 1 to continue. Enter 0 to Exit.");
        scanf("%d", &f);
        if (f == 0)
        {
            content();
        }
        if (f == 1)
        {
            choice3();
        }
    }

    printf("\nEnter the vehicle type to check time (1.Bus  2.Car  3.Bike): ");
    scanf("%d", &vehicleType);

    if (vehicleType > 3 || vehicleType < 0)
    {
        printf("Invalid Input\n");
        printf("Enter 1 to continue. Enter 0 to Exit.");
        scanf("%d", &f);
        if (f == 0)
        {
            content();
        }
        if (f == 1)
        {
            choice3();
        }
    }

    if (vehicleType == 1 && busStartTime != 0)
    {
        seconds = difftime(currentTime, busStartTime);
        strcpy(vehicleTypeStr, "Bus");
        parkingNo = randomnumberbus;
    }
    else if (vehicleType == 2 && carStartTime != 0)
    {
        seconds = difftime(currentTime, carStartTime);
        strcpy(vehicleTypeStr, "Car");
        parkingNo = randomnumbercar;
    }
    else if (vehicleType == 3 && bikeStartTime != 0)
    {
        seconds = difftime(currentTime, bikeStartTime);
        strcpy(vehicleTypeStr, "Bike");
        parkingNo = randomnumberbike;
    }
    else
    {
        printf("\nTime data not available for this vehicle type.");
        content();
    }

    int hours = (int)(seconds / 3600);
    int minutes = (int)((seconds - (hours * 3600)) / 60);
    int secs = (int)(seconds - (hours * 3600) - (minutes * 60));

    printf("\nVehicle Parked since: %02d:%02d:%02d\n", hours, minutes, secs);
    saveCustomerDetails(customerName, vehicleNo, vehicleTypeStr, parkingNo, 0, "Checked");

    printf("\n\nPress any key to Exit....");
    int key;
    scanf("%d", &key);
    system("clear"); // use system("cls") if on windows;
    content();
}

void choice4()
{
    system("clear"); // use system("cls") if on windows;

    printf("Instructions:\n\n1. Ensure your vehicle is properly parked in the designated slot. \n2. Retain your parking ticket for verification.\n3. Payments are non-refundable.\n4. Exceeding the ticket time validity incurs additional charges.\n5. Adhere to safety and security guidelines.\n");

    int key;
    printf("\n\nPress any key to Exit....");
    scanf("%d", &key);
    system("clear"); // use system("cls") if on windows;
    content();
}