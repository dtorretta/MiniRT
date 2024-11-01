/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:07:23 by dtorrett          #+#    #+#             */
/*   Updated: 2024/05/28 18:55:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//If we have the string ababaaaMy name is Simonbbaaabbad and our set is ab, we'll get this result out of the ft_strtrim() function : My name is Simon.
//We removed every a and b from the start and the end of s1, without touching at the a in the middle of s1.

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*result;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	end = ft_strlen(s1) - 1;
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (s1[end] && ft_strchr(set, s1[end]))
		end--;
	result = ft_substr(s1, start, (end - start + 1));
	return (result);
}
/*
int	main(void)
{
	char	str[] = "Trick or treat?";
	char	str1[] = "T or?";
	char *result = ft_strtrim(str, str1);
	printf("%s\n", result);
}*/
