/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:03:15 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/27 14:57:54 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "libft.h"
#include <mach-o/nlist.h>
#include <mach-o/loader.h>

void	ft_otool(void *ptr);
void	ft_otool64(void *ptr);
void	ft_otool32(void *ptr);
void	ft_printhex(unsigned char c);
#endif