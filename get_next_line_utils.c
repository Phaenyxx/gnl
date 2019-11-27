/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_utils.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: trifflet <trifflet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/21 16:34:43 by trifflet     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/26 17:48:41 by trifflet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

size_t	ft_strclen(const char *str, char c)
{
	return ((*str && *str != c) ? 1 + ft_strclen(str + 1, c) : 0);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*mem;
	unsigned char	*meh;
	size_t			i;

	if (!(mem = malloc(size * count)))
		return (NULL);
	meh = (unsigned char *)mem;
	i = 0;
	while (i < size * count && BUFFER_SIZE < 100000000)
		meh[i++] = 0;
	return (mem);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*cdst;
	char	*csrc;

	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	cdst = (char *)dst;
	csrc = (char *)src;
	while (i < n)
	{
		cdst[i] = csrc[i];
		i++;
	}
	return (dst);
}

char	*ft_strnldup(char *s1)
{
	size_t	i;
	char	*cpy;

	i = 0;
	if (!(cpy = ft_calloc(ft_strclen(s1, '\n') + 1, sizeof(char))))
		return (NULL);
	while (i < ft_strclen(s1, '\n'))
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	free(s1);
	return (cpy);
}

char	*fusion(char *str, char *to_add)
{
	char	*st;
	size_t	slen;
	size_t	tlen;

	st = NULL;
	if (!str && !to_add)
	{
		st = ft_calloc(1, sizeof(char));
		return (ft_strnldup(st));
	}
	if (!str)
		return (ft_strnldup(to_add));
	if (!to_add)
		return (ft_strnldup(str));
	slen = ft_strclen(str, '\n');
	tlen = ft_strclen(to_add, '\n');
	if (!(st = ft_calloc(slen + tlen + 1, sizeof(char))))
		return (NULL);
	ft_memcpy(st, str, slen);
	ft_memcpy(st + slen, to_add, tlen);
	*(st + slen + tlen) = '\0';
	free(to_add);
	free(str);
	return (st);
}
