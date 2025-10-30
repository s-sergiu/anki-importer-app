
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

void save_to_file(void *memory)
{
	int		fd;

	fd = open("data.html", O_CREAT | O_APPEND | O_WRONLY, 0600);
	write(fd, (char *)memory, strlen((char *)memory));
	close(fd);
}

void	set_options(CURL *handle, t_data **data, char *word)
{
	CURLcode	res;
	static char	errorBuffer[CURL_ERROR_SIZE];
	char		url[100] ="https://www.verbformen.de/?w=";

	strncat(url, word, strlen(word));
	res = curl_easy_setopt(handle, CURLOPT_ERRORBUFFER, errorBuffer);
	if(res != CURLE_OK)
		fprintf(stderr, "Failed: [%d]\n", res);
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

int scraper_function(char *word)
{
	CURL		*curl;
	t_data		*data;
	char		*placeholder;

	memset(&data, 0, sizeof(data));
	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	set_options(curl, &data, word);
	curl_easy_perform(curl);

	// calculate the sum of the chunks;
	t_data *curr;
	int sum;
	curr = data;
	sum = 0;
	while (curr)
	{
		sum += curr->chunk;
		curr=curr->next;
	}
	// allocate one contiguos block of memory total size of chunks;
	placeholder = malloc(sizeof(char) * sum);
	curr = data;
	int index = 0;
	// copy each chunk into the block;
	while (curr)
	{
		strncat(placeholder + index, curr->memory, curr->chunk);
		curr=curr->next;
		if (curr)
			index += curr->chunk;
	}

	// output structure to a file - data.html
	printf("Iterated over: %d nodes to save the file.\n",
			t_data_iter(data, save_to_file));
	printf("Iterated over: %d nodes to clear the struct of memory.\n",
			t_data_clear(&data, free));

	curl_easy_cleanup(curl);
	//printf("%s", placeholder);

	return(0);
}
