# my_decaf_compiler
aim to realize a decaf compiler, good luck to me

# data struct
## ast.h
class Node
class Identifier : public Node 
class Error : public Node

## ast_decl.h
class Decl : public Node 
class VarDecl : public Decl 
class ClassDecl : public Decl 
class InterfaceDecl : public Decl 
class FnDecl : public Decl 

## ast_stmt.h
class Program : public Node
class Stmt : public Node
class StmtBlock : public Stmt 
class ConditionalStmt : public Stmt
class LoopStmt : public ConditionalStmt 
class ForStmt : public LoopStmt 
class WhileStmt : public LoopStmt 
class IfStmt : public ConditionalStmt 
class BreakStmt : public Stmt 
class ReturnStmt : public Stmt  
class PrintStmt : public Stmt
class CaseStmt : public Stmt
class DefaultStmt : public Stmt
class SwitchStmt : public Stmt