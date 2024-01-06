#include <stdio.h>
#include <stdlib.h>
#include "../headers/cJSON.h"
#include <curl/curl.h>
#include <string.h>



typedef struct {
    char time[64];
    double temp_C;
    char condition[64];
    int is_day;
    double windKph;
    double humidity;
    double heatIndex_C;
    double chance_of_rain;
    double UV;

} Days_Forecast;

typedef struct {
    char city[64];
    char country[64];
    char date[64];
    double temp;
    char condition[64];
    double maxTemp;
    double minTemp;
    double maxWind;
    double minWind;
    double avgTemp;
    //double avgWind;
    double avgHumidity;
    double chanceOfRain;
    double UV;
    char sunrise[64];
    char sunset[64];
    char moonrise[64];
    char moonset[64];
    Days_Forecast Night[2];
    Days_Forecast Day[2];
} Days;


double average(double* arr)
{
    int s = 0;
    for (int i = 0; i < 3; i++)
    {
        s += arr[i];
    }
    return s/3;
}


void Analyze(Days* d)
{
    Days d1 = d[0];
    Days d2 = d[1];
    Days d3 = d[2];

    double avgTemp[3] = {d1.avgTemp, d2.avgTemp, d3.avgTemp};
    double avgHumidity[3] = {d1.avgHumidity, d2.avgHumidity, d3.avgHumidity};
    double avgUV[3] = {d1.UV, d2.UV, d3.UV};
    double avgRain[3] = {d1.chanceOfRain, d2.chanceOfRain, d3.chanceOfRain};
    double avgWind[3] = {d1.maxWind, d2.maxWind, d3.maxWind};

    double temp_analysis = average(avgTemp); 
    double humidity_analysis = average(avgHumidity); 
    double UV_analysis = average(avgUV); 
    double Rain_analysis = average(avgRain); 
    double Wind_analysis = average(avgWind);

    

    FILE* fptr = fopen("Anamoly.log", "w");
    FILE *fptr2 = fopen("history.log", "a");
    
    if(fptr != NULL && fptr2 != NULL)
    {
        if ((int)temp_analysis > 40)
        {
            fprintf(fptr, "Warning: Temperature Too High!!\n");
            fprintf(fptr2, "Warning: Temperature Too High!!\n");
        } else if ((int)temp_analysis < 10)
        {
            fprintf(fptr, "Warning: Temperature Too Low!!\n");
            fprintf(fptr2, "Warning: Temperature Too Low!!\n");
        }

        if ((int)humidity_analysis >= 65)
        {
            fprintf(fptr, "Warning: High Moisture!!\n");
            fprintf(fptr2, "Warning: High Moisture!!\n");
        } else if ((int)humidity_analysis <= 55)
        {
            fprintf(fptr, "Warning: Low Moisture!!\n");
            fprintf(fptr2, "Warning: Low Moisture!!\n");
        }
        if ((int)UV_analysis >= 8)
        {
            fprintf(fptr, "Warning: Avoid being outside during midday hours! Make sure you seek shade! Shirt, sunscreen and hat are a must!\n");
            fprintf(fptr2, "Warning: Avoid being outside during midday hours! Make sure you seek shade! Shirt, sunscreen and hat are a must!\n");
        } 
        if (Rain_analysis >= 0.7 && Wind_analysis >= 93)
        {
            fprintf(fptr, "Warning: Thunderstorm!!\n");
            fprintf(fptr2, "Warning: Thunderstorm!!\n");
        }

        if (Wind_analysis >= 93)
        {
            fprintf(fptr, "Warning: Wind Gust!!\n");
            fprintf(fptr2, "Warning: Wind Gust!!\n");
        }

    }
    fclose(fptr);
    fclose(fptr2);
    

    
    
    
    
    
}


