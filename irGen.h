#ifndef IRGEN_H
#define IRGEN_H
#include "ir.h"
#include "parse_tree.h"
#include <map>
#include <string>
#include <iostream>

class stmtChunk {
public:
	std::list<irStmt*>* stmts;
	std::list<JumpStmt*>* nextjumps;

	stmtChunk(std::list<irStmt*>* stmts, std::list<JumpStmt*>* nextjumps) {
		this->nextjumps = nextjumps;
		this->stmts = stmts;
	}
};

class condChunk {
public:
	std::list<irStmt*>* stmts;
	std::list<JumpStmt*>* truejumps;
	std::list<JumpStmt*>* falsejumps;

	condChunk(std::list<irStmt*>* stmts, std::list<JumpStmt*>* truejumps, std::list<JumpStmt*>* falsejumps) {
		this->stmts = stmts;
		this->truejumps = truejumps;
		this->falsejumps = falsejumps;
	}
};

class RvalChunk {
public:
	Rval* rv;
	std::list<JumpStmt*>* nextjumps;

	RvalChunk(Rval* rv, std::list<JumpStmt*>* stmts) {
		this->rv = rv;
		this->nextjumps = stmts;
	}
};

class breakStmt :public irStmt {
	std::string render(int a) {
		return "";
	}
};

class continueStmt : public irStmt {
	std::string render(int a) {
		return "";
	}
};

class IrGen {
private: 
	std::list<Var*>* datas = new std::list<Var*>();
	std::list<Meth*>* meths = new std::list<Meth*>();

	std::map<std::string, Var*>* dataMap = new std::map<std::string, Var*>();
	std::map<std::string, arrayVar*>* arrayMap = new std::map<std::string, arrayVar*>();


	std::map<std::string, type>* methMap = new std::map<std::string, type>();

	std::list<Var>* irLocals;
	int tmpCounters;
	int labelCounters;
	std::string curr_func_name;
	bool curr_func_bl;

	IntLitRval* one = new IntLitRval(1);
	IntLitRval* zero = new IntLitRval(0);

public :
	Prog* run(CompUnits prog) {
		curr_func_name = "global";
		tmpCounters = labelCounters = 0;
		std::list<irStmt*>* declBlock=new std::list<irStmt*>();
		std::list<Meth*>* methBlock=new std::list<Meth*>();
		methMap->insert(std::pair<std::string, type>("getint", _int));
		methMap->insert(std::pair<std::string, type>("getch", _int));
		methMap->insert(std::pair<std::string, type>("getarray", _int));
		methMap->insert(std::pair<std::string, type>("rand", _int));
		methMap->insert(std::pair<std::string, type>("putint", _void));
		methMap->insert(std::pair<std::string, type>("putch", _void));
		methMap->insert(std::pair<std::string, type>("putarray", _void));
		methMap->insert(std::pair<std::string, type>("putf", _void));
		methMap->insert(std::pair<std::string, type>("starttime", _void));
		methMap->insert(std::pair<std::string, type>("stoptime", _void));
		int length = prog->len();
		for (int i = 0; i < length; i++) {
			int len;
			CompUnit unit = (prog->nth_length(i, len));
			decl_CompUnit* u1 = dynamic_cast<decl_CompUnit*>((unit));
			if (u1 != nullptr) {
				doDecl(u1->e1, declBlock,true);
			}
		}
		for (int i = 0; i < prog->len(); i++) {
			int len;
			CompUnit unit = (prog->nth_length(i, len));
			funcDef_CompUnit* u2 = dynamic_cast<funcDef_CompUnit*>((unit));
			if (u2 != nullptr) {
				doMethType(u2->e1);
			}
		}
		for (int i = 0; i < prog->len(); i++) {
			int len;
			CompUnit unit = (prog->nth_length(i, len));
			funcDef_CompUnit* u2 = dynamic_cast<funcDef_CompUnit*>((unit));
			if (u2 != nullptr) {
				curr_func_bl = false;
				Meth* func = doFunc(u2->e1);
				if (func->name == "main")
					methBlock->push_front(func);
				else
					methBlock->push_back(func);
			}
		}
		return new Prog(declBlock, methBlock);
	}

private:
	Meth* doFunc(FuncDef e1) {
		void_Func* v = (dynamic_cast<void_Func*>(e1));
		if (v != nullptr) {
			id* _id = dynamic_cast<id*>(v->e1);
			this->curr_func_name = _id->e1;
			FuncFParams param = v->e2;
			std::list<irDecl*>* args = new std::list<irDecl*>();
			for (int i = 0; i < param->len(); i++) {
				int len;
				FuncFParam p = param->nth_length(i, len);
				int_Param* _int = dynamic_cast<int_Param*>(p);
				if (_int != nullptr) {
					id* _id = dynamic_cast<id*>(_int->e1);
					Var* newVar = new Var((_id->e1));
					args->push_back(new irVarDecl(newVar));
					this->dataMap->insert(std::pair<std::string, Var*>(this->curr_func_name+_id->e1, newVar));
				}
				array_Param* _arr = dynamic_cast<array_Param*>(p);
				if (_arr != nullptr) {
					int len;
					std::list<int>* rval_list=new std::list<int>();
					rval_list->push_back(10);
					for (int i = 0; i < _arr->e2->len(); i++) {
						AddExp exp = _arr->e2->nth_length(i, len);
						Rval* val = doAddExp(exp, nullptr);
						IntLitRval* intval = dynamic_cast<IntLitRval*>(val);
						if (intval != nullptr) {
							rval_list->push_back(intval->i);
						}
						else {
							std::cout << "error error";
						}
					}
					id* _id = dynamic_cast<id*>(_arr->e1);
					arrayVar* arr = new arrayVar(_id->e1,rval_list);
					arrayMap->insert(std::pair<std::string, arrayVar*>(this->curr_func_name+_id->e1, arr));
					args->push_back(new irArrayDecl(arr));
				}
			}
			Blocks b = v->e3;
			stmtChunk* res = doBlocks(b);
			if (dynamic_cast<ir_return*>(res->stmts->back()) == nullptr) {
				LabelStmt* label = new LabelStmt("l" + std::to_string(labelCounters++));
				res->stmts->push_back(label);
				addJump(res->nextjumps, label);
				res->stmts->push_back(new ir_return());
			}
			Meth* newmeth=new Meth(_void, (_id->e1), args, res->stmts,this->curr_func_bl);
			//this->methMap->insert(std::pair<std::string,Meth*>((_id->e1),newmeth));
			return newmeth;
		}
		int_Func* f = dynamic_cast<int_Func*>(e1);
		if (f != nullptr) {
			id* _id = dynamic_cast<id*>(f->e1);
			this->curr_func_name = _id->e1;
			FuncFParams param = f->e2;
			std::list<irDecl*>* args = new std::list<irDecl*>();
			for (int i = 0; i < param->len(); i++) {
				int len;
				FuncFParam p = param->nth_length(i, len);
				int_Param* _int = dynamic_cast<int_Param*>(p);
				if (_int != nullptr) {
					id* _id = dynamic_cast<id*>(_int->e1);
					Var* arg = new Var((_id->e1));
					dataMap->insert(std::pair<std::string, Var*>(this->curr_func_name + _id->e1, arg));
					args->push_back(new irVarDecl(arg));
				}
				array_Param* _arr = dynamic_cast<array_Param*>(p);
				if (_arr != nullptr) {
					int len;
					std::list<int>* rval_list = new std::list<int>();
					rval_list->push_back(10);
					for (int i = 0; i < _arr->e2->len(); i++) {
						AddExp exp = _arr->e2->nth_length(i, len);
						Rval* val = doAddExp(exp, nullptr);
						IntLitRval* intval = dynamic_cast<IntLitRval*>(val);
						if (intval != nullptr) {
							rval_list->push_back(intval->i);
						}
						else {
							std::cout << "error error";
						}
					}
					id* _id = dynamic_cast<id*>(_arr->e1);
					arrayVar* arr = new arrayVar(_id->e1,rval_list);
					arrayMap->insert(std::pair<std::string, arrayVar*>(this->curr_func_name + _id->e1, arr));
					args->push_back(new irArrayDecl(arr));
				}
			}
			Blocks b = f->e3;
			stmtChunk* res = doBlocks(b);
			Meth* newmeth = new Meth(_int, (_id->e1), args, res->stmts, this->curr_func_bl);
			//this->methMap->insert(std::pair<std::string, Meth*>((_id->e1), newmeth));
			return newmeth;
		}
	}

