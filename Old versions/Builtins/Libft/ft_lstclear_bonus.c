/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:38:14 by jelliott          #+#    #+#             */
/*   Updated: 2023/01/24 17:38:20 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*hold;
	
	if(!*lst)
		return ;
	while (*lst != NULL)
	{
		hold = *lst;
		(*del)(hold -> content);
		free(hold);
		*lst (*lst) -> next;
	}
	*lst = NULL;
}
