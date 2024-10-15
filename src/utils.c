#include "cub.h"

void ft_error(const char *msg)
{
    ft_printf_fd(2,"Error: %s\n", msg);
    exit(EXIT_FAILURE);
}

void free_all_doc(char ***all_doc)
{
    int i = 0;

    if (!all_doc || !*all_doc)
        return;
    while ((*all_doc)[i])
	{
        free((*all_doc)[i]);
        i++;
    }
    free(*all_doc);
    *all_doc = NULL;
}
