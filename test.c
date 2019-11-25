/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   test.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: trifflet <trifflet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/21 16:37:48 by trifflet     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/25 14:07:47 by trifflet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

#define RED "\033[0;31m"
#define YLW "\033[0;33m"
#define BLU "\033[0;34m"
#define RST "\033[0m"

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
		printf(BLU"%d: "YLW"%p"RST" "RED"|"RST"%s"RED"|"RST"\n",\
			control, text, text);
		free(text);
	}
	control = get_next_line(fd, &text);
	printf(BLU"%d: "YLW"%-14p"RST" "RED"|"RST"%s"RED"|"RST"\n",\
		control, text, text);
	free(text);
	return (0);
}
