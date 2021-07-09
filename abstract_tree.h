#ifndef _ABSTRACT_SYNTAX_TREE_H
#define _ABSTRACT_SYNTAX_TREE_H 1

enum AST_NODES_TYPE{PROGRAM, FUNCTION, STATEMENTS, ARGUMENT_LIST, FUNCTION_CALL,
                    FUNCTION_CALL_ARGUMENT_NODE,   FUNCTION_DEFINITION_ARGUMENT_NODE,
                    IF_STATEMENT, ELSE_STATEMENT,  BOOLEAN_STATEMENT_NODE,
                    COMPARISON_NODE, LOGICAL_AND,  LOGICAL_OR,
                    LOGICAL_NOT, MUTABLE_VARIABLE_DEFINITION, IMMUTABLE_VARIABLE_DEFINITION,
                    INT_TYPE, STR_TYPE, BOOL_TYPE, VALUE, MUTABLE_ARRAY_DEFINITION,
                    IMMUTABLE_ARRAY_DEFINITION, ARRAY_LIST, MATH_EXPRESSION, OPERATION,
                    ADD, SUB, MUL, DIV, BITWISE_AND, BITWISE_OR};

typedef struct ASTnode_t{
 enum AST_NODES_TYPE type; // e.g., program, function, etc.
 intmax_t val;
 size_t function_symbol_table_index;
 size_t variable_symbol_table_index;
 size_t child_count;
 struct ASTnode_t **next; // Double pointer in case that there is more than 1 child
}ASTnode_t;


#endif