	void doMethType(FuncDef func) {
		void_Func* v = (dynamic_cast<void_Func*>(func));
		if (v != nullptr) {
			id* _id = dynamic_cast<id*>(v->e1);
			this->methMap->insert(std::pair<std::string, type>((_id->e1), _void));
		}

		int_Func* f = dynamic_cast<int_Func*>(func);
		if (f != nullptr) {
			id* _id = dynamic_cast<id*>(f->e1);
			this->methMap->insert(std::pair<std::string, type>((_id->e1), _int));
		}

	}

	void doDecl(Decl u1, std::list<irStmt*>* declBlock,bool global=false) {
		constVarDecl* c = dynamic_cast<constVarDecl*>(u1);
		if (c != nullptr) {
			for (int j = 0; j < c->e1->len(); j++) {
				int len;
				VarDef def = c->e1->nth_length(j, len);
				uninit_VarDef* _uninit = dynamic_cast<uninit_VarDef*>(def);
				if (_uninit != nullptr) {
					id* _id = dynamic_cast<id*>(_uninit->e1);
					if (_uninit->e2->len() == 0) {
						Var* newVar = new Var((_id->e1), global);
						irStmt* pt = new irVarDecl(newVar);
						this->dataMap->insert(std::pair<std::string, Var*>(this->curr_func_name + _id->e1, newVar));
						declBlock->push_back(pt);
					}
					else {
						std::list<int>* dimension = new std::list<int>();
						for (int k = 0; k < _uninit->e2->len(); k++) {
							AddExp exp = _uninit->e2->nth_length(k, len);
							Rval* res = doAddExp(exp, declBlock);
							IntLitRval* val = dynamic_cast<IntLitRval*>(res);
							dimension->push_back(val->i);
						}
						arrayVar* newArr = new arrayVar(_id->e1, dimension, global);

						this->arrayMap->insert(std::pair<std::string, arrayVar*>(this->curr_func_name + _id->e1, newArr));
						irStmt* pt = new irArrayDecl(newArr);
						declBlock->push_back(pt);
					}
				}
				init_VarDef* _init = dynamic_cast<init_VarDef*>(def);
				//std::cout << "lvar name:" << _init->e1 << std::endl;
				if (_init != nullptr) {
					id* _id = dynamic_cast<id*>(_init->e1);
					if (_init->e2->len() == 0) {
						one_InitVal* val = dynamic_cast<one_InitVal*>(_init->e3);
						if (val != nullptr) {
							Var* v = new Var((_id->e1), global);
							v->if_const = true;
							this->dataMap->insert(std::pair<std::string, Var*>(this->curr_func_name + _id->e1, v));

							Rval* res = doAddExp(val->e1, declBlock);
							IntLitRval* _int = dynamic_cast<IntLitRval*>(res);
							if (_int != nullptr) {
								v->instanceValue = _int->i;
							}
							irStmt* pt1 = new irVarDecl(v);
							declBlock->push_back(pt1);
						}
					}
					else {
						std::list<int>* dimension = new std::list<int>();
						for (int k = 0; k < _init->e2->len(); k++) {
							AddExp exp = _init->e2->nth_length(k, len);
							Rval* res = doAddExp(exp, declBlock);
							IntLitRval* val = dynamic_cast<IntLitRval*>(res);
							if (val != nullptr)
								dimension->push_back(val->i);

						}
						arrayVar* newArr = new arrayVar(_id->e1, dimension, global);
						this->arrayMap->insert(std::pair<std::string, arrayVar*>(this->curr_func_name + _id->e1, newArr));
						irArrayDecl* pt = new irArrayDecl(newArr);
						declBlock->push_back(pt);

						more_InitVal* val = dynamic_cast<more_InitVal*>(_init->e3);
						if (val != nullptr) {
							std::list<Rval*>* init_data = new std::list<Rval*>();
							for (int k = 0; k < val->e1->len(); k++) {
								InitVal exp = val->e1->nth_length(k, len);
								one_InitVal* one = dynamic_cast<one_InitVal*>(exp);
								if (one == nullptr) {
									std::cout << "error at initval" << std::endl;
									continue;
								}
								Rval* res = doAddExp(one->e1, declBlock);
								init_data->push_back(res);
							}
							declBlock->push_back(new arrayInitStmt(pt, init_data));
						}
					}
				}
			}
		}
		

		varDecl* v = dynamic_cast<varDecl*>(u1);
		if (v != nullptr) {
			for (int j = 0; j < v->e1->len(); j++) {
				int len;
				VarDef def = v->e1->nth_length(j, len);
				uninit_VarDef* _uninit = dynamic_cast<uninit_VarDef*>(def);
				if (_uninit != nullptr) {
					id* _id = dynamic_cast<id*>(_uninit->e1);
					if (_uninit->e2->len() == 0) {
						Var* newVar = new Var((_id->e1), global);
						irStmt* pt = new irVarDecl(newVar);
						this->dataMap->insert(std::pair<std::string, Var*>(this->curr_func_name + _id->e1, newVar));
						declBlock->push_back(pt);
					}
					else {
						std::list<int>* dimension = new std::list<int>();
						for (int k = 0; k < _uninit->e2->len(); k++) {
							AddExp exp = _uninit->e2->nth_length(k, len);
							Rval* res = doAddExp(exp, declBlock);
							IntLitRval* val = dynamic_cast<IntLitRval*>(res);
							dimension->push_back(val->i);
						}
						arrayVar* newArr = new arrayVar(_id->e1, dimension, global);

						this->arrayMap->insert(std::pair<std::string, arrayVar*>(this->curr_func_name + _id->e1, newArr));
						irStmt* pt = new irArrayDecl(newArr);
						declBlock->push_back(pt);
					}
				}
				init_VarDef* _init = dynamic_cast<init_VarDef*>(def);
				//std::cout << "lvar name:" << _init->e1 << std::endl;
				if (_init != nullptr) {
					id* _id = dynamic_cast<id*>(_init->e1);
					if (_init->e2->len() == 0) {
						one_InitVal* val = dynamic_cast<one_InitVal*>(_init->e3);
						if (val != nullptr) {
							Rval* res = doAddExp(val->e1, declBlock);
							Var* v = new Var((_id->e1), global);
							this->dataMap->insert(std::pair<std::string, Var*>(this->curr_func_name + _id->e1, v));
							irStmt* pt1 = new irVarDecl(v);
							irStmt* pt2 = new numberAssignStmt(v, res);
							declBlock->push_back(pt1);
							declBlock->push_back(pt2);
						}
					}
					else {
						std::list<int>* dimension = new std::list<int>();
						for (int k = 0; k < _init->e2->len(); k++) {
							AddExp exp = _init->e2->nth_length(k, len);
							Rval* res = doAddExp(exp, declBlock);
							IntLitRval* val = dynamic_cast<IntLitRval*>(res);
							dimension->push_back(val->i);
						}
						arrayVar* newArr = new arrayVar(_id->e1, dimension, global);
						this->arrayMap->insert(std::pair<std::string, arrayVar*>(this->curr_func_name + _id->e1, newArr));
						irArrayDecl* pt = new irArrayDecl(newArr);
						declBlock->push_back(pt);

						more_InitVal* val = dynamic_cast<more_InitVal*>(_init->e3);
						if (val != nullptr) {
							this->curr_func_bl = true;
							std::list<Rval*>* init_data = new std::list<Rval*>();
							for (int k = 0; k < val->e1->len(); k++) {
								InitVal exp = val->e1->nth_length(k, len);
								one_InitVal* one = dynamic_cast<one_InitVal*>(exp);
								if (one == nullptr) {
									std::cout << "error at initval" << std::endl;
									continue;
								}
								Rval* res = doAddExp(one->e1, declBlock);
								init_data->push_back(res);
							}
							declBlock->push_back(new arrayInitStmt(pt, init_data));
						}
					}
				}
			}
		}
	}

