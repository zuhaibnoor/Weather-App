#include <stdio.h>
#include <stdlib.h>  // For atoi

#include "headers/weather.h"
#include "Functions/report.c"  // Make sure this includes the necessary functions

enum Locations {
    FIRST_LOCATION  = '1',
    SECOND_LOCATION = '2',
    THIRD_LOCATION  = '3'
};

int main(int argc, char* argv[]) {
    int Result = 0;  // Initialize Result to a default value

    if (argc >= 2) {
        int choice = atoi(argv[1]); // Convert the second command-line argument to an integer

        if (choice == 1) {
            char* date = getDate();
            ret(date, FIRST_LOCATION);
            incrementDate(date);
            ret(date, SECOND_LOCATION);
            incrementDate(date);
            ret(date, THIRD_LOCATION);
        } else if (choice == 2) {
        	Result = Read();
        	printf("%d", Result);
        } else if (choice == 3) {
            printFileContents("display.txt");
            printFileContents("analysis.txt");
        } 
    } 
	return Result;
    
}

