/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 12:51:05 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/28 01:10:56 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H
# include <string.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include "libft.h"
# include <mach-o/nlist.h>
# include <mach-o/loader.h>
# include <mach-o/stab.h>
# include "short.h"

typedef struct	s_symbol
{
	char		*name;
	uint64_t	address;
	uint8_t		type;
	uint8_t		section;
}				t_symbol;

typedef struct	s_params
{
	t_list		*list;
	void		*ptr;
	char		arch;
	size_t		size;
	t_segment32	*seg32;
	t_segment64	*seg64;
}				t_params;

void			ft_sort(t_list *list);
void			ft_nm(t_params *params);
void			ft_nm64(t_params *params);
void			ft_nm32(t_params *params);
#endif
