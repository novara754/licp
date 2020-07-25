#include "parser.h"
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    lexer_state lexer;
    jmp_buf error_jmp;
} parser_state;

static parser_state make_parser(const char *source)
{
    return (parser_state){
        .lexer = make_lexer(source),
    };
}

static inline void pabort(parser_state *state)
{
    longjmp(state->error_jmp, -1);
}

static inline token expect(parser_state *state, token_kind expected)
{
    token t = next_token(&state->lexer);
    if (t.kind != expected)
        pabort(state);
    return t;
}

static inline void revert(parser_state *state, token *t)
{
    if (state->lexer.pos > 0)
        state->lexer.pos -= t->len;
}

static token peek(parser_state *state)
{
    token t = next_token(&state->lexer);
    revert(state, &t);
    return t;
}

static expr_node *make_s_expr_node(token fname)
{
    expr_node *n = malloc(sizeof(expr_node));
    n->kind = NODE_S_EXPR;
    n->s_expr_value.fname = fname;
    return n;
}

static expr_node *make_const_expr_node(token number)
{
    expr_node *n = malloc(sizeof(expr_node));
    n->kind = NODE_CONST_EXPR;
    n->number_value.raw = number;
    n->number_value.value = strtol(number.source, NULL, 10);
    return n;
}

static expr_node *parse_s_expr(parser_state *state);
static expr_node *parse_const_expr(parser_state *state);

static expr_node *parse_expression(parser_state *state)
{
    if (peek(state).kind == TOKEN_OPAREN)
        return parse_s_expr(state);
    else
        return parse_const_expr(state);
}

static expr_node *parse_s_expr(parser_state *state)
{
    expect(state, TOKEN_OPAREN);

    token fname = expect(state, TOKEN_IDENT);

    expr_node *n = make_s_expr_node(fname);
    while (peek(state).kind != TOKEN_CPAREN && n->s_expr_value.args_len < MAX_ARGS)
        n->s_expr_value.args[n->s_expr_value.args_len++] = parse_expression(state);

    expect(state, TOKEN_CPAREN);
    return n;
}

static expr_node *parse_const_expr(parser_state *state)
{
    token number = expect(state, TOKEN_NUMBER);
    return make_const_expr_node(number);
}

expr_node *parse(const char *source)
{
    parser_state state = make_parser(source);
    if (setjmp(state.error_jmp) == -1)
        return NULL;
    return parse_expression(&state);
}

void free_ast(expr_node *node)
{
    switch (node->kind)
    {
        case NODE_CONST_EXPR: free(node); break;
        case NODE_S_EXPR:
            for (size_t i = 0; i < node->s_expr_value.args_len; i++)
                free_ast(node->s_expr_value.args[i]);
            free(node);
            break;
    }
}
