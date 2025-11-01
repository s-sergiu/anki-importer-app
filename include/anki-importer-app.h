#ifndef ANKI_IMPORTER_APP_HPP
#define ANKI_IMPORTER_APP_HPP

#include "raylib.h"
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "raygui.h"

#define RAYGUI_IMPLEMENTATION

typedef struct s_data t_data;
typedef struct s_curl_data t_curl_data;

struct s_curl_data {
	CURL	*handle;
};

struct s_data {
	char	*memory;
	t_data	*next;
	size_t	chunk;
};

void	t_data_addback(t_data**, t_data*);
void	t_data_addfront(t_data**, t_data*);
int		t_data_iter(t_data*, void (*)(void*));
int		t_data_clear(t_data**, void (*)(void*));
t_data	*t_data_new(void*);

void	display_gui(void);
t_data	*fetch_http(char*);
int		parse_data(t_data*);


#endif
