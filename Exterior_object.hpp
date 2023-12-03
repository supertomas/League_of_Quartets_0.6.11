#pragma once
#include <Siv3D.hpp>
#include"player.hpp"
#include"Object.hpp"

class Exterior_Object : public Object
{
public:
	Array<bool> is_gate = {
		false,
		false,
		false
	};

	Exterior_Object(Point _pos, Point _region, Point _shadow, Point _door, Point _size, int32 _adjust, String _texture)
	{
		pos = _pos;
		texture = _texture;
		region = _region;
		shadow = _shadow;
		size = _size;
		adjust = _adjust;
		door = _door;
	}

	Rect getRegion() const
	{
		return Rect(pos.x + shadow.x - region.x / 2, pos.y + shadow.y - region.y, region.x, region.y);
	}

	Rect getBody() const
	{
		return Rect(pos.x - size.x + adjust, pos.y - size.y, size.x, size.y);
	}

	//シーンの名前を受け取る
	String getName()
	{
		if (is_gate[0])
		{
			return U"In1";
		}
		else if (is_gate[1])
		{
			return U"In2";
		}
		else if (is_gate[2])
		{
			return U"In3";
		}
		else
		{
			return U"No";
		}
	}

	Rect getDoor()
	{
		return Rect(pos.x - door.x, pos.y +5 ,door.y, 10);
		//door.yはドアの幅
	}

	bool intersect_Wall(std::shared_ptr<Player>& player)
	{
		return player->getBody().intersects(getBody());
	}

	bool intersectWithDoor(std::shared_ptr<Player>& player)
	{
		return player->getBody().intersects(getDoor());
	}

	void draw()
	{
		getRegion()(TextureAsset(texture)).draw();
		if (debug)
		{
			getBody().draw();
			getDoor().draw(Palette::Red);
			Circle({ pos.x,pos.y }, 10).draw(Palette::Blue);
		}
	}
private:
	Point region, size, shadow;
	String texture;
	Point door;
	int32 adjust;
};

class Exterior01 : public Exterior_Object
{
public:
	Exterior01(Point _pos, Point _region, Point _shadow,Point _door, Point _size, int32 _adjust, String _texture)
		: Exterior_Object(_pos, _region, _shadow, _door, _size, _adjust, _texture)
	{}
	void update(std::shared_ptr<Player>& player) override
	{
		if (intersectWithDoor(player))
		{
			is_gate[0] = true;
		}
		if (intersect_Wall(player))
		{
			player->pos -= player->speed;
		}
	}

};

class Exterior02 : public Exterior_Object
{
public:
	Exterior02(Point _pos, Point _region, Point _shadow, Point _door,Point _size, int32 _adjust, String _texture)
		: Exterior_Object(_pos, _region, _shadow, _door, _size, _adjust, _texture)
	{}
	void update(std::shared_ptr<Player>& player) override
	{
		if (intersectWithDoor(player))
		{
			is_gate[1] = true;
		}
		if (intersect_Wall(player))
		{
			player->pos -= player->speed;
		}
	}

};

class PlayerHouse_Exterior : public Exterior_Object
{
public:
	PlayerHouse_Exterior(Point _pos, Point _region, Point _shadow,Point _door,Point _size,int32 _adjust, String _texture)
		: Exterior_Object(_pos, _region, _shadow, _door, _size, _adjust, _texture)
	{}
	void update(std::shared_ptr<Player>& player) override
	{
		if (intersectWithDoor(player))
		{
			is_gate[2] = true;
		}
		if (intersect_Wall(player))
		{
			player->pos -= player->speed;
		}
	}

};
