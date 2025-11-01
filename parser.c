
#include "anki-importer-app.h"

// optional function;
// saves memory chunks to a file;
void save_to_file(void *memory)
{
	int		fd;

	fd = open("data.html", O_CREAT | O_APPEND | O_WRONLY, 0600);
	write(fd, (char *)memory, strlen((char *)memory));
	close(fd);
}

// returns value of the entire request in bytes;
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

// copies each chunk of memory from the list to a contiguous block of mem;
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

// allocate one contiguos block of memory total size of chunks;
// copy from linked list to one single block of memory
// output structure to a file - data.html
int parse_data(t_data *transfer_data)
{
	char		*placeholder;

	placeholder = malloc(sizeof(char) * get_total_chunks(transfer_data));
	str_chunk_copy(transfer_data, placeholder);
	printf("Iterated over: %d nodes to save the file.\n",
			t_data_iter(transfer_data, save_to_file));
	printf("Iterated over: %d nodes to clear the struct of memory.\n",
			t_data_clear(&transfer_data, free));

	return(0);
}
