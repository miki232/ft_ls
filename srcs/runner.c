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

int ft_detail_symlink(char *src) {
    struct stat sb;
    struct passwd *pw;
    struct group *gr;
    char link_target[1024];
    ssize_t link_len;
    if (lstat(src, &sb) == -1) {
        perror("lstat");
        return 0;
    }
    if (S_ISLNK(sb.st_mode)) {
        link_len = readlink(src, link_target, sizeof(link_target));
        if (link_len == -1) {
            perror("readlink");
            return 0;
        }
        link_target[link_len] = '\0';
    };
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
    if (op.raw == 1) {
        ft_printf(" %s%s%s", ft_get_color(src, &sb), src, RESET);
    }
    else {
        ft_printf(" %s", src);
    }
    if (S_ISLNK(sb.st_mode))
        ft_printf(" -> %s\n", link_target);
    free(month);
    free(day);
    free(hour);
    free(minute);

    return 1;
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
    if (op.raw == 1) {
        ft_printf(" %s%s%s", ft_get_color(src, &sb), src, RESET);
    }
    else {
        ft_printf(" %s", src);
    }
    if (S_ISLNK(sb.st_mode))
        ft_printf(" -> %s", link_target);
    free(month);
    free(day);
    free(hour);
    free(minute);

    return 1;
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
                    ft_printf("%s%s%s%s", ft_get_color(arr[i], NULL), arr[i], (arr[i + 1]) ? "  " : "", RESET);
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
                    ft_printf("%s%s%s%s", ft_get_color(arr[i], NULL), arr[i], (arr[i + 1]) ? "  " : "", RESET);
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

int run(int mlt, char *tmp, int argc) {
    struct dirent *s_entry;
    char **arr = NULL;
    op.path = tmp;
    char **to_expand = NULL;
    DIR *dir = opendir(tmp);
    if (!dir) {
        if (is_file(tmp)) {
            ft_printf("%s%s%s", ft_get_color(tmp, NULL), tmp, RESET);
            return 0;
        }
        error_handler(tmp, "open directory");
        return 1;
    }
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
    if (op.flag & OPT_LONG_FORMAT) {
        struct stat sb;
        if (lstat(tmp, &sb) == -1) {
            perror("lstat");
            return 0;
        }
        if (S_ISLNK(sb.st_mode)) {
            ft_detail_symlink(tmp);
            return 1;
        }
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