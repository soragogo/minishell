#include "../includes/minishell.h"
#include "../tokenizer/token.h"


// typedef struct s_node
// {
// 	int newfd;		//bのfd
// 	int stashfd;	//一時保存
// 	int oldfd;		//a>b -> STDOUT_FILENO, a<b -> STDIN_FILENO a
// 	const char *filename;
// 	struct s_node	*next;
// 	struct s_node	*prev;
// }	t_redirect;

t_redirect *create_node(t_token *tokens){
    t_redirect *node;

    node = (t_redirect *)malloc(sizeof(t_redirect));
    node->filename = tokens->arg;
	node->next = NULL;
    return (node);
}

void handle_redirection(t_token *tokens)
{
	if (tokens == NULL)
		return ;
		// tokens->node = (t_redirect *)malloc(sizeof(t_redirect));
	if (tokens->type == REDIRECT_OUT)
	{
		redirect_out(tokens);
		// tokens->node->oldfd = STDOUT_FILENO;
	}
	else if (tokens->type == REDIRECT_IN)
	{
		redirect_in(tokens);
		// tokens->node->oldfd = STDIN_FILENO;
	}
	else if (tokens->type == HERE_DOCUMENT)
	{
		// tokens->node->oldfd = STDIN_FILENO;
		here_document(tokens);
	}
}

void redirect_out(t_token *tokens)
{
	// int fd;

	tokens->node->oldfd = STDOUT_FILENO;
	tokens->node->newfd = open(tokens->node->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	do_redirect(tokens->node);
	printf("\nfd:%d\n", tokens->node->newfd);
}

void redirect_in(t_token *tokens){
	// int fd;

	tokens->node->oldfd = STDIN_FILENO;
	tokens->node->newfd = open(tokens->node->filename, O_RDONLY);
	do_redirect(tokens->node);
	printf("\nfd:%d\n", tokens->node->newfd);
}

void here_document(t_token *tokens){
	// int fd;

	tokens->node->oldfd = STDIN_FILENO;
	tokens->node->newfd = heredoc("EOF");
	do_redirect(tokens->node);
	printf("\nfd:%d\n", tokens->node->newfd);
}

//cat a > b
void do_redirect(t_redirect *node){
	if (node == NULL)
		return ;
	// node->newfd = open(node->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	node->stashfd = dup(node->oldfd);//STDOUT_FILENOを一時保存
	dup2(node->newfd, node->oldfd);//bのfdをSTDOUT_FILENOにコピー
	do_redirect(node->next);
}

void undo_redirect(t_redirect *node){
	if (node == NULL)
		return ;
	undo_redirect(node->next);
	dup2(node->stashfd, node->oldfd);//一時保存したSTDOUT_FILENOを復元
	close(node->newfd);
}

int heredoc(const char *delimiter){//pipeの読み込み側fdを返す
	int pipefd[2];
	char *line;

	pipe(pipefd);
	while(1){
		line = readline("> ");
		if (line == NULL)
			break ;
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	/*------------------- vscode debug 用 ---------------------*/
	// char *line[3] = {"Hello, world!\n", "asdgfdg\n", "EOF"};
	// for (int i = 0; i < 3; i++)
	// {
	// 	if (strcmp(line[i], delimiter) == 0)
	// 	{
	// 		// free(line[i]);
	// 		break ;
	// 	}
	// 	write(pipefd[1], line[i], strlen(line[i]));
	// 	write(pipefd[1], "\n", 1);
	// 	i++;
	// }
	/*------------------- vscode debug 用 ---------------------*/
	close(pipefd[1]);
	return (pipefd[0]);
}

// int main() {
//     // ダミーのトークンを作成（これはあなたのプログラムでトークンを生成する部分に相当します）
//     t_token *tokens = (t_token *)malloc(sizeof(t_token));
//     tokens->type = HERE_DOCUMENT; // 例: 標準出力リダイレクション
// 	tokens->node = (t_redirect *)malloc(sizeof(t_redirect));
//     tokens->node->filename = "output.txt"; // 出力ファイル名

//     // トークンにノードを作成
//     create_node(tokens);

//     // リダイレクションを実行
//     handle_redirection(tokens);

//     // ここで何かコマンドを実行する
// 	write(tokens->node->oldfd, "Hello, world!1\n", 14);
// 	char buf[1024];
// 	// read(STDIN_FILENO, buf, 14);

//     // リダイレクションを元に戻す
//     undo_redirect(tokens->node);
// 	write(tokens->node->oldfd, "Hello, world!2\n", 14);
//     // メモリの解放（実際のプログラムでは適切なタイミングで行う必要があります）
//     free(tokens->node);
//     free(tokens);

//     return 0;
// }

// int main() {
//     const char *delimiter = "EOF"; // 区切り文字を指定
//     int input_fd;

//     // ヒアドキュメントを呼び出し
//     input_fd = heredoc(delimiter);

//     // ヒアドキュメントからのデータを読み取り、表示
//     char buffer[1024];
//     ssize_t n;
//     while ((n = read(input_fd, buffer, sizeof(buffer))) > 0) {
//         write(STDOUT_FILENO, buffer, n);
//     }

//     // ヒアドキュメントからのデータの読み取りが終了したらファイルディスクリプタを閉じる
//     close(input_fd);

//     return 0;
// }



// int main()
// {
//     // ダミーのトークンを作成
//     t_redirect *redirect = (t_redirect *)malloc(sizeof(t_redirect));
//     redirect->filename = "output.txt"; // 出力ファイル名
//     redirect->oldfd = STDOUT_FILENO;   // 標準出力に対するリダイレクト
// 	redirect->next = NULL;

// 	t_token *tokens = (t_token *)malloc(sizeof(t_token));
// 	tokens->node = redirect;
// 	tokens->type = REDIRECT_OUT;


//     // 新しいファイルディスクリプタを作成
//     int newfd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
//     redirect->newfd = newfd;
// 	printf("\nfd:%d\n", redirect->newfd);
// 	fflush(stdout);

//     // リダイレクトを実行
//     // do_redirect(redirect);
// 	handle_redirection(tokens);

//     // ファイルディスクリプタを使ってデータを書き込み
//     write(newfd, "This should go to output.txt\n", 30);
// 	char *buf[1024];
// 	read(newfd, *buf, 1024);
// 	printf("%s\n", *buf);

//     // リダイレクトを元に戻す
//     undo_redirect(redirect);

//     // メモリの解放
//     free(redirect);

//     return 0;
// }