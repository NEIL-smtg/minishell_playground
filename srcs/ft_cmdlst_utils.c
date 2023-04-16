/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 01:28:31 by suchua            #+#    #+#             */
/*   Updated: 2023/04/17 00:15:38 by suchua           ###   ########.fr       */
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
	return (0);
}

char	**interesting_split(char *cmd, int depth)
{
	char	*str;
	char	**dst;
	int		i;
	int		is_quoted;

	is_quoted = 0;
	while (*cmd == 32)
		cmd++;
	if (*cmd == 34 || *cmd == 39)
		is_quoted = *cmd++;
	i = 0;
	while (cmd[i] && (cmd[i] != 32 || is_quoted))
		if (cmd[i++] == is_quoted)
			break ;
	str = ft_substr(cmd, 0, i - !(!is_quoted));
	while (cmd[i] && cmd[i] == 32)
		++i;
	if (!cmd[i])
		dst = ft_calloc(depth + 2, sizeof(char *));
	else
		dst = interesting_split(cmd + i, depth + 1);
	dst[depth] = str;
	return (dst);
}

//if bonus == '||' , returns 1 when s == double
//if bonus == '&&' , ^
int	cmdlst_is_double(char *s, char *bonus)
{
	return (ft_strncmp(s, bonus, ft_strlen(bonus)) == 0);
}
