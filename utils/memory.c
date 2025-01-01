//
// Created by mtoia on 01/01/25.
//

#include "../include/ft_ls.h"

char **copy_to_temp(char **to_expand) {
    size_t len = array_length(to_expand);
    char **temp = (char **)malloc((len + 1) * sizeof(char *));
    if (temp == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < len; i++) {
        temp[i] = strdup(to_expand[i]);
        if (temp[i] == NULL) {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
    }
    temp[len] = NULL;
    return temp;
}