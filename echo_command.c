/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 05:18:55 by asolis            #+#    #+#             */
/*   Updated: 2017/06/22 05:18:56 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			echo(char *c)
{
	int		i;

	i = 0;
	while (c[i] != '\0')
	{
		if (c[i] == '\\' && c[i + 1] == 'c')
			return (0);
		if (c[i] == '\\' && c[i + 1] == 'n')
		{
			ft_printfbasic("\n");
			i++;
		}
		else if (c[i] != 34)
			ft_putchar(c[i]);
		i++;
	}
	return (1);
}

void		validation_echo(char **c, t_list *e)
{
	int		i;
	char	*tmp;

	i = 0;
	while (c[++i] != NULL)
	{
		if (i > 1)
			ft_printfbasic(" ");
		if (c[i][0] == '$')
		{
			tmp = ft_strsub(c[i], 1, ft_strlen(c[i]));
			if (validation_name(tmp))
				ft_lstsearch(e, tmp);
			ft_memdel((void**)&tmp);
		}
		else if (!echo(c[i]))
			return ;
	}
	ft_printfbasic("\n");
}
