/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:02:42 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/27 15:56:55 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int		ft_open(void **ptr, char *file, size_t *size)
{
	int			fd;
	struct stat	st;

	if ((fd = open(file, O_RDONLY)) < 0)
	{
		ft_printf("error opening file\n");
		return (0);
	}
	if (fstat(fd, &st))
	{
		ft_printf("error file's file descriptor\n");
		return (0);
	}
	if ((*ptr = mmap(0, st.st_size,
			PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_printf("error mapping file\n");
		return (0);
	}
	*size = st.st_size;
	return (fd);
}

int		main(int argc, char **argv)
{
	int			fd;
	int			i;
	void		*ptr;
	size_t		size;

	i = 1;
	while (i < argc)
	{
		if ((fd = ft_open(&ptr, argv[i], &size)) > 0)
		{
			ft_printf("%s:\n", argv[i]);
			ft_otool(ptr);
			munmap(ptr, size);
			close(fd);
		}
		i++;
	}
	if (argc < 2)
		ft_printf("usage otool file\n");
}
