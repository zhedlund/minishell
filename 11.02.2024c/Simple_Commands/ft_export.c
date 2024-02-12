/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:28:33 by jelliott          #+#    #+#             */
/*   Updated: 2023/12/11 15:28:35 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell_tree.h"
//anything can be added if there is an '='; otherwise either nothing happens OR
//if the next items contain a +=- etc. them there will be an error message - bash: export: `hallo-de': not a valid identifier
//also the unexpected token message
//placement rationale isn't clear - perhaps it doesn't matter to just put at the end
//still seems to work even if nonsense for argc 2
//if there isn't a '='
//export also seems to overwrite if the variable is in the list
bool ft_equalpresent(char *check)
{
    int a;
    bool    validcheck;

    a = 0;
    validcheck = false;
    while(check[a] != '\0')
    {
        if(check[a] == '=')
            validcheck = true;
        a++;
    }
    return(validcheck);
}

int ft_inititalchar(char *arraystring)
{
    //need a list of invalid identifiers - anything that isn't a char
    if ((arraystring[0] >= 65 && arraystring[0] <= 90)
        || (arraystring[0] >= 97 && arraystring[0] <= 122))
        return (0);
    printf("Minishell: export: '");
    printf("%s", arraystring);
    printf("':  not a valid identifier\n");
    return (1);
}

void    ft_exportsub(char *toexport, t_env **head)
{
    t_env   *holdnext;
    t_env   *hold;
    t_env   *insert;
    char    **split;

    split = ft_split(toexport, '=');
    ft_unsetsub(split[0], head);
    ft_freearray(split);
    hold = *head;
    holdnext = (*head)->next;
    insert = (t_env *)malloc(sizeof(t_env));
    insert->field = ft_strdup(toexport);
    (*head)->next = insert;
    insert->prev = *head;
    insert->next = holdnext;
    holdnext->prev = insert;
}

bool    ft_unexpectedtoken(char *check)
{
    int a;
    bool    unexpected;

    unexpected = false;
    a = 0;
    while (check[a] != '\0')
    { 
        if (check[0] == '(' || check[0] == ')')
            unexpected = true;
        if (unexpected == true)
            break ;
        else
            a++;
    }
    if (unexpected == false)
        return (false);
    printf("Minishell: syntax error near unexpected token '");
    printf("%c", check[a]);
    printf("'\n");
    return (true);
}

void    ft_valididentifier(char *check, t_env **head)
{
    int a;

    a = 0;
    while (check[a] != '\0')
    { 
        if ((check[a] >= 65 && check[a] <= 90)
            || (check[a] >= 97 && check[a] <= 122))
            a++;
        else
            break ;
    }
    if (check[a] == '=' && a != 0)
    {
        ft_exportsub(check, head);
        return ;
    }
    if (check[a] == '\0')
        return ;
    printf("Minishell: export: '");
    printf("%s", check);
    printf("':  not a valid identifier\n");
}

//concern with error checking - if this happens in a pipe, then we will print things...
//but could this entail a problem with e.g. grep or ls...the error message seems to print anyway
//and this happens whereever it is in the order of piping e.g. pwd | export invalid | ls - still get error message
//can't find an unexpected token list...perhaps can just have a generic error message?
int    ft_export(char *arraystring, char **cmdarray, t_env **head)
{
    char    **check;
    int a;
    bool unexpected;
    bool    exportcmd;

    a = 1;
    unexpected = false;
    //initial invalid identifier
    check = cmdarray;
    printf("input === %s\n", arraystring);
    if (check[1] == NULL)
    {
        if (ft_strncmp(check[0], "export", ft_strlen(check[0])) == 0)
        {
                ft_env("env", head);
                return (0);
        }
        exportcmd = false;
        a = 0;
    }
    while (check[a] != NULL)
    {
        unexpected = ft_unexpectedtoken(check[a]);
        if (unexpected == true)
        {
            ft_freearray(check);
            return (0);
        }
        a++;
    }
    a = 1;
    if (exportcmd == false)
        a = 0;
    if (ft_inititalchar(check[a]) == 1)
    {   
        ft_freearray(check);
        return (1); //??
    }
    //equal present? either way, will need to check other arguements
    if (ft_equalpresent(check[a]) == true)
        ft_exportsub(check[a], head);
    a = 2;
    if (exportcmd == false)
        a = 1;
    while (check[a] != NULL)
    {
        ft_valididentifier(check[a], head);
        a++;
    }
    //ft_freearray(check);
    return (0);
}