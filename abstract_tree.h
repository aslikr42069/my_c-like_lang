#ifndef _ABSTRACT_SYNTAX_TREE_H
#define _ABSTRACT_SYNTAX_TREE_H 1
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

enum AST_NODES_TYPE{PROGRAM, BODY, FUNCTION, STATEMENTS, ARGUMENT_LIST, FUNCTION_CALL,
                    FUNCTION_CALL_ARGUMENT_NODE,   FUNCTION_DEFINITION_ARGUMENT_NODE,
                    IF_STATEMENT, ELSE_STATEMENT,  BOOLEAN_STATEMENT_NODE,
                    COMPARISON_NODE, LOGICAL_AND,  LOGICAL_OR,
                    LOGICAL_NOT, MUTABLE_VARIABLE_DEFINITION, IMMUTABLE_VARIABLE_DEFINITION,
                    INT_TYPE, STR_TYPE, BOOL_TYPE, VALUE, MUTABLE_ARRAY_DEFINITION,
                    IMMUTABLE_ARRAY_DEFINITION, ARRAY_LIST, MATH_EXPRESSION, OPERATION,
                    ADD, SUB, MUL, DIV, BITWISE_AND, BITWISE_OR};

typedef struct ASTnode_t{
 enum AST_NODES_TYPE type; // e.g., program, function, etc.
 union {
  intmax_t val;
  size_t function_symbol_table_index;
  size_t variable_symbol_table_index;
 };
 size_t child_count;
 struct ASTnode_t **next; // Double pointer in case that there is more than 1 child
}ASTnode_t;

 ASTnode_t *makeProgramNode(ASTnode_t *body);
 ASTnode_t *makeFunctionNode(char *name, ASTnode_t* parameters, enum AST_NODES_TYPE return_type, ASTnode_t* statements);
 ASTnode_t *makeStructNode(char *name, ASTnode_t* structure_body);
 ASTnode_t *makeBodyNode(char *name, ASTnode_t* body, ASTnode_t* function, ASTnode_t* structure_node);
 ASTnode_t *makeImmutableVarNode(size_t var_type, ASTnode_t* var_assignment, ASTnode_t* standalone_var_def);
 ASTnode_t *makeMutableVarNode(size_t var_type, ASTnode_t* var_assignment, ASTnode_t* standalone_var_def);
 ASTnode_t *makeVarAssignmentNode(char *name, size_t type, ASTnode_t* function_call, ASTnode_t* expression);
 ASTnode_t *makeFunctionCallNode(char *name, ASTnode_t* parameters);
 ASTnode_t *makeFunctionDefParametersNode(size_t type, char *name, ASTnode_t* parameters, size_t isEmpty);
 ASTnode_t *makeFunctionCallParametersNode(size_t type, char *name, size_t isVar);
 ASTnode_t *makeStructBodyNode(ASTnode_t* struct_body, ASTnode_t* var_defs);
 ASTnode_t *makeStatementNode(size_t type, ASTnode_t* first_node, ASTnode_t* second_node, intmax_t int_literal, char *str, size_t bool_literal);
 ASTnode_t *makeStatementsNode(size_t isEmpty, ASTnode_t statements);
 ASTnode_t *makeBooleanStatementNode(size_t logical_operator, ASTnode_t *BOOL1, ASTnode_t *BOOL2, ASTnode_t* indexing_expression, ASTnode_t function_call, char* identifier1, char* identifier2);
 ASTnode_t *makeMathExpressionNode(char binary_operator, size_t opt_case, intmax_t int_literal1, intmax_t int_literal2, char* identifier1, char* identifier2, ASTnode_t* function_call1, ASTnode_t* function_call2, ASTnode_t* math_expression1, ASTnode_t* math_expression2);
 ASTnode_t *makeWhileLoopNode(ASTnode_t *boolean_statement, ASTnode_t* statements);
 ASTnode_t *makeIndexingExpressionNode(size_t the_case, char* identifier1, intmax_t int_literal, char* identifier2);
 ASTnode_t *makeStandaloneVarDefNode(size_t type, char *identifier, ASTnode_t* indexing_expression);
 ASTnode_t *makeArrayListNode(size_t standalone, ASTnode_t* Array_List, intmax_t int_or_bool_literal, char* identifier_or_str, ASTnode_t* func, ASTnode_t* indexing_expr, ASTnode_t* array_list);


#endif
