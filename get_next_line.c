/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: trifflet <trifflet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/04 19:13:42 by trifflet     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/12 20:00:58 by trifflet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

void	reposition(t_info *info, int i)
{
	int	j;

	j = 0;
	if (info->rest[i] == '\n')
	{
		info->state = LINE_READ;
		i++;
	}
	if (info->rest[i])
	{
		while (info->rest[i])
			info->rest[j++] = info->rest[i++];
		info->rest[j] = '\0';
		info->state = LINE_READ;
	}
	else
	{
		free(info->rest);
		info->rest = NULL;
	}
}

int		retrieve(char **line, t_info *info)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!info->rest)
		*line = (char *)malloc(sizeof(char));
	else
	{
		if (!(*line = malloc(1 + ft_strclen(info->rest, '\n') * sizeof(char))))
			return (ERROR);
		while (info->rest[i] && info->rest[i] != '\n')
			(*line)[j++] = info->rest[i++];
		(*line)[j] = '\0';
		reposition(info, i);
	}
	(*line)[j] = '\0';
	return (info->state == LINE_READ ? LINE_READ : NO_EOL);
}

char	*get_rest(char *str)
{
	char	*returned;
	int		i;

	while (*str++ != '\n')
		;
	i = 0;
	if (!(returned = malloc(1 + ft_strclen(str, '\0') * sizeof(char))))
		return (NULL);
	while (str[i])
	{
		returned[i] = str[i];
		i++;
	}
	returned[i] = '\0';
	return (returned);
}

int		add(int fd, char **line, t_info *info)
{
	char *buffer;

	info->state = wrap_read(fd, &buffer);
	if (info->state == ERROR)
		return (ERROR);
	if (ft_strclen(buffer, '\n') != ft_strclen(buffer, '\0'))
	{
		if (!(info->rest = get_rest(buffer)))
		{
			free(buffer);
			return (ERROR);
		}
		info->state = LINE_READ;
	}
	assemble(line, buffer);
	if (!*line)
	{
		*line = malloc(sizeof(char));
		return (ERROR);
	}
	free(buffer);
	return (info->state);
}

int		get_next_line(int fd, char **line)
{
	static t_info	info[FD_SETSIZE];

	if (read(fd, 0, 0) < 0 || BUFFER_SIZE < 1 || !line)
	{
		*line = malloc(sizeof(char));
		return (ERROR);
	}
	info[fd].state = NO_EOL;
	info[fd].state = retrieve(line, &info[fd]);
	while (info[fd].state == NO_EOL)
		info[fd].state = add(fd, line, &info[fd]);
	return (info[fd].state);
}
