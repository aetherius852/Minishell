/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_aply.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/03 11:39:08 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	apply_redirections(t_redir *redirs, t_mini *mini)
{
	t_redir	*current;

	current = redirs;
	while (current)
	{
		if (!apply_single_redir(current, mini))
			return (0);
		current = current->next;
	}
	apply_fds(mini);
	return (1);
}
