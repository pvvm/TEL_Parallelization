grammar TEL;

// Parser

initial     : (structLike|eventProc|dispatcher)*
            ;

dispatcher  : 'dispatch' ID '{' dispEPs '}'
            ;

dispEPs     : ((ID|(ID '::' ID)) '->' '{' ID (',' ID)* '}' ';')*
            ;

structLike : ('context'|'struct'|'interm_output'|'event'|'header') ID '{' onlyVarDecl '}'
            | 'event' ID ':' ID '{' onlyVarDecl '}'
            ;

onlyVarDecl : (type ID ';'|type ID '=' (INT|FLOAT) ';')*
            ;

eventProc   : 'void' ID '(' (type ID (',' type ID)*)? ')' '{' statement* '}'
            ;

statement   : (condition|for|foreach|assign ';'|return ';'|varDecl ';'| 'break'  ';')
            ;

condition   : 'if' '(' assign ')' curlyBrack
            | 'if' '(' assign ')' curlyBrack 'else' curlyBrack
            ;

for         : 'for' '(' forArg ')' curlyBrack
            ;

forArg      : varDecl ';' or ';' assign
            | assign ';' or ';' assign
            ;

foreach     : 'foreach' '(' ID 'in' ID ')' curlyBrack
            ;

curlyBrack  : '{' statement* '}'
            | statement
            ;

return      : 'return' assign
            ;

listDecl    : LIST_T '<' type '>' ID
            ;

varDecl     : type ID ('=' or)*
            ;

type        : (INT_T|FLOAT_T|BOOL_T|STREAM_T|EVENT_T|PACKET_T|QUEUE_T|ID)
            ;

assign      : ID ('=' or)*
            | or
            ;

or          : and ('||' and)*
            ;

and         : comparison ('&&' comparison)*
            ;

comparison  : relational (('=='|'!=') relational)*
            ;

relational  : mathLow (('>'|'<'|'<='|'>=') mathLow)*
            ;

mathLow     : mathHigh (('+'|'-') mathHigh)*
            ;

mathHigh    : unary (('*'|'/') unary)*
            ;

unary       : ('-'|'!')? symbol
            | '(' assign ')'
            ;

symbol      : ID
            | INT
            | FLOAT
            ;

// Lexer
INT_T       : 'int' ;
FLOAT_T     : 'float' ;
BOOL_T      : 'bool' ;
STREAM_T    : 'stream' ;
EVENT       : 'event' ;
EVENT_T     : 'event_t' ;
QUEUE_T     : 'queue_t' ;
DISPATCH    : 'dispatch' ;
CONTEXT_T   : 'context' ;
PACKET_T    : 'pkt_t' ;
LIST_T      : 'list' ;

INT         : [0-9]+ ;
FLOAT       : [0-9]*'.'[0-9]+ ;

ID          : [a-zA-Z][_a-zA-Z0-9]* ;

NEWLINE     : [ \r\n]+ -> skip;
