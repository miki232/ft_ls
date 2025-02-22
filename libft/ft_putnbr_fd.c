/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassyao <ohassyao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:40:57 by ohassyao          #+#    #+#             */
/*   Updated: 2022/03/22 17:58:29 by ohassyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	printer(char c, int fd)
{
	return(write(fd, &c, 1));
}

int	ft_putnbr_fd(int n, int fd)
{
  int i;
  i = 0;
	if (n == -2147483648)
	{
		i += ft_putnbr_fd(n / 10, fd);
		i += printer('8', fd);
	}
	else if (n < 0)
	{
		i += printer('-', fd);
		i += ft_putnbr_fd(-n, fd);
	}
	else
	{
		if (n <= 9)
			i += printer(n + '0', fd);
		else
		{
			i += ft_putnbr_fd(n / 10, fd);
			i += printer((n % 10) + '0', fd);
		}
	}
    return (i);
}

