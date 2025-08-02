#include <parser.h>

Token peek(Parser* parser) {
  if (parser->current >= parser->count) return (Token){TOKEN_EOF, "EOF", 0, 0};
  return parser->tokens[parser->current];
}

Token advance(Parser* parser) {
  if (parser->current < parser->count) return parser->tokens[parser->current++];
  return (Token){TOKEN_EOF, "EOF", 0, 0};
}

int match(Parser* parser, TokenType type){
  if (peek(parser).type == type) {
    advance(parser);
    return 1;
  }
  return 0;
}

ASTNode* parse_primary(Parser* parser) {
  Token tok = advance(parser);

  if (tok.type == TOK_NUMBER) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_LITERAL;
    node->literal.token = tok;
    return node;
  }
  if (tok.type == TOK_IDENTIFIER) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_VARIABLE;
    node->variable.name = tok;
    return node;
  }
  if (tok.type == TOK_LPAREN) {
    ASTNode* expr = parse_expression(parser);
    match(parser, TOK_RPAREN);
    return expr;
  }
  return NULL; // Error case
}

ASTNode* parse_term(Parser* parser) {
  ASTNode* left = parse_primary(parser);
  while (peek(parser).type == TOK_MUL || peek(parser).type == TOK_DIV) {
    Token op = advance(parser);
    ASTNode* right = parse_primary(parser);
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_BINARY;
    node->binary.left = left;
    node->binary.op = op;
    node->binary.right = right;
    left = node;
  }
  return left;
}

ASTNode* parse_expression(Parser* parser) {
  ASTNode* left = parse_term(parser);
  while (peek(parser).type == TOK_ADD || peek(parser).type == TOK_SUB) {
    Token op = advance(parser);
    ASTNode* right = parse_term(parser);
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_BINARY;
    node->binary.left = left;
    node->binary.right = right;
    node->binary.op = op;
    left = node;
  }
  return left;
}

ASTNode* parse_assignment(Parser* parser) {
  if (peek(parser).type != TOK_IDENTIFIER) return NULL;

  Token name = advance(parser);

  if (match(parser, TOK_ASSIGN) == 0) return NULL;

  ASTNode* value = parse_expression(parser);
  ASTNode* node = malloc(sizeof(ASTNode));
  node->type = AST_ASSIGNMENT;
  node->assignment.variable = name;
  node->assignment.value = value;
  return node;
}

ASTNode** parse(Parser* parser, size_t* outCount) {
  size_t capacity = 16;
  size_t count = 0;
  ASTNode** statements = malloc(sizeof(ASTNode*) * capacity);

  while (peek(parser).type != TOKEN_EOF) {
    ASTNode* stmt = parse_assignment(parser);

    if (!stmt) break;
    if (count >= capacity) {
      capacity *= 2;
      statements = realloc(statements, sizeof(ASTNode*) * capacity);
    }
    statements[count++] = stmt;
  }

  *outCount = count;
  return statements;
}

    
