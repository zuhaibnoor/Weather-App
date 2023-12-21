#include <stdio.h>
#include <stdlib.h>
#include "Functions/retrieval.c"
#include "Functions/read.c"
#include "Functions/date_utils.c"
#include "Functions/ip_utils.c"



int main() {
    cJSON *json_parse = retIp();//Function in ip_utils.c purpose to get langitude and latitude for dynamic weather application
    char* date = getDate();//Trying To Get Todays Date Function In date_utils.c

    if (json_parse != NULL) {
        cJSON *loc = cJSON_GetObjectItemCaseSensitive(json_parse, "loc");
        ret(loc, date);//Function In retrival.c
        cJSON_Delete(json_parse);
    }

    

    return 0;
}
