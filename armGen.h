#ifndef  ARMGEN_H
#define ARMGEN_H
#include "ir.h"
#include "arm.h"
#include <set>
#include <map>
#include <iostream>

class armGen {
public:
	int addrCount[1];
	sub_sp* tmp_sp;
	std::list<armStmt*>* run(Prog* prog) {
		std::list<armStmt*>* stmt_list = new std::list<armStmt*>();

		stmt_list->push_back(new armstring(".data\n"));
		//写global 语句

		for (irStmt* stmt : *(prog->datas)) {
			irArrayDecl* _arr = dynamic_cast<irArrayDecl*>(stmt);
			if (_arr != nullptr) {
				stmt_list->push_back(new armstring(".balign 4"));
				stmt_list->push_back(new armstring(_arr->arr->name + ":"));
				stmt_list->push_back(new armstring("    .skip " + std::to_string(_arr->arr->totalSize * 4) + "\n"));
				//stmt_list->push_back(new armstring("=of_" + _arr->arr->name + ": .word " + _arr->arr->name + "\n"));
			}
			irVarDecl* _var = dynamic_cast<irVarDecl*>(stmt);
			if (_var != nullptr) {
				stmt_list->push_back(new armstring(".balign 4"));
				stmt_list->push_back(new armstring(_var->var->name + ":"));
				stmt_list->push_back(new armstring("    .word " + std::to_string(_var->var->instanceValue) + "\n"));

			}
		}

		stmt_list->push_back(new armstring(".text\n"));

		stmt_list->push_back(new globalStmt("main"));
		for (Meth* func : *(prog->meths)) {
			//1.函数名 main:
			//2. push register
			//3. sub sp 数量待定，放一个指针，最后再修改
			stmt_list->push_back(new funcLabel(func->name));
			std::set<reg>* pushlist = new std::set<reg>();
			std::set<reg>* poplist = new std::set<reg>();
			pushlist->insert(fp);
			poplist->insert(fp);
			pushlist->insert(r8);
			poplist->insert(r8);
			//pushlist->insert(r7);
			//poplist->insert(r7);
			stmt_list->push_back(new pushStmt(pushlist));
			stmt_list->push_back(new movVarStmt(sp, fp));
			addrCount[0] = 0;
			tmp_sp = new sub_sp(0);
			stmt_list->push_back(tmp_sp);

			if (func->name == "main") {
				stmt_list->push_back(new SubInstr(r8, fp, new operand2Const(4)));
				for (irStmt* stmt : *(prog->datas)) {
					if (dynamic_cast<irDecl*>(stmt) != nullptr)
						continue;
					doStmt(stmt, stmt_list, addrCount, pushlist, poplist);
				}
			}
			else {
				if (func->jump)
					addrCount[0] = 0;
				else
					addrCount[0] = 1;
			}
			if (func->args->size() != 0) {
				for (irDecl* arg : *(func->args)) {
					irVarDecl* d1 = dynamic_cast<irVarDecl*>(arg);
					if (d1 != nullptr) {
						d1->var->address = addrCount[0]++;
					}
					irArrayDecl* d2 = dynamic_cast<irArrayDecl*>(arg);
					if (d2 != nullptr) {
						int totalSize = 1;
						for (int r : *(d2->arr->dimentions)) {
							totalSize *= r;
						}
						d2->arr->address = addrCount[0]++;
						//addrCount[0] += totalSize;
						d2->arr->totalSize = totalSize;

						/*int totalSize = 1;
						for (int r : *(d2->arr->dimentions)) {
							totalSize *= r;
						}
						d2->arr->address = addrCount[0]++;
						stmt_list->push_back(new SubInstr(r1, fp, new operand2Const((d2->arr->address + 2) * 4)));
						stmt_list->push_back(new strStmt(r1, d2->arr->address));
						d2->arr->totalSize = totalSize;
						addrCount[0] += totalSize;*/
					}
				}
			}
				/*for (irStmt* stmt : *(func->blocks->front()->stmts)) {
					doStmt(stmt, stmt_list, addrCount, pushlist, poplist);
				}*/
			for (irBlock* block : *(func->blocks)) {
				stmt_list->push_back(new armLabel(block->label->name));
				for (irStmt* stmt : *(block->stmts)) {
					doStmt(stmt, stmt_list, addrCount, pushlist, poplist);
				}
			}
				this->tmp_sp->address = addrCount[0];
				//修改sp深度
				//add sp
				stmt_list->push_back(new armstring(".ltorg\n"));
			}
			stmt_list->push_back(new armstring("fmt:\n    .asciz \"  %x  \\n\"\n.end "));
			
			return stmt_list;
		}

