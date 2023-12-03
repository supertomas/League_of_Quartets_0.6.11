#pragma once
# include <Siv3D.hpp>
#include"backGround.hpp"
#include"TextManager.hpp"
#include"Battle.hpp"
#include"Mobu.hpp"
#include"encount_rader.hpp"
#include"Special_Com.hpp"
#include"Exterior_object.hpp"
#include"Object.hpp"

struct changerect
{
	Rect rect;
	String Scene;
	Point nextpos;
};

class Field : public MyApp::Scene
{
public:
	std::shared_ptr<Player> player;
	Array<std::shared_ptr<Object>> objects;
	Array<std::shared_ptr<Object>> grounds;
	Array<std::shared_ptr<flower>> flowers;
	Audio townM;
	Vec2 changeBattle;
	std::vector<changerect> change_scene_rects;
	std::vector<String> battle_scenes;
	EncountRadar rader;
	bool is_encount_rader = false;
	CellManager cellManager;
	// コンストラクタ（必ず実装）
	Field(const InitData& init):
		IScene(init)
	{

	}

	void update() override
	{
		//rader.update(cellManager, changeBattle, player->distance);
		townM.play();
		for (auto& object : objects)
		{
			if (object->getName().includes(U"In"))
			{
				if (object->getName()[2] == '1')
				{
					changeScene(U"In");
					getData().pos = { -290,720 };
					getData().movement = player->movement;
				}
				else if (object->getName()[2] == '2')
				{
					changeScene(U"In2");
					getData().pos = { -290,720 };
					getData().movement = player->movement;
				}
				else if (object->getName()[2] == '3')
				{
					changeScene(U"In3");
					getData().pos = { -260,620 };
					getData().movement = player->movement;
				}
			}
			object->update(player);
		}
		std::sort(objects.begin(), objects.end(), [](std::shared_ptr<Object> a, std::shared_ptr<Object> b)
			{
				return a->pos.y < b->pos.y;
			});
		//次のフィールドに移り変わる処理
		for (auto& changerect : change_scene_rects)
		{
			if (player->getBody().intersects(changerect.rect))
			{
				changeScene(changerect.Scene);
				getData().pos = changerect.nextpos;
				getData().movement = player->movement;
			}
		}
		//フィールドのモンスターと戦うシーンに移り変わる処理
		for (auto& battle_secne : battle_scenes)
		{
			if (is_encount_rader)
			{
				if (rader.Battle_Scene)
				{
					changeScene(battle_secne);
					townM.pause();
					getData().pos = player->pos;
					rader.Battle_Scene = false;
					player->distance = { 0,0 };
					getData().movement = player->movement;
				}
			}
			else
			{
				if (player->distance.x > changeBattle.x || player->distance.y > changeBattle.y)
				{
					changeScene(battle_secne);
					townM.pause();
					getData().pos = player->pos;
					player->distance = { 0,0 };
					getData().movement = player->movement;
				}
			}
		}
		String flag = TextManager::text->getFlag();
		//特定のセリフの話しが終わったらバトルに移り変わる処理
		if (flag != U"")
		{
			townM.pause();
			flag;
			changeScene(flag);
			getData().pos = player->pos;
			getData().movement = player->movement;
		}
		TextManager::text->update();

	}

	void draw() const override
	{
		Scene::SetBackground(Color(15, 15, 15));
		{
			Transformer2D t0(Mat3x2::Translate(-player->pos.x + Window::DefaultClientSize.x / 2, -player->pos.y + Window::DefaultClientSize.y / 2));
			for (auto& ground : grounds)
			{
				ground->draw();
			}
			for (auto& flower : flowers)
			{
				flower->draw();
			}
			for (auto& object : objects)
			{
				object->draw();
			}
		}
		message_font(game_message).draw(20, 10, Palette::Black);
		//rader.draw(cellManager);
		TextManager::text->draw();

	}
private:
	std::shared_ptr<Mobu> mobu;
	Skill_Com skill_com;
	Font message_font = Font(20);
	String game_message = U"北の砂漠にいるイエローを倒しに行こう!";
	Font font = Font(30);
};


