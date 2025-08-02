#include "corelibs.h"
#include "ashtypes.h"
#include "lexer.h"

char* TokenTypeNames[] = {
  "TOK_NUMBER",
  "TOK_FLOATL",
  "TOK_DOUBLEL",
  "TOK_SQUOTE",
  "TOK_DQUOTE",
  "TOK_BOOLEAN",
  "TOK_FLOAT",
  "TOK_DOUBLE",
  "TOK_INVALID",
  "TOK_INIT",
  "TOK_UNINIT",
  "TOK_VAR",
  "TOK_INT",
  "TOK_INT64",
  "TOK_INT32",
  "TOK_INT16",
  "TOK_INT8",
  "TOK_INT1",
  "TOK_UINT",
  "TOK_UINT64",
  "TOK_UINT32",
  "TOK_UINT16",
  "TOK_UINT8",
  "TOK_UINT1",
  "TOK_VOID",
  "TOK_CHAR",
  "TOK_STR",
  "TOK_BOOL",
  "TOK_IDENTIFIER",
  "TOK_ASSIGN",
  "TOK_COMMENT",
  "TOK_SPECIAL",
  "TOK_MACRO",
  "TOK_INCLUDE",
  "TOK_ENDL",
  "TOK_LPAR",
  "TOK_RPAR",
  "TOK_LBRACKET",
  "TOK_RBRACKET",
  "TOK_LCURLY",
  "TOK_RCURLY",
  "TOK_GT",
  "TOK_LT",
  "TOK_GTE",
  "TOK_LTE",
  "TOK_EQUALS",
  "TOK_FUNC",
  "TOK_RUN",
  "TOK_EXEC",
  "TOK_VMEM",
  "TOK_STACK",
  "TOK_HEAP",
  "TOK_ALLOCATE",
  "TOK_FREE",
  "TOK_OUT",
  "TOK_STDOUT",
  "TOK_ERROUT",
  "TOK_STDERR",
  "TOK_FAIL",
  "TOK_EXIT",
  "TOK_ADD",
  "TOK_SUB",
  "TOK_MUL",
  "TOK_DIV",
  "TOK_FDIV",
  "TOK_XOR",
  "TOK_EXPO",
  "TOK_PTR",
  "TOK_DREF",
  "TOK_PERCENT",
  "TOK_FORWARD",
  "TOK_BOOT",
  "TOK_IGNITE",
  "TOK_OUTSTACK",
  "TOK_EOF",
  "TOK_IF",
  "TOK_ELSE",
  "TOK_FOR",
  "TOK_WHILE",
  "TOK_BREAK",
  "TOK_CONTINUE",
  "TOK_RETURN"
};

char* token_type_to_str(TokenType type) {
  if (type < 0 || type < TOK_NUMBER) {
    return "INVALID_TOKEN_TYPE";
  }

  return TokenTypeNames[type];
}

TokenType getType(const char* wrd) {
  if (strcmp(wrd, "init") == 0) return TOK_INIT;
  if (strcmp(wrd, "uninit") == 0) return TOK_UNINIT;
  if (strcmp(wrd, "var") == 0) return TOK_VAR;
  if (strcmp(wrd, "int") == 0) return TOK_INT;
  if (strcmp(wrd, "uint") == 0) return TOK_UINT;
  if (strcmp(wrd, "boolean") == 0) return TOK_BOOL;
  if (strcmp(wrd, "str") == 0) return TOK_STR;
  if (strcmp(wrd, "char") == 0) return TOK_CHAR;
  if (strcmp(wrd, "void") == 0) return TOK_VOID;
  if (strcmp(wrd, "out") == 0) return TOK_OUT;
  if (strcmp(wrd, "stdout") == 0) return TOK_STDOUT;
  if (strcmp(wrd, "errout") == 0) return TOK_ERROUT;
  if (strcmp(wrd, "stderr") == 0) return TOK_STDERR;
  if (strcmp(wrd, "outstack") == 0) return TOK_OUTSTACK;
  if (strcmp(wrd, "include") == 0) return TOK_INCLUDE;
  if (strcmp(wrd, "vmem") == 0) return TOK_VMEM;
  if (strcmp(wrd, "stack") == 0) return TOK_STACK;
  if (strcmp(wrd, "heap") == 0) return TOK_HEAP;
  if (strcmp(wrd, "allocate") == 0) return TOK_ALLOCATE;
  if (strcmp(wrd, "free") == 0) return TOK_FREE;
  if (strcmp(wrd, "outstack") == 0) return TOK_OUTSTACK;
  if (strcmp(wrd, "run") == 0) return TOK_RUN;
  if (strcmp(wrd, "exec") == 0) return TOK_EXEC;
  if (strcmp(wrd, "forward") == 0) return TOK_FORWARD;
  if (strcmp(wrd, "boot") == 0) return TOK_BOOT;
  if (strcmp(wrd, "ignite") == 0) return TOK_IGNITE;
  if (strcmp(wrd, "fail") == 0) return TOK_FAIL;
  if (strcmp(wrd, "exit") == 0) return TOK_EXIT;
  if (strcmp(wrd, "fnc") == 0) return TOK_FUNC;
  if (strcmp(wrd, "ret") == 0) return TOK_RETURN;
  if (strcmp(wrd, "break") == 0) return TOK_BREAK;
  if (strcmp(wrd, "continue") == 0) return TOK_CONTINUE;
  if (strcmp(wrd, "if") == 0) return TOK_IF;
  if (strcmp(wrd, "else") == 0) return TOK_ELSE;
  if (strcmp(wrd, "for") == 0) return TOK_FOR;
  if (strcmp(wrd, "while") == 0) return TOK_WHILE;

  if (strcmp(wrd, "true") == 0 || strcmp(wrd, "false") == 0) return TOK_BOOLEAN;
  
  if (strcmp(wrd, "==") == 0) return TOK_EQUALS;
  if (strcmp(wrd, ">=") == 0) return TOK_GTE;
  if (strcmp(wrd, "<=") == 0) return TOK_LTE;
  if (strcmp(wrd, "#!") == 0) return TOK_MACRO;
  if (strcmp(wrd, "ptr") == 0) return TOK_PTR;
  if (strcmp(wrd, "dref") == 0) return TOK_DREF;
  if (strcmp(wrd, "//") == 0) return TOK_FDIV;
  
  return TOK_IDENTIFIER;
}

