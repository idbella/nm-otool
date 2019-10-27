# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/26 22:31:28 by sid-bell          #+#    #+#              #
#    Updated: 2019/10/27 14:15:52 by sid-bell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

lib= src/libft/libft.a -Isrc/libft

all:
	make -C src/libft
	gcc src/nm/*.c -o nm $(lib)
	gcc src/otool/*.c -o otool $(lib)
	gcc src/hexdump.c -o hexdump $(lib)