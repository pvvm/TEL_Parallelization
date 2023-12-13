grammar TEL;

// Parser

initial     : (structLike|eventProc|dispatcher)*
            ;

dispatcher  : 'dispatch' ID '{' dispEPs '}'
            ;

dispEPs     : ((ID|(ID '::' ID)) '->' '{' ID (',' ID)* '}' ';')*
            |
            ;

structLike : ('context'|'struct'|'interm_output'|'event'|'header') ID '{' onlyVarDecl '}'
            | 'event' ID ':' ID '{' onlyVarDecl '}'
            ;

onlyVarDecl : (type ID ';'|type ID '=' ('-')? (INT|FLOAT|TRUE|FALSE) ';'|LIST_T '<' type '>' ID ';')*
            ;

eventProc   : 'void' ID ('<' 'T' '>')? '(' ((type|'T') ID (',' ((type ID) | (('list' '<' type '>' ID))))*)? ')' '{' statement* '}'
            ;

statement   : (condition|forCommon|forEach|assign ';'|returnTEL ';'|varDecl ';'| 'break'  ';')
            ;

condition   : 'if' '(' assign ')' curlyBrack
            | 'if' '(' assign ')' curlyBrack 'else' curlyBrack
            ;

forCommon   : ('for' '(' forArg ')' curlyBrack
            | 'while' '(' orTEL ')' curlyBrack)
            ;

forArg      : (varDecl|assign)? ';' orTEL ';' assign
            ;

forEach     : 'foreach' '(' identifier 'in' identifier ')' curlyBrack
            ;

curlyBrack  : '{' statement* '}'
            | statement
            ;

returnTEL   : 'return' (assign)?
            ;

varDecl     : type ID ('=' orTEL)*
            | LIST_T '<' type '>' ID
            ;

type        : (INT_T|FLOAT_T|BOOL_T|STREAM_T|EVENT_T|PACKET_T|QUEUE_T|ID)
            ;

assign      : identifier '=' orTEL
            | orTEL
            ;

orTEL       : andTEL ('||' andTEL)*
            ;

andTEL      : comparison ('&&' comparison)*
            ;

comparison  : relational (('=='|'!=') relational)*
            ;

relational  : mathLow (('>'|'<'|'<='|'>=') mathLow)*
            ;

mathLow     : mathHigh (('+'|'-') mathHigh)*
            ;

mathHigh    : unary (('*'|'/') unary)*
            ;

unary       : (('-'|'!')? symbol | ('-'|'!')? '(' orTEL ')'
                | ('type'|'byte'|'ceil'|'min'|'max'|'abs')? '(' assign (',' assign)* ')'
                | 'now' '(' ')'
                | ('mem_write' '(' orTEL (',' orTEL)* ')'))
            ;

symbol      : (identifier|INT|FLOAT|FALSE|TRUE|'new_pkt' '(' ')')
            ;

identifier  : ID ('.' ID|'.' builtFunc '(' (assign (',' assign)*)? ')'|'[' orTEL (':' orTEL)* ']')*
            ;

builtFunc   : ('add'|'remove'|'add_hdr'|'extract_hdr'|'add_data'|'get_data'|'push'|'pop'|'len'|'mem_append'|'rate')
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
COMMENT     : '//' ~[\r\n]* -> skip;   
