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
//problem here that there is no variable to give - same with some other builtin functions
void    ft_unset(char *arraystring)
{
	if (args[1] == NULL)
        	printf("unset: not enough arguments\n");
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

