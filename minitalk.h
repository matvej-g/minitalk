/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:15:48 by mgering           #+#    #+#             */
/*   Updated: 2024/04/17 14:50:50 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include "resource/ft_printf/ft_printf.h"
# include "resource/libft/libft.h"

typedef struct GlobalData{
	volatile sig_atomic_t	bit_index;
	volatile sig_atomic_t	current_char;
}	t_GlobalData;

#endif