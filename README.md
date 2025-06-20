# Parkinglot-management-using-C

This C program is a simple Car Management System designed to help manage vehicle parking in a lot. It allows users to park vehicles, check available spots, view parking history, and see parking instructions.

#**Features**

      1.Vehicle Parking: Park buses, cars, and bikes with associated fees.
      2.Dynamic Pricing: Parking fees can increase based on the number of vehicles already parked.
      3.Parking Spot Availability: Check the number of empty slots for each vehicle type.
      4.Parking Time Tracking: See how long a vehicle has been parked.
      5.Customer Records: View a detailed list of all parked and checked vehicles, including name, vehicle number, type, parking spot, time, and fees.
      6.Graphical Representation: Visualize the parking lot occupancy with [X] for occupied and [ ] for empty slots.
      7.Previous Parking Lookup: Check details of a previously parked vehicle using customer name and vehicle number.
      8.User Authentication: A basic login system is in place for accessing the main menu.
      9.Input Validation: Basic validation for user input like names, vehicle numbers, and choices.

#**Getting Started**
***Prerequisites**

      To compile and run this program, you'll need a C compiler (like GCC).

***How to Compile**

      1.Save the code: Save the provided C code as a .c file (e.g., parking_system.c).
      
      2.Open a terminal or command prompt: Navigate to the directory where you saved the file.
      
      3.Compile the code: Use the following command to compile the program: gcc parking_system.c -o parking_system -lm
      gcc: The C compiler.
      parking_system.c: Your source code file.
      -o parking_system: Specifies the output executable name.
      -lm: Links the math library, which is used for difftime (though math.h itself isn't strictly necessary for difftime, it's good practice to include it if you might use other math functions).

***How to Run**

      After successful compilation, you can run the executable: ./parking_system 

***How to Use**

      1.Login: Upon starting the program, you'll be prompted for a UserName and Password.
            For this version, the password is hardcoded as 1. You can enter any username.
      
      2.Main Menu: After a successful login, you'll see the main menu with the following options:
      
        *Park Vehicle: Allows you to park a bus, car, or bike. You'll need to enter your name, vehicle details (state code, district code, series code, vehicle number), and select the vehicle type. The system will display the fees and a receipt.
        
        *Check Empty Spots in Parking-lot: Shows the remaining available slots for buses, cars, and bikes.
        
        *Check Time when your Vehicle was Parked in the Parking lot: Enter your name and vehicle number, and select the vehicle type to see how long it has been parked.
        
        *Instructions: Displays important guidelines for parking.
        
        *View All Customer Records: Shows a table of all recorded parking and checking activities.
          
        *Display Parking Slots (Graphics): Provides a visual representation of occupied ([X]) and empty ([ ]) parking spots for each vehicle type.
        
        *Check Parking Lot Number of Previously Parked Vehicle: Find details of a vehicle you've previously parked by entering your name and vehicle number.
        
        *Exit: Exits the program.
  
#**File Storage**

      The program stores customer parking details in a file named customers.csv. This file is created automatically if it doesn't exist. Each entry includes:
      
      1.Name
      2.Vehicle Number
      3.Vehicle Type
      4.Parking Lot Number
      5.Time & Date of action
      6.Fee paid
      7.Action (e.g., "Parked", "Checked")

***Important Notes**

    1.system("clear"): This command is used to clear the console screen. It works on Unix-like systems (Linux, macOS). If you are on Windows, you might need to change it to system("cls").
    2.Password Handling: The current password input is basic. In a real-world application, password input should be masked (e.g., using getch() for hidden input) and securely handled (e.g., hashed and stored). The commented-out getch() block shows an attempt at this.
    3.Error Handling: While some input validation is present, robust error handling (e.g., for file operations, unexpected user input) could be improved.
    4.Time Tracking: The busStartTime, carStartTime, and bikeStartTime variables are global and only track the start time for the last vehicle of that type parked. This means that if multiple vehicles of the same type are parked, only the most recent one's start time is accurately tracked for the "Check Time" feature. For a more robust system, each parked vehicle would need its own associated time_t for its entry time.
    5.Vehicle Number Validation: The vehicle number validation checks for exactly 4 digits. This might not be suitable for all vehicle numbering formats.
