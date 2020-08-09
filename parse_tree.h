#pragma once
#ifndef PARSE_TREE_H
#define PARSE_TREE_H
#include <stdio.h>   
#include <stdlib.h>
#include"tree.h"
//class CompUnit_class :public Node { virtual int tmp(){ return 0; } };
//class Decl_class :public Node { virtual int tmp(){ return 0; } };
//class VarDef_class :public Node { virtual int tmp(){ return 0; } };
//class InitVal_class :public Node { virtual int tmp(){ return 0; } };
//class FuncDef_class :public Node { virtual int tmp(){ return 0; } };
//class FuncFParam_class :public Node { virtual int tmp(){ return 0; } };
//class Block_class :public Node { virtual int tmp(){ return 0; } };
//class Stmt_class :public Node { virtual int tmp(){ return 0; } };
//class PrimaryExp_class :public Node { virtual int tmp(){ return 0; } };
//class UnaryExp_class :public Node { virtual int tmp(){ return 0; } };
//class UnaryOp_class :public Node { virtual int tmp(){ return 0; } };
//class MulExp_class :public Node { virtual int tmp(){ return 0; } };
//class AddExp_class :public Node { virtual int tmp(){ return 0; } };
//class RelExp_class :public Node { virtual int tmp(){ return 0; } };
//class EqExp_class :public Node { virtual int tmp(){ return 0; } };
//class LAndExp_class :public Node { virtual int tmp(){ return 0; } };
//class LOrExp_class :public Node { virtual int tmp(){ return 0; } };

typedef class Program_class *Program;
class Program_class :public Node { virtual int tmp() { return 0; } };
typedef class CompUnit_class *CompUnit;
class CompUnit_class :public Node { virtual int tmp() { return 0; } };
typedef class Decl_class *Decl;
class Decl_class :public Node { virtual int tmp() { return 0; } };
typedef class VarDef_class *VarDef;
class VarDef_class :public Node { virtual int tmp() { return 0; } };
typedef class InitVal_class *InitVal;
class InitVal_class :public Node { virtual int tmp() { return 0; } };
typedef class FuncDef_class *FuncDef;
class FuncDef_class :public Node { virtual int tmp() { return 0; } };
typedef class FuncFParam_class *FuncFParam;
class FuncFParam_class :public Node { virtual int tmp() { return 0; } };
typedef class Block_class *Block;
class Block_class :public Node { virtual int tmp() { return 0; } };
typedef class Stmt_class *Stmt;
class Stmt_class :public Node { virtual int tmp() { return 0; } };
typedef class PrimaryExp_class *PrimaryExp;
class PrimaryExp_class :public Node { virtual int tmp() { return 0; } };
typedef class UnaryExp_class *UnaryExp;
class UnaryExp_class :public Node { virtual int tmp() { return 0; } };
typedef class UnaryOp_class *UnaryOp;
class UnaryOp_class :public Node { virtual int tmp() { return 0; } };
typedef class MulExp_class *MulExp;
class MulExp_class :public Node { virtual int tmp() { return 0; } };
typedef class AddExp_class *AddExp;
class AddExp_class :public Node { virtual int tmp() { return 0; } };
typedef class RelExp_class *RelExp;
class RelExp_class :public Node { virtual int tmp() { return 0; } };
typedef class EqExp_class *EqExp;
class EqExp_class :public Node { virtual int tmp() { return 0; } };
typedef class LAndExp_class *LAndExp;
class LAndExp_class :public Node { virtual int tmp() { return 0; } };
typedef class LOrExp_class *LOrExp;
class LOrExp_class :public Node { virtual int tmp() { return 0; } };
typedef class Id_class *Id;
class Id_class :public Node { virtual int tmp() { return 0; } };



typedef List<CompUnit> CompUnits_class;
typedef CompUnits_class *CompUnits;
typedef List<VarDef> VarDefs_class;
typedef VarDefs_class* VarDefs;
typedef List<InitVal> InitVals_class;
typedef InitVals_class* InitVals;
typedef List<FuncFParam> FuncFParams_class;
typedef FuncFParams_class* FuncFParams;
typedef List<Block> Blocks_class;
typedef Blocks_class* Blocks;
typedef List<AddExp> AddExps_class;
typedef AddExps_class* AddExps;
typedef List<AddExp> FuncRParams_class;
typedef FuncRParams_class* FuncRParams;

class program : public Program_class {
public:
	CompUnits e1;
	program(CompUnits t1) {
		e1 = t1;
	}
};

class decl_CompUnit :public  CompUnit_class {
public:
	Decl e1;
	decl_CompUnit(Decl t1) {
		e1 = t1;
	}
};

