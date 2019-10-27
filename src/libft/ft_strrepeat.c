/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrepeat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 06:18:08 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/26 23:28:13 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrepeat(char const *str, size_t count)
{
	char *new;

	new = NULL;
	if (str && count > 0)
	{
		if ((new = (char *)malloc(sizeof(char) *
			(ft_strlen(str) * count))) == NULL)
			return (NULL);
		while (count--)
		{
			ft_strcat(new, str);
		}
	}
	return (new);
}
