/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:09:49 by raldanda          #+#    #+#             */
/*   Updated: 2025/07/01 13:09:51 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>  // For read function
# include <stdlib.h>  // For malloc, free
# include <fcntl.h>   // For open function
# include <stdio.h>   // For printf function (used in main)
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*read_line(int fd, char *buffer, int *buf_pos, int *buf_size);
ssize_t	buffer_read(int fd, char *buffer, int *buf_pos, int *buf_size);
char	*append_char_to_line(char *line, char c, int len);
#endif 
