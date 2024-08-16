/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42roma.it>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:24:44 by mtoia             #+#    #+#             */
/*   Updated: 2024/08/16 18:12:29 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

// // Helper function to get file information for -l option
// void print_file_info(const char *path, const struct stat *sb) {
//     // File type and permissions
//     printf((S_ISDIR(sb->st_mode)) ? "d" : "-");
//     printf((sb->st_mode & S_IRUSR) ? "r" : "-");
//     printf((sb->st_mode & S_IWUSR) ? "w" : "-");
//     printf((sb->st_mode & S_IXUSR) ? "x" : "-");
//     printf((sb->st_mode & S_IRGRP) ? "r" : "-");
//     printf((sb->st_mode & S_IWGRP) ? "w" : "-");
//     printf((sb->st_mode & S_IXGRP) ? "x" : "-");
//     printf((sb->st_mode & S_IROTH) ? "r" : "-");
//     printf((sb->st_mode & S_IWOTH) ? "w" : "-");
//     printf((sb->st_mode & S_IXOTH) ? "x" : "-");
//     printf(" ");

//     // Number of links
//     printf("%ld ", sb->st_nlink);

//     // Owner and group
//     struct passwd *pw = getpwuid(sb->st_uid);
//     struct group *gr = getgrgid(sb->st_gid);
//     printf("%s %s ", pw->pw_name, gr->gr_name);

//     // Size
//     printf("%ld ", sb->st_size);

//     // Modification time
//     char time_str[20];
//     strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&sb->st_mtime));
//     printf("%s ", time_str);

//     // File name
//     printf("%s\n", path);
// }

// // Helper function to sort files by time
// int compare(const void *a, const void *b) {
//     struct stat sb_a, sb_b;
//     stat(((struct dirent **)a)[0]->d_name, &sb_a);
//     stat(((struct dirent **)b)[0]->d_name, &sb_b);
//     return sb_b.st_mtime - sb_a.st_mtime;
// }

// // Core function to list directories
// void list_directory(const char *dir_name, int show_all, int long_format, int recursive, int sort_time, int reverse) {
//     DIR *dir = opendir(dir_name);
//     if (!dir) {
//         perror("opendir");
//         return;
//     }

//     struct dirent *entry;
//     struct dirent **entries = NULL;
//     int count = 0;

//     // Collect directory entries
//     while ((entry = readdir(dir)) != NULL) {
//         if (!show_all && entry->d_name[0] == '.') {
//             continue; // Skip hidden files if -a is not set
//         }
//         entries = realloc(entries, sizeof(struct dirent *) * (count + 1));
//         entries[count++] = entry;
//     }

//     closedir(dir);

//     // Sort entries if necessary
//     if (sort_time) {
//         qsort(entries, count, sizeof(struct dirent *), compare);
//     }

//     // Reverse entries if necessary
//     if (reverse) {
//         for (int i = 0; i < count / 2; i++) {
//             struct dirent *tmp = entries[i];
//             entries[i] = entries[count - i - 1];
//             entries[count - i - 1] = tmp;
//         }
//     }

//     // Print entries
//     for (int i = 0; i < count; i++) {
//         struct stat sb;
//         char path[1024];
//         snprintf(path, sizeof(path), "%s/%s", dir_name, entries[i]->d_name);
//         stat(path, &sb);

//         if (long_format) {
//             print_file_info(entries[i]->d_name, &sb);
//         } else {
//             printf("%s\n", entries[i]->d_name);
//         }

//         // Recurse into directories if -R is set
//         if (recursive && S_ISDIR(sb.st_mode) && strcmp(entries[i]->d_name, ".") != 0 && strcmp(entries[i]->d_name, "..") != 0) {
//             printf("\n%s:\n", path);
//             list_directory(path, show_all, long_format, recursive, sort_time, reverse);
//         }
//     }

//     free(entries);
// }

// int main(int argc, char *argv[]) {
//     int show_all = 0, long_format = 0, recursive = 0, sort_time = 0, reverse = 0;
//     int opt;

//     // Parse command-line options
//     while ((opt = getopt(argc, argv, "lRart")) != -1) {
//         switch (opt) {
//             case 'l': long_format = 1; break;
//             case 'R': recursive = 1; break;
//             case 'a': show_all = 1; break;
//             case 'r': reverse = 1; break;
//             case 't': sort_time = 1; break;
//             default: exit(EXIT_FAILURE);
//         }
//     }

//     // List directories/files specified in arguments or current directory if none
//     if (optind >= argc) {
//         list_directory(".", show_all, long_format, recursive, sort_time, reverse);
//     } else {
//         for (int i = optind; i < argc; i++) {
//             printf("%s:\n", argv[i]);
//             list_directory(argv[i], show_all, long_format, recursive, sort_time, reverse);
//         }
//     }

//     return 0;
// }


int main(int argc, char **argv)
{
	int opt;

	while ((opt = ft_getopt(argc, argv, "lRart")) != -1)
	{
		switch (opt)
		{
		case 'l':
			op.long_format = 1;
			break;
		case 'R':
			op.recursive = 1;
			break;
		case 'a':
			op.show_all = 1;
			break;
		case 'r':
			op.reverse = 1;
			break;
		case 't':
			op.sort_time = 1;
			break;
		default:
			exit(EXIT_FAILURE);
		}
	}
	//Checker for the path if the path given is a directory or a file and if it exists
	// if not exists it will print an error message
	// printf("%d %d\n", op.my_optind, argc);
	if (op.my_optind >= argc)
	{
		op.path = ".";
	}
	else
	{
		
		for (int i = op.my_optind; i < argc; i++)
		{
			op.path = argv[i];
			run(i);
		}
		return (0);
	}
	printf("Resutl: %d %d %d %d %d\n", op.long_format, op.recursive, op.show_all, op.reverse, op.sort_time);
	run(0);
}