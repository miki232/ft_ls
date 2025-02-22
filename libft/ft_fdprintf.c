//
// Created by mtoia on 2/22/25.
//
#include "libft.h"

int	ft_hexavoid_fd(unsigned long long nb, int fd)
{
    int		i;
    char	*s;

    i = 0;
    if (nb < 16)
    {
        s = "0123456789abcdef";
        i += ft_putchar_fd(s[nb], fd);
    }
    else
    {
        i += ft_hexavoid_fd(nb / 16, fd);
        i += ft_hexavoid_fd(nb % 16, fd);
    }
    return (i);
}

int	ft_checker_fd(va_list *ptr, const char *str, int i, int fd)
{
    int	count;

    count = 0;
    if (str[i] == 'c')
        count += ft_putchar_fd(va_arg(*ptr, int), fd);
    else if (str[i] == 's')
        count += ft_putstr_fd(va_arg(*ptr, char *), fd);
    else if (str[i] == 'p')
    {
        count += ft_putstr_fd("0x", fd);
        count += ft_hexavoid_fd(va_arg(*ptr, unsigned long long), fd);
    }
    else if (str[i] == 'd' || str[i] == 'i')
        count += ft_putnbr_fd(va_arg(*ptr, int), fd);
    else if (str[i] == 'u')
        count += ft_putnbr_uns(va_arg(*ptr, unsigned int));
    else if (str[i] == 'x' || str[i] == 'X')
        count += ft_hexa_fd(va_arg(*ptr, unsigned int), str[i], fd);
    else if (str[i] == '%')
        count += write (fd, "%", 1);
    return (count);
}

int	ft_fdprintf(int fd, const char *str, ...)
{
    va_list	list;
    int		i;
    int		j;

    if (!str)
        return (0);
    va_start(list, str);
    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == '%')
            j += ft_checker_fd(&list, str, ++i, fd);
        else
            j += ft_putchar_fd(str[i], fd);
        i++;
    }
    va_end(list);
    return (j);
}