class funcDef_CompUnit : public CompUnit_class {
public:
	FuncDef e1;
	funcDef_CompUnit(FuncDef t1) {
		e1 = t1;
	}
};

class varDecl :public  Decl_class {
public:
	VarDefs e1;
	varDecl(VarDefs t1) {
		e1 = t1;
	}
};

class constVarDecl :public Decl_class {
public:
	VarDefs e1;
	constVarDecl(VarDefs t1) {
		e1 = t1;
	}
};

class uninit_VarDef :public VarDef_class {
public:
	Id e1;
	AddExps e2;
	uninit_VarDef(Id t1, AddExps t2) {
		e1 = t1;
		e2 = t2;
	}
};
class init_VarDef :public VarDef_class {
public:
	Id e1;
	AddExps e2;
	InitVal e3;
	init_VarDef(Id t1, AddExps t2, InitVal t3) {
		e1 = t1;
		e2 = t2;
		e3 = t3;
	}
};

class one_InitVal :public InitVal_class {
public:
	AddExp e1;
	one_InitVal(AddExp t1) {
		e1 = t1;
	}
};

class more_InitVal :public InitVal_class {
public:
	InitVals e1;
	more_InitVal(InitVals t1) {
		e1 = t1;
	}
};
class void_Func :public FuncDef_class {
public:
	Id e1;
	FuncFParams e2;
	Blocks e3;
	void_Func(Id t1, FuncFParams t2, Blocks t3) {
		e1 = t1;
		e2 = t2;
		e3 = t3;
	}
};

class int_Func :public FuncDef_class {
public:
	Id e1;
	FuncFParams e2;
	Blocks e3;
	int_Func(Id t1, FuncFParams t2, Blocks t3) {
		e1 = t1;
		e2 = t2;
		e3 = t3;
	}
};

class int_Param :public FuncFParam_class {
public:
	Id e1;
	int_Param(Id t1) {
		e1 = t1;
	}
};

class array_Param :public FuncFParam_class {
public:
	Id e1;
	AddExps e2;
	array_Param(Id t1, AddExps t2) {
		e1 = t1;
		e2 = t2;
	}
};

class decl_block :public Block_class {
public:
	Decl e1;
	decl_block(Decl t1) {
		e1 = t1;
	}
};

class stmt_block :public Block_class {
public:
	Stmt e1;
	stmt_block(Stmt t1) {
		e1 = t1;
	}
};

class assign_Stmt :public Stmt_class {
public:
	Id e1;
	AddExps e2;
	AddExp e3;
	assign_Stmt(Id t1, AddExps t2, AddExp t3) {
		e1 = t1;
		e2 = t2;
		e3 = t3;
	}
};

class empty_Stmt :public Stmt_class { virtual int tmp() { return 0; } };

class exp_Stmt :public Stmt_class {
public:
	AddExp e1;
	exp_Stmt(AddExp t1) {
		e1 = t1;
	}
};

class block_Stmt :public Stmt_class {
public:
	Blocks e1;
	block_Stmt(Blocks t1) {
		e1 = t1;
	}
};

class else_Stmt :public Stmt_class {
public:
	LOrExp e1;
	Stmt e2;
	Stmt e3;
	else_Stmt(LOrExp t1, Stmt t2, Stmt t3) {
		e1 = t1;
		e2 = t2;
		e3 = t3;
	}
};

class if_Stmt :public Stmt_class {
public:
	LOrExp e1;
	Stmt e2;
	if_Stmt(LOrExp t1, Stmt t2) {
		e1 = t1;
		e2 = t2;
	}
};

class while_Stmt :public Stmt_class {
public:
	LOrExp e1;
	Stmt e2;
	while_Stmt(LOrExp t1, Stmt t2) {
		e1 = t1;
		e2 = t2;
	}
};

class break_Stmt :public Stmt_class { virtual int tmp() { return 0; } };

class continue_Stmt :public Stmt_class { virtual int tmp() { return 0; } };

class return_exp_Stmt :public Stmt_class {
public:
	AddExp e1;
	return_exp_Stmt(AddExp t1) {
		e1=t1;
	}
};

class return_Stmt :public Stmt_class { virtual int tmp() { return 0; } };



class primary_Exp :public PrimaryExp_class {
public:
	AddExp e1;
	primary_Exp(AddExp t1) {
		e1 = t1;
	}
};

class lval :public PrimaryExp_class {
public:
	Id e1;
	AddExps e2;
	lval(Id t1, AddExps t2) {
		e1 = t1;
		e2 = t2;
	}
};

class number :public PrimaryExp_class {
public:
	char* e1;
	number(char* t1) {
		e1 = t1;
	}
};

