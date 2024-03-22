/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:56:05 by jelliott          #+#    #+#             */
/*   Updated: 2023/01/24 09:56:07 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_list *ft_lstnew(void *content)
{
	t_list	*new;
	
	new = (t_list *)malloc(sizeof(new));
	if (!new)
		return (NULL);
	new -> content = content;
	new -> next = NULL;
	return (new);
}
