/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 12:49:48 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/29 18:11:34 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	ft_sort(t_list *list)
{
	t_list		*head;
	t_symbol	*symbol1;
	t_symbol	*symbol2;
	char		c;

	c = 1;
	head = list;
	while (c && ((c = 0) || 1))
	{
		while (list)
		{
			if (list->next)
			{
				symbol2 = list->next->content;
				symbol1 = list->content;
				if (ft_strcmp(symbol1->name, symbol2->name) > 0 && (c = 1))
				{
					list->next->content = list->content;
					list->content = symbol2;
				}
			}
			list = list->next;
		}
		list = head;
	}
}

char	ft_open(t_params *params, char *file)
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
	if ((params->ptr = mmap(0, st.st_size,
			PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_printf("error mapping file\n");
		return (0);
	}
	params->size = st.st_size;
	return (fd);
}

int		main(int argc, char **argv)
{
	int			fd;
	t_params	params;
	int			i;

	i = 1;
	while (i < argc)
	{
		if (argc > 2)
			ft_printf("\n%s:\n", argv[i]);
		if ((fd = ft_open(&params, argv[i])))
		{
			params.list = NULL;
			params.sections = NULL;
			ft_nm(&params);
			munmap(params.ptr, params.size);
			close(fd);
		}
		i++;
	}
	if (argc < 2)
		ft_printf("usage otool file\n");
}
