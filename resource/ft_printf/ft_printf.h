/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:24:08 by mgering           #+#    #+#             */
/*   Updated: 2023/11/27 12:34:53 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//ft_printf V10

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct flag_list
{
	va_list	args;
	int		count;
	int		base;
	int		error;
	int		fd;
	char	*hexlower;
	char	*hexupper;
}	t_flags;

int	ft_printf(const char *format, ...);
int	write_char(int c, t_flags *flag);
int	write_str(char *str, t_flags *flag);
int	write_number(int n, t_flags *flag);
int	write_hex(unsigned long int n, t_flags *flag, char c);
int	write_p(unsigned long int ptr, t_flags *flag);

#endif