/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   test.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: trifflet <trifflet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/21 16:37:48 by trifflet     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/27 16:10:15 by trifflet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

#define RED "\033[0;31m"
#define YLW "\033[0;33m"
#define BLU "\033[0;34m"
#define MAG "\033[0;35m"
#define GRY "\033[0;90m"
#define RST "\033[0m"

int		call_gnl(int fd, int second)
{
	char	*text;
	int		ret;

	text = NULL;
	ret = get_next_line(fd, &text);
	if (second)
		printf(MAG"%d: "YLW"%-14p"RST" "MAG"|"GRY"%s"MAG"|"RST"\n",\
			ret, text, text);
	else
		printf(BLU"%d: "YLW"%-14p"RST" "RED"|"RST"%s"RED"|"RST"\n",\
			ret, text, text);
	free(text);
	return (ret);
}

void	close_fd(int fd1, int fd2, int ac)
{
	if (ac > 1)
		close(fd1);
	if (ac == 3)
		close(fd2);
}

int		main(int ac, char **av)
{
	int		fd1;
	int		fd2;
	int		control1;
	int		control2;
	char	pause[1];

	control1 = 1;
	control2 = 1;
	if (ac == 1)
		fd1 = 0;
	else
		fd1 = open(av[1], O_RDONLY);
	if (ac == 3)
		fd2 = open(av[2], O_RDONLY);
	else
		control2 = 0;
	while (control1 > 0 || control2 > 0)
	{
		if (control1 > 0)
			control1 = call_gnl(fd1, 0);
		if (control2 > 0)
			control2 = call_gnl(fd2, 1);
	}
	read(0, pause, 1);
	return (0);
}