class firstCity : public Field
{
public:
	firstCity(const InitData& init) : Field(init)
	{
		townM = AudioAsset(U"Town");
		AudioAsset(U"Town").setVolume(0.1);
		grounds.push_back(std::make_shared<Ground>(Point{ -1000,-700 }, Point{ 3000, 2700 }, U"grass", 5, 7));
		grounds.push_back(std::make_shared<Ground>(Point({ -380,80 }), Point({ 400, 300 }), U"soil2", 2, 1));
		flowers.push_back(std::make_shared<flower>(Point({ 80,-600 }), Point({ 60, 60 }), U"flower", 3, 3));
		flowers.push_back(std::make_shared<flower>(Point({ 150,0 }), Point({ 60, 60 }), U"flower", 5, 3));
		flowers.push_back(std::make_shared<flower>(Point({ -450,200 }), Point({ 60, 60 }), U"flower", 3, 2));
		player = std::make_shared<Player>(Point(getData().pos), Point({ 55, 40 }), Point({ 91, 154 }), std::array<String, 4>{ U"AberuR", U"AberuL", U"AberuB", U"AberuF" }, Point(getData().movement));
		objects.push_back(player);
		changeBattle = { INFINITY,INFINITY };
		objects.push_back(std::make_shared<tree>(Point{ -750, 1000 }, Point{ 370, 370 }, Point{ -100, -180 }, String(U"tree1"), 9, 3));
		objects.push_back(std::make_shared<tree>(Point{ -500, -1300 }, Point{ 370, 370 }, Point{ -100, -190 }, U"tree1", 3, 3));
		objects.push_back(std::make_shared<tree>(Point({ -1700,-1200 }), Point({ 370, 370 }), Point({ -50, -100 }), String(U"tree1"), 6, 12));
		objects.push_back(std::make_shared<tree>(Point({ 900,-1200 }), Point({ 370, 370 }), Point({ -50, -100 }), String(U"tree1"), 4, 15));

		//Exteriorの引数(位置、描画のサイズ、影のサイズ、ドアの判定の調整、当たり判定のサイズ、調整、画像の名前、シーン)
		objects.push_back(std::make_shared<Exterior01>(Point{ 400, -400 }, Point{ 500, 500 }, Point{8,50}, Point{ 155,70 }, Point{ 300, 80 }, 108, String(U"house")));
		objects.push_back(std::make_shared<Exterior02>(Point{ -300, 0 }, Point{ 500, 500 }, Point{8,50}, Point{ 155,70 }, Point{ 300, 80 }, 108, String(U"house")));
		objects.push_back(std::make_shared<PlayerHouse_Exterior>(Point{ 350, 450 }, Point{ 500, 500 }, Point{8,50}, Point{ 140, 80 }, Point{ 360, 110 }, 175, String(U"house2")));

		objects.push_back(std::make_shared<Mobu>(Point{ -100, 500 }, Point{ 40, 30 }, MobuDirection::Backward, Point{ 94 ,158 }, std::array < String, 4>{ U"Mobu2R", U"Mobu2L", U"Mobu2B", U"Mobu2F" }, 0));
		objects.push_back(std::make_shared<Mobu>(Point{ 500, -100 }, Point{ 40, 30 }, MobuDirection::Right, Point{ 100 ,173 }, std::array < String, 4>{ U"PieroR", U"PieroL", U"PieroB", U"PieroF" }, 1));
		objects.push_back(std::make_shared<Mobu>(Point{ 100, -900 }, Point{ 40, 30 }, MobuDirection::Forward, Point{ 94,158 }, std::array < String, 4>{ U"Lady1R", U"Lady1L", U"Lady1B", U"Lady1F" }, 5));
		objects.push_back(std::make_shared<Mobu>(Point{ -150, -500 }, Point({ 40, 30 }), MobuDirection::Forward, 2, Point{ 82, 155 }, std::array< String, 4>{ U"DoctorR", U"DoctorL", U"DoctorB", U"DoctorF" }, 3));
		change_scene_rects.push_back(changerect{ Rect(-100, -1300, 1000, 20), U"FirstField",{ 130,750 } });

	}
	void init()
	{

	}
private:

};

