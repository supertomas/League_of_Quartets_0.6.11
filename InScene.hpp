#pragma once
# include <Siv3D.hpp>
#include"Interior_object.hpp"
#include"Mobu.hpp"

class Desk :public Object
{
public:
	Desk(Point _pos,Point _region_size,Point _intersect_size,Point _adjust,String _texture)
	{
		pos = _pos;
		intersect_size = _intersect_size;
		region_size = _region_size;
		adjust = _adjust;
		texture = _texture;
	}

	Rect getRegion_D() const
	{
		return Rect(pos.x - region_size.x / 2, pos.y - region_size.y / 2 - 20, region_size);
	}

	Rect getBody() const
	{
		return Rect(pos.x+adjust.x, pos.y+adjust.y,intersect_size);
	}

	Circle getPos()
	{
		return Circle(pos, 10);
	}
	void update(std::shared_ptr<Player>& player)
	{
		if (player->getBody().intersects(getBody()))
		{
			player->pos -= player->speed;
		}
	}
	void draw() 
	{
		getRegion_D()(TextureAsset(texture)).draw();
		//getPos().draw();
		//getBody().draw();
	}

private:
	Point intersect_size,region_size;
	Point adjust;
	String texture;

};

class Chair :public Object
{
public:
	Chair(Point _pos, Point _region_size, Point _intersect_size, Point _adjust, String _texture)
	{
		pos = _pos;
		intersect_size = _intersect_size;
		region_size = _region_size;
		adjust = _adjust;
		texture = _texture;
	}
	Rect getRegion_C() const
	{
		return Rect(pos.x - region_size.x / 2, pos.y - region_size.y / 2 - 5, region_size.x, region_size.y);
	}

	Rect getBody() const
	{
		return Rect(pos.x + adjust.x, pos.y + adjust.y, intersect_size);
	}

	Circle getPos()
	{
		return Circle(pos, 10);
	}
	void update(std::shared_ptr<Player>& player)
	{
		if (player->getBody().intersects(getBody()))
		{
			player->pos -= player->speed;
		}
	}
	void draw()
	{
		getRegion_C()(TextureAsset(texture)).draw();
		//getPos().draw();
		//getBody().draw();
	}

private:
	Point intersect_size, region_size;
	Point adjust;
	String texture;
};



class In_scene :public MyApp::Scene
{
public:
	Rect bed_body;
	std::shared_ptr<Player> player;
	Array<std::shared_ptr<Object>> objects;
	// コンストラクタ（必ず実装）
	In_scene(const InitData& init)
		: IScene(init)
	{

	}
	void update() override
	{
		/*for (auto& object : objects)
		{
			Print(object->pos);
		}*/
		std::sort(objects.begin(), objects.end(), [](std::shared_ptr<Object> a, std::shared_ptr<Object> b)
			{
				return a->pos.y < b->pos.y;
			});

		for (auto& object : objects)
		{
			//exit = 家の中から外に出た時のプレイヤーの初期値
			object->update(player);
			if (object->getName().includes(U"Out"))
			{
				//Parse = String→intに変換
				Point exit = ParseOr<Point>(object->getName().substr(3, object->getName().size() - 1), Point{ 0,0 });
				changeScene(U"FirstCity");
				getData().pos = exit;
				getData().movement = player->movement;
			}
		}

		std::sort(objects.begin(), objects.end(), [](std::shared_ptr<Object> a, std::shared_ptr<Object> b)
		{
			return a->pos.y < b->pos.y;
		});
		if (player->getBody().intersects(bed_body))
		{
			player->pos -= player->speed;
		}
	
		if (player->getFace().intersects(bed_body) && KeyEnter.up())
		{
			TextManager::text->start(4);
		}
		String flag = TextManager::text->getFlag();
		if (flag != U"")
		{
			changeScene(flag);
			getData().pos = player->pos;
		}
		TextManager::text->update();
	}
	void draw() const override
	{
		Scene::SetBackground(Color(15, 15, 15));
		{
			Transformer2D t0(Mat3x2::Translate(-player->pos.x + Window::DefaultClientSize.x / 2, -player->pos.y + Window::DefaultClientSize.y / 2));
			for (auto& object : objects)
			{
				object->draw();
			}
			//bed_body.draw();
		}
		TextManager::text->draw();
	}
private:
	bool error_bed = false;

};
class In1 :public In_scene
{
public:

