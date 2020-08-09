#ifndef ARM_H
#define ARM_H
#include <string>
#include "ir.h"
#include <set>

class arm {

};

class armStmt {
public:
	virtual std::string render() = 0;
};

enum reg{r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,sp,fp,lr,pc};
std::string regtostring[15] = { "r0","r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "sp", "fp", "lr", "pc" };

class operand2 {
public:
	virtual std::string render() = 0;
};

class operand2Const :public operand2 {
public:
	int i;
	operand2Const(int i) {
		this->i = i;
	}
	std::string render() {
		return "#"+std::to_string(i);
	}
};

class operand2Reg :public operand2 {
public:
	reg r;
	operand2Reg(reg r) {
		this->r = r;
	}
	std::string render() {
		return regtostring[r];
	}
};

class Instr:public armStmt {
public:
	virtual std::string render() = 0;
};

class AddInstr :public Instr {
public:
	reg dst;
	reg r1;
	operand2* r2;
	AddInstr(reg dst, reg r1, operand2* r2) {
		this->r1 = r1;
		this->dst = dst;
		this->r2 = r2;
	}
	std::string render() {
		std::string sb = "    ";
		operand2Const* _int = dynamic_cast<operand2Const*>(r2);
		if (_int != nullptr && _int->i > 256)
			sb = sb + "ldr r7,=" + std::to_string(_int->i) + ";    add " + regtostring[dst] + ", " + regtostring[r1] + ", r7\n";
		else
			sb = sb + "add " + regtostring[dst] + ", " + regtostring[r1] + ", " + r2->render() + "\n";
		return sb;
	}
};

class SubInstr :public Instr {
public:
	reg dst;
	reg r1;
	operand2* r2;
	SubInstr(reg dst, reg r1, operand2* r2) {
		this->r1 = r1;
		this->dst = dst;
		this->r2 = r2;
	}
	std::string render() {
		std::string sb = "    ";
		operand2Const* _int = dynamic_cast<operand2Const*>(r2);
		if (_int != nullptr && _int->i > 256) 
			sb=sb+"ldr r7,="+std::to_string(_int->i)+";    sub "+ regtostring[dst] + ", " + regtostring[r1] + ", r7\n";
		else
			sb = sb + "sub " + regtostring[dst] + ", " + regtostring[r1] + ", " + r2->render() + "\n";
		return sb;
	}
};

class sub_sp :public Instr {
public:
	int address;
	sub_sp(int addr) {
		this->address = addr;
	}
	std::string render() {
		std::string sb;
		if(address>256)
			 sb= "    ldr r7,="+std::to_string(address*4)+";"+"    sub sp, sp, r7\n";
		else
			sb = "    sub sp, sp, #" + std::to_string(address*4) + "\n";
		return sb;
	}
};

class MulInstr :public Instr {
public:
	reg dst;
	reg r1;
	operand2* r2;
	MulInstr(reg dst, reg r1, operand2* r2) {
		this->r1 = r1;
		this->dst = dst;
		this->r2 = r2;
	}
	std::string render() {
		std::string sb = "    ";
		sb = sb + "mul " + regtostring[dst] + ", " + regtostring[r1] + ", " + r2->render() + "\n";
		return sb;
	}
};



class loadVarStmt:public armStmt {
public:
	int address;
	reg dst;
	
	loadVarStmt(int address, reg dst) {
		this->address = (address+1)*4;
		this->dst = dst;
	}

	std::string render() {
		std::string sb = "    ";
		if (address<256 )
			sb.append("ldr ").append(regtostring[dst] + ", [fp, #-").append(std::to_string(address) + "]\n");
		else {
			sb.append("ldr r7,=" + std::to_string(address) + ";");
			sb.append("    sub r7,fp,r7;    ldr ").append(regtostring[dst] + ", [r7]\n");
		}
		return sb;
	}
};

class loadVarStmt2 :public armStmt {
public:
	reg address;
	reg dst;

	loadVarStmt2(reg address, reg dst) {
		this->dst = dst;
		this->address = address;
	}

	std::string render() {
		std::string sb = "    ";
		sb.append("ldr ").append(regtostring[dst] + ", ").append("[" + regtostring[address]).append("]\n");
		return sb;
	}
};

class movIntStmt:public armStmt {
public:
	int number;
	reg dst;
	movIntStmt(int number, reg dst) {
		this->number = number;
		this->dst = dst;
	}
	std::string render() {
		std::string sb = "    ";
		if(number<=256 && number>0)
			sb.append("mov ").append(regtostring[dst] + ", ").append("#" + std::to_string(number)).append("\n");
		else
			sb.append("ldr ").append(regtostring[dst] + ", ").append("=" + std::to_string(number)).append("\n");

		return sb;
	}
};
/*class movIntStmt2 :public armStmt {
public:
	int number;
	reg dst;
	movIntStmt2(int number, reg dst) {
		this->number = number;
		this->dst = dst;
	}
	std::string render() {
		std::string sb = "    ";
		sb.append("ldr ").append(regtostring[dst] + ", ").append("=" + std::to_string(number)).append("\n");
		return sb;
	}
};*/
class movVarStmt :public armStmt {
public:
	reg src;
	reg dst;
	movVarStmt(reg src, reg dst) {
		this->src = src;
		this->dst = dst;
	}
	std::string render() {
		std::string sb = "    ";
		sb.append("mov ").append(regtostring[dst] + ", ").append(regtostring[src]+"").append("\n");
		return sb;
	}
};

class strStmt :public armStmt {
public:
	reg src;
	int address;
	strStmt(reg src, int address) {
		this->src = src;
		this->address = (address+1)*4;
	}

	std::string render() {
		std::string sb = "    ";
		if(address<256 && address>=0)
			sb.append("str ").append(regtostring[src] + ", [fp, #-").append(std::to_string(address) + "]\n");
		else {
			sb.append("ldr r7,=" + std::to_string(address)+";");
			sb.append("    sub r7,fp,r7;    str ").append(regtostring[src] + ", [r7]\n");
		}
		return sb;
	}
};

class strStmt2 :public armStmt {
public:
	reg address;
	reg dst;

	strStmt2(reg address,reg dst) {
		this->dst = dst;
		this->address = address;
	}

	std::string render() {
		std::string sb = "    ";
		sb.append("str ").append(regtostring[dst] + ", ").append("[" + regtostring[address]).append("]\n");
		return sb;
	}
};

class strStmt3 :public armStmt {
public:
	reg src;
	int address;	
	strStmt3(reg src, int address) {
		this->src = src;
		this->address = (address + 1) * 4;
	}

	std::string render() {
		std::string sb = "    ";
		sb.append("str ").append(regtostring[src] + ", [sp, #-").append(std::to_string(address) + "]\n");
		return sb;
	}
};

class armLabel :public armStmt {
public:
	std::string name;
	armLabel(std::string name) {
		this->name = name;
	}
	std::string render() {
		std::string sb = "";
		sb.append("." + name + ":\n");
		return sb;
	}
};

class bJump :public armStmt {
public:
	std::string name;
	bJump(std::string name) {
		this->name = name;
	}
	std::string render() {
		std::string sb = "";
		sb.append("    b ." + name + "\n");
		return sb;
	}
};

class blJump :public armStmt {
public:
	std::string name;
	blJump(std::string name) {
		this->name = name;
	}
	std::string render() {
		std::string sb = "";
		sb.append("    bl " + name + "\n");
		return sb;
	}
};

class bxJump :public armStmt {
public:
	bxJump(){}
	std::string render() {
		return "    bx lr\n";
	}
};

class armCmp :public armStmt {
public:
	operand2* op1;
	operand2* op2;
	condOp op;
	std::string labelName;
	armCmp(operand2* op1, operand2* op2, condOp op, std::string labelName) {
		this->op1 = op1;
		this->op2 = op2;
		this->op = op;
		this->labelName=labelName;
	}
	std::string render() {
		std::string sb = "    ";
		operand2Const* _int = dynamic_cast<operand2Const*>(op2);
		if (_int != nullptr && (_int->i > 256 || _int->i < 0)) {
		//if(false){
			sb.append("ldr r7,=").append(std::to_string(_int->i)).append(";");
			sb.append("cmp " + op1->render() + ", r7;");
		}
		else
			sb.append("cmp " + op1->render()+", "+op2->render() + ";");
		sb.append("    b");
		switch (op)
		{
		case _EQ:
			sb.append("eq");
			break;
		case _NE:
			sb.append("ne");
			break;
		case _LT:
			sb.append("lt");
			break;
		case _GT:
			sb.append("gt");
			break;
		case _LE:
			sb.append("le");
			break;
		case _GE:
			sb.append("ge");
			break;
		default:
			break;
		}
		
		sb.append(" .").append(labelName).append("\n");
		return sb;
	}
};

class funcLabel :public armStmt {
public:
	std::string name;
	funcLabel(std::string name) {
		this->name = name;
	}
	std::string render() {
		std::string sb = "";
		sb.append(name + ":\n");
		return sb;
	}
};

class pushStmt :public armStmt {
public:
	std::set<reg>* list;
	pushStmt(std::set<reg>* list) {
		this->list = list;
	}
	std::string render() {
		std::string sb = "    ";
		sb.append("push {r8");
		bool first = true;
		for (reg r: *list) {
			if(r==r8)
				continue;
			sb.append(","+regtostring[r]);
		}
		sb.append("}\n");
		return sb;
	}
};

class popStmt :public armStmt {
public:
	std::set<reg>* list;
	popStmt(std::set<reg>* list) {
		this->list = list;
	}
	std::string render() {
		std::string sb = "    ";
		sb.append("pop {");
		bool first = true;
		for (reg r : *list) {
			if (!first)
				sb.append(",");
			else
				first = false;
			sb.append(regtostring[r]);
		}
		sb.append("}\n");
		return sb;
	}
};

class globalStmt :public armStmt{
public:
	std::string name;
	globalStmt(std::string name) {
		this->name = name;
	}
	std::string render() {
		return ".global " + name+"\n";
	}
};

class armstring :public armStmt {
public:
	std::string str;
	armstring(std::string str) {
		this->str = str;
	}
	std::string render() {
		return str + "\n";
	}
};
#endif // !"ARM_H"

//int main(){int a=1;int b=a;}a