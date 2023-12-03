#pragma once
#include <Siv3D.hpp>
#include"player.hpp"
#include"Object.hpp"
#include"TextManager.hpp"
enum class MobuDirection
{
	Forward, Backward, Right, Left
};
enum class MoveType
{
	Stop, SideMove
};
class Player;
class Text;
class Mobu : public Object
{
public:


	Mobu(Point _pos, Point _size, MobuDirection _direction, Point _region, std::array<String, 4> _textures, int32 _phrase)
	{
		pos = _pos;
		size = _size;
		direction = _direction;
		region = _region;
		animes[0] = asc::AssetAnime(_textures[0], 4, 200,StartImmediately::No);
		animes[1] = asc::AssetAnime(_textures[1], 4, 200,StartImmediately::No);
		animes[2] = asc::AssetAnime(_textures[2], 4, 200,StartImmediately::No);
		animes[3] = asc::AssetAnime(_textures[3], 4, 200,StartImmediately::No);
		phrase = _phrase;
		type = MoveType::Stop;
	}

	Mobu(Point _pos, Point _size, MobuDirection _direction, int _speed, Point _region, std::array<String, 4> _textures, int32 _phrase)
	{
		pos = _pos;
		size = _size;
		direction = _direction;
		speed = _speed;
		region = _region;
		phrase = _phrase;
		animes[0] = asc::AssetAnime(_textures[0], 4, 200);
		animes[1] = asc::AssetAnime(_textures[1], 4, 200);
		animes[2] = asc::AssetAnime(_textures[2], 4, 200);
		animes[3] = asc::AssetAnime(_textures[3], 4, 200);
		type = MoveType::SideMove;
	}
	Rect getBody() const
	{
		return Rect(pos.x - size.x / 2, pos.y - size.y, size.x, size.y);
	}

	Rect getRegion() const
	{
		return Rect(pos.x - region.x / 2, pos.y - region.y, region.x, region.y);
	}

	void lookAt(Vec2 point)
	{
		Vec2 v = point - pos;
		if (Abs(v.x) > Abs(v.y))
		{
			if (v.x < 0)
			{
				direction = MobuDirection::Left;
			}
			else
			{
				direction = MobuDirection::Right;
			}
		}
		else
		{
			if (v.y > 0)
			{
				direction = MobuDirection::Forward;
			}
			else
			{
				direction = MobuDirection::Backward;
			}
		}
	}

	bool intersect_playerBody_Mobu(std::shared_ptr<Player>& player)
	{
		return player->getBody().intersects(getBody());
		AudioAsset(U"wall").play();
	}

	bool intersect_playerDirectionFacing_Mobu(std::shared_ptr<Player>& player) const
	{
		return (player->getFace().intersects(getBody()));
	}

	void update(std::shared_ptr<Player>& player)
	{
		
		for (auto& anime : animes)
		{
			anime.update();
		}
	
		if (intersect_playerBody_Mobu(player))
		{
			player->pos -= player->speed;
		}
		if (intersect_playerDirectionFacing_Mobu(player)&& KeyEnter.up())
		{
			AudioAsset(U"話しかける").play();
			TextManager::text->start(phrase);
			lookAt(player->getPos());
		}
		if (!TextManager::text->isActive())
		{
			count++;
			switch (type)
			{
				case MoveType::Stop:
					if (count > 250)
					{
						uint32 directionNumber = Random(0, 3);
						if (directionNumber == 0)
						{
							direction = MobuDirection::Backward;
						}
						else if (directionNumber == 1)
						{
							direction = MobuDirection::Forward;
						}
						else if (directionNumber == 2)
						{
							direction = MobuDirection::Left;
						}
						else if (directionNumber == 3)
						{
							direction = MobuDirection::Right;
						}
						count = 0;;
					}
					break;
				case MoveType::SideMove:
					if (distance > 100)
					{
						switch (direction)
						{
							case MobuDirection::Forward:
								direction = MobuDirection::Backward;
							break;
							case MobuDirection::Backward:
								direction = MobuDirection::Forward;
							break;
							case MobuDirection::Right:
								direction = MobuDirection::Left;
							break;
							case MobuDirection::Left:
								direction = MobuDirection::Right;
							break;
						default:
							break;
					}
						distance = 0;
					}
					switch (direction)
					{
						case MobuDirection::Forward:
						if (!intersect_playerBody_Mobu(player))
						{
							pos.y += speed;
						}
						break;
						case MobuDirection::Backward:
							if (!intersect_playerBody_Mobu(player))
							{
								pos.y -= speed;
							}
						break;
						case MobuDirection::Right:
						if (!intersect_playerBody_Mobu(player))
						{
							pos.x += speed;
						}
						break;
						case MobuDirection::Left:
							if (!intersect_playerBody_Mobu(player))
							{
								pos.x -= speed;
							}
						break;
						default:
						break;
					}
					break;
				default:
				break;
			}
		}

		if (!intersect_playerBody_Mobu(player))
		{
			distance += speed;
		}
	}

	void draw()
	{
		switch (direction)
		{
		case MobuDirection::Forward:
			getRegion()(animes[3].get()).draw();
			break;
		case MobuDirection::Backward:
			getRegion()(animes[2].get()).draw();
			break;
		case MobuDirection::Right:
			getRegion()(animes[0].get()).draw();
			break;
		case MobuDirection::Left:
			getRegion()(animes[1].get()).draw();
			break;
		default:
			break;
		}
		//getBody().draw();
	}
	private:
		//時間によって向きがかわる。
		int32 count = 0;
		int32 phrase;
		// 当たり判定の大きさ
		Point size;
		// 向き
		MobuDirection direction;
		MoveType type;
		//描画の四角形
		Point region, move;
		int speed, distance = 0;
		// 画像
		std::array < asc::AssetAnime, 4 > animes;
};
