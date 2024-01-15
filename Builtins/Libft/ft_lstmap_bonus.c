/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:28:31 by jelliott          #+#    #+#             */
/*   Updated: 2023/01/25 10:28:34 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft"

t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	
	if (!lst || !f || !del)
		return ;
	*lst = ft_lstiter(lst, f);
	new = ft_lstnew(f(lst -> content));
	while (lst != NULL)
	{
		if (!(*f)(lst -> content))
			(*del)(lst -> content);
		lst = lst -> next;
		ft_lsadd_back(&lst, new);
	}
	return (new);
}
