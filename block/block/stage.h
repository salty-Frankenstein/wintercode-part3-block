/*						*\
		stage.h
		游戏关卡
	2020 wintercode
	by id:191220017
\*						*/
#pragma once
#ifndef STAGE_H
#define STAGE_H

#include "resources.h"

void BlockShow(Block* t) {
	if (t->rank >= 0) {
		t->image = Block::img[t->rank][int(gameTimer / (7 + (0.2*t->rank))) % 5 + 1];
		DefaultShow(t);
	}

}

void BlockUpdate(Block *t) {
	if (t->rank <= 0) {
		if (!t->sound) {
			enepSE->Play();
			t->sound = true;
		}
		t->opacity -= 0.05;
		if (t->opacity < 0)
			t->del = true;
	}
}

class Stage {
public:
	Stage() {
		poolPtr = nullptr;
	}

	~Stage() {
		delete poolPtr;
	}

	void Load(LPCWSTR path) {
		if(poolPtr != nullptr)delete poolPtr;
		poolPtr = new ObjectBuffer;
		blocks.clear();

		std::ifstream in(path);
		int num;
		in >> num;
		for (int i = 1; i <= num; i++) {
			float tx, ty;
			int rank;
			in >> tx >> ty >> rank;
			blocks.push_back(new Block(tx, ty, BlockShow, BlockUpdate, rank));
			poolPtr->AddSon(blocks.back());
		}
	}

	auto GetBlocksBegin() {
		return blocks.begin();
	}

	auto GetBlocksEnd() {
		return blocks.end();
	}
	
	void Show() {
		poolPtr->Show();
	}

	void Update() {
		blocks.remove_if([](Object* x) {return x->del; });
		poolPtr->Update();
	}

	bool IsOver() {
		return blocks.size() == 0;
	}

	int BlockNum() {
		return blocks.size();
	}

private:
	ObjectBuffer* poolPtr;
	std::list<Block*> blocks;
	
};

#endif // !STAGE_H

