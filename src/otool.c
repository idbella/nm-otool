/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 19:17:27 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/27 11:00:49 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "libft/libft.h"
#include <mach-o/nlist.h>
#include <mach-o/loader.h>

void ft_printhex(unsigned char c)
{
	char *patt = "0123456789abcdef";
	ft_printf("%c", patt[c / 16]);
	ft_printf("%c", patt[c % 16]);
}

void	ft_print(uint64_t ptr, uint64_t size, char *tmp, uint32_t offset)
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

static void ft_otool(char *ptr)
{
	int							ncmds;
	int							i;
	struct mach_header_64		*header;
	struct symtab_command		*sym;
	struct segment_command_64	*seg;
	struct section_64			*sec;
	char						*tmp;
	int							magic_number;

	tmp = ptr;
	header = (struct mach_header_64 *) ptr;
	ncmds = header->ncmds;
	seg = (void *)ptr + sizeof(*header);
	i = 0;
	while (i < ncmds)
	{
		if (seg->cmd == LC_SEGMENT_64)
		{
			if (ft_strequ(seg->segname, "__TEXT"))
			{
				ft_printf("Contents of (__TEXT,__text) section\n");
				int index = 0;
				int count = seg->nsects;
				sec = (void *) seg + sizeof(struct segment_command_64);
				while (index < count)
				{
					if (ft_strequ(sec->sectname, "__text"))
					{
						ft_print(sec->addr, sec->size, tmp, sec->offset);
						return ;
					}
					sec = (void *)sec + sizeof(struct section_64);
					index++;
				}
			}
		}
		seg = (void *)seg + seg->cmdsize;
		i++;
	}

}

int main(int argc, char **argv)
{
	size_t		size;
	struct stat	st;
	int			fd;
	void		*ptr;

	if (argc > 1)
	{
		if ((fd = open(argv[1], O_RDONLY)) < 0)
		{
			ft_printf("error opening file\n");
			return 1;
		}
		if (stat(argv[1], &st))
		{
			ft_printf("error opening file\n");
			return (1);
		}
		if ((ptr = mmap(0, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		{
			ft_printf("error mapping file\n");
			return (1);
		}
		ft_printf("%s:\n", argv[1]);
		ft_otool(ptr);
	}
	else
		ft_printf("usage otool file\n");
}