// $Id: scanner.h 17 2007-08-19 18:51:39Z tb $

#ifndef dcc_SCANNER_H
#define dcc_SCANNER_H

// Flex expects the signature of yylex to be defined in the macro YY_DECL, and
// the C++ parser expects it to be declared. We can factor both as follows.

#ifndef YY_DECL

#define YY_DECL                         \
    dcc::Parser::token_type             \
    dcc::Scanner::lex(                  \
    dcc::Parser::semantic_type* yylval, \
    dcc::Parser::location_type* yylloc  \
    )
#endif

#ifndef __FLEX_LEXER_H
#define yyFlexLexer dccFlexLexer
#include "FlexLexer.h"
#undef yyFlexLexer
#endif

#include "parser.tab.hh"

typedef enum { 
    T_Void = 256,
    T_Int, T_Double, T_Bool, T_String, T_Class, T_Null, T_Dims,
    T_LessEqual, T_GreaterEqual, T_Equal, T_NotEqual, T_And, T_Or,
    T_While, T_For, T_If, T_Else, T_Return, T_Break,
    T_Extends, T_This, T_Implements, T_Interface, T_New, T_NewArray,
    T_Identifier, T_StringConstant, T_IntConstant, T_DoubleConstant,
    T_BoolConstant, T_Print, T_ReadInteger, T_ReadLine,
    T_NumTokenTypes
} TokenType;

static const char *gTokenNames[T_NumTokenTypes] = {
  "T_Void", "T_Int", "T_Double", "T_Bool", "T_String", "T_Class", "T_Null", "T_Dims",
  "T_LessEqual", "T_GreaterEqual", "T_Equal", "T_NotEqual",
  "T_And", "T_Or", "T_While", "T_For", "T_If", "T_Else", "T_Return",
  "T_Break", "T_Extends", "T_This", "T_Implements", "T_Interface",
  "T_New", "T_NewArray","T_Identifier", "T_StringConstant",
  "T_IntConstant", "T_DoubleConstant", "T_BoolConstant", "T_Print",
  "T_ReadInteger", "T_ReadLine"
};

namespace dcc {

/** Scanner is a derived class to add some extra function to the scanner
 * class. Flex itself creates a class named yyFlexLexer, which is renamed using
 * macros to dccFlexLexer. However we change the context of the generated
 * yylex() function to be contained within the Scanner class. This is required
 * because the yylex() defined in dccFlexLexer has no parameters. */
class Scanner : public dccFlexLexer
{
public:
    /** Create a new scanner object. The streams arg_yyin and arg_yyout default
     * to cin and cout, but that assignment is only made when initializing in
     * yylex(). */
    Scanner(std::istream* arg_yyin = 0,
        std::ostream* arg_yyout = 0);

    /** Required for virtual functions */
    virtual ~Scanner();

    /** This is the main lexing function. It is generated by flex according to
     * the macro declaration YY_DECL above. The generated bison parser then
     * calls this virtual function to fetch new tokens. */
    virtual Parser::token_type lex(
    Parser::semantic_type* yylval,
    Parser::location_type* yylloc
    );

    /** Enable debug output (via arg_yyout) if compiled into the scanner. */
    void set_debug(bool b);
};

} // namespace dcc

#endif // dcc_SCANNER_H
