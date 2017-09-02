/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_basic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 05:50:20 by asolis            #+#    #+#             */
/*   Updated: 2017/06/22 05:50:22 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_printfbasic(const char *format, ...)
{
	va_list p;
	char	*str;

	va_start(p, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			if ((*(format + 1)) == 's')
				ft_putstr(va_arg(p, char*));
			else if ((*(format + 1)) == 'd')
			{
				str = ft_itoa(va_arg(p, int));
				ft_putstr(str);
				ft_memdel((void**)&str);
			}
			format += 1;
		}
		else
			write(1, format, 1);
		format += 1;
	}
	va_end(p);
}
