/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_csd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 06:05:31 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/27 16:30:31 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_csd(t_printf_params *param)
{
	if (*param->format == 's')
	{
		ft_getstr(param);
		return (1);
	}
	else if (*param->format == 'c')
	{
		ft_getchar(param);
		return (1);
	}
	else if (*param->format == 'd')
	{
		ft_getint(param);
		return (1);
	}
	else if (*param->format == 'x')
	{
		ft_gethex(param);
		return (1);
	}
	return (0);
}

void	ft_padding(int padding, char **str, char leading)
{
	char	s[2];
	int		len;
	int		count;
	char	*pad;
	char	*tmp;

	if (padding > 0)
	{
		s[0] = leading;
		s[1] = 0;
		len = ft_strlen(*str);
		count = padding - len;
		if (count > 0)
		{
			if ((pad = ft_strrepeat(s, count)))
			{
				tmp = *str;
				*str = ft_strjoin(pad, *str);
				free(tmp);
			}
		}
	}
}

void	ft_getstr(t_printf_params *param)
{
	char	*str;
	char	*tmp;

	str = va_arg(*param->list, char *);
	if (!str)
		str = ft_strdup("(null)");
	else
		str = ft_strdup(str);
	ft_padding(param->padding, &str, param->leading);
	tmp = param->str;
	param->str = ft_strjoin(param->str, str);
	free(tmp);
	free(str);
}

void	ft_getint(t_printf_params *param)
{
	int		result;
	char	*str;
	char	*tmp;

	result = va_arg(*param->list, int);
	str = ft_itoa(result, 10);
	ft_padding(param->padding, &str, param->leading);
	tmp = param->str;
	param->str = ft_strjoin(param->str, str);
	free(tmp);
	free(str);
}

void	ft_getchar(t_printf_params *param)
{
	char	*str;
	char	*tmp;

	str = (char *)ft_strnew(1);
	str[0] = (char)va_arg(*param->list, int);
	str[1] = '\0';
	ft_padding(param->padding, &str, param->leading);
	tmp = param->str;
	param->str = ft_strjoin(param->str, str);
	free(tmp);
}
