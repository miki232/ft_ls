//
// Created by mtoia on 01/01/25.
//

#include "../include/ft_ls.h"

int compare_reverse(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    return ft_strcasecmp(str2, str1);
}

int compare_normal(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    return ft_strcasecmp(str1, str2);
}

int compare_time(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    struct stat sb1;
    struct stat sb2;
    char *tmp1 = ft_strjoin(op.path, "/");
    char *path1 = ft_strjoin(tmp1, str1);
    free(tmp1);
    if (lstat(path1, &sb1) == -1) {
        perror("lstat");
        return 0;
    }
    free(path1);
    char *tmp2 = ft_strjoin(op.path, "/");
    char *path2 = ft_strjoin(tmp2, str2);
    free(tmp2);
    if (lstat(path2, &sb2) == -1) {
        perror("lstat");
        return 0;
    }
    free(path2);
    return sb2.st_mtime - sb1.st_mtime;
}

int compare_time_reverse(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    struct stat sb1;
    struct stat sb2;
    char *tmp1 = ft_strjoin(op.path, "/");
    char *path1 = ft_strjoin(tmp1, str1);
    free(tmp1);
    if (lstat(path1, &sb1) == -1) {
        perror("lstat");
        return 0;
    }
    free(path1);
    char *tmp2 = ft_strjoin(op.path, "/");
    char *path2 = ft_strjoin(tmp2, str2);
    free(tmp2);
    if (lstat(path2, &sb2) == -1) {
        perror("lstat");
        return 0;
    }
    free(path2);
    return sb1.st_mtime - sb2.st_mtime;
}

char **sort_array(char **arr) {
    int i = op.flag;
    if (op.flag & OPT_SORT_TIME) {
        ft_sort(arr, array_length(arr), sizeof(char *), compare_time);
    }else {
        ft_sort(arr, array_length(arr), sizeof(char *), compare_normal);
    }
    if (op.flag & OPT_REVERSE && op.flag & OPT_SORT_TIME) {
        ft_sort(arr, array_length(arr), sizeof(char *), compare_time_reverse);
    } else
    if (op.flag & OPT_REVERSE) {
        ft_sort(arr, array_length(arr), sizeof(char *), compare_reverse);
    }
    return arr;
}


/*char** sort_path_list(int argc, int index, char **argv) {
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
}*/

char** sort_path_list(int argc, int index, char **argv) {
    char **path = (char **)malloc(sizeof(char *) * argc);
    int valid_count = 0;
    int invalid_count = 0;

    if (!path) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Create two temporary arrays for valid and invalid paths
    char **valid_paths = (char **)malloc(sizeof(char *) * argc);
    char **invalid_paths = (char **)malloc(sizeof(char *) * argc);

    if (!valid_paths || !invalid_paths) {
        free(path);
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Separate valid and invalid paths
    for (int i = index; i < argc; i++) {
        struct stat sb;
        if (stat(argv[i], &sb) == 0 && S_ISDIR(sb.st_mode)) {
            valid_paths[valid_count++] = argv[i];
        } else {
            invalid_paths[invalid_count++] = argv[i];
        }
    }

    // Sort invalid paths first
    if (op.reverse) {
        ft_sort(invalid_paths, invalid_count, sizeof(char *), compare_reverse);
        ft_sort(valid_paths, valid_count, sizeof(char *), compare_reverse);
    } else {
        ft_sort(invalid_paths, invalid_count, sizeof(char *), compare_normal);
        ft_sort(valid_paths, valid_count, sizeof(char *), compare_normal);
    }

    // Combine the results
    int pos = index;
    for (int i = 0; i < invalid_count; i++) {
        path[pos++] = invalid_paths[i];
    }
    for (int i = 0; i < valid_count; i++) {
        path[pos++] = valid_paths[i];
    }

    // Copy the non-path arguments
    for (int i = 0; i < index; i++) {
        path[i] = argv[i];
    }

    free(valid_paths);
    free(invalid_paths);
    return path;
}
