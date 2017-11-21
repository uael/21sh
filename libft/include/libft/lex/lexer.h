/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/lexer.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 10:03:31 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LEX_LEXER_H
# define LIBFT_LEX_LEXER_H

# include "tok.h"

typedef int8_t		(*t_lrule)(t_tok *, char, t_src *);

typedef struct		s_lexer
{
	t_vec			srcs;
	t_vec			toks;
	t_vec			vals;
	t_vec			rules;
}					t_lexer;

extern void			ft_lexer_ctor(t_lexer *self);
extern void			ft_lexer_dtor(t_lexer *self);
extern t_bool		ft_lexer_init_file(t_lexer *self, char const *filename);
extern t_bool		ft_lexer_init_str(t_lexer *self, char const *s);
extern t_bool		ft_lexer_init_nstr(t_lexer *self, char const *s, size_t n);
extern ssize_t		ft_lexer_scan(t_lexer *self, size_t n);

#endif
