/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:17:10 by vgoldman          #+#    #+#             */
/*   Updated: 2019/12/03 12:37:08 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		isn(char c, char *s)
{
	int i;

	i = 0;
	while (s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

void	inter(char *s1, char *s2)
{
	int printed[256] = {0};
	int i;

	i = 0;
	while (s1[i])
	{
		if (isn(s1[i], s2) && !printed[(int)s1[i]])
		{
			printed[(int)s1[i]] = 1;
			write(1, &s1[i], 1);
		}
		i++;
	}
}

int		main(int argc, char **argv)
{
	if (argc == 3)
		inter(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}
