#include <stdio.h>
#include <curl/curl.h>


size_t write_callback(void* contents, size_t size, size_t nmemb, FILE* file) {
    size_t written = fwrite(contents, size, nmemb, file);
    return written;
}

int ret() {
    CURL* hnd = curl_easy_init();
    if (!hnd) {
        fprintf(stderr, "Error initializing libcurl.\n");
        return 1;  // Exit with an error code
    }

    FILE* json_file = fopen("response.json", "w");
    if (!json_file) {
        fprintf(stderr, "Error opening the file for writing.\n");
        curl_easy_cleanup(hnd);
        return 1;  // Exit with an error code
    }

    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(hnd, CURLOPT_URL, "https://weatherapi-com.p.rapidapi.com/current.json?q=Karachi&");
    curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYPEER, 0);

    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "X-RapidAPI-Key: dcd065dca6mshe67c6396d12f665p138055jsn532617cef63a");
	headers = curl_slist_append(headers, "X-RapidAPI-Host: weatherapi-com.p.rapidapi.com");
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

    // Set the write callback function
    curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, write_callback);
    // Pass the file pointer to the callback function
    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, json_file);

    CURLcode ret = curl_easy_perform(hnd);
    if (ret != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(ret));
        curl_easy_cleanup(hnd);
        fclose(json_file);
        return 1;  // Exit with an error code
    }

    // Clean up and close the file
    fclose(json_file);
    curl_easy_cleanup(hnd);
    curl_slist_free_all(headers);

    return 0;
}
