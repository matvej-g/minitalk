/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:39:52 by mgering           #+#    #+#             */
/*   Updated: 2023/11/27 17:00:11 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flags	*ft_initialise_flag(t_flags *flag)
{
	flag->count = 0;
	flag->base = 0;
	flag->error = 0;
	flag->fd = 1;
	flag->hexlower = "0123456789abcdef";
	flag->hexupper = "0123456789ABCDEF";
	return (flag);
}

static int	check_format(char specifier, t_flags *flag)
{
	if (specifier == 'c')
		write_char(va_arg(flag->args, int), flag);
	else if (specifier == 's')
		write_str(va_arg(flag->args, char *), flag);
	else if (specifier == 'p')
		write_p(va_arg(flag->args, unsigned long int), flag);
	else if (specifier == '%')
		write_char('%', flag);
	else if (specifier == 'd' || specifier == 'i')
		write_number(va_arg(flag->args, int), flag);
	else if (specifier == 'u')
		write_hex(va_arg(flag->args, unsigned int), flag, specifier);
	else if (specifier == 'x')
		write_hex(va_arg(flag->args, unsigned int), flag, specifier);
	else if (specifier == 'X')
		write_hex(va_arg(flag->args, unsigned int), flag, specifier);
	else
		flag->error = -1;
	return (flag->error);
}

static int	free_list(t_flags *flag)
{
	va_end(flag->args);
	free(flag);
	return (-1);
}

int	ft_printf(const char *format, ...)
{
	t_flags	*flag;
	int		len;

	len = 0;
	flag = malloc(sizeof(t_flags));
	if (!flag)
		return (-1);
	ft_initialise_flag(flag);
	va_start(flag->args, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			if (check_format(*(++format), flag) == -1)
				return (free_list(flag));
		}
		else if (write_char((int)*format, flag) == -1)
			return (free_list(flag));
		format++;
	}
	len = flag->count;
	va_end(flag->args);
	free(flag);
	return (len);
}
