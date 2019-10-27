/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:03:15 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/27 16:15:11 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H
# include <string.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include "libft.h"
# include <mach-o/nlist.h>
# include <mach-o/loader.h>

typedef struct segment_command_64	t_segment64;
typedef struct mach_header_64		t_header64;
typedef struct segment_command		t_segment32;
typedef struct mach_header			t_header32;
typedef struct section_64			t_section64;
typedef struct section				t_section32;

void								ft_otool(void *ptr);
void								ft_otool64(void *ptr);
void								ft_otool32(void *ptr);
void								ft_printhex(unsigned char c);
#endif
