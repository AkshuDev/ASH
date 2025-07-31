" Clear existing syntax
syntax clear

" Special Instructions start with #!
syntax match ashSpecialInstruction "^#!.*$"

" Comments start with #
syntax match ashComment "#.*$"

" Keywords (commands, control flow)
syntax keyword ashKeyword run set out log warn fail if else for stdout errout exit logout exec try catch include boot ignite parse ret fnc ptr void var forward uninit init break outstack stack heap vmem allocate setup

" Contants
syntax keyword ashConstant true false null

" Built-in types
syntax keyword ashtypes boolean path char str int uint int64 int32 int16 int8 int1 uint64 uint32 uint16 uint8 uint1 

" Built-in funcs
syntax keyword ashFunctions openf closef readf writef clocf sizef allocmem freemem 

" User-Defined funcs
syntax match ashUsrFunc /\<[a-zA-Z_][a-zA-Z0-9_]*\>\s*(.*)/

" Strings
syntax region ashString start=+"+ skip=+\\\\\|\\"+ end=+"+
syntax match ashChar "'\\.'"
syntax match ashChar "'[^\\]'"

" Variables
syntax match ashVariable "\$[a-zA-Z_][a-zA-Z0-9_]*"
syntax match ashSpecialVariable "@[a-zA-Z_][a-zA-Z0-9_]*"

" Brackets and blocks
syntax match ashBlock "[{}()\[\]]"

" Numbers
syntax match ashNumber "\<[0-9]\+\>"

" Operators and Access
syntax match ashDotAccess "\<a-zA-Z_][a-zA-Z0-9_]*\>\.\<[a-zA-Z_][a-zA-Z0-9_]*\>"
syntax match ashOperators "[+\-*/%=!<>&|^]"

" Highlight groups

highlight link ashComment Comment
highlight link ashSpecialInstruction PreProc
highlight link ashKeyword Keyword
highlight link ashConstant Constant
highlight link ashFunctions Function
highlight link ashUsrFunc Function
highlight link ashTypes Type
highlight link ashString String
highlight link ashChar Character
highlight link ashVariable Identifier
highlight link ashSpecialVariable Identifier
highlight link ashBlock Structure
highlight link ashNumber Number
highlight link ashOperator Operator
highlight link ashDotaccess Identifier
