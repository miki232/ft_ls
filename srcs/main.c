/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42roma.it>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:24:44 by mtoia             #+#    #+#             */
/*   Updated: 2024/08/19 21:17:12 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int main(int argc, char **argv)
 {
 	int opt;
 	op.flag = 0;
 	op.head = NULL;
 	op.raw = isatty(STDOUT_FILENO);
	char **newargv = rearrange_argv(&argc, argv);
 	while ((opt = ft_getopt(argc, newargv, "lRart")) != -1)
 	{
 		switch (opt)
 		{
 		case 'l':
 			op.long_format = 1;
 			op.flag |= OPT_LONG_FORMAT;
 			break;
 		case 'R':
 			op.recursive = 1;
 			op.flag |= OPT_RECURSIVE;
 			break;
 		case 'a':
 			op.show_all = 1;
 			op.flag |= OPT_SHOW_ALL;
 			break;
 		case 'r':
 			op.reverse = 1;
 			op.flag |= OPT_REVERSE;
 			break;
 		case 't':
 			op.sort_time = 1;
 			op.flag |= OPT_SORT_TIME;
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
 		run(0, op.path, 0);
 	}
 	else
 	{
 		char **path = sort_path_list(argc, op.my_optind, newargv);
 		for (int i = op.my_optind; i < argc; i++)
 		{
 			if (path[i] == NULL) {
 				continue;
 			}
 			op.path = path[i];
 			run(i, op.path, argc - op.my_optind);
 			if (need_extra_nline(i, argc))
 				ft_printf("\n");
 		}
 		free(path);
 	}
 	for (int i = 0; i < argc; i++) {
 		free(newargv[i]);
 	}
 	free(newargv);

	if (!op.flag)
 		ft_printf("\n");
 	// print_5_bits(op.flag);
 }
//TODO RIFARE LA FUNZIONE get_opt fare in modo che funzioni anche con "srcs/ -l" e non solo con "-l srcs/"
// puo essere un idea> fare un sort che mette in cima le opzioni e poi i path
//
// int main(int argc, char **argv)
// {
//     int opt;
//     op.flag = 0;
//     op.head = NULL;
//     op.raw = isatty(STDOUT_FILENO);
//
//     // Skip program name in first pass
//     for (int i = 1; i < argc; i++) {
//         // Handle standalone "-" differently
//         if (strcmp(argv[i], "-") == 0) {
//             continue;  // Skip lone dash
//         }
//         // Process options only if they start with "-" and aren't just "-"
//         if (argv[i][0] == '-' && argv[i][1] != '\0') {
//             op.my_optind = i;
//             while ((opt = ft_getopt(argc, argv, "lRart")) != -1) {
//                 switch (opt) {
//                     case 'l':
//                         op.long_format = 1;
//                         op.flag |= OPT_LONG_FORMAT;
//                         break;
//                     case 'R':
//                         op.recursive = 1;
//                         op.flag |= OPT_RECURSIVE;
//                         break;
//                     case 'a':
//                         op.show_all = 1;
//                         op.flag |= OPT_SHOW_ALL;
//                         break;
//                     case 'r':
//                         op.reverse = 1;
//                         op.flag |= OPT_REVERSE;
//                         break;
//                     case 't':
//                         op.sort_time = 1;
//                         op.flag |= OPT_SORT_TIME;
//                         break;
//                     default:
//                         exit(EXIT_FAILURE);
//                 }
//             }
//         }
//     }
//
//     if (op.my_optind >= argc) {
//         op.path = ".";
//         run(0, op.path, 0);
//     } else {
//         char **path = sort_path_list(argc, op.my_optind, argv);
//         for (int i = op.my_optind; i < argc; i++) {
//             // Skip arguments that were processed as options
//             if (argv[i][0] == '-' && argv[i][1] != '\0') {
//                 continue;
//             }
//             op.path = path[i];
//             run(i, op.path, argc - op.my_optind);
//             if (need_extra_nline(i, argc))
//                 ft_printf("\n");
//         }
//         free(path);
//
//     }
//     if (!op.flag)
//         ft_printf("\n");
// }
