#include "minishell.h"

char    *fetch_input_line()
{
    char str[1];
    char *ptr = malloc(1);
    ptr[0] = '\0';
    while(read(1,str, 1) == 1 && str[0] != '\n')
            ptr = ft_realloc(ptr, str[0]);
    int start = 0;
    while (ptr[start] != 0 && ptr[start] == ' ' && ptr[start + 1] != '\\')
        start++;
    int end = ft_strlen(ptr) - 1;
    while (end != 0 && ptr[end] == ' ' && ptr[end - 1] != '\\')
        end--;
    ptr = ft_substr(ptr, start, end + 1);
    return(ptr);
}
