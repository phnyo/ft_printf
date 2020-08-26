/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 15:23:59 by fsugimot          #+#    #+#             */
/*   Updated: 2020/08/26 16:16:24 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     ft_strlen(const char *c)
{
    int index;

    index = 0;
    while (c[index])
        ++index;
    return (index);
}

char    *ft_strdup(const char *c)
{
    char *ret;
    int     alloc_size;

    alloc_size = ft_strlen(c);
    ret = malloc(alloc_size + 1);
    if (!ret)
        return (ret);
    ret[alloc_size--] = 0;
    while (alloc_size > -1)
    {
        ret[alloc_size] = c[alloc_size];
        alloc_size--;
    }
    return (ret);
}

long long   ft_max(long long a, long long b)
{
    return (a > b ? a : b);
}

long long   ft_abs(long long nbr)
{
    return (nbr > 0 ? nbr : -nbr);
}

long long   ft_min(long long a, long long b)
{
    return (a > b ? b : a);
}

int     is_num(char c)
{
    return (c <= '9' && c >= '0');
}

void    super_write(char *s)
{
    write(1, s, ft_strlen(s));
}

char    *cut_str(char *str, int size)
{
    int ind;
    char *ret;

    if (!str)
        return (0);
    if (!size)
        return (str);
    ret = malloc(size + 1);
    if (!ret)
        return (0);
    ind = 0;
    while (ind < size)
    {
        ret[ind] = str[ind];
        ind++;
    }
    ret[ind] = 0;
    free(str);
    return (ret);
}

char    *extend_str(char *str, int size, int cpy_limit)
{
    int ind;
    int tmp;
    char *ret;

    if(!size || !cpy_limit)
        return (str);
    ret = malloc(size + 1);
    if (!ret)
        return (0);
    ret[size] = 0;
    ind = 0;
    tmp = size - ft_min(cpy_limit, ft_strlen(str));
    while (ind < tmp)
    {
        ret[ind] = ' ';
        ++ind;
    }
    while (ind < size)
    {
        ret[ind] = str[ind - tmp];
        ++ind;
    }
    free(str);
    return (ret); 
}

int     process_w_p(t_dataset *data, char **str)
{
    int tmp;

    if (!data->width)
        data->width = ft_strlen(*str);
    if (!data->precision)
        data->precision = ft_strlen(*str);
    tmp = ft_max(data->precision, ft_max(data->width, ft_strlen(*str)));
    if (data->width > ft_strlen(*str) || data->precision > ft_strlen(*str))
        *str = extend_str(*str, tmp, data->precision);
    if (data->precision == tmp)
        data->flg |= 16;
    if (data->precision < ft_strlen(*str))
    {
        tmp = ft_strlen(*str);
        *str = cut_str(*str, data->precision);
        *str = extend_str(*str, tmp, ft_strlen(*str));
    }
    if (!str[0])
        return (-1);
    return (0);
}

char    *conv_left(char *str)
{
    int size;
    int ind;
    int rear;

    ind = 0;
    rear = 0;
    size = ft_strlen(str);
    while (str[rear] == ' ' && str[rear])
        rear++;
    while (ind < size - rear)
    {
        str[ind] = str[ind + rear];
        ind++;
    }
    while (ind < size)
    {
        str[ind] = ' ';
        ind++;
    }
    return (str);
}

char    *fill_zero(char *str)
{
    int ind;

    ind = 0;
    while (str[ind] == ' ')
    {
        str[ind] = '0';
        ind++;
    }
    return (str);
}

char    *add_prefix(char *str, int flg, int len)
{
    int ind;

    ind = 0;
    if (!str)
        return (0);
    while (str[ind] == ' ')
        ind++;
    if (ind < len)
        str = extend_str(str, ft_strlen(str) + (len - ind), ft_strlen(str));
    ind = (ind < len ? 0 : ind - len);
    if (!str)
        return (str);
    if (flg & 1)
        str[ind] = 'o';
    if (flg & 2)
    {
        str[ind] = '0'; 
        str[ind + 1] = 'X' + (((flg & 4) > 0) << 5);
    }
    if (flg & 8)
        str[ind] = ' ';
    if (flg & 16)
        str[ind] = '+';
    return (str);
}

int     process_flg(t_dataset *data, char **str)
{
    if (data->flg & MIN_FLG)
        *str = conv_left(*str);
    if (data->flg & SPC_FLG && data->datatype & SIGNED)
        *str = add_prefix(*str, 8, 1);
    if (data->flg & POS_FLG && data->datatype & SIGNED)
        *str = add_prefix(*str, 16, 1);
    if (data->flg & SHA_FLG && data->prefix > 0)
        *str = add_prefix(*str, data->prefix, 1 + ((data->prefix & 2) != 0));
    if (data->flg & ZERO_FLG && data->datatype & NUM)
        *str = fill_zero(*str);
    if (!(*str))
        return (-1);
    return (0); 
}

int     process_fmt(t_dataset *data, char *str)
{
    int tmp;

    tmp = process_w_p(data, &str);
    if (tmp == -1)
    {
        free(data);
        return (-1);
    }
    tmp = process_flg(data, &str);
    if (tmp == -1)
    {
        free(data);
        return (-1);
    }
    tmp = ft_strlen(str);
    super_write(str);
    free(str);
    free(data);
    return (tmp);
}

int     count_digit(unsigned long long int num, int div)
{
    int dig;

    dig = 0;
    while (num > 0)
    {
        num /= div;
        ++dig; 
    }
    return (dig);
}

char    *num_to_str(int num)
{
    int dig; 
    char    *ret;

    dig = count_digit(num, 10);
    dig += (num <= 0);
    ret = malloc(dig + 1);
    if (!ret)
        return (ret);
    ret[dig--] = 0;
    if (num < 0)
        ret[0] = '-';
    if (!num)
        ret[0] = '0';
    while (ft_abs(num) > 0)
    {
        ret[dig--] = '0' + ft_abs(num % 10);
        num /= 10; 
    }
    return (ret);
}

char    *u_num_to_str(unsigned int num, int is_hex, int is_oct)
{
    int div;
    int dig;
    int is_cap;
    char    *ret;

    div = is_hex & 1 ? (1 << 4) : 10;
    div = is_oct ? 8 : div;
    is_cap = (is_hex & 2 << 5); 
    dig = count_digit(num, div);
    ret = malloc(dig + 1);
    if (!ret)
        return (ret);
    ret[dig--] = 0;
    if (!num)
        ret[0] = '0';
    while (num > 0)
    {
        if (num % div > 9)
            ret[dig--] = ('A' ^ is_cap) + num % div - 10;
        else
            ret[dig--] = '0' + num % div;
        num /= div; 
    }
    return (ret);
}

int output_ptr(t_dataset *data, unsigned long long int ptr)
{
    int dig;
    int ret;
    char    *str;

    dig = count_digit(ptr, (1 << 4)) + 1;
    str = malloc(dig + 3);
    str[dig + 1] = 0;
    str[0] = '0';
    str[1] = 'x';
    while (ptr > 0)
    {
        if (ptr % 16 > 9)
            str[dig--] = 'a' + ptr % 16 - 10;
        else
            str[dig--] = '0' + ptr % 16;
        ptr /= 16; 
    }
    ret = process_fmt(data, str);
    return (ret); 
}

int output_char(t_dataset *data, char c)
{
    int ret;
    char    *str;

    str = malloc(2);
    if (!str)
        return (-1);
    str[1] = 0;
    str[0] = c;
    ret = process_fmt(data, str);
    return (ret);
}

int output_num(t_dataset *data, int nbr)
{
    int ret;
    char *str;

    data->datatype |= (nbr < 0 ? NUM : SIGNED + NUM);
    str = num_to_str(nbr);
    if (!str)
        return (-1);
    ret = process_fmt(data, str);
    return (ret);
}

int output_unum(t_dataset *data, unsigned int nbr, int is_hex, int is_oct)
{
    int ret;
    char *str;

    str = u_num_to_str(nbr, is_hex, is_oct);
    if (!str)
        return (-1);
    data->prefix |= ((is_hex & 2) << 1);
    data->prefix |= ((is_hex & 1) << 1);
    data->prefix |= is_oct;
    data->datatype |= NUM; 
    ret = process_fmt(data, str);
    return (ret);
}

int output_str(t_dataset *data, const char *content)
{
    int ret;
    char *str;

    str = ft_strdup(content);
    if (!str)
        return (-1);
    ret = process_fmt(data, str);
    return (ret);
}

int is_terminator(const char c)
{
    if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u' ||\
        c == 'x' || c == 'X' || c == 'o' || c == '%')
        return (1);
    return (0);
}

int     is_flg(char c)
{
    return (c == '-' || c == ' ' || c == '+' || c == '0' || c == '#');
}

int     str_to_int(const char *str, int front)
{
    int ret;
    
    ret = 0;
    while (is_num(str[front]))
    {
        ret *= 10;
        ret += str[front] - '0';
        front++;
    }
    return (ret);
}

int     fill_field(const char *args, int *front, int rear)
{
    int num_r;
    int ret;

    num_r = *front;
    while (is_flg(args[num_r]))
        num_r++;
    if (args[num_r] == '*')
        return (-1);
    ret = str_to_int(args, num_r);
    *front = num_r;
    return (ret);
}

int     fill_flg(const char *str, int front)
{
    int ret;
    int ind;

    ret = 0;
    ind = front;
    while (is_flg(str[ind]))
    {
        if (str[ind] == '-' && !(ret & MIN_FLG))
            ret |= (MIN_FLG);
        if (str[ind] == ' ' && !(ret & SPC_FLG))
            ret |= (SPC_FLG);
        if (str[ind] == '+' && !(ret & POS_FLG))
            ret |= (POS_FLG);
        if (str[ind] == '#' && !(ret & SHA_FLG))
            ret |= (SHA_FLG);
        if (str[ind] == '0' && !(ret & ZERO_FLG)) 
            ret |= (ZERO_FLG);
        ind++;
    }
    if (ret & ZERO_FLG && ret & MIN_FLG)
        ret |= ZERO_FLG;
    if (ret & POS_FLG && ret & SPC_FLG)
        ret |= SPC_FLG;
    return (ret);
}

int    parse_front(t_dataset **data, const char *args, int front, int rear, va_list list)
{
    int ret;
    t_dataset *tmp;

    ret = 0;
    tmp = *data;
    tmp->prefix = 0;
    tmp->flg = fill_flg(args, front);
    tmp->width = fill_field(args, &front, rear);
    if (tmp->width == -1)
        tmp->width = va_arg(list, int);
    if (args[front] == '.')
        front++;
    tmp->precision = fill_field(args, &front, rear);
    if (tmp->precision == -1)
        tmp->precision = va_arg(list, int);
    return (1);
}

int output(const char *args, int front, int rear, va_list list)
{
    int ret;
    t_dataset *data;

    if (!(data = malloc(sizeof(t_dataset))))
        return (-1);
    ret = 0;
    if (parse_front(&data, args, front, rear, list) == -1)
        return (-1);
    if (args[rear] == '%')
        ret += output_char(data, '%');
    if (args[rear] == 'c')
        ret += output_char(data, va_arg(list, int));        
    if (args[rear] == 'i' || args[rear] == 'd')
        ret += output_num(data, va_arg(list, long long));
    if (args[rear] == 'u' || args[rear] == 'x' || args[rear] == 'X' || args[rear] == 'o')
        ret += output_unum(data, va_arg(list, unsigned int), \
            1 + ((args[rear] == 'X') << 1), (args[rear] == 'o'));
    if (args[rear] == 's')
        ret += output_str(data, va_arg(list, char *));
    if (args[rear] == 'p')
        ret += output_ptr(data, va_arg(list, long long unsigned int));
    return (ret);
}

int ft_vprintf(const char *args, va_list list)
{
    int     ind;
    int     ret;
    int     tmp;

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
        else {
            write(1, &args[ind++], 1);
            ret++;
        }
    }
    return (ret);
}

int ft_printf(const char *args, ...)
{
    int ret;
    va_list list;

    ret = 0;
    va_start(list, args);
    ret = ft_vprintf(args, list);
    va_end(list);
    return (ret);
}