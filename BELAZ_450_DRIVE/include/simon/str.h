/*******************************************************************************

    str.h -  string functions included in netlib to prevent using of rts
             (most copied from original rts but some missing in runtime sources)

    Revision same as net.h
    Company  D.SignT
    Author   Claus Hermbusche
    Created  10 Apr 2002
 
    Hardware D.Module.91C111
             D.Module.8900
             C.Module.ODEM
             DSK91C111

    Compiler VC33: Code Composer Studio
                   Version: 1.1
             C6x:  Code Composer Studio
                   Version: 2.x
             C5x:  Code Composer Studio
                   Version: 2.x
             21065: Visual DSP 1.0
                    Visual DSP++ 2.0
                    Visual DSP++ 3.0

    Options  VC33:
             C6x:
             21065: -D _ADSP21065

    History  1.0 initial release 10 Apr 2002 by CH

*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif /* !__cplusplus */

/*******************************************************************************

    Function   string_cmp - string compare. similar to stdlib function strcmp()

    Parameter  *s1, *s2   - strings to compare
    Returns    FALSE (0)  - strings are the same
               TRUE (1)   - strings are differnt

*******************************************************************************/
int string_cmp (char *s1,
                char *s2);

/*******************************************************************************

    Function    string_ncmp() - string n copmare.
    similar to stdlib function strncmp(); compares up to n characters of the
    NULL-terminated strings pointed to by s1 and s2.

    Parameter  *s1, *s2   - strings to compare
               n          - number of charcters to compare

    Returns    FALSE (0)  - strings are the same
               TRUE (1)   - strings are differnt

*******************************************************************************/
int string_ncmp (const char *string1,
                 const char *string2,
                 int n);

/*******************************************************************************

    Function  string_cpy() - copies the NULL-terminated string pointed to by src
    into the space pointed to by dest. Memory allocated for dest must be large
    enough to hold src, plus one space for the NULL character ('0'). The be-
    havior of strcpy is undefined if the two strings overlap or if dest is not
    large enough. The strcpy function returns the new string.

    Parameter  *dest  - destination string
               *src   - source strings
    Returns    *dest

*******************************************************************************/
char *string_cpy (char *dest,
                  const char *src);

/*******************************************************************************

    Function   string_ncpy() - copies up to n characters of the NULL-terminated
    string src into the string dest. If the last character copied from src is
    not a NULL, the result will not end with a NULL. The behavior of strncpy is
    undefined if the two strings overlap. The string_ncpy() function returns the
    new string.
    If the src string contains fewer than n characters, the dest string is
    padded with the NULL character until all n characters have been written.

    Parameter  *dest  - destination string
               *src   - source strings
                n     - number of characters to copy
    Returns    *dest

*******************************************************************************/
char *string_ncpy (char *dest,
                   const char *src,
                   int n);

/*******************************************************************************

    Function  string_chr()   -  search a char in a string
    The string_chr function returns a pointer to the first location in s, a NULL-
    terminated string, that contains the character chr.

    Parameter *s   - string
               chr - character to search
    Returns    pointer to char or NULL

*******************************************************************************/
char *string_chr (char *s,
                  char chr);

/*******************************************************************************

    Function  string_str()   -  search a string in a string
    The string_str function returns a pointer to the first location in string1
    that contains the string2.

    Parameter *string1 - string
              *string2 - string to search
    Returns    pointer to string or NULL

*******************************************************************************/
char *string_str (register const char *string1, const char *string2);

/*******************************************************************************

    Function string_dup() -  duplicate and malloc a string

    The string_dup function allocates memory to hold a new string and copies all
    characters pointed by *buffer including a terminating zero.

    Parameter *buffer - string to duplicate
    Returns   *new    - pointer to new string

*******************************************************************************/
char *string_dup ( char *buffer);


/*******************************************************************************

    Function string_len() - The string_len function returns the length of the
    NULL-terminated string pointed to by buffer (not including the NULL).

    Parameter *buffer - string
    Returns    string length

*******************************************************************************/
int string_len (char *buffer);

/*******************************************************************************

    Function   string_concat() - concatenate two strings
    be sure *dest is large enough to hold both strings!

    Parameter   *dest  - first string to concat
                *src   - second string is apended on string 1
    Returns     *dest  - pointer to new concatenated string

*******************************************************************************/
char *string_concat (char *dest,
                     const char *src);

/*******************************************************************************

    Function   string_toi() - convert a zero terminated string to integer

    Parameter  *s - string to convert
    Returns     n - integer

*******************************************************************************/
unsigned int string_toi (char *s);

/*******************************************************************************

    Function    char *ltonstr (longc, char *buffer, int n)

    convert a long integer to a n-bit hex digit string

    Parameter   x       integer to convert
                *buffer pointer to string buffer
                n       number of digits in string
    Returns     pointer to string buffer
    Calls       -

*******************************************************************************/
char *ltonstr (unsigned int x, char *buffer, int n);

/*******************************************************************************

    Function  get_string_command()
    search a user defined command list for specific command

    Parameter command  - command to search for
              cmd_list - user defined list of commands

    Returns   command offset in user defined list if found
              else (-1)

    Calls     string_len()
              string_ncmp()

*******************************************************************************/
int get_string_command ( char **command, char **cmd_list );

/*******************************************************************************

    function    char *ntodstr (int n, char *buffer)

    convert a int to a not zero terminated decimal string

    Parameter   n       integer to convert
                *buffer pointer to string buffer
    Returns     pointer to converted string buffer end +1
    Calls       -

*******************************************************************************/
char *ntodstr (unsigned int n, char *buffer);


#ifdef __cplusplus
} // extern "C"
#endif
