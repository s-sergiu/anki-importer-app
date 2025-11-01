
#include "anki-importer-app.h"

static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	char	*data;
	t_data	*node;

	data = (char *)malloc(sizeof(char) * nmemb + size);
	memset(data, 0, nmemb + size);
	memcpy(data, ptr, nmemb);
	node = t_data_new(data);
	t_data_addback((t_data **)userdata, node);
	node->chunk = nmemb * size;

	return (size * nmemb);
}

void	set_options(CURL *handle, t_data **data, char *word)
{
	CURLcode	res;
	char		url[100] ="https://www.verbformen.de/?w=";

	strncat(url, word, strlen(word));
	res = curl_easy_setopt(handle, CURLOPT_URL, url);
	if(res != CURLE_OK)
		fprintf(stderr, "Failed: [%d]\n", res);
	res = curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_callback);
	if(res != CURLE_OK)
		fprintf(stderr, "Failed: [%d]\n", res);
	res = curl_easy_setopt(handle, CURLOPT_WRITEDATA, data);
	if(res != CURLE_OK)
		fprintf(stderr, "Failed: [%d]\n", res);
}

t_data	*fetch_http(char *search_var)
{
	t_curl_data	curl_data;
	t_data		*transfer_data;

	memset(&transfer_data, 0, sizeof(transfer_data));
	curl_data.handle = curl_easy_init();
	set_options(curl_data.handle, &transfer_data, search_var);
	curl_easy_perform(curl_data.handle);
	curl_easy_cleanup(curl_data.handle);

	return (transfer_data);
}

