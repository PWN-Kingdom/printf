/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: white <white@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 05:07:31 by white             #+#    #+#             */
/*   Updated: 2020/07/21 06:01:33 by white            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	ft_recovery_structure(t_param *f_param)
{
	f_param->sign = 0;
	f_param->spase = 0;
	f_param->octo = 0;
	f_param->orientation = 'r';
	f_param->size_type = 0;
	f_param->width_value = ' ';
	f_param->width = 0;
	f_param->accuracy = -1;
}

void	print_width(int width, int len_word, char sumbol, t_param *f_param)
{
	while (len_word < width)
	{
		f_param->len += write(1, &sumbol, 1);
		len_word += 1;
	}
}

void	print_char(va_list ap, t_param *f_param)
{
	char	c;

	c = (char)va_arg(ap, int);
	if (f_param->orientation == 'r')
		print_width(f_param->width, 1, ' ', f_param);
	f_param->len += write(1, &c, 1);
	if (f_param->orientation == 'l')
		print_width(f_param->width, 1, ' ', f_param);
}

void	print_string(char *str, t_param *f_param)
{
	if (str == NULL && f_param->accuracy < 6 && f_param->accuracy != -1)
			f_param->accuracy = 0;
	if (str == NULL)
		str = "(null)";
	if (f_param->accuracy == -1 || f_param->accuracy > ft_strlen(str))
		f_param->accuracy = ft_strlen(str);
	f_param->width -= f_param->accuracy;
	if (f_param->orientation == 'r')
		print_width(f_param->width, 0, ' ', f_param);
	while (*str != '\0' && f_param->accuracy-- > 0)
		f_param->len += write(1, str++, 1);
	if (f_param->orientation == 'l')
		print_width(f_param->width, 0, ' ', f_param);	
}

unsigned long long int	for_u_x(va_list ap, t_param *f_param)
{
	unsigned long long int number;

	if (f_param->size_type == 1)
		number = va_arg(ap, unsigned long int);
	else if (f_param->size_type == 2)
		number = va_arg(ap, unsigned long long int);
	else if (f_param->size_type == 11)
		number = (unsigned short int)va_arg(ap, unsigned int);
	else if (f_param->size_type == 12)
		number = (unsigned char)va_arg(ap, unsigned int);
	else
		number = va_arg(ap, unsigned int);
	return (number);
}

void	print_hex(unsigned long long int n, t_param *f_param, char *hex, char f)
{
	int		len;

	len = ft_len_number(n, 16);
	f_param->width -= (f_param->accuracy - len > 0) ? f_param->accuracy : len;
	if (n == 0 && f_param->accuracy < 0)
		f_param->width -= 1;
	if ((f_param->octo == '#' && n != 0) || f == 1)
		f_param->width -= 2;
	if (f_param->orientation == 'r')
		if (f_param->accuracy >= 0 || f_param->width_value == ' ')
			print_width(f_param->width, 0, ' ', f_param);
	if ((f_param->octo == '#' && n != 0) || f == 1)
		f_param->len += write(1, "0x", 2);
	if (f_param->orientation == 'r')
		if (f_param->accuracy < 0 && f_param->width_value == '0')
			print_width(f_param->width, 0, '0', f_param);
	f_param->accuracy -= len;
	if (n == 0 && f_param->accuracy < 0)
		f_param->accuracy = 1;
	print_width(f_param->accuracy, 0, '0', f_param);
	print_hex_number(n, hex, f_param);
	if (f_param->orientation == 'l')
		print_width(f_param->width, 0, ' ', f_param);
}

long long int	for_d_i(va_list ap, t_param *f_param)
{
	long long int number;

	if (f_param->size_type == 1)
		number = va_arg(ap, long int);
	else if (f_param->size_type == 2)
		number = va_arg(ap, long long int);
	else if (f_param->size_type == 11)
		number = (short int)va_arg(ap, int);
	else if (f_param->size_type == 12)
		number = (char)va_arg(ap, int);
	else
		number = va_arg(ap, int);
	return (number);
}

void	ft_putnbr(long long int n, t_param *f_param)
{
	int	max;
	int	symbol;

	max = 1000000000;
	if (n < 0)
		max = -1000000000;
	//if (n == 0)
	//	write(1, "0", 1);
	//else
	if (n != 0)
	{
		while (n / max == 0)
			max = max / 10;
		while (max)
		{
			symbol = n / max + '0';
			f_param->len += write(1, &symbol, 1);
			n = n % max;
			max = max / 10;
		}
	}
}

void	print_int_width(long long int n, int len, t_param *f_param)
{
	if (n < 0 || f_param->sign == '+' || f_param->spase == ' ')
		f_param->width -= 1;
	f_param->width -= (f_param->accuracy - len > 0) ? f_param->accuracy : len;
	if (n == 0 && f_param->accuracy < 0)
		f_param->width -= 1;
	if (f_param->orientation == 'r')
		if (f_param->accuracy >= 0 || f_param->width_value == ' ')
			print_width(f_param->width, 0, ' ', f_param);
}

void	print_int(long long int n, t_param *f_param)
{
	int		len;

	len = ft_len_number_d(n, 10);
	print_int_width(n, len, f_param);
	if (n < 0)
		f_param->len += write(1, "-", 1);
	else if (f_param->sign == '+')
		f_param->len += write(1, "+", 1);
	else if (f_param->spase == ' ')
		f_param->len += write(1, " ", 1);
	if (f_param->orientation == 'r')
		if (f_param->accuracy < 0 && f_param->width_value == '0')
			print_width(f_param->width, 0, '0', f_param);
	f_param->accuracy -= len;
	if (n == 0 && f_param->accuracy < 0)
		f_param->accuracy = 1;
	print_width(f_param->accuracy, 0, '0', f_param);
	ft_putnbr(n, f_param);
	if (f_param->orientation == 'l')
		print_width(f_param->width, 0, ' ', f_param);
}

void	print_unsigned_int(unsigned long long int n, t_param *f_param)
{
	int		len;
	len = ft_len_number_d(n, 10);
	print_int_width(n, len, f_param);
	if (f_param->orientation == 'r')
		if (f_param->accuracy < 0 && f_param->width_value == '0')
			print_width(f_param->width, 0, '0', f_param);
	f_param->accuracy -= len;
	if (n == 0 && f_param->accuracy < 0)
		f_param->accuracy = 1;
	print_width(f_param->accuracy, 0, '0', f_param);
	ft_putnbr(n, f_param);
	if (f_param->orientation == 'l')
		print_width(f_param->width, 0, ' ', f_param);
}

void	print_persent(char c, t_param *f_param)
{
	if (f_param->orientation == 'r')
		print_width(f_param->width, 1, ' ', f_param);
	f_param->len += write(1, &c, 1);
	if (f_param->orientation == 'l')
		print_width(f_param->width, 1, ' ', f_param);
}

int		ft_isalnum(int c)
{
	if (c >= '0' && c <= '9')
		return (8);
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (8);
	return (0);
}

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}

long int	ft_strlen(const char *s)
{
	long int len;

	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}

size_t	ft_len_number_d(long long int number, int base)
{
	size_t	len;

	len = 0;
	while (number != 0)
	{
		len += 1;
		number = number / base;
	}
	return (len);
}

size_t	ft_len_number(unsigned long int number, int base)
{
	size_t	len;

	len = 0;
	while (number != 0)
	{
		len += 1;
		number = number / base;
	}
	return (len);
}

void	print_hex_number(unsigned long int number, char *hex_value, t_param *f_param)
{
	size_t	i;
	char	hex_number[16];

	i = 15;
	while (number != 0)
	{
		hex_number[i] = hex_value[number % 16];
		number = number / 16;
		i--;
	}
	while (++i <= 15)
		f_param->len += write(1, &hex_number[i], 1);
}
