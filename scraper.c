
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

int get_total_chunks(t_data *data)
{
	t_data	*curr;
	int		sum;

	sum = 0;
	curr = data;
	while (curr)
	{
		sum += curr->chunk;
		curr=curr->next;
	}

	return (sum);
}

void str_chunk_copy(t_data *data, char *string)
{
	t_data	*curr;
	int		index;

	curr =	data;
	index =	0;
	while (curr)
	{
		strncat(string + index, curr->memory, curr->chunk);
		curr=curr->next;
		if (curr)
			index += curr->chunk;
	}
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

int parse_data(t_data *transfer_data)
{
	char		*placeholder;

	// allocate one contiguos block of memory total size of chunks;
	placeholder = malloc(sizeof(char) * get_total_chunks(transfer_data));
	// copy from linked list to one single block of memory
	str_chunk_copy(transfer_data, placeholder);
	// output structure to a file - data.html
	printf("Iterated over: %d nodes to save the file.\n",
			t_data_iter(transfer_data, save_to_file));
	printf("Iterated over: %d nodes to clear the struct of memory.\n",
			t_data_clear(&transfer_data, free));

	return(0);
}
