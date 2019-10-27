/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 12:49:48 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/27 15:20:58 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int main(int argc, char **argv)
{
	size_t		size;
	struct stat	st;
	int			fd;
	void		*ptr;
	t_params	params;
	int			i;

	i = 1;
	while (i < argc)
	{
		if (argc > 2)
			ft_printf("\n%s:\n", argv[i]);
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
		params.list = NULL;
		params.ptr = ptr;
		ft_nm(&params);
		i++;
	}
	if (argc < 2)
		ft_printf("usage otool file\n");
}
