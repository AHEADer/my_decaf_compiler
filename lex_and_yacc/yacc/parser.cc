// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.
#line 4 "parser.yy" // lalr1.cc:404
 /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>
//#include "scanner.h"
#include "expression.h"

#define MaxIdentLen 31


#line 48 "parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.hh"

// User implementation prologue.
#line 144 "parser.yy" // lalr1.cc:412


#include "driver.h"
#include "scanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex


#line 74 "parser.cc" // lalr1.cc:412


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 160 "parser.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (class Driver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  Parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 38 "parser.yy" // lalr1.cc:741
{
    // initialize the initial location object
    yyla.location.begin.filename = yyla.location.end.filename = &driver.streamname;
}

#line 539 "parser.cc" // lalr1.cc:741

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 161 "parser.yy" // lalr1.cc:859
    {
                                      yystack_[0].location;
                                      /* pp2: The @1 is needed to convince
                                       * yacc to set up yylloc. You can remove
                                       * it once you have other uses of @n*/
                                      (yylhs.value.program) = NULL;
                                     }
#line 655 "parser.cc" // lalr1.cc:859
    break;

  case 3:
#line 170 "parser.yy" // lalr1.cc:859
    { (yylhs.value.declList) = NULL; }
#line 661 "parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 171 "parser.yy" // lalr1.cc:859
    { (yylhs.value.declList) = NULL; }
#line 667 "parser.cc" // lalr1.cc:859
    break;

  case 9:
#line 180 "parser.yy" // lalr1.cc:859
    { (yylhs.value.vardecl) = (yylhs.value.vardecl) = NULL; }
#line 673 "parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 183 "parser.yy" // lalr1.cc:859
    { (yylhs.value.simpletype) = NULL; }
#line 679 "parser.cc" // lalr1.cc:859
    break;

  case 11:
#line 184 "parser.yy" // lalr1.cc:859
    { (yylhs.value.simpletype) = NULL; }
#line 685 "parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 185 "parser.yy" // lalr1.cc:859
    { (yylhs.value.simpletype) = NULL; }
#line 691 "parser.cc" // lalr1.cc:859
    break;

  case 13:
#line 186 "parser.yy" // lalr1.cc:859
    { (yylhs.value.simpletype) = NULL; }
#line 697 "parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 191 "parser.yy" // lalr1.cc:859
    { (yylhs.value.namedtype) = NULL; }
#line 703 "parser.cc" // lalr1.cc:859
    break;

  case 17:
#line 194 "parser.yy" // lalr1.cc:859
    { (yylhs.value.arraytype) = NULL; }
#line 709 "parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 198 "parser.yy" // lalr1.cc:859
    { (yylhs.value.fndecl) = NULL; }
#line 715 "parser.cc" // lalr1.cc:859
    break;

  case 19:
#line 200 "parser.yy" // lalr1.cc:859
    { (yylhs.value.fndecl) = NULL; }
#line 721 "parser.cc" // lalr1.cc:859
    break;

  case 21:
#line 204 "parser.yy" // lalr1.cc:859
    { (yylhs.value.vardecls) = NULL; }
#line 727 "parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 208 "parser.yy" // lalr1.cc:859
    { (yylhs.value.vardecls) = NULL; }
#line 733 "parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 209 "parser.yy" // lalr1.cc:859
    { (yylhs.value.vardecls) = NULL; }
#line 739 "parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 213 "parser.yy" // lalr1.cc:859
    { (yylhs.value.classdecl) = NULL; }
#line 745 "parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 215 "parser.yy" // lalr1.cc:859
    { (yylhs.value.classdecl) = NULL; }
#line 751 "parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 219 "parser.yy" // lalr1.cc:859
    { (yylhs.value.namedtype) = NULL; }
#line 757 "parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 220 "parser.yy" // lalr1.cc:859
    { (yylhs.value.namedtype) = NULL; }
#line 763 "parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 224 "parser.yy" // lalr1.cc:859
    { (yylhs.value.implements) = NULL; }
