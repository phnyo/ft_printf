#ifndef FT_PRINTF_H
#define  FT_PRINTF_H
#include  <stdarg.h>
#include  <stdlib.h>
#include  <unistd.h>

# define SIGNED 1
# define NUM 2
# define MIN_FLG 1
# define SPC_FLG 2
# define POS_FLG 4 
# define SHA_FLG 8
# define ZERO_FLG 16

typedef struct s_dataset
{
    int flg;
    int width;
    int precision;
    int prefix;
    int datatype;
} t_dataset;

#endif