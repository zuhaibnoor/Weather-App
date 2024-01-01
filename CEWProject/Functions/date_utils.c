#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>



void incrementDate(char* date) {
    struct tm tm_date = {0}; // Initialize struct tm with zeros

    // Parse the date string manually
    sscanf(date, "%d-%d-%d", &tm_date.tm_year, &tm_date.tm_mon, &tm_date.tm_mday);
    tm_date.tm_year -= 1900; // Adjust year (years since 1900)
    tm_date.tm_mon--;       // Adjust month (0-based)

    // Increment the day by 1
    tm_date.tm_mday++;

    // Use mktime to normalize the date
    mktime(&tm_date);

    // Convert struct tm back to string
    strftime(date, 12, "%Y-%m-%d", &tm_date);
}

char* getDate()
{
    time_t t;
    struct tm *current_time;

    time(&t);
    current_time = localtime(&t);

    // Format the current date as a string
     char* date_string = (char*)malloc(10 * sizeof(char));  // Adjust the size based on the format "YYYY-MM-DD"
    sprintf(date_string, "%04d-%02d-%02d",
            current_time->tm_year + 1900,
            current_time->tm_mon + 1,
            current_time->tm_mday);

   
    return date_string;
}