class firstField :public Field
{
public:

	firstField(const InitData& init) : Field(init)
	{
		townM = AudioAsset(U"Town");
		AudioAsset(U"Town").setVolume(0.1);
		player = std::make_shared<Player>(Point(getData().pos), Point({ 55, 40 }), Point({ 91, 154 }), std::array<String, 4>{ U"AberuR", U"AberuL", U"AberuB", U"AberuF" }, Point(getData().movement));
		grounds.push_back(std::make_shared<Ground>(Point{ -1000,-700 }, Point{ 3000, 2700 }, String(U"grass"), 5, 7));
		grounds.push_back(std::make_shared<Ground>(Point{ -850,-2100 }, Point{ 3000, 2700 }, String(U"soil"), 3, 1));
		flowers.push_back(std::make_shared<flower>(Point{ 460, -320 }, Point{ 60, 60 }, String(U"flower"), 3, 3));
		flowers.push_back(std::make_shared<flower>(Point({ 80,-600 }), Point({ 60, 60 }), U"flower", 3, 3));
		flowers.push_back(std::make_shared<flower>(Point({ 150,0 }), Point({ 60,60 }), U"flower", 5, 3));
		flowers.push_back(std::make_shared<flower>(Point({ -450,200 }), Point({ 60, 60 }), U"flower", 3, 3));
		flowers.push_back(std::make_shared<flower>(Point({ 380,-750 }), Point({ 60, 60 }), U"flower", 5, 5));

		objects.push_back(std::make_shared<tree>(Point{ 800,-1200 }, Point{ 370, 370 }, Point{ -50, -100 }, U"tree1", 6, 15));
		objects.push_back(std::make_shared<tree>(Point{ -1200,-1200 }, Point{ 370, 370 }, Point{ -50, -100 }, U"tree1", 5, 17));
		objects.push_back(std::make_shared<tree>(Point{ -1400,-2300 }, Point{ 370, 370 }, Point{ -50, -180 }, U"tree1", 1, 20));
		objects.push_back(std::make_shared<tree>(Point{ -900,-2500 }, Point{ 370, 370 }, Point{ -50, -180 }, U"tree1", 20, 5));
		objects.push_back(std::make_shared<tree>(Point{ 50,200 }, Point{ 370, 370 }, Point{ -80, -230 }, U"tree1", 4, 2));
		objects.push_back(std::make_shared<tree>(Point{ -230,-850 }, Point{ 370, 370 }, Point{ -80, -230 }, U"tree1", 3, 2));
		objects.push_back(std::make_shared<rock>(Point{ 1790,-1350 }, Point{ 780, 780 }, Point{ 470, 350 }, U"stone"));
		changeBattle = { Random(80,400),Random(80,400) };
		objects.push_back(std::make_shared<Mobu>(Point({ 505, -370 }), Point({ 40, 30 }), MobuDirection::Left, 2, Point({ 94, 158 }), std::array<String, 4>{ U"Mobu2R", U"Mobu2L", U"Mobu2B", U"Mobu2F" }, 9));
		objects.push_back(std::make_shared<Mobu>(Point{ 1140, -1610 }, Point{ 40, 30 }, MobuDirection::Backward, Point{ 72 ,158 }, std::array<String, 4>{ U"Mobu1R", U"Mobu1L", U"Mobu1B", U"Mobu1F" }, 6));
		objects.push_back(player);
		if (!getData().Arisu_finish)
		{
			objects.push_back(std::make_shared<Mobu>(Point{ -1155, -1900 }, Point{ 40, 30 }, MobuDirection::Right, Point{ 98 ,167 }, std::array<String, 4>{ U"MajyoR", U"MajyoL", U"MajyoB", U"MajyoF" }, 7));
		}
		else if (getData().Arisu_finish)
		{
			objects.push_back(std::make_shared<Mobu>(Point{ -1155, -1900 }, Point{ 40, 30 }, MobuDirection::Right, Point{ 98 ,167 }, std::array<String, 4>{ U"MajyoR", U"MajyoL", U"MajyoB", U"MajyoF" }, 10));
		}
		change_scene_rects.push_back(changerect{ Rect(-300, 800, 1000, 20), U"FirstCity",{ 385,-1130 } });
		change_scene_rects.push_back(changerect{ Rect(-1300, -2335, 400, 10), U"SecondField",{ 0,720 } });
		battle_scenes.push_back(String(U"Battle"));
	}
	void init()
	{
		
	}
};


