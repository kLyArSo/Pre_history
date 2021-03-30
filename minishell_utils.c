#include "minishell.h"

int     ft_strlen(char *str)
{
    int i = 0;
    while(str[i])
        i++;
    return i;

}

char    *ft_strdup(char     *str)
{
    int len = ft_strlen(str) + 1;
    int i = 0;
    char *result = malloc(len * sizeof(char));
    while (i <= len)
    {
        result[i] = str[i];
        i++;
    }
    return(result);
}

char    *ft_realloc(char *str, char c)
{
    int len  = ft_strlen(str) + 1; //+1 for c
    char *result = malloc(len + 1);//+1 for \0
    int i = 0;
    while(str[i])
    {
        result[i] = str[i];
        i++;
    }
    result[i] = c;
    i++;
    result[i] = 0;
    free(str);
    return (result);
}

int     ft_test_char(char   *str, char c)
{
    int i = 0;
    while (str[i] != 0)
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}

char    *ft_substr(char *s, int start, int finish)// from start to finish bruv
{
    char    *result = malloc(finish - start + 2);
    int i = 0;
    while (start <= finish)
    {
        result[i] = s[start];
        start++;
        i++;
    }
    result[i] = 0;
    return (result);
}

int     is_white_space(char c)
{
    if ((c >= 9 && c <= 13) || c == 32)
        return (1);
    return (0);
}

int     back_slash_presence(char *input, int i)
{
    int counter = 0;
    while(i >= 0 && input[i] == '\\')
    {
        i--;
        counter++;
    }
    return (counter % 2);
}



void    *ft_error(char *str)
{
    write(1, str, ft_strlen(str));
    return (NULL);
}

char    *trim_spaces(char *command)
{
    int i = 0;
    int start;
    int end;
    while(command[i] != 0 && is_white_space(command[i]) == 1)
        i++;
    start = i;
    i = ft_strlen(command) - 1;
    while(i >= 0 && is_white_space(command[i]) == 1) 
        if  (back_slash_presence(command, i - 1) == 1)
            break ;
        else
            i--;
    end = i;
    char *ptr = ft_substr(command, start, end);
    free(command);
    command = NULL;
    return(ptr);
}

void    print_n_free(t_linedata *ptr)
{
    if (ptr->next == NULL)
    {
        ptr->command = trim_spaces(ptr->command);
        printf("|%s|\n", ptr->command);
        free(ptr->command);
        free(ptr);
    }
    else
    {
        while(ptr->next != NULL)
        {
            ptr->command = trim_spaces(ptr->command);
            printf("|%s|\n", ptr->command);
            free(ptr->command);
            free(ptr);
            ptr = ptr->next;
        }
        ptr->command = trim_spaces(ptr->command);
        printf("|%s|\n", ptr->command);
        free(ptr->command);
        free(ptr);
    }
}








