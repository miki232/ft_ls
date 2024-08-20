/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42roma.it>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:48:38 by mtoia             #+#    #+#             */
/*   Updated: 2024/08/19 18:56:58 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"
struct optionStruct op = Option();


int ft_getopt(int argc, char *const argv[], const char *optstring) {
    static int opt_pos = 0; // Position within the current argv element

    // End of options or no more arguments to process
    if (op.my_optind >= argc || argv[op.my_optind][0] != '-' || argv[op.my_optind][1] == '\0') {
        return -1;
    }

    // Handle "--help"
    if (strcmp(argv[op.my_optind], "--help") == 0) {
        op.my_optind++;
        return -1;
    }

    // Get the current option character
    if (opt_pos == 0) {
        opt_pos++;
    }
    op.my_optopt = argv[op.my_optind][opt_pos];

    // Look for the option in optstring
    char *optchar = strchr(optstring, op.my_optopt);
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
    // Option without argument
    if (argv[op.my_optind][opt_pos + 1] == '\0') {
        op.my_optind++;
        opt_pos = 0;
    } else {
        opt_pos++;
    }
    op.my_optarg = NULL;

    return op.my_optopt;
}
