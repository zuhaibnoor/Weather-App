#include <stdio.h>
#include <stdlib.h>

#include "Functions/read.c"
#include "Functions/date_utils.c"




int main() {
   
   retIp();
   cJSON *LOC = getLoc();
    char* DATE = getDate();

    //res(LOC, DATE);
    return 0;
}