	stmtChunk* doBlocks(Blocks blocks) {
		std::list<irStmt*>* irStmts = new std::list<irStmt*>();
		stmtChunk* lastChunk = nullptr;
		for (int i = 0; i < blocks->len(); i++) {
			LabelStmt* label;
			if (lastChunk != nullptr && lastChunk->nextjumps->size() > 0) {
				label = new LabelStmt("l" + std::to_string(labelCounters++));
				irStmts->push_back(label);
				addJump(lastChunk->nextjumps, label);
			}
			int len;
			Block b = blocks->nth_length(i, len);
			stmt_block* s = dynamic_cast<stmt_block*>(b);
			if (s != nullptr) {
				stmtChunk* chunk = doStmt(s->e1);
				//LabelStmt* test = dynamic_cast<LabelStmt*>(chunk->stmts->front());
				/*if (lastChunk != nullptr && lastChunk->nextjumps->size() > 0) {
					if (test != nullptr) {
						label = test;
					}
					else {
						label = new LabelStmt("l" + std::to_string(labelCounters++));
					}					
					irStmts->push_back(label);
					addJump(lastChunk->nextjumps, label);
				}*/
				addAll(irStmts, chunk->stmts);
				lastChunk = chunk;
			}
			decl_block* d = dynamic_cast<decl_block*>(b);
			if (d != nullptr) {
				/*if (lastChunk != nullptr && lastChunk->nextjumps->size() > 0) {
					label = new LabelStmt("l" + std::to_string(labelCounters++));
					addJump(lastChunk->nextjumps, label);
				}*/
				doDecl(d->e1, irStmts);
				lastChunk = nullptr;
			}
		}
		std::list<JumpStmt*>* nextjumps = new std::list<JumpStmt*>();
		if (lastChunk != nullptr)
			nextjumps = lastChunk->nextjumps;
		return new stmtChunk(irStmts, nextjumps);
	}

	/*stmtChunk* doStmtBlock(std::list<Stmt*>* stmts) {
		std::list<irStmt*>* irStmts = new std::list<irStmt*>();
		stmtChunk* lastChunk = nullptr;
		for (Stmt* s: *stmts) {
			stmtChunk* chunk = doStmt(s);//这个要pop的，兄弟
			if (lastChunk != nullptr && lastChunk->nextjumps->size() > 0) {
				LabelStmt* label = new LabelStmt("l" + std::to_string(labelCounters++));
				irStmts->push_back(label);
				addJump(lastChunk->nextjumps, label);
			}
			addAll(irStmts, chunk->stmts);
			lastChunk = chunk;
		}
		std::list<JumpStmt*>* nextjumps = new std::list<JumpStmt*>();
		if (lastChunk != nullptr)
			nextjumps = lastChunk->nextjumps;
		return new stmtChunk(irStmts, nextjumps);
	}*/

