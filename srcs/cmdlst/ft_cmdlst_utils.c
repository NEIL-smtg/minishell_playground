/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 01:28:31 by suchua            #+#    #+#             */
/*   Updated: 2023/04/24 22:44:25 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmdlst_addback(t_cmdlst	**lst, char *s)
{
	t_cmdlst	*new;
	t_cmdlst	*tmp;

	new = ft_calloc(1, sizeof(t_cmdlst));
	new->cmd = ft_strdup(s);
	new->next = NULL;
	new->prev = NULL;
	new->within_brac = 0;
	new->open_brac = 0;
	new->closed_brac = 0;
	if (!lst || !*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
	}
}

//if bonus == '||' or '&&' , returns 1 when s == double
int	cmdlst_is_double(char *s, char *bonus)
{
	return (ft_strncmp(s, bonus, ft_strlen(bonus)) == 0);
}

int	to_split(char *s)
{
	if (!ft_strncmp(s, "|", 2))
		return (1);
	if (!ft_strncmp(s, "||", 3))
		return (1);
	if (!ft_strncmp(s, "&&", 3))
		return (1);
	if (!ft_strncmp(s, ";", 2))
		return (1);
	return (0);
}

int	instr_split(char *s)
{
	if (!ft_strncmp(s, "||", 2))
		return (2);
	if (!ft_strncmp(s, "|", 1))
		return (1);
	if (!ft_strncmp(s, "&&", 2))
		return (2);
	if (!ft_strncmp(s, ";", 1))
		return (1);
	return (0);
}

void	print_lst(t_cmdlst *lst)
{
	t_cmdlst	*tmp;

	tmp = lst;
	while (tmp)
	{
		ft_printf("%s\n", tmp->cmd);
		ft_printf("open_brac = %d close_brac = %d within_brac = %d\n",
			tmp->open_brac, tmp->closed_brac, tmp->within_brac);
		tmp = tmp->next;
	}
}
