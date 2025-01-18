//
// Created by mtoia on 01/01/25.
//
#include "../include/ft_ls.h"

void error_handler(char *path, char *error) {
    char *nl = "\n";
    char *tmp = strerror(errno);
    if (!op.flag)
        nl = "";
    if (strcmp(tmp, "Permission denied") == 0) {
        ft_printf("ft_ls: cannot open directory %s: %s%s", path, tmp, nl);
        return ;
    }
    ft_printf("ft_ls: cannot access '%s': %s%s", path, tmp, nl);
}