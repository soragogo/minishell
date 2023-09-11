ファイルと関数名説明
【tokenizer.h】
tokenizer関数のための構造体定義とenumが要チェッ。

渡されたコマンドは単語ごとに構造体のリストt_tokenに格納した。それぞれの単語は、argに格納されていて、argに関する情報がtype, is_freedに格納されている。
type=> クオートなし単語、''で渡された単語、""で渡された単語、パイプ。enum参照
is_freed=>フリーしてない場合、０。フリーされている場合、１。getpath.cでフリーのタイミングがズレるため、フリータイミングをトラックするために実装した。
typedef struct s_list
{
	char *arg;
	TYPE type;
    int is_freed;
} t_token;


~~typedef enum~~
~~{~~
~~	NON_EXPANDABLE,　=>~~
~~	EXPANDABLE_QUOTED, =>~~
~~	PIPE, =>~~
~~	EXPANDABLE, =>~~
~~} TYPE;~~

--------------------------------------------------
9/11　enum変えた！
tokenizer.cで単語ごとに切り分け。
parserで文法解析して下のどれのカテゴリーに入るか分類した。

typedef enum
{
	UNCATEGORIZED,
	PIPE,		   // | (パイプ)
	REDIRECT_OUT,  // > (リダイレクト出力)
	REDIRECT_IN,   // < (リダイレクト入力)
	APPEND_OUT,	   // >> (出力の追加)
	HERE_DOCUMENT, // << (ヒアドキュメント)
	COMMAND,
	COMMAND_OPTION,
	FILE_NAME
} TYPE;
