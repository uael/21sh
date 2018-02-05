/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/lex.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:28:28 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_LEX_H
# define USH_LEX_H

# include <librl.h>
# include "err.h"
# include "var.h"
# include "word.h"

enum			e_tok
{
	TOK_END = '\0',
	TOK_HEREDOC = TOK_END + 1,
	TOK_HEREDOCT,
	TOK_RAOUT,
	TOK_LAMP,
	TOK_RAMP,
	TOK_CMP,
	TOK_EOL = '\n',
	TOK_RPOUT = TOK_EOL + 1,
	TOK_AMPR,
	TOK_LAND,
	TOK_LOR,
	TOK_CASE,
	TOK_DO,
	TOK_DONE,
	TOK_ELIF,
	TOK_ELSE,
	TOK_FUNCTION,
	TOK_FOR,
	TOK_FI,
	TOK_IF,
	TOK_IN,
	TOK_ESAC,
	TOK_SELECT,
	TOK_THEN,
	TOK_UNTIL,
	TOK_WHILE,
	TOK_WORD,
	TOK_TRUE,
	TOK_FALSE,
	TOK_NOT = '!',
	TOK_VAR = TOK_NOT + 1,
	TOK_AMP = '&',
	TOK_LPAR = '(',
	TOK_RPAR = ')',
	TOK_HYPEN = '-',
	TOK_SEMICOLON = ';',
	TOK_RIN = '<',
	TOK_ASSIGN = '=',
	TOK_ROUT = '>',
	TOK_LBRACKET = '[',
	TOK_RBRACKET = ']',
	TOK_BQUOTE = '`',
	TOK_LCURLY = '{',
	TOK_PIPE = '|',
	TOK_RCURLY = '}',
};

# define SYNCH "!;()`"
# define OPCH SYNCH"><&|"

# define ISREOL(IT) (*(IT) == '\n')
# define ISWEOL(IT) (*(IT) == '\r' && *((IT) + 1) == '\n')
# define ISEOL(IT) (ISREOL(IT) || ISWEOL(IT))

# define TOK_ISREDIR_1(ID) ((ID)==TOK_RIN||(ID)==TOK_ROUT)
# define TOK_ISREDIR_2(ID) ((ID)!=TOK_EOL&&((ID)>=TOK_HEREDOC&&(ID)<=TOK_AMPR))
# define TOK_ISREDIR(ID) (TOK_ISREDIR_1(ID)||TOK_ISREDIR_2(ID))
# define TOK_ISBOOL(ID) ((ID)==TOK_TRUE||(ID)==TOK_FALSE)
# define TOK_ISWORD(I) (TOK_ISBOOL(I)||(I)==TOK_WORD||(I)==TOK_VAR||(I)=='`')
# define TOK_ISEND(ID) ((ID)==TOK_EOL||(ID)==TOK_END)
# define TOK_ISSEP(ID) ((ID)==TOK_SEMICOLON||(ID)==TOK_AMP)
# define TOK_ISHDOC(ID) ((ID)==TOK_HEREDOC||(ID)==TOK_HEREDOCT)
# define TOK_ISCMDM(ID) (TOK_ISWORD(ID)||TOK_ISREDIR(ID))

enum			e_tspec
{
	TSPEC_CONTINUOUS = 1 << 1,
	TSPEC_SQUOTE = 1 << 2,
	TSPEC_DQUOTE = 1 << 3
};

typedef union	u_tokv
{
	t_sds		word;
	int			fd;
}				t_tokv;

typedef struct	s_tok
{
	char		*val;
	size_t		cap;
	size_t		len;
	uint16_t	pos;
	uint8_t		id;
	char		spec;
}				t_tok;

typedef struct	s_tok2
{
	char		*val;
	size_t		cap;
	size_t		len;
	uint16_t	pos;
	uint8_t		id;
}				t_tok2;

typedef struct	s_tokit
{
	char		**it;
	char		**ln;
}				t_tokit;

typedef int		(t_tokcb)(int fd, t_deq *toks, char **ln);

extern char		*sh_tokstr(t_tok *tok);

extern int		sh_tokenize(int fd, char **it, char **ln, t_tokcb *cb);
extern int		sh_lexvar(int fd, t_tok2 *tok, char **it, char **ln);
extern int		sh_lexop(int fd, t_tok2 *tok, char **it, char **ln);
extern int		sh_lexbslash(int fd, char **it, char **ln);
extern int		sh_lexword(int fd, t_tok2 *tok, char **it, char **ln);
extern int		sh_lexheredoc(int fd, t_tok2 *tok, char **it, char **ln);
extern int		sh_lexheredoct(int fd, t_tok2 *tok, char **it, char **ln);
extern int		sh_lexreduce(int fd, t_deq *toks, char **it, char **ln);
extern char		sh_rbracket(char b);
extern t_bool	sh_isname(char *word);

#endif
