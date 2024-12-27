/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42roma.it>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:17:59 by mtoia             #+#    #+#             */
/*   Updated: 2024/08/19 20:05:43 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_H
# define OPTION_H

#include <stdio.h>
#include <string.h>
#include <dirent.h>


#define Option() (struct optionStruct){1, NULL, 1, 0}

struct optionStruct
{
	int 	my_optind;      // Index of the next element to be processed
	char 	*my_optarg; 		// Pointer to the argument associated with the option
	int 	my_opterr;      // If nonzero, prints error message
	int 	my_optopt;      // Last known option character
	int     long_format;	// -l option
	int     recursive;		// -R option
	int     sort_time;		// -t option
	int     reverse;		// -r option
	int     show_all;		// -a option
	char   *path;			// path
	char	**to_expand;	// Matrix of subdir to expand if -R flag
	int 	flag;
	int		size_width;		// width of the size column
	int		layer;			// layer of the recursion
	t_list  *head;			// list of files
	// char   **res;			// Array of results to print // not used
}; extern struct optionStruct op;


int ft_getopt(int argc, char *const argv[], const char *optstring);
int no_option(char *path, DIR *dir);
//mtl variable is used to check if there 2 or more path given
int run(int mlt, char *tmp, int argc);  // run function

#endif