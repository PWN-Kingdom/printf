#include "print.h"

int ft_printf(const char *format, ...);

int		main(void)
{
		int             a = -4;
        int             b = 0;
        char    c = 'a';
        int             d = 2147483647;
        int             e = -2147483648;
        int             f = 42;
        int             g = 25;
        int             h = 4200;
        int             i = 8;
        int             j = -12;
        int             k = 123456789;
        int             l = 0;
        int             m = -12345678;
        char    *n = "abcdefghijklmnop";
        char    *o = "-a";
        char    *p = "-12";
        char    *q = "0";
        char    *r = "%%";
        char    *s = "-2147483648";
        char    *t = "0x12345678";
        char    *u = "-0";

        ft_printf("!!!!\n");
        ft_printf("%lld\n", LONG_MAX, ULLONG_MAX, ULLONG_MAX, ULLONG_MAX);
        printf("%lld\n", LONG_MAX, ULLONG_MAX, ULLONG_MAX, ULLONG_MAX);
        ft_printf("!!!!\n");
		ft_printf("!%.*s!", -3, "hello");
		ft_printf("\n");
		printf("%.*s", -3, "hello");
		ft_printf("\n");
	return 0;
}