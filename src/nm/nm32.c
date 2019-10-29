/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm32.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 12:53:06 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/29 18:04:55 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	ft_get32(t_params *params, struct symtab_command *sym)
{
	int				i;
	struct nlist	*array;
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

void	ft_getsection32(t_segment32 *seg, t_params *params)
{
	int			i;
	int			count;
	t_section32	*sec;
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

void	ft_nm32(t_params *params)
{
	int						ncmds;
	int						i;
	struct symtab_command	*sym;
	struct segment_command	*seg;

	ncmds = ((t_header32 *)params->ptr)->ncmds;
	seg = params->ptr + sizeof(t_header32);
	i = 0;
	while (i < ncmds)
	{
		if (seg->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)seg;
			ft_get32(params, sym);
		}
		if (seg->cmd == LC_SEGMENT)
			ft_getsection32(seg, params);
		seg = (void *)seg + seg->cmdsize;
		i++;
	}
}