class secondField :public Field
{
public:
	secondField(const InitData& init) : Field(init)
	{
		townM = AudioAsset(U"Town");
		AudioAsset(U"Town").setVolume(0.1);
		player = std::make_shared<Player>(Point(getData().pos), Point({ 55, 40 }), Point({ 91, 154 }), std::array<String, 4>{ U"AberuR", U"AberuL", U"AberuB", U"AberuF" }, Point(getData().movement));
		grounds.push_back(std::make_shared<Ground>(Point{ -1000,-700 }, Point{ 3000, 2700 }, String(U"soil"), 7, 7));

		objects.push_back(std::make_shared<Rock>(Point{ 270, 580 }, Point{ 370, 370 }, Point{ -70, -120 }, U"stone", 14, 3));
		objects.push_back(std::make_shared<Rock>(Point{ -1200, -2050 }, Point{ 370, 370 }, Point{ -50, -100 }, U"stone", 5, 20));
		objects.push_back(std::make_shared<Rock>(Point{ -205, -1000 }, Point{ 370, 370 }, Point{ -50, -100 }, U"stone", 13, 5));
		objects.push_back(std::make_shared<Rock>(Point{ 3045, -1480 }, Point{ 370, 370 }, Point{ -50, -100 }, U"stone", 5, 15));
		objects.push_back(std::make_shared<Rock>(Point{ 0, -2080 }, Point{ 370, 370 }, Point{ -50, -100 }, U"stone", 16, 3));
		changeBattle = { Random(80,400),Random(80,400) };
		objects.push_back(player);
		if (!getData().Donald_finish)
		{
			objects.push_back(std::make_shared<Mobu>(Point{ 2635, -950 }, Point{ 40, 30 }, MobuDirection::Right, Point{ 100 ,173 }, std::array<String, 4>{ U"PieroR", U"PieroL", U"PieroB", U"PieroF" }, 11));
		}
		else if (getData().Donald_finish)
		{
			objects.push_back(std::make_shared<Mobu>(Point{ 2635, -950 }, Point{ 40, 30 }, MobuDirection::Right, Point{ 100 ,173 }, std::array<String, 4>{ U"PieroR", U"PieroL", U"PieroB", U"PieroF" }, 13));
		}

		change_scene_rects.push_back(changerect{ Rect(-300, 800, 1000, 20), U"FirstField", {-1150,-2150} });
		change_scene_rects.push_back(changerect{ Rect(1320,-1680,50,480) , U"ThirdField", { 1500,-25 } });
		battle_scenes.push_back(String(U"Battle2"));
	}

	void init()
	{
	

	}
};


class thirdField :public Field
{
public:

