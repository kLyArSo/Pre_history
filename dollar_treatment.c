#include "functions_headerfile.h"

int     test_c(char c)
{
    if ((c >= 'a' && c <= 'z')
    || (c >= 'A' && c <= 'Z')
    || (c >= '0' && c <= '9')
    || (c == '_'))
        return (1);
    return (0);
}

ssize_t     find_valid_dollar(char *slice)// returns index of the first valid dollar sign
{
    int i;
    char c;

    i = 0;
    while (slice[i] != 0)
    {
       while (slice[i] != 0
        && ((ft_test_char("\'\"$", slice[i]) == 0)
        || (ft_test_char("\'\"$", slice[i]) == 1 && back_slash_presence(slice, i - 1) == 1)))
            i++;
        if (ft_test_char("\'\"", slice[i]) == 1)
            i = skip_quotes(slice, i) + 1;
        if (slice[i] == '$' && back_slash_presence(slice, i - 1) == 0)
            return (i);
        if (slice[i] != 0)
            i++;
    }
    return (-1);
}

char    *fetch_var_name(char *slice, int i) //return the variable name
{
    int start;
    int end;
    char *result;

    start  = i;
    while (slice[i] != 0 && test_c(slice[i]) == 1)
        i++;
    end = i - 1;
    result = ft_substr(slice, start, end);
    return (result);
}

char    *var_replacement(t_var_rep *data)//replaces the dollar + variable name with the latters content
{
    char *tmp_1;
    char *tmp_2;

    tmp_1 = ft_substr(data->slice, 0, data->dollar_position - 1);
    tmp_2 = ft_substr(data->slice, data->dollar_position + ft_strlen(data->variable_name) + 1, ft_strlen(data->slice));
    tmp_1 = ft_strjoin(tmp_1, data->variable_content);
    tmp_1 = ft_strjoin(tmp_1, tmp_2);
    return(tmp_1);
}

ssize_t     equal_sign(char     *str)
{
    int i;

    i = 0;
    while(str[i] != 0)
    {
        if (str[i] == '=')
            return (i);
        i++;
    }
    return(-1);
}

t_env       *fetch_all_variables(char **env)
{
    int i;
    int init;
    int equ;
    t_env   *ptr;
    t_env   *ret;

    i = 0;
    init = -1;
    ptr = malloc(sizeof(t_env));
    ret = ptr;
    while (env[i] != NULL)
    {
        equ = equal_sign(env[i]);
        if (equ == -1)
            break ;
        ptr->var_name = ft_substr(env[i], 0, equ - 1);
        ptr->var_content = ft_substr(env[i], equ + 1, ft_strlen(env[i]));
        if (env[++i] != NULL)
        {
            ptr->next = malloc(sizeof(t_env));
            ptr = ptr->next;
        }
    }
    return (ret);
}

char    *ft_strdup(char     *str)
{
    char *ret;
    int i;

    if (str == NULL)
        return(NULL);
    i = ft_strlen(str) + 1;
    ret = my_calloc(i);
    if (ret == NULL)
        return (NULL);
    i = 0;
    while (str[i] != 0)
    {
        ret[i] = str[i];
        i++;
    }
    return(ret);
}

char    *fetch_wanted_var(char    *name, t_env   *ptr)
{
    while (ptr != NULL)
    {
        if (strcmp(name, ptr->var_name) == 0)
            return (ft_strdup(ptr->var_content));
        ptr = ptr->next;
    }
    return (NULL);
}


void    print_k(t_env   *ptr)
{
    while(ptr != NULL)
    {
        printf("%s|=|%s\n",ptr->var_name, ptr->var_content);
        ptr = ptr->next;
    }
}

char    *fetch_variable_content(char **env, char    *name)
{
    t_env   *ptr;
    char    *ret;

    ptr = fetch_all_variables(env);
    ret = fetch_wanted_var(name, ptr);
    return (ret);
}

char    *dollar_treatment(char  **env, char *slice)
{
    int i = 0;
    t_var_rep *data = malloc(sizeof(t_var_rep));
    data->slice = slice;
    while (data->slice[i] != 0)
    {
        i = find_valid_dollar(data->slice);
        if (i == -1)
            break ;
        data->dollar_position = i++;
        data->variable_name = fetch_var_name(data->slice, i);
        data->variable_content = fetch_variable_content(env, data->variable_name);//aymen function goes here
        if (data->variable_content == NULL)
            data->variable_content = ft_strdup("");
        data->slice = var_replacement(data);
    }
    return (data->slice);
}
/*
int     main(int    argc, char      **argv, char        **env)
{
    int i;

    i = 0;
    char *str = ft_strdup(argv[1]);
    dollar_treatment(env, str);
    printf("%s\n", str);
    return (0);
}*/