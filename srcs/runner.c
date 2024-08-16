/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42roma.it>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:26:13 by mtoia             #+#    #+#             */
/*   Updated: 2024/08/16 18:16:53 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int run(int mlt)
{
	// printf("run %d\n", mlt);
	if (mlt >= 1)
	{
		if (mlt > 2)
			printf("\n%s:\n", op.path);
		else
			printf("%s:\n", op.path);
	}
	DIR *dir = opendir(op.path);
    if (!dir) {
        perror("opendir");
        return (1);
    }
	if (no_option(".", dir) != 0)
		ft_printf("\n");
	return (0);
}

