/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:27:07 by zhedlund          #+#    #+#             */
/*   Updated: 2024/02/23 22:17:22 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_tree.h"

/* 	start_ptr: pointer to the first character of the string to be copied
	end_ptr: pointer to the last character of the string to be copied
	return: pointer to the copy of the string
	note: the copy is allocated on the heap and must be freed by the caller */
	
char *make_copy(char *start_ptr, char *end_ptr)
{
	size_t len;
	char *copy;

	len = end_ptr - start_ptr;
	copy = malloc(len + 1);
	if (copy != NULL)
		ft_strlcpy(copy, start_ptr, len + 1); //copy n characters from s to c and ensure null-termination
	return (copy);
}

int	is_whitespace(const char *buf)
{
    while (*buf != '\0')
	{
		if (!ft_isspace(*buf))
            return (0);
        buf++;
    }
    return (1);
}

/*libft functions, remove after linking libft*/
void	*ft_memset(void *s, int c, size_t n)
{
	char	*ps;
	char	uc;

	ps = (char *)s;
	uc = (char)c;
	while (n > 0)
	{
		ps[n - 1] = uc;
		n--;
	}
	return (ps);
}

size_t	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

char	*ft_strpbrk(const char *s1, const char *s2)
{
	int i = 0;

	if (!s1 || !s2)
		return (0);
	while (*s1)
	{
		i = 0;
		while (s2[i])
		{
			if (*s1 == s2[i])
				return ((char *)s1);
			i++;
		}
		s1++;
	}
	return (0);
}

char *ft_strtok(char *str, const char *delim)
{
	static char	*token;
	char		*found;
	char		*result;
	
	if (str != NULL)
		token = str;
	if (token == NULL || *token == '\0')
		return (NULL);
	found = ft_strpbrk(token, delim);
	if (found != NULL)
	{
		*found = '\0';
		found++;
	}
	result = token;
	token = found;
	return (result);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!str)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s1[i] == s2[i] && i < n -1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	srclen;

	srclen = ft_strlen(src);
	if (size == 0)
		return (srclen);
	i = 0;
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	ch;

	ch = c;
	if (ch == '\0')
	{
		i = ft_strlen(s);
		return ((char *)s + i++);
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	int		i;
	void	*str;
	char	*new;
	int		hold;

	hold = (nmemb * size);
	i = 0;
	str = malloc(sizeof(void) * hold);
	new = (char *)str;
	if (!str)
		return (NULL);
	while (hold != 0)
	{
		new[i] = '\0';
		i++;
		hold--;
	}
	str = (void *)new;
	return (str);
}

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

char	*ft_mallocjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*join;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	join = malloc((i + j + 1) * sizeof(char));
	if (!join)
		return (0);
	return (join);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*join;

	i = 0;
	j = 0;
	if ((*s1 == '\0') && (*s2 == '\0'))
		return (ft_strdup(""));
	join = ft_mallocjoin(s1, s2);
	if (!join)
		return (0);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		join[i] = s2[j];
		i++;
		j++;
	}
	join[i] = '\0';
	return (join);
}

int	ft_atoi(const char *nptr)
{
	int	minus;
	int	i;
	int	b;

	b = 0;
	minus = 1;
	i = 0;
	while (nptr[b] == ' ' || (nptr[b] >= 9 && nptr[b] <= 13))
		nptr++;
	if (nptr[b] == '-')
		minus *= -1;
	if (nptr[b] == '+' || nptr[b] == '-')
		nptr++;
	if (nptr[b] < '0' || nptr[b] > '9')
		return (0);
	while (nptr[b] == '0')
		nptr++;
	while (nptr[b] >= '0' && nptr[b] <= '9')
	{
		i = (nptr[b] - '0') + i * 10;
		b++;
	}
	return (i * minus);
}

static char	*num_to_array(char *arr, unsigned int number, long int len)
{
	while (number > 0)
	{
		arr[len--] = 48 + (number % 10);
		number = number / 10;
	}
	return (arr);
}

static long int	num_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	long int		len;
	unsigned int	num;

	len = num_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!(str))
		return (NULL);
	str[len--] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		num = n * -1;
		str[0] = '-';
	}
	else
		num = n;
	str = num_to_array(str, num, len);
	return (str);
}

int ft_isspace(char c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r')
        return (1);
    else
        return (0);
}
