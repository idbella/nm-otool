/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 19:17:27 by sid-bell          #+#    #+#             */
/*   Updated: 2019/11/02 08:38:54 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	ft_printhex(unsigned char c)
{
	char *patt;

	patt = "0123456789abcdef";
	ft_printf("%c", patt[c / 16]);
	ft_printf("%c", patt[c % 16]);
}

void	ft_otool(void *ptr)
{
	uint32_t	mgc_nbr;

	mgc_nbr = *((int *)ptr);
	if (mgc_nbr & MH_MAGIC_64)
	{
		ft_otool64(ptr);
	}
	else if (mgc_nbr & MH_MAGIC)
	{
		ft_otool32(ptr);
	}
	else
		ft_printf("failed to dectect arch :-(\n");
}
