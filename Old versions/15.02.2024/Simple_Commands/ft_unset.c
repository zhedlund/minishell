/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:23:44 by jelliott          #+#    #+#             */
/*   Updated: 2023/12/11 15:23:46 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell_tree.h"

//char	**ft_multiarguements()

//need a better way of doing this - initial function that
//checks how many arguements - maybe don't even need that
//then sends to subfunction that does what env does now
//multiple times if multiple arguements

void	ft_unsetsub(char *inputi, t_env **head)
{
	t_env	*temp;
	t_env	*passnext;
	t_env	*passprev;
	t_env	*test;

	temp = *head;
	test = *head;
	while (temp != NULL)
        {
        	if (ft_strncmp(temp->field, inputi, strlen(inputi)) == 0)
        		break ;
        	temp = temp->next;
        }
        if (temp == NULL)
        	return ;
        else if (temp->prev == NULL)
        {
        	*head = temp->next;
        	(*head)->prev = temp->prev;
        	free(temp->field);
        	free(temp);
        }
        else if (temp->next == NULL)
        {
        	passprev = temp->prev;
        	passnext = temp->next;
        	passprev->next = passnext;
        	//passnext->prev = passprev;
        	free(temp->field);
        	free(temp);
        }
        else
        {
        	passprev = temp->prev;
        	passnext = temp->next;
        	//if (ft_strncmp(temp->field, test->field, ft_strlen(temp->field)) == 0)
        	//	*head = passnext;
        	free(temp->field);
        	free(temp);
        	passprev->next = passnext;
        	passnext->prev = passprev;
        }
}

void    ft_unset(char *arraystring, char **cmdinfo, t_env **head, t_info **info)
{
	//extern char	**environ;
	char	**input;
	int	i;
	
	input = cmdinfo;
	i = 1;
	if (input[i] == NULL)
    {
		(*info)->exitstatus = 0;
		if ((*info)->inchild == true)
			exit(0);
	}
	while (input[i] != NULL)
	{
		ft_unsetsub(input[i], head);
		i++;
	}
    //ft_freearray(input);
	//ft_env("env", head);
	(*info)->exitstatus = 0;
	if ((*info)->inchild == true)
		exit(0);
        //to finish this need environmental variable set up
        //parser needs 'not a valid variable' i.e. doesn't conform to naming rules
        //echo $variable_name
        
        //check if the entered text is an enviromental variable [perhaps there will be an array
        //containing these? so can compare with this]
        //if no
        	//new line
        //else
        	//free the variable + information from whatever it has been saved in
}
