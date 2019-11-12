/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_utils.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: trifflet <trifflet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/21 16:34:43 by trifflet     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/06 13:31:13 by trifflet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strnllen(const char *str)
{
	return ((*str && *str != '\n') ? 1 + ft_strnllen(str + 1) : 0);
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
	while (i < size * count)
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
	if (!(cpy = ft_calloc(ft_strnllen(s1) + 1, sizeof(char))))
		return (NULL);
	while (i < ft_strnllen(s1))
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
	char *st;

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
	if (!(st = ft_calloc((ft_strnllen(str) + ft_strnllen(to_add)) + 1,\
		sizeof(char))))
		return (NULL);
	ft_memcpy(st, str, ft_strnllen(str));
	ft_memcpy(st + ft_strnllen(str), to_add, ft_strnllen(to_add));
	*(st + ft_strnllen(str) + ft_strnllen(to_add)) = '\0';
	free(to_add);
	free(str);
	return (st);
}