	void addAll(std::list<irStmt*>* a, std::list<irStmt*>* b) {
		for (irStmt* s : *b) {
			a->push_back(s);
		}
	}

	void addStmtToWhile(std::list<irStmt*>* a, std::list<irStmt*>* b,LabelStmt* toplabel, std::list<JumpStmt*>* breakTo) {
		for (irStmt* s: *b) {
			breakStmt* _break = dynamic_cast<breakStmt*>(s);
			if (_break != nullptr) {
				GotoStmt* go = new GotoStmt(nullptr);
				a->push_back(go);
				breakTo->push_back(go);
				continue;
			}
			continueStmt* _continue = dynamic_cast<continueStmt*>(s);
			if (_continue != nullptr) {
				GotoStmt* go = new GotoStmt(toplabel);
				a->push_back(go);
				continue;
			}
			a->push_back(s);
		}
	}

	void addAllJumps(std::list<JumpStmt*>* a, std::list<JumpStmt*>* b) {
		for (JumpStmt* j : *b) {
			a->push_back(j);
		}
	}

	void addJump(std::list<JumpStmt*>* a,LabelStmt* l) {
		for (JumpStmt* j : *a) {
			j->label = l;
		}
	}

	stmtChunk* doStmt(Stmt stmt) {
		std::list<irStmt*>* stmts = new std::list<irStmt*>();
		std::list<JumpStmt*>* nextjumps = new std::list<JumpStmt*>();
		assign_Stmt* s1 = dynamic_cast<assign_Stmt*>(stmt);
		if (s1 != nullptr) {
			id* _id = dynamic_cast<id*>(s1->e1);
			if (s1->e2->len() == 0) {
				Rval* v1 = doAddExp(s1->e3, stmts);

				std::map<std::string, Var*>::iterator iter;
				iter = this->dataMap->find(this->curr_func_name + _id->e1);
				if (iter != this->dataMap->end()) {
					stmts->push_back(new numberAssignStmt(iter->second, v1));
					return new stmtChunk(stmts, nextjumps);
				}
				std::string tmp = "global";
				iter = this->dataMap->find( tmp+ _id->e1);
				if (iter != this->dataMap->end()) {
					stmts->push_back(new numberAssignStmt(iter->second, v1));
					return new stmtChunk(stmts, nextjumps);
				}
			}
			else {
				std::list<Rval*>* _list = new std::list<Rval*>();
				for (int i = 0; i < s1->e2->len(); i++) {
					int len;
					Rval* v2 = doAddExp(s1->e2->nth_length(i, len), stmts);
					_list->push_back(v2);
				}
				Rval* v1 = doAddExp(s1->e3, stmts);
				std::map<std::string, arrayVar*>::iterator iter;
				iter = this->arrayMap->find(this->curr_func_name+_id->e1);
				if (iter != this->arrayMap->end()) {
					stmts->push_back(new arrayAssignStmt2(iter->second, _list, v1));
					return new stmtChunk(stmts, nextjumps);
				}
				std::string tmp = "global";
				iter = this->arrayMap->find(tmp+_id->e1);
				if (iter != this->arrayMap->end()) {
					stmts->push_back(new arrayAssignStmt2(iter->second, _list, v1));
					return new stmtChunk(stmts, nextjumps);
				}
				else {
					std::cout << "error";
				}
			}
		}
		exp_Stmt* s2 = dynamic_cast<exp_Stmt*>(stmt);
		if (s2 != nullptr) {
			doAddExp(s2->e1, stmts);
			return new stmtChunk(stmts, nextjumps);

		}
		else_Stmt* s3 = dynamic_cast<else_Stmt*>(stmt);
		if (s3 != nullptr) {
			condChunk* condChunk = doLorExp(s3->e1);
			stmtChunk* thenChunk = doStmt(s3->e2);
			stmtChunk* elseChunk = doStmt(s3->e3);
			addAll(stmts, condChunk->stmts);
			//stmts->push_back(new ir_return());
			if (condChunk->truejumps->size() > 0) {
				LabelStmt* truelabel = new LabelStmt("l" + std::to_string(labelCounters++));
				stmts->push_back(truelabel);
				addJump(condChunk->truejumps, truelabel);
			}

			addAll(stmts, thenChunk->stmts);
			addAllJumps(nextjumps, thenChunk->nextjumps);

			GotoStmt* go = new GotoStmt(nullptr);
			stmts->push_back(go);
			nextjumps->push_back(go);

			if (condChunk->falsejumps->size() > 0) {
				LabelStmt* falselabel = new LabelStmt("l" + std::to_string(labelCounters++));
				stmts->push_back(falselabel);
				addJump(condChunk->falsejumps, falselabel);
			}

			
			addAll(stmts, elseChunk->stmts);
			ir_return* r1 = dynamic_cast<ir_return*>(elseChunk->stmts->back());
			ir_return_rval* r2 = dynamic_cast<ir_return_rval*>(elseChunk->stmts->back());
			GotoStmt* r3 = dynamic_cast<GotoStmt*>(elseChunk->stmts->back());
			//if(r1==nullptr && r2==nullptr && r3==nullptr)
			addAllJumps(nextjumps, elseChunk->nextjumps);
			return new stmtChunk(stmts, nextjumps);
		}
		if_Stmt* s4 = dynamic_cast<if_Stmt*>(stmt);
		if (s4 != nullptr) {
			condChunk* condChunk = doLorExp(s4->e1);
			stmtChunk* thenChunk = doStmt(s4->e2);
			addAll(stmts, condChunk->stmts);
			if (condChunk->truejumps->size() > 0) {
				LabelStmt* truelabel = new LabelStmt("l" + std::to_string(labelCounters++));
				stmts->push_back(truelabel);
				addJump(condChunk->truejumps, truelabel);
			}

			addAll(stmts, thenChunk->stmts);
			addAllJumps(nextjumps, thenChunk->nextjumps);

			GotoStmt* go = new GotoStmt(nullptr);
			stmts->push_back(go);
			nextjumps->push_back(go);

			ir_return* r1 = dynamic_cast<ir_return*>(condChunk->stmts->back());
			ir_return_rval* r2 = dynamic_cast<ir_return_rval*>(condChunk->stmts->back());
			GotoStmt* r3 = dynamic_cast<GotoStmt*>(condChunk->stmts->back());
			//if (r1 == nullptr && r2 == nullptr && r3 == nullptr)
			addAllJumps(nextjumps, condChunk->falsejumps);

			return new stmtChunk(stmts, nextjumps);
		}
		while_Stmt* s5 = dynamic_cast<while_Stmt*>(stmt);
		if (s5 != nullptr) {
			condChunk* condChunk = doLorExp(s5->e1);
			stmtChunk* Chunk = doStmt(s5->e2);

			LabelStmt* toplabel = new LabelStmt("l" + std::to_string(labelCounters++));
			stmts->push_back(toplabel);
			addAll(stmts, condChunk->stmts);

			if (condChunk->truejumps->size() > 0) {
				LabelStmt* truelabel = new LabelStmt("l" + std::to_string(labelCounters++));
				stmts->push_back(truelabel);
				addJump(condChunk->truejumps, truelabel);
			}

			addStmtToWhile(stmts, Chunk->stmts,toplabel,nextjumps);


			LabelStmt* finallabel = new LabelStmt("l" + std::to_string(labelCounters++));
			addJump(Chunk->nextjumps, finallabel);

			stmts->push_back(finallabel);
			stmts->push_back(new GotoStmt(toplabel));

			addAllJumps(nextjumps, condChunk->falsejumps);
			//addAllJumps(nextjumps, Chunk->nextjumps);

			return new stmtChunk(stmts, nextjumps);
		}
		break_Stmt* s6 = dynamic_cast<break_Stmt*>(stmt);
		if (s6 != nullptr) {
			stmts->push_back(new breakStmt());
			return new stmtChunk(stmts, nextjumps);
		}
		continue_Stmt* s7 = dynamic_cast<continue_Stmt*>(stmt);
		if (s7 != nullptr) {
			stmts->push_back(new continueStmt());
			return new stmtChunk(stmts, nextjumps);
		}
		return_Stmt* s8 = dynamic_cast<return_Stmt*>(stmt);
		if (s8 != nullptr) {
			stmts->push_back(new ir_return());
			return new stmtChunk(stmts, nextjumps);			
		}
		return_exp_Stmt* s9 = dynamic_cast<return_exp_Stmt*>(stmt);
		if (s9 != nullptr) {
			Rval* res = doAddExp(s9->e1,stmts);
			stmts->push_back(new ir_return_rval(res));
			return new stmtChunk(stmts, nextjumps);
		}
		block_Stmt* s10 = dynamic_cast<block_Stmt*>(stmt);
		if (s10 != nullptr) {
			return doBlocks(s10->e1);
		}
	}

