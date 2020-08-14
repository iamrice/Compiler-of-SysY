#ifndef FLOWPASS_H
#define FLOWPASS_H
#include <list>
#include "ir.h"
#include "blockGen.h"
#include <iostream>
#include <string>
#include<set>
#include<map>

class FlowPass
{
public:
	std::list<LabelStmt*>* blockLabels = new std::list<LabelStmt*>();//store the label temporarily
	std::list<irStmt*>* blockStmts = new std::list<irStmt*>();//store the statement temporarily
	std::set<LabelStmt*>* usedLabels = new std::set<LabelStmt*>();//store the label of Jump Statement
	std::map<LabelStmt*, irBlock*>* labelToBlock = new std::map<LabelStmt*, irBlock*>();
	std::list<irBlock*>* blocks = new std::list<irBlock*>();
	std::list<irBlock*>* blocksPre = new std::list<irBlock*>();
	std::list<irBlock*>* blocksPo = new std::list<irBlock*>();
	std::list<irBlock*>* blocksRpo = new std::list<irBlock*>();
	std::set<irBlock*>* visited = new std::set<irBlock*>();
	int blockIndex = 0;
	int postorderIndex = 0;

	void run(Meth* meth)
	{
		for (irBlock* block : *(meth->blocks))
		{
			for (irStmt* stmt : *(block->stmts))
			{
				//first store the jumpstmt to the use
				if (dynamic_cast<JumpStmt*>(stmt) != nullptr)
				{
					LabelStmt* label = ((JumpStmt*)(stmt))->label;
					usedLabels->insert(label);
				}
			}
		}

		makeBlock();

		for (irBlock* block : *(meth->blocks))
		{
			if (block->label != nullptr)
			{
				doLabel(block->label);
			}
			for (irStmt* stmt : *(block->stmts))
			{
				if (dynamic_cast<LabelStmt*>(stmt) != nullptr)
				{
					doLabel((LabelStmt*)(stmt));
				}
				else
				{
					blockStmts->push_back(stmt);
					if (dynamic_cast<CmpStmt*>(stmt) != nullptr || dynamic_cast<GotoStmt*>(stmt) != nullptr || dynamic_cast<ir_return*>(stmt) != nullptr || dynamic_cast<ir_return_rval*>(stmt) != nullptr)
					{
						makeBlock();
					}
				}
			}
		}

		if (!(blockStmts->empty()))
			makeBlock();
		
		std::list<irBlock*>::iterator t1;
		for (t1 = blocks->begin(); t1 != blocks->end();)
		{
			irBlock* block = *(t1);
			if (block->stmts->empty())
			{
				irBlock* nextBlock = *(++t1);
				block->stmts->push_back(new GotoStmt(nextBlock->label));
				block->outgoingDirect = nextBlock;
				block->outgoingCond = nullptr;
				continue;
			}

			std::list<irStmt*>::iterator t2 = block->stmts->end();
			irStmt* lastStmt = *(--t2);
			if (dynamic_cast<CmpStmt*>(lastStmt) != nullptr)
			{
				irBlock* nextBlock = *(++t1);
				t1--;
				std::map<LabelStmt*, irBlock*>::iterator t3;
				t3 = labelToBlock->find(((JumpStmt*)(lastStmt))->label);
				irBlock* targetBlock;
				if (t3 != labelToBlock->end())
					targetBlock = t3->second;
				else targetBlock = nullptr;
				block->outgoingDirect = nextBlock;
				block->outgoingCond = targetBlock;
				(dynamic_cast<JumpStmt*>(lastStmt))->label = targetBlock->label;
			}
			else if (dynamic_cast<GotoStmt*>(lastStmt) != nullptr)
			{
				std::map<LabelStmt*, irBlock*>::iterator t3;
				t3 = labelToBlock->find(((GotoStmt*)(lastStmt))->label);
				irBlock* targetBlock;
				if (t3 != labelToBlock->end())
					targetBlock = t3->second;
				else targetBlock = nullptr;
				block->outgoingDirect = targetBlock;
				block->outgoingCond = nullptr;
				(dynamic_cast<JumpStmt*>(lastStmt))->label = targetBlock->label;
			}
			else if (dynamic_cast<ir_return*>(lastStmt) != nullptr || dynamic_cast<ir_return_rval*>(lastStmt) != nullptr) {}
			else
			{
				irBlock* nextBlock = *(++t1);
				t1--;
				block->stmts->push_back(new GotoStmt(nextBlock->label));
				block->outgoingDirect = nextBlock;
				block->outgoingCond = nullptr;

			}
			t1++;
		}
		
		visited = new std::set<irBlock*>();
		postorderIndex = 0;
		if (!(blocks->empty()))
		{
			dfs(*(blocks->begin()));
			std::list<irBlock*>::iterator it;
			for (it = blocksPo->end(); it != blocksPo->begin(); it--)
				blocksRpo->push_back(*(it));
		}
		std::list<irBlock*>* newBlocks = new std::list<irBlock*>();
		for (irBlock* block : *(blocks))
		{
			if (visited->count(block))
			{
				newBlocks->push_back(block);
			}
		}
		blocks = newBlocks;
		/*for (irBlock* ib : *newBlocks) std::cout << ib->render(0);
		for (irBlock* block : *(blocks))
		{
			if (block->outgoingDirect != nullptr)
				block->outgoingDirect->incoming->push_back(block);
			if (block->outgoingCond != nullptr)
				block->outgoingCond->incoming->push_back(block);
		}*/

		int blockIndex = 0;
		for (irBlock* block : *(blocks))
		{
			block->label->name = "B" + std::to_string(blockIndex++);
		}

		meth->blocks = blocks;
		meth->blocksPre = blocksPre;
		meth->blocksPo = blocksPo;
		meth->blocksRpo = blocksRpo;//update
		
	}
		void makeBlock()
		{
			irBlock* block = new irBlock(blockStmts);
			// Map the block's labels to the block
			for (LabelStmt* label : *blockLabels)
				labelToBlock->insert(std::make_pair(label, block));
			// Create a label for the block
			std::string labelTemp = "B" + std::to_string(blockIndex++);
			block->label = new LabelStmt(labelTemp);
			blocks->push_back(block);

			blockStmts = new std::list<irStmt*>();
			blockLabels = new std::list<LabelStmt*>();
		}

		void doLabel(LabelStmt* label)
		{
			// Ignore labels that are not actually used
			if (usedLabels->find(label) == usedLabels->end()) return;
			if (!(blockStmts->empty())) makeBlock();
			blockLabels->push_back(label);
		}

		void dfs(irBlock* block)
		{
			visited->insert(block);
			blocksPre->push_back(block);
			if (block->outgoingDirect != nullptr && (visited->find(block->outgoingDirect) == visited->end()))
				dfs(block->outgoingDirect);
			if (block->outgoingCond != nullptr && (visited->find(block->outgoingCond) == visited->end()))
				dfs(block->outgoingCond);
			blocksPo->push_back(block);
			block->postorderIndex = postorderIndex++;
		}
};

#endif