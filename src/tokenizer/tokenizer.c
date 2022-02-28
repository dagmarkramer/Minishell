#include "minishell.h"

int	ms_find_word_end(char *input, int i, char state)
{
	if (state == '\'')
	{
		i = ms_find_offset(input, "\'", i);
		if (input[i] == '\0')
			return (i);
		return (ms_find_word_end(input, i + 1, 0));
	}
	if (state == '\"')
	{
		i = ms_find_offset(input, "\"", i);
		if (input[i] == '\0')
			return (i);
		return (ms_find_word_end(input, i + 1, 0));
	}
	else
	{
		i = ms_find_offset(input, "\"\' \t\n|><", i);
		if (input[i] == '\0')
			return (i);
		if (ft_strchr(" \t\n", input[i]))
			return (i);
		if (ft_strchr("|<>", input[i]))
			return (i + 1);
		return (ms_find_word_end(input, i + 1, input[i]));
	}
}

char	*ms_claim_word(char *input, int start, int size)
{
	char	*new_word;

	new_word = malloc(size + 1);
	new_word[size] = 0;
	if (new_word == NULL)
		return (NULL);
	return(ft_memcpy(new_word, &input[start], size));
}

int	ms_add_tokens(t_list **tokens, char *input)
{
	int		i;
	int		start;
	char	*new_word;

	i = 0;
	while (input[i])
	{
		start = ms_skip_chars(input, " \t\n", i);	// this is different now not 0 but i instead
		i = start;
		i = ms_find_word_end(input, i, 0); // did i do this right?
		new_word = ms_claim_word(input, start, i - start);
		if (new_word == NULL)
			return (1);
		if(ms_lstadd_token(tokens, new_word))
			return (1);
		start = i;
	}
	return (0);
}

t_list	*ms_tokenizer(char *input)
{
	t_list	*tokens;

	tokens = 0;
	if (ms_add_tokens(&tokens, input))
	{
		ft_lstclear(&tokens, ms_del_token);
		// ms_new_prompt();
	}
	return (tokens);
}
