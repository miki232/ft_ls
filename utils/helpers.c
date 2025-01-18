//
// Created by mtoia on 26/12/24.
//

#include "../include/ft_ls.h"

int need_extra_nline(int i, int argc) {
    return i < argc - 1;
}

size_t array_length(char **arr) {
    size_t len = 0;
    while (arr && arr[len]) {
        len++;
    }
    return len;
}

int compare(const char* content1, const char* content2) {
    int i = 0;
    while (content1[i] != '\0' && content2[i] != '\0') {
        if (content1[i] != content2[i])
        {
            i++;
            continue;
        }
        return 1;
    }
    return 0;
}

int ft_space_cnt(int n) {
    int count = 0;
    while (n > 0) {
        n /= 10;
        count++;
    }
    return count;
}

int calculate_total_blocks(char *dir_path) {
    DIR *dir;
    struct dirent *entry;
    struct stat sb;
    long total = 0;
    char *path;

    dir = opendir(dir_path);
    if (dir == NULL)
    {
        perror("opendir");
        return -1;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] == '.' && !op.show_all)
            continue;

        path = ft_strjoin(dir_path, "/");
        char *full_path = ft_strjoin(path, entry->d_name);
        free(path);

        if (lstat(full_path, &sb) == 0) {
            total += sb.st_blocks;
        }
        free(full_path);
    }

    closedir(dir);
    return total / 2;  // Divide by 2 to match ls output (512-byte blocks to 1024-byte blocks)
}

int is_archive(const char *filename) {
    const char *ext = strrchr(filename, '.');
    if (ext != NULL) {
        return (strcmp(ext, ".zip") == 0 ||
                strcmp(ext, ".tar") == 0 ||
                strcmp(ext, ".gz") == 0 ||
                strcmp(ext, ".bz2") == 0 ||
                strcmp(ext, ".rar") == 0 ||
                strcmp(ext, ".7z") == 0 ||
                strcmp(ext, ".tgz") == 0);
    }
    return 0;
}

char *path_maker(char *basepath, char *filename) {
    char *path;
    if ((basepath[strlen(basepath) - 1] == '/' || basepath[strlen(basepath) - 1] == '.') && filename[0] == '/') {
        if (ft_strlen(filename) > 1) {
            path = ft_strjoin(basepath, filename + 1);
        } else {
            path = ft_strdup(basepath);
        }
    }
    else if (basepath[strlen(basepath) - 1] == '/') {
        path = ft_strjoin(basepath, filename);
    } else {
        if (filename[0] == '/') {
            path = ft_strjoin(basepath, filename);
        } else
        {
            char *tmp = ft_strjoin(basepath, "/");
            path = ft_strjoin(tmp, filename);
            free(tmp);
        }
    }
    return path;
}

char *is_dir(char *path) {
    struct stat path_stat;

    char *tmp1 = path_maker(op.path, "/");
    if (!tmp1) {
        perror("ft_strjoin");
        return NULL;
    }
    char *tmp = path_maker(tmp1, path);
    free(tmp1);
    if (!tmp) {
        perror("ft_strjoin");
        return NULL;
    }
    if (lstat(tmp, &path_stat) == -1) {
        free(tmp);
        return NULL;
    }
    if (S_ISLNK(path_stat.st_mode)) {
        free(tmp);
        return NULL;
    }
    if (S_ISDIR(path_stat.st_mode)) {
        return tmp;
    }
    free(tmp);
    return NULL;
}

int is_file(const char *src) {
    struct stat sb;

    if (stat(src, &sb) == 0 && S_ISREG(sb.st_mode)) {
        return 1;
    } else {
        return 0;
    }
}

void calculate_size_long_format(char **arr) {
    int i = 0;
    int max = 0;
    while (arr[i]) {
        struct stat sb;
        struct passwd *pw;
        struct group *gr;
        char link_target[1024];
        ssize_t link_len;
        char *tmp = ft_strjoin(op.path, "/");
        char *path = ft_strjoin(tmp, arr[i]);
        free(tmp);
        if (lstat(path, &sb) == -1) {
            error_handler(path, NULL);
            ft_printf("\n");
            free(path);
            return ;
        }
        free(path);

        int temp = sb.st_size;
        int max_temp = 0;
        while (temp > 0) {
            temp /= 10;
            max_temp++;
        }
        if (max_temp > max) {
            max = max_temp;
        }
        i++;
    }
    op.size_width = max;
}


char **rearrange_argv(int *argc, char **argv) {
    char **new_argv = (char **)malloc((*argc + 1) * sizeof(char *));
    if (!new_argv) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    int new_argc = 0;
    int i, j;
    char flags[256] = {0};

    // Copy the program name
    new_argv[new_argc++] = strdup(argv[0]);

    // Collect all flags
    for (i = 1; i < *argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] != '\0') {
            for (j = 1; argv[i][j] != '\0'; j++) {
                if (!strchr(flags, argv[i][j])) {
                    strncat(flags, &argv[i][j], 1);
                }
            }
        }
    }

    // Add collected flags as a single argument
    if (flags[0] != '\0') {
        char *flag_arg = (char *)malloc((strlen(flags) + 2) * sizeof(char));
        if (!flag_arg) {
            // Clean up before exit
            for (i = 0; i < new_argc; i++) {
                free(new_argv[i]);
            }
            free(new_argv);
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        flag_arg[0] = '-';
        strcpy(flag_arg + 1, flags);
        new_argv[new_argc++] = flag_arg;
    }

    // Add non-flag arguments
    for (i = 1; i < *argc; i++) {
        if (!(argv[i][0] == '-' && argv[i][1] != '\0')) {
            new_argv[new_argc++] = strdup(argv[i]);
        }
    }

    *argc = new_argc;
    new_argv[new_argc] = NULL;

    // Remove the lines that free argv
    // DO NOT free the original argv

    return new_argv;
}