//
// Created by mtoia on 26/12/24.
//

#include "../include/ft_ls.h"

int need_extra_nline(int i, int argc) {
    return i < argc - 1;
}

char** sort_path_list(int argc, int index, char **argv) {
    char **path = (char **)malloc(sizeof(char *) * argc);
    if (!path) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < argc; i++) {
        path[i] = argv[i];
    }
    if (op.reverse) {
        ft_sort(&path[index], argc - index, sizeof(char *), compare_reverse);
        return path;
    }
    ft_sort(path, argc, sizeof(char *), compare_normal);
    return path;
}