	condChunk* doLorExp(LOrExp cond) {
		std::list<irStmt*>* stmts = new std::list<irStmt*>();
		std::list<JumpStmt*>* truejumps = new std::list<JumpStmt*>();
		std::list<JumpStmt*>* falsejumps = new std::list<JumpStmt*>();
		and_LOrExp* c1 = dynamic_cast<and_LOrExp*>(cond);
		if (c1 != nullptr) {
			return doLandExp(c1->e1);
		}
		or_LOrExp* c2 = dynamic_cast<or_LOrExp*>(cond);
		if (c2 != nullptr) {
			condChunk* left = doLorExp(c2->e1);
			condChunk* right = doLandExp(c2->e2);

			LabelStmt* label = new LabelStmt("l" + std::to_string(labelCounters++));
			addJump(left->falsejumps, label);
			addAll(stmts, left->stmts);

			stmts->push_back(label);
			addAll(stmts, right->stmts);

			addAllJumps(truejumps, left->truejumps);
			addAllJumps(truejumps, right->truejumps);
			addAllJumps(falsejumps, right->falsejumps);

			return new condChunk(stmts, truejumps, falsejumps);
		}
	}

	condChunk* doLandExp(LAndExp cond) {
		std::list<irStmt*>* stmts = new std::list<irStmt*>();
		std::list<JumpStmt*>* truejumps = new std::list<JumpStmt*>();
		std::list<JumpStmt*>* falsejumps = new std::list<JumpStmt*>();
		eq_LAndExp* c1 = dynamic_cast<eq_LAndExp*>(cond);
		if (c1 != nullptr) {
			RvalChunk* chunk = doEqExp(c1->e1, stmts);
			LabelStmt* label = new LabelStmt("l" + std::to_string(labelCounters++));
			stmts->push_back(label);
			addJump(chunk->nextjumps, label);

			IntLitRval* a1 = dynamic_cast<IntLitRval*>(chunk->rv);
			if (a1 != nullptr) {
				if (a1->i != 0) {
					GotoStmt* go = new GotoStmt(nullptr);
					truejumps->push_back(go);
					stmts->push_back(go);
				}
				else {
					GotoStmt* go = new GotoStmt(nullptr);
					falsejumps->push_back(go);
					stmts->push_back(go);
				}
				return new condChunk(stmts, truejumps, falsejumps);
			}
			CmpStmt* cmp = new CmpStmt(_EQ, chunk->rv, one, nullptr);
			truejumps->push_back(cmp);
			stmts->push_back(cmp);

			GotoStmt* go = new GotoStmt(nullptr);
			falsejumps->push_back(go);
			stmts->push_back(go);

			return new condChunk(stmts, truejumps, falsejumps);
		}
		and_LAndExp* c2 = dynamic_cast<and_LAndExp*>(cond);
		if (c2 != nullptr) {
			condChunk* left = doLandExp(c2->e1);
			LabelStmt* label = new LabelStmt("l" + std::to_string(labelCounters++));
			addJump(left->truejumps, label);
			addAll(stmts, left->stmts);
			stmts->push_back(label);
			
			RvalChunk* right = doEqExp(c2->e2, stmts);
			LabelStmt* label2 = new LabelStmt("l" + std::to_string(labelCounters++));
			stmts->push_back(label2);
			addJump(right->nextjumps, label2);

			CmpStmt* cmp = new CmpStmt(_EQ, right->rv, one, nullptr);
			stmts->push_back(cmp);

			GotoStmt* go = new GotoStmt(nullptr);
			stmts->push_back(go);

			truejumps->push_back(cmp);
			falsejumps->push_back(go);
			addAllJumps(falsejumps, left->falsejumps);

			return new condChunk(stmts, truejumps, falsejumps);
		}
	}

