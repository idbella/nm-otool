/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm64.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 12:56:01 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/29 18:06:16 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	ft_get64(t_params *params, struct symtab_command *sym)
{
	int				i;
	struct nlist_64	*array;
	char			*string;
	t_symbol		*symbol;
	char			*name;

	array = params->ptr + sym->symoff;
	string = params->ptr + sym->stroff;
	i = 0;
	while (i < sym->nsyms)
	{
		name = string + array[i].n_un.n_strx;
		if (!(array[i].n_type & N_STAB))
		{
			symbol = ft_memalloc(sizeof(t_symbol));
			symbol->address = array[i].n_value;
			symbol->name = name;
			symbol->type = array[i].n_type;
			symbol->section = array[i].n_sect;
			ft_lstadd(&params->list, ft_lstnew(symbol, 0));
		}
		i++;
	}
}

void	ft_getsection64(t_segment64 *seg, t_params *params)
{
	int			i;
	int			count;
	t_section64	*sec;
	t_list		*node;

	i = 0;
	count = seg->nsects;
	sec = (void *)++seg;
	while (i < count)
	{
		node = ft_lstnew(0, 0);
		node->content = sec;
		ft_lstadd(&params->sections, node);
		sec++;
		i++;
	}
}

void	ft_nm64(t_params *params)
{
	int							ncmds;
	int							i;
	struct symtab_command		*sym;
	struct segment_command_64	*seg;

	ncmds = ((t_header64 *)params->ptr)->ncmds;
	seg = params->ptr + sizeof(t_header64);
	i = 0;
	while (i < ncmds)
	{
		if (seg->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)seg;
			ft_get64(params, sym);
		}
		if (seg->cmd == LC_SEGMENT_64)
			ft_getsection64(seg, params);
		seg = (void *)seg + seg->cmdsize;
		i++;
	}
}
