/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm32.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 12:53:06 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/27 20:18:51 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	ft_get32(t_params *params, struct symtab_command *sym)
{
	int				i;
	struct nlist	*array;
	char			*string;
	t_list			*node;
	t_symbol		*symbol;

	array = params->ptr + sym->symoff;
	string = params->ptr + sym->stroff;
	i = 0;
	while (i < sym->nsyms)
	{
		symbol = ft_memalloc(sizeof(t_symbol));
		symbol->address = array[i].n_value;
		symbol->name = string + array[i].n_un.n_strx;
		symbol->type = array[i].n_type;
		symbol->section = array[i].n_sect;
		node = ft_lstnew(symbol, 0);
		ft_lstadd(&params->list, node);
		i++;
	}
}

void	ft_nm32(t_params *params)
{
	int							ncmds;
	int							i;
	struct mach_header			*header;
	struct symtab_command		*sym;
	struct segment_command		*seg;

	header = (struct mach_header *)params->ptr;
	ncmds = header->ncmds;
	seg = params->ptr + sizeof(*header);
	i = 0;
	while (i < ncmds)
	{
		if (seg->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)seg;
			ft_get32(params, sym);
			break ;
		}
		seg = (void *)seg + seg->cmdsize;
		i++;
	}
}
