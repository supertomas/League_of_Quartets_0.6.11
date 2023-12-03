#pragma once
# include <Siv3D.hpp>
#include"Object.hpp"

class EnemyData
{
public:
	String type;
	int Hp, Speed, Defence, Attack, Exp, money;
	Point pos, size;
	Font font = Font(20);
	Array<String> action;

	EnemyData(String _type, int _Hp, int _Speed, int _Defence, int _Attack, int _Exp, int _money, Array<String> _action, Point _pos, Point _size)
	{
		type = _type;
		Hp = _Hp;
		Speed = _Speed;
		Defence = _Defence;
		Exp = _Exp;
		Attack = _Attack;
		money = _money;
		action = _action;
		pos = _pos;
		size = _size;
	}
	Rect getBody() const
	{
		return Rect(pos.x, pos.y, size.x, size.y);
	}
	void draw() const
	{
		if (Hp > 0)
		{
			getBody()(TextureAsset(type)).draw();
			font(type).draw(pos.x + 20, pos.y + 240, Palette::Black);
		}
	}
};