	RvalChunk* doEqExp(EqExp cond, std::list<irStmt*>* stmts) {
		//std::list<irStmt*>* stmts;
		std::list<JumpStmt*>* nextjumps=new std::list<JumpStmt*>();
		rel_EqExp* c1 = dynamic_cast<rel_EqExp*>(cond);
		if (c1 != nullptr) {
			return doRelExp(c1->e1,stmts);
		}
		eq_EqExp* c2 = dynamic_cast<eq_EqExp*>(cond);
		nq_EqExp* c3 = dynamic_cast<nq_EqExp*>(cond);
		if (c2 != nullptr || c3 != nullptr) {
			condOp op;
			RvalChunk* left;
			RvalChunk* right;
			if (c2 != nullptr) {
				op = _EQ;
				left = doEqExp(c2->e1, stmts);
				right = doRelExp(c2->e2, stmts);
			}
			if (c3 != nullptr) {
				op = _NE;
				left = doEqExp(c3->e1, stmts);
				right = doRelExp(c3->e2, stmts);
			}

			IntLitRval* t1 = dynamic_cast<IntLitRval*>(left->rv);
			IntLitRval* t2 = dynamic_cast<IntLitRval*>(right->rv);
			if (t1 != nullptr && t2 != nullptr) {
				Var* t = new Var("t" + std::to_string(getTmpIndex()));
				stmts->push_back(new irVarDecl(t));
				if (op == _EQ) {
					if(t1->i==t2->i)
						stmts->push_back(new numberAssignStmt(t, one));
					else
						stmts->push_back(new numberAssignStmt(t, zero));
				}else if (op == _NE) {
					if (t1->i != t2->i)
						stmts->push_back(new numberAssignStmt(t, one));
					else
						stmts->push_back(new numberAssignStmt(t, zero));
				}
				GotoStmt* go = new GotoStmt(nullptr);
				stmts->push_back(go);
				nextjumps->push_back(go);
				return new RvalChunk(new VarRval(t), nextjumps);
			}

			LabelStmt* label = new LabelStmt("l" + std::to_string(labelCounters++));
			stmts->push_back(label);
			addJump(left->nextjumps, label);
			addJump(right->nextjumps, label);

			Var* t = new Var("t" + std::to_string( getTmpIndex()));
			stmts->push_back(new irVarDecl(t));
			stmts->push_back(new numberAssignStmt(t, one));

			CmpStmt* cmp = new CmpStmt(op, left->rv, right->rv, nullptr);
			stmts->push_back(cmp);
			nextjumps->push_back(cmp);

			stmts->push_back(new numberAssignStmt(t, zero));
			GotoStmt* go = new GotoStmt(nullptr);
			stmts->push_back(go);
			nextjumps->push_back(go);

			return new RvalChunk(new VarRval(t), nextjumps);
		}
	}

	RvalChunk* doRelExp(RelExp cond, std::list<irStmt*>* stmts) {
		std::list<JumpStmt*>* nextjumps = new std::list<JumpStmt*>();
		add_RelExp* c1 = dynamic_cast<add_RelExp*>(cond);
		if (c1 != nullptr) {
			Rval* res = doAddExp(c1->e1,stmts);
			return new RvalChunk(res, nextjumps);
		}
		lt_RelExp* c2 = dynamic_cast<lt_RelExp*>(cond);
		gt_RelExp* c3 = dynamic_cast<gt_RelExp*>(cond);
		le_RelExp* c4 = dynamic_cast<le_RelExp*>(cond);
		ge_RelExp* c5 = dynamic_cast<ge_RelExp*>(cond);
		if (c2 != nullptr || c3 != nullptr || c4 != nullptr || c5 != nullptr) {
			condOp op;
			RvalChunk* left;
			Rval* right;
			if (c2 != nullptr) {
				op = _LT;
				left = doRelExp(c2->e1, stmts);
				right = doAddExp(c2->e2, stmts);
			}
			if (c3 != nullptr) {
				op = _GT;
				left = doRelExp(c3->e1, stmts);
				right = doAddExp(c3->e2, stmts);
			}
			if (c4 != nullptr) {
				op = _LE;
				left = doRelExp(c4->e1, stmts);
				right = doAddExp(c4->e2, stmts);
			}
			if (c5 != nullptr) {
				op = _GE;
				left = doRelExp(c5->e1, stmts);
				right = doAddExp(c5->e2, stmts);
			}

			IntLitRval* t1 = dynamic_cast<IntLitRval*>(left->rv);
			IntLitRval* t2 = dynamic_cast<IntLitRval*>(right);
			if (t1 != nullptr && t2 != nullptr) {
				Var* t = new Var("t" + std::to_string(getTmpIndex()));
				stmts->push_back(new irVarDecl(t));
				switch (op)
				{
				case _LT:
					if(t1->i<t2->i)
						stmts->push_back(new numberAssignStmt(t, one));
					else
						stmts->push_back(new numberAssignStmt(t, zero));

					break;
				case _GT:
					if (t1->i > t2->i)
						stmts->push_back(new numberAssignStmt(t, one));
					else
						stmts->push_back(new numberAssignStmt(t, zero));
					break;
				case _LE:
					if (t1->i <= t2->i)
						stmts->push_back(new numberAssignStmt(t, one));
					else
						stmts->push_back(new numberAssignStmt(t, zero));
					break;
				case _GE:
					if (t1->i >= t2->i)
						stmts->push_back(new numberAssignStmt(t, one));
					else
						stmts->push_back(new numberAssignStmt(t, zero));
					break;
				default:
					break;
				}
				GotoStmt* go = new GotoStmt(nullptr);
				stmts->push_back(go);
				nextjumps->push_back(go);
				return new RvalChunk(new VarRval(t), nextjumps);
			}

			LabelStmt* label = new LabelStmt("l" + std::to_string(labelCounters++));
			stmts->push_back(label);
			addJump(left->nextjumps, label);

			Var* t = new Var("t" + std::to_string( getTmpIndex()));
			stmts->push_back(new irVarDecl(t));
			stmts->push_back(new numberAssignStmt(t, one));

			CmpStmt* cmp = new CmpStmt(op, left->rv, right, nullptr);
			stmts->push_back(cmp);
			nextjumps->push_back(cmp);

			stmts->push_back(new numberAssignStmt(t, zero));
			GotoStmt* go = new GotoStmt(nullptr);
			stmts->push_back(go);
			nextjumps->push_back(go);

			return new RvalChunk(new VarRval(t), nextjumps);
		}
	}

