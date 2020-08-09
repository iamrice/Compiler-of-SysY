#ifndef IR_H
#define IR_H
#include <string>
#include <list>

class ir {
};

enum type{_void,_int};
enum binaryOp { _PLUS, _MINUS, _MUL, _DIV, _MOD };
enum unaryOp { _POS, _NEG, _NOT };
enum condOp { _EQ, _NE, _LT, _GT, _LE, _GE };

std::string doIndent(std::string sb, int indent) {
	while (indent > 0) {
		sb.append("  ");
		indent--;
	}
	return sb;
}

/*class typ {
public :
	type type;
	
	std::string render(int indent) {
		std::string sb = doIndent(sb,indent);
		if (type == _void) {
			sb.append("void");
		}
		if (type == _int) {
			sb.append("int");
		}
		return sb;
	}
};*/

class irStmt {
public:
	virtual std::string render(int indent) = 0;
};

class Var {
public :
	std::string name;
	int address;
	bool if_global;
	bool if_const=false;
	int instanceValue;

	Var(std::string name,bool global=false) {
		this->name = name;
		this->if_global = global;
	}

	std::string render() {
		return name;
		/*if (name[0] == 't')
			return name;
		else
			return "var";*/
	}
};

class arrayVar {
public:
	std::string name;
	int address;
	std::list<int>* dimentions;
	int totalSize;
	bool if_global;
	arrayVar(std::string name, std::list<int>* dimentions,bool global=false) {
		this->name = name;
		this->dimentions=dimentions;
		this->if_global = global;
	}
};

class Rval {
public:
	virtual std::string render() = 0;
	//virtual type getTyp() = 0;
};

class IntLitRval :public  Rval {
public:
	int i;
	IntLitRval(int i) {
		this->i = i;
	}
	std::string render() {
		return "" + std::to_string(i);
	}
};

class VarRval :public  Rval {
public:
	Var* v;
	VarRval(Var* v) {
		this->v = v;
	}
	std::string render() {
		return v->render();
	}

};

class arrayRval :public  Rval {
public:
	arrayVar* v;
	arrayRval(arrayVar* v) {
		this->v = v;
	}
	std::string render() {
		return v->name;
	}

};

class irDecl :public irStmt {
public:
	virtual std::string render(int indent) = 0;
};

class irVarDecl :public irDecl {
public:
	Var* var;
	irVarDecl(Var* var) {
		this->var = var;
	}
	std::string render(int indent) {
		std::string sb = doIndent("", indent);
		sb.append("int ").append(var->name).append(";\n");
		return sb;
	}
};

class irArrayDecl :public irDecl {
public:
	arrayVar* arr;
	int size;

	irArrayDecl(arrayVar* arr_name) {
		this->arr = arr_name;
		
		size = 0;
	}
	std::string render(int indent) {
		std::string sb = doIndent("", indent);
		sb.append("int ").append(arr->name);
		for (int r : *arr->dimentions) {
			sb.append("[").append(std::to_string(r)+"").append("]");
		}
		sb.append(";\n");
		return sb;

	}
};

/*class Data{
public :
	std::string cname;
	std::list<DataField>* fields;

	Data(std::string cname, std::list<DataField> fields) {
		this->cname = cname;
		//this->fields = fields;
		this->fields = new std::list<DataField>(fields);
	}

	std::string render(int indent) {
		std::string sb;
		sb=doIndent(sb, indent);
		sb.append("Data3 ").append(cname).append(" {\n");
		for (DataField dataField :  *fields) {
			sb.append(dataField.render(indent + 1));
		}
		sb=doIndent(sb, indent);
		sb.append("}\n");
		return sb;
	}
};

class DataField{
public :
	int val;
	std::string name;
	
	DataField(std::string name, int val = 0) {
		this->name = name;
		this->val = val;
	}

	std::string render(int indent) {
		std::string sb = "";
		sb=doIndent(sb, indent);
		sb.append("int").append(" ").append(name).append("=").append(std::to_string(val)).append(";\n");
		return sb;
	}
};*/

/*class irStmt {
public:
	int a;
	virtual std::string render(int indent) = 0;
};*/

class LabelStmt:public  irStmt {
public :
	//LabelStmt* a;
	std::string name;
	LabelStmt(std::string name) {
		this->name = name;
	}
	std::string render(int indent) {
		std::string sb = doIndent("\n", indent);
		sb.append(name + ": \n");
		return sb;
	}
};

