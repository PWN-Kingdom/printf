#ifndef _HEADER_FILE_H_
#define _HEADER_FILE_H_

# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <limits.h>
# include <stdint.h>
# include <wchar.h>

typedef struct
{
	char		sign;					// Знак
	char		spase;					// ' '
	char		octo;					// #
	char		orientation;			// Ориентация:	право/лево
	char		size_type;				// l ll h hh
	char		width_value;			// Заполнение ширины ' '/0
	long int	width;					// Ширина
	long int	accuracy;				// Точность
	long int	len;					// Возвращаемая длина
	size_t		i;						// Индекс
}		t_param;

void	ft_recovery_structure(t_param *f_param);

void	print_width(int width, int len_word, char sumbol, t_param *f_param);
void	print_char(va_list ap, t_param *f_param);
void	print_string(char *str, t_param *f_param);
unsigned long long int	for_u_x(va_list ap, t_param *f_param);
void	print_hex(unsigned long long int n, t_param *f_param, char *hex, char f, char *x);
void	print_hex_number(unsigned long int number, char *hex_value, t_param *f_param);
void	print_ptr(va_list ap, t_param *f_param, char *hex_numbers);
void	print_int(long long int, t_param *f_param);
void	print_unsigned_int(unsigned long long int n, t_param *f_param);
void	print_persent(char c, t_param *f_param);

long long int	for_d_i(va_list ap, t_param *f_param);
unsigned long long int	for_u_x(va_list ap, t_param *f_param);

int		ft_isalnum(int c);
int		ft_isdigit(int c);
long int	ft_strlen(const char *s);
size_t	ft_len_number(unsigned long int number, int base);
size_t	ft_len_number_d(long long int number, int base);

#endif //_HEADER_FILE_H_
