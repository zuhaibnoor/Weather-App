// weather.h
#ifndef WEATHER_H
#define WEATHER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../headers/cJSON.h"
#include <time.h>



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
size_t write_callback(void* contents, size_t size, size_t nmemb, FILE* file);
int ret(cJSON *loc, char *d, char No);
double average(double* arr);
void Analyze(Days* d);
void display(Days* d);
void writeTxt(Days* d);
Days* parseJSON();
void Read();
size_t wrtclb(void *contents, size_t size, size_t nmemb, void *userp);

cJSON* retIp();

void incrementDate(char* date);
char* getDate();

#endif