	In1(const InitData& init) :In_scene(init)
	{
		player = std::make_shared<Player>(getData().pos, Point{ 55, 40 }, Point{ 95, 152 }, std::array<String, 4> { U"AberuR", U"AberuL", U"AberuB", U"AberuF" }, Point(getData().movement));
		objects.push_back(std::make_shared<Interior_object>(Point{ 0, 0 }, Point{ 800,760 }, Point{ 400, 480 }, Point{ 5, 5 }, String(U"indoor"), Point{ 310, -320 }, 1));
		objects.push_back(std::make_shared<Desk>(Point{ -120, 650 }, Point{ 120,120 }, Point{ 75,45 }, Point{ -20,-38 }, String(U"desk")));
		objects.push_back(std::make_shared<Chair>(Point{ -180, 620 }, Point{ 220,220 }, Point{ 20,25 }, Point{-20 ,0 }, String(U"chair")));
		objects.push_back(player);
	}
	void init()
	{

	}
private:

};

class In2 :public In_scene
{
public:

	In2(const InitData& init) :In_scene(init)
	{
		player = std::make_shared<Player>(getData().pos, Point{ 55, 40 }, Point{ 95, 152 }, std::array<String, 4> { U"AberuR", U"AberuL", U"AberuB", U"AberuF" }, Point(getData().movement));
		objects.push_back(std::make_shared<Interior_object>(Point({ 0, 0 }), Point{ 800,760 }, Point{ 400, 480 }, Point{ 5, 5 }, String(U"indoor"), Point({ -390, 60 }), 2));
		objects.push_back(std::make_shared<Desk>(Point{ -120, 650 }, Point{ 120,120 }, Point{ 75,45 }, Point{ -20,-38 }, String(U"desk")));
		objects.push_back(std::make_shared<Chair>(Point{ -180, 620 }, Point{ 220,220 }, Point{ 20,25 }, Point{ -20 ,0 }, String(U"chair")));
		objects.push_back(std::make_shared<Mobu>(Point({ -290, 620 }), Point({ 40, 30 }), MobuDirection::Forward, Point({ 71, 155 }), std::array<String, 4>{ U"Mobu1R", U"Mobu1L", U"Mobu1B", U"Mobu1F" }, 2));
		objects.push_back(player);
	}
	void init()
	{

	}
private:

};

class In3 :public In_scene
{
public:
	In3(const InitData& init) :In_scene(init)
	{
		if (getData().Firstmessage == false)
		{
			TextManager::text->start(12);
			getData().Firstmessage = true;
		}
		player = std::make_shared<Player>(getData().pos, Point{ 55, 40 }, Point{ 95, 152 }, std::array<String, 4> { U"AberuR", U"AberuL", U"AberuB", U"AberuF" }, Point(getData().movement));
		bed_body = Rect(-320, 180, 170, 130);
		objects.push_back(std::make_shared<Interior_object>(Point({ 0, 0 }), Point{ 700,660 }, Point{ 240, 260 }, Point({ 5, 5 }), String(U"mainHouse"), Point({ 280, 510 }), 0));
		objects.push_back(std::make_shared<Desk>(Point{ -80, 500 }, Point{ 140,140 }, Point{ 85,60 }, Point{ -25 ,-40 }, String(U"desk")));
		objects.push_back(std::make_shared<Chair>(Point{ -130, 470 }, Point{ 220,220 }, Point{ 30,40 }, Point{ -15, 5 }, String(U"chair")));
		objects.push_back(player);
	}
	void init()
	{

	}
private:

};
