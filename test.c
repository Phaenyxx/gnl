/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   test.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: trifflet <trifflet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/21 16:37:48 by trifflet     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/06 14:45:33 by trifflet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	char	*text;
	int		fd;
	int		control;

	control = 1;
	text = NULL;
	if (ac == 1)
	fd = 0;
	else
	fd = open(av[1], O_RDONLY);
	while (control > 0)
	{
		control = get_next_line(fd, &text);
		printf("%d, %s\n", control, text);
		free(text);
	}
	return (0);
}
