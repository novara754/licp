#pragma once

#include <stdlib.h>

typedef enum
{
    TOKEN_OPAREN,
    TOKEN_CPAREN,
    TOKEN_IDENT,
    TOKEN_NUMBER,
    TOKEN_UNKNOWN,
    TOKEN_EOF,
} token_kind;

typedef struct
{
    token_kind kind;
    const char *source;
    size_t len;
} token;

typedef struct
{
    const char *source;
    size_t pos;
} lexer_state;

lexer_state make_lexer(const char *source);
token next_token(lexer_state *state);
