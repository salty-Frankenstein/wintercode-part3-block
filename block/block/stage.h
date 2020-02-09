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
	if (t->x < 0 || t->x > 420 || t->y < -10 || t->y > 470)
		t->del = true;
}

void BossShow(Boss* t) {
	static double hp_x = 415;
	DefaultShow(t);
	if (hp_x > 415 * (1.0*t->HP_now / t->HP_max))
		hp_x -= 0.2 * (hp_x - (hp_x + 415 * (1.0*t->HP_now / t->HP_max)) / 2);
	
	myGFactory->DrawBitmap(t->HP_Img, 30, 15, 30 + hp_x, 20);
}

void BossUpdate(Boss* t) {
	if (t->HP_now < 0) {
		if (!t->sound) {
			bossepSE->Play();
			t->sound = true;
		}
		t->opacity -= 0.05;
		
	}
	if (t->IsDead())
		t->del = true;
}

Boss * mokou = new Boss(200, 60, mokouSImg, BossShow, BossUpdate, 71 * 0.8, 119 * 0.8, 1000);

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


class Stage {
public:
	Stage() {
		stageNum = 0;
		poolPtr = nullptr;
		textPtr = new GameText;
	}

	~Stage() {
		delete poolPtr;
		delete textPtr;
	}

	void Load() {
		delete poolPtr;
		poolPtr = new ObjectBuffer;
		blocks.clear();
		
		switch (stageNum)
		{
		case 3:	//妹红
			boss = mokou;
			poolPtr->AddSon(boss);
			textPtr->Load(L"./data/s1.script");
			textPtr->Next();
			break;
		default:
			boss = nullptr;

			std::string path = "./data/" + std::to_string(stageNum) + ".blk";
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
			break;
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
		myGFactory->DrawBitmap(mokouSCImg, 40, 30, 40+364, 30+18);
	}

	void Update() {
		blocks.remove_if([](Object* x) {return x->del; });
		poolPtr->Update();
		switch (stageNum)
		{
		case 3:	//boss1 妹红
			if (!textPtr->IsOver()) {
				if (getKey['Z'] && gameTimer % 5 == 0)
					textPtr->Next();
				break;
			}
			if (boss->GetLiveTime() % (60 * 3) == 10) {
				tanSE->Play();
				std::string path = "./data/" + std::to_string(stageNum) + ".blk";
				std::ifstream in(path);
				int num;
				in >> num;
				for (int i = 1; i <= num; i++) {
					float tx, ty;
					int rank;
					in >> tx >> ty >> rank;
					blocks.push_back(new Block(boss->x + tx - 30 *3, boss->y + ty, BlockShow, BlockUpdate, rank));
					poolPtr->AddSon(blocks.back());
				}
			}

			if (boss->GetLiveTime() / 70 % 8 == 0) {
				boss->x++;
			}
			else if (boss->GetLiveTime() / 70 % 8 == 4) {
				boss->x--;
			}
			else if (boss->GetLiveTime() / 70 % 8 == 2) {
				boss->x--;
			}
			else if (boss->GetLiveTime() / 70 % 8 == 6) {
				boss->x++;
			}

			if (boss->GetLiveTime() / 42 % 8 == 0) {
				boss->y++;
			}
			else if (boss->GetLiveTime() / 42 % 8 == 4) {
				boss->y--;
			}
			else if (boss->GetLiveTime() / 42 % 8 == 2) {
				boss->y--;
			}
			else if (boss->GetLiveTime() / 42 % 8 == 6) {
				boss->y++;
			}
			

			for (auto i = blocks.begin(); i != blocks.end(); i++) {
				//(*i)->x++;
				(*i)->y++;
			}
			break;
		default:
			break;
		}
	}

	bool IsOver() {
		if(!IsBossStage())
			return blocks.size() == 0;
		return boss->IsDead();
	}

	int BlockNum() {
		return blocks.size();
	}

	void Next() {
		if(stageNum <= 3)
			stageNum++;
	}

	bool IsGameOver() {
		return stageNum == 4;
	}

	int GetStageNum() {
		return stageNum;
	}

	double x, y;	//渲染的开始坐标
	Boss *boss;
	GameText * textPtr;

private:
	bool IsBossStage() {
		return stageNum == 3;
	}

	ObjectBuffer* poolPtr;
	std::list<Block*> blocks;
	int stageNum;
};

#endif // !STAGE_H

