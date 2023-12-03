#pragma once
#include <Siv3D.hpp>
#include"player.hpp"


class tree : public Object
{
public :
	tree(Point _pos, Point _region, Point _wall, String _texture, int _beside_n, int _vertical_n)
	{
		pos = _pos;
		texture = _texture;
		region = _region;
		wall = _wall;
		beside_n = _beside_n;
		vertical_n = _vertical_n;
	}

	Rect getRegion() const
	{
		return Rect(pos.x - region.x / 2 + i * 200, pos.y - region.y + j * 200, region.x, region.y);
	}

	Rect getWall()
	{
		return Rect(pos.x + wall.x , pos.y + wall.y, 185 * beside_n, 190 * vertical_n);
	}

	void update(std::shared_ptr<Player>& player)
	{
		if (player->getBody().intersects(getWall()))
		{
			player->pos -= player->speed;
		}
	}

	void draw()
	{
		for (i = 0; i < beside_n; i++)
		{
			for (j = 0; j < vertical_n; j++)
			{
				getRegion()(TextureAsset(texture)).draw();
			}
		}
		if (debug)
		{
			getWall().draw();
		}
	}
private:
	Point region, size, wall;
	Point shadow;
	String texture;
	int beside_n, vertical_n, i, j;
};

class Rock : public Object
{
public:
	Rock(Point _pos, Point _region, Point _wall, String _texture, int _beside_n, int _vertical_n)
	{
		pos = _pos;
		texture = _texture;
		region = _region;
		wall = _wall;
		beside_n = _beside_n;
		vertical_n = _vertical_n;
	}

	Rect getRegion() const
	{
		return Rect(pos.x - region.x / 2 + i * 200, pos.y - region.y + j * 200, region.x, region.y);
	}

	Rect getWall()
	{
		return Rect(pos.x + wall.x, pos.y + wall.y, 190 * beside_n, 180 * vertical_n);
	}

	void update(std::shared_ptr<Player>& player)
	{
		if (player->getBody().intersects(getWall()))
		{
			player->pos -= player->speed;
		}
	}

	void draw()
	{
		for (i = 0; i < beside_n; i++)
		{
			for (j = 0; j < vertical_n; j++)
			{
				getRegion()(TextureAsset(texture)).draw();
			}
		}
		if (debug)
		{
			getWall().draw();
		}

	}
private:
	Point region, size, wall;
	String texture;
	int beside_n, vertical_n, i, j;
};
class Ground : public Object
{
public:
	Ground(Point _pos, Point _region, String _texture, int _beside_n, int _vertical_n)
	{
		pos = _pos;
		texture = _texture;
		region = _region;
		beside_n = _beside_n;
		vertical_n = _vertical_n;
	}

	Rect getRegion() const
	{
		return Rect(pos.x - region.x / 2 + i * 670, pos.y - region.y + j * 570, region.x, region.y);
	}

	void update(std::shared_ptr<Player>& player)
	{
		player->getVoid();
	}

	void draw()
	{
		for (i = 0; i < beside_n; i++)
		{
			for (j = 0; j < vertical_n; j++)
			{
				getRegion()(TextureAsset(texture)).draw();
			}
		}
	}
private:
	Point pos, region, wall;
	Point shadow;
	String texture;
	int beside_n, vertical_n, i, j;
};

class flower
{
public:
	flower(Point _pos, Point _region, String _texture, int _beside_n , int _vertical_n)
	{
		pos = _pos;
		texture = _texture;
		region = _region;
		beside_n = _beside_n;
		vertical_n = _vertical_n;
	}

	Rect getRegion() const
	{
		return Rect(pos.x - region.x / 2 + i * 30, pos.y - region.y + j * 35, region.x, region.y);
	}

	void update(std::shared_ptr<Player>& player)
	{
		player->getVoid();
	}

	void draw()
	{
		for (i = 0; i < beside_n; i++)
		{
			for (j = 0; j < vertical_n; j++)
			{
				getRegion()(TextureAsset(texture)).draw();
			}
		}
	}
private:
	Point pos, region, size;
	Point shadow;
	String texture;
	int beside_n, vertical_n, i, j;
};


class rock : public Object
{
public:
	rock(Point _pos, Point _region, Point _wall, String _texture)
	{
		pos = _pos;
		region = _region;
		wall = _wall;
		texture = _texture;
	}


	Rect getRegion() const
	{
		return Rect(pos.x - region.x / 2 , pos.y - region.y , region.x, region.y);
	}

	Rect getWall()
	{
		return Rect(pos.x - wall.x / 2, pos.y - wall.y, wall.x, wall.y + 80);
	}

	void update(std::shared_ptr<Player>& player)
	{
		if (player->getBody().intersects(getWall()))
		{
			player->pos -= player->speed;
		}
	}

	void draw()
	{
		getRegion()(TextureAsset(texture)).draw();
		if (debug)
		{
			getWall().draw();
		}
	}
private:
	Point region, wall;
	String texture;
};

