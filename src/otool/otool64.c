/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:10:33 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/27 15:02:42 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	ft_print(uint64_t ptr, uint64_t size, char *tmp, uint32_t offset)
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
		ptr+=16;
		i += 16;
	}
}

void ft_otool64(void *ptr)
{
	int							ncmds;
	int							i;
	struct mach_header_64		*header;
	struct segment_command_64	*seg;
	struct section_64			*sec;

	header = (struct mach_header_64 *) ptr;
	ncmds = header->ncmds;
	seg = ptr + sizeof(struct mach_header_64);
	i = 0;
	while (i < ncmds)
	{
		if (seg->cmd == LC_SEGMENT_64)
		{
			if (ft_strequ(seg->segname, "__TEXT"))
			{
				i = 0;
				ncmds = seg->nsects;
				sec = (void *) ++seg;
				while (i < ncmds)
				{
					if (ft_strequ(sec->sectname, "__text"))
					{
						ft_printf("Contents of (__TEXT,__text) section\n");
						ft_print(sec->addr, sec->size, ptr, sec->offset);
						return ;
					}
					sec++;
					i++;
				}
				return ;
			}
		}
		seg++;
		i++;
	}
}
