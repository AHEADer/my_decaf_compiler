
%{

#include "utilities.h"
#include "scanner.h"
#include "errors.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

YYSTYPE yylval;
struct yyltype yylloc;
static void DoBeforeEachAction();

#define YY_USER_ACTION DoBeforeEachAction();
#define TAB_SIZE 4

int linenum, colno;
%}

%x COMMENT              

ARITHMETIC              ([-+*/%])
DECIMAL                 (-?[0-9]+)
HEX                     (-?0[xX][0-9a-fA-F]+)
RELATIONAL_OPERATOR     ([=<>])
INTEGER                 ({DECIMAL}|{HEX})
FLOAT                   (-?{DECIMAL}\.{DECIMAL}?((E|e)(\+|\-)?{DECIMAL})?)
IDEANTIFIER             ([_a-zA-Z][a-zA-Z0-9_]*)
STRING                  (\"[^\"\n]*\")
BOOLEAN                 (true|false)
OPERATOR                ({ARITHMETIC}|RELATIONAL_OPERATOR)
PUNCTUATION             ([!,.[\]{}();])

%%

[\n]                    { colno = 1; linenum++;}
[\t]                    { colno += TAB_SIZE - colno % TAB_SIZE + 1;}
[ ]                     ;

void                    { return T_Void; }
int                     { return T_Int; }
double                  { return T_Double; }
bool                    { return T_Bool; }
string                  { return T_String; }
class                   { return T_Class; }
interface               { return T_Interface; }
null                    { return T_Null; }
this                    { return T_This; }
extends                 { return T_Extends; }
implements              { return T_Implements; }
for                     { return T_For; }
while                   { return T_While; }
if                      { return T_If; }
else                    { return T_Else; }
return                  { return T_Return; }
break                   { return T_Break; }
new                     { return T_New; }
NewArray                { return T_NewArray; }
Print                   { return T_Print; }
ReadInteger             { return T_ReadInteger; }
ReadLine                { return T_ReadLine; }

{PUNCTUATION} | 
{OPERATOR}              {return yytext[0];}

\<=                     { return T_LessEqual; }
\>=                     { return T_GreaterEqual; }
==                      { return T_Equal; }
!=                      { return T_NotEqual; }
\[\]                    { return T_Dims; }
&&                      { return T_And; }
\|\|                    { return T_Or; } 

{STRING}                {
                            yylval.stringConstant = strdup(yytext);
                            return T_StringConstant;
                        }

{BOOLEAN}               {
                            if (strcmp(yytext,"true")==0)
                                yylval.boolConstant = true;
                            else
                                yylval.boolConstant = false;
                            return T_BoolConstant;
                        }

{DECIMAL}               {
                            yylval.integerConstant = strtol(yytext, NULL, 10);
                            return T_IntConstant;
                        } 

{HEX}                   {
                            yylval.integerConstant = strtol(yytext, NULL, 16);
                            return T_IntConstant;
                        }

{FLOAT}                 {
                            yylval.doubleConstant = atof(yytext);
                            return T_DoubleConstant;
                        }

{IDEANTIFIER}           {
                            if (strlen(yytext) > MaxIdentLen)
                                ReportError::LongIdentifier(&yylloc, yytext);
                            
                            strncpy(yylval.identifier, yytext, MaxIdentLen);
                            yylval.identifier[MaxIdentLen] = '\0';
                            
                            return T_Identifier;
                        }

%%                                                                    

void InitScanner()
{
    PrintDebug("lex", "Initializing scanner");
    //yy_flex_debug = true;
    linenum = 1;
    colno = 1;
}

static void DoBeforeEachAction()
{
  yylloc.first_line = yylloc.last_line = linenum;

  yylloc.first_column = colno;
  yylloc.last_column = colno + strlen(yytext) - 1;
  colno = colno + strlen(yytext);
}