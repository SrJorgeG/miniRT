
#include "../../include/minirt.h"

static size_t ft_findchr(char const *s, char c[2])
{
	size_t i;

	i = 0;
	while (s[i] && s[i] != c[0] && s[i] != c[1])
		i++;
	return (i);
}

static size_t ft_count_words(char const *s, char c[2])
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c[0] || *s == c[1])
		{
			if (in_word)
			{
				count++;
				in_word = 0;
			}
		}
		else
			in_word = 1;
		s++;
	}
	if (in_word)
		count++;
	return (count);
}

static void ft_copy_word(char *dest, const char *src, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

char **ft_split_2(char const *s, char c[2])
{
	size_t	words;
	size_t	i;
	char	**list;
	size_t	wordsize;

	if (! s)
		return (NULL);
	words = ft_count_words(s, c);
	list = malloc((words + 1) * sizeof(char *));
	if (list == NULL)
		return (NULL);
	list[words] = NULL;
	i = 0;
	while (i < words)
	{
		while (*s && (*s == c[0] || *s == c[1]))
			s++;
		wordsize = ft_findchr(s, c);
		list[i] = malloc((wordsize + 1) * sizeof(char));
		if (list[i] == NULL)
		{
			while (i > 0)
				free(list[--i]);
			free(list);
			return (NULL);
		}
		ft_copy_word(list[i], s, wordsize);
		s += wordsize;
		i++;
	}
	return (list);
}