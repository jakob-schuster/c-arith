#include "intexp.h"
#include <stdio.h>
#include <stdlib.h>

int 
main()
{
    // construct the expression (1 + (2 * -2))
    node_t* node = node_binop_addition_create(
        node_intlit_create(1),
        node_binop_multiplication_create(
            node_intlit_create(2), 
            node_unop_minus_create(node_intlit_create(2))
        )
    );

    // print out the expression
    node_print(node);
    // evaluate it
    printf(" = %d", node_eval(node));

    // free it at the end
    node_destroy(node);
}

// 

node_t*
node_intlit_create(int i)
{
    node_t* node = malloc(sizeof(node_t));
    node->tag = 'i';
    node->data = intlit_create(i);

    return(node);
}

node_t*
node_unop_minus_create(node_t* node) 
{
    node_t* node1 = malloc(sizeof(node_t));
    node1->tag = 'u';
    node1->data = unop_create('-', node);

    return(node1);
}

node_t*
node_binop_addition_create(node_t* left, node_t* right)
{
    node_t* node = malloc(sizeof(node_t));
    node->tag = 'b';
    node->data = binop_create('+', left, right);

    return(node);
}

node_t*
node_binop_subtraction_create(node_t* left, node_t* right)
{
    node_t* node = malloc(sizeof(node_t));
    node->tag = 'b';
    node->data = binop_create('-', left, right);

    return(node);
}

node_t*
node_binop_multiplication_create(node_t* left, node_t* right)
{
    node_t* node = malloc(sizeof(node_t));
    node->tag = 'b';
    node->data = binop_create('*', left, right);

    return(node);
}

node_t*
node_binop_division_create(node_t* left, node_t* right)
{
    node_t* node = malloc(sizeof(node_t));
    node->tag = 'b';
    node->data = binop_create('/', left, right);

    return(node);
}

void
node_print(node_t* node)
{
    if (node->tag == 'i') {
        intlit_print(node->data);
    } else if (node->tag == 'u') {
        unop_print(node->data);
    } else if (node->tag == 'b') {
        binop_print(node->data);
    }
}

int
node_eval(node_t* node)
{
    if (node->tag == 'i') {
        return(intlit_eval(node->data));
    } else if (node->tag == 'u') {
        return(unop_eval(node->data));
    } else if (node->tag == 'b') {
        return(binop_eval(node->data));
    }

    // shouldn't get here
    return(-1);
}

void
node_destroy(node_t* node)
{
    if (node->tag == 'i') {
        intlit_destroy(node->data);
    } else if (node->tag == 'u') {
        unop_destroy(node->data);
    } else if (node->tag == 'b') {
        binop_destroy(node->data);
    }
}

// 

intlit_t*
intlit_create(int i)
{
    intlit_t* intlit = malloc(sizeof(intlit_t));
    intlit->i = i;

    return(intlit);
}

void
intlit_print(intlit_t* intlit)
{
    printf("%d", intlit->i);
}

int
intlit_eval(intlit_t* intlit)
{
    return(intlit->i);
}

void
intlit_destroy(intlit_t* intlit)
{
    free(intlit);
}

// 

unop_t*
unop_create(char tag, node_t* node)
{
    unop_t* unop = malloc(sizeof(unop_t));
    unop->tag = tag;
    unop->node = node;

    return(unop);
}

void
unop_print(unop_t* unop)
{
    // directly print the tag, as it corresponds to the operation
    printf("%c", unop->tag);
    node_print(unop->node);
}

int
unop_eval(unop_t* unop)
{
    if (unop->tag == '-') {
        return(-node_eval(unop->node));
    }

    // shouldn't get here
    return(-1);
}

void
unop_destroy(unop_t* unop)
{
    node_destroy(unop->node);
    free(unop);
}

// 

binop_t*
binop_create(char tag, node_t* left, node_t* right)
{
    binop_t* binop = malloc(sizeof(binop_t));
    binop->tag = tag;
    binop->left = left;
    binop->right = right;

    return(binop);
}

void
binop_print(binop_t* binop)
{
    // directly print the tag, as it corresponds to the operation

    printf("(");
    node_print(binop->left);
    printf(" %c ", binop->tag);
    node_print(binop->right);
    printf(")");
}

int 
binop_eval(binop_t* binop)
{
    int left = node_eval(binop->left);
    int right = node_eval(binop->right);

    if (binop->tag == '+') {
        return(left + right);
    } else if (binop->tag == '-') {
        return(left - right);
    } else if (binop->tag == '*') {
        return(left * right);
    } else if (binop->tag == '/') {
        return(left / right);
    }

    // shouldn't get here
    return(-1);
}

void
binop_destroy(binop_t* binop)
{
    node_destroy(binop->left);
    node_destroy(binop->right);
    free(binop);
}
