#pragma once

#include "lexer.h"

#define MAX_ARGS 5

struct expr_node;

typedef struct
{
    token fname;
    struct expr_node *args[MAX_ARGS];
    size_t args_len;
} s_expr;

typedef struct
{
    token raw;
    int value;
} const_expr;

typedef enum
{
    NODE_S_EXPR,
    NODE_CONST_EXPR,
} node_kind;

typedef struct expr_node
{
    node_kind kind;
    union {
        s_expr s_expr_value;
        const_expr number_value;
    };
} expr_node;

expr_node *parse(const char *source);
void free_ast(expr_node *ast);
