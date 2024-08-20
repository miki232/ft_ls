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
//
// //make a function that check if a file is a directory
// char *is_dir(char *path)
// {
//     struct stat path_stat;
//     char *tmp1 = ft_strjoin(op.path, "/");
//     //char *tmp = ft_strjoin(tmp1, path);
// 	strcat(tmp1, path);
//     //free(tmp1); // Free intermediate string
//     stat(tmp1, &path_stat);
//     //free(tmp); // Free concatenated string
// 	if (S_ISDIR(path_stat.st_mode))
// 		return tmp1;
// 	free(tmp1);
//     return NULL;
// }
//
// void add_to_expand(char **to_expand, char *path) {
// 	if (to_expand== NULL) {
// 		to_expand = (char **)malloc(sizeof(char *) * 2);
// 		to_expand[1] = NULL;
// 	}
// 	to_expand = ft_matrixextend(to_expand, path);
// }
//
// size_t array_length(char **arr) {
// 	size_t len = 0;
// 	while (arr && arr[len]) {
// 		len++;
// 	}
// 	return len;
// }
//
// // Function to copy `to_expand` to a temporary array
// char **copy_to_temp(char **to_expand) {
// 	// Determine the size of the `to_expand` array
// 	size_t len = array_length(to_expand);
//
// 	// Allocate memory for the temporary array
// 	char **temp = (char **)malloc((len + 1) * sizeof(char *));
// 	if (temp == NULL) {
// 		perror("malloc");
// 		exit(EXIT_FAILURE);
// 	}
//
// 	// Copy each element from `to_expand` to the temporary array
// 	for (size_t i = 0; i < len; i++) {
// 		temp[i] = strdup(to_expand[i]); // Use strdup to copy strings
// 		if (temp[i] == NULL) {
// 			perror("strdup");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
//
// 	// NULL-terminate the temporary array
// 	temp[len] = NULL;
//
// 	return temp;
// }
//
// char **print_list(char **arr, char **to_expand)
// {
// 	int i = 0;
// 	while (arr[i]) {
// 		if (i == 32) {
// 			ft_putstr("\n");
// 		}
// 		if (strcmp((char *)arr[i] , ".") != 0 && strcmp((char *)arr[i] , "..") != 0)
// 		{
// 			ft_printf("%s  ", arr[i]);
// 			char *content_copy = NULL; // Copy content
// 			if ((content_copy = is_dir(arr[i])))
// 			{
// 				char **temp = copy_to_temp(to_expand);
//
// 				to_expand = ft_matrixextend(temp, content_copy);
// 			}
// 		}
// 		i++;
// 		if (arr[i] == NULL)
// 			return to_expand;
// 		// sleep(1);
// 	}
// }
//
// int layer = 0;
//
// void printss(void *content)
// {
// 	layer++;
// 	ft_printf("\n");
// 	run(1, (char *)content);
// }
//
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
//
// int run(int mlt, char *tmp)
// {
// 	// ft_printf("run %d\n", mlt);
// 	struct dirent *s_entry;
// 	char	**arr = NULL;
// 	op.path = tmp;
// 	char **to_expand = NULL;
// 	printf("path23 %s\n", op.path);
// 	if (mlt >= 1)
// 	{
// 		if (mlt > 2)
// 			ft_printf("\n%s:\n", tmp);
// 		else
// 			ft_printf("%s:\n", tmp);
// 	}
// 	DIR *dir = opendir(tmp);
//     if (!dir) {
//         perror("opendir");
//         return (1);
//     }
// 	int count = 0;
// 	while ((s_entry = readdir(dir)) != NULL){
// 		if (op.flag != OPT_SHOW_ALL && compare(s_entry->d_name, ".") != 0)
// 			continue;
// 		count++;
// 	}
// 	arr = (char **)malloc(sizeof(char *) * (count));
// 	count = 0;
// 	closedir(dir);
// 	DIR *dir2 = opendir(tmp);
// 	while ((s_entry = readdir(dir2)) != NULL) {
// 		if (op.flag != OPT_SHOW_ALL && compare(s_entry->d_name, ".") != 0)
// 			continue;
// 		arr[count++] = ft_strdup(s_entry->d_name);
// 	}
// 	arr[count] = NULL;
// 	to_expand = print_list(arr, to_expand);
// 	closedir(dir2);
//
// 	ft_printf("\n");
// 	if (to_expand != NULL) {
// 		for (int i = 0; to_expand[i] != NULL ; i++) {
// 			run(1, to_expand[i]);
// 		}
// 	}
// 	// if (layer <= 0)
// 	// {
// 	// 	// printf("layer %d\n", layer);
// 	// 	ft_lstiter(op.head, printss);
// 	// }
// 	// layer--;
// 	return (0);
// }
//

