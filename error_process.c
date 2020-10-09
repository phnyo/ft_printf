/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 00:55:06 by fsugimot          #+#    #+#             */
/*   Updated: 2020/10/10 02:17:10 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		process_invalid_str(const char *args, int front)
{
	int		flg;
	int		ind;
	char	*str;

	flg = fill_flg(args, front);
	str = malloc(ft_strlen(args) + 2);
	ind = 0;
	if (!str)
		return (-1);
	str[ft_strlen(args) + 1] = 0;
	str[ind++] = '%';
	str[ind++] = flg & ZERO_FLG ? '0' : '-';
	str[ind++] = '.';
	while (args[front] != '.')
		front++;
	if (args[++front] == '-' || args[front] == '.')
		str[ind++] = '0';
	str_cpy(args, &str, front, ind);
	ind = ft_strlen(str);
	write(1, str, ind);
	free(str);
	return (ind);
}

void	str_cpy(const char *args, char **str, int a_ind, int s_ind)
{
	char	*tmp;

	tmp = *str;
	while (args[a_ind] && !is_terminator(args[a_ind]))
	{
		tmp[s_ind++] = args[a_ind++];
	}
	tmp[s_ind++] = args[a_ind++];
	tmp[s_ind] = 0;
}
