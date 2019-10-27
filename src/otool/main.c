/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:02:42 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/27 15:08:39 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int main(int argc, char **argv)
{
	size_t		size;
	struct stat	st;
	int			fd;
	void		*ptr;
	int			i;

	i = 1;
	while (i < argc)
	{
		if ((fd = open(argv[i], O_RDONLY)) < 0)
		{
			ft_printf("error opening file\n");
			return 1;
		}
		if (fstat(fd, &st))
		{
			ft_printf("error file's file descriptor\n");
			return (1);
		}
		if ((ptr = mmap(0, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		{
			ft_printf("error mapping file\n");
			return (1);
		}
		ft_printf("%s:\n", argv[i]);
		ft_otool(ptr);
		i++;
	}
	if (argc < 2)
		ft_printf("usage otool file\n");
}