		void doStmt(irStmt* stmt, std::list<armStmt*>* stmt_list, int *addrCount, std::set<reg>* pushlist, std::set<reg>* poplist) {
			numberAssignStmt* numAssign = dynamic_cast<numberAssignStmt*>(stmt);
			if (numAssign != nullptr) {
				doNumberassign(numAssign, stmt_list);
				return;
			}
			binaryStmt* binStmt = dynamic_cast<binaryStmt*>(stmt);
			if (binStmt != nullptr) {
				VarRval* val1;
				IntLitRval* val2;
				/*if (binStmt->op == _MOD) {
					 val1= dynamic_cast<VarRval*>(binStmt->a);
					if (val1 != nullptr) {
						stmt_list->push_back(new loadVarStmt(val1->v->address, r1));
					}
					val2= dynamic_cast<IntLitRval*>(binStmt->a);
					if (val2 != nullptr) {
						stmt_list->push_back(new movIntStmt(val2->i, r1));
					}

					val1 = dynamic_cast<VarRval*>(binStmt->b);
					if (val1 != nullptr) {
						stmt_list->push_back(new loadVarStmt(val1->v->address, r0));
					}
					val2 = dynamic_cast<IntLitRval*>(binStmt->b);
					if (val2 != nullptr) {
						stmt_list->push_back(new movIntStmt(val2->i, r0));
					}
				}
				else */

				val1 = dynamic_cast<VarRval*>(binStmt->a);
				if (val1 != nullptr) {
					if (val1->v->if_global) {
						stmt_list->push_back(new armstring("ldr r0,=" + val1->v->name));
						stmt_list->push_back(new loadVarStmt2(r0, r0));
						//stmt_list->push_back(new SubInstr(r1, r8, new operand2Const((val1->v->address) * 4)));
						//stmt_list->push_back(new loadVarStmt2(r1, r0));
					}
					else
						stmt_list->push_back(new loadVarStmt(val1->v->address, r0));
				}
				val2 = dynamic_cast<IntLitRval*>(binStmt->a);
				if (val2 != nullptr) {
					stmt_list->push_back(new movIntStmt(val2->i, r0));
				}

				val1 = dynamic_cast<VarRval*>(binStmt->b);
				if (val1 != nullptr) {
					if (val1->v->if_global) {
						stmt_list->push_back(new armstring("ldr r1,=" + val1->v->name));
						stmt_list->push_back(new loadVarStmt2(r1, r1));
						//stmt_list->push_back(new SubInstr(r2, r8, new operand2Const((val1->v->address) * 4)));
						//stmt_list->push_back(new loadVarStmt2(r2, r1));
					}
					else
						stmt_list->push_back(new loadVarStmt(val1->v->address, r1));
				}
				val2 = dynamic_cast<IntLitRval*>(binStmt->b);
				if (val2 != nullptr) {
					stmt_list->push_back(new movIntStmt(val2->i, r1));
				}



				switch (binStmt->op) {
				case _PLUS:
					stmt_list->push_back(new AddInstr(r3, r0, new operand2Reg(r1)));
					stmt_list->push_back(new strStmt(r3, binStmt->c->address));
					break;
				case _MINUS:
					stmt_list->push_back(new SubInstr(r3, r0, new operand2Reg(r1)));
					stmt_list->push_back(new strStmt(r3, binStmt->c->address));
					break;
				case _MUL:
					stmt_list->push_back(new MulInstr(r3, r0, new operand2Reg(r1)));
					stmt_list->push_back(new strStmt(r3, binStmt->c->address));
					break;
				case _DIV:
					stmt_list->push_back(new blJump("__aeabi_idiv"));
					stmt_list->push_back(new strStmt(r0, binStmt->c->address));
					pushlist->insert(lr);
					poplist->insert(pc);
					break;
				case _MOD:
					stmt_list->push_back(new blJump("__aeabi_idivmod"));
					stmt_list->push_back(new strStmt(r1, binStmt->c->address));
					pushlist->insert(lr);
					poplist->insert(pc);
					break;
				}
				return;
			}
			unaryStmt* unary = dynamic_cast<unaryStmt*>(stmt);
			if (unary != nullptr) {
				IntLitRval* _int = dynamic_cast<IntLitRval*>(unary->b);
				VarRval* _var = dynamic_cast<VarRval*>(unary->b);
				switch (unary->op)
				{
				case _NOT:
					if (_int->i == 0) {
						stmt_list->push_back(new movIntStmt(1, r1));
						stmt_list->push_back(new strStmt(r1, unary->c->address));
					}
					else if (_int->i != 0) {
						stmt_list->push_back(new movIntStmt(0, r1));
						stmt_list->push_back(new strStmt(r1, unary->c->address));
					}
					break;
				case _POS:
					if (_int != nullptr) {
						stmt_list->push_back(new movIntStmt(_int->i, r1));
						stmt_list->push_back(new strStmt(r1, unary->c->address));
					}
					else if (_var != nullptr) {
						if (_var->v->if_global) {
							stmt_list->push_back(new armstring("ldr r2, =" + _var->v->name));
							stmt_list->push_back(new loadVarStmt2(r2, r2));
							//stmt_list->push_back(new SubInstr(r0, r8, new operand2Const((_var->v->address) * 4)));
							//stmt_list->push_back(new loadVarStmt2(r0, r2));
						}
						else
							stmt_list->push_back(new loadVarStmt(_var->v->address, r2));
						stmt_list->push_back(new movVarStmt(r2, r1));
						if (unary->c->if_global) {
							stmt_list->push_back(new armstring("ldr r1, =" + unary->c->name));
							stmt_list->push_back(new strStmt2(r1, r2));
							//stmt_list->push_back(new SubInstr(r3, r8, new operand2Const((unary->c->address) * 4)));
							//stmt_list->push_back(new strStmt2(r3, r1));
						}
						else
							stmt_list->push_back(new strStmt(r1, unary->c->address));
					}
					break;
				case _NEG:
					if (_int != nullptr) {
						stmt_list->push_back(new movIntStmt((-1)*(_int->i), r1));
						stmt_list->push_back(new strStmt(r1, unary->c->address));
					}
					else if (_var != nullptr) {
						if (_var->v->if_global) {
							stmt_list->push_back(new armstring("ldr r2, =" + _var->v->name));
							stmt_list->push_back(new loadVarStmt2(r2, r2));
							//stmt_list->push_back(new SubInstr(r0, r8, new operand2Const((_var->v->address) * 4)));
							//stmt_list->push_back(new loadVarStmt2(r0, r2));
						}
						else
							stmt_list->push_back(new loadVarStmt(_var->v->address, r2));
						stmt_list->push_back(new movIntStmt(0, r1));
						stmt_list->push_back(new SubInstr(r1, r1, new operand2Reg(r2)));
						if (unary->c->if_global) {
							stmt_list->push_back(new armstring("ldr r3, =" + unary->c->name));
							stmt_list->push_back(new strStmt2(r3, r1));
							//stmt_list->push_back(new SubInstr(r3, r8, new operand2Const((unary->c->address) * 4)));
							//stmt_list->push_back(new strStmt2(r3, r1));
						}
						else
							stmt_list->push_back(new strStmt(r1, unary->c->address));
					}
					break;
				default:
					break;
				}
				return;
			}
			irVarDecl* vardecl = dynamic_cast<irVarDecl*>(stmt);
			if (vardecl != nullptr) {
				vardecl->var->address = addrCount[0]++;
				return;
			}
			irArrayDecl* arrdecl = dynamic_cast<irArrayDecl*>(stmt);
			if (arrdecl != nullptr) {
				//ir代码：int a[3][3];
				int totalSize = 1;
				for (int r : *(arrdecl->arr->dimentions)) {
					totalSize *= r;
				}
				//arrdecl->arr->address = addrCount[0]++;
				//stmt_list->push_back(new SubInstr(r1, fp, new operand2Const((arrdecl->arr->address + 2) * 4)));
				//stmt_list->push_back(new strStmt(r1, arrdecl->arr->address));
				arrdecl->arr->totalSize = totalSize;
				addrCount[0] += totalSize;
				arrdecl->arr->address = addrCount[0]++;
				stmt_list->push_back(new SubInstr(r1, fp, new operand2Const((arrdecl->arr->address) * 4)));
				stmt_list->push_back(new strStmt(r1, arrdecl->arr->address));
				return;
			}
			arrayInitStmt* arrInit = dynamic_cast<arrayInitStmt*>(stmt);
			if (arrInit != nullptr) {
				//ir代码： a={0,1,2};
				if (arrInit->arr->arr->if_global) {
					stmt_list->push_back(new armstring("    ldr r2,=" + arrInit->arr->arr->name));
				}
				else {
					stmt_list->push_back(new loadVarStmt(arrInit->arr->arr->address, r2));
				}

				int count = 0;
				for (Rval* r : *(arrInit->vals)) {
					stmt_list->push_back(new AddInstr(r3, r2, new operand2Const((count++) * 4)));

					VarRval* val1 = dynamic_cast<VarRval*>(r);
					if (val1 != nullptr) {

						if (val1->v->if_global) {
							stmt_list->push_back(new armstring("ldr r0, =" + val1->v->name));
							stmt_list->push_back(new loadVarStmt2(r0, r1));
							//stmt_list->push_back(new SubInstr(r0, r8, new operand2Const((val1->v->address) * 4)));
							//stmt_list->push_back(new loadVarStmt2(r0, r1));
						}
						else
							stmt_list->push_back(new loadVarStmt(val1->v->address, r1));
					}
					IntLitRval* val2 = dynamic_cast<IntLitRval*>(r);
					if (val2 != nullptr) {
						stmt_list->push_back(new movIntStmt(val2->i, r1));
					}
					stmt_list->push_back(new strStmt2(r3, r1));
				}
				stmt_list->push_back(new movIntStmt((arrInit->arr->arr->totalSize - arrInit->vals->size()) * 4, r2));
				stmt_list->push_back(new movIntStmt(0, r1));
				//stmt_list->push_back(new SubInstr(r0, fp, new operand2Const((arrInit->arr->arr->address - arrInit->vals->size()) * 4)));
				if(arrInit->arr->arr->if_global)
					stmt_list->push_back(new armstring("    ldr r0,=" + arrInit->arr->arr->name));
				else {
					stmt_list->push_back(new loadVarStmt(arrInit->arr->arr->address, r0));
				}					
				stmt_list->push_back(new AddInstr(r0, r0, new operand2Const(arrInit->vals->size() * 4)));
				stmt_list->push_back(new blJump("memset"));
				pushlist->insert(lr);
				poplist->insert(pc);

				return;
			}
			arrayAssignStmt* arrAssign1 = dynamic_cast<arrayAssignStmt*>(stmt);
			if (arrAssign1 != nullptr) {
				//1. 计算内存位置 2. 赋值
				doArrayAssign(arrAssign1, stmt_list);
				return;
			}
			arrayAssignStmt2* arrAssign2 = dynamic_cast<arrayAssignStmt2*>(stmt);
			if (arrAssign2 != nullptr) {
				//1. 计算内存位置 2. 赋值
				doArrayAssign2(arrAssign2, stmt_list);
				return;
			}
			LabelStmt* label = dynamic_cast<LabelStmt*>(stmt);
			if (label != nullptr) {
				stmt_list->push_back(new armLabel(label->name));
				return;
			}
			GotoStmt* jump = dynamic_cast<GotoStmt*>(stmt);
			if (jump != nullptr) {
				if (jump->label != nullptr)
					stmt_list->push_back(new bJump(jump->label->name));
				return;
			}
			CmpStmt* cmp = dynamic_cast<CmpStmt*>(stmt);
			if (cmp != nullptr) {
				doCmpStmt(cmp, stmt_list);
				return;
			}
			intFuncCallStmt* intFunc = dynamic_cast<intFuncCallStmt*>(stmt);
			if (intFunc != nullptr) {
				pushlist->insert(lr);
				poplist->insert(pc);
				//1.把参数存进寄存器（如何分配空间） 2.bl跳转 3.将r0返回值赋值给变量
				if (intFunc->name == "getarray") {
					arrayRval* val3 = dynamic_cast<arrayRval*>(intFunc->paramR->front());
					if (val3 != nullptr) {
						if (val3->v->if_global) {
							stmt_list->push_back(new armstring("    ldr r0,=" + val3->v->name));
						}
						else {
							stmt_list->push_back(new loadVarStmt(val3->v->address, r0));
						}
					}
					stmt_list->push_back(new blJump(intFunc->name));
					stmt_list->push_back(new strStmt(r0, intFunc->a->address));
					return;
				}

				int count = 3;
				for (Rval* r : *intFunc->paramR) {
					VarRval* val1 = dynamic_cast<VarRval*>(r);
					if (val1 != nullptr) {
						if (val1->v->if_global) {
							stmt_list->push_back(new armstring("ldr r0, =" + val1->v->name));
							stmt_list->push_back(new loadVarStmt2(r0, r1));
							//stmt_list->push_back(new SubInstr(r0, r8, new operand2Const((val1->v->address) * 4)));
							//stmt_list->push_back(new loadVarStmt2(r0, r1));
						}
						else
							stmt_list->push_back(new loadVarStmt(val1->v->address, r1));

						stmt_list->push_back(new strStmt3(r1, count++));
					}
					IntLitRval* val2 = dynamic_cast<IntLitRval*>(r);
					if (val2 != nullptr) {
						stmt_list->push_back(new movIntStmt(val2->i, r1));
						stmt_list->push_back(new strStmt3(r1, count++));
					}
					arrayRval* val3 = dynamic_cast<arrayRval*>(r);
					if (val3 != nullptr) {
						if (val3->v->if_global) {
							stmt_list->push_back(new armstring("    ldr r1,=" + val3->v->name));
						}
						else {
							stmt_list->push_back(new loadVarStmt(val3->v->address, r1));
							//stmt_list->push_back(new SubInstr(r2, fp, new operand2Const((val3->v->address + 1) * 4)));
							//stmt_list->push_back(new loadVarStmt2(r2, r1));
						}
						stmt_list->push_back(new strStmt3(r1, count++));
					}
				}
				stmt_list->push_back(new blJump(intFunc->name));
				stmt_list->push_back(new strStmt(r0, intFunc->a->address));

				return;
			}
			voidFuncCallStmt* voidFunc = dynamic_cast<voidFuncCallStmt*>(stmt);
			if (voidFunc != nullptr) {
				pushlist->insert(lr);
				poplist->insert(pc);
				//1.把参数存进寄存器 2.bl跳转
				if (voidFunc->name == "cout") {
					Rval* r = voidFunc->paramR->front();
					VarRval* val1 = dynamic_cast<VarRval*>(r);
					if (val1->v->if_global) {
						stmt_list->push_back(new armstring("ldr r0, =" + val1->v->name));
						stmt_list->push_back(new loadVarStmt2(r0, r1));
					}
					else
						stmt_list->push_back(new loadVarStmt(val1->v->address, r1));
					//stmt_list->push_back(new loadVarStmt(val1->v->address, r1));
					stmt_list->push_back(new armstring("    ldr r0,=fmt"));
					stmt_list->push_back(new blJump("printf"));
					return;
				}
				if (voidFunc->name == "putint" || voidFunc->name == "putch") {
					Rval* r = voidFunc->paramR->front();
					VarRval* val1 = dynamic_cast<VarRval*>(r);
					if (val1 != nullptr) {
						if (val1->v->if_global) {
							stmt_list->push_back(new armstring("ldr r0, =" + val1->v->name));
							stmt_list->push_back(new loadVarStmt2(r0, r0));
							//stmt_list->push_back(new SubInstr(r1, r8, new operand2Const((val1->v->address) * 4)));
							//stmt_list->push_back(new loadVarStmt2(r1, r0));
						}
						else
							stmt_list->push_back(new loadVarStmt(val1->v->address, r0));
					}
					IntLitRval* val2 = dynamic_cast<IntLitRval*>(r);
					if (val2 != nullptr) {
						stmt_list->push_back(new movIntStmt(val2->i, r0));
					}
					stmt_list->push_back(new blJump(voidFunc->name));
					return;
				}
				if (voidFunc->name == "starttime" || voidFunc->name == "stoptime") {
					stmt_list->push_back(new movIntStmt(stmt_list->size()+1, r0));
					stmt_list->push_back(new blJump("_sysy_" + voidFunc->name));
					return;
				}
				if (voidFunc->name == "putarray") {
					Rval* v1 = voidFunc->paramR->front();
					voidFunc->paramR->pop_front();
					Rval* v2 = voidFunc->paramR->front();

					VarRval* val1 = dynamic_cast<VarRval*>(v1);
					if (val1 != nullptr) {
						if (val1->v->if_global) {
							stmt_list->push_back(new armstring("ldr r0, =" + val1->v->name));
							stmt_list->push_back(new loadVarStmt2(r0, r0));
							//stmt_list->push_back(new SubInstr(r1, r8, new operand2Const((val1->v->address) * 4)));
							//stmt_list->push_back(new loadVarStmt2(r1, r0));
						}
						else
							stmt_list->push_back(new loadVarStmt(val1->v->address, r0));
					}
					IntLitRval* val2 = dynamic_cast<IntLitRval*>(v1);
					if (val2 != nullptr) {
						stmt_list->push_back(new movIntStmt(val2->i, r0));
					}

					arrayRval* val3 = dynamic_cast<arrayRval*>(v2);
					if (val3 != nullptr) {
						if (val3->v->if_global) {
							//stmt_list->push_back(new SubInstr(r2, r8, new operand2Const((val3->v->address) * 4)));
							//stmt_list->push_back(new loadVarStmt2(r2, r1));
							stmt_list->push_back(new armstring("    ldr r1,=" + val3->v->name));
						}
						else {
							stmt_list->push_back(new loadVarStmt(val3->v->address, r1));
							//stmt_list->push_back(new SubInstr(r2, fp, new operand2Const((val3->v->address + 1) * 4)));
							//stmt_list->push_back(new loadVarStmt2(r2, r1));
						}
					}

					stmt_list->push_back(new blJump("putarray"));
					return;
				}
				int count = 3;//2020.8.8
				for (Rval* r : *voidFunc->paramR) {
					VarRval* val1 = dynamic_cast<VarRval*>(r);
					if (val1 != nullptr) {
						if (val1->v->if_global) {
							stmt_list->push_back(new armstring("ldr r0, =" + val1->v->name));
							stmt_list->push_back(new loadVarStmt2(r0, r1));
							//stmt_list->push_back(new SubInstr(r0, r8, new operand2Const((val1->v->address) * 4)));
							//stmt_list->push_back(new loadVarStmt2(r0, r1));
						}
						else
							stmt_list->push_back(new loadVarStmt(val1->v->address, r1));
						stmt_list->push_back(new strStmt3(r1, count++));
					}
					IntLitRval* val2 = dynamic_cast<IntLitRval*>(r);
					if (val2 != nullptr) {
						stmt_list->push_back(new movIntStmt(val2->i, r1));
						stmt_list->push_back(new strStmt3(r1, count++));
					}
					arrayRval* val3 = dynamic_cast<arrayRval*>(r);
					if (val3 != nullptr) {
						if (val3->v->if_global) {
							//stmt_list->push_back(new SubInstr(r2, r8, new operand2Const((val3->v->address) * 4)));
							//stmt_list->push_back(new loadVarStmt2(r2, r1));
							stmt_list->push_back(new armstring("    ldr r1,=" + val3->v->name));
						}
						else {
							stmt_list->push_back(new loadVarStmt(val3->v->address, r1));
							//stmt_list->push_back(new SubInstr(r2, fp, new operand2Const((val3->v->address + 1) * 4)));
							//stmt_list->push_back(new loadVarStmt2(r2, r1));
						}
						stmt_list->push_back(new strStmt3(r1, count++));
						/*for (int i = 0; i < val3->v->totalSize; i++) {
							stmt_list->push_back(new loadVarStmt(val3->v->address + i, r1));
							stmt_list->push_back(new strStmt3(r1, count++));
						}*/
					}
				}
				stmt_list->push_back(new blJump(voidFunc->name));
				return;
			}
			ir_return* return1 = dynamic_cast<ir_return*>(stmt);
			if (return1 != nullptr) {
				//1.add sp 2.pop register 3.bx lr 
				stmt_list->push_back(new movVarStmt(fp, sp));
				stmt_list->push_back(new popStmt(poplist));
				stmt_list->push_back(new bxJump());
				return;
			}
			ir_return_rval* return2 = dynamic_cast<ir_return_rval*>(stmt);
			if (return2 != nullptr) {
				//0.将返回值存入r0 1.add sp 2.pop register 3.bx lr 
				IntLitRval* t1 = dynamic_cast<IntLitRval*>(return2->val);
				if (t1 != nullptr) {
					stmt_list->push_back(new movIntStmt(t1->i, r0));
				}
				VarRval* t2 = dynamic_cast<VarRval*>(return2->val);
				if (t2 != nullptr) {
					if (t2->v->if_global) {
						stmt_list->push_back(new armstring("ldr r0, =" + t2->v->name));
						stmt_list->push_back(new loadVarStmt2(r0, r0));
						//stmt_list->push_back(new SubInstr(r1, r8, new operand2Const((t2->v->address) * 4)));
						//stmt_list->push_back(new loadVarStmt2(r1, r0));

					}
					else {
						stmt_list->push_back(new loadVarStmt(t2->v->address, r0));
					}
				}
				stmt_list->push_back(new movVarStmt(fp, sp));
				stmt_list->push_back(new popStmt(poplist));
				stmt_list->push_back(new bxJump());
				return;
			}
		}

