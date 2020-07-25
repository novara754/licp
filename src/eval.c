#include "eval.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

typedef int (*fn)(expr_node **args, size_t args_len);
typedef struct
{
    const char *name;
    fn f;
} builtin_fn;

int eval(expr_node *n);

int add(expr_node **args, size_t args_len)
{
    int sum = 0;
    for (size_t i = 0; i < args_len; i++)
        sum += eval(args[i]);
    return sum;
}

int sub(expr_node **args, size_t args_len)
{
    if (args_len == 0)
        return 0;

    int diff = eval(args[0]);

    for (size_t i = 1; i < args_len; i++)
        diff -= eval(args[i]);

    return diff;
}

builtin_fn builtin_fns[] = {
    {"+", add},
    {"-", sub},
};

int call_builtin(const char *fname, size_t fname_len, expr_node **args, size_t args_len)
{
    size_t builtin_fns_len = sizeof(builtin_fns) / sizeof(builtin_fn);
    for (size_t i = 0; i < builtin_fns_len; i++)
    {
        if (strncmp(builtin_fns[i].name, fname, fname_len) == 0)
            return builtin_fns[i].f(args, args_len);
    }

    printf("no such function: %.*s\n", (int)fname_len, fname);
    return 0;
}

int eval(expr_node *n)
{
    switch (n->kind)
    {
        case NODE_CONST_EXPR: return n->number_value.value;
        case NODE_S_EXPR:
            return call_builtin(n->s_expr_value.fname.source, n->s_expr_value.fname.len, n->s_expr_value.args,
                                n->s_expr_value.args_len);
        default: assert(0);
    }
}
