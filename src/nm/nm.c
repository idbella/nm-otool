/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 19:17:27 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/28 00:51:37 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	ft_sort(t_list *list)
{
	t_list		*head;
	t_symbol	*symbol1;
	t_symbol	*symbol2;
	char		c;

	c = 1;
	head = list;
	while (c && ((c = 0) || 1))
	{
		while (list)
		{
			if (list->next)
			{
				symbol2 = list->next->content;
				symbol1 = list->content;
				if (ft_strcmp(symbol1->name, symbol2->name) > 0 && (c = 1))
				{
					list->next->content = list->content;
					list->content = symbol2;
				}
			}
			list = list->next;
		}
		list = head;
	}
}

char	ft_getkey(int type, char c)
{
	if (type & N_EXT)
		return (ft_toupper(c));
	return (c);
}

char	ft_gettype(t_symbol *sym)
{
	int type;

	type = sym->type;
	if ((type & N_TYPE) == N_UNDF)
		return 'U';
	if ((type & N_TYPE) == N_ABS)
		return 'A';
	if ((type & N_TYPE) == N_SECT)
	{
		if (sym->section == 1)
			return (ft_getkey(type, 't'));
		if (sym->section == 31 || sym->section == 11)
			return (ft_getkey(type, 'b'));
		if (sym->section == 17 || sym->section == 5 || sym->section == 12 || sym->section == 29 || sym->section == 10 || sym->section == 28 || sym->section == 32)
			return (ft_getkey(type, 's'));
		else if (sym->section == 30)
			return (ft_getkey(type, 'd'));
		return ('*');
	}
	if ((type & N_TYPE) == N_PBUD)
		return ('u');
	if ((type & N_TYPE) == N_INDR)
		return ('I');
	
	return '#';
}

void	ft_print(t_params *params)
{
	t_list		*lst;
	t_symbol	*symbol;
	char		c;

	lst = params->list;
	while (lst)
	{
		symbol = lst->content;
		c = ft_gettype(symbol);
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

void	ft_nm(t_params *params)
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