		void doNumberassign(numberAssignStmt* stmt, std::list<armStmt*>* stmt_list) {

			if (stmt->def->if_global) {
				stmt_list->push_back(new armstring("ldr r3, =" + stmt->def->name));
				//stmt_list->push_back(new SubInstr(r3, r8, new operand2Const((stmt->def->address) * 4)));
			}
			IntLitRval* t1 = dynamic_cast<IntLitRval*>(stmt->src);
			if (t1 != nullptr) {
				stmt_list->push_back(new movIntStmt(t1->i, r1));
				if (stmt->def->if_global)
					stmt_list->push_back(new strStmt2(r3, r1));
				else
					stmt_list->push_back(new strStmt(r1, stmt->def->address));
			}
			VarRval* t2 = dynamic_cast<VarRval*>(stmt->src);
			if (t2 != nullptr) {
				if (t2->v->if_global) {
					stmt_list->push_back(new armstring("ldr r2, =" + t2->v->name));
					stmt_list->push_back(new loadVarStmt2(r2, r2));
					//stmt_list->push_back(new SubInstr(r1, r8, new operand2Const((t2->v->address) * 4)));
					//stmt_list->push_back(new loadVarStmt2(r1, r2));
					if (stmt->def->if_global)
						stmt_list->push_back(new strStmt2(r3, r2));
					else
						stmt_list->push_back(new strStmt(r2, stmt->def->address));
				}
				else {
					stmt_list->push_back(new loadVarStmt(t2->v->address, r1));
					if (stmt->def->if_global)
						stmt_list->push_back(new strStmt2(r3, r1));
					else
						stmt_list->push_back(new strStmt(r1, stmt->def->address));
				}
			}
		}

