//
// Created by mtoia on 01/01/25.
//
#include "../include/ft_ls.h"

void error_handler(char *path, char *error) {
    char *tmp = strerror(errno);
    if (strcmp(tmp, "Permission denied") == 0) {
        ft_printf("ft_ls: cannot open directory %s: %s", path, tmp);
        return ;
    }
    ft_printf("ft_ls: cannot access '%s': %s", path, tmp);
}