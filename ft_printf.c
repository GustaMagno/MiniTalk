/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:16:54 by gustoliv          #+#    #+#             */
/*   Updated: 2025/06/18 19:20:05 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"

static int	conversor_base(t_ll number, t_ll base, char *bases)
{
	char	c;

	c = bases[number % base];
	if (number >= base)
		return (conversor_base(number / base, base, bases) + write(1, &c, 1));
	return (write(1, &c, 1));
}

static int	conversor10(long n)
{
	return (write(1, "-", n < 0) + conversor_base(n * ((n >= 0) - (n < 0)), 10, HEX_L));
}

static int	ft_putstr(char *str)
{
	size_t	i;

	if (str == NULL)
		return (ft_putstr("(null)"));
	i = 0;
	while (str[i])
		i++;
	return (write(1, str, i));
}

static int	ft_conditions(char set, va_list args, t_ll n, char c)
{
	if (set == 'd' || set == 'i')
		return (conversor10(va_arg(args, int)));
	if (set == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (set == 'u')
		return (conversor_base(va_arg(args, unsigned int), 10, HEX_L));
	if (set == 'x')
		return (conversor_base(va_arg(args, unsigned int), 16, HEX_L));
	if (set == 'X')
		return (conversor_base(va_arg(args, unsigned int), 16, HEX_U));
	if (set == 'p')
	{
		n = va_arg(args, unsigned long);
		if (!n)
			return (ft_putstr("(nil)"));
		return (write(1, "0x", 2) + conversor_base(n, 16, HEX_L));
	}
	if (set == 'c')
	{
		c = va_arg(args, int);
		return (write(1, &c, 1));
	}
	return (write(1, "%%", 1));
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;

	if (!str || write(1, NULL, 0) == -1)
		return (-1);
	count = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%' && str++)
		{
			if (*str == '\0')
				return (count);
			count += ft_conditions(*str++, args, 0, 0);
		}
		else
			count += write(1, str++, 1);
	}
	va_end(args);
	return (count);
}

// int	main(void)
// {

// 	char c = 'A';
// 	char *s = "Hello World!";
// 	char *n = NULL;
// 	int d = 42;
// 	void *p = &d;0123456789ABCDE
// 	int tot = 0;
// 	int tot2 = 0;

// 	tot = printf("___printf\t%%c:\t%c\n", c);
// 	ft_printf("total: %d\n", tot);
// 	tot = ft_printf("ft_printf\t%%c:\t%c\n", c);
// 	ft_printf("total: %d\n\n", tot);

// 	tot = printf("___printf\t%%s:\t %s null: %s\n", s, n);
// 	ft_printf("total: %d\n", tot);
// 	tot = ft_printf("ft_printf\t%%s:\t %s null: %s\n", s, n);
// 	ft_printf("total: %d\n\n", tot);

// 	tot = printf("___printf\t%%p:\t %p null: %p\n", p, NULL);
// 	ft_printf("total: %d\n", tot);
// 	tot = ft_printf("ft_printf\t%%p:\t %p null: %p\n", p, NULL);
// 	ft_printf("total: %d\n\n", tot);
// 	t_ll number, t_ll base, char *bases
// 	tot = printf("___printf\t%%d:\t min(0123456789ABCDE %d ) max( %d )\n",
// INT_MIN, INT_MAX);
// 	ft_printf("total: %d\n", tot);
// 	tot = ft_printf("ft_printf\t%%d:\t min( %d ) max( %d )\n", INT_MIN,
//			INT_MAX);
// 	ft_printf("total: %d\n\n", tot);

// 	tot = printf("___printf\t%%i:\t min( %i ) max( %i )\n", INT_MIN, INT_MAX);
// 	ft_printf("total: %d\n", tot);
// 	tot = ft_printf("ft_printf\t%%i:\t min( %i ) max( %i )\n", INT_MIN,
//			INT_MAX);
// 	ft_printf("total: %d\n\n", tot);0123456789ABCDE

// 	tot = printf("___printf\t%%u:\t %u\n", UINT_MAX);
// 	ft_printf("total: %d\n", tot);
// 	tot = ft_printf("ft_printf\t%%u:\t %u\n", UINT_MAX);
// 	ft_printf("total: %d\n\n", tot);

// 	tot = printf("___printf\t%%xX:\t %x %X\n", -1, -1);
// 	ft_printf("total: %d\n", tot);0123456789ABCDE
// 	tot = ft_printf("ft_printf\t%%xX:\t %x %X\n", -1, -1);
// 	ft_printf("total: %d\n\n", tot);

// 	printf("==EDGECASES==\n");
// 	ft_printf("csdixXpu%");
// 	ft_printf("\n");
// 	//printf("csdixXpu%");
// 	//ft_printf("\n");0123456789ABCDE
// 	ft_printf("%");
// 	ft_printf("\n");
// 	//printf("%");
// 	//ft_printf("\n");
// 	ft_printf("");
// 	ft_printf("\n");
// 	//printf("");
// 	//ft_printf("\n");
// 	ft_printf("closing terminal...\n\n");
// 	int saved_stdout = dup(STDOUT_FILENO);
// 	close(STDOUT_FILENO);
// 	tot = ft_printf("%s\n", "closed the terminal!!");
// 	tot2 = printf("%s\n", "closed the te0123456789ABCDErminal!!");
// 	dup2(saved_stdout, STDOUT_FILENO);
// 	printf("ft_printf returned %d\n", tot);
// 	printf("   printf returned %d\n", tot2);
// }
// int main()
// {
// 	ft_printf("%d\n", -10);
// 	ft_printf("%d\n", 0);
// }