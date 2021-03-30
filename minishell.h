#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <printf.h>

typedef struct  s_parsedata
{
    char                *slice;
    struct s_parsedata  *next;
}   t_parsedata;

typedef struct  s_linedata
{
    char            *command;
    char            ending_char; //1 if present 0 if absent
    int             redirection;
    struct s_linedata *next;
}   t_linedata;


/*************************************************************/ //utilities
int         ft_strlen(char  *str);
char       *ft_strdup(char *str);
char       *ft_realloc(char *str, char c);
int         ft_test_char(char   *str, char c);
char       *ft_substr(char *s, int start, int finish);
int         is_white_space(char c);
/*************************************************************/ //utilities

/*************************************************************/ //fetch input line
char       *fetch_input_line();
/*************************************************************/ //fetch input line

/*************************************************************/ //parsing functions
int         back_slash_presence(char *input, int i);
char       *trim_spaces(char *command);
void        print_n_free(t_linedata *ptr);
/*************************************************************/ //parsing functions

/*************************************************************/ //error_check
char        *error_check(char    *input);
int         parse_error_check(char *input, int i);
int         redirection_error_check(char *input, int i);
void       *ft_error(char *str); //+ || -
/*************************************************************/ //error_check