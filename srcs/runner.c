// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   runner.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mtoia <mtoia@student.42roma.it>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/08/16 17:26:13 by mtoia             #+#    #+#             */
// /*   Updated: 2024/08/20 09:36:44 by mtoia            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */
//
#include "../include/ft_ls.h"

int compare(char *content1, char *content2) {
	int i = 0;
	int j = 0;
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

int ft_long_format(char *src) {
    struct stat sb;
    struct passwd *pw;
    struct group *gr;
    char link_target[1024];
    ssize_t link_len;
    char *tmp = ft_strjoin(op.path, "/");
    char *path = ft_strjoin(tmp, src);
    free(tmp);
    if (lstat(path, &sb) == -1) {
        perror("lstat");
        return 0;
    }
    if (S_ISLNK(sb.st_mode)) {
        link_len = readlink(path, link_target, sizeof(link_target));
        if (link_len == -1) {
            perror("readlink");
            return 0;
        }
        link_target[link_len] = '\0';
    }
    free(path);
    ft_printf("%s", (S_ISDIR(sb.st_mode)) ? "d" : (S_ISLNK(sb.st_mode)) ? "l" : "-");
    ft_printf("%s", (sb.st_mode & S_IRUSR) ? "r" : "-");
    ft_printf("%s", (sb.st_mode & S_IWUSR) ? "w" : "-");
    ft_printf("%s", (sb.st_mode & S_IXUSR) ? "x" : "-");
    ft_printf("%s", (sb.st_mode & S_IRGRP) ? "r" : "-");
    ft_printf("%s", (sb.st_mode & S_IWGRP) ? "w" : "-");
    ft_printf("%s", (sb.st_mode & S_IXGRP) ? "x" : "-");
    ft_printf("%s", (sb.st_mode & S_IROTH) ? "r" : "-");
    ft_printf("%s", (sb.st_mode & S_IWOTH) ? "w" : "-");
    ft_printf("%s", (sb.st_mode & S_IXOTH) ? "x" : "-");

    ft_printf(" %d", sb.st_nlink);

    pw = getpwuid(sb.st_uid);
    gr = getgrgid(sb.st_gid);
    ft_printf(" %s %s", pw->pw_name, gr->gr_name);
    int space = op.size_width - ft_space_cnt((int)sb.st_size);
    if ((int)sb.st_size == 0) {
        space--;
    }
    for (int i = 0; i <= space; i++) {
        ft_printf(" ");
    }
    ft_printf("%d", (int)sb.st_size);

    char *time_str = ctime(&sb.st_mtime);
    time_str[strlen(time_str) - 1] = '\0';
    char *month = ft_substr(time_str, 4, 3);
    char *day = ft_substr(time_str, 8, 2);
    char *hour = ft_substr(time_str, 11, 2);
    char *minute = ft_substr(time_str, 14, 2);
    ft_printf(" %s %s %s:%s", month, day, hour, minute);
    char *color = (S_ISDIR(sb.st_mode)) ? "\033[1;34m" : (S_ISLNK(sb.st_mode)) ? "\033[1;36m" : "";
    ft_printf(" %s", src);
    if (S_ISLNK(sb.st_mode))
        ft_printf(" -> %s", link_target);
    free(month);
    free(day);
    free(hour);
    free(minute);

    return 1;
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

size_t array_length(char **arr) {
    size_t len = 0;
    while (arr && arr[len]) {
        len++;
    }
    return len;
}

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

void error_handler(char *path, char *error) {
    char *tmp = strerror(errno);
    if (strcmp(tmp, "Permission denied") == 0) {
        ft_printf("ft_ls: cannot open directory %s: %s", path, tmp);
        return ;
    }
    ft_printf("ft_ls: cannot access '%s': %s", path, tmp);
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

char **print_list(char **arr, char **to_expand) {
    int i = 0;
    char *content_copy = NULL;
    calculate_size_long_format(arr);
    if (op.flag & OPT_LONG_FORMAT) {
        ft_printf("total %d", calculate_total_blocks(op.path));
    }
    while (arr[i]) {
        if (op.flag & OPT_SHOW_ALL)
        {
            if (op.flag & OPT_LONG_FORMAT)
            {
                ft_printf("\n");
                ft_long_format(arr[i]);
            }
            else
            {
                if (op.raw == 1)
                    ft_printf("%s%s", arr[i], (arr[i + 1]) ? "  " : "");
                else
                    ft_printf("%s%s", arr[i], (arr[i + 1]) ? "\n" : "");
            }
        }
        else if (compare(arr[i], ".") == 0)
        {
            if (op.flag & OPT_LONG_FORMAT) {
                ft_printf("\n");
                ft_long_format(arr[i]);
            }
            else
            {
                if (op.raw == 1)
                    ft_printf("%s%s", arr[i], (arr[i + 1]) ? "  " : "");
                else
                    ft_printf("%s%s", arr[i], (arr[i + 1]) ? "\n" : "");
            }
        }
        if (strcmp(arr[i], ".") != 0 && strcmp(arr[i], "..") != 0)
        {
            if (op.flag & OPT_RECURSIVE && (content_copy = is_dir(arr[i])) != NULL)
            {
                char **temp = copy_to_temp(to_expand);
                ft_matrixfree(&to_expand);
                to_expand = ft_matrixextend(temp, content_copy);
                free(content_copy);
            }
        }
        i++;
    }
    if (op.flag)
        ft_printf("\n");
    return to_expand;
}

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

int run(int mlt, char *tmp, int argc) {
    struct dirent *s_entry;
    char **arr = NULL;
    op.path = tmp;
    char **to_expand = NULL;
    if (mlt >= 1) {
        if (mlt >= 2 && !op.flag) {
            ft_printf("\n%s:\n", tmp);
        }
        else if (argc >= 2) {
            ft_printf("%s:\n", tmp);
        }
        else if (op.flag & OPT_RECURSIVE)
            ft_printf("%s:\n", tmp);

    }
    else if (op.flag & OPT_RECURSIVE) {
        ft_printf("%s:\n", tmp);
    }
    DIR *dir = opendir(tmp);
    if (!dir) {
        error_handler(tmp, "open directory");
        return 1;
    }
    int count = 0;
    while ((s_entry = readdir(dir)) != NULL) {
        if (!(op.flag & OPT_SHOW_ALL) && compare(s_entry->d_name, ".") != 0) {
            continue;
        }
        count++;
    }
    arr = (char **)malloc(sizeof(char *) * (count + 1));
    if (!arr) {
        perror("malloc");
        closedir(dir);
        return 1;
    }
    count = 0;
    closedir(dir);
    DIR *dir2 = opendir(tmp);
    while ((s_entry = readdir(dir2)) != NULL) {
        if (!(op.flag & OPT_SHOW_ALL) && compare(s_entry->d_name, ".") != 0) {
            continue;
        }
        arr[count++] = ft_strdup(s_entry->d_name);
    }
    arr[count] = NULL;
    arr = sort_array(arr);
    to_expand = print_list(arr, to_expand);
    closedir(dir2);
    for (int i = 0; arr[i] != NULL; i++) {
        free(arr[i]);
    }
    free(arr);
    if (to_expand != NULL && op.flag & OPT_RECURSIVE) {
        for (int i = 0; to_expand[i] != NULL; i++) {
            ft_printf("\n");
            run(1, to_expand[i], 0);
        }
    }
    ft_matrixfree(&to_expand);
    return 0;
}