class numberAssignStmt :  public irStmt {
public :
	Rval* src;
	Var* def;
	numberAssignStmt(Var* dst, Rval* src) {
		def = dst;
		this->src = src;
	}
	std::string render(int indent) {
		std::string sb = doIndent("", indent);
		sb.append(def->name).append("=").append(src->render()).append(";\n");
		return sb;
	}
};

class arrayInitStmt:public irStmt {
public:
	irArrayDecl* arr;
	std::list<Rval*>* vals;
	arrayInitStmt(irArrayDecl* arr, std::list<Rval*>* vals) {
		this->arr = arr;
		this->vals=vals;
	}
	std::string render(int indent) {
		std::string sb = doIndent("", indent);
		sb.append(arr->arr->name).append("={");
		int i = 0;
		for (Rval* r : *vals) {
			if (i == 0) {
				i++;
			}
			else {
				sb.append(",");
			}
			sb.append(r->render());
		}
		sb.append("};\n");
		return sb;
	}
};

class arrayAssignStmt : public irStmt {
public:
	Var* def;
	arrayVar* arr;
	std::list<Rval*>* _list;
	arrayAssignStmt(Var* def, arrayVar* arr_id,std::list<Rval*>* _list) {
		this->def = def;
		this->arr = arr_id;
		this->_list = _list;
	}
	std::string render(int indent) {
		std::string sb = doIndent("", indent);
		sb.append(def->render()).append("=").append(arr->name);
		for (Rval* r:*_list) {
			sb.append("[" + r->render() + "]");
		}
		sb.append(";\n");
		return sb;
	}
};

class arrayAssignStmt2 : public irStmt {
public:
	arrayVar* arr;
	std::list<Rval*>* _list;
	Rval* val;
	arrayAssignStmt2(arrayVar* arr_id, std::list<Rval*>* _list,Rval* val) {
		this->arr = arr_id;
		this->_list = _list;
		this->val = val;
	}
	std::string render(int indent) {
		std::string sb = doIndent("", indent);
		sb.append(arr->name);
		for (Rval* r : *_list) {
			sb.append("[" + r->render() + "]");
		}
		sb.append("=").append(val->render());
		sb.append(";\n");
		return sb;
	}
};

class voidFuncCallStmt :public irStmt {
public:
	std::list<Rval*>* paramR;
	std::string name;
	voidFuncCallStmt(std::list<Rval*>* paramR, std::string name) {
		this->paramR=paramR;
		this->name = name;
	}
	std::string render(int indent) {
		std::string sb = doIndent("", indent);
		sb.append(name+"(");
		for (Rval* r : *paramR) {
			sb.append( r->render() + ",");
		}
		sb.append(");\n");
		return sb;
	}
};

class intFuncCallStmt :public irStmt {
public:
	std::list<Rval*>* paramR;
	std::string name;
	Var* a;
	intFuncCallStmt(std::list<Rval*>* paramR, std::string name,Var* a) {
		this->paramR=paramR;
		this->name=name;
		this->a = a;
	}
	std::string render(int indent) {
		std::string sb = doIndent("", indent);
		sb.append(a->name+"="+name + "(");
		for (Rval* r : *paramR) {
			sb.append(r->render() + ",");
		}
		sb.append(");\n");
		return sb;
	}
};

class binaryStmt :public irStmt {
public:
	binaryOp op;
	Rval* a;
	Rval* b;
	Var* c;
	binaryStmt(Rval* a, Rval* b, Var* c,binaryOp op) {
		this->a = a;
		this->b = b;
		this->c = c;
		this->op = op;
	}

	std::string render(int indent) {
		std::string sb = doIndent("", indent);		
		sb.append(c->name).append("=").append(a->render()); 
		switch (op)
		{
		case _PLUS:
			sb.append("+");
			break;
		case _MINUS:
			sb.append("-");
			break;
		case _MUL:
			sb.append("*");
			break;
		case _DIV:
			sb.append("/");
			break;
		case _MOD:
			sb.append("%");
			break;
		default:
			break;
		}
		sb.append(b->render()).append(";\n");
		return sb;
	}
};

class unaryStmt :public irStmt {
public:
	unaryOp op;
	Rval* b;
	Var* c;
	unaryStmt(Var* c,unaryOp op, Rval* b) {
		this->b = b;
		this->c = c;
		this->op = op;
	}

	std::string render(int indent) {
		std::string sb = doIndent("", indent);
		sb.append(c->name).append("=");
		switch (op)
		{
		case _POS:
			sb.append("+");
			break;
		case _NEG:
			sb.append("-");
			break;
		case _NOT:
			sb.append("!");
			break;
		default:
			break;
		}
		sb.append(b->render()).append(";\n");
		return sb;
	}
};

