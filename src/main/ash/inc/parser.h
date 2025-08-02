#pragma once

#include <corelibs.h>
#include <ash.h>
#include <ashtypes.h>
#include <lexer.h>

typedef enum {
  AST_EXPRESSION,
  AST_STATEMENT,
  AST_IF,
  AST_WHILE,
  AST_ASSIGNMENT,
  AST_BLOCK,
  AST_LITERAL,
  AST_BINARY,
  AST_VARIABLE
} ASTNodeType;

typedef struct ASTNode {
  ASTNodeType type;

  union {
    struct { struct ASTNode* left; Token op; struct ASTNode* right; } binary;
    struct { Token variable; struct ASTNode* value; } assignment;
    struct { Token token; } literal;
    struct { Token name; } variable;
    struct { struct ASTNode** statements; size_t count; } block;
    struct { struct ASTNode* condition; struct ASTNode* thenBranch; struct ASTNode* elseBranch; } if_stmt;
  };

} ASTNode;

typedef struct {
  Token* tokens;
  size_t current;
  size_t count;
} Parser;

Token peek(Parser* parser);
Token advance(Parser* parser);
int match(Parser* parser, TokenType type);

ASTNode* parse_primary(Parser* parser);
ASTNode* parse_term(Parser* parser);
ASTNode* parse_expression(Parser* parser);
ASTNode* parse_assignment(Parser* parser);
ASTNode** parse(Parser* parser, size_t* outCount);
