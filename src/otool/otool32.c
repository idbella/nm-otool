/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:12:53 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/27 16:19:08 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	ft_print32(uint32_t ptr, uint32_t size, char *tmp, uint32_t offset)
{
	uint32_t i;
	uint32_t i2;

	i = 0;
	while (i < size)
	{
		ft_printf("%08x\t", ptr);
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

char	ft_getsection32(t_segment32 *seg, void *ptr)
{
	int			i;
	int			count;
	t_section32	*sec;

	i = 0;
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
				ft_print32(sec->addr, sec->size, ptr, sec->offset);
				return (1);
			}
			sec++;
			i++;
		}
		return (1);
	}
	return (0);
}

void	ft_otool32(void *ptr)
{
	int			ncmds;
	int			i;
	t_header32	*header;
	t_segment32	*seg;

	header = (t_header32 *)ptr;
	ncmds = header->ncmds;
	seg = ptr + sizeof(t_header32);
	i = 0;
	while (i < ncmds)
	{
		if (seg->cmd == LC_SEGMENT)
		{
			if (ft_getsection32(seg, ptr))
				break ;
		}
		seg++;
		i++;
	}
}
