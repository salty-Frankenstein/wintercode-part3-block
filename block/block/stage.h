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
	if (t->x < 0 || t->x > 500 || t->y < -10 || t->y > 470)
		t->del = true;
}

void BossShow(Boss* t) {
	static double hp_x = 390;
	DefaultShow(t);
	if (hp_x > 390 * (1.0*t->HP_now / t->HP_max))
		hp_x -= 0.2 * (hp_x - (hp_x + 390 * (1.0*t->HP_now / t->HP_max)) / 2);
	
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
Boss * pachi = new Boss(200, 60, pachiSImg, BossShow, BossUpdate, 98 * 0.45, 202 * 0.45, 1500);
Boss * utsuho = new Boss(200, 60, utsuhoSImg, BossShow, BossUpdate, 100 * 0.8, 120 * 0.8, 2500);

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
		rightImg = new Bitmap(L"./src/boss/pachi/0.png");
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
		//right = new Sprite(200, 100, rightImg, DefaultShow, DefaultUpdate, 256 * 0.95, 256 * 0.95);
		right = new Sprite(290, 100, rightImg, DefaultShow, DefaultUpdate, 128 * 0.95, 256 * 0.95);
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

struct BlockSet {	//砖块对象的集合，用于整体操作
	BlockSet(double _x, double _y) {
		x = _x;
		y = _y;
	}

	void AddBlock(Block* t) {
		blockList.push_back(t);
	}

	void Translate(double dx, double dy) {
		x += dx;
		y += dy;
		for (auto i = blockList.begin(); i != blockList.end(); i++) {
			(*i)->x += dx;
			(*i)->y += dy;
		}
	}

	void Rotate(double angle) {
		for (auto i = blockList.begin(); i != blockList.end(); i++) {
			double tx = (*i)->x - x, ty = (*i)->y - y, ttx, tty;
			ttx = tx * cos(angle) - ty * sin(angle);
			tty = tx * sin(angle) + ty * cos(angle);
			(*i)->x = ttx + x;
			(*i)->y = tty + y;
		}
	}

	bool IsDeleted() {
		blockList.remove_if([](Object* x) {return x->del; });
		return blockList.empty();
	}

	std::list<Block*> blockList;
	double x, y;
};

class Stage {
public:
	Stage() {
		stageNum = 8;
		poolPtr = nullptr;
		textPtr = new GameText;
		spellCard = new Sprite(40, 25, INVISIBLE_IMG, DefaultShow, DefaultUpdate, 364, 18);
	}

	~Stage() {
		delete poolPtr;
		delete textPtr;
	}

	void Load() {
		delete poolPtr;
		poolPtr = new ObjectBuffer;
		blocks.clear();
		blockSets.clear();
		
		switch (stageNum)
		{
		case 3:	//妹红
			boss = mokou;
			poolPtr->AddSon(boss);
			textPtr->Load(L"./data/s1.script");
			textPtr->Next();
			spellCard->image = &mokouSCImg;
			break;
		case 6:	//姆Q
			boss = pachi;
			poolPtr->AddSon(boss);
			textPtr->Load(L"./data/s2.script");
			textPtr->Next();
			spellCard->image = &pachiSCImg;
			break;
		case 9:	//阿空
			boss = utsuho;
			poolPtr->AddSon(boss);
			textPtr->Load(L"./data/s3.script");
			textPtr->Next();
			spellCard->image = &utsuhoSC1Img;
			break;
		default:
			if (stageNum == 1)mokouMidBgm->Play();
			else if (stageNum == 4) { mokouBgm->Stop(); pachiMidBgm->Play(); }
			else if (stageNum == 7) { pachiBgm->Stop(); utsuhoMidBgm->Play(); }
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
		if (IsBossStage() && boss->setTime)spellCard->Show();
	}

	void Update() {
		blocks.remove_if([](Object* x) {return x->del; });
		blockSets.remove_if([](BlockSet& x) {return x.IsDeleted(); });
		poolPtr->Update();
		
		switch (stageNum)
		{
		case 3:	//boss1 妹红
			if (!textPtr->IsOver()) {
				if (getKey['Z'] && gameTimer % 5 == 0)
					textPtr->Next();
				if (textPtr->IsOver()) {
					mokouMidBgm->Stop();
					mokouBgm->Play();
				}
				break;
			}
			boss->SetTime();
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

			BossMove();

			for (auto i = blocks.begin(); i != blocks.end(); i++) {
				(*i)->y++;
			}
			break;
		case 6:	//姆Q
			if (!textPtr->IsOver()) {
				if (getKey['Z'] && gameTimer % 5 == 0)
					textPtr->Next();
				if (textPtr->IsOver()) {
					pachiMidBgm->Stop();
					pachiBgm->Play();
				}
				break;
			}
			boss->SetTime();
			int t;
			t = boss->GetLiveTime() % (60 * 3);
			if (t == 10 || t == 20 || t == 30) {
				int dx, drank;
				if (t == 10)dx = -70, drank = 0;
				else if (t == 20)dx = 0, drank = 1;
				else dx = 70, drank = 2;
				tanSE->Play();
				std::string path = "./data/" + std::to_string(stageNum) + ".blk";
				std::ifstream in(path);
				int num;
				in >> num;
				blockSets.push_back(BlockSet(boss->x + 10 + dx, boss->y + 100));
				for (int i = 1; i <= num; i++) {
					float tx, ty;
					int rank;
					in >> tx >> ty >> rank;
					blocks.push_back(new Block(tx + (blockSets.back().x) - 100, ty + (blockSets.back().y - 100),
						BlockShow, BlockUpdate, rank + drank));
					blockSets.back().AddBlock(blocks.back());
					poolPtr->AddSon(blocks.back());

				}
			}
			
			t = boss->GetLiveTime() / 20;
			if (boss->GetLiveTime() % 20 == 0) {	//散弹
				blocks.push_back(new Block(30 + t % 6 / 6.0*(415 - 30), 15, BlockShow, 
					[](Block* t) {t->y += 1; BlockUpdate(t); }, t % 4 + 1));
				poolPtr->AddSon(blocks.back());
			}

			BossMove();
			for (auto i = blockSets.begin(); i != blockSets.end(); i++) {
				if((*i).blockList.front()->rank==1)
					(*i).Translate(-1.5, 1.5);
				else if ((*i).blockList.front()->rank == 3)
					(*i).Translate(1.5, 1.5);
				else (*i).Translate(0, 1.5);
				(*i).Rotate(2 * 3.14 /180);
			}
			
			break;
		case 9:	//阿空
			if (!textPtr->IsOver()) {
				if (getKey['Z'] && gameTimer % 5 == 0)
					textPtr->Next();
				if (textPtr->IsOver()) {
					utsuhoMidBgm->Stop();
					utsuhoBgm->Play();
				}
				break;
			}
			boss->SetTime();
			
			if (boss->HP_now > boss->HP_max * 0.5) {	//SC1
				if (boss->GetLiveTime() % (60 * 2) == 10) {
					tanSE->Play();
					std::string path = "./data/" + std::to_string(stageNum) + ".blk";
					std::ifstream in(path);
					int num;
					in >> num;
					blockSets.push_back(BlockSet(150, 0));
					for (int i = 1; i <= num; i++) {
						float tx, ty;
						int rank;
						in >> tx >> ty >> rank;
						blocks.push_back(new Block(tx*0.8 + (blockSets.back().x) + 100, ty*0.8 + (blockSets.back().y + 150),
							BlockShow, BlockUpdate, rank, 40, 40));
						blockSets.back().AddBlock(blocks.back());
						poolPtr->AddSon(blocks.back());
					}
				}

				t = boss->GetLiveTime() / 40;
				if (boss->GetLiveTime() % 40 == 0) {	//散弹
					void(*update[6])(Block*);
					update[0] = [](Block* t) {t->x += 2.5 * cos(60 * 3.14 / 180); t->y += 2.5 * sin(60 * 3.14 / 180); BlockUpdate(t); };
					update[1] = [](Block* t) {t->x += 2.5 * cos(2 * 60 * 3.14 / 180); t->y += 2.5 * sin(2 * 60 * 3.14 / 180); BlockUpdate(t); };
					update[2] = [](Block* t) {t->x += 2.5 * cos(3 * 60 * 3.14 / 180); t->y += 2.5 * sin(3 * 60 * 3.14 / 180); BlockUpdate(t); };
					update[3] = [](Block* t) {t->x += 2.5 * cos(4 * 60 * 3.14 / 180); t->y += 2.5 * sin(4 * 60 * 3.14 / 180); BlockUpdate(t); };
					update[4] = [](Block* t) {t->x += 2.5 * cos(5 * 60 * 3.14 / 180); t->y += 2.5 * sin(5 * 60 * 3.14 / 180); BlockUpdate(t); };
					update[5] = [](Block* t) {t->x += 2.5 * cos(6 * 60 * 3.14 / 180); t->y += 2.5 * sin(6 * 60 * 3.14 / 180); BlockUpdate(t); };
					for (int i = 0; i < 6; i++) {
						blocks.push_back(new Block(boss->x + boss->width*0.5, boss->y + boss->height*0.5, BlockShow,
							update[i], t % 4 + 1));
						poolPtr->AddSon(blocks.back());
					}
				}

				BossMove();
				for (auto i = blockSets.begin(); i != blockSets.end(); i++) {
					(*i).y -= 0.5;
					(*i).Rotate(0.25 * 3.14 / 180);
				}
			}
			else {	//SC2
				LoadSC2();
				t = boss->GetLiveTime() / 40;
				if (boss->GetLiveTime() % 40 == 0)
					tanSE->Play();
				if (boss->GetLiveTime() % 20 == 0) {
					
					void(*update[6])(Block*);
					update[0] = [](Block* t) {t->x += 1 * cos(60 * 3.14 / 180); t->y += 1 * sin(60 * 3.14 / 180); BlockUpdate(t); };
					update[1] = [](Block* t) {t->x += 1 * cos(2 * 60 * 3.14 / 180); t->y += 1 * sin(2 * 60 * 3.14 / 180); BlockUpdate(t); };
					update[2] = [](Block* t) {t->x += 1 * cos(3 * 60 * 3.14 / 180); t->y += 1 * sin(3 * 60 * 3.14 / 180); BlockUpdate(t); };
					update[3] = [](Block* t) {t->x += 1 * cos(4 * 60 * 3.14 / 180); t->y += 1 * sin(4 * 60 * 3.14 / 180); BlockUpdate(t); };
					update[4] = [](Block* t) {t->x += 1 * cos(5 * 60 * 3.14 / 180); t->y += 1 * sin(5 * 60 * 3.14 / 180); BlockUpdate(t); };
					update[5] = [](Block* t) {t->x += 1 * cos(6 * 60 * 3.14 / 180); t->y += 1 * sin(6 * 60 * 3.14 / 180); BlockUpdate(t); };
					blockSets.push_back(BlockSet(boss->x + boss->width*0.5, boss->y + boss->height*0.5));
					for (int i = 0; i < 6; i++) {
						blocks.push_back(new Block(blockSets.back().x, blockSets.back().y, BlockShow,
							update[i], t % 4 + 1));
						blockSets.back().AddBlock(blocks.back());
						poolPtr->AddSon(blocks.back());
					}
				}
				for (auto i = blockSets.begin(); i != blockSets.end(); i++) {
					//(*i).y -= 0.5;
					//(*i).Translate(0, 1);
					
					if(boss->GetLiveTime()/360 %2 == 0)
						(*i).Rotate((4 * (*i).blockList.front()->x/400) * 0.25 * 3.14 / 180);
					else (*i).Rotate(-(4 * (*i).blockList.front()->x / 400) * 0.25 * 3.14 / 180);
				}
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
		if(stageNum <= 9)
			stageNum++;
	}

	bool IsGameOver() {
		return stageNum == 10;
	}

	int GetStageNum() {
		return stageNum;
	}

	double x, y;	//渲染的开始坐标
	Boss *boss;
	GameText * textPtr;

private:
	void BossMove() {
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
	}

	bool IsBossStage() {
		return stageNum == 3 || stageNum == 6 || stageNum == 9;
	}

	void LoadSC2() {
		static bool loaded = false;
		if (!loaded) {
			for (auto i = blocks.begin(); i != blocks.end(); i++)
				(*i)->rank = 0;
			spellCard->image = &utsuhoSC2Img;
			alertSE->Play();
			boss->x = 180;
			boss->y = 60;
			loaded = true;
		}
	}
	
	ObjectBuffer* poolPtr;
	std::list<Block*> blocks;
	std::list<BlockSet> blockSets;
	Sprite * spellCard;
	int stageNum;
};

#endif // !STAGE_H

