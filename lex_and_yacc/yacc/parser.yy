/* $Id: parser.yy 48 2009-09-05 08:07:10Z tb $ -*- mode: c++ -*- */
/** \file parser.yy Contains the dcc Bison parser source */

%{ /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>

#include "expression.h"

#define MaxIdentLen 31

%}

/*** yacc/bison Declarations ***/

/* add debug output code to generated parser. disable this for release
 * versions. */
%debug

/* start symbol is named "start" */
%start start

/* write out a header file containing the token defines */
%defines

/* use newer C++ skeleton file */
%skeleton "lalr1.cc"


/* set the parser's class identifier */
%define "parser_class_name" {"Parser"}

/* keep track of the current position within the input */
%locations
%initial-action
{
    // initialize the initial location object
    @$.begin.filename = @$.end.filename = &driver.streamname;
};

/* The driver is passed by reference to the parser and to the scanner. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class Driver& driver }

/* verbose error messages */
%error-verbose

 /*** BEGIN dcc - Change the dcc grammar's tokens below ***/

%union {
    int       integerVal;
    double      doubleVal;
    std::string*    stringVal;
    bool boolVal;
    char identifier[MaxIdentLen+1];
    class CalcNode*   calcnode;
}

%token      END      0  "end of file"
%token      EOL   "end of line"
%token <integerVal> INTEGER   "integer"
%token <doubleVal>  DOUBLE    "double"
%token <stringVal>  STRING    "string"

/*dcc tokens*/
%token   T_Void T_Bool T_Int T_Double T_String T_Class
%token   T_LessEqual T_GreaterEqual T_Equal T_NotEqual T_Dims T_Increment T_Decrement
%token   T_And T_Or T_Null T_Extends T_This T_Interface T_Implements
%token   T_While T_For T_If T_Else T_Return T_Break T_Switch T_Case T_Default
%token   T_New T_NewArray T_Print T_ReadInteger T_ReadLine

%token   <identifier> T_Identifier
%token   <stringVal>  T_StringConstant
%token   <integerVal> T_IntConstant
%token   <doubleVal>  T_DoubleConstant
%token   <boolVal>    T_BoolConstant



%type <calcnode>  constant variable
%type <calcnode>  atomexpr powexpr unaryexpr mulexpr addexpr expr

/* Non-terminal types
 * ------------------
 * In order for yacc to assign/access the correct field of $$, $1, we
 * must to declare which field is appropriate for the non-terminal.
 * As an example, this first type declaration establishes that the DeclList
 * non-terminal uses the field named "declList" in the yylval union. This
 * means that when we are setting $$ for a reduction for DeclList or reading
 * $n which corresponds to a DeclList nonterminal we are accessing the field
 * of the union named "declList" which is of type List<Decl*>.
 */
%type <program>       Program
%type <declList>      DeclList
%type <decl>          Decl
%type <vardecl>       VarDecl
%type <fndecl>        FnDecl
%type <classdecl>     ClassDecl
%type <interfacedecl> InterfaceDecl
%type <simpletype>    Type
%type <namedtype>     NamedType
%type <arraytype>     ArrayType
%type <vardecls>      Formals
%type <vardecls>      Variables
%type <implements>    Implements
%type <implements>    Impl
%type <namedtype>     Extend
%type <decl>          Field
%type <declList>      Fields
%type <decl>          Prototype
%type <declList>      Prototypes
%type <vardecls>      VarDecls
%type <stmt>          Stmt
%type <stmts>         Stmts
%type <stmtblock>     StmtBlock
%type <ifstmt>        IfStmt
%type <whilestmt>     WhileStmt
%type <forstmt>       ForStmt
%type <rtnstmt>       ReturnStmt
%type <brkstmt>       BreakStmt
%type <switchstmt>    SwitchStmt
%type <casestmts>     Cases
%type <casestmt>      Case
%type <defaultstmt>   Default
%type <pntstmt>   PrintStmt
%type <expr>          Expr
%type <expr>          OptExpr
%type <exprs>         Exprs
%type <exprs>       Actuals
%type <expr>        Constant
%type <intconst>      IntConstant 
%type <boolconst>     BoolConstant
%type <stringconst>   StringConstant
%type <doubleconst>   DoubleConstant
%type <nullconst>     NullConstant
%type <call>          Call
%type <arithmeticexpr> ArithmeticExpr
%type <relationalexpr> RelationalExpr
%type <equalityexpr>   EqualityExpr
%type <logicalexpr>    LogicalExpr
%type <assignexpr>     AssignExpr
%type <postfixexpr>    PostfixExpr
%type <lvalue>        LValue
%type <fieldaccess>   FieldAccess
%type <arrayaccess>   ArrayAccess




%destructor { delete $$; } STRING
%destructor { delete $$; } constant variable
%destructor { delete $$; } atomexpr powexpr unaryexpr mulexpr addexpr expr

 /*** END dcc - Change the dcc grammar's tokens above ***/

%{

#include "driver.h"
#include "scanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex

%}

%% /*** Grammar Rules ***/

 /*** BEGIN dcc - Change the dcc grammar rules below ***/

constant : INTEGER
           {
         $$ = new CNConstant($1);
     }
         | DOUBLE
           {
         $$ = new CNConstant($1);
     }

variable : STRING
           {
         if (!driver.calc.existsVariable(*$1)) {
       error(yyloc, std::string("Unknown variable \"") + *$1 + "\"");
       delete $1;
       YYERROR;
         }
         else {
       $$ = new CNConstant( driver.calc.getVariable(*$1) );
       delete $1;
         }
     }

atomexpr : constant
           {
         $$ = $1;
     }
         | variable
           {
         $$ = $1;
     }
         | '(' expr ')'
           {
         $$ = $2;
     }

powexpr : atomexpr
          {
        $$ = $1;
    }
        | atomexpr '^' powexpr
          {
        $$ = new CNPower($1, $3);
    }

unaryexpr : powexpr
            {
    $$ = $1;
      }
          | '+' powexpr
            {
    $$ = $2;
      }
          | '-' powexpr
            {
    $$ = new CNNegate($2);
      }

mulexpr : unaryexpr
          {
        $$ = $1;
    }
        | mulexpr '*' unaryexpr
          {
        $$ = new CNMultiply($1, $3);
    }
        | mulexpr '/' unaryexpr
          {
        $$ = new CNDivide($1, $3);
    }
        | mulexpr '%' unaryexpr
          {
        $$ = new CNModulo($1, $3);
    }

addexpr : mulexpr
          {
        $$ = $1;
    }
        | addexpr '+' mulexpr
          {
        $$ = new CNAdd($1, $3);
    }
        | addexpr '-' mulexpr
          {
        $$ = new CNSubtract($1, $3);
    }

expr  : addexpr
          {
        $$ = $1;
    }

assignment : STRING '=' expr
             {
     driver.calc.variables[*$1] = $3->evaluate();
     std::cout << "Setting variable " << *$1
         << " = " << driver.calc.variables[*$1] << "\n";
     delete $1;
     delete $3;
       }

start : /* empty */
        | start ';'
        | start EOL
  | start assignment ';'
  | start assignment EOL
  | start assignment END
        | start expr ';'
          {
        driver.calc.expressions.push_back($2);
    }
        | start expr EOL
          {
        driver.calc.expressions.push_back($2);
    }
        | start expr END
          {
        driver.calc.expressions.push_back($2);
    }

 /*** END dcc - Change the dcc grammar rules above ***/

%% /*** Additional Code ***/

void dcc::Parser::error(const Parser::location_type& l,
          const std::string& m)
{
    driver.error(l, m);
}
