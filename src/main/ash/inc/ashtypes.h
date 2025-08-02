#pragma once

typedef enum { TYPE_INT, TYPE_CHAR, TYPE_VAR, TYPE_BOOL, TYPE_STR, TYPE_VOID } DataType; // Data types
typedef enum { INIT, UNINIT } InitState; // Var state

typedef struct {
  char* name;
  DataType type;
  InitState state;
  void* value;
  int is_ptr;
} Variable;

typedef struct {
  char* name;
  Variable* parameters;
  char** body_lines;
  int param_count;
  DataType return_type;
} Function;
