/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42roma.it>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:48:38 by mtoia             #+#    #+#             */
/*   Updated: 2024/08/16 18:16:30 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"
struct optionStruct op = Option();

int no_option(char *path, DIR *dir)
{
	int i = 0;
	struct dirent *sd;
	while ((sd = readdir(dir)) != NULL)
	{
		if (sd->d_name[0] == '.')
			continue;
		i = 1;
		ft_printf("%s  ", sd->d_name);
	}
	closedir(dir);
	return (i);
}

int ft_getopt(int argc, char *const argv[], const char *optstring) {
    static int opt_pos = 0; // Position within the current argv element
    char *optchar;

    // End of options or no more arguments to process
    if (op.my_optind >= argc || argv[op.my_optind][0] != '-' || argv[op.my_optind][1] == '\0') {
        return -1;
    }

    // Handle "--" which indicates end of options
    if (strcmp(argv[op.my_optind], "--") == 0) {
        op.my_optind++;
        return -1;
    }

    // Get the current option character
    if (opt_pos == 0) {
        opt_pos++;
    }
    op.my_optopt = argv[op.my_optind][opt_pos];

    // Look for the option in optstring
    optchar = strchr(optstring, op.my_optopt);
    if (optchar == NULL) {
        // Option not found
        if (op.my_opterr) {
            fprintf(stderr, "Unknown option: -%c\n", op.my_optopt);
        }
        opt_pos++;
        if (argv[op.my_optind][opt_pos] == '\0') {
            op.my_optind++;
            opt_pos = 0;
        }
        return '?';
    }

    // Check if the option requires an argument
    if (optchar[1] == ':') {
        // Option with required argument
        if (argv[op.my_optind][opt_pos + 1] != '\0') {
            // Argument is attached to the option
            op.my_optarg = &argv[op.my_optind][opt_pos + 1];
            op.my_optind++;
            opt_pos = 0;
        } else if (op.my_optind + 1 < argc) {
            // Argument is the next element in argv
            op.my_optarg = argv[++op.my_optind];
            op.my_optind++;
            opt_pos = 0;
        } else {
            // Argument missing
            if (op.my_opterr) {
                fprintf(stderr, "Option -%c requires an argument\n", op.my_optopt);
            }
            opt_pos = 0;
            return '?';
        }
    } else {
        // Option without argument
        if (argv[op.my_optind][opt_pos + 1] == '\0') {
            op.my_optind++;
            opt_pos = 0;
        } else {
            opt_pos++;
        }
        op.my_optarg = NULL;
    }

    return op.my_optopt;
}
