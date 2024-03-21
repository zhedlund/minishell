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
//also looks complicated
int    ft_export(char *arraystring, t_env **head)
{
	t_env   *holdpp;
    t_env   *holdprev;
    char    **check;
    extern char **environ;

    check = ft_split(arraystring, ' ');
    if (check[2] != NULL)
    {
        printf();
    }
    while (check[1][i] != '\0')
        i++;
    if (check[1][i - 1] != '=')
        return (1);
    ft_strjoin(check[1], check [2]);
    holdprev = *head;
    holdprev = holdprev->prev;
    holdpp = holdprev->prev;
    
    
}

