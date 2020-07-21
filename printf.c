/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: white <white@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 04:29:11 by white             #+#    #+#             */
/*   Updated: 2020/07/21 06:14:47 by white            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	ft_find_start_format(char *format, t_param *f_param)
{
	while (format[f_param->i] != '%')
	{
		if (format[f_param->i] == '\0')
			break ;
		f_param->len += write(1, format + f_param->i, 1);
		f_param->i += 1;
	}
}

int		ft_find_signs(int j, char *format, t_param *f_param)
{
	while (ft_isalnum(format[j]) == 0 || format[j] == '0')
	{
		if (format[j] == '*' || format[j] == '.' || format[j] == '%')
			break ;
		if (format[j] == '+')
			f_param->sign = '+';
		else if (format[j] == '-')
			f_param->orientation = 'l';
		else if (format[j] == '#')
			f_param->octo = '#';
		else if (format[j] == ' ')
			f_param->spase = ' ';
		else if (format[j] == '0' && f_param->width == 0 && f_param->accuracy == -1)
			f_param->width_value = '0';
		else
			return (-1);
		j++;
	}
	return (j);
}

int		ft_find_width(va_list ap, int j, char *format, t_param *f_param)
{
	if (format[j] == '*')
	{
		f_param->width = va_arg(ap, int);
		if (f_param->width < 0)
		{
			f_param->orientation = 'l';
			f_param->width *= -1;
		}
		return(j + 1);
	}
	if (format[j] == '0')
		f_param->width_value = '0';
	while (ft_isdigit(format[j]) != 0)
	{
		if (f_param->width > INT_MAX)
			return (-1);
		f_param->width = f_param->width * 10 + format[j] - 48;
		j++;
	}
	return (j);
}

int		ft_find_accuracy(va_list ap, int j, char *format, t_param *f_param)
{
	if (format[j] == '.')
		j++;
	else
		return (j);
	if (format[j] == '*')
	{
		f_param->accuracy = va_arg(ap, int);
		return (j + 1);
	}
	f_param->accuracy = 0;
	while (ft_isdigit(format[j]) != 0)
	{
		if (f_param->accuracy > INT_MAX)
			return (-1);
		f_param->accuracy = f_param->accuracy * 10 + format[j] - 48;
		j++;
	}
	return (j);
}

int		ft_find_size(int j, char *format, t_param *f_param)
{
	if (format[j] == 'l')
	{
		if (format[j + 1] != 'l' )
			f_param->size_type = 1;
		else
			f_param->size_type = 2;
	}
	else if (format[j] == 'h')
	{
		if (format[j + 1] != 'h')
			f_param->size_type = 11;
		else
			f_param->size_type = 12;
	}
	return (j + f_param->size_type % 10);
}

int		ft_format_print(va_list ap, int j, char *format, t_param *f_param)
{
	if (format[j] == 'c')
		print_char(ap, f_param);
	else if (format[j] == 's')
		print_string(va_arg(ap, char *), f_param);
	else if (format[j] == 'x')
		print_hex(for_u_x(ap, f_param), f_param, "0123456789abcdef", 0);
	else if (format[j] == 'X')
		print_hex(for_u_x(ap, f_param), f_param, "0123456789ABCDEF", 0);
	else if (format[j] == 'p')
		print_hex(va_arg(ap, unsigned long int), f_param, "0123456789abcdef", 1);
	else if (format[j] == 'd' || format[j] == 'i')
		print_int(for_d_i(ap, f_param), f_param);
	else if (format[j] == 'u')
		print_unsigned_int(for_u_x(ap, f_param), f_param);
	else if (format[j] == '%')
		print_persent('%', f_param);
	else
		j = -1;

	return (j);
}

char	init_and_print(va_list ap, char *format, t_param *f_param)
{
	int	j;

	j = f_param->i + 1;
	if ((j = ft_find_signs(j, format, f_param)) == -1)
		return (-1);
	if ((j = ft_find_width(ap, j, format, f_param)) == -1)
		return (-1);
	if ((j = ft_find_accuracy(ap, j, format, f_param)) == -1)
		return (-1);
	j = ft_find_size(j, format, f_param);
	if ((j = ft_format_print(ap, j, format, f_param)) == -1)
		return (-1);
	
	//printf("\nwidth    = %ld\n", f_param->width);
	//printf("accuracy = %ld\n", f_param->accuracy);
	//printf("size_type = %d\n", f_param->size_type);

	f_param->i = j + 1;
	return (1);
}

size_t	ft_vprintf(va_list ap, char *format)
{
	t_param *f_param;

	if ((f_param = (t_param *)malloc(sizeof(t_param))) == NULL)
		return (0);
	f_param->len = 0;
	f_param->i = 0;
	ft_find_start_format(format, f_param);
	while (format[f_param->i] != '\0')
	{
		ft_recovery_structure(f_param);
		if (init_and_print(ap, format, f_param) == -1)
		{
			f_param->len += write(1, format + f_param->i, 1);
			f_param->i += 1;
		}
		ft_find_start_format(format, f_param);
	}
	free(f_param);
	return (f_param->len);
}

int		ft_printf(const char *format, ...)
{
	int			result;
	va_list		ap;

	if (format == NULL)
		return (-1);
	va_start(ap, format);
	result = ft_vprintf(ap, (char *)format);
	va_end(ap);
	return (result);
}
