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

statement   : (condition|forCommon|forEach|assign ';'|returnTEL ';'|varDecl ';'| 'break'  ';')
            ;

condition   : 'if' '(' assign ')' curlyBrack
            | 'if' '(' assign ')' curlyBrack 'else' curlyBrack
            ;

forCommon   : 'for' '(' forArg ')' curlyBrack
            ;

forArg      : varDecl ';' orTEL ';' assign
            | assign ';' orTEL ';' assign
            ;

forEach     : 'foreach' '(' ID 'in' ID ')' curlyBrack
            ;

curlyBrack  : '{' statement* '}'
            | statement
            ;

returnTEL   : 'return' assign
            ;

listDecl    : LIST_T '<' type '>' ID
            ;

varDecl     : type ID ('=' orTEL)*
            ;

type        : (INT_T|FLOAT_T|BOOL_T|STREAM_T|EVENT_T|PACKET_T|QUEUE_T|ID)
            ;

assign      : ID ('=' orTEL)*
            | orTEL
            ;

orTEL       : andTEL ('||' andTEL)*
            ;

andTEL         : comparison ('&&' comparison)*
            ;

comparison  : relational (('=='|'!=') relational)*
            ;

relational  : mathLow (('>'|'<'|'<='|'>=') mathLow)*
            ;

mathLow     : mathHigh (('+'|'-') mathHigh)*
            ;

mathHigh    : unary (('*'|'/') unary)*
            ;

unary       : (('-'|'!')? symbol| ('type'|'bytes')? '(' assign ')')
            ;

symbol      : (identifier|INT|FLOAT|FALSE|TRUE|'new_pkt' '(' ')')
            ;

identifier  : ID ('.' ID|'.' builtFunc '(' (assign)? ')'|'[' orTEL (':' orTEL)* ']')*
            ;

builtFunc   : ('add'|'remove'|'add_hdr'|'get_hdr' '<' ID '>'|'add_data'|'get_data'|'push'|'pop'|'len')
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
FALSE       : 'false' ;
TRUE        : 'true' ;

ID          : [a-zA-Z][_a-zA-Z0-9]* ;

NEWLINE     : [ \r\n\t]+ -> skip;
