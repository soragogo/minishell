// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main2.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: emukamada <emukamada@student.42.fr>        +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/08/22 16:57:51 by emukamada         #+#    #+#             */
// /*   Updated: 2023/08/22 17:33:55 by emukamada        ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include <libc.h>
// #include "token.h"
// #include <assert.h>

// int main(void)
// {
// 	t_token *tmp;

// 	tmp = ft_tokenizer("\"a\"b\'b\' || \"aaaaa\" \'abc\'");
// 	assert(strcmp(tmp[0].arg, "a") == 0);
// 	assert(tmp[0].type == 1);
// 	printf("%s = a : %d = 1\n", tmp[0].arg, tmp[0].type);
// 	printf("%s = b : %d = 3\n", tmp[1].arg, tmp[1].type);
// 	printf("%s = b : %d = 0\n", tmp[2].arg, tmp[2].type);
// 	printf("%s = | : %d = 2\n", tmp[3].arg, tmp[3].type);
// 	printf("%s = | : %d = 2\n", tmp[4].arg, tmp[4].type);
// 	printf("%s = aaaaa : %d = 1\n", tmp[5].arg, tmp[5].type);
// 	printf("%s = abc : %d = 0\n", tmp[6].arg, tmp[6].type);
// 	exit(0);
// }
