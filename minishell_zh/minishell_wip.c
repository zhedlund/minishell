/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_wip.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 14:59:48 by zhedlund          #+#    #+#             */
/*   Updated: 2023/12/14 16:41:37 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MAX_LINE 80 // Max command line length

int main(void)
{
    char *args[MAX_LINE]; // command line args
    int i;
    char *input;
    pid_t pid;

    while (1) {
        input = readline("minishell> ");
        if (input == NULL) {
            printf("\n");
            break; // User pressed Ctrl+D or error
        }
        if (strcmp(input, "exit") == 0)
		{
            free(input);
            break;
        }
        add_history(input); // Add input to the history
        char *token = ft_strtok(input, " \n");
        i = 0;
        while (token != NULL)
		{
            args[i] = token;
            token = ft_strtok(NULL, "\n"); // to read whole line for cd, touch etc, read and write file names with spaces
            i++;
        }
        args[i] = NULL;
        if (strcmp(args[0], "cd") == 0) // works w file name with/without space. can go back w cd .., ../ ..
		{
            char dir[MAX_LINE] = "";
            for (int j = 1; args[j] != NULL; ++j)
			{
                ft_strcat(dir, args[j]);
                if (args[j + 1] != NULL) ft_strcat(dir, " "); // Add space if there are more arguments
            }
            if (chdir(dir) != 0)
                perror("chdir");
            free(input); // Free input and continue loop
            continue;
        }
		pid = fork();
        if (pid == 0)
		{
			execute_simple_command(args[0], args);
			perror("execve\n");
			exit(1);
        }
        else if (pid > 0)
            wait(NULL);
        else
		{
            perror("pid");
            exit(1);
        }
        free(input);
    }
    return (0);
}
