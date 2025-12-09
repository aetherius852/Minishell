/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inandres <inandres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 10:37:53 by efsilva-          #+#    #+#             */
/*   Updated: 2025/12/09 10:28:19 by inandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"#include "../libft/libft.h"

static t_cmd    *parse_single_cmd(t_token **tokens)
{
    t_cmd   *cmd;
    int     arg_count;

    cmd = create_cmd_node();
    if (!cmd)
        return (NULL);
    arg_count = count_args(*tokens);
    cmd->args = malloc(sizeof(char *) * (arg_count + 1));
    if (!cmd->args)
    {
        free(cmd);
        return (NULL);
    }
    if (!fill_args(cmd, tokens))
    {
        free_cmds(cmd);
        return (NULL);
    }
    return (cmd);
}

t_cmd   *parse_tokens(t_token *tokens)
{
    t_cmd   *cmds;
    t_cmd   *new_cmd;
    t_token *current;
}