#line 769 "parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 225 "parser.yy" // lalr1.cc:859
    { (yylhs.value.implements) = NULL; }
#line 775 "parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 229 "parser.yy" // lalr1.cc:859
    { (yylhs.value.implements) = NULL; }
#line 781 "parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 230 "parser.yy" // lalr1.cc:859
    { (yylhs.value.implements) = NULL; }
#line 787 "parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 233 "parser.yy" // lalr1.cc:859
    { (yylhs.value.declList) = NULL; }
#line 793 "parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 234 "parser.yy" // lalr1.cc:859
    { (yylhs.value.declList) = NULL; }
#line 799 "parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 242 "parser.yy" // lalr1.cc:859
    { (yylhs.value.interfacedecl) = NULL; }
#line 805 "parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 244 "parser.yy" // lalr1.cc:859
    { (yylhs.value.interfacedecl) = NULL; }
#line 811 "parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 247 "parser.yy" // lalr1.cc:859
    { (yylhs.value.declList) = NULL; }
#line 817 "parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 248 "parser.yy" // lalr1.cc:859
    { (yylhs.value.declList) = NULL; }
#line 823 "parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 252 "parser.yy" // lalr1.cc:859
    { (yylhs.value.decl) = NULL; }
#line 829 "parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 254 "parser.yy" // lalr1.cc:859
    { (yylhs.value.decl) = NULL; }
#line 835 "parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 257 "parser.yy" // lalr1.cc:859
    { (yylhs.value.stmtblock) = NULL; }
#line 841 "parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 258 "parser.yy" // lalr1.cc:859
    { (yylhs.value.stmtblock) = NULL; }
#line 847 "parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 261 "parser.yy" // lalr1.cc:859
    { (yylhs.value.vardecls) = NULL;    }
#line 853 "parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 262 "parser.yy" // lalr1.cc:859
    { (yylhs.value.vardecls) = NULL;  }
#line 859 "parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 265 "parser.yy" // lalr1.cc:859
    { (yylhs.value.stmts) = NULL; }
#line 865 "parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 266 "parser.yy" // lalr1.cc:859
    { (yylhs.value.stmts) = NULL;  }
#line 871 "parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 282 "parser.yy" // lalr1.cc:859
    { (yylhs.value.ifstmt) = NULL; }
#line 877 "parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 284 "parser.yy" // lalr1.cc:859
    { (yylhs.value.ifstmt) = NULL; }
#line 883 "parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 289 "parser.yy" // lalr1.cc:859
    { (yylhs.value.whilestmt) = NULL; }
#line 889 "parser.cc" // lalr1.cc:859
    break;

  case 60:
#line 293 "parser.yy" // lalr1.cc:859
    { (yylhs.value.forstmt) = NULL; }
#line 895 "parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 296 "parser.yy" // lalr1.cc:859
    { (yylhs.value.rtnstmt) = NULL; }
#line 901 "parser.cc" // lalr1.cc:859
    break;

  case 62:
#line 299 "parser.yy" // lalr1.cc:859
    { (yylhs.value.brkstmt) = NULL; }
#line 907 "parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 303 "parser.yy" // lalr1.cc:859
    { (yylhs.value.switchstmt) = NULL; }
#line 913 "parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 306 "parser.yy" // lalr1.cc:859
    { (yylhs.value.casestmts) = NULL; }
#line 919 "parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 307 "parser.yy" // lalr1.cc:859
    { (yylhs.value.casestmts) = NULL; }
#line 925 "parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 311 "parser.yy" // lalr1.cc:859
    { (yylhs.value.casestmt) = NULL; }
#line 931 "parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 312 "parser.yy" // lalr1.cc:859
    { (yylhs.value.casestmt) = NULL; }
#line 937 "parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 315 "parser.yy" // lalr1.cc:859
    { (yylhs.value.defaultstmt) = NULL; }
#line 943 "parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 316 "parser.yy" // lalr1.cc:859
    { (yylhs.value.defaultstmt) = NULL; }
