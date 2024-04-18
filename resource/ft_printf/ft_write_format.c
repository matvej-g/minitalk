/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:37:55 by mgering           #+#    #+#             */
/*   Updated: 2023/11/27 17:06:08 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_char(int c, t_flags *flag)
{
	flag->count += 1;
	if (write(flag->fd, &c, 1) == -1)
		flag->error = -1;
	return (flag->error);
}

int	write_str(char *str, t_flags *flag)
{
	int	count;

	count = 0;
	if (str == NULL)
		str = "(null)";
	while (*str != '\0')
	{
		if (write_char((int)*str, flag) == -1)
			return (-1);
		str++;
	}
	return (flag->error);
}

int	write_number(int n, t_flags *flag)
{
	unsigned int	i;

	i = 0;
	flag->base = 10;
	if (n < 0)
	{
		write_char('-', flag);
		i = -1 * n;
	}
	else
		i = n;
	if (i >= 10)
	{
		write_number(i / 10, flag);
		write_number(i % 10, flag);
	}
	else
	{
		if (flag->error == -1)
			return (-1);
		write_char(i + '0', flag);
	}
	return (flag->error);
}

int	write_hex(unsigned long int n, t_flags *flag, char c)
{
	unsigned long int	*i;

	i = &n;
	if (c == 'u')
		flag->base = 10;
	else
		flag->base = 16;
	if (*i >= (unsigned long int)flag->base)
	{
		write_hex(*i / flag->base, flag, c);
		write_hex(*i % flag->base, flag, c);
	}
	else
	{
		if (flag->error == -1)
			return (-1);
		else if (c == 'X')
			write_char(flag->hexupper[*i], flag);
		else
			write_char(flag->hexlower[*i], flag);
	}
	return (flag->error);
}

int	write_p(unsigned long int ptr, t_flags *flag)
{
	if (write(flag->fd, "0x", 2) == -1)
	{
		flag->error = -1;
		return (-1);
	}
	flag->count += 2;
	if (ptr == 0)
	{
		if (write(flag->fd, "0", 1) == -1)
		{
			flag->error = -1;
			return (-1);
		}
		flag->count += 1;
	}
	else
	{
		if (write_hex(ptr, flag, 'x') == -1)
			return (-1);
	}
	return (flag->error);
}
