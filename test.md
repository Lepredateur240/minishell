# Liste des fonctions - Minishell

### src/main.c
- `int main(int argc, char *argv[], char **envp)`


///////////////////////////////////////////////// ENV
### src/env/env_init.c NORM
- `static int fill_env_data(t_env *new_node, char *str)`
- `static t_env *new_env_node(char *str)`
- `t_list *init_env(char **envp)`

### src/env/env_utils.c NORM
- `char *get_env_value(t_minishell *minishell, char *key)`

### src/env/env_path.c NORM
- `char **get_exec_path(t_minishell *minishell)`


///////////////////////////////////////////////// EXEC
### src/exec/exec_path.c NORM
- `static char *find_exec(char **cmd, char **path)`
- `void find_path(t_minishell *minishell)`



///////////////////////////////////////////////// PARSING
### src/parsing/cmds_builder.c NORM
- `int format_cmds(t_minishell *minishell, t_list *token_list)`

### src/parsing/expands.c NORM
- `static char *integrate_expand(char *token, char *expand_start, char *expand_key, char *expand_value)`
- `static char *is_there_expands(char *word)`
- `static char *extract_expand(char *word)`
- `static int	token_expands(t_minishell *minishell, t_token *token)`
- `int handle_expands(t_minishell *minishell, t_list *token_list)`

### src/parsing/lexer.c NORM
- `static t_type get_type(char *token)`
- `static void each_token(char *prompt, int start, int *i)`
- `static t_token *get_token(char *prompt, int *i)`
- `t_list *list_token(char *prompt)`

### src/parsing/parser.c
- `t_cmd *init_cmd_struct(void)`
- `void parsing_prompt(t_minishell *minishell, char *prompt)`

### src/parsing/post_expands.c
- `void remake_token_list(t_list **token_list)`

### src/parsing/quotes.c NORM
- `void update_quote_state(char c, int *state)`
- `int get_quote_state(char *str, int index)`
- `int verify_unclosed_quotes(char *prompt)`

### src/parsing/syntax.c NORM
- `int syntax_token_list(t_token *token, t_token *next)`
- `int verify_token_list(t_list *token_list)`

### src/parsing/utils.c NORM
- `int count_args(t_list *token_list)`


///////////////////////////////////////////////// UTILS
### src/utils/free.c NORM
- `void free_token(void *content)`
- `void free_cmds(void *content)`
- `void free_env(void *content)`
- `void free_tab(char **tab)`
- `void free_all(t_minishell *minishell)`

### src/utils/ft_split_unquoted.c NORM
- `static size_t ft_count_word(char const *s, char c)`
- `static size_t ft_len_word(char const *s, char c)`
- `static void ft_freeall(char **tab, size_t index)`
- `static int ft_putwords(char **tab, char const *s, char c, size_t nbr_words)`
- `char **ft_split_unquoted(char const *s, char c)`


///////////////////////////////////////////////// TEST
### src/test.c
- `void test_print_env(t_list *env)`
- `void test_print_exec_path_tab(char **exec_path_tab)`
- `void test_print_list_token(t_list *token_list)`
- `void test_print_minish_cmds(t_minishell *minishell)`