#line 949 "parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 320 "parser.yy" // lalr1.cc:859
    { (yylhs.value.pntstmt) = NULL; }
#line 955 "parser.cc" // lalr1.cc:859
    break;

  case 74:
#line 326 "parser.yy" // lalr1.cc:859
    { (yylhs.value.expr) = NULL; }
#line 961 "parser.cc" // lalr1.cc:859
    break;

  case 76:
#line 328 "parser.yy" // lalr1.cc:859
    { (yylhs.value.expr) = NULL; }
#line 967 "parser.cc" // lalr1.cc:859
    break;

  case 82:
#line 334 "parser.yy" // lalr1.cc:859
    { (yylhs.value.expr) = NULL; }
#line 973 "parser.cc" // lalr1.cc:859
    break;

  case 83:
#line 335 "parser.yy" // lalr1.cc:859
    { (yylhs.value.expr) = NULL; }
#line 979 "parser.cc" // lalr1.cc:859
    break;

  case 84:
#line 336 "parser.yy" // lalr1.cc:859
    { (yylhs.value.expr) = NULL; }
#line 985 "parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 338 "parser.yy" // lalr1.cc:859
    { (yylhs.value.expr) = NULL; }
#line 991 "parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 342 "parser.yy" // lalr1.cc:859
    { (yylhs.value.assignexpr) = NULL; }
#line 997 "parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 345 "parser.yy" // lalr1.cc:859
    { (yylhs.value.arithmeticexpr) = NULL; }
#line 1003 "parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 346 "parser.yy" // lalr1.cc:859
    { (yylhs.value.arithmeticexpr) = NULL; }
#line 1009 "parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 347 "parser.yy" // lalr1.cc:859
    { (yylhs.value.arithmeticexpr) = NULL; }
#line 1015 "parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 348 "parser.yy" // lalr1.cc:859
    { (yylhs.value.arithmeticexpr) = NULL; }
#line 1021 "parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 349 "parser.yy" // lalr1.cc:859
    { (yylhs.value.arithmeticexpr) = NULL; }
#line 1027 "parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 351 "parser.yy" // lalr1.cc:859
    { (yylhs.value.arithmeticexpr) = NULL; }
#line 1033 "parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 354 "parser.yy" // lalr1.cc:859
    { (yylhs.value.postfixexpr) = NULL; }
#line 1039 "parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 355 "parser.yy" // lalr1.cc:859
    { (yylhs.value.postfixexpr) = NULL; }
#line 1045 "parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 359 "parser.yy" // lalr1.cc:859
    { (yylhs.value.equalityexpr) = NULL; }
#line 1051 "parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 361 "parser.yy" // lalr1.cc:859
    { (yylhs.value.equalityexpr) = NULL; }
#line 1057 "parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 365 "parser.yy" // lalr1.cc:859
    { (yylhs.value.relationalexpr) = NULL; }
#line 1063 "parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 367 "parser.yy" // lalr1.cc:859
    { (yylhs.value.relationalexpr) = NULL; }
#line 1069 "parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 369 "parser.yy" // lalr1.cc:859
    { (yylhs.value.relationalexpr) = NULL; }
#line 1075 "parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 371 "parser.yy" // lalr1.cc:859
    { (yylhs.value.relationalexpr) = NULL; }
#line 1081 "parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 375 "parser.yy" // lalr1.cc:859
    { (yylhs.value.logicalexpr) = NULL; }
#line 1087 "parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 377 "parser.yy" // lalr1.cc:859
    { (yylhs.value.logicalexpr) = NULL; }
#line 1093 "parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 378 "parser.yy" // lalr1.cc:859
    { (yylhs.value.logicalexpr) = NULL; }
#line 1099 "parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 382 "parser.yy" // lalr1.cc:859
    { (yylhs.value.exprs) = NULL; }
#line 1105 "parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 383 "parser.yy" // lalr1.cc:859
    { (yylhs.value.exprs) = NULL; }