		void doCmpStmt(CmpStmt* cmp, std::list<armStmt*>* stmt_list) {
			operand2 *op1, *op2;
			IntLitRval* t1 = dynamic_cast<IntLitRval*>(cmp->a);
			if (t1 != nullptr) {
				op1 = new operand2Const(t1->i);
			}
			VarRval* t2 = dynamic_cast<VarRval*>(cmp->a);
			if (t2 != nullptr) {
				if (t2->v->if_global) {
					stmt_list->push_back(new armstring("ldr r1, =" + t2->v->name));
					stmt_list->push_back(new loadVarStmt2(r1, r1));
					//stmt_list->push_back(new SubInstr(r0, r8, new operand2Const((t2->v->address) * 4)));
					//stmt_list->push_back(new loadVarStmt2(r0, r1));
				}
				else
					stmt_list->push_back(new loadVarStmt(t2->v->address, r1));
				op1 = new operand2Reg(r1);
			}
			t1 = dynamic_cast<IntLitRval*>(cmp->b);
			if (t1 != nullptr) {
				op2 = new operand2Const(t1->i);
			}
			t2 = dynamic_cast<VarRval*>(cmp->b);
			if (t2 != nullptr) {
				if (t2->v->if_global) {
					stmt_list->push_back(new armstring("ldr r2, =" + t2->v->name));
					stmt_list->push_back(new loadVarStmt2(r2, r2));
					//stmt_list->push_back(new SubInstr(r0, r8, new operand2Const((t2->v->address) * 4)));
					//stmt_list->push_back(new loadVarStmt2(r0, r2));
				}
				else
					stmt_list->push_back(new loadVarStmt(t2->v->address, r2));
				op2 = new operand2Reg(r2);
			}
			stmt_list->push_back(new armCmp(op1, op2, cmp->op, cmp->label->name));
		}

