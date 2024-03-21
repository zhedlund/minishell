/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:25:07 by jelliott          #+#    #+#             */
/*   Updated: 2023/12/11 15:25:09 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell_tree.h"
#include <limits.h>

char	*ft_cdsub(char *arraystring)
{
	char	*locate;
	int	j;

	j = 0;
	while (arraystring[j] != '\0')
		j++;
	locate = (char *)malloc(sizeof(char) * (j + 1));
	if (!locate)
		return (NULL);
	locate[j] = '\0';
	j = 0;
	while (arraystring[j] != '\0')
	{
		locate[j] = arraystring[j];
		j++;
	}
	locate[j] = '\0';
	return (locate);
}

bool	ft_homeset(t_env **head)
{
	t_env	*temp;

	temp = *head;
	while (temp != NULL)
        {
        	if (ft_strncmp(temp->field, "HOME", strlen("HOME")) == 0)
        		return (true);
        	temp = temp->next;
        }
		return (false);
}

char	*ft_gethome(t_env **head, char *locate)
{
	char	**homeinfo;
	char	*address;
	t_env	*temp;
	temp = *head;
	while (temp != NULL)
        {
        	if (ft_strncmp(temp->field, "HOME", strlen("HOME")) == 0)
			{
				homeinfo = ft_split(temp->field, '=');
				if (homeinfo[1] != NULL)
					address = ft_strdup(homeinfo[1]);
				else
				{
					ft_freearray(homeinfo);
					return (locate);
				}
				break ;
			}
        	temp = temp->next;
        }
		ft_freearray(homeinfo);
		return (address);
}

char	*ft_home(char *locate, t_env **head)
{
	if (ft_homeset(head) == true)
		locate = ft_gethome(head, locate);
	else
	{
			printf("Minishell: cd: HOME not set\n");
			return (NULL);
	}
	if (locate == NULL || *locate == '\0')
	{
		printf("Minishell: cd: HOME not set\n");
		return (NULL);
	}
	return(locate);
}

char	*ft_path(char *former)
{
	char	store[PATH_MAX];
	char	*path;
	int	i;
	char	*output;
	
	path = getcwd(store, sizeof(store));
	i = ft_strlen(path);
	output = (char *)malloc(sizeof(char) * (i + 1));
	output[i] = '\0';
	output = strcpy(output, path);
	if (!former)
		return (output);
	else
		free(former);
	return (output);
}

char	*ft_backone(char *locate)
{
	int	i;
	int	j;
	char	*output;
	
	i = 0;
	j = 0;
	output = NULL;
	if (locate[i] == '/' && locate[1] == '\0')
		return (locate);
	while (locate[i] != '\0')
		i++;
	while (locate[i] != '/')
		i--;
	if (ft_strlen(locate) > 5)
		i--;
	output = malloc(sizeof(char) * (i + 2));
	//error??
	while (j <= i)
	{
		output[j] = locate[j];
		j++;
	}
	output[j] = '\0';
	return (output);
}

void	ft_move(char *locate, t_env **head)
{
	char	*newpwd;
	
	newpwd = NULL;
	if (chdir(locate) != 0)
		perror("chdir");
	else
	{
		newpwd = ft_strjoin("PWD=", locate);
		ft_exportsub(newpwd, head);
		free(newpwd);
	}
}

void   ft_cd(char *arraystring, char **cmdarray, t_env **head)
{
	char	*locate;
	char 	**cdpath;
	bool	move;

	move = true;
	locate = NULL;
	locate = ft_path(locate);
	if (cmdarray[1] == NULL || cmdarray[1][0] == '~')
	{
		locate = ft_home(locate, head);
		if (ft_homeset(head) == false)
			move = false;
	}
	else if (cmdarray[1][1] != '\0' 
		&& ft_strncmp(cmdarray[1], "..", ft_strlen(cmdarray[1])) == 0)
		locate = ft_backone(locate);
	else if (cmdarray[1][0] != '.' 
		&& cmdarray[1][1] != '\0')
		locate = ft_cdsub(cmdarray[1]);
	if (move == true)
		ft_move(locate, head);
	if (locate)
		free(locate);
}