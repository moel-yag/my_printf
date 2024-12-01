/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-yag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:25:14 by moel-yag          #+#    #+#             */
/*   Updated: 2024/11/28 20:25:17 by moel-yag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <fcntl.h>
int	print_format(char specifier, va_list ap)
{
	int        count;
    int         check;

	count = 0;
    check = 0;
    if (specifier == 'c')
        check = ft_putchar(va_arg(ap, int));
    else if (specifier == 's')
        check = ft_putstr(va_arg(ap, char *));
    else if (specifier == 'd' || specifier == 'i')
        check = ft_putnbr((long )va_arg(ap, int), 10, 0);
    else if (specifier == 'u')
        check = ft_putnbr(va_arg(ap, unsigned int), 10, 0);
    else if (specifier == 'x' || specifier == 'X')
        check = ft_putnbr(va_arg(ap, unsigned int), 16,specifier == 'x' );
    else if (specifier == 'p')
        check = ft_putaddr(va_arg(ap, unsigned long));
	else if (specifier == '%')
	    check = ft_putchar('%');
    if (check < 0)
        return (-1);
    count += check;
	return (count);
}

int is_valid_format(const char *fmt)
{
    if (fmt == NULL)
	return (0);
    while (*fmt!= '\0')
    {
        if (*fmt == '%')
        {
            ++fmt;
            if (*fmt != 'c' && *fmt != 's' && *fmt != 'd' 
            && *fmt != 'i' && *fmt != 'u' && *fmt != 'x' 
            && *fmt != 'X' && *fmt != 'p' && *fmt != '%')
                return (0);   
        }
        ++fmt;
    }
    return (1);
}

int	ft_printf(const char *fmt,...)
{
    va_list    ap;
    int        count;
    int         check;

    if (!is_valid_format(fmt))
        return (-1);
    va_start(ap, fmt);
	count = 0;
	while (*fmt != '\0')
	{
		if (*fmt == '%')
        {
                ++fmt;
            check = print_format(*fmt, ap);
        }
        else
			check = write(1, fmt, 1);
        if (check < 0)
            return (-1);
        count += check;
		++fmt;
	}
    va_end(ap);
    return (count);
}

int main()
{
    char * fmt = "%p";
    size_t num = 0xFFFFFFFFFFFFFFFFUL; 
    
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("Expected : \n");    
    printf("\tOutput   : ");    
    int a = printf(fmt, num);
    printf("\n\tReturn   : %d\n", a);

    printf("Got : \n");     
    printf("\tOutput   : ");     
     a = ft_printf(fmt, num);
  
    printf("\n\tReturn   : %d\n", a);

    printf("%d\n",sizeof(&a));
    // close(1);
    // int b = ft_printf(fmt, num);    
    // open("/dev/tty",O_WRONLY);
    // printf("%d,%d\n", a,b);
    return (0);
}
