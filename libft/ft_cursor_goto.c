/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_goto.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 20:15:57 by asolis            #+#    #+#             */
/*   Updated: 2017/07/27 20:15:59 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_cursor_goto(int x, int y)
{
	char *str1;
	char *str2;

	if ((str1 = tgetstr("cm", NULL)) != NULL)
	{
		if ((str2 = tgoto(str1, x, y)) != NULL)
			ft_putstr_fd(str2, 2);
	}
}
