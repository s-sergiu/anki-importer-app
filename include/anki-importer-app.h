#ifndef ANKI_IMPORTER_APP_HPP
#define ANKI_IMPORTER_APP_HPP

#include "raylib.h"
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define RAYGUI_IMPLEMENTATION

typedef struct s_data t_data;

struct s_data {
	char	*memory;
	t_data	*next;
};

void	t_data_addfront(t_data**, t_data*);
void	t_data_iter(t_data*, void (*)(void*));
void	t_data_clear(t_data**, void (*)(void*));
t_data	*t_data_new(void*);

void	run_gui(void);
int		scraper_function(char*);

#endif
