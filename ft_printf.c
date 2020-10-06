/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 15:23:59 by fsugimot          #+#    #+#             */
/*   Updated: 2020/08/27 08:56:54 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		output(const char *args, int front, int rear, va_list list)
{
	int			ret;
	t_dataset	*data;

	if (!(data = malloc(sizeof(t_dataset))))
		return (-1);
	ret = 0;
	if (parse_front(&data, args, front, list) == -1)
		return (-1);
	if (args[rear] == '%')
		ret += output_char(data, '%');
	if (args[rear] == 'c')
		ret += output_char(data, va_arg(list, int));
	if (args[rear] == 'i' || args[rear] == 'd')
		ret += output_num(data, va_arg(list, long long));
	if (args[rear] == 'u' || args[rear] == 'x' || args[rear] == 'X' ||\
		args[rear] == 'o')
		ret += output_unum(data, va_arg(list, unsigned int), \
			(args[rear] == 'x' || args[rear] == 'X') + ((args[rear] == 'X') << 1), (args[rear] == 'o'));
	if (args[rear] == 's')
		ret += output_str(data, va_arg(list, char *));
	if (args[rear] == 'p')
		ret += output_ptr(data, va_arg(list, long long unsigned int));
	return (ret);
}

int		ft_vprintf(const char *args, va_list list)
{
	int	ind;
	int	ret;
	int	tmp;

	ret = 0;
	ind = 0;
	while (args[ind])
	{
		if (args[ind] == '%')
		{
			tmp = ++ind;
			while (args[ind] && !is_terminator(args[ind]))
				ind++;
			tmp = output(args, tmp, ind++, list);
			if (tmp != -1)
				ret += tmp;
			else
				return (-1);
		}
		else
		{
			write(1, &args[ind++], 1);
			ret++;
		}
	}
	return (ret);
}

int		ft_printf(const char *args, ...)
{
	int		ret;
	va_list	list;

	ret = 0;
	va_start(list, args);
	ret = ft_vprintf(args, list);
	va_end(list);
	return (ret);
}
