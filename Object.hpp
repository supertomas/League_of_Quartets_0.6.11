#pragma once
# include <Siv3D.hpp>
class Player;
class Object
{
public:
	Point pos;
	bool debug = false;
	virtual void update(std::shared_ptr<Player>& player) = 0;
	virtual String getName() {
		return U"object_name";
	};
	virtual void draw() = 0;
};

class Gamedata
{
public:
	Point pos = { -50,400 };//主人公の最初の初期値
	int32 Hp = 35, Mp = 16, Exp = 0, Level = 1, Gold = 0;//主人公の最初のステータス
	Point movement = { 0,0 };
	Array<bool> skillmessages = {
		false,
		false,
		false
	};
	bool Firstmessage = false;
	bool Donald_finish = false;
	bool Arisu_finish = false;

private:

};
// シーン管理クラス
using MyApp = SceneManager<String, Gamedata>;
