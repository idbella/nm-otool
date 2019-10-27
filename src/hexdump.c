/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexdump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 19:17:27 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/27 11:24:31 by sid-bell         ###   ########.fr       */
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
		ft_printf("%08x\t", ptr);
		i2 = 0;
		while (i2 < 16 && i + i2 < size)
		{
			if (i2 != 0)
				ft_printf(" ");
			ft_printhex(*(tmp + offset + i + i2));
			i2++;
		}
		while (i2 < 16)
		{
			ft_printf("   ");
			i2++;
		}
		i2 = 0;
		ft_printf("\t\t");
		while (i2 < 16 && i + i2 < size)
		{
			char c = *(tmp + offset + i + i2);
			if (ft_isprint(c))
				ft_printf("%c", c);
			else
				ft_printf(".");
			i2++;
		}
		ft_printf(" \n");
		ptr+=16;
		i += 16;
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
		ft_print(0,  st.st_size,  ptr, 0);
	}
	else
		ft_printf("usage otool file\n");
}