	Rval* doAddExp(AddExp exp, std::list<irStmt*>* stmt_list) {
		mul_AddExp* a1 = dynamic_cast<mul_AddExp*>(exp);
		if (a1 != nullptr) {
			Rval* v1=doMulExp(a1->e1,stmt_list);
			return v1;
		}
		plus_AddExp* a2 = dynamic_cast<plus_AddExp*>(exp);
		if (a2 != nullptr) {
			Rval* v1=doAddExp(a2->e1, stmt_list);
			Rval* v2=doMulExp(a2->e2, stmt_list);
			Var* v3 = new Var("t"+(std::to_string( getTmpIndex())));
			irStmt* pt1 = new irVarDecl(v3);
			irStmt* pt2;
			IntLitRval* _v1 = dynamic_cast<IntLitRval*>(v1);
			IntLitRval* _v2 = dynamic_cast<IntLitRval*>(v2);
			if (_v1 != nullptr&& _v2 != nullptr)
				return new IntLitRval(_v1->i + _v2->i);
				//pt2 = new numberAssignStmt(v3, new IntLitRval(_v1->i + _v2->i));
			else
				pt2 = new binaryStmt(v1, v2, v3, _PLUS);
			stmt_list->push_back(pt1);
			stmt_list->push_back(pt2);

			return (new VarRval(v3));
		}
		minus_AddExp* a3 = dynamic_cast<minus_AddExp*>(exp);
		if (a3 != nullptr) {
			Rval* v1 = doAddExp(a3->e1, stmt_list);
			Rval* v2 = doMulExp(a3->e2, stmt_list);
			Var* v3 = new Var("t" + (std::to_string(getTmpIndex())));
			irStmt* pt1 = new irVarDecl(v3);
			irStmt* pt2;
			IntLitRval* _v1 = dynamic_cast<IntLitRval*>(v1);
			IntLitRval* _v2 = dynamic_cast<IntLitRval*>(v2);
			if (_v1 != nullptr&& _v2 != nullptr)
				return new IntLitRval(_v1->i - _v2->i);
				//pt2 = new numberAssignStmt(v3, new IntLitRval(_v1->i - _v2->i));
			else
				pt2 = new binaryStmt(v1, v2, v3, _MINUS);
			stmt_list->push_back(pt1);
			stmt_list->push_back(pt2);

			return (new VarRval(v3));
		}
	}

	Rval* doMulExp(MulExp exp, std::list<irStmt*>* stmt_list) {
		una_Mul* a1 = dynamic_cast<una_Mul*>(exp);
		if (a1 != nullptr) {
			Rval* v1 = doUnaExp(a1->e1, stmt_list);
			return v1;
		}
		times_Mul* a2 = dynamic_cast<times_Mul*>(exp);
		if (a2 != nullptr) {
			Rval* v1 = doUnaExp(a2->e2, stmt_list);
			Rval* v2 = doMulExp(a2->e1, stmt_list);
			Var* v3 = new Var("t" + (std::to_string(getTmpIndex())));
			irStmt* pt1 = new irVarDecl(v3);
			irStmt* pt2;
			IntLitRval* _v1 = dynamic_cast<IntLitRval*>(v1);
			IntLitRval* _v2 = dynamic_cast<IntLitRval*>(v2);
			if (_v1 != nullptr&& _v2 != nullptr)
				return new IntLitRval(_v1->i * _v2->i);
				//pt2 = new numberAssignStmt(v3, new IntLitRval(_v1->i * _v2->i));
			else
				pt2 = new binaryStmt(v1, v2, v3, _MUL);
			stmt_list->push_back(pt1);
			stmt_list->push_back(pt2);

			return (new VarRval(v3));
		}
		over_Mul* a3 = dynamic_cast<over_Mul*>(exp);
		if (a3 != nullptr) {
			Rval* v1 = doUnaExp(a3->e2, stmt_list);
			Rval* v2 = doMulExp(a3->e1, stmt_list);
			Var* v3 = new Var("t" + (std::to_string(getTmpIndex())));
			irStmt* pt1 = new irVarDecl(v3);
			irStmt* pt2;
			IntLitRval* _v1 = dynamic_cast<IntLitRval*>(v1);
			IntLitRval* _v2 = dynamic_cast<IntLitRval*>(v2);
			if (_v1 != nullptr&& _v2 != nullptr)
				return new IntLitRval(_v1->i / _v2->i);
				//pt2 = new numberAssignStmt(v3, new IntLitRval(_v2->i / _v1->i));
			else
				this->curr_func_bl = true;
				pt2 = new binaryStmt(v2, v1, v3, _DIV);
			stmt_list->push_back(pt1);
			stmt_list->push_back(pt2);

			return (new VarRval(v3));
		}
		mod_Mul* a4 = dynamic_cast<mod_Mul*>(exp);
		if (a4 != nullptr) {
			Rval* v1 = doUnaExp(a4->e2, stmt_list);
			Rval* v2 = doMulExp(a4->e1, stmt_list);
			Var* v3 = new Var("t" + (std::to_string(getTmpIndex())));
			irStmt* pt1 = new irVarDecl(v3);
			irStmt* pt2;
			IntLitRval* _v1 = dynamic_cast<IntLitRval*>(v1);
			IntLitRval* _v2 = dynamic_cast<IntLitRval*>(v2);
			if (_v1 != nullptr&& _v2 != nullptr)
				return new IntLitRval(_v1->i % _v2->i);
				//pt2 = new numberAssignStmt(v3, new IntLitRval(_v2->i % _v1->i));
			else
				this->curr_func_bl = true;
				pt2 = new binaryStmt(v2, v1, v3, _MOD);
			stmt_list->push_back(pt1);
			stmt_list->push_back(pt2);

			return (new VarRval(v3));
		}
	}

