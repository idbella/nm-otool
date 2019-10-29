/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 19:17:27 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/29 18:24:50 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	ft_getkey(int type, char c)
{
	if (type & N_EXT)
		return (ft_toupper(c));
	return (c);
}

char	ft_gettypeofsection(t_list *lst, t_symbol *symbol)
{
	int				i;
	t_section32		*section;

	i = 1;
	while (lst)
	{
		section = lst->content;
		if (i == symbol->section)
		{
			if (ft_strequ(section->sectname, "__bss"))
				return (ft_getkey(symbol->type, 'b'));
			if (ft_strequ(section->sectname, "__data"))
				return (ft_getkey(symbol->type, 'd'));
			if (ft_strequ(section->sectname, "__text"))
				return (ft_getkey(symbol->type, 't'));
			if (ft_strequ(section->sectname, "__common")
				|| ft_strequ("__const", section->sectname))
				return (ft_getkey(symbol->type, 's'));
		}
		lst = lst->next;
		i++;
	}
	return ('?');
}

char	ft_gettype(t_symbol *sym, t_list *lst)
{
	int	type;

	type = sym->type;
	if ((type & N_TYPE) == N_UNDF)
		return ('U');
	if ((type & N_TYPE) == N_ABS)
		return ('A');
	if ((type & N_TYPE) == N_SECT)
		return (ft_gettypeofsection(lst, sym));
	if ((type & N_TYPE) == N_PBUD)
		return ('u');
	if ((type & N_TYPE) == N_INDR)
		return ('I');
	return ('?');
}

void	ft_print(t_params *params)
{
	t_list		*lst;
	t_symbol	*symbol;
	char		c;
	char		*format;

	lst = params->list;
	while (lst)
	{
		symbol = lst->content;
		c = ft_gettype(symbol, params->sections);
		if (symbol->address)
		{
			format = params->arch == 64 ? "%016x %c %s\n" : "%08x %c %s\n";
			ft_printf(format, symbol->address, c, symbol->name);
		}
		else
		{
			format = params->arch == 64 ? "% 16s %c %s\n" : "% 8s %c %s\n";
			ft_printf(format, "", c, symbol->name);
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
