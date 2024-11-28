#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

int print_char(int c)
{
	return (write(1, &c, 1));
}

int print_str(char *str)
{
	int count;

	count = 0;
	while (*str != '\0')
	{
		print_char((int)*str);
		++count;
		++str;
	}
	return (count);
}

int print_digit(long n, int base)
{
	int count;
	char *symbols;

	symbols = "0123456789abcdef";
	if (n < 0)
	{
		write(1, "-", 1);
		return (print_digit(-n, base) + 1);
	}
	else if (n < base)
		return (print_char(symbols[n]));
	else
	{
		count = print_digit(n / base, base);
		return (count + print_digit(n % base, base));
	}
}

int print_format(char specifier, va_list ap)
{
	int count;

	count = 0;
	if (specifier == 'c')
		count += print_char(va_arg(ap, int));
	else if (specifier == 's')
		count += print_str(va_arg(ap, char *));
	else if (specifier == 'd' || specifier == 'i')
		count += print_digit((long)va_arg(ap, int), 10);
	else if (specifier == 'x' || specifier == 'X')
		count += print_digit((long)va_arg(ap, unsigned int), 16);
	else
		count += write(1, &specifier, 1);
	return (count);
}

int ft_printf(const char *fmt, ...)
{
	va_list ap;
	int count;

	va_start(ap, fmt);
	count = 0;
	while (*fmt != '\0')
	{
		if (*fmt == '%')
			count += print_format(*(++fmt), ap);
		else
			count += write(1, fmt, 1);
		++fmt;
	}
	va_end(ap);
	return (count);
}

// int	main()
// {
// 	int count;
// 	// count = ft_printf("Hello %s\n", "John");
// 	// ft_printf("The chars witten are %d\n", count);
// 	// count = ft_printf("%x\n", 42);
// 	// ft_printf("The chars written are %d\n", count);

// 	ft_printf("Hello %s, today is %d, in hex %x, char ->%c\n",
// 			"Mohammed", 28, 28, 'y');

// 	return (0);
// }
