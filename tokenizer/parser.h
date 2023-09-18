#ifndef PARSER_H
#define PARSER_H

#include <libc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "token.h"

typedef struct s_command
{
	t_token *command;
} t_command;

#endif
