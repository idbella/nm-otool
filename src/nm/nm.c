/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 19:17:27 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/27 14:13:21 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	ft_sort(t_list *list)
{
	t_list		*head;
	t_symbol	*symbol1;
	t_symbol	*symbol2;
	char	c;

	c = 1;
	head = list;
	while (c)
	{
		c = 0;
		while (list)
		{
			if (list->next)
			{
				symbol2 = list->next->content;
				symbol1 = list->content;
				if (ft_strcmp(symbol1->name, symbol2->name) > 0)
				{
					c = 1;
					list->next->content = list->content;
					list->content = symbol2;
				}
			}
			list = list->next;
		}
		list = head;
	}
}

static char ft_gettype(int type)
{
	if (type == 1)
		return 'U';
	else if (type == 15)
		return 'T';
	else if (type == 14)
		return 't';
	else
		return ('?');
}

void ft_print(t_params *params)
{
	t_list		*lst;
	t_symbol	*symbol;
	char		c;

	lst = params->list;
	while (lst)
	{
		symbol = lst->content;
		c = ft_gettype(symbol->type);
		if (symbol->address)
		{
			if (params->arch == 64)
				ft_printf("%016x %c %s\n", symbol->address, c, symbol->name);
			else
				ft_printf("%08x %c %s\n", symbol->address, c, symbol->name);
		}
		else
		{
			if (params->arch == 64)
				ft_printf("% 16s %c %s\n", "", c, symbol->name);
			else
				ft_printf("% 8s %c %s\n", "", c, symbol->name);
		}
		lst = lst->next;
	}
}

void ft_nm(t_params *params)
{
	uint32_t	mgc_nbr;

	mgc_nbr = *((int *)params->ptr);
	if (mgc_nbr == MH_MAGIC_64)
	{
		params->arch = 64;
		ft_nm64(params);
	}
	else if (mgc_nbr == MH_MAGIC)
	{
		params->arch = 32;
		ft_nm32(params);
	}
	ft_sort(params->list);
	ft_print(params);
}
