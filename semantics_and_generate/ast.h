/**
 * File: ast.h
 * ----------- 
 * This file defines the abstract base class Node and the concrete 
 * Identifier and Error node subclasses that are used through the tree as 
 * leaf nodes. A parse tree is a hierarchical collection of ast nodes (or, 
 * more correctly, of instances of concrete subclassses such as VarDecl,
 * ForStmt, and AssignExpr).
 * 
 * Location: Each node maintains its lexical location (line and columns in 
 * file), that location can be NULL for those nodes that don't care/use 
 * locations. The location is typcially set by the node constructor.  The 
 * location is used to provide the context when reporting semantic errors.
 *
 * Parent: Each node has a pointer to its parent. For a Program node, the 
 * parent is NULL, for all other nodes it is the pointer to the node one level
 * up in the parse tree.  The parent is not set in the constructor (during a 
 * bottom-up parse we don't know the parent at the time of construction) but 
 * instead we wait until assigning the children into the parent node and then 
 * set up links in both directions. The parent link is typically not used 
 * during parsing, but is more important in later phases.
 *
 * Semantic analysis: For pp3 you are adding "Check" behavior to the ast
 * node classes. Your semantic analyzer should do an inorder walk on the
 * parse tree, and when visiting each node, verify the particular
 * semantic rules that apply to that construct.

 */

#ifndef _H_ast
#define _H_ast

#include <stdlib.h>   // for NULL

#include <iostream>

#include "errors.h"
#include "hashtable.h"
#include "list.h"
#include "location.h"
#include "sparsepp.h"
#include "errors.h"
#include "list.h"

using spp::sparse_hash_map;

class Decl;

class Node  {
 protected:
  yyltype *location;
  Node *parent;

 public:
  Node(yyltype loc);
  Node();
  virtual ~Node() {}
    
  yyltype *GetLocation()   { return location; }
  void SetParent(Node *p)  { parent = p; }
  Node *GetParent()        { return parent; }

<<<<<<< HEAD
  virtual void CheckDeclError() {}
  virtual void CheckStatements() {}
  virtual Hashtable<Decl*> *GetSymTable() { return NULL; }
=======
    virtual const char *GetPrintNameForNode() = 0;
    
    virtual void CheckDeclError() {}
    virtual void CheckStatementsError() {}
    //virtual sparse_hash_map<Decl*> *GetSymTable() {return NULL;}
    // Print() is deliberately _not_ virtual
    // subclasses should override PrintChildren() instead
    void Print(int indentLevel, const char *label = NULL); 
    virtual void PrintChildren(int indentLevel)  {}
>>>>>>> f1924cde196d558e91d8cc331e0a2a5b9a4357f3
};
   

class Identifier : public Node 
{
 protected:
  char *name;
    
<<<<<<< HEAD
 public:
  Identifier(yyltype loc, const char *name);
  const char *GetName() { return name; }
  Decl *CheckIdDecl();
  Decl *CheckIdDecl(Hashtable<Decl*> *sym_table, const char *name);
  friend ostream& operator<<(ostream& out, Identifier *id) { if (id) return out << id->name; else return out;}
=======
  public:
    Identifier(yyltype loc, const char *name);
    const char *GetPrintNameForNode()   { return "Identifier"; }
    void PrintChildren(int indentLevel);
    const char *GetName() { return name; }
>>>>>>> f1924cde196d558e91d8cc331e0a2a5b9a4357f3
};


// This node class is designed to represent a portion of the tree that 
// encountered syntax errors during parsing. The partial completed tree
// is discarded along with the states being popped, and an instance of
// the Error class can stand in as the placeholder in the parse tree
// when your parser can continue after an error.
class Error : public Node
{
 public:
 Error() : Node() {}
};

#endif
