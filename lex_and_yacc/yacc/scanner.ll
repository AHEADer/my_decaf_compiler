%{

//#include "utilities.h"
#include "scanner.h"

#include <string.h>
//#include <ctype.h>
#include <stdlib.h>

//YYSTYPE yylval;

typedef dcc::Parser::token token;
typedef dcc::Parser::token_type token_type;

#define yyterminate() return token::END
#define YY_NO_UNISTD_H
#define MaxIdentLen 31
#define TAB_SIZE 4

int linenum, colno;
%}

%option c++
%option prefix="dcc"
%option batch
%option debug
%option yywrap nounput 
%option stack
%{
#define YY_USER_ACTION  yylloc->columns(yyleng);
%}

            

ARITHMETIC              ([-+*/%])
DECIMAL                 ((\+|\-)?[0-9]+)
DIGIT                   ([0-9]+)
HEX                     ((\+|\-)?0[xX][0-9a-fA-F]+)
RELATIONAL_OPERATOR     ([=<>])
INTEGER                 ({DECIMAL}|{HEX})
FLOAT                   (({DECIMAL}?\.{DIGIT}?((E|e)(\+|\-)?{DIGIT})?)|({DECIMAL}(E|e)(\+|\-)?{DIGIT}))
IDEANTIFIER             ([_a-zA-Z][a-zA-Z0-9_]*)
STRING                  (\"[^\"\n]*\")
BOOLEAN                 (true|false)
OPERATOR                ({ARITHMETIC}|{RELATIONAL_OPERATOR})
PUNCTUATION             ([!,.[\]{}();])
%x COMMENT

%% /*** Regular Expressions Part ***/

 /* code to place at the beginning of yylex() */
%{
    // reset location
    yylloc->step();
%}

[\n]                    { colno = 1; linenum++;}
[\t]                    { colno += TAB_SIZE - colno % TAB_SIZE + 1;}
[ ]                     ;

void                    { return token::T_Void; }
int                     { return token::T_Int; }
double                  { return token::T_Double; }
bool                    { return token::T_Bool; }
string                  { return token::T_String; }
class                   { return token::T_Class; }
interface               { return token::T_Interface; }
null                    { return token::T_Null; }
this                    { return token::T_This; }
extends                 { return token::T_Extends; }
implements              { return token::T_Implements; }
for                     { return token::T_For; }
while                   { return token::T_While; }
if                      { return token::T_If; }
else                    { return token::T_Else; }
return                  { return token::T_Return; }
break                   { return token::T_Break; }
new                     { return token::T_New; }
NewArray                { return token::T_NewArray; }
Print                   { return token::T_Print; }
ReadInteger             { return token::T_ReadInteger; }
ReadLine                { return token::T_ReadLine; }

{PUNCTUATION} | 
{OPERATOR}              {return static_cast<token_type>(*yytext);}

\<=                     { return token::T_LessEqual; }
\>=                     { return token::T_GreaterEqual; }
==                      { return token::T_Equal; }
!=                      { return token::T_NotEqual; }
\[\]                    { return token::T_Dims; }
&&                      { return token::T_And; }
\|\|                    { return token::T_Or; } 

{STRING}                {
                            yylval->stringVal = new std::string(yytext, yyleng);
                            return token::T_StringConstant;
                        }

{BOOLEAN}               {
                            if (strcmp(yytext,"true")==0)
                                yylval->boolVal = true;
                            else
                                yylval->boolVal = false;
                            return token::T_BoolConstant;
                        }

{DECIMAL}               {
                            yylval->integerVal = strtol(yytext, NULL, 10);
                            return token::T_IntConstant;
                        } 

{HEX}                   {
                            yylval->integerVal = strtol(yytext, NULL, 16);
                            return token::T_IntConstant;
                        }

{FLOAT}                 {
                            yylval->doubleVal = atof(yytext);
                            return token::T_DoubleConstant;
                        }

{IDEANTIFIER}           {
                            if (strlen(yytext) > MaxIdentLen)
                                printf("errors");
                                //(&yylloc, yytext);
                            
                            strncpy(yylval->identifier, yytext, MaxIdentLen);
                            yylval->identifier[MaxIdentLen] = '\0';
                            
                            return token::T_Identifier;
                        }

.                       { return static_cast<token_type>(*yytext);}
%%                                                                    

/*** Additional Code ***/

namespace dcc {

Scanner::Scanner(std::istream* in,
         std::ostream* out)
    : dccFlexLexer(in, out)
{
}

Scanner::~Scanner()
{
}

void Scanner::set_debug(bool b)
{
    yy_flex_debug = b;
}

}

/* This implementation of dccFlexLexer::yylex() is required to fill the
 * vtable of the class dccFlexLexer. We define the scanner's main yylex
 * function via YY_DECL to reside in the Scanner class instead. */

#ifdef yylex
#undef yylex
#endif

int dccFlexLexer::yylex()
{
    std::cerr << "in dccFlexLexer::yylex() !" << std::endl;
    return 0;
}

/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */

int dccFlexLexer::yywrap()
{
    return 1;
}
