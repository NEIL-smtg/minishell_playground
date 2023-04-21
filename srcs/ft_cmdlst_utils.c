/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 01:28:31 by suchua            #+#    #+#             */
/*   Updated: 2023/04/22 04:03:34 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_cmdlst(t_cmdlst **lst)
{
	t_cmdlst	*tmp;

	while ((*lst))
	{
		tmp = (*lst)->next;
		free((*lst)->cmd);
		free((*lst));
		(*lst) = tmp;
	}
}

void	print_lst(t_cmdlst *lst)
{
	t_cmdlst	*tmp;

	tmp = lst;
	while (tmp)
	{
		ft_printf("%s\n", tmp->cmd);
		ft_printf("open_brac = %d close_brac = %d within_brac = %d\n", tmp->open_brac, tmp->closed_brac, tmp->within_brac);
		tmp = tmp->next;
	}
}

void	ft_cmdlst_addback(t_cmdlst	**lst, char *s)
{
	t_cmdlst	*new;
	t_cmdlst	*tmp;

	new = ft_calloc(1, sizeof(t_cmdlst));
	new->cmd = ft_strdup(s);
	new->next = NULL;
	new->prev = NULL;
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

//sq = single quote, dq = double quote
char	**interesting_split(char *cmd, int depth, int sq, int dq)
{
	char	**res;
	int		i;
	char	*sub;
	
	while (ft_isspace(*cmd))
		cmd++;
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == 34)
			sq = !sq;
		if (cmd[i] == 39)
			dq = !dq;
		if (ft_isspace(cmd[i]) && !sq && !dq)
			break ;
	}
	sub = ft_substr(cmd, 0, (size_t) i);
	if (!cmd[i])
		res = ft_calloc(depth + 2, sizeof(char *));
	else
		res = interesting_split(cmd + i, depth + 1, 0, 0);
	res[depth] = sub;
	return (res);
}

//if bonus == '||' | '&&' , returns 1 when s == double
int	cmdlst_is_double(char *s, char *bonus)
{
	return (ft_strncmp(s, bonus, ft_strlen(bonus)) == 0);
}
