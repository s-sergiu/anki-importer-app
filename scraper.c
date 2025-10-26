
#include "anki-importer-app.h"
#include <curl/curl.h>

int scraper_function(void)
{
	CURLcode	res;
	char		*url = "https://www.verbformen.de/deklination/substantive/Abend.htm";
	CURL		*curl;

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url);
	res = curl_easy_perform(curl);
	if (CURLE_OK == res)
		printf("all good\n");
	(void)res;

	curl_easy_cleanup(curl);

	return(0);
}
