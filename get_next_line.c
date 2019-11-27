/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: trifflet <trifflet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/04 19:13:42 by trifflet     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/26 17:53:55 by trifflet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		check(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (NO_NL);
	while (str[i])
		if (str[i++] == '\n')
			return (FOUND_NL);
	if (i != 0)
		return (NO_NL);
	return (FILE_END);
}

void	save(char *str, t_info *info)
{
	int i;

	i = 0;
	while (*str++ != '\n')
		;
	if (!(info->rest = ft_calloc(BUFFER_SIZE, sizeof(char))))
		return ;
	while (*str)
		info->rest[i++] = *str++;
	info->rest[i] = '\0';
}

char	*get_rest(char *str)
{
	char	*st;
	int		i;

	i = 0;
	while (*str && *str++ != '\n')
		;
	if (!*str)
		return (NULL);
	if (!(st = ft_calloc(ft_strclen(str, '\0') + 1, sizeof(char))))
		return (NULL);
	while (*str)
		st[i++] = *str++;
	st[i] = '\0';
	return (st);
}

char	*read_and_split(int fd, t_info *info)
{
	char *ret;
	char *buf;

	ret = NULL;
	buf = NULL;
	if (info->rest)
	{
		ret = info->rest;
		info->rest = get_rest(info->rest);
		info->state = check(ret);
	}
	if (info->state == NO_NL || info->state == FILE_END)
	{
		if (!(buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char))))
			return (NULL);
		buf[BUFFER_SIZE] = '\0';
		read(fd, buf, BUFFER_SIZE);
	}
	info->state = check(buf);
	if (info->state == FOUND_NL)
		save(buf, info);
	if (!buf)
		info->state = check(ret);
	return (fusion(ret, buf));
}

int		get_next_line(int fd, char **line)
{
	static t_info	info[4096];

	*line = NULL;
	if (read(fd, 0, 0) < 0 || BUFFER_SIZE < 1)
		return (-1);
	info[fd].state = NO_NL;
	while (info[fd].state == NO_NL)
		*line = fusion(*line, read_and_split(fd, &info[fd]));
	return (info[fd].state == FILE_END ? 0 : 1);
}
