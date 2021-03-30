#include "minishell.h"

int     skip_quotes(char    *input, int i)
{
    char    c;

    c = input[i];
    i++;
    if (c == '\"')
    {
        while(input[i] != 0 && 
        (input[i] != '\"' || (input[i] == '\"' && back_slash_presence(input, i) == 1)))
            i++;
    }
    else if (c == '\'')
    {
        while(input[i] != 0 && input[i] != '\'')
            i++;
    }
    return (i);
}
char        *treat_lines(char    *input, t_linedata *data)
{
    int     i = 0;
    int     start = 0;
    int     end;

    while (input[i] != 0)
    {
        while(input[i] != 0
        && (ft_test_char("<>\'\"|;",input[i]) == 0 || 
        (ft_test_char("<>\'\"|;",input[i]) == 1 && back_slash_presence(input, i - 1) == 1) || is_white_space(input[i]) == 0))
            i++;
        if (ft_test_char("\'\"",input[i]) == 1)
            i = skip_quotes(input, i);
        else if (ft_test_char("|;",input[i]) == 1)
        {
            end = i - 1;
            data->command = ft_substr(input, start, end);
            data->ending_char = input[i];
            if(!(data->next = (t_linedata*)malloc(sizeof(t_linedata))))
                return(ft_error("Failed Mem Alloc\n"));
            data = data->next;
            start = i + 1;
        }
        else if (ft_test_char("<>",input[i]) == 1)
        {
            end = i - 1;
            data->command = ft_substr(input, start, end);
            data->ending_char = input[i];
            if(!(data->next = (t_linedata*)malloc(sizeof(t_linedata))))
                return(ft_error("Failed Mem Alloc\n"));
            data = data->next;
            start = i;

            while (input[i] != 0 && ft_test_char("<>",input[i]) == 1)
                i++;

            end = i - 1;
            data->command = ft_substr(input, start, end);
            data->redirection = 1;
            if(!(data->next = (t_linedata*)malloc(sizeof(t_linedata))))
                return(ft_error("Failed Mem Alloc\n"));
            data = data->next;
            start = i;
        }
        else if (is_white_space(input[i]) == 1)
        {
            end = i - 1;
            data->command = ft_substr(input, start, end);
            data->ending_char = input[i];
            if(!(data->next = (t_linedata*)malloc(sizeof(t_linedata))))
                return(ft_error("Failed Mem Alloc\n"));
            data = data->next;
            while (input[i] != 0 && is_white_space(input[i]) == 1)
                i++;
            start = i;
        }
        if (input[i] != 0)
            i++;
        if (input[i] == 0)
        {
            end = i - 1;
            data->command = ft_substr(input, start, end);
            data->ending_char = input[i];
            data->next = NULL;
        }
    }
    return ("done");
}

int     main()
{
    char *input;
    while (1)
    {
        t_linedata  *h = (t_linedata*)malloc(sizeof(t_linedata));
        write(1, "~minishell~", ft_strlen("~minishell~"));
        input = fetch_input_line();
        t_linedata *ptr = h;
        if (error_check(input) == NULL)
            continue ;
        treat_lines(input, ptr);
        print_n_free(ptr);
    }
    return (0);
}