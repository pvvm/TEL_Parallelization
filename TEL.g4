grammar TEL;

// Parser

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
