/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: trifflet <trifflet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/04 19:13:42 by trifflet     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/25 18:23:34 by trifflet    ###    #+. /#+    ###.fr     */
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
	if (!(info->stocks = ft_calloc(BUFFER_SIZE, sizeof(char))))
	{
		info->state = ERROR;
		return ;
	}
	while (*str)
		info->stocks[i++] = *str++;
	info->stocks[i] = '\0';
}

char	*rest(char *str)
{
	char	*st;
	int		i;

	i = 0;
	while (*str++ != '\n' && *str)
		;
	if (!(st = ft_calloc(BUFFER_SIZE, sizeof(char))))
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
	if (info->stocks)
	{
		ret = info->stocks;
		info->stocks = rest(info->stocks);
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
	int				keep;
	char			*rdline;
	static t_info	*info[4096];

	if (read(fd, 0, 0) < 0 || BUFFER_SIZE < 1)
		return (-1);
	if (!(rdline = NULL) && !info[fd])
	{
		if (!(info[fd] = ft_calloc(1, sizeof(t_info))))
			return (ERROR);
		info[fd]->state = NO_NL;
		info[fd]->stocks = NULL;
	}
	rdline = fusion(rdline, read_and_split(fd, info[fd]));
	while (info[fd]->state == NO_NL)
		rdline = fusion(rdline, read_and_split(fd, info[fd]));
	*line = rdline;
	if (!(keep = info[fd]->state - FILE_END) && info[fd]->stocks)
	{
		free(info[fd]);
		info[fd] = NULL;
	}
	else if (!keep)
		*line = NULL;
	return (keep ? 1 : 0);
}
