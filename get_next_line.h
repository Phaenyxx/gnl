/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: trifflet <trifflet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/16 16:17:02 by trifflet     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/12 15:49:26 by trifflet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <stdlib.h>
# include <unistd.h>

# define ERROR		-1
# define FILE_END	0
# define LINE_READ	1
# define NO_EOL		2

typedef struct	s_info
{
	int			state;
	char		*rest;
}				t_info;

size_t			ft_strclen(const char *str, char c);
int				wrap_read(int fd, char **buffer);
void			assemble(char **result, char *buffer);
int				get_next_line(int fd, char **line);

#endif
