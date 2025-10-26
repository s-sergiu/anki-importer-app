
#include "anki-importer-app.h"
#include <curl/curl.h>

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	int	test;
	(void)userdata;
	(void)size;
	(void)nmemb;
	test = open("test.txt", O_CREAT | O_RDWR);
	write(test, ptr, nmemb);
	return (1);
}

int scraper_function(void)
{
	CURLcode	res;
	char		*url = "https://www.verbformen.de/deklination/substantive/Abend.htm";
	CURL		*curl;

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	res = curl_easy_perform(curl);
	if (CURLE_OK == res)
		printf("all good\n");
	(void)res;

	curl_easy_cleanup(curl);

	return(0);
}