#line 1111 "parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 387 "parser.yy" // lalr1.cc:859
    { (yylhs.value.expr) = NULL; }
#line 1117 "parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 395 "parser.yy" // lalr1.cc:859
    { (yylhs.value.fieldaccess) = NULL; }
#line 1123 "parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 397 "parser.yy" // lalr1.cc:859
    { (yylhs.value.fieldaccess) = NULL; }
#line 1129 "parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 401 "parser.yy" // lalr1.cc:859
    { (yylhs.value.call) = NULL; }
#line 1135 "parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 403 "parser.yy" // lalr1.cc:859
    { (yylhs.value.call) = NULL; }
#line 1141 "parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 406 "parser.yy" // lalr1.cc:859
    { (yylhs.value.arrayaccess) = NULL; }
#line 1147 "parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 410 "parser.yy" // lalr1.cc:859
    { (yylhs.value.exprs) = NULL; }
#line 1153 "parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 420 "parser.yy" // lalr1.cc:859
    { (yylhs.value.intconst) = NULL; }
#line 1159 "parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 423 "parser.yy" // lalr1.cc:859
    { (yylhs.value.doubleconst) = NULL; }
#line 1165 "parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 426 "parser.yy" // lalr1.cc:859
    { (yylhs.value.boolconst) = NULL; }
#line 1171 "parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 429 "parser.yy" // lalr1.cc:859
    { (yylhs.value.stringconst) = NULL; }
#line 1177 "parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 432 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nullconst) = NULL; }
#line 1183 "parser.cc" // lalr1.cc:859
    break;


