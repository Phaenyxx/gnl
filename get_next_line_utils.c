/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_utils.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: trifflet <trifflet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/12 16:32:20 by trifflet     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/12 18:19:49 by trifflet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

size_t			ft_strclen(const char *str, char c)
{
    return (*str && *str != c ? 1 + ft_strclen(str + 1, c) : 0);
}

int				wrap_read(int fd, char **buffer)
{
    int value;

    if (!(*buffer = malloc((BUFFER_SIZE + 1) * sizeof(char))))
        return (ERROR);
    value = read(fd, *buffer, BUFFER_SIZE);
    (*buffer)[value] = '\0';
    return (value < BUFFER_SIZE ? FILE_END : NO_EOL);
}

void			assemble(char **result, char *buffer)
{
    char    *old_string;
    int     len;
    int     i;

    i = -1;
    old_string = *result;
    len = ft_strclen(*result, '\0');
    if (!(*result = malloc((len + ft_strclen(buffer, '\n') + 1)* sizeof(char))))
    {
        free(old_string);
        *result = NULL;
        return ;
    }
    while (++i < len)
        (*result)[i] = old_string[i];
    while (*buffer && *buffer != '\n')
        (*result)[i++] = *buffer++;
    (*result)[i] = '\0';
    free(old_string);
}