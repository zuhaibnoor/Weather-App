#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <curl/curl.h>

int main () {
	CURL *hnd = curl_easy_init();

	curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
	curl_easy_setopt(hnd, CURLOPT_URL, "https://weatherapi-com.p.rapidapi.com/current.json?q=53.1%2C-0.13");

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "X-RapidAPI-Key: dcd065dca6mshe67c6396d12f665p138055jsn532617cef63a");
	headers = curl_slist_append(headers, "X-RapidAPI-Host: weatherapi-com.p.rapidapi.com");
	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYPEER, 0);


	CURLcode ret = curl_easy_perform(hnd);



printf("\n\nTest succesful!, Press any key to Continue.");
getch();

}
