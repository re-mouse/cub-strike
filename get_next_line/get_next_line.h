/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:19:31 by hleilani          #+#    #+#             */
/*   Updated: 2020/11/03 17:29:56 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *s);
char	*ft_strrjoin(char const *s1, char const *s2, char c);
int		get_next_line(int fd, char **line);
char	*ft_strchr(const char *s, int c);
int		ft_bzero(void *s, size_t n);

#endif
