#pragma once

#include <corelibs.h>
#include <ash.h>
#include <ashtypes.h>
#include <lexer.h>
#include <stdbool.h>

typedef enum {
  AST_EXPRESSION,
  AST_STATEMENT,
  AST_IF,
  AST_WHILE,
  AST_ASSIGNMENT,
  AST_BLOCK,
  AST_LITERAL_INT,
  AST_LITERAL_UINT,
  AST_LITERAL_FLOAT,
  AST_LITERAL_DOUBLE,
  AST_LITERAL_CHAR,
  AST_LITERAL_STR,
  AST_LITERAL_BOOL,
  AST_BINARY,
  AST_VARIABLE,
  AST_VARIABLE_INIT,
  AST_VARIABLE_UNINIT,
  AST_RETURN,
  AST_PACKAGE,
  AST_IMPORT,
  AST_FUNCCALL,
  AST_FUNCDECL,
  AST_NOOP,
  AST_UNKNOWN,
} ASTNodeType;

typedef struct ASTNode {
  ASTNodeType type;

  union {
    int int_val;
    float float_val;
    char* string_val;
    char* identifier;
    
    struct {
      ASTNode* left;
      Token op;
      ASTNode* right;
    } binary;

    struct {
      Token op;
      ASTNode* operand;
    } unary;
    
    struct {
      Token variable;
      ASTNode* value;
    } assignment;

    struct {
      Token name;
    } variable;
    
    struct {
      TokenType dtype;
      int ptr_count;
      VarStates state;
      ASTNode* assignment_node;
    } init_variable;
      
    struct {
      Token token;
    } literal;
    
    struct {
      TokenType dtype;
      int ptr_count;
      VarStates state;
    } uninit_variable;
    
    struct {
      ASTNode* value;
    } return_stmt;
    
    struct {
      ASTNode** statements;
      size_t count;
    } block;
    
    struct {
      ASTNode* condition;
      ASTNode* thenBranch;
      ASTNode* elseBranch;
    } if_stmt;

    struct {
      ASTNode* condition;
      ASTNode* loopBranch;
    } while_stmt;

    struct {
      ASTNode* newVars;
      ASTNode* condition;
      ASTNode* loopOperation;
      ASTNode* loopBranch;
      ASTNode* failBranch;
      int count;
    } for_stmt;
    
    struct {
      char* name;
      ASTNode** args;
      int arg_count;
    } func_call;
    
    struct {
      char* name;
      ASTNode** params;
      ASTNode* body;
    } func_decl;
  };

} ASTNode;

typedef struct {
  Token* tokens;
  size_t current;
  size_t count;
} Parser;

Token peek(Parser* parser);
Token advance(Parser* parser);
bool match(Parser* parser, TokenType type);


ASTNode* parse_primary(Parser* parser);
ASTNode* parse_unary(Parser* parser);
ASTNode* parse_binary(Parser* parser, int precedence);
ASTNode* parse_expression(Parser* parser);
ASTNode* parse_assignment(Parser* parser);
ASTNode* parse_var_decl(Parser* parser);
ASTNode* parse_return(Parser* parser);
ASTNode** parse(Parser* parser, size_t* outCount);
