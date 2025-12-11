// integer expression language

typedef struct node {
    char tag;
    // i int lit
    // u unop
    // b binop

    void* data;
} node_t;

node_t*
node_intlit_create(int i);

node_t*
node_unop_minus_create(node_t* node);

node_t*
node_binop_addition_create(node_t* left, node_t* right);
node_t*
node_binop_subtraction_create(node_t* left, node_t* right);
node_t*
node_binop_multiplication_create(node_t* left, node_t* right);
node_t*
node_binop_division_create(node_t* left, node_t* right);

void
node_print(node_t* node);

int
node_eval(node_t* node);

void 
node_destroy(node_t* node);

// 

typedef struct intlit {
    int i;
} intlit_t;

intlit_t*
intlit_create(int i);

void
intlit_print(intlit_t* intlit);

int
intlit_eval(intlit_t* intlit);

void
intlit_destroy(intlit_t* intlit);

// 

typedef struct unop {
    char tag;
    // - unary minus

    node_t* node;
} unop_t;

unop_t*
unop_create(char tag, node_t* node);

void
unop_print(unop_t* unop);

int
unop_eval(unop_t* unop);

void
unop_destroy(unop_t* unop);

// 

typedef struct binop {
    char tag;
    // + addition
    // - subtraction
    // * multiplication
    // / division

    node_t* left;
    node_t* right;
} binop_t;

binop_t*
binop_create(char tag, node_t* left, node_t* right);

void
binop_print(binop_t* binop);

int
binop_eval(binop_t* binop);

void
binop_destroy(binop_t* binop);