#line 1187 "parser.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -96;

  const signed char Parser::yytable_ninf_ = -108;

  const short int
  Parser::yypact_[] =
  {
      20,    -8,   -96,   -96,   -96,   -96,    -4,    10,   -96,    60,
      20,   -96,   -96,     8,   -96,   -96,   -96,   -96,   -96,    37,
      76,    61,   -96,   -96,   -96,    49,   105,    78,    91,     2,
     -96,   105,    19,    80,    86,   -96,    78,    97,    85,   -96,
      68,    57,   -96,    89,   -96,   101,   105,   -96,   106,    82,
     109,   120,   -96,   -96,   101,   -96,   -96,    69,    78,   -96,
     -96,   -96,    93,   -96,   105,   105,   -96,   121,   -96,   -96,
     -96,   -96,   122,   131,   -96,   -96,   135,   136,   142,   463,
     123,   143,   150,   147,   148,   149,   154,    65,   -96,   -96,
     -96,   -96,   463,   -96,   463,   463,   -96,    77,   -96,   368,
     -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   324,   -96,
     -96,   -96,   -96,   -96,   -96,   156,     1,   -96,   -96,   -96,
     -96,   -96,   -96,   -96,   -96,   -96,   157,   161,   463,   463,
     463,   159,   162,   -96,   463,   -96,   463,   463,   163,   164,
     463,   172,   324,   324,   167,   -96,   -96,   463,   463,   463,
     463,   463,   463,   463,   463,   463,   463,   463,   463,   463,
     168,   463,   -96,   -96,   -96,   463,   -96,   -96,   184,   177,
     237,   -96,   249,   260,   324,    -1,   -96,   -96,   165,   187,
     -96,   324,   324,   324,   324,   324,   324,   324,   324,   324,
     324,   324,   324,   324,   191,   160,   324,   434,   463,   434,
     194,   105,   201,   463,   -96,   463,   -96,   -96,   313,   180,
     220,     9,   -96,   324,   207,   463,   434,   213,    87,   -96,
     -96,   -96,   211,   -96,   208,   214,   -96,   209,   434,   401,
     434,   -96,   -96,   401,   401
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,    12,    10,    11,    13,     0,     0,    16,     0,
       2,     4,     5,     0,    14,    15,     6,     7,     8,     0,
      27,     0,     1,     3,    17,     0,    21,     0,    29,     0,
       9,    21,     0,     0,    20,    26,     0,     0,     0,    37,
       0,     0,    39,     0,    23,     0,     0,    31,    28,     0,
       0,     0,    36,    38,     0,    45,    19,     0,     0,    25,
      34,    35,     0,    33,    21,    21,    18,   107,    22,    30,
      24,    32,     0,     0,   126,    74,     0,     0,     0,   107,
       0,     0,     0,     0,     0,     0,     0,   110,   125,   122,
     123,   124,     0,    43,     0,     0,    44,     0,    56,   107,
      47,    49,    50,    51,    53,    52,    54,    55,   106,    71,
      77,    81,    78,    79,    80,     0,    73,   108,    75,   109,
      72,   117,   118,   119,   120,   121,     0,     0,     0,   107,
       0,   110,     0,    62,     0,    84,     0,     0,     0,     0,
     116,     0,    92,   103,     0,    42,    46,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    48,    93,    94,     0,    41,    40,     0,     0,
       0,    61,     0,     0,   105,     0,    82,    83,   115,     0,
      76,    99,   100,    95,    96,   101,   102,    87,    88,    89,
      90,    91,    97,    98,   111,     0,    86,   107,     0,   107,
       0,     0,     0,     0,   112,   116,   114,    59,     0,    57,
       0,     0,    70,   104,     0,   107,   107,     0,    69,    65,
      85,   113,     0,    58,     0,     0,    64,     0,   107,    67,
     107,    63,    60,    66,    68
  };

  const short int
  Parser::yypgoto_[] =
  {
     -96,   -96,   -96,   253,   -30,   -26,   -15,   -96,   -31,   -29,
     -96,   -96,   -96,   -96,   -96,   -96,   203,   -96,   -96,   227,
      40,   -96,   -94,   -95,   -96,   -96,   -96,   -96,   -96,   -96,
     -96,    51,   -96,   -96,   -81,   -96,   -96,   -96,   -96,   -96,
     -96,   137,   -78,   -96,   -96,   -96,   -96,    70,   -96,    59,
     -96,   -96,   -96,   -96
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     9,    10,    11,    12,    13,    14,    15,    16,    33,
      34,    17,    28,    37,    48,    62,    63,    18,    41,    42,
      98,    67,    99,   100,   101,   102,   103,   104,   105,   106,
     218,   219,   227,   107,   108,   109,   110,   111,   112,   113,
     114,   178,   115,   116,   117,   118,   119,   179,   120,   121,
     122,   123,   124,   125
  };

  const short int
  Parser::yytable_[] =
  {
      32,   132,    43,    40,   146,    32,    38,     2,     3,     4,
       5,   141,    35,   142,   143,    40,   163,   164,    61,    60,
      57,    47,    24,    24,     1,     2,     3,     4,     5,     6,
      19,    61,    60,    24,    20,    72,    73,    96,    32,    32,
       8,    97,     7,    69,   202,   203,    25,   168,    21,   170,
      39,   169,   165,   172,   220,   173,   174,    44,     8,   174,
      22,    38,     2,     3,     4,     5,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   -16,
     195,    26,    24,    24,   196,    56,     1,     2,     3,     4,
       5,    24,    30,    31,    66,     8,    27,     1,     2,     3,
       4,     5,   207,   -16,   209,    52,    51,    68,    29,   140,
       2,     3,     4,     5,    36,   144,     8,   208,   217,   225,
       8,   223,   213,    50,   174,    45,     2,     3,     4,     5,
      59,     8,    46,   232,    54,   233,   234,   222,   146,   146,
      74,    70,    75,     8,    49,    76,    77,    78,    55,    79,
      80,    81,    58,    64,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    65,    92,   133,   126,    55,    93,
     147,   148,   149,   150,    94,   211,   127,   151,   152,   128,
     129,    95,   147,   148,   149,   150,   130,   134,   135,   151,
     152,   136,   137,   138,   147,   148,   149,   150,   139,   162,
     166,   151,   152,   140,   167,   171,   194,   216,   176,   177,
      30,   203,   153,   154,   155,   156,   157,   180,   158,   159,
     198,   160,   161,   206,   153,   154,   155,   156,   157,   197,
     158,   159,   204,   160,   161,   205,   153,   154,   155,   156,
     157,   210,   158,   159,   212,   160,   161,   147,   148,   149,
     150,   217,   221,    89,   151,   152,   228,   231,   229,   147,
     148,   149,   150,    23,   230,    71,   151,   152,    53,   226,
     147,   148,   149,   150,   175,   214,   224,   151,   152,     0,
       0,     0,   199,     0,     0,     0,     0,     0,     0,   153,
     154,   155,   156,   157,   200,   158,   159,     0,   160,   161,
       0,   153,   154,   155,   156,   157,   201,   158,   159,     0,
     160,   161,   153,   154,   155,   156,   157,     0,   158,   159,
       0,   160,   161,   147,   148,   149,   150,     0,     0,     0,
     151,   152,     0,     0,   147,   148,   149,   150,     0,     0,
       0,   151,   152,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   215,     0,     0,     0,
       0,     0,     0,     0,     0,   153,   154,   155,   156,   157,
       0,   158,   159,     0,   160,   161,   153,   154,   155,   156,
     157,     0,   158,   159,     0,   160,   161,    74,     0,    75,
       0,     0,    76,    77,    78,     0,    79,    80,    81,     0,
       0,    82,    83,    84,    85,    86,   131,    88,    89,    90,
      91,     0,    92,     0,     0,    55,   145,     0,     0,     0,
      74,    94,    75,     0,     0,    76,    77,    78,    95,    79,
      80,    81,     0,     0,    82,    83,    84,    85,    86,   131,
      88,    89,    90,    91,  -107,    92,     0,     0,    55,     0,
       0,     0,     0,    74,    94,    75,     0,     0,    76,    77,
      78,    95,    79,    80,    81,     0,     0,    82,    83,    84,
      85,    86,   131,    88,    89,    90,    91,     0,    92,     0,
       0,    55,    74,     0,    75,     0,     0,    94,     0,     0,
       0,     0,     0,     0,    95,     0,    82,    83,     0,    85,
      86,   131,    88,    89,    90,    91,     0,    92,     0,     0,
       0,     0,     0,     0,     0,     0,    94,     0,     0,     0,
       0,     0,     0,    95
  };

  const short int
  Parser::yycheck_[] =
  {
      26,    79,    31,    29,    99,    31,     4,     5,     6,     7,
       8,    92,    27,    94,    95,    41,    15,    16,    49,    49,
      46,    36,    14,    14,     4,     5,     6,     7,     8,     9,
      38,    62,    62,    14,    38,    64,    65,    67,    64,    65,
      38,    67,    22,    58,    45,    46,    38,   128,    38,   130,
      48,   129,    51,   134,    45,   136,   137,    38,    38,   140,
       0,     4,     5,     6,     7,     8,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,    14,
     161,    44,    14,    14,   165,    45,     4,     5,     6,     7,
       8,    14,    43,    44,    54,    38,    20,     4,     5,     6,
       7,     8,   197,    38,   199,    48,    38,    38,    47,    44,
       5,     6,     7,     8,    23,    38,    38,   198,    31,    32,
      38,   216,   203,    38,   205,    45,     5,     6,     7,     8,
      48,    38,    46,   228,    45,   229,   230,   215,   233,   234,
      19,    48,    21,    38,    47,    24,    25,    26,    47,    28,
      29,    30,    46,    44,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    44,    44,    43,    45,    47,    48,
      10,    11,    12,    13,    53,   201,    45,    17,    18,    44,
      44,    60,    10,    11,    12,    13,    44,    44,    38,    17,
      18,    44,    44,    44,    10,    11,    12,    13,    44,    43,
      43,    17,    18,    44,    43,    43,    38,    27,    45,    45,
      43,    46,    52,    53,    54,    55,    56,    45,    58,    59,
      43,    61,    62,    63,    52,    53,    54,    55,    56,    45,
      58,    59,    45,    61,    62,    44,    52,    53,    54,    55,
      56,    47,    58,    59,    43,    61,    62,    10,    11,    12,
      13,    31,    45,    40,    17,    18,    45,    48,    50,    10,
      11,    12,    13,    10,    50,    62,    17,    18,    41,   218,
      10,    11,    12,    13,   137,   205,   217,    17,    18,    -1,
      -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      53,    54,    55,    56,    45,    58,    59,    -1,    61,    62,
      -1,    52,    53,    54,    55,    56,    46,    58,    59,    -1,
      61,    62,    52,    53,    54,    55,    56,    -1,    58,    59,
      -1,    61,    62,    10,    11,    12,    13,    -1,    -1,    -1,
      17,    18,    -1,    -1,    10,    11,    12,    13,    -1,    -1,
      -1,    17,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    53,    54,    55,    56,
      -1,    58,    59,    -1,    61,    62,    52,    53,    54,    55,
      56,    -1,    58,    59,    -1,    61,    62,    19,    -1,    21,
      -1,    -1,    24,    25,    26,    -1,    28,    29,    30,    -1,
      -1,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    44,    -1,    -1,    47,    48,    -1,    -1,    -1,
      19,    53,    21,    -1,    -1,    24,    25,    26,    60,    28,
      29,    30,    -1,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    19,    53,    21,    -1,    -1,    24,    25,
      26,    60,    28,    29,    30,    -1,    -1,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    44,    -1,
      -1,    47,    19,    -1,    21,    -1,    -1,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    -1,    33,    34,    -1,    36,
      37,    38,    39,    40,    41,    42,    -1,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    60
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     4,     5,     6,     7,     8,     9,    22,    38,    65,
      66,    67,    68,    69,    70,    71,    72,    75,    81,    38,
      38,    38,     0,    67,    14,    38,    44,    20,    76,    47,
      43,    44,    69,    73,    74,    70,    23,    77,     4,    48,
      69,    82,    83,    73,    38,    45,    46,    70,    78,    47,
      38,    38,    48,    83,    45,    47,    84,    69,    46,    48,
      68,    72,    79,    80,    44,    44,    84,    85,    38,    70,
      48,    80,    73,    73,    19,    21,    24,    25,    26,    28,
      29,    30,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    44,    48,    53,    60,    68,    69,    84,    86,
      87,    88,    89,    90,    91,    92,    93,    97,    98,    99,
     100,   101,   102,   103,   104,   106,   107,   108,   109,   110,
     112,   113,   114,   115,   116,   117,    45,    45,    44,    44,
      44,    38,   106,    43,    44,    38,    44,    44,    44,    44,
      44,    98,    98,    98,    38,    48,    87,    10,    11,    12,
      13,    17,    18,    52,    53,    54,    55,    56,    58,    59,
      61,    62,    43,    15,    16,    51,    43,    43,    98,   106,
      98,    43,    98,    98,    98,   105,    45,    45,   105,   111,
      45,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    38,    98,    98,    45,    43,    45,
      45,    46,    45,    46,    45,    44,    63,    87,    98,    87,
      47,    69,    43,    98,   111,    43,    27,    31,    94,    95,
      45,    45,   106,    87,   113,    32,    95,    96,    45,    50,
      50,    48,    87,    86,    86
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    64,    65,    66,    66,    67,    67,    67,    67,    68,
      69,    69,    69,    69,    69,    69,    70,    71,    72,    72,
      73,    73,    74,    74,    75,    75,    76,    76,    77,    77,
      78,    78,    79,    79,    80,    80,    81,    81,    82,    82,
      83,    83,    84,    84,    85,    85,    86,    86,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    88,    88,    89,
      90,    91,    92,    93,    94,    94,    95,    95,    96,    96,
      97,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    99,   100,   100,   100,
     100,   100,   100,   101,   101,   102,   102,   103,   103,   103,
     103,   104,   104,   104,   105,   105,   106,   106,   107,   107,
     108,   108,   109,   109,   110,   111,   111,   112,   112,   112,
     112,   112,   113,   114,   115,   116,   117
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     1,     2,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     2,     6,     6,
       1,     0,     4,     2,     7,     6,     2,     0,     2,     0,
       3,     1,     2,     1,     1,     1,     5,     4,     2,     1,
       6,     6,     4,     3,     2,     0,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     5,     7,     5,
       9,     3,     2,     8,     2,     1,     4,     3,     3,     0,
       5,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     3,     3,     2,     6,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     1,     1,     0,     1,     1,
       1,     3,     4,     6,     4,     1,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"end of line\"", "T_Void",
  "T_Bool", "T_Int", "T_Double", "T_String", "T_Class", "T_LessEqual",
  "T_GreaterEqual", "T_Equal", "T_NotEqual", "T_Dims", "T_Increment",
  "T_Decrement", "T_And", "T_Or", "T_Null", "T_Extends", "T_This",
  "T_Interface", "T_Implements", "T_While", "T_For", "T_If", "T_Else",
  "T_Return", "T_Break", "T_Switch", "T_Case", "T_Default", "T_New",
  "T_NewArray", "T_Print", "T_ReadInteger", "T_ReadLine", "T_Identifier",
  "T_StringConstant", "T_IntConstant", "T_DoubleConstant",
  "T_BoolConstant", "';'", "'('", "')'", "','", "'{'", "'}'",
  "LOWER_THAN_ELSE", "':'", "'='", "'+'", "'-'", "'*'", "'/'", "'%'",
  "UMINUS", "'<'", "'>'", "'!'", "'.'", "'['", "']'", "$accept", "Program",
  "DeclList", "Decl", "VarDecl", "Type", "NamedType", "ArrayType",
  "FnDecl", "Formals", "Variables", "ClassDecl", "Extend", "Impl",
  "Implements", "Fields", "Field", "InterfaceDecl", "Prototypes",
  "Prototype", "StmtBlock", "VarDecls", "Stmts", "Stmt", "IfStmt",
  "WhileStmt", "ForStmt", "ReturnStmt", "BreakStmt", "SwitchStmt", "Cases",
  "Case", "Default", "PrintStmt", "Expr", "AssignExpr", "ArithmeticExpr",
  "PostfixExpr", "EqualityExpr", "RelationalExpr", "LogicalExpr", "Exprs",
  "OptExpr", "LValue", "FieldAccess", "Call", "ArrayAccess", "Actuals",
  "Constant", "IntConstant", "DoubleConstant", "BoolConstant",
  "StringConstant", "NullConstant", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   161,   161,   170,   171,   174,   175,   176,   177,   180,
     183,   184,   185,   186,   187,   188,   191,   194,   197,   199,
     203,   204,   207,   209,   212,   214,   218,   220,   223,   225,
     228,   230,   233,   234,   237,   238,   241,   243,   247,   248,
     251,   253,   257,   258,   261,   262,   265,   266,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   281,   283,   288,
     292,   296,   299,   302,   306,   307,   310,   312,   315,   316,
     319,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   341,   345,   346,   347,
     348,   349,   350,   354,   355,   358,   360,   364,   366,   368,
     370,   374,   376,   378,   382,   383,   386,   387,   391,   392,
     395,   396,   400,   402,   406,   409,   410,   413,   414,   415,
     416,   417,   420,   423,   426,   429,   432
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    60,     2,     2,     2,    56,     2,     2,
      44,    45,    54,    52,    46,    53,    61,    55,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    50,    43,
      58,    51,    59,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    62,     2,    63,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    47,     2,    48,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    49,    57
    };
    const unsigned int user_token_number_max_ = 299;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 1838 "parser.cc" // lalr1.cc:1167
#line 436 "parser.yy" // lalr1.cc:1168
 /*** Additional Code ***/

void dcc::Parser::error(const Parser::location_type& l,
          const std::string& m)
{
    driver.error(l, m);
}
