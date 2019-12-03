/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:40:09 by vgoldman          #+#    #+#             */
/*   Updated: 2019/12/03 16:25:18 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

typedef struct	s_format
{
	int		size;
	int		width;
	char	spec;
}				t_format;

void	handle_format(char **ptr, va_list args, int *count);
void	ws(char **ptr, t_format *format, va_list args);
int		ft_atoi(char **str);
int		isdigit(int n);
int		ft_abs(int n);
void	ft_putnchar(char c, int n, int *count);
int		ft_strlen(char *str);
void	ft_putnbr(int nb, int *count);
void	ft_puthexa(long int nb, int *count);
void	ft_putnstr(char *str, int n, int *count);
void	ft_string(char *str, t_format *format, int *count);
void	ft_int(int i, t_format *format, int *count);
int		len_nb(int n);

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
	ws(ptr, &format, args);
	format.spec = **ptr;
	if (**ptr != '\0')
		(*ptr)++;
	if (format.spec == 's')
		ft_string(va_arg(args, int), &format, count);
	else if (format.spec == 'd')
		ft_int(va_arg(args, char*), &format, count);
	else if (format.spec == 'x')
		ft_hexa(va_arg(args, int), &format, count);
}

void	ws(char **ptr, t_format *format, va_list args)
{
	if (**ptr == '*')
	{
		format->width = va_arg(args, int);
		(*ptr)++;
	}
	else if (isdigit(**ptr))
		format->width = ft_atoi(ptr);
	if (**ptr == '.')
	{
		(*ptr)++;
		if (**ptr == '*')
		{
			format->size = va_arg(args, int);
			(*ptr)++;
		}
		else
			format->size = ft_atoi(ptr);
	}
}

int		ft_atoi(char **str)
{
	int res;
	int sign;

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

void	ft_putnbr(int nb, int *count)
{
	int a;

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

int		len_nb(int n)
{
	int i;

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

void	ft_string(char *str, t_format *format, int *count)
{
	int fill;
	int print_len;

	if (str == NULL)
	{
		ft_string("(null)", format, count);
		return ;
	}
	if (ft_abs(format->size) < ft_strlen(str) && format->size)
		print_len = ft_abs(format->size);
	else
		print_len = ft_strlen(str);
	fill = ft_abs(format->width) - print_len;
	ft_putnchar(' ', fill, count);
	ft_putnstr(str, print_len, count);
}

void	ft_int(int i, t_format *format, int *count)
{
	int fill_spaces;
	int fill_zeros;

	if (format->size >= len_nb(i) || (format->width && format->size))
		fill_zeros = ft_abs(format->size) - len_nb(i) + (i < 0 && format->size > 0);
	else if (format->width > 0)
		fill_zeros = ft_abs(format->width) - len_nb(i);
	if (ft_abs(format->width) > len_nb + fill_zeros)
	{
		fill_spaces = ft_abs(format->width) - len_nb(i) - (fill_zeros < 0 ? 0 : fill_zeros);
	}
	if (i < 0)
		ft_putnchar('-', 1, count);
	ft_putnchar('0', fill_zeros, count);
	ft_putnbr(i, count);
}