		void doArrayAssign(arrayAssignStmt* arrAssign1, std::list<armStmt*>* stmt_list) {
			int len = arrAssign1->_list->size();
			if (len == 1) {
				Rval* val = arrAssign1->_list->front();
				IntLitRval* v1 = dynamic_cast<IntLitRval*>(val);
				if (v1 != nullptr) {
					stmt_list->push_back(new movIntStmt(v1->i, r1));
				}
				VarRval* v2 = dynamic_cast<VarRval*>(val);
				if (v2 != nullptr) {
					if (v2->v->if_global) {
						stmt_list->push_back(new armstring("ldr r0, =" + v2->v->name));
						stmt_list->push_back(new loadVarStmt2(r0, r1));
						//stmt_list->push_back(new SubInstr(r0, r8, new operand2Const((v2->v->address) * 4)));
						//stmt_list->push_back(new loadVarStmt2(r0, r1));
					}
					else
						stmt_list->push_back(new loadVarStmt(v2->v->address, r1));
				}
				/*stmt_list->push_back(new movIntStmt(arrAssign1->arr->address+1, r2));
				stmt_list->push_back(new AddInstr(r1, r1, new operand2Reg(r2)));
				stmt_list->push_back(new movIntStmt(4, r3));
				stmt_list->push_back(new MulInstr(r2, r1, new operand2Reg(r3)));
				stmt_list->push_back(new SubInstr(r2, fp, new operand2Reg(r2)));*/
				stmt_list->push_back(new movIntStmt(4, r3));
				stmt_list->push_back(new MulInstr(r2, r1, new operand2Reg(r3)));
				if (arrAssign1->arr->if_global) {
					//stmt_list->push_back(new SubInstr(r3, r8, new operand2Const((arrAssign1->arr->address) * 4)));
					//stmt_list->push_back(new loadVarStmt2(r3, r1));
					stmt_list->push_back(new armstring("    ldr r1,=" + arrAssign1->arr->name));
				}
				else {
					stmt_list->push_back(new loadVarStmt(arrAssign1->arr->address, r1));
				}
				//stmt_list->push_back(new SubInstr(r2, r1, new operand2Reg(r2)));
				stmt_list->push_back(new AddInstr(r2, r1, new operand2Reg(r2)));
				stmt_list->push_back(new loadVarStmt2(r2, r1));
				stmt_list->push_back(new strStmt(r1, arrAssign1->def->address));
			}
			else if (len == 2) {
				int d1 = -1, d2 = -1;
				for (int i : *arrAssign1->arr->dimentions) {
					if (d1 == -1)
						d1 = i;
					else
						d2 = i;
				}
				stmt_list->push_back(new movIntStmt(0, r1));
				stmt_list->push_back(new movIntStmt(d2, r2));

				Rval* val = arrAssign1->_list->front();
				arrAssign1->_list->pop_front();
				IntLitRval* v1 = dynamic_cast<IntLitRval*>(val);
				if (v1 != nullptr) {
					stmt_list->push_back(new movIntStmt(v1->i, r3));
				}
				VarRval* v2 = dynamic_cast<VarRval*>(val);
				if (v2 != nullptr) {
					if (v2->v->if_global) {
						stmt_list->push_back(new armstring("ldr r3, =" + v2->v->name));
						stmt_list->push_back(new loadVarStmt2(r3, r3));
						//stmt_list->push_back(new SubInstr(r0, r8, new operand2Const((v2->v->address) * 4)));
						//stmt_list->push_back(new loadVarStmt2(r0, r3));
					}
					else
						stmt_list->push_back(new loadVarStmt(v2->v->address, r3));
				}

				stmt_list->push_back(new MulInstr(r4, r2, new operand2Reg(r3)));
				stmt_list->push_back(new AddInstr(r1, r1, new operand2Reg(r4)));

				Rval* val2 = arrAssign1->_list->front();
				arrAssign1->_list->pop_front();
				v1 = dynamic_cast<IntLitRval*>(val2);
				if (v1 != nullptr) {
					stmt_list->push_back(new movIntStmt(v1->i, r3));
				}
				v2 = dynamic_cast<VarRval*>(val2);
				if (v2 != nullptr) {
					if (v2->v->if_global) {
						stmt_list->push_back(new armstring("ldr r3, =" + v2->v->name));
						stmt_list->push_back(new loadVarStmt2(r3, r3));
						//stmt_list->push_back(new SubInstr(r0, r8, new operand2Const((v2->v->address) * 4)));
						//stmt_list->push_back(new loadVarStmt2(r0, r3));
					}
					else
						stmt_list->push_back(new loadVarStmt(v2->v->address, r3));
				}

				stmt_list->push_back(new AddInstr(r1, r1, new operand2Reg(r3)));
				/*stmt_list->push_back(new movIntStmt(arrAssign1->arr->address+1, r2));
				stmt_list->push_back(new AddInstr(r1, r2, new operand2Reg(r1)));
				stmt_list->push_back(new movIntStmt(4, r2));
				stmt_list->push_back(new MulInstr(r3, r1, new operand2Reg(r2)));
				stmt_list->push_back(new SubInstr(r1, fp, new operand2Reg(r3)));
				stmt_list->push_back(new loadVarStmt2(r1, r1));*/

				stmt_list->push_back(new movIntStmt(4, r3));
				stmt_list->push_back(new MulInstr(r2, r1, new operand2Reg(r3)));
				if (arrAssign1->arr->if_global) {
					//stmt_list->push_back(new SubInstr(r3, r8, new operand2Const((arrAssign1->arr->address) * 4)));
					//stmt_list->push_back(new loadVarStmt2(r3, r1));
					stmt_list->push_back(new armstring("    ldr r1,=" + arrAssign1->arr->name));
				}
				else {
					stmt_list->push_back(new loadVarStmt(arrAssign1->arr->address, r1));
				}
				stmt_list->push_back(new AddInstr(r2, r1, new operand2Reg(r2)));
				//stmt_list->push_back(new SubInstr(r2, r1, new operand2Reg(r2)));
				stmt_list->push_back(new loadVarStmt2(r2, r1));

				stmt_list->push_back(new strStmt(r1, arrAssign1->def->address));

			}
			else if (len == 3) {
				int d1 = -1, d2 = -1, d3 = -1;
				for (int i : *arrAssign1->arr->dimentions) {
					if (d1 == -1)
						d1 = i;
					else if (d2 == -1)
						d2 = i;
					else
						d3 = i;
				}
				stmt_list->push_back(new movIntStmt(0, r1));

				stmt_list->push_back(new movIntStmt(d2*d3, r2));
				Rval* val = arrAssign1->_list->front();
				arrAssign1->_list->pop_front();
				IntLitRval* v1 = dynamic_cast<IntLitRval*>(val);
				if (v1 != nullptr) {
					stmt_list->push_back(new movIntStmt(v1->i, r3));
				}
				VarRval* v2 = dynamic_cast<VarRval*>(val);
				if (v2 != nullptr) {
					if (v2->v->if_global) {
						stmt_list->push_back(new armstring("ldr r3, =" + v2->v->name));
						stmt_list->push_back(new loadVarStmt2(r3, r3));
						//stmt_list->push_back(new SubInstr(r0, r8, new operand2Const((v2->v->address) * 4)));
						//stmt_list->push_back(new loadVarStmt2(r0, r3));
					}
					else
						stmt_list->push_back(new loadVarStmt(v2->v->address, r3));
				}
				stmt_list->push_back(new MulInstr(r4, r2, new operand2Reg(r3)));
				stmt_list->push_back(new AddInstr(r1, r1, new operand2Reg(r4)));

				stmt_list->push_back(new movIntStmt(d3, r2));
				Rval* val2 = arrAssign1->_list->front();
				arrAssign1->_list->pop_front();
				v1 = dynamic_cast<IntLitRval*>(val2);
				if (v1 != nullptr) {
					stmt_list->push_back(new movIntStmt(v1->i, r3));
				}
				v2 = dynamic_cast<VarRval*>(val2);
				if (v2 != nullptr) {
					if (v2->v->if_global) {
						stmt_list->push_back(new armstring("ldr r3, =" + v2->v->name));
						stmt_list->push_back(new loadVarStmt2(r3, r3));
						//stmt_list->push_back(new SubInstr(r0, r8, new operand2Const((v2->v->address) * 4)));
						//stmt_list->push_back(new loadVarStmt2(r0, r3));
					}
					else
						stmt_list->push_back(new loadVarStmt(v2->v->address, r3));
				}
				stmt_list->push_back(new MulInstr(r4, r2, new operand2Reg(r3)));
				stmt_list->push_back(new AddInstr(r1, r1, new operand2Reg(r4)));

				Rval* val3 = arrAssign1->_list->front();
				arrAssign1->_list->pop_front();
				v1 = dynamic_cast<IntLitRval*>(val3);
				if (v1 != nullptr) {
					stmt_list->push_back(new movIntStmt(v1->i, r3));
				}
				v2 = dynamic_cast<VarRval*>(val3);
				if (v2 != nullptr) {
					if (v2->v->if_global) {
						stmt_list->push_back(new armstring("ldr r3, =" + v2->v->name));
						stmt_list->push_back(new loadVarStmt2(r3, r3));
						//stmt_list->push_back(new SubInstr(r0, r8, new operand2Const((v2->v->address) * 4)));
						//stmt_list->push_back(new loadVarStmt2(r0, r3));
					}
					else
						stmt_list->push_back(new loadVarStmt(v2->v->address, r3));
				}
				stmt_list->push_back(new AddInstr(r1, r1, new operand2Reg(r3)));

				/*stmt_list->push_back(new movIntStmt(arrAssign1->arr->address+1, r2));
				stmt_list->push_back(new AddInstr(r1, r1, new operand2Reg(r2)));
				stmt_list->push_back(new movIntStmt(4, r2));
				stmt_list->push_back(new MulInstr(r3, r1, new operand2Reg(r2)));
				stmt_list->push_back(new SubInstr(r1, fp, new operand2Reg(r3)));
				stmt_list->push_back(new loadVarStmt2(r1, r2));*/

				//stmt_list->push_back(new SubInstr(r1, r1, new operand2Const(1)));
				stmt_list->push_back(new movIntStmt(4, r3));
				stmt_list->push_back(new MulInstr(r2, r1, new operand2Reg(r3)));
				if (arrAssign1->arr->if_global) {
					//stmt_list->push_back(new SubInstr(r3, r8, new operand2Const((arrAssign1->arr->address) * 4)));
					//stmt_list->push_back(new loadVarStmt2(r3, r1));
					stmt_list->push_back(new armstring("    ldr r1,=" + arrAssign1->arr->name));
				}
				else {
					stmt_list->push_back(new loadVarStmt(arrAssign1->arr->address, r1));
				}
				stmt_list->push_back(new AddInstr(r2, r1, new operand2Reg(r2)));
				//stmt_list->push_back(new SubInstr(r2, r1, new operand2Reg(r2)));
				stmt_list->push_back(new loadVarStmt2(r2, r1));

				stmt_list->push_back(new strStmt(r1, arrAssign1->def->address));

			}
		}