void display(Days* d)
{
    for (int i = 0; i < 3; i++)
    {
        Days_Forecast* N = d[i].Night;
        Days_Forecast* D = d[i].Day;

        printf("%s\n", d[i].city);
        printf("%s\n", d[i].country);
        printf("%s\n", d[i].date);
        printf("%s\n", d[i].condition);
        printf("%f\n", d[i].temp);
        printf("%f\n", d[i].maxTemp);
        printf("%f\n", d[i].minTemp);
        printf("%f\n", d[i].maxWind);
        printf("%f\n", d[i].minWind);
        printf("%f\n", d[i].avgHumidity);
        printf("%f\n", d[i].avgTemp);
        printf("%f\n", d[i].chanceOfRain);
        printf("%f\n", d[i].UV);
        printf("%s\n", d[i].sunset);
        printf("%s\n", d[i].sunrise);
        printf("%s\n", d[i].moonrise);
        printf("%s\n", d[i].moonset);
        for (int j = 0; j<2; j++) {
            printf("%s\n", N[j].time);
            printf("DAY %s\n", D[j].time);
            printf("%s\n", N[j].condition);
            printf("%s\n", D[j].condition);
            printf("%f\n", N[j].windKph);
            printf("%f\n", D[j].windKph);
            printf("%f\n", D[j].humidity);
            printf("%f\n", N[j].humidity);
            printf("%f\n", N[j].heatIndex_C);
            printf("%f\n", D[j].heatIndex_C);
            printf("%f\n", D[j].chance_of_rain);
            printf("%f\n", N[j].chance_of_rain);
            printf("%f\n", N[j].UV);
            printf("%f\n", D[j].UV);
    }
}
}

void writeTxt(Days *d) {
    FILE *fptr = fopen("display.txt", "w");
    if (fptr == NULL) {
        perror("Error opening file for writing");
        return;
    }

    Days day = d[0];
    Days_Forecast *dd = day.Day;
     fprintf(fptr, "--------------------- %s -------------------\n", day.date);
    fprintf(fptr, "City: %s\n", day.city);
        fprintf(fptr, "Country: %s\n",day.country);
        fprintf(fptr, "Date: %s\n",day.date);
        fprintf(fptr, "Condition: %s\n",day.condition);
        fprintf(fptr, "Temperature: %f\n",day.temp);
        fprintf(fptr, "Max Temperature: %f\n",day.maxTemp);
        fprintf(fptr, "Min Temperature: %f\n",day.minTemp);
        fprintf(fptr, "Max Wind: %f\n",day.maxWind);
        //fprintf(fptr, "Min Wind: %f\n",day.minWind);
        fprintf(fptr, "Avg Humidity: %f\n",day.avgHumidity);
        fprintf(fptr, "Avg Temperature: %f\n",day.avgTemp);
        fprintf(fptr, "Chance of Rain: %f\n",day.chanceOfRain);
        fprintf(fptr, "UV: %f\n",day.UV);
        fprintf(fptr, "Sunset: %s\n",day.sunset);
        fprintf(fptr, "Sunrise: %s\n",day.sunrise);
        fprintf(fptr, "Moonrise: %s\n",day.moonrise);
        fprintf(fptr, "Moonset: %s\n",day.moonset);

        for (int j = 0; j < 2; j++) {
            fprintf(fptr, "--------------------- NIGHT %s -------------------\n", day.Night[j].time);
            fprintf(fptr, "Night[%d] Time: %s\n", j,day.Night[j].time);
           // printf("%s", day.Night[j].time);
            fprintf(fptr, "Night[%d] is_day: %d\n", j,day.Night[j].is_day);
            fprintf(fptr, "Night[%d] condition: %s\n", j,day.Night[j].condition);
            fprintf(fptr, "Night[%d] Wind: %f\n", j,day.Night[j].windKph);
            fprintf(fptr, "Night[%d] Humidity: %f\n", j,day.Night[j].humidity);
            fprintf(fptr, "Night[%d] Heat Index: %f\n", j,day.Night[j].heatIndex_C);
            fprintf(fptr, "Night[%d] Chance of Rain: %f\n", j,day.Night[j].chance_of_rain);
            fprintf(fptr, "Night[%d] UV: %f\n", j,day.Night[j].UV);
       
        }
        for (int j = 0; j < 2; j++) {
    fprintf(fptr, "--------------------- DAY %s -------------------\n", day.Day[j].time);

    // Check if Day data is available
    if (day.Day != NULL) {
        fprintf(fptr, "Day[%d] Time: %s\n", j, dd[j].time);
        fprintf(fptr, "Day[%d] Condition: %s\n", j, dd[j].condition);
        fprintf(fptr, "Day[%d] is_day: %d\n", j, dd[j].is_day);
        fprintf(fptr, "Day[%d] Wind: %f\n", j, dd[j].windKph);
        fprintf(fptr, "Day[%d] Humidity: %f\n", j, dd[j].humidity);
        fprintf(fptr, "Day[%d] Heat Index: %f\n", j, dd[j].heatIndex_C);
        fprintf(fptr, "Day[%d] Chance of Rain: %f\n", j, dd[j].chance_of_rain);
        fprintf(fptr, "Day[%d] UV: %f\n", j, dd[j].UV);
    } else {
        fprintf(fptr, "No Day data available for this day.\n");
    }
}




    for (int i = 1; i < 3; i++) {
        fprintf(fptr, "--------------------- %s -------------------\n", d[i].date);
    //     fprintf(fptr, "City: %s\n", d[i].city);
    //     fprintf(fptr, "Country: %s\n", d[i].country);
         fprintf(fptr, "Date: %s\n", d[i].date);
        fprintf(fptr, "Condition: %s\n", d[i].condition);
        fprintf(fptr, "Temperature: %f\n", d[i].temp);
        fprintf(fptr, "Max Temperature: %f\n", d[i].maxTemp);
        fprintf(fptr, "Min Temperature: %f\n", d[i].minTemp);
    ////     fprintf(fptr, "Max Wind: %f\n", d[i].maxWind);
    ////     fprintf(fptr, "Min Wind: %f\n", d[i].minWind);
        fprintf(fptr, "Avg Humidity: %f\n", d[i].avgHumidity);
        fprintf(fptr, "Avg Temperature: %f\n", d[i].avgTemp);
        fprintf(fptr, "Chance of Rain: %f\n", d[i].chanceOfRain);
        fprintf(fptr, "UV: %f\n", d[i].UV);
        fprintf(fptr, "Sunset: %s\n", d[i].sunset);
        fprintf(fptr, "Sunrise: %s\n", d[i].sunrise);
        fprintf(fptr, "Moonrise: %s\n", d[i].moonrise);
        fprintf(fptr, "Moonset: %s\n", d[i].moonset);

        
    }

    if (fclose(fptr) != 0) {
        perror("Error closing file");
    }
}









