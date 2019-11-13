/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: trifflet <trifflet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/16 16:17:02 by trifflet     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/12 19:40:51 by trifflet    ###    #+. /#+    ###.fr     */
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
# define FOUND_NL	1
# define NO_NL		2
# define FILE_END	3

typedef struct	s_info
{
	int			state;
	char		*stocks;
}				t_info;

void			*ft_calloc(size_t count, size_t size);
int				get_next_line(int fd, char **line);
void			save(char *str, t_info *info);
char			*fusion(char *str, char *to_add);

#endif
