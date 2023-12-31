#include <stdio.h>
#include "Functions/retrieval.c" 
#include "Functions/read.c"
#include "Functions/date_utils.c"
#include "Functions/ip_utils.c"

enum Locations {
    FIRST_LOCATION  = '1',
    SECOND_LOCATION = '2',
    THIRD_LOCATION  = '3'
};

int main() {
    cJSON *json_parse = retIp();    // Function in ip_utils.c to get latitude and longitude for a dynamic weather application
    char* date = getDate();         // Trying To Get Today's Date Function In date_utils.c

    if (json_parse != NULL) {
        cJSON *loc = cJSON_GetObjectItemCaseSensitive(json_parse, "loc");
        ret(loc, date, FIRST_LOCATION);  // Function in retrieval.c
        incrementDate(date);
        ret(loc, date, SECOND_LOCATION);
        incrementDate(date);
        ret(loc, date, THIRD_LOCATION);
        cJSON_Delete(json_parse);
        Read();
    }

    printf("DONE");

    return 0;
}