Days* parseJSON() {
    Days *d = NULL;
    d = (Days*)malloc(sizeof(Days)*3);

    
    for (int i = 1; i < 4; i++ )
    {
        char fname[50];  
        strcpy(fname, "response");

        char val[2];  
        sprintf(val, "%d", i);

        char JSON[] = ".json";
        strcat(fname, val);
        strcat(fname, JSON);
        
        FILE* fptr = fopen(fname, "r");
        if (fptr == NULL)
        {
            printf("Error In Opening The File\n");
            return d;
        }
        
        fseek(fptr, 0 , SEEK_END);
        int len = ftell(fptr) + 1;
        fseek(fptr, 0 , SEEK_SET);
        

        char* buffer = malloc(len);
        if (buffer != NULL)
        {
            int s = fread(buffer, 1, len, fptr);
            fclose(fptr);
            cJSON *jsonParse = cJSON_Parse(buffer);
            cJSON *location = cJSON_GetObjectItemCaseSensitive(jsonParse, "location");
            cJSON *current = cJSON_GetObjectItemCaseSensitive(jsonParse, "current");
            cJSON *condition = cJSON_GetObjectItemCaseSensitive(current,"condition");
            cJSON *texT = cJSON_GetObjectItemCaseSensitive(condition,"text");
            cJSON *forecast = cJSON_GetObjectItemCaseSensitive(jsonParse, "forecast");
            cJSON *forecastDay = cJSON_GetObjectItemCaseSensitive(forecast, "forecastday");
            cJSON *name = cJSON_GetObjectItemCaseSensitive(location, "name");
            cJSON *country = cJSON_GetObjectItemCaseSensitive(location, "country");
           // cJSON *localtime = cJSON_GetObjectItemCaseSensitive(location, "localtime");
            cJSON *temp_c = cJSON_GetObjectItemCaseSensitive(current,"temp_c");
            cJSON *text = cJSON_GetObjectItemCaseSensitive(condition,"text");
            cJSON *FC = cJSON_GetArrayItem(forecastDay, 0);
             cJSON *localtime = cJSON_GetObjectItemCaseSensitive(FC, "date");
            cJSON *day = cJSON_GetObjectItemCaseSensitive(FC,"day");
            cJSON *astro = cJSON_GetObjectItemCaseSensitive(FC,"astro");
            cJSON *max_temp = cJSON_GetObjectItemCaseSensitive(day,"maxtemp_c");
            cJSON *min_temp = cJSON_GetObjectItemCaseSensitive(day,"mintemp_c");
            cJSON *avgtemp_c = cJSON_GetObjectItemCaseSensitive(day,"avgtemp_c");
            cJSON *max_wind = cJSON_GetObjectItemCaseSensitive(day,"maxwind_kph");
           // cJSON *min_wind = cJSON_GetObjectItemCaseSensitive(day,"minwind_kph");
            cJSON *avghumidity = cJSON_GetObjectItemCaseSensitive(day,"avghumidity");
            cJSON *daily_chance_of_rain = cJSON_GetObjectItemCaseSensitive(day,"daily_chance_of_rain");
            cJSON *uv = cJSON_GetObjectItemCaseSensitive(day,"uv");
            // printf("%d\n", avgtemp_c->valueint);
            cJSON *sunrise = cJSON_GetObjectItemCaseSensitive(astro,"sunrise");
            cJSON *moonrise = cJSON_GetObjectItemCaseSensitive(astro,"moonrise");
            cJSON *sunset = cJSON_GetObjectItemCaseSensitive(astro,"sunset");
            cJSON *moonset = cJSON_GetObjectItemCaseSensitive(astro,"moonset");
            cJSON *hour = cJSON_GetObjectItemCaseSensitive(FC,"hour");
            printf(" Parse1: %lf\n", max_wind->valuedouble);
          //  printf(" Parse2: %lf\n", min_wind->valuedouble);

            strncpy(d[i-1].city, name->valuestring, sizeof(d[i-1].city) - 1);
            d[i-1].city[sizeof(d[i-1].city) - 1] = '\0';  // Ensure null-terminated string
            strncpy(d[i-1].country, country->valuestring, sizeof(d[i-1].country)-1);
            d[i-1].country[sizeof(d[i-1].country)-1] = '\0';
            strncpy(d[i-1].date, localtime->valuestring, sizeof(d[i-1].date) - 1);
            d[i-1].date[sizeof(d[i-1].date) - 1] = '\0';  
            strncpy(d[i-1].condition, texT->valuestring, sizeof(d[i-1].condition) - 1);
            d[i-1].condition[sizeof(d[i-1].condition) - 1] = '\0';  
            d[i-1].temp = temp_c->valuedouble;
            d[i-1].maxTemp = max_temp->valuedouble;
            
            d[i-1].minTemp = min_temp->valuedouble;
            d[i-1].maxWind = max_wind->valuedouble;
            //d[i-1].minWind = min_wind->valuedouble;
            d[i-1].avgTemp = avgtemp_c->valuedouble;
            d[i-1].avgHumidity = avghumidity->valuedouble;
            d[i-1].chanceOfRain = daily_chance_of_rain->valueint;
            d[i-1].UV = uv->valueint;
            strncpy(d[i-1].sunrise, sunrise->valuestring, sizeof(d[i-1].sunrise) - 1);
            d[i-1].sunrise[sizeof(d[i-1].sunrise) - 1] = '\0';  
            strncpy(d[i-1].sunset, sunset->valuestring, sizeof(d[i-1].sunset) - 1);
            d[i-1].sunset[sizeof(d[i-1].sunset) - 1] = '\0';  
            strncpy(d[i-1].moonrise, moonrise->valuestring, sizeof(d[i-1].moonrise) - 1);
            d[i-1].moonrise[sizeof(d[i-1].moonrise) - 1] = '\0';  
            strncpy(d[i-1].moonset, moonset->valuestring, sizeof(d[i-1].moonset) - 1);
            d[i-1].moonset[sizeof(d[i-1].moonset) - 1] = '\0';  
            
           //printf("%s %d", d[i-1].moonset, d[i-1].chanceOfRain);
            int N = 0,D = 0;
            for (int j = 1; j <= 16; j += 4) {
                cJSON *ite = cJSON_GetArrayItem(hour, j);
                if (ite != NULL) {
                    cJSON *t = cJSON_GetObjectItemCaseSensitive(ite, "time");
                    cJSON *tc = cJSON_GetObjectItemCaseSensitive(ite, "temp_c");
                    cJSON *is_day = cJSON_GetObjectItemCaseSensitive(ite, "is_day");
                    cJSON *c1 = cJSON_GetObjectItemCaseSensitive(ite, "condition");
                    cJSON *t1 = cJSON_GetObjectItemCaseSensitive(c1, "text");
                    cJSON *wk = cJSON_GetObjectItemCaseSensitive(ite, "wind_kph");
                    cJSON *hm = cJSON_GetObjectItemCaseSensitive(ite, "humidity");
                    cJSON *heat_index = cJSON_GetObjectItemCaseSensitive(ite, "heatindex_c");
                    cJSON *cr = cJSON_GetObjectItemCaseSensitive(ite, "chance_of_snow");
                    cJSON *ul_v = cJSON_GetObjectItemCaseSensitive(ite, "uv");

                    printf("day: %d is_day:%d\n",i+1, is_day->valueint);
                    if (is_day->valueint == 0)
                    {
                        Days_Forecast *p = d[i-1].Night;
                        strncpy(p[N].time, t->valuestring, sizeof(p[N].time) - 1);
                        p[N].time[ sizeof(p[N].time) - 1] = '\0';  
                        strncpy(p[N].condition, t1->valuestring, sizeof(p[N].condition) - 1);
                        p[N].condition[ sizeof(p[N].condition) - 1] = '\0';  
                        p[N].temp_C = tc->valuedouble;
                        p[N].is_day = is_day->valueint;
                        //printf("%f\n", p[N].temp_C);
                        p[N].windKph = wk->valuedouble;
                        p[N].humidity = hm->valuedouble;
                        p[N].heatIndex_C = heat_index->valuedouble;
                        p[N].chance_of_rain = cr->valuedouble;
                        p[N].UV = ul_v->valuedouble;
                        N++;
                    } else if (is_day->valueint == 1)
                    {
                       // printf("ENTER");
                        Days_Forecast *P = d[i-1].Day;
                        strncpy(P[D].time, t->valuestring, sizeof(P[D].time) - 1);
                        P[D].time[ sizeof(P[N].time) - 1] = '\0'; 
                        //printf("%s\n", P[N].time); 
                        strncpy(P[D].condition, t1->valuestring, sizeof(P[D].condition) - 1);
                        P[D].condition[ sizeof(P[D].condition) - 1] = '\0';  
                        P[D].temp_C = tc->valuedouble;
                        P[D].is_day = is_day->valueint;
                        //printf("%d\n", P[N].is_day); 
                        P[D].windKph = wk->valuedouble;
                        P[D].humidity = hm->valuedouble;
                        P[D].heatIndex_C = heat_index->valuedouble;
                        P[D].chance_of_rain = cr->valuedouble;
                        P[D].UV = ul_v->valuedouble;
                        D++;

                    }
                } 
            }
            free(buffer);
        }
    }



    
    return d;
    
}

void Read()
{
    
   Days* d = parseJSON();
    //display(d);
    writeTxt(d);
    Analyze(d);
    
    free(d);
}