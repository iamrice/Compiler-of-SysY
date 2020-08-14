#ifndef BLOCKGEN_H
#define BLOCKGEN_H
#include<list>
#include"ir.h"
class BlockGen
{
public:
	std::list<irBlock*>* newBlocks = new std::list<irBlock*>();
	void newGen(Meth* meth)
	{
		irBlock* temp = new irBlock(new std::list<irStmt*>());
		for (irBlock* block : *(meth->blocks))
		{
			for (irStmt* stmt : *(block->stmts))
			{
				if (dynamic_cast<LabelStmt*>(stmt) != nullptr)
				{
					newBlocks->push_back(temp);
					temp = new irBlock(new std::list<irStmt*>());
					temp->label = dynamic_cast<LabelStmt*>(stmt);
				}
				temp->stmts->push_back(stmt);
			}
		}
		newBlocks->push_back(temp);
		meth->blocks = newBlocks;
	}
};







#endif