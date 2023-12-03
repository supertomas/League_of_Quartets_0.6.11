#pragma once
#include <Siv3D.hpp>
#include"player.hpp"
#include"Object.hpp"

class Interior_object : public Object
{
public:
	Interior_object(Point _pos, Point _region, Point _adjust, Point _wall,String _texture, Point _exit, int32 _Interior_number)
	{
		pos = _pos;
		texture = _texture;
		region = _region;
		adjust = _adjust;
		wall = _wall;
		exit = _exit;
		Interior_number = _Interior_number;
		if (_Interior_number != 0)
		{
			init1();
		}
		else
		{
			init0();
		}
	}

	void init0()
	{
		rects.push_back(Rect(pos.x + region.x / 2 - adjust.x, pos.y + adjust.y, wall.x, region.y - adjust.y));
		rects.push_back(Rect(pos.x - region.x / 2, pos.y + adjust.y, wall.x, region.y - adjust.y));
		rects.push_back(Rect(pos.x - region.x / 2, pos.y + adjust.y, region.x - adjust.x, wall.y));
		rects.push_back(Rect(pos.x - region.x / 2, pos.y + region.y, region.x - adjust.x, wall.y));
		rects.push_back(Rect(10, 250, 60, 70));
		rects.push_back(Rect(-95, 250, 85, 80));
	}
	void init1()
	{
		rects.push_back(Rect(pos.x + region.x / 2 - adjust.x, pos.y + adjust.y, wall.x, region.y - adjust.y));
		rects.push_back(Rect(pos.x - region.x / 2, pos.y + adjust.y, wall.x, region.y - adjust.y));
		rects.push_back(Rect(pos.x - region.x / 2, pos.y + adjust.y, region.x - adjust.x, wall.y));
		rects.push_back(Rect(pos.x - region.x / 2, pos.y + region.y, region.x - adjust.x, wall.y));
		rects.push_back(Rect(-280, 480, 60, 65));
	}
	void update(std::shared_ptr<Player>& player)
	{
		for (uint32 i = 0; i < rects.size(); i++)
		{
			if (player->getBody().intersects(rects[i]))
			{
				player->pos -= player->speed;
			}
		}
		if (intersect_WithDoor(player, Interior_number))
		{
			is_door = true;
		}
	}

	String getName()
	{
		
		if (is_door)
		{
			return U"Out{}"_fmt(exit);
		}
		else
		{
			return U"Not";
		}
	}
	void draw()
	{
		
		getRegion()(TextureAsset(texture)).draw();
		if (debug)
		{
			for (auto rect : rects)
			{
				rect.draw();
			}
			Door0().draw(Palette::Red);
			Door1().draw(Palette::Red);
		}

	}


	Rect getRegion() const
	{
		return Rect(pos.x - region.x / 2, pos.y, region.x, region.y);
	}



private:
	Point region, wall, adjust, exit;
	String texture;
	std::vector<Rect> rects;
	bool is_door = false;
	int32 Interior_number;
	Rect Door1() const
	{
		return Rect(-320, 745, 80, 5);
	}
	Rect Door0() const
	{
		return Rect(-270, 635, 110, 5);
	}

	bool intersect_WithDoor(std::shared_ptr<Player>& player, int32 num)
	{
		if (num == 0)
		{
			return player->getBody().intersects(Door0());
		}
		else if (num == 1 || num == 2)
		{
			return player->getBody().intersects(Door1());
		}
	}
};
