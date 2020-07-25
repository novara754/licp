#include "eval.h"
#include "parser.h"
#include <stdbool.h>
#include <stdio.h>

#define INPUT_SIZE 1024

const char *token_kind_str(token_kind kind)
{
#define TO_STRING(kind) \
    case kind: return #kind

    switch (kind)
    {
        TO_STRING(TOKEN_OPAREN);
        TO_STRING(TOKEN_CPAREN);
        TO_STRING(TOKEN_IDENT);
        TO_STRING(TOKEN_NUMBER);
        TO_STRING(TOKEN_UNKNOWN);
        TO_STRING(TOKEN_EOF);
        default: return "INVALID";
    }
#undef TO_STRING
}

void repl(void)
{
    while (!feof(stdin))
    {
        printf("> ");
        fflush(stdout);

        char input[INPUT_SIZE];
        if (fgets(input, INPUT_SIZE, stdin) == NULL)
            break;
        if (input[0] == 0 || input[0] == '\n')
            continue;

        expr_node *ast = parse(input);
        if (ast != NULL)
        {
            printf("%d\n", eval(ast));
            free_ast(ast);
        }
        else
            puts("invalid input");
    }
}

int main(void)
{
    repl();
    return 0;
}
