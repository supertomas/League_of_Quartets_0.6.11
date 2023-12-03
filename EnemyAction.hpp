#pragma once
#include<Siv3D.hpp>
#include"Battle_Escape_Com.hpp"
#include"Special_Com.hpp"
# include "TextManager.hpp"

void Enemy_Action(String Skill_name)
{
	if (choice == U"かみつく")
	{
		int Playerdamage = enemies[index].Attack - DefenceP;
		if (Playerdamage > 0)
		{
			getData().Hp = Max(0, getData().Hp - Playerdamage);
			messages.push_back(Format(enemies[index].type, U"のかみつくこうげき !\nアベルに", Playerdamage, U"ポイントのダメージ"));
			//SoundAsset(L"damage").playMulti();
		}
		else if (Playerdamage <= 0)
		{
			messages.push_back(Format(enemies[index].type, U"のかみつくこうげき !  しかし\nアベルはダメージを受けなかった。"));
		}

	}

	else if (choice == U"こうげき")
	{
		int Playerdamage = enemies[index].Attack - 5 - DefenceP;
		if (Playerdamage > 0)
		{
			getData().Hp = Max(0, getData().Hp - Playerdamage);
			messages.push_back(Format(enemies[index].type, U"のつうじょうこうげき !\nアベルに", Playerdamage, U"ポイントのダメージ"));
			//SoundAsset(L"damage").playMulti();
		}
		else if (Playerdamage <= 0)
		{
			messages.push_back(Format(enemies[index].type, U"のつうじょうこうげき !  しかし\nアベルはダメージを受けなかった。"));
		}
	}
	else if (choice == U"つめとぎ")
	{
		enemies[index].Attack += 5;
		messages.push_back(Format(enemies[index].type, U"は つめとぎ をした。\n", enemies[index].type, U"の攻撃力があがった。"));
	}
	else if (choice == U"けいかい")
	{
		messages.push_back(Format(enemies[index].type, U"はけいかいしている。"));
	}
	else if (choice == U"つきさす")
	{
		int Playerdamage = enemies[index].Attack - DefenceP;
		if (Playerdamage > 0)
		{
			getData().Hp = Max(0, getData().Hp - Playerdamage);
			messages.push_back(Format(enemies[index].type, U"の つきさす こうげき\nアベルは", Playerdamage, U"ポイントのダメージを受けた"));
			//SoundAsset(L"damage").playMulti();
		}
		else if (Playerdamage <= 0)
		{
			messages.push_back(Format(enemies[index].type, U"のつきさす こうげき !  しかし\nアベルはダメージを受けなかった。"));
		}
	}
	else if (choice == U"様子")
	{
		messages.push_back(Format(enemies[index].type, U"はようすをみている。"));
	}
	else if (choice == U"メーレ")
	{
		enemies[index].Hp = Min(10, enemies[index].Hp + 8);
		messages.push_back(Format(enemies[index].type, U"は メーレ のじゅもん\nをとなえた。"));
		messages.push_back(Format(enemies[index].type, U"はかいふくした。"));
	}

	else if (choice == U"メーレ2")
	{
		enemies[index].Hp = Min(46, enemies[index].Hp + 10);
		messages.push_back(Format(enemies[index].type, U"は メーレ のじゅもん\nをとなえた。"));
		messages.push_back(Format(enemies[index].type, U"はかいふくした。"));
	}

	else if (choice == U"メーレ3")
	{
		enemies[index].Hp = Min(65, enemies[index].Hp + 10);
		messages.push_back(Format(enemies[index].type, U"は メーレ のじゅもん\nをとなえた。"));
		messages.push_back(Format(enemies[index].type, U"はかいふくした。"));
	}
	else if (choice == U"ねばねば")
	{
		SpeedP -= 5;
		messages.push_back(Format(enemies[index].type, U"は ねばねば の液を出した。"));
		messages.push_back(Format(U"からみついて すばやさ が\n下がってしまった。"));
	}

	else if (choice == U"とげラッシュ")
	{
		int Playerdamage = enemies[index].Attack - DefenceP;
		if (Playerdamage > 0)
		{
			getData().Hp = Max(0, getData().Hp - Playerdamage);
			messages.push_back(Format(enemies[index].type, U"のとげラッシュ !\nアベルに", Playerdamage, U"ポイントのダメージ"));
			//SoundAsset(L"damage").playMulti();
		}
		else if (Playerdamage <= 0)
		{
			messages.push_back(Format(enemies[index].type, U"のとげラッシュ!  しかし\nアベルはダメージを受けなかった。。"));
		}
		getData().Hp = getData().Hp - Playerdamage;

	}

	else if (choice == U"ロックガード")
	{
		if (rock_limit_defence == false)
		{
			MetalDefence = enemies[index].Defence + 10;
			rock_limit_defence = true;
		}
		if (enemies[index].Defence < MetalDefence)
		{
			enemies[index].Defence = Min(enemies[index].Defence + 5, MetalDefence);
			messages.push_back(Format(enemies[index].type, U"のロックガード !!\n", enemies[index].type, U"の防御力があがった。"));
		}
		else
		{

			messages.push_back(Format(enemies[index].type, U"のロックガード !!"));
			messages.push_back(Format(U"しかし、これ以上", enemies[index].type, U"\nの防御力はあがらない。"));
		}
	}

	else if (choice == U"のしかかり")
	{
		int Playerdamage = enemies[index].Attack - DefenceP;
		if (Playerdamage > 0)
		{
			getData().Hp = Max(0, getData().Hp - Playerdamage);
			messages.push_back(Format(enemies[index].type, U"はのしかかってきた。\nアベルに", Playerdamage, U"ポイントのダメージ"));
			//SoundAsset(L"damage").playMulti();
		}
		else if (Playerdamage <= 0)
		{
			messages.push_back(Format(enemies[index].type, U"のこうげき !  しかし\nアベルはダメージを受けなかった。"));
		}
	}
	else if (choice == U"ボディープレス")
	{
		int Playerdamage = enemies[index].Attack - 3 - DefenceP;
		if (Playerdamage > 0)
		{
			getData().Hp = Max(0, getData().Hp - Playerdamage);
			messages.push_back(Format(enemies[index].type, U"のボディープレス。\nアベルに", Playerdamage, U"ポイントのダメージ受け"));
			messages.push_back(U"防御力が下がってしまった。");
			//SoundAsset(L"damage").playMulti();
			DefenceP = Max(8, DefenceP - 4);
		}
		else if (Playerdamage <= 0)
		{
			messages.push_back(Format(enemies[index].type, U"のボディープレス !  \nアベルはダメージを受けなかったが"));
			messages.push_back(U"防御力が下がってしまった。");
			DefenceP = Max(8, DefenceP - 4);
		}
	}
	else if (choice == U"フレア")
	{
		int Playerdamage = enemies[index].Attack - DefenceP;
		if (Playerdamage > 0)
		{
			getData().Hp = Max(0, getData().Hp - Playerdamage);
			messages.push_back(Format(enemies[index].type, U"の じゅもん フレア \nアベルは", Playerdamage, U"ポイントのダメージを受けた"));
			//SoundAsset(L"fire").playMulti();
		}
		else if (Playerdamage <= 0)
		{
			messages.push_back(Format(enemies[index].type, U"のこうげき !  しかし\nアベルはダメージを受けなかった。。"));
		}
	}

	else if (choice == U"ルノバス")
	{
		if (DefenceP > 5)
		{
			messages.push_back(Format(enemies[index].type, U"の ルノバスのじゅもん ！"));
			messages.push_back(Format(U"アベルの 防御力が 下げってしまった"));
			DefenceP = Max(5, DefenceP - 4);
		}
		else
		{
			messages.push_back(Format(enemies[index].type, U"の ルノバスのじゅもん ！"));
			messages.push_back(U"しかし、アベルの 防御力 \nは十分下がっている。");
		}
	}
	else if (choice == U"幻惑の瞳")
	{
		if (AttackP > 19)
		{
			messages.push_back(Format(enemies[index].type, U"の 幻惑の瞳"));
			messages.push_back(U"アベルは みりょうされ \n攻撃力がさがった");
			AttackP = Max(19, AttackP - 8);
		}
		else
		{
			messages.push_back(Format(enemies[index].type, U"の 幻惑の瞳"));
			messages.push_back(U"しかし、アベルの 攻撃力 \nは十分下がっている。");
		}
	}

	else if (choice == U"イリュージョンダンス")
	{
		if (AttackP > 14)
		{
			messages.push_back(Format(enemies[index].type, U"の イリュージョンダンス"));
			messages.push_back(U"アベルは みりょうされ \n攻撃力がさがった");
			AttackP = Max(14, AttackP - 6);
		}
		else
		{
			messages.push_back(Format(enemies[index].type, U"の イリュージョンダンス"));
			messages.push_back(U"しかし、アベルの 攻撃力 \nは十分下がっている。");
		}
	}

	else if (choice == U"火吹き")
	{
		int Playerdamage = enemies[index].Attack - DefenceP;
		if (Playerdamage > 0)
		{
			getData().Hp = Max(0, getData().Hp - Playerdamage);
			messages.push_back(Format(enemies[index].type, U"の 火吹き こうげき \nアベルは", Playerdamage, U"ポイントのダメージを受けた"));
		}
		else if (Playerdamage <= 0)
		{
			messages.push_back(Format(enemies[index].type, U"の火吹き こうげき !  しかし\nアベルはダメージを受けなかった。"));
		}
	}
	else if (choice == U"ただのパンチ")
	{
		int Playerdamage = enemies[index].Attack - 6 - DefenceP;
		if (Playerdamage > 0)
		{
			getData().Hp = Max(0, getData().Hp - Playerdamage);
			messages.push_back(Format(enemies[index].type, U"の ただのパンチ\n", Playerdamage, U"ポイントのダメージを受けた"));
		}
		else if (Playerdamage <= 0)
		{
			messages.push_back(Format(enemies[index].type, U"のこうげき !  しかし\nアベルはダメージを受けなかった。。"));
		}
	}

	else if (choice == U"杖")
	{
		int Playerdamage = enemies[index].Attack - 5 - DefenceP;
		if (Playerdamage > 0)
		{
			getData().Hp = Max(0, getData().Hp - Playerdamage);
			messages.push_back(Format(enemies[index].type, U"は 魔法の杖をふってきた。\n", Playerdamage, U"ポイントのダメージを受けた"));
		}
		else if (Playerdamage <= 0)
		{
			messages.push_back(Format(enemies[index].type, U"は 魔法の杖をふってきた。 !  \nしかしアベルはダメージを受けなかった。。"));
		}
	}
	else if (choice == U"ステップ")
	{
		messages.push_back(Format(enemies[index].type, U"はステップ しはじめた。 \n", enemies[index].type, U"のすばやさがあがった。"));
		enemies[index].Speed += 8;
	}
	else if (choice == U"ボルテックス")
	{
		int Playerdamage = enemies[index].Attack - 4 - DefenceP;
		if (Playerdamage > 0)
		{
			getData().Hp = Max(0, getData().Hp - Playerdamage);
			SpeedP -= 3;
			messages.push_back(Format(enemies[index].type, U"の ボルテックス \nアベルは", Playerdamage, U"ポイントのダメージを受けた。"));
			messages.push_back(U"さらにしびれてアベルの\n素早さが下がった … ");
		}
		else if (Playerdamage <= 0)
		{
			messages.push_back(Format(enemies[index].type, U"のこうげき !  しかし\nアベルはダメージを受けなかった。"));
		}
	}
	else if (choice == U"はどうショット")
	{
		int Playerdamage = enemies[index].Attack + 3 - DefenceP;
		if (Playerdamage > 0)
		{
			getData().Hp = Max(0, getData().Hp - Playerdamage);
			messages.push_back(Format(enemies[index].type, U"の 必殺 はどうショット\nアベルは", Playerdamage, U"ポイントのダメージを受けた。"));
			messages.push_back(Format(U"さらに", enemies[index].type, U"の攻撃力があがった。"));
			enemies[index].Attack += 4;
		}
		else if (Playerdamage <= 0)
		{
			messages.push_back(Format(enemies[index].type, U"のこうげき !  しかし\nアベルはダメージを受けなかった。"));
			messages.push_back(Format(U"しかし", enemies[index].type, U"の攻撃力があがった。"));
			enemies[index].Attack += 4;
		}
	}
	else
	{
		// 何かの間違いでどの技にも引っかからなかった時.

		messages.push_back(Format(enemies[index].type, U"は ぼーっと している"));
	}
}
