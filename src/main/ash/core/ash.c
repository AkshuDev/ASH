// AkshuDev

#include <ash.h>
#include <corelibs.h>
#include <ashtypes.h>
#include <lexer.h>

char* readfile(const char* path, size_t* out_size) {
  FILE* file = fopen(path, "rb");
  if (!file) { fprintf(stderr, "[ERROR] Cannot open file: [%s]\n", path); return NULL; }

  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  rewind(file);

  char* buffer = (char*)malloc(size + 1);
  if (!buffer) { fprintf(stderr, "[ERROR] Cannot allocate memory!\n"); fclose(file); return NULL; }

  fread(buffer, 1, size, file);
  buffer[size] = '\0';
  fclose(file);

  if (out_size) *out_size = size;
  return buffer;
}

int main(int argc, char** argv) {
  int debug = 0;

  if (argc < 2) { fprintf(stderr, HELP); return 1; }

  char* fIn = argv[1];
  
  for (int i = 2; i < argc; i++) {
    if (strcmp(argv[i], "-debug") == 0) { debug = 1; continue; }
  }

  // Start lexer
  int tokCount;

  size_t fileSize;
  char* code = readfile(fIn, &fileSize);
  if (!code) return 2;
  
  // Call lexer
  Token* tokens = lex(code, &tokCount);

  if (!tokens) {
    fprintf(stderr, "[ERROR] Lexing Failed!\n");
    free(code);
    return 2;
  }

  if (debug) {
    printf("=== TOKENS (Count = %d) ===\n", tokCount);
    for (int i = 0; i < tokCount; i++){
      printf("[%d]\n\tType: %s\n\tValue: [%s]\n", i, token_type_to_str(tokens[i].type), tokens[i].lexeme);
    }
  }

  // Free
  free(tokens);
  free(code);

  return 0;
}
