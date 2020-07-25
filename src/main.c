#include "lexer.h"
#include <stdio.h>

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

int main(void)
{
    const char *source = "(+ 1 2 3)";
    lexer_state state = make_lexer(source);
    token t;
    do
    {
        t = next_token(&state);
        printf("token(kind=%s, start=%ld, len=%ld) = '%.*s'\n", token_kind_str(t.kind), t.start, t.len, (int)t.len,
               source + t.start);
    } while (t.kind != TOKEN_EOF);

    return 0;
}