class JumpStmt :public  irStmt {
public :
	LabelStmt* label;
};

class CmpStmt :public  JumpStmt {
public :
	condOp op;
	Rval* a;
	Rval* b;

	CmpStmt(condOp op, Rval* a, Rval*b, LabelStmt* label) {
		this->op = op;
		this->a = a;
		this->b = b;
		this->label = label;
	}

	std::string render(int indent) {
		std::string sb = doIndent("", indent);
		sb.append("if (");
		sb.append(a->render());
		sb.append(" ");
		switch (op)
		{
		case _EQ:
			sb.append("==");
			break;
		case _NE:
			sb.append("!=");
			break;
		case _GT:
			sb.append(">");
			break;
		case _LT:
			sb.append("<");
			break;
		case _LE:
			sb.append("<=");
			break;
		case _GE:
			sb.append(">=");
			break;
		default:
			break;
		}
		sb.append(" ");
		sb.append(b->render());
		sb.append(") goto ");
		sb.append(label == nullptr ? "[NULL]" :  this->label->name);
		sb.append(";\n");
		return sb;
	}
};

class GotoStmt :public  JumpStmt {
public :
	GotoStmt(LabelStmt* label) {
		this->label = label;
	}
	std::string render(int indent) {
		std::string sb = doIndent("", indent);
		sb.append("goto ").append(this->label == nullptr ? "[Null]" :  label->name).append(";\n");
		return sb;
	}
};


class ir_return :public irStmt {
public:
	std::string render(int a) {
		std::string sb = doIndent("", a);
		sb.append("return;\n");
		return sb;
	}
};

class ir_return_rval :public irStmt {
public:
	Rval* val;
	ir_return_rval(Rval* val) {
		this->val = val;
	}
	std::string render(int a) {
		std::string sb = doIndent("", a);
		sb.append("return ").append(val->render()).append(";\n");
		return sb;
	}
};

class irBlock {
public:
	//irBlock* a;
	std::list<irStmt*>* stmts;
	LabelStmt* label;

	irBlock(std::list<irStmt*>* stmts) {
		this->stmts = stmts;
	}

	std::string render(int indent) {
		std::string sb = "";
		sb = doIndent(sb, indent);
		/*if (label != nullptr)
			sb.append(label->render(indent));
		for (irStmt* stmt :  *stmts) {
			sb.append(stmt->render(indent));
		}*/
		return sb;
	}
};

class Meth {
public:
	type retTyp;
	std::string name;
	std::list<irDecl*>* args;
	std::list<irBlock*>* blocks;
	bool jump;

	Meth(type retTyp, std::string name, std::list<irDecl*>* args, std::list<irStmt*>* stmts, bool jump) {
		this->retTyp = retTyp;
		this->name = name;
		this->args = args;
		this->jump = jump;
		blocks = new std::list<irBlock*>();
		/*for (irStmt* stmt : *stmts) {
			if (typeid(stmt).name() == "labelStmt") {

			}
		}*/
		irBlock* a = new irBlock(stmts);
		blocks->push_back(a);
	}

	std::string render(int indent) {
		std::string sb = doIndent("", indent);
		if (retTyp == _void)
			sb.append("void");
		else
			sb.append("int");
		sb.append(" ");
		//sb.append("FuncName");
		sb.append(name);
		sb.append("(");
		bool first = true;
		for (irDecl* d : *args) {
			if (first)
				first = false;
			else
				sb.append(",");
			std::string tmp = d->render(0);
			tmp = tmp.substr(0, tmp.size() - 2);
			sb.append(tmp);
		}
		sb.append("){\n");
		for (irStmt* s : *(blocks->front()->stmts)) {
			sb.append(s->render(indent + 1));
		}
		sb = doIndent(sb, indent);
		sb.append("}\n");
		return sb;
	}
};

class Prog {
public:
	std::list< irStmt* >* datas;
	std::list<Meth*>* meths;

	Prog(std::list<irStmt*>* datas, std::list<Meth*>* meths) {
		this->datas = datas;
		this->meths = meths;
	}

	std::string render(int indent) {
		std::string sb = "";

		for (irStmt* data :  (*datas)) {
			sb.append(data->render(indent));
		}
		for (Meth* meth :  (*meths)) {
			sb.append(meth->render(indent));
		}
		return sb;
	}
};

#endif // !IR_H
