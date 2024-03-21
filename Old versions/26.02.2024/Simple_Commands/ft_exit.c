/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:25:59 by jelliott          #+#    #+#             */
/*   Updated: 2023/12/11 15:26:01 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//can exit alone or with a numerical variable
//when there is a numerical variable - echo $? will print the exit status [is this relevant?]
//this function primarily deals with exit alone
void    ft_exit(char *arraystring)
{
	//ft_freethings
	printf("mad it to exit\n");
	exit(255); //use 255 because it is maximum and not a standard exit status
}
