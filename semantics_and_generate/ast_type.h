/* File: ast_type.h
 * ----------------
 * In our parse tree, Type nodes are used to represent and
 * store type information. The base Type class is used
 * for built-in types, the NamedType for classes and interfaces,
 * and the ArrayType for arrays of other types.  
 */
 
#ifndef _H_ast_type
#define _H_ast_type

#include <string.h>

#include <string>

#include "ast.h"
#include "list.h"


class Type : public Node 
{
  protected:
    char *typeName;
    virtual void print(ostream &out) const { out << typeName;}

  public :
    static Type *intType, *doubleType, *boolType, *voidType,
                *nullType, *stringType, *errorType;

    Type(yyltype loc) : Node(loc) {}
    Type(const char *str);
<<<<<<< HEAD
    virtual Type *GetElemType() { return this; }
    virtual const char *GetTypeName() { return typeName; }
    virtual bool HasSameType(Type *t);
    virtual void CheckTypeError() {}
    friend ostream& operator<<(ostream &out, Type *type) { if (type) type->print(out); return out; }
=======
    
    const char *GetPrintNameForNode() { return "Type"; }
    void PrintChildren(int indentLevel);
    virtual const char *GetTypeName() { return typeName; }
>>>>>>> f1924cde196d558e91d8cc331e0a2a5b9a4357f3
};

class NamedType : public Type 
{
  protected:
    Identifier *id;
    virtual void print(ostream &out) const { out << id; }
    
  public:
    NamedType(Identifier *i);
<<<<<<< HEAD
    Identifier *GetID() { return id; }
    Type *GetElemType() { return this; }
    const char *GetTypeName() { if (id) return id->GetName(); else return NULL; }
    bool HasSameType(Type *nt);
    void CheckTypeError();
=======
    const char *GetTypeName() { if (id) return id->GetName(); else return NULL; }
    const char *GetPrintNameForNode() { return "NamedType"; }
    void PrintChildren(int indentLevel);
>>>>>>> f1924cde196d558e91d8cc331e0a2a5b9a4357f3
};

class ArrayType : public Type 
{
  protected:
    Type *elemType;
    virtual void print(ostream &out) const { out << elemType; }
  public:
    ArrayType(yyltype loc, Type *elemType);
<<<<<<< HEAD
    Type *GetElemType() { return elemType; }
    const char *GetTypeName();
    bool HasSameType(Type *at);
    void CheckTypeError();
=======
    const char *GetTypeName();
    const char *GetPrintNameForNode() { return "ArrayType"; }
    void PrintChildren(int indentLevel);
>>>>>>> f1924cde196d558e91d8cc331e0a2a5b9a4357f3
};

#endif