char *is_dir(char *path) {
    struct stat path_stat;
    char *tmp1 = ft_strjoin(op.path, "/");
    if (!tmp1) {
        perror("ft_strjoin");
        return NULL;
    }
    char *tmp = ft_strjoin(tmp1, path);
    free(tmp1);
    if (!tmp) {
        perror("ft_strjoin");
        return NULL;
    }
    if (stat(tmp, &path_stat) == -1) {
        perror("stat");
        free(tmp);
        return NULL;
    }
    if (S_ISDIR(path_stat.st_mode)) {
        return tmp;
    }
    free(tmp);
    return NULL;
}

void add_to_expand(char **to_expand, char *path) {
    if (to_expand == NULL) {
        to_expand = (char **)malloc(sizeof(char *) * 2);
        if (!to_expand) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        to_expand[0] = strdup(path);
        to_expand[1] = NULL;
    } else {
        to_expand = ft_matrixextend(to_expand, path);
    }
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

char **print_list(char **arr, char **to_expand) {
    int i = 0;
    while (arr[i]) {
        if (i == 32) {
            ft_putstr("\n");
        }
        if (op.flag & OPT_SHOW_ALL)
            ft_printf("%s  ", arr[i]);
        else if (compare(arr[i], ".") == 0)
            ft_printf("%s  ", arr[i]);
        if (strcmp(arr[i], ".") != 0 && strcmp(arr[i], "..") != 0) {
            char *content_copy = is_dir(arr[i]);
            if (content_copy) {
                char **temp = copy_to_temp(to_expand);
                to_expand = ft_matrixextend(temp, content_copy);
                free(content_copy);
            }
        }
        i++;
    }
    return to_expand;
}

// Comparison function for normal order
// Comparison function for reverse order (case-insensitive)
int compare_reverse(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    return strcasecmp(str2, str1);
}

// Comparison function for normal order (case-insensitive)
int compare_normal(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    return strcasecmp(str1, str2);
}

char **sort_array(char **arr) {
    if (op.flag & OPT_REVERSE) {
        qsort(arr, array_length(arr), sizeof(char *), compare_reverse);
    } else {
        qsort(arr, array_length(arr), sizeof(char *), compare_normal);
    }
    return arr;
}

int run(int mlt, char *tmp) {
    struct dirent *s_entry;
    char **arr = NULL;
    op.path = tmp;
    char **to_expand = NULL;
    if (mlt >= 1) {
        if (mlt > 2) {
            ft_printf("\n%s:\n", tmp);
        } else {
            ft_printf("%s:\n", tmp);
        }
    }
    DIR *dir = opendir(tmp);
    if (!dir) {
        perror("opendir");
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
    ft_printf("\n\n");
    if (to_expand != NULL && op.flag & OPT_RECURSIVE) {
        for (int i = 0; to_expand[i] != NULL; i++) {

            run(1, to_expand[i]);
            free(to_expand[i]);
        }
        free(to_expand);
    }
    return 0;
}