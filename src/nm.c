/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 19:17:27 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/27 10:55:39 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "libft/libft.h"
#include <mach-o/nlist.h>
#include <mach-o/loader.h>

typedef struct	s_symbol
{
	char		*name;
	uint64_t	address;
	uint8_t		type;
}				t_symbol;

void	ft_sort(t_list *list)
{
	t_list		*head;
	t_symbol	*symbol1;
	t_symbol	*symbol2;
	char	c;

	c = 1;
	head = list;
	while (c)
	{
		c = 0;
		while (list)
		{
			if (list->next)
			{
				symbol2 = list->next->content;
				symbol1 = list->content;
				if (ft_strcmp(symbol1->name, symbol2->name) > 0)
				{
					c = 1;
					list->next->content = list->content;
					list->content = symbol2;
				}
			}
			list = list->next;
		}
		list = head;
	}
}

static char ft_gettype(int type)
{
	if (type == 1)
		return 'U';
	else if (type == 15)
		return 'T';
	else if (type == 14)
		return 't';
	else
		return ('?');
}

void ft_print(t_list *lst)
{
	t_symbol	*symbol;
	char		c;

	while (lst)
	{
		symbol = lst->content;
		c = ft_gettype(symbol->type);
		if (symbol->address)
			ft_printf("%016x %c %s\n", symbol->address, c, symbol->name);
		else
			ft_printf("% 18c %s\n", c, symbol->name);
		lst = lst->next;
	}
}

t_list	*ft_get(struct symtab_command *sym, char *ptr)
{
	int				i;
	struct nlist_64	*array;
	char			*string;
	t_list			*lst;
	t_list			*node;
	t_symbol		*symbol;

	lst = NULL;
	array = (void *)ptr + sym->symoff;
	string = (void *)ptr + sym->stroff;
	i = 0;
	while (i < sym->nsyms)
	{
		symbol = ft_memalloc(sizeof(t_symbol));
		symbol->address = array[i].n_value;
		symbol->name = string + array[i].n_un.n_strx;
		symbol->type = array[i].n_type;
		node = ft_lstnew(symbol, 0);
		ft_lstadd(&lst, node);
		i++;
	}
	return (lst);
}

static void ft_nm(char *ptr)
{
	int							ncmds;
	int							i;
	struct mach_header_64		*header;
	struct symtab_command		*sym;
	struct segment_command_64	*seg;
	t_list						*lst;

	header = (struct mach_header_64 *) ptr;
	ncmds = header->ncmds;
	seg = (void *)ptr + sizeof(*header);
	i = 0;
	while (i < ncmds)
	{
		if (seg->cmd == LC_SYMTAB)
		{
			sym = (void *)seg;
			lst = ft_get(sym, (void *)ptr);
			ft_sort(lst);
			ft_print(lst);
			break ;
		}
		seg = (void *)seg + seg->cmdsize;
		i++;
	}

}

int main(int argc, char **argv)
{
	size_t size;
	struct stat st;
	int fd = open(argv[1], O_RDONLY);
	fstat(fd, &st);
	void *ptr = mmap(0, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	ft_nm(ptr);
	close(fd);
	munmap(ptr, st.st_size);
}