	Rval* doUnaExp(UnaryExp exp, std::list<irStmt*>* stmt_list) {
		pri_Una* a1 = dynamic_cast<pri_Una*>(exp);
		if (a1 != nullptr) {
			Rval* v1 = doPriExp(a1->e1, stmt_list);
			return v1;
		}
		func_Una* a2 = dynamic_cast<func_Una*>(exp);
		if (a2 != nullptr) {
			this->curr_func_bl = true;
			std::list<Rval*>* paramR = new std::list<Rval*>();
			int l = a2->e2->len();
			AddExp v1;
			Rval* v2;
			for (int i = 0; i < l; i++) {
				int len;
				v1 = a2->e2->nth_length(i,len);
				v2 = doAddExp(v1, stmt_list);
				paramR->push_back(v2);
			}
			
			std::map<std::string, type>::iterator iter;
			id* _id = dynamic_cast<id*>(a2->e1);
			iter= this->methMap->find((_id->e1));
			if (iter->second == _void) {
				stmt_list->push_back(new voidFuncCallStmt(paramR, (_id->e1)));
				return nullptr;
			}
			else if (iter->second == _int) {
				Var* v3 = new Var("t"+(std::to_string( getTmpIndex()))  );
				irStmt* pt1 = new irVarDecl(v3);
				irStmt* pt2 = new intFuncCallStmt(paramR, (_id->e1), v3);
				stmt_list->push_back(pt1);
				stmt_list->push_back(pt2);
				return new VarRval(v3);
			}
		}
		op_Una* a3 = dynamic_cast<op_Una*>(exp);
		if (a3 != nullptr) {
			Rval* v1 = doUnaExp(a3->e2, stmt_list);
			Var* v2 = new Var("t"+(std::to_string( getTmpIndex()))  );
			irStmt* pt = new irVarDecl(v2);
			stmt_list->push_back(pt);
			una_Op* v3 = dynamic_cast<una_Op*>(a3->e1);
			irStmt* pt2;
			if (v3->e1 == "+") {
				pt2 = new unaryStmt(v2, _POS, v1);
				stmt_list->push_back(pt2);
			}
			else if (v3->e1 == "-") {
				pt2 = new unaryStmt(v2, _NEG, v1);
				stmt_list->push_back(pt2);
			}
			else if (v3->e1 == "!") {
				pt2 = new unaryStmt(v2, _NOT, v1);
				stmt_list->push_back(pt2);
			}

			return new VarRval(v2);
		}
	}

	Rval* doPriExp(PrimaryExp exp, std::list<irStmt*>* stmt_list) {
		primary_Exp* a1 = dynamic_cast<primary_Exp*>(exp);
		if (a1 != nullptr) {
			Rval* v1 = doAddExp(a1->e1, stmt_list);
			return v1;
		}
		lval* a2 = dynamic_cast<lval*>(exp);
		if (a2 != nullptr) {
			id* _id = dynamic_cast<id*>(a2->e1);
			if (a2->e2->len() == 0) {
				//std::cout <<"rvar name:"<< a2->e1 << std::endl;
				std::map<std::string, Var*>::iterator iter;
				iter = this->dataMap->find(this->curr_func_name+_id->e1);
				if (iter != this->dataMap->end()) {
					if (iter->second->if_const)
						return new IntLitRval(iter->second->instanceValue);
					return new VarRval(iter->second);
				}
				std::string tmp = "global";
				iter = this->dataMap->find( tmp+ _id->e1);
				if (iter != this->dataMap->end()) {
					if (iter->second->if_const)
						return new IntLitRval(iter->second->instanceValue);
					return new VarRval(iter->second);
				}
				std::map<std::string, arrayVar*>::iterator iter2;
				iter2 = this->arrayMap->find(this->curr_func_name+_id->e1);
				if (iter2 != this->arrayMap->end()) {
					return new arrayRval(iter2->second);
				}
				iter2 = this->arrayMap->find(tmp+_id->e1);
				if (iter2 != this->arrayMap->end()) {
					return new arrayRval(iter2->second);
				}
				else {
					std::cout << "error while finding the variable name" << std::endl;
				}

				//return new VarRval(new Var((_id->e1)));
			}
			else {
				std::list<Rval*>* _list = new std::list<Rval*>();
				for (int i = 0; i < a2->e2->len(); i++) {
					int len;
					Rval* v2 = doAddExp(a2->e2->nth_length(i,len),stmt_list);
					_list->push_back(v2);
				}
				Var* v3 = new Var("t" + std::to_string( getTmpIndex()));
				std::map<std::string, arrayVar*>::iterator iter;
				iter = this->arrayMap->find(this->curr_func_name+_id->e1);
				irStmt* pt2;
				if (iter != this->arrayMap->end()) {
					pt2 = new arrayAssignStmt(v3, iter->second, _list);
				}
				else {
					std::string tmp = "global";
					iter = this->arrayMap->find(tmp + _id->e1);
					if (iter != this->arrayMap->end()) {
						pt2 = new arrayAssignStmt(v3, iter->second, _list);
					}
					else
						std::cout << "error while array assign";
				}
				irStmt* pt1 = new irVarDecl(v3);
				stmt_list->push_back(pt1);
				stmt_list->push_back(pt2);
				return new VarRval(v3);
			}
		}
		number* a3 = dynamic_cast<number*>(exp);
		if (a3 != nullptr) {
			int i;
			std::string t = a3->e1;
			if (strlen(a3->e1) > 1 && a3->e1[0] == '0') {
				if (a3->e1[1] == 'x' || a3->e1[1] == 'X') {
					i = Atoint(t.substr(2, t.length()), 16);
				}
				else {
					i = Atoint(t.substr(1, t.length()), 8);
				}
			}
			else
				i = Atoint(t, 10);
			return new IntLitRval(i);
		}
	}

	int  getTmpIndex() {
		/*std::map<std::string, Var>::iterator iter;
		while (true) {
			iter = dataMap->find("t" + (tmpCounters++));
			if (iter == dataMap->end())
				break;
		}*/
		return tmpCounters++;
	}


	int Atoint(std::string s, int radix)    //s是给定的radix进制字符串
	{
		int ans = 0;
		for (int i = 0; i < s.size(); i++)
		{
			char t = s[i];
			if (t >= '0'&&t <= '9') ans = ans * radix + t - '0';
			else ans = ans * radix + t - 'a' + 10;
		}
		return ans;
	}
};


#endif // !IRGEN_H
