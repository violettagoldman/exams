/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:40:09 by vgoldman          #+#    #+#             */
/*   Updated: 2019/12/04 19:36:13 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct	s_format
{
	int		size;
	int		width;
	int		wd;
	int		sd;
	char	spec;
}				t_format;

void	handle_format(char **ptr, va_list args, int *count);
int		ft_atoi(char **str);
int		isdigit(int n);
int		ft_abs(int n);
void	ft_putnchar(char c, int n, int *count);
int		ft_strlen(char *str);
void	ft_putnbr(long int nb, int *count);
void	ft_puthexa(long int nb, int *count);
void	ft_putnstr(char *str, int n, int *count);
void	ft_string(char *str, t_format *format, int *count);
void	ft_int(int i, t_format *format, int *count);
int		len_nb(long int n);
void	ft_hexa(long int i, t_format *format, int *count);

int		ft_printf(const char *format, ...)
{
	int		count;
	char	*ptr;
	va_list	args;

	count = 0;
	ptr = (char *)format;
	va_start(args, format);
	while (*ptr)
	{
		if (*ptr == '%')
		{
			ptr++;
			handle_format(&ptr, args, &count);
		}
		else
			ft_putnchar(*(ptr++), 1, &count);
	}
	va_end(args);
	return (count);
}

void	handle_format(char **ptr, va_list args, int *count)
{
	t_format format;

	format.size = 0;
	format.width = 0;
	format.wd = 0;
	format.sd = 0;
	if (isdigit(**ptr))
	{
		format.width = ft_atoi(ptr);
		format.wd = 1;
	}
	if (**ptr == '.')
	{
		(*ptr)++;
		format.size = ft_atoi(ptr);
		format.sd = 1;
	}
	format.spec = **ptr;
	if (**ptr != '\0')
		(*ptr)++;
	if (format.spec == 's')
		ft_string(va_arg(args, char*), &format, count);
	else if (format.spec == 'd')
		ft_int(va_arg(args, int), &format, count);
	else if (format.spec == 'x')
		ft_hexa(va_arg(args, int), &format, count);
}

int		ft_atoi(char **str)
{
	int res;
	int sign;

	sign = 1;
	res = 0;
	if (**str == '-')
	{
		sign *= -1;
		(*str)++;
	}
	while (isdigit(**str) && **str)
	{
		res = (res * 10) + (**str - '0');
		(*str)++;
	}
	return (res * sign);
}

int		isdigit(int n)
{
	return (n <= '9' && n >= '0');
}

int ft_abs(int n)
{
	return (n < 0 ? -n : n);
}

void	ft_putnchar(char c, int n, int *count)
{
	int i;

	i = 0;
	while (i < n)
	{
		write(1, &c, 1);
		(*count)++;
		i++;
	}
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putnbr(long int nb, int *count)
{
	long int a;

	a = nb;
	if (a < 0)
		a = a * (-1);
	if (a > 9)
	{
		ft_putnbr(a / 10, count);
		ft_putnchar(a % 10 + '0', 1, count);
	}
	else
		ft_putnchar(a + '0', 1, count);
}

void	ft_puthexa(long int nb, int *count)
{
	long int a;
	char *str;

	str = "0123456789abcdef";
	a = nb;
	if (a > 15)
	{
		ft_puthexa(a / 16, count);
		ft_putnchar(*(a % 16 + str), 1, count);
	}
	else
		ft_putnchar(*(a + str), 1, count);
}

void	ft_putnstr(char *str, int n, int *count)
{
	int i;

	i = 0;
	while (i < n)
	{
		ft_putnchar(str[i], 1, count);
		i++;
	}
}

int		len_nb(long int n)
{
	long int i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i + 1);
}

int		len_nb_hexa(long int n)
{
	int i;

	i = 0;
	while (n >= 16)
	{
		n /= 16;
		i++;
	}
	return (i + 1);
}

void	ft_string(char *str, t_format *format, int *count)
{
	int fill;
	int len;
	int i;

	if (str == NULL)
	{
		ft_string("(null)", format, count);
		return ;
	}
	fill = 0;
	len = ft_strlen(str);
	i = 0;
	if (format->sd && format->size < len)
		len = format->size;
	if (format->wd && format->width > len)
		fill = format->width - len;
	ft_putnchar(' ', fill, count);
	ft_putnstr(str, len, count);
}

void	ft_int(int i, t_format *format, int *count)
{
	long int n = i;
	int len = len_nb(n);
	int fill_s = 0;
	int fill_z = 0;

	if (format->sd && format->size > len)
		fill_z = format->size - len + (n < 0);
	if (format->wd && format->width > fill_z + len)
		fill_s = format->width - fill_z - len;
	ft_putnchar(' ', fill_s, count);
	if (i < 0)
		ft_putnchar('-', 1, count);
	ft_putnchar('0', fill_z, count);
	//if (!(format->sd && !format->size && !n))
	ft_putnbr(n, count);
}

void	ft_hexa(long int i, t_format *format, int *count)
{
	if (i < 0)
		i += 4294967296;
	int len = len_nb_hexa(i);
	int fill_s = 0;
	int fill_z = 0;

	if (format->sd && format->size > len)
		fill_z = format->size - len;
	if (format->wd && format->width > fill_z + len)
		fill_s = format->width - fill_z - len;
	ft_putnchar(' ', fill_s, count);
	ft_putnchar('0', fill_z, count);
	ft_puthexa(i, count);
}

#include <stdio.h>

int main(void)
{
	//char *c = "15.2";
	//printf("|%d|", ft_atoi(&c));
	printf("|%d|", printf("%15.10x\n", -2147483647));
	printf("|%d|", ft_printf("%15.10x\n", -2147483647));
	return (0);
}