TokenType getTypeChar(const char c) {
  if (c == '=') return TOK_ASSIGN;
  if (c == '#') return TOK_COMMENT;
  if (c == '@') return TOK_SPECIAL;
  if (c == '(') return TOK_LPAR;
  if (c == ')') return TOK_RPAR;
  if (c == '[') return TOK_LBRACKET;
  if (c == ']') return TOK_RBRACKET;
  if (c == '{') return TOK_LCURLY;
  if (c == '}') return TOK_RCURLY;
  if (c == ';') return TOK_ENDL;
  if (c == '-') return TOK_SUB;
  if (c == '+') return TOK_ADD;
  if (c == '*') return TOK_MUL;
  if (c == '/') return TOK_DIV;
  if (c == '=') return TOK_ASSIGN;
  if (c == '%') return TOK_PERCENT;
  if (c == '<') return TOK_LT;
  if (c == '>') return TOK_GT;
  if (c == '^') return TOK_XOR;
  if (c == '!') return TOK_EXPO;
  if (c == '\'') return TOK_SQUOTE;
  if (c == '"') return TOK_DQUOTE;
  
  return TOK_INVALID;
}

Token* lex(const char* src, int* tok_count) {
  *tok_count = 0;
  int cap = LEX_MAXTOKS;
  int i = 0; int line = 1; int col = 1;
  int realloc_amt = 0;
  
  Token* toks = malloc(sizeof(Token) * cap);

  while (src[i] != '\0') {
    if (*tok_count >= cap ) {
      realloc_amt++;
      cap *= 2;
      
      Token* ntoks = realloc(toks, sizeof(Token) * cap);
      if (!ntoks) { fprintf(stderr, "[ERROR] Realloc failed at token %d count!\n", *tok_count); free(toks), exit(1); }

      toks = ntoks;
    }
    
    if (isspace(src[i])) {
      if (src[i] == '\n') { line++; col = 1; }
      i++;
      continue;
    }

    if (isalpha(src[i])) {
      int start = i;
      while (isalnum(src[i])) i++;

      int len = i - start;
      char* word = strndup(src + start, len);

      TokenType type = getType(word);

      toks[*tok_count] = (Token){type, word, line, col};
      (*tok_count)++;
      col += len;

      continue;
    }

    if (isdigit(src[i])) {
      int start = i;

      while(isdigit(src[i])) i++;
      char* num = strndup(src + start, i - start);
      toks[*tok_count] = (Token){TOK_NUMBER, num, line, col};
      (*tok_count)++;
      col += (i - start);
      continue;
    }

    if (src[i + 1] != '\0') {
      char* wrd = strndup(src + i, 2);
      TokenType type = getType(wrd);

      if (type != TOK_INVALID && type != TOK_IDENTIFIER) {
	toks[*tok_count] = (Token){type, wrd, line, col};
	(*tok_count)++;
	col++;
	i++;
	continue;
      }
    }

    char* c = strndup(src + i, 1);
    TokenType type = getTypeChar(src[i]);

    toks[*tok_count] = (Token){type, c, line, col};
    (*tok_count)++;
    i++;
    col++;
  }

  toks[*tok_count] = (Token){TOK_EOF, strdup("EOF"), line, col};
  (*tok_count)++;
  return toks;
}
