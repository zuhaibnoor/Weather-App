#include <stdio.h>
#include <stdlib.h>
#include "cJSON.c"

int readJSON() {
    FILE *fptr = fopen("response.json", "r");

    if (fptr != NULL) {
        fseek(fptr, 0, SEEK_END);
        long totalSize = ftell(fptr) + 1;
        fseek(fptr, 0, SEEK_SET);

        char *buffer = malloc(totalSize);

        if (buffer != NULL) {
            int len = fread(buffer, 1, totalSize, fptr);
            fclose(fptr);

            FILE *f2ptr = fopen("weatherData.txt", "w");

            if (f2ptr != NULL) {
                cJSON *json = cJSON_Parse(buffer);

                if (json == NULL) {
                    const char *error_ptr = cJSON_GetErrorPtr();
                    if (error_ptr != NULL) {
                        printf("JSON Parse Error: %s\n", error_ptr);
                    }
                    free(buffer);
                    return 1;
                }

                //Extracting data and printing values
                cJSON *location = cJSON_GetObjectItemCaseSensitive(json, "location");
                cJSON *name = cJSON_GetObjectItemCaseSensitive(location, "name");
                cJSON *region = cJSON_GetObjectItemCaseSensitive(location, "region");
                cJSON *country = cJSON_GetObjectItemCaseSensitive(location, "country");

                // Extract other fields...
                 // //current
                cJSON *current = cJSON_GetObjectItemCaseSensitive(json, "current"); 
                cJSON *temp_c = cJSON_GetObjectItemCaseSensitive(current,"temp_c");
                
                 cJSON *temp_f = cJSON_GetObjectItemCaseSensitive(current,"temp_f");
                cJSON *is_day = cJSON_GetObjectItemCaseSensitive(current,"is_day");
               

                // //current -> condition
                cJSON *condition = cJSON_GetObjectItemCaseSensitive(current,"condition");
                cJSON *text = cJSON_GetObjectItemCaseSensitive(condition,"text");

                // //other
                cJSON *wind_mph = cJSON_GetObjectItemCaseSensitive(current, "wind_mph"); 
                cJSON *wind_degree = cJSON_GetObjectItemCaseSensitive(current, "wind_degree"); 
               
                cJSON *wind_dir = cJSON_GetObjectItemCaseSensitive(current, "wind_dir"); 
                
                 cJSON *precip_in = cJSON_GetObjectItemCaseSensitive(current, "precip_in"); 
                 cJSON *humidity = cJSON_GetObjectItemCaseSensitive(current, "humidity"); 
                 cJSON *cloud = cJSON_GetObjectItemCaseSensitive(current, "cloud"); 
                 cJSON *feelslike_c = cJSON_GetObjectItemCaseSensitive(current, "feelslike_c"); 
                 cJSON *uv = cJSON_GetObjectItemCaseSensitive(current, "uv"); 


                //Writing In File
                fprintf(f2ptr, "%s\n", name->valuestring);
                fprintf(f2ptr, "%s\n", region->valuestring);
                fprintf(f2ptr, "%s\n", country->valuestring);
                fprintf(f2ptr, "%.2f\n", temp_c->valuedouble);
                fprintf(f2ptr, "%.2f\n", temp_f->valuedouble);
                fprintf(f2ptr, "%d\n", is_day->valueint);
                fprintf(f2ptr, "%s\n", text->valuestring);
                fprintf(f2ptr, "%s\n", wind_dir->valuestring);
                fprintf(f2ptr, "%.2f\n", wind_mph->valuedouble);
                fprintf(f2ptr, "%.2f\n", wind_degree->valuedouble);
                fprintf(f2ptr, "%.2f\n", precip_in->valuedouble);
                fprintf(f2ptr, "%.2f\n", humidity->valuedouble);
                fprintf(f2ptr, "%.2f\n", cloud->valuedouble);
                fprintf(f2ptr, "%.2f\n", feelslike_c->valuedouble);
                fprintf(f2ptr, "%.2f\n", uv->valuedouble);

                
                // Clean up cJSON object
                cJSON_Delete(json);

                fclose(f2ptr);
            } else {
                printf("Error opening weatherData.txt for writing\n");
            }

            free(buffer);
        } else {
            printf("Memory allocation failed\n");
        }
    } else {
        printf("Error opening response.json\n");
    }

    return 0;
}
