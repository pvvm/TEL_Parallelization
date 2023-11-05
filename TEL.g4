grammar TEL;

// Parser

/*prog:	expr EOF ;
expr:	expr ('*'|'/') expr
    |	expr ('+'|'-') expr
    |	INT
    |	'(' expr ')'
    ;
NEWLINE : [\r\n]+ -> skip;*/

math        : math ('*'|'/') math
            | math ('+'|'-') math
            | '(' unary ')'
            ;

unary       : '-' INT 
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

INT         : [0-9]+ ;
FLOAT       : [0-9]*'.'[0-9]+ ;

ID          : [a-zA-Z][_a-zA-Z0-9]* ;

