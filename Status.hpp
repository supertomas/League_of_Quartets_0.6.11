#pragma once
# include <Siv3D.hpp>
#include"Object.hpp"
class Status
{
public:

	Status()
	{
	
	};


	bool LevelUp(int32 nowExp, int32 nowLevel)
	{
		return nowExp >= ExpTable[nowLevel - 1];
	}

	int getSkill(int32 nowLevel)
	{
		if (nowLevel >= SkillTable[0] && nowLevel < SkillTable[1])
		{
			return 1;
		}
		else if (nowLevel >= SkillTable[1] && nowLevel < SkillTable[2])
		{
			return 2;
		}
		else if (nowLevel >= SkillTable[2])
		{
			return 3;
		}

		else
		{
			return 0;
		}
	}
	int AttackPUp(int32 nowLevel) const
	{
		return	AttackTable[nowLevel-1];
	}

	int MaxHp(int32 nowLevel) const
	{
		return	HpTable[nowLevel - 1];
	}

	int MaxMp(int32 nowLevel) const
	{
		return MpTable[nowLevel - 1];
	}

	int DefencePUp(int32 nowLevel)
	{
		return DefenceTable[nowLevel - 1];
	}

	int SpeedPUp(int32 nowLevel)
	{
		return SpeedTable[nowLevel - 1];
	}
private:
	int ExpTable[20] = { 23, 86, 185, 336, 482, 646, 904, 1280, 1850, 2580, 3400, 4800, 6300, 8100,
	9500, 12000, 16000, 20000, 25000 }; //経験値テーブル(累積)

	int AttackTable[20] = { 20,22,26,28,31,35,38,42,47,50,53,56,60,62, 65, 68, 72, 77, 80, 84 }; //こうげき力テーブル

	int HpTable[20] = { 35, 40, 46, 51, 58,65,72,79,86,99,104,110,114,118,123,128, 131 ,135, 141, 147 };//Hpテーブル

	int MpTable[20] = { 16,19,22,25,28,32,35,40,43,47,50,52,55,59,65, 68, 72, 76, 80 }; //Mpテーブル

	int DefenceTable[20] = { 5,7,10,12,15,17,20,22,25,26,29,32,34,37,40, 42, 45, 47, 50 }; //ぼうぎょ力テーブル

	int SpeedTable[20] = { 4,13,16,19,23,27,31,34,38,42,45,50,53,56,58,60,62,63,66,70 };

	int SkillTable[10] = { 2,3,5,10,14,18,23,27,33,37 };//何レベで何を覚えるか
};
