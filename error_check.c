#include "minishell.h"

char        *error_check(char    *input)
{
    int     i = 0;
    char    c;

    while (input[i] != 0)
    {
        while(input[i] != 0
        && (ft_test_char("<>\'\"|;",input[i]) == 0 || 
        (ft_test_char("<>\'\"|;",input[i]) == 1 && back_slash_presence(input, i - 1) == 1)))
            i++;
        if (ft_test_char("\'\"",input[i]) == 1)
        {
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
            if (input[i] == '\0')
                return (ft_error("Unmatched quotes\n"));
        }
        else if (ft_test_char("|;",input[i]) == 1)
        {
                if ((i = parse_error_check(input, i)) == -1)
                    return (ft_error("Parse_error\n"));
        }
        else if (ft_test_char("<>",input[i]) == 1)
        {
                if ((i = redirection_error_check(input, i)) == -1)
                    return (ft_error("Redirection_error\n"));
        }
        if (input[i] != 0)
            i++;
    }
    return ("done");
}

int     parse_error_check(char *input, int i)
{
    if (i == 0 || ft_test_char(";|", input[i + 1]) == 1 || (input[i] == '|' && input[i+1] == '\0'))
        return (-1);
    i++;
    while (input[i] != 0 && is_white_space(input[i]) == 1)
        i++;
    if (ft_test_char(";|", input[i]) == 1)
        return (-1);
    return (i);
}

int     redirection_error_check(char *input, int i)
{
    int start;
    int end;
    char *str;
    int counter;

    counter = 0;
    start = i;
    while (input[i] != 0 && ft_test_char("<>", input[i]) == 1) // skips all redirection parts
        i++;
    end = i - 1;
    str = ft_substr(input, start, end);
    //printf("|%s|\n", str);
    while (input[i] != 0 && is_white_space(input[i]) == 1) // skips all spaces
    {
        i++;
        counter++;
    }
    if (strcmp(">", str) != 0 && strcmp(">>", str) != 0 && strcmp("<", str) != 0 && strcmp("<>", str) != 0)
        return (-1);
    if (counter != 0)
    {
        if (input[i] == '\0' || input[i] == ';' || input[i] == '|')
            return (-1);
    }
    else if (counter == 0)
    {
        if (input[i] == ';' || input[i] == '\0' || (input[i] == '|' && strcmp(">", str) != 0))
            return (-1);
        if (input[i] == '|')
        {
            while(input[i] != 0 && is_white_space(input[i]) == 1)
                i++;
            if (input[i] == '\0' || ft_test_char("<>", input[i]) == 1)
                return (-1);
        }
    }
    return (i);
}