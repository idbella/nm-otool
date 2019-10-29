/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:10:33 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/28 23:39:28 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	ft_print64(uint64_t ptr, uint64_t size, char *tmp, uint32_t offset)
{
	uint64_t i;
	uint64_t i2;

	i = 0;
	while (i < size)
	{
		ft_printf("%016x\t", ptr);
		i2 = 0;
		while (i2 < 16 && i + i2 < size)
		{
			if (i2 != 0)
				ft_printf(" ");
			ft_printhex(*(tmp + offset + i + i2));
			i2++;
		}
		ft_printf(" \n");
		ptr += 16;
		i += 16;
	}
}

char	ft_getsection(t_segment64 *seg, void *ptr)
{
	int			i;
	int			count;
	t_section64	*sec;

	if (ft_strequ(seg->segname, "__TEXT"))
	{
		i = 0;
		count = seg->nsects;
		sec = (void *)++seg;
		while (i < count)
		{
			if (ft_strequ(sec->sectname, "__text"))
			{
				ft_printf("Contents of (__TEXT,__text) section\n");
				ft_print64(sec->addr, sec->size, ptr, sec->offset);
				return (1);
			}
			sec += sec->size;
			i++;
		}
		return (1);
	}
	return (0);
}

void	ft_otool64(void *ptr)
{
	int			ncmds;
	int			i;
	t_header64	*header;
	t_segment64	*seg;

	header = (t_header64 *)ptr;
	ncmds = header->ncmds;
	seg = ptr + sizeof(t_header64);
	i = 0;
	while (i < ncmds)
	{
		if (seg->cmd == LC_SEGMENT_64)
		{
			if (ft_getsection(seg, ptr))
				break ;
		}
		seg = (void *)seg + seg->cmdsize;
		i++;
	}
}