		void doArrayAssign2(arrayAssignStmt2* arrAssign1, std::list<armStmt*>* stmt_list) {
			int len = arrAssign1->_list->size();
			if (len == 1) {
				Rval* val = arrAssign1->_list->front();
				IntLitRval* v1 = dynamic_cast<IntLitRval*>(val);
				if (v1 != nullptr) {
					stmt_list->push_back(new movIntStmt(v1->i, r1));
				}
				VarRval* v2 = dynamic_cast<VarRval*>(val);
				if (v2 != nullptr) {
					if (v2->v->if_global) {
						stmt_list->push_back(new armstring("ldr r1, =" + v2->v->name));
						stmt_list->push_back(new loadVarStmt2(r1, r1));
						//stmt_list->push_back(new SubInstr(r0, r8, new operand2Const((v2->v->address) * 4)));
						//stmt_list->push_back(new loadVarStmt2(r0, r1));
					}
					else
						stmt_list->push_back(new loadVarStmt(v2->v->address, r1));
				}
				/*stmt_list->push_back(new loadVarStmt(arrAssign1->arr->address, r2));
				stmt_list->push_back(new AddInstr(r1, r1, new operand2Reg(r2)));
				stmt_list->push_back(new MulInstr(r1, r1, new operand2Const(4)));*/


				stmt_list->push_back(new movIntStmt(4, r3));
				stmt_list->push_back(new MulInstr(r2, r1, new operand2Reg(r3)));
				if (arrAssign1->arr->if_global) {
					//stmt_list->push_back(new SubInstr(r3, r8, new operand2Const((arrAssign1->arr->address) * 4)));
					//stmt_list->push_back(new loadVarStmt2(r3, r1));
					stmt_list->push_back(new armstring("    ldr r1,=" + arrAssign1->arr->name));
				}
				else {
					stmt_list->push_back(new loadVarStmt(arrAssign1->arr->address, r1));
				}
				stmt_list->push_back(new AddInstr(r1, r1, new operand2Reg(r2)));
				//stmt_list->push_back(new SubInstr(r1, r1, new operand2Reg(r2)));

				val = arrAssign1->val;
				v1 = dynamic_cast<IntLitRval*>(val);
				if (v1 != nullptr) {
					stmt_list->push_back(new movIntStmt(v1->i, r2));
				}
				v2 = dynamic_cast<VarRval*>(val);
				if (v2 != nullptr) {
					//if(v2->v->if_global)
					stmt_list->push_back(new loadVarStmt(v2->v->address, r2));
				}
				stmt_list->push_back(new strStmt2(r1, r2));
			}
			else if (len == 2) {
				int d1 = -1, d2 = -1;
				for (int i : *arrAssign1->arr->dimentions) {
					if (d1 == -1)
						d1 = i;
					else
						d2 = i;
				}
				stmt_list->push_back(new movIntStmt(0, r1));
				stmt_list->push_back(new movIntStmt(d2, r2));

				Rval* val = arrAssign1->_list->front();
				arrAssign1->_list->pop_front();
				IntLitRval* v1 = dynamic_cast<IntLitRval*>(val);
				if (v1 != nullptr) {
					stmt_list->push_back(new movIntStmt(v1->i, r3));
				}
				VarRval* v2 = dynamic_cast<VarRval*>(val);
				if (v2 != nullptr) {
					if (v2->v->if_global) {
						stmt_list->push_back(new armstring("ldr r3, =" + v2->v->name));
						stmt_list->push_back(new loadVarStmt2(r3, r3));
						//stmt_list->push_back(new SubInstr(r0, r8, new operand2Const((v2->v->address) * 4)));
						//stmt_list->push_back(new loadVarStmt2(r0, r3));
					}
					else
						stmt_list->push_back(new loadVarStmt(v2->v->address, r3));
				}

				stmt_list->push_back(new MulInstr(r4, r2, new operand2Reg(r3)));
				stmt_list->push_back(new AddInstr(r1, r1, new operand2Reg(r4)));

				Rval* val2 = arrAssign1->_list->front();
				arrAssign1->_list->pop_front();
				v1 = dynamic_cast<IntLitRval*>(val2);
				if (v1 != nullptr) {
					stmt_list->push_back(new movIntStmt(v1->i, r3));
				}
				v2 = dynamic_cast<VarRval*>(val2);
				if (v2 != nullptr) {
					if (v2->v->if_global) {
						stmt_list->push_back(new armstring("ldr r3, =" + v2->v->name));
						stmt_list->push_back(new loadVarStmt2(r3, r3));
						//stmt_list->push_back(new SubInstr(r0, r8, new operand2Const((v2->v->address) * 4)));
						//stmt_list->push_back(new loadVarStmt2(r0, r3));
					}
					else
						stmt_list->push_back(new loadVarStmt(v2->v->address, r3));
				}

				stmt_list->push_back(new AddInstr(r1, r1, new operand2Reg(r3)));

				/*stmt_list->push_back(new loadVarStmt(arrAssign1->arr->address, r2));
				stmt_list->push_back(new AddInstr(r1, r1, new operand2Reg(r2)));
				stmt_list->push_back(new MulInstr(r1, r1, new operand2Const(4)));*/


				stmt_list->push_back(new movIntStmt(4, r3));
				stmt_list->push_back(new MulInstr(r2, r1, new operand2Reg(r3)));
				if (arrAssign1->arr->if_global) {
					//stmt_list->push_back(new SubInstr(r3, r8, new operand2Const((arrAssign1->arr->address) * 4)));
					//stmt_list->push_back(new loadVarStmt2(r3, r1));
					stmt_list->push_back(new armstring("    ldr r1,=" + arrAssign1->arr->name));
				}
				else {
					stmt_list->push_back(new loadVarStmt(arrAssign1->arr->address, r1));
				}
				stmt_list->push_back(new AddInstr(r1, r1, new operand2Reg(r2)));

				val = arrAssign1->val;
				v1 = dynamic_cast<IntLitRval*>(val);
				if (v1 != nullptr) {
					stmt_list->push_back(new movIntStmt(v1->i, r2));
				}
				v2 = dynamic_cast<VarRval*>(val);
				if (v2 != nullptr) {
					stmt_list->push_back(new loadVarStmt(v2->v->address, r2));
				}
				stmt_list->push_back(new strStmt2(r1, r2));

			}
			else if (len == 3) {
				int d1 = -1, d2 = -1, d3 = -1;
				for (int i : *arrAssign1->arr->dimentions) {
					if (d1 == -1)
						d1 = i;
					else if (d2 == -1)
						d2 = i;
					else
						d3 = i;
				}
				std::cout << d1 << d2 << d3;
				stmt_list->push_back(new movIntStmt(0, r1));

				stmt_list->push_back(new movIntStmt(d2*d3, r2));
				Rval* val = arrAssign1->_list->front();
				arrAssign1->_list->pop_front();
				IntLitRval* v1 = dynamic_cast<IntLitRval*>(val);
				if (v1 != nullptr) {
					stmt_list->push_back(new movIntStmt(v1->i, r3));
				}
				VarRval* v2 = dynamic_cast<VarRval*>(val);
				if (v2 != nullptr) {
					if (v2->v->if_global) {
						stmt_list->push_back(new armstring("ldr r3, =" + v2->v->name));
						stmt_list->push_back(new loadVarStmt2(r3, r3));
						//stmt_list->push_back(new SubInstr(r0, r8, new operand2Const((v2->v->address) * 4)));
						//stmt_list->push_back(new loadVarStmt2(r0, r3));
					}
					else
						stmt_list->push_back(new loadVarStmt(v2->v->address, r3));
				}
				stmt_list->push_back(new MulInstr(r4, r2, new operand2Reg(r3)));
				stmt_list->push_back(new AddInstr(r1, r1, new operand2Reg(r4)));

				stmt_list->push_back(new movIntStmt(d3, r2));
				Rval* val2 = arrAssign1->_list->front();
				arrAssign1->_list->pop_front();
				v1 = dynamic_cast<IntLitRval*>(val2);
				if (v1 != nullptr) {
					stmt_list->push_back(new movIntStmt(v1->i, r3));
				}
				v2 = dynamic_cast<VarRval*>(val2);
				if (v2 != nullptr) {
					if (v2->v->if_global) {
						stmt_list->push_back(new armstring("ldr r3, =" + v2->v->name));
						stmt_list->push_back(new loadVarStmt2(r3, r3));
						//stmt_list->push_back(new SubInstr(r0, r8, new operand2Const((v2->v->address) * 4)));
						//stmt_list->push_back(new loadVarStmt2(r0, r3));
					}
					else
						stmt_list->push_back(new loadVarStmt(v2->v->address, r3));
				}
				stmt_list->push_back(new MulInstr(r4, r2, new operand2Reg(r3)));
				stmt_list->push_back(new AddInstr(r1, r1, new operand2Reg(r4)));

				Rval* val3 = arrAssign1->_list->front();
				arrAssign1->_list->pop_front();
				v1 = dynamic_cast<IntLitRval*>(val3);
				if (v1 != nullptr) {
					stmt_list->push_back(new movIntStmt(v1->i, r3));
				}
				v2 = dynamic_cast<VarRval*>(val3);
				if (v2 != nullptr) {
					if (v2->v->if_global) {
						stmt_list->push_back(new armstring("ldr r3, =" + v2->v->name));
						stmt_list->push_back(new loadVarStmt2(r3, r3));
						//stmt_list->push_back(new SubInstr(r0, r8, new operand2Const((v2->v->address) * 4)));
						//stmt_list->push_back(new loadVarStmt2(r0, r3));
					}
					else
						stmt_list->push_back(new loadVarStmt(v2->v->address, r3));
				}
				stmt_list->push_back(new AddInstr(r1, r1, new operand2Reg(r3)));

				/*stmt_list->push_back(new loadVarStmt(arrAssign1->arr->address, r2));
				stmt_list->push_back(new AddInstr(r1, r1, new operand2Reg(r2)));
				stmt_list->push_back(new MulInstr(r1, r1, new operand2Const(4)));*/


				stmt_list->push_back(new movIntStmt(4, r3));
				stmt_list->push_back(new MulInstr(r2, r1, new operand2Reg(r3)));
				if (arrAssign1->arr->if_global) {
					//stmt_list->push_back(new SubInstr(r3, r8, new operand2Const((arrAssign1->arr->address) * 4)));
					//stmt_list->push_back(new loadVarStmt2(r3, r1));
					stmt_list->push_back(new armstring("    ldr r1,=" + arrAssign1->arr->name));
				}
				else {
					stmt_list->push_back(new loadVarStmt(arrAssign1->arr->address, r1));
				}
				stmt_list->push_back(new AddInstr(r1, r1, new operand2Reg(r2)));

				val = arrAssign1->val;
				v1 = dynamic_cast<IntLitRval*>(val);
				if (v1 != nullptr) {
					stmt_list->push_back(new movIntStmt(v1->i, r2));
				}
				v2 = dynamic_cast<VarRval*>(val);
				if (v2 != nullptr) {
					stmt_list->push_back(new loadVarStmt(v2->v->address, r2));
				}
				stmt_list->push_back(new strStmt2(r1, r2));

			}
		}
	
};
#endif // ! ARMGEN_H

