#include <stdio.h>
#include <curl/curl.h>
#include "../headers/cJSON.h"


size_t write_callback(void* contents, size_t size, size_t nmemb, FILE* file) {
    size_t written = fwrite(contents, size, nmemb, file);
    return written;
}

int rtIp() {
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();

    if (curl) {
        // Buffer to store the response
        char response_buffer[4096] = "";
        FILE *fp = fopen("ip.json", "w");

        curl_easy_setopt(curl, CURLOPT_URL, "https://ipinfo.io/json");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response_buffer);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

        // Set the write callback function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        // Pass the file pointer to the callback function
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        // Perform the HTTP request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return 0;
}

int ret(cJSON *loc, char *d, char No) {
    //Making Api For Real Time Details Of Weather
    char path[20] = "response";
    char NoStr[2] = {No, '\0'};  // Convert char to string
    strcat(path, NoStr);
    strcat(path, ".json");
    cJSON *l = loc; // langitude and latitude
    const char* AND = "&dt="; // On Date
    char api[1000]; // To merge with apipre
    const char *apipre = "https://weatherapi-com.p.rapidapi.com/forecast.json?q=";

    strcpy(api, apipre); // Initialize the array with the prefix
    strcat(api, l->valuestring); //concat api with location
    strcat(api, AND);
    strcat(api, d);//concat api with date
    CURL *hnd = curl_easy_init();

    if (!hnd) {
        fprintf(stderr, "Error initializing libcurl\n");
        return 1;
    }

    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(hnd, CURLOPT_URL, api);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "X-RapidAPI-Key: dcd065dca6mshe67c6396d12f665p138055jsn532617cef63a");
    headers = curl_slist_append(headers, "X-RapidAPI-Host: weatherapi-com.p.rapidapi.com");
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYPEER, 0L);

    FILE *fp = fopen(path, "w");
    if (!fp) {
        fprintf(stderr, "Error opening file for writing\n");
        curl_easy_cleanup(hnd);
        return 1;
    }

    curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, fp);

    CURLcode curl_ret = curl_easy_perform(hnd);

    fclose(fp);
    if (curl_ret != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(curl_ret));
    }
    curl_easy_cleanup(hnd);
    curl_slist_free_all(headers);
    return 0;
}

// int ret() {
//     CURL* hnd = curl_easy_init();
//     if (!hnd) {
//         fprintf(stderr, "Error initializing libcurl.\n");
//         return 1;  // Exit with an error code
//     }

//     FILE* json_file = fopen("response.json", "w");
//     if (!json_file) {
//         fprintf(stderr, "Error opening the file for writing.\n");
//         curl_easy_cleanup(hnd);
//         return 1;  // Exit with an error code
//     }

//     curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
//     curl_easy_setopt(hnd, CURLOPT_URL, "https://weatherapi-com.p.rapidapi.com/current.json?q=Karachi&");
//     curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYPEER, 0);

//     struct curl_slist* headers = NULL;
//     headers = curl_slist_append(headers, "X-RapidAPI-Key: dcd065dca6mshe67c6396d12f665p138055jsn532617cef63a");
// 	headers = curl_slist_append(headers, "X-RapidAPI-Host: weatherapi-com.p.rapidapi.com");
//     curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

//     // Set the write callback function
//     curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, write_callback);
//     // Pass the file pointer to the callback function
//     curl_easy_setopt(hnd, CURLOPT_WRITEDATA, json_file);

//     CURLcode ret = curl_easy_perform(hnd);
//     if (ret != CURLE_OK) {
//         fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(ret));
//         curl_easy_cleanup(hnd);
//         fclose(json_file);
//         return 1;  // Exit with an error code
//     }

//     // Clean up and close the file
//     fclose(json_file);
//     curl_easy_cleanup(hnd);
//     curl_slist_free_all(headers);

//     return 0;
// }

