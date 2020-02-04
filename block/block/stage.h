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


std::wstring t;
void FileInit() {
	std::wifstream fin(L"./data/s1.sc");
	fin.imbue(std::locale("chs"));
	fin >> t;
}

class GameText {
public:
	GameText() {
		text.Create(40 + 30, 340 + 15, 410, 450, 17);
		background = Bitmap(L"./src/textbg.png");
		BmpInit(background);

		myGFactory->CreateBrush(blue, _COLOR(Aqua));
		myGFactory->CreateBrush(red, _COLOR(Red));

		leftImg = new Bitmap(L"./src/boss/reimu/0.png");
		BmpInit(*leftImg);
		rightImg = new Bitmap(L"./src/boss/mokou/0.png");
		BmpInit(*rightImg);

		left = nullptr;
		right = nullptr;
		fin = nullptr;
	}

	~GameText() {
	}

	void Load(LPCWSTR path) {
		delete left;
		left = new Sprite(30, 100, leftImg, DefaultShow, DefaultUpdate, 128 * 0.95, 256 * 0.95);
		delete right;
		right = new Sprite(200, 100, rightImg, DefaultShow, DefaultUpdate, 256 * 0.95, 256 * 0.95);

		delete fin;
		fin = new std::wifstream(path);
		fin->imbue(std::locale("chs"));
		(*fin) >> num;
	}

	void Next() {
		if (!IsOver()) {
			(*fin) >> side;
			(*fin) >> now;
			num--;
		}
	}

	void Show() {
		if (side) {
			left->opacity = 0.5;
			right->opacity = 1;
		}
		else {
			left->opacity = 1;
			right->opacity = 0.5;
		}
		left->Show();
		right->Show();
		myGFactory->DrawBitmap(background, 40, 340, 410, 450);
		if (side) {
			myGFactory->WriteW(text, red, now.c_str());
		}
		else {
			myGFactory->WriteW(text, blue, now.c_str());
		}
	}

	bool IsOver() {
		return num == 0;
	}

private:
	Bitmap * leftImg;
	Bitmap * rightImg;
	Sprite * left;			//左侧人物显示
	Sprite * right;			//右侧人物显示
	bool side;				//目前说话者

	Bitmap background;		//文字背景
	Text text;
	Brush blue;
	Brush red;
	//Brush blue, gray;
	std::wifstream* fin;	
	std::wstring now;		//目前渲染的文字
	int num;				//文档总行数
};

GameText *myGameText;

class Stage {
public:
	Stage() {
		poolPtr = nullptr;
	}

	~Stage() {
		delete poolPtr;
	}

	void Load(LPCWSTR path) {
		delete poolPtr;
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

