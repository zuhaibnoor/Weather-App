#include <stdio.h>
//#include "Functions/retrieval.c" 
//#include "Functions/read.c"
//#include "Functions/date_utils.c"
//#include "Functions/ip_utils.c"
#include "headers/weather.h"
#include "Functions/report.c"

enum Locations {
    FIRST_LOCATION  = '1',
    SECOND_LOCATION = '2',
    THIRD_LOCATION  = '3'
};

int main() {
    
        char* date = getDate();         // Trying To Get Today's Date Function In date_utils.c

    
        ret(date, FIRST_LOCATION);  // Function in retrieval.c
        incrementDate(date);
        ret(date, SECOND_LOCATION);
        incrementDate(date);
        ret(date, THIRD_LOCATION);
    
        Read();
        printFileContents("display.txt");
        printFileContents("analysis.txt");

        printf("DONE");

    return 0;
}
