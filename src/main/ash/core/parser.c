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
    node->type = AST_LITERAL_INT;
    node->literal.token = tok;
    return node;
  }
  if (tok.type == TOK_BOOLEAN) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_LITERAL_BOOL;
    node->literal.token = tok;
    return node;
  }
  if (tok.type == TOK_SQUOTE) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_LITERAL_CHAR;
    node->literal.token = advance(parser); // consume and get value as well
    return node;
  }
  if (tok.type == TOK_DQUOTE) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_LITERAL_STR;
    node->literal.token = advance(parser); // consume and get value as well
    return node;
  }
  if (tok.type == TOK_FLOATL) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_LITERAL_FLOAT;
    node->literal.token = tok;
    return node;
  }
  if (tok.type == TOK_DOUBLEL) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_LITERAL_DOUBLE;
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

ASTNode* parse_unary(Parser* parser) {
  TokenType type = peek(parser).type;

  if (type == TOK_ADD || type == TOK_SUB || type == TOK_NOT) {
    Token op = advance(parser); // consume and get
    ASTNode* right = parse_unary(parser);

    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_UNARY;
    node->unary->op = op;
    node->unary->right = right;
    return node;
  }
  return parse_primary(parser);
}

ASTNode* parse_binary(Parser* parser, int precedence) {
  ASTNode* left = parse_unary(parser);
  while (1) {
    int currPrec = get_precendence(current(parser).type);
    if (currPrec < precedence) break;

    Token op = advance(parser); // consume and get
    ASTNode* right = parseBinary(parser, currPrec + 1);
    ASTNode* lft = malloc(sizeof(ASTNode));
    lft->type = AST_BINARY;
    lft->binary->left = left;
    lft->binary->right = right;

    free(left);
    left = lft;
  }
  return left;
}
    
ASTNode* parse_expression(Parser* parser) {
  return parse_binary(parser, 0);
}

ASTNode* parse_assignment(Parser* parser) {
  if (peek(parser).type != TOK_IDENTIFIER) return NULL;
  Token name = advance(parser); // get name

  if (match(parser, TOK_ASSIGN) == 0) return NULL;

  ASTNode* value = parse_expression(parser);
  ASTNode* node = malloc(sizeof(ASTNode));
  node->type = AST_ASSIGNMENT;
  node->assignment.variable = name;
  node->assignment.value = value;
  return node;
}

ASTNode* parse_var_decl(Parser* parser) {
  TokenType peekType = peek(parser).type;

  if (peekType != TOK_INIT && peekType != TOK_UNINIT) return NULL;
  VarStates state = INIT;
  
  if (peekType == TOK_INIT) {
    state = INIT;
    advance(parser); // consume init
  
    TokenType dtype = advance(parser).type; // get datatype
    int ptr_count = 0; // ptr count (*, **, ***, **** ?)
  
    while (peek(parser).type == TOK_PTR) {
      ptr_count++;
      advance(parser); // consume
    }

    ASTNode* assignNode = parse_assignment(parser);
    ASTNode* node = malloc(sizeof(ASTNode));

    node->type = AST_VARIABLE_INIT;
    node->init_variable->dtype = dtype;
    node->init_variable->ptr_count = ptr_count;
    node->state = state;
    node->assignment_node = assignNode;

    return node;
  } else {
    state = UNINIT;
    advance(parser); // consume uninit
  
    TokenType dtype = advance(parser).type; // get datatype
    int ptr_count = 0; // ptr count (*, **, ***, **** ?)
  
    while (peek(parser).type == TOK_PTR) {
      ptr_count++;
      advance(parser); // consume
    }

    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_VARIABLE_UNINIT;
    node->uninit_variable->dtype = dtype;
    node->uninit_variable->ptr_count = ptr_count;
    node->uninit_variable->state = state;
    return node;
  }

  return NULL;
}

ASTNode* parse_return(Parser* parser) {
  if (peek(parser).type != TOK_RETURN) return NULL;
  advance(parser); // consume
  
  ASTNode* value = parse_expression(parser);
  ASTNode* node = malloc(sizeof(ASTNode));
  node->type = AST_RETURN;
  node->return_stmt->value = value;
  return node;
}

ASTNode* parse_block(Parser* parser) {
  ASTNode* node = malloc(sizeof(ASTNode));
  node->type = AST_BLOCK;
  return node;
}

ASTNode* parse_if(Parser* parser) {
  ASTNode* node = malloc(sizeof(ASTNode));
  node->type = AST_IF;

  node->if_stmt->condition = parse_expression(parser);
  node->if_stmt->thenBranch = parse_block(parser);
  node->if_stmt->elseBranch = parse_block(parser);
  return node;
}

ASTNode* parse_statement(Parser* parser) {
  if (match(parser, TOK_IF)) return parse_if(parser);
  if (match(parser, TOK_WHILE)) return parse_while(parser);
  if (match(parser, TOK_RETURN)) return parse_return(parser);
  if (isType(current(parser))) return parse_var_decl(parser);
  if (match(parser, TOK_LBRACKET)) return parse_block(parser);
  return parse_expression(parser);
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

    
