/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/lex.h"

inline int	sh_lexword(int fd, t_tok *tok, char **it, char **ln)
{
	while (**it)
		if (ft_isspace(**it) || ft_strchr("><&|!;(){}", **it))
			break ;
		else if (**it == '\'' || **it == '"')
		{
			if (sh_lexquote(fd, tok, it, ln) < 0)
				return (WUT);
		}
		else if (**it == '\\' && *++*it == '\n' && !*++*it &&
			(fd < 0 || !(*it = sh_readcat(fd, "> ", -2, NULL))))
			return (WUT);
		else
			ft_sdscpush((t_sds *)tok, *(*it)++);
	if (!tok->len)
		return (NOP);
	tok->id = TOK_WORD;
	return (YEP);
}
