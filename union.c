/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:40:42 by vgoldman          #+#    #+#             */
/*   Updated: 2019/12/03 12:53:05 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		isn(char c, char *s)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

void	ft_union(char *s1, char *s2)
{
	int i;
	int printed[256] = {0};

	i = 0;
	while (s1[i])
	{
		if ((isn(s1[i], s1) || isn(s1[i], s2)) && !printed[(int)s1[i]])
		{
			printed[(int)s1[i]] = 1;
			write(1, &s1[i], 1);
		}
		i++;
	}
		i = 0;
	while (s2[i])
	{
		if ((isn(s2[i], s1) || isn(s2[i], s2)) && !printed[(int)s2[i]])
		{
			printed[(int)s2[i]] = 1;
			write(1, &s2[i], 1);
		}
		i++;
	}
}

int		main(int argc, char **argv)
{
	if (argc == 3)
		ft_union(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}
