// #include "../includes/minishell.h"

// // void handle_pipe(t_token *tokens, t_info *info){
// //     pid_t pid;
// //     t_redirect *node;
// //     extern char **environ;

// //     node = tokens->node;
// //     pid = fork();
// //     if (pid < 0)
// //         printf("fork");
// //     else// if (pid == 0)
// //     {
// //         // child process
// //         if (pipe(node->outpipe) < 0)
// //             printf("pipe error");
// //         if (node->next)
// //         {
// //             node->next->inpipe[0] = node->outpipe[1];
// //             tokens->node->filefd = STDOUT_FILENO;
// //             tokens->node->new_fd = node->outpipe[1];
// //             // do_redirect(tokens->node);
// //         }
// //         execve(info->tokens->arg, &info->tokens->arg, environ);
// //     }
// // }

// // t_redirect *create_node(t_token *tokens){
// //     t_redirect *node;

// //     node = (t_redirect *)malloc(sizeof(t_redirect));
// //     node->filename = tokens;
// //     node->inpipe[0] = STDIN_FILENO;
// // 	node->inpipe[1] = -1;
// // 	node->outpipe[0] = -1;
// // 	node->outpipe[1] = STDOUT_FILENO;
// //     node->next = NULL;
// //     return (node);
// // }

// typedef enum			e_pipe_state
// {
// 	NO_PIPE,
// 	PIPE_READ_ONLY,
// 	PIPE_WRITE_ONLY,
// 	PIPE_READ_WRITE
// }						t_pipe_state;

// void handle_pipe(t_token *tokens, t_info *info){
//     pid_t pid;
//     t_redirect *node;
//     extern char **environ;

//     node = tokens->node;
//     pid = fork();
//     if (pid < 0)
//         printf("fork");
//     else// if (pid == 0)
//     {
//         // child process
//         if (pipe(node->outpipe) < 0)
//             printf("pipe error");
//         if (node->next)
//         {
//             node->next->inpipe[0] = node->outpipe[1];
//             tokens->node->filefd = STDOUT_FILENO;
//             tokens->node->new_fd = node->outpipe[1];
//             // do_redirect(tokens->node);
//         }
//         execve(info->tokens->arg, &info->tokens->arg, environ);
//     }
// }

