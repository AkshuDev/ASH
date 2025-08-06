#pragma once

#include "corelibs.h"
#include "ashtypes.h"

#define LEX_MAXTOKS 128

typedef enum {
  TOK_NUMBER = 0,
  TOK_FLOATL,
  TOK_DOUBLEL,
  TOK_SQUOTE,
  TOK_DQUOTE,
  TOK_BOOLEAN,
  TOK_FLOAT,
  TOK_DOUBLE,
  TOK_INVALID,
  TOK_INIT,
  TOK_UNINIT,
  TOK_VAR,
  TOK_INT,
  TOK_INT64,
  TOK_INT32,
  TOK_INT16,
  TOK_INT8,
  TOK_INT1,
  TOK_UINT,
  TOK_UINT64,
  TOK_UINT32,
  TOK_UINT16,
  TOK_UINT8,
  TOK_UINT1,
  TOK_VOID,
  TOK_CHAR,
  TOK_STR,
  TOK_BOOL,
  TOK_IDENTIFIER,
  TOK_ASSIGN,
  TOK_COMMENT,
  TOK_SPECIAL,
  TOK_MACRO,
  TOK_INCLUDE,
  TOK_ENDL,
  TOK_LPAR,
  TOK_RPAR,
  TOK_LBRACKET,
  TOK_RBRACKET,
  TOK_LCURLY,
  TOK_RCURLY,
  TOK_GT,
  TOK_LT,
  TOK_GTE,
  TOK_LTE,
  TOK_EQUALS,
  TOK_FUNC,
  TOK_RUN,
  TOK_EXEC,
  TOK_VMEM,
  TOK_STACK,
  TOK_HEAP,
  TOK_ALLOCATE,
  TOK_FREE,
  TOK_OUT,
  TOK_STDOUT,
  TOK_ERROUT,
  TOK_STDERR,
  TOK_FAIL,
  TOK_EXIT,
  TOK_ADD,
  TOK_SUB,
  TOK_MUL,
  TOK_DIV,
  TOK_FDIV,
  TOK_XOR,
  TOK_EXPO,
  TOK_PTR,
  TOK_DREF,
  TOK_PERCENT,
  TOK_FORWARD,
  TOK_BOOT,
  TOK_IGNITE,
  TOK_OUTSTACK,
  TOK_EOF,
  TOK_IF,
  TOK_ELSE,
  TOK_FOR,
  TOK_WHILE,
  TOK_BREAK,
  TOK_CONTINUE,
  TOK_RETURN,
  TOK_NOT,
  TOK_AND,
  TOK_NOR,
  TOK_XNOR,
  TOK_OR,
  TOK_NAND,
  TOK_IN,
} TokenType;

extern char* TokenTypeNames[];

typedef struct {
  TokenType type;
  char* lexeme;
  int line;
  int col;
} Token;

char* token_type_to_str(TokenType type);
TokenType getType(const char* wrd);
TokenType getTypeChar(const char c);
Token* lex(const char* src, int* tok_count);