class pri_Una :public UnaryExp_class {
public:
	PrimaryExp e1;
	pri_Una(PrimaryExp t1) {
		e1 = t1;
	}
};

class func_Una :public UnaryExp_class {
public:
	Id e1;
	FuncRParams e2;
	func_Una(Id t1, FuncRParams t2) {
		e1 = t1;
		e2 = t2;
	}
};
class op_Una :public UnaryExp_class {
public:
	UnaryOp e1;
	UnaryExp e2;
	op_Una(UnaryOp t1, UnaryExp t2) {
		e1 = t1;
		e2 = t2;
	}
};

class una_Op :public UnaryOp_class {
public:
	char* e1;
	una_Op(char * t1) {
		e1 = t1;
	}
};

class una_Mul :public MulExp_class {
public:
	UnaryExp e1;
	una_Mul(UnaryExp t1) {
		e1 = t1;
	}
};

class times_Mul :public MulExp_class {
public:
	MulExp e1;
	UnaryExp e2;
	times_Mul(MulExp t1, UnaryExp t2) {
		e1 = t1;
		e2 = t2;
	}
};

class over_Mul :public MulExp_class {
public:
	MulExp e1;
	UnaryExp e2;
	over_Mul(MulExp t1, UnaryExp t2) {
		e1 = t1;
		e2 = t2;
	}
};

class mod_Mul :public MulExp_class {
public:
	MulExp e1;
	UnaryExp e2;
	mod_Mul(MulExp t1, UnaryExp t2) {
		e1 = t1;
		e2 = t2;
	}
};

class mul_AddExp :public AddExp_class {
public:
	MulExp  e1;
	mul_AddExp(MulExp t1) {
		e1 = t1;
	}
};

class plus_AddExp :public AddExp_class {
public:
	AddExp e1;
	MulExp e2;
	plus_AddExp(AddExp t1, MulExp t2) {
		e1 = t1;
		e2 = t2;
	}
};

class minus_AddExp :public AddExp_class {
public:
	AddExp e1;
	MulExp e2;
	minus_AddExp(AddExp t1, MulExp t2) {
		e1 = t1;
		e2 = t2;
	}
};

class add_RelExp :public RelExp_class {
public:
	AddExp  e1;
	add_RelExp(AddExp t1) {
		e1 = t1;
	}
};

class lt_RelExp :public RelExp_class {
public:
	RelExp e1;
	AddExp e2;
	lt_RelExp(RelExp t1, AddExp t2) {
		e1 = t1;
		e2 = t2;
	}
};

class gt_RelExp :public RelExp_class {
public:
	RelExp e1;
	AddExp e2;
	gt_RelExp(RelExp t1, AddExp t2) {
		e1 = t1;
		e2 = t2;
	}
};

class le_RelExp :public RelExp_class {
public:
	RelExp e1;
	AddExp e2;
	le_RelExp(RelExp t1, AddExp t2) {
		e1 = t1;
		e2 = t2;
	}
};

class ge_RelExp :public RelExp_class {
public:
	RelExp e1;
	AddExp e2;
	ge_RelExp(RelExp t1, AddExp t2) {
		e1 = t1;
		e2 = t2;
	}
};

class rel_EqExp :public EqExp_class {
public:
	RelExp e1;
	rel_EqExp(RelExp t1) {
		e1 = t1;
	}
};

class eq_EqExp :public EqExp_class {
public:
	EqExp e1;
	RelExp e2;
	eq_EqExp(EqExp t1, RelExp t2) {
		e1 = t1;
		e2 = t2;
	}
};

class nq_EqExp :public EqExp_class {
public:
	EqExp e1;
	RelExp e2;
	nq_EqExp(EqExp t1, RelExp t2) {
		e1 = t1;
		e2 = t2;
	}
};

class eq_LAndExp :public LAndExp_class {
public:
	EqExp e1;
	eq_LAndExp(EqExp t1) {
		e1 = t1;
	}
};

class and_LAndExp :public LAndExp_class {
public:
	LAndExp e1;
	EqExp e2;
	and_LAndExp(LAndExp t1, EqExp t2) {
		e1 = t1;
		e2 = t2;
	}
};

class and_LOrExp :public LOrExp_class {
public:
	LAndExp e1;
	and_LOrExp(LAndExp t1) {
		e1 = t1;
	}
};

class or_LOrExp :public LOrExp_class {
public:
	LOrExp e1;
	LAndExp e2;
	or_LOrExp(LOrExp t1, LAndExp t2) {
		e1 = t1;
		e2 = t2;
	}
};

class id : public Id_class {
public:
	char* e1;
	id(char* t1) {
		e1 = t1;
	}
};
#endif // !
