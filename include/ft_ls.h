/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42roma.it>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:31:09 by mtoia             #+#    #+#             */
/*   Updated: 2024/08/19 17:59:07 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include "../libft/libft.h"
#include "option.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>

#define OPT_LONG_FORMAT  0b00001
#define OPT_RECURSIVE    0b00010
#define OPT_SHOW_ALL     0b00100
#define OPT_REVERSE      0b01000
#define OPT_SORT_TIME    0b10000

//Color codes
#define RESET   "\033[0m"

int need_extra_nline(int i, int argc);
int compare_normal(const void *a, const void *b);
int compare_reverse(const void *a, const void *b);
char** sort_path_list(int argc, int index, char **argv);
int compare(const char* content1, const char* content2);
int ft_space_cnt(int n);
int calculate_total_blocks(char *dir_path);
int is_archive(const char *filename);
char *path_maker(char *basepath, char *filename);
char *is_dir(char *path);
char **copy_to_temp(char **to_expand);
size_t array_length(char **arr);
void error_handler(char *path, char *error);
void calculate_size_long_format(char **arr);
char **sort_array(char **arr);
int compare_time(const void *a, const void *b);
int compare_time_reverse(const void *a, const void *b);
int compare_normal(const void *a, const void *b);
int compare_reverse(const void *a, const void *b);
char *ft_get_color(const char *src, struct stat *sb_ptr);
char **rearrange_argv(int *argc, char **argv);
int is_file(const char *src);

//Debug functions
void print_5_bits(int num);
#endif