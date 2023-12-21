#include <stdio.h>
#include <curl/curl.h>
#include "../headers/cJSON.h"

size_t wrtclb(void *contents, size_t size, size_t nmemb, void *userp) {
    // This callback function is used to write the response to a buffer
    size_t realsize = size * nmemb;
    char *buffer = (char *)userp;

    strcat(buffer, (char *)contents);

    return realsize;
}

cJSON* retIp() {
    CURL *curl;
    CURLcode res;
    cJSON *json_parse = NULL;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();

    if (curl) {
        // Buffer to store the response
        char response_buffer[4096] = "";

        curl_easy_setopt(curl, CURLOPT_URL, "https://ipinfo.io/json");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, wrtclb);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response_buffer);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

        // Perform the HTTP request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            // Parse the JSON response
            json_parse = cJSON_Parse(response_buffer);

            if (json_parse == NULL) {
                fprintf(stderr, "Error parsing JSON: %s\n", cJSON_GetErrorPtr());
            }
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return json_parse;
}