	thirdField(const InitData& init) : Field(init)
	{
		townM = AudioAsset(U"Town");
		AudioAsset(U"Town").setVolume(0.1);
		grounds.push_back(std::make_shared<Ground>(Point{ -2000,-1500 }, Point{ 3000, 2700 }, String(U"soil"), 8, 8));
		objects.push_back(std::make_shared<Mobu>(Point{ -1990, -2150 }, Point{ 40, 30 }, MobuDirection::Forward, Point{ 94 ,158 }, std::array<String, 4>{ U"Mobu2R", U"Mobu2L", U"Mobu2B", U"Mobu2F" }, 14));
		objects.push_back(std::make_shared<Mobu>(Point{ -1885, -3000 }, Point{ 40, 30 }, MobuDirection::Forward, Point{ 95 ,152 }, std::array<String, 4>{ U"Chara2R", U"CharaL", U"CharaB", U"CharaF" }, 8));
		player = std::make_shared<Player>(Point(getData().pos), Point({ 55, 40 }), Point({ 91, 154 }), std::array<String, 4>{ U"AberuR", U"AberuL", U"AberuB", U"AberuF" }, Point(getData().movement));
		changeBattle = { Random(50,320),Random(80,350) };
		objects.push_back(player);
		change_scene_rects.push_back(changerect{ Rect(1605,-260,50,480) , U"SecondField",{ 1450,-1500 } });
		objects.push_back(std::make_shared<Rock>(Point{ 200, -305 }, Point{ 370, 370 }, Point{ -50, -100 }, U"stone", 20, 1));
		objects.push_back(std::make_shared<Rock>(Point{ -350, 280 }, Point{ 370, 370 }, Point{ -50, -100 }, U"stone", 25, 1));
		objects.push_back(std::make_shared<Rock>(Point{ -400, -1000 }, Point{ 370, 370 }, Point{ -50, -100 }, U"stone", 1, 7));
		objects.push_back(std::make_shared<Rock>(Point{ 145, -1350 }, Point{ 370, 370 }, Point{ -50, -100 }, U"stone", 1, 6));
		objects.push_back(std::make_shared<Rock>(Point{ -1520, -1500 }, Point{ 370, 370 }, Point{ -50, -100 }, U"stone", 9, 1));
		objects.push_back(std::make_shared<Rock>(Point{ -2005, -1000 }, Point{ 370, 370 }, Point{ -50, -100 }, U"stone", 9, 1));
		objects.push_back(std::make_shared<Rock>(Point{ -2200, -2225 }, Point{ 370, 370 }, Point{ -50, -100 }, U"stone", 1, 7));
		objects.push_back(std::make_shared<Rock>(Point{ -1580, -2220 }, Point{ 370, 370 }, Point{ -50, -100 }, U"stone", 1, 4));
		objects.push_back(std::make_shared<Rock>(Point{ -2680, -2350 }, Point{ 370, 370 }, Point{ -50, -100 }, U"stone", 3, 1));
		objects.push_back(std::make_shared<Rock>(Point{ -1565, -2350 }, Point{ 370, 370 }, Point{ -50, -100 }, U"stone", 3, 1));
		objects.push_back(std::make_shared<Rock>(Point{ -2880, -3300 }, Point{ 370, 370 }, Point{ -50, -100 }, U"stone", 1, 6));
		objects.push_back(std::make_shared<Rock>(Point{ -980, -3300 }, Point{ 370, 370 }, Point{ -50, -100 }, U"stone", 1, 6));
		objects.push_back(std::make_shared<Rock>(Point{ -2880, -3400 }, Point{ 370, 370 }, Point{ -50, -100 }, U"stone", 10, 1));
		battle_scenes.push_back(String(U"Battle3"));
	}

	void init()
	{
		
	}
};

class Clear :public MyApp::Scene
{
public:
	Font font = Font(60);
	const String text3 = U"Game     Clear";
	Clear(const InitData& init) : IScene(init)
	{
		Window::Resize(1200, 750);
		TextureAsset::Register(U"sky", U"Images/sky.jpg");
	}
	void init()
	{

	}
	void update() override
	{
		if (KeyEnter.up())
		{
			getData().pos = { 0,400 };
			changeScene(U"Title");
		}
	}
	void draw() const override
	{
		TextureAsset(U"sky").scaled(0.8, 0.8).draw();
		font(text3).draw(600, 300);
	}
private:

};


