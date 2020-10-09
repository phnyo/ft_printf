/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 17:00:20 by fsugimot          #+#    #+#             */
/*   Updated: 2020/10/09 23:42:58 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define SIGNED 1
# define NUM 2
# define CHAR 4
# define MIN_FLG 1
# define SPC_FLG 2
# define POS_FLG 4
# define SHA_FLG 8
# define ZERO_FLG 16
# define ZERO_PREC 32
# define MIN_FIELD 64
# define PTR_FLG 128
# define CHAR_NULL_FLG 256

typedef struct		s_dataset
{
	int	flg;
	int	width;
	int	precision;
	int	prefix;
	int	datatype;
}					t_dataset;

int					count_digit(long long int num, int div);
char				*num_to_str(long long int num);
char				*u_num_to_str(unsigned long long int num, int is_hex, \
					int is_oct);
int					str_to_int(const char *str, int *front, t_dataset **data);
int					output_ptr(t_dataset *data, unsigned long long int ptr);
int					output_char(t_dataset *data, char c);
int					output_num(t_dataset *data, int nbr);
int					output_unum(t_dataset *data, unsigned int nbr, int is_hex, \
					int is_oct);
int					output_str(t_dataset *data, const char *content);
int					fill_field(const char *args, int *front, t_dataset **data, \
					int rot);
int					fill_flg(const char *str, int front);
int					parse_front(t_dataset **data, const char *args, \
								int front, va_list list);
void				fill_neg_flgs(t_dataset **data, int val, int is_prec);
int					is_terminator(const char c);
int					is_flg(char c);
int					process_w_p(t_dataset *data, char **str);
int					process_flg(t_dataset *data, char **str);
int					process_fmt(t_dataset *data, char *str);
char				*conv_left(char *str);
char				*fill_zero(char *str, t_dataset *data);
char				*fill_0x(char *str);
char				*add_prefix(char *str, int flg, int len);
int					is_neg(char *str);
long long			ft_max(long long a, long long b);
long long			ft_abs(long long nbr);
long long			ft_min(long long a, long long b);
int					is_num(char c);
int					ft_strlen(const char *c);
char				*ft_strdup(const char *c);
void				super_write(char *s, int flg);
char				*cut_str(char *str, int size);
char				*extend_str(char *str, int size, int cpy_limit);
int					output(const char *args, int front, int rear, va_list list);
int					ft_vprintf(const char *args, va_list list);
int					ft_printf(const char *args, ...);

#endif
