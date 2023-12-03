# pragma once
#include<Siv3D.hpp>
# include "Enemy.hpp"
#include "Object.hpp"
#include"Battle_Escape_Com.hpp"
#include"Special_Com.hpp"
# include "TextManager.hpp"
#include"Status.hpp"
#include"Title.hpp"

enum class mode
{
	comandMenu, skiimenu, target, escape, statusMessage
};

void getEffectDraw(Point pos, String texture)
{
	(Rect(pos.x - 250 / 2, pos.y-100, 500, 500))(TextureAsset(texture)).draw();
}
class AllBattle : public SceneManager<String, Gamedata>::Scene
{
public:
	int AttackP;
	int DefenceP;
	int MetalDefence;
	int SpeedP;
	Status status;
	Array<EnemyData> enemies;
	String Firstmessage;
	String escapeMessage;
	mode ModeScreen = mode::comandMenu;
	std::vector<String> Scene;
	std::unique_ptr <Images> Image;
	Battle_Escape_Com battle_com;
	Audio townM;
	Audio BattleM;
	bool attack_effect = false;
	Point effect_pos;
	Stopwatch effect_timer;
	AllBattle(const InitData& init)
		: IScene(init)
	{

	}
	int escapeRandom()
	{
		return Random(0, 1);
	}
	String playerAction(String action)
	{

		if (getData().Hp > 0)
		{
			if (action == U"こうげき")
			{
				int Enemydamage = AttackP - enemies[target].Defence;
				if (Enemydamage > 0)
				{
					enemies[target].Hp = enemies[target].Hp - Enemydamage;
					attack_effect = true;
					effect_timer.restart();
					effect_pos = { enemies[target].pos};
					return Format(U"アベルのこうげき", enemies[target].type, U"に\n", Enemydamage, U"ポイントのダメージを与えた。");
				}
				else if (Enemydamage <= 0)
				{
					return Format(U"アベルのこうげき   しかし\n", enemies[target].type, U"にダメージを与えられない。");
				}
			}
			else if (action == U"きあいだめ")
			{
				//攻撃力がgetData().Level) + 8 + getData().Levelよりも低かったら攻撃力上昇
				if (AttackP < status.AttackPUp(getData().Level) + 8 + getData().Level)
				{
					AttackP = Min(AttackP + 4 + getData().Level, status.AttackPUp(getData().Level) + 8 + getData().Level);
					getData().Mp -= 3;
					return Format(U"アベルは きあいだめ をした\nこうげき力 じょうしょう !");
				}
				else
				{
					return Format(U"アベルは きあいだめ をした\nしかし、これ以上こうげき力 は上がらない");
				}
			}

			else if (action == U"ばくれつけん")
			{
				getData().Mp -= 5;
				for (uint32 i = 0; i < enemies.size(); i++)
				{
					int Enemydamage = AttackP - getData().Level * 2 - enemies[i].Defence;
					if (Enemydamage > 0)
					{
						enemies[i].Hp = enemies[i].Hp - Enemydamage;
					}
					else
					{

					}
				}
				return Format(U"アベルのばくれつけん\n敵全体にダメージを与えた。");
			}

			else if (action == U"ホープ")
			{
				if (DefenceP < status.DefencePUp(getData().Level) + 5 + getData().Level)
				{
					getData().Mp -= 3;
					DefenceP = Min(DefenceP + 3 + getData().Level, status.AttackPUp(getData().Level) + 5 + getData().Level);
					return Format(U"アベルはホープ のじゅもんをとなえた\nぼうぎょ力があがった。");
				}
				else
				{
					return Format(U"アベルはホープ のじゅもんをとなえた \nしかし、これ以上ぼうぎょ力 は上がらない");
				}

			}

			else if (action == U"ソニックジャブ")
			{
				getData().Mp -= 4;
				int Enemydamage = AttackP - getData().Level * 3 - enemies[target].Defence;
				if (Enemydamage > 0)
				{
					enemies[target].Hp = enemies[target].Hp - Enemydamage;
					SpeedP += 6;
					attack_effect = true;
					effect_pos = { enemies[target].pos };
					effect_timer.restart();
					return Format(U"アベルのソニックジャブ !!  敵に",Enemydamage,U"ダメージ\nを与え、さらにアベルの素早さがあがった。");
				}
				else
				{
					effect_pos = { enemies[target].pos };
					return Format(U"アベルのソニックジャブ!  敵はダメージを\n受けなかったが、アベルの素早さはあがった。");
				}
			}
			else if (action == U"めいそう")
			{
				getData().Mp = Min(status.MaxMp(getData().Level),getData().Mp + 8);
				return Format(U"アベルはめいそうをした。\nMPがかいふく !");
			}
			else if (action == U"メーレ")
			{
				getData().Mp -= 3;
				getData().Hp = Min(status.MaxHp(getData().Level), getData().Hp + 15);
				return Format(U"アベルは メーレ のじゅもんをとなえた\nHPが かいふく した。");
			}
			else if (action == U"にげる")
			{
				return Format(U"アベルは わざ がだせない");
			}

			else
			{
				// 何かの間違いでどの技にも引っかからなかった時.
				return U"アベルは ぼーっと している";
			}
		}
		else
		{
			return Format(U"アベルに戦う力は残っていない...");
		}
	}


	void battle(String action)
	{
		// これをソートするとターゲット先が変わるため使用しない.
		// std::sort(enemies.begin(), enemies.end(), [](const EnemyData& a, const EnemyData& b) { return a.Speed < b.Speed; });

		// std::pair<int32, int32> は<スピード, enemiesの添え字>のデータを表す.
		// { 10, 1 } ならenemies[1].Speedが10であることになる.
		Array<std::pair<int32, int32>> characters;

		for (uint32 i = 0; i < enemies.size(); i++)
		{
			characters.emplace_back(enemies[i].Speed, i);
		}

		// enemiesの代わりにcharactersをソート.
		std::sort(characters.begin(), characters.end(), [](const std::pair<int32, int32>& a, const std::pair<int32, int32>& b) { return a.first > b.first; });

		Array<String> messages;
		bool player = false;

		if (action == U"にげる")
		{
			messages.push_back(U"しかしにげられない。");
		}

		// enemiesではなくcharactersを回す.
		for (uint32 i = 0; i < characters.size(); i++)
		{
			// これ以降 i の代わりに index を使うので要注意！
			const int32 speed = characters[i].first;
			const int32 index = characters[i].second;
		
			if (SpeedP > speed && player == false && getData().Hp > 0)
			{
				messages.push_back(playerAction(action));
				player = true;
			}
			else if (player == false)
			{
				messages.push_back(playerAction(action));
			}
			if (enemies[index].Hp > 0)
			{
				// 一度変数に格納しないとif文ごとに違う技が出てしまう.
				//
				int s = enemies[index].action.size() - 1;
				const String choice = enemies[index].action[Random(0,s)];
				if (choice == U"かみつく")
				{
					int Playerdamage = enemies[index].Attack - DefenceP;
					if (Playerdamage > 0)
					{
						getData().Hp = Max(0,getData().Hp - Playerdamage);
						messages.push_back(Format(enemies[index].type, U"のかみつくこうげき !\nアベルに", Playerdamage, U"ポイントのダメージ"));
						//SoundAsset(L"damage").playMulti();
					}
					else if(Playerdamage <= 0)
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
				else if(choice == U"ボディープレス")
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
						DefenceP = Max(8,DefenceP - 4);
					}
				}
				else if(choice == U"フレア")
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
						messages.push_back(Format(U"アベルの 防御力が 下がってしまった"));
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
						AttackP = Max(19,AttackP - 8);
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
						getData().Hp = Max(0,getData().Hp - Playerdamage);
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
					int Playerdamage = enemies[index].Attack - 5- DefenceP;
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
					messages.push_back(Format(enemies[index].type, U"はステップ しはじめた。 \n",enemies[index].type,U"のすばやさがあがった。"));
					enemies[index].Speed += 8;
				}
				else if (choice == U"ボルテックス")
				{
					int Playerdamage = enemies[index].Attack - 4 - DefenceP;
					if (Playerdamage > 0)
					{
						getData().Hp = Max(0, getData().Hp - Playerdamage);
						SpeedP -= 3;
						messages.push_back(Format(enemies[index].type, U"の ボルテックス \nアベルは" ,Playerdamage,U"ポイントのダメージを受けた。"));
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
						getData().Hp = Max(0,getData().Hp - Playerdamage);
						messages.push_back(Format(enemies[index].type, U"の 必殺 はどうショット\nアベルは",Playerdamage,U"ポイントのダメージを受けた。"));
						messages.push_back(Format(U"さらに", enemies[index].type,U"の攻撃力があがった。"));
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
		}

		TextManager::text->start(messages);
		//turnFinish = true;
	}

	void resetTarget()
	{
		// target先が死んでないか調べる.
		// 死んでいたら、ループで右隣りに移動する.
		for (uint32 index = 0; index < enemies.size(); index++)
		{
			const int32 newTarget = (target + index) % enemies.size();

			if (enemies[newTarget].Hp > 0)
			{
				target = newTarget;

				break;
			}
		}
	}

	void targetUpdate()
	{
		if (KeyRight.up())
		{
			// ターゲットを右に移動し、要素数を超えていたらそれに合わせる.
			target = Min<int32>(target + 1, enemies.size() - 1);

			// target先が死んでないか調べる.
			// 死んでいたら、ループで右隣りに移動する.
			for (uint32 index = 0; index < enemies.size(); index++)
			{
				const int32 newTarget = (target + index) % enemies.size();

				if (enemies[newTarget].Hp > 0)
				{
					target = newTarget;

					break;
				}
			}
		}

		if (KeyLeft.up())
		{
			// ターゲットを左に移動し、0になったら0に合わせる.
			target = Max<int32>(target - 1, 0);

			// targetの移動先が死んでないか調べる.
			// 死んでいたら、ループで左隣りに移動する.
			for (uint32 index = 0; index < enemies.size(); index++)
			{
				// 負の値に剰余算は使えないのでenemies.size()を足して、必ず正の数になるようにする.
				const int32 newTarget = (target - index + enemies.size()) % enemies.size();

				if (enemies[newTarget].Hp > 0)
				{
					target = newTarget;
					break;
				}
			}
		}
	}

	bool win() const
	{
		bool win = true;

		for (uint32 i = 0; i < enemies.size(); ++i)
		{
			// 一人でも生き残ってたら win ではない
			if (enemies[i].Hp > 0)
			{
				win = false;
			}
		}

		return win;
	}

	bool lose() const
	{
		// プレイヤーが死んだらゲームオーバー

		return getData().Hp <= 0;
	}

	void update() override
	{
		//ClearPrint();
		//Print(U"effect_timer_in update = ", effect_timer);
		//Print(attack_effect);
		//Print(TextManager::text->isActive());
		//エフェクト関連
		if (effect_timer.ms() > 400)
		{
			attack_effect = false;
			effect_timer.reset();
		}
		BattleM.play();

		// 「まものがあらわれた」表示中は何もさせない.
		if (timer.ms() < 1000)
		{
			return;
		}

		// これは必ず必要なのでMain.cppに移動
		TextManager::text->update();

		// TextManager起動中は何もしない.、テキストメッセージが起動中はここで処理が止まってしまう
		if (TextManager::text->isActive() == true)
		{
			return;
		}

		// finishがtrueになったらシーン遷移
		for (auto& i : Scene)
		{
			if (finish == true)
			{
				//負けた時だけゲームオーバーに遷移する.
				//勝つか引き分けの時は元のフィールドに戻る.
				if (lose())
				{
					changeScene(U"Gameover");
					BattleM.pause();
				}
				else
				{
					changeScene(i);
					BattleM.pause();
					townM.play();
				}
				return;
			}
		}


			
		// 敗北判定
		if (lose())
		{
			TextManager::text->start({ U"アベルは 力つきてしまった ..." });

			finish = true;

			return;
		}

		// 勝利判定
		if (win())
		{
			int32 allExp = 0;
			int32 allMoney = 0;
		
			for (uint32 i = 0; i < enemies.size(); i++)
			{
				allExp += enemies[i].Exp;
				allMoney += enemies[i].money;
			}

			getData().Exp += allExp;
			Array<String> messages;
			messages.push_back(U"敵をたおした。");
			messages.push_back(Format(allExp, U"ポイントのけいけんちをかくとく"));
			//messages.push_back(Format(allMoney, U"ゼニーをかくとく"));
			//レベルアップしたときの処理
			if (status.LevelUp(getData().Exp,getData().Level))
			{
				ModeScreen = mode::statusMessage;
				messages.push_back(Format(U"アベルのレベルがあがった。"));
				messages.push_back(Format(U"それぞれのステータスがあがった。"));
				getData().Level += 1;
				getData().Hp = status.MaxHp(getData().Level);
				getData().Mp = status.MaxMp(getData().Level);
			}

			//特定のレベル
			if (status.getSkill(getData().Level) == 1 && getData().skillmessages[0] == false)
			{
				messages.push_back(Format(U"アベルはホープのじゅもんを覚えた。"));
				getData().skillmessages[0] = true;
			}

			else if (status.getSkill(getData().Level) == 2 && getData().skillmessages[1] == false)
			{
				messages.push_back(Format(U"アベルはソニックジャブを覚えた。"));
				getData().skillmessages[1] = true;
			}

			else if (status.getSkill(getData().Level) == 3 && getData().skillmessages[2] == false)
			{
				messages.push_back(Format(U"アベルは ばくれつけんを覚えた。"));
				getData().skillmessages[2] = true;
			}
			if (ModeScreen == mode::statusMessage)
			{
				statusMessage.setList(
				{
					Format(U"最大HP    +",status.MaxHp(getData().Level) - status.MaxHp(getData().Level - 1),U"    ",status.MaxHp(getData().Level))
					,Format(U"最大MP    +",status.MaxMp(getData().Level) - status.MaxMp(getData().Level - 1),U"    ",status.MaxMp(getData().Level))
					,Format(U"攻撃力    +",status.AttackPUp(getData().Level) - status.AttackPUp(getData().Level - 1),U"    ",status.AttackPUp(getData().Level))
					,Format(U"防御力    +",status.DefencePUp(getData().Level) - status.DefencePUp(getData().Level - 1),U"    ",status.DefencePUp(getData().Level))
					,Format(U"素早さ    +",status.SpeedPUp(getData().Level) - status.SpeedPUp(getData().Level - 1),U"    ",status.SpeedPUp(getData().Level))
				});
			}
			finish = true;
			if (enemies[0].type == U"アリス")
			{
				getData().Arisu_finish = true;
			}

			if (enemies.size() == 2 && enemies[1].type == U"ドナルド")
			{
				getData().Donald_finish = true;
			}
			TextManager::text->start(messages);

			return;
		}

		// コマンドメニューの時の操作
		if (ModeScreen == mode::comandMenu)
		{
			battle_com.update();
			if (KeyEnter.up())
			{
				AudioAsset(U"カーソル音").play();
				if (battle_com.selected() == U"たたかう")
				{
					battle_com.setItem({ U"こうげき", U"とくぎ",U"",U""/*, L"ゆうごう", L"アイテム"*/ });
				}
				else if (battle_com.selected() == U"にげる")
				{
					if (escapeMessage == U"逃げられる")
					{
						if (escapeRandom() == 1)
						{
							TextManager::text->start({ U"うまくにげきれた" });
							finish = true;
						}
						else
						{
							battle(U"にげる");
							ModeScreen = mode::comandMenu;
						}
					}
					else if (escapeMessage == U"逃げられない")
					{
						TextManager::text->start({U"勝負で 逃げてはダメだ !!"});
						ModeScreen = mode::comandMenu;
					}
				}
				else if (battle_com.selected() == U"こうげき")
				{
					ModeScreen = mode::target;

					// すぐbattleを呼ばずに一度、変数に格納する.
					targetCommand = U"こうげき";

					// これを呼ばないとどうなるかやってみるといいかもしれない.
					resetTarget();
				}

				else if (battle_com.selected() == U"とくぎ")
				{
					ModeScreen = mode::skiimenu;
					skill_com.setList({ U"きあいだめ",U"メーレ",U"めいそう" });
					if (status.getSkill(getData().Level) == 1)
					{
						skill_com.setList({ U"きあいだめ",U"メーレ", U"めいそう",U"ホープ" });
					}

					else if (status.getSkill(getData().Level) == 2)
					{
						skill_com.setList({ U"きあいだめ",U"メーレ", U"めいそう",U"ホープ" ,U"ソニックジャブ" });
					}

					else if (status.getSkill(getData().Level) == 3)
					{
						skill_com.setList({ U"きあいだめ",U"メーレ",U"めいそう", U"ホープ",U"ソニックジャブ",U"ばくれつけん" });
					}
				}
			}
			if (KeySpace.up())
			{
				AudioAsset(U"キャンセル").play();
				battle_com.setItem({ U"たたかう",U"にげる",U"",U"" });
			}

			return;
		}

		// スキルメニューの時の操作
		if (ModeScreen == mode::skiimenu)
		{
			skill_com.update();

			if (KeyEnter.up())
			{
				AudioAsset(U"カーソル音").play();
				if (skill_com.selected() == U"きあいだめ")
				{
					if (getData().Mp >= 3)
					{
						battle(U"きあいだめ");
						ModeScreen = mode::comandMenu;
					}
					else
					{
						TextManager::text->start({ U"MPがたりない !" });
					}
				}

				if (skill_com.selected() == U"ばくれつけん")
				{
					if (getData().Mp >= 5)
					{
						ModeScreen = mode::comandMenu;
						battle(U"ばくれつけん");
					}
					else
					{
						TextManager::text->start({ U"MPがたりない !" });
					}
				}

				if (skill_com.selected() == U"メーレ")
				{
					if (getData().Mp >= 3)
					{
						ModeScreen = mode::comandMenu;
						battle(U"メーレ");
					}
					else
					{
						TextManager::text->start({ U"MPがたりない !" });
					}
				}

				if (skill_com.selected() == U"ホープ")
				{
					if (getData().Mp >= 3)
					{
						ModeScreen = mode::comandMenu;
						battle(U"ホープ");
					}
					else
					{
						TextManager::text->start({ U"MPがたりない !" });
					}
				}
				if (skill_com.selected() == U"ソニックジャブ")
				{
					if (getData().Mp >= 4)
					{
						ModeScreen = mode::target;
						targetCommand = U"ソニックジャブ";
						resetTarget();
					}
					else
					{
						TextManager::text->start({ U"MPがたりない !" });
					}
				}
				if (skill_com.selected() == U"めいそう")
				{
					ModeScreen = mode::comandMenu;
					battle(U"めいそう");
				}
			}
			if (KeySpace.up())
			{
				AudioAsset(U"キャンセル").play();
				ModeScreen = mode::comandMenu;
			}

			return;
		}

		// ターゲット選択時の操作
		if (ModeScreen == mode::target)
		{
			targetUpdate();

			if (KeyEnter.up())
			{
				// 変数に格納したので "こうげき" 以外もターゲットを取れるように.
				battle(targetCommand);
				ModeScreen = mode::comandMenu;
			}

			if (KeySpace.up())
			{
				AudioAsset(U"キャンセル").play();
				ModeScreen = mode::comandMenu;
			}
		}

	}

	void draw() const override
	{
		Scene::SetBackground(ColorF(15, 15, 15));
		Image->draw();
		//getBody()(TextureAsset(texture)).draw();
		for (uint32 i = 0; i < enemies.size(); i++)
		{
			enemies[i].draw();
		}
		battle_com.draw();

		if (ModeScreen == mode::skiimenu)
		{
			skill_com.draw();
		}

		if (ModeScreen == mode::statusMessage)
		{
			statusMessage.draw();
		}

		if (ModeScreen == mode::target)
		{
			const Triangle cursor({ 270, 220 }, { 330, 220 }, { 300, 260 });
			
			if (enemies.size() == 1)
			{
				cursor.movedBy(300 * 1, 0).draw(Palette::Black);
			}
			else
			{
				cursor.movedBy(300 * target, 0).draw(Palette::Black);
			}

			
		}

		const Rect frame(10, 20, 260, 230);

		frame.draw();
		frame.stretched(2).drawFrame(2, 0, Palette::Black);
		frame.stretched(-2).drawFrame(2, 0, Palette::Black);
		font(U"  アベル", U"\nHP : ", getData().Hp,U" / ", status.MaxHp(getData().Level), U"\nMP : ", getData().Mp,U" / ",status.MaxMp(getData().Level), U"\nLv : ", getData().Level).draw(20, 20, Palette::Black);

		TextManager::text->draw();
		if (attack_effect)
		{
			getEffectDraw(effect_pos,U"effect");
		}
		if (timer.ms() < 1000)
		{
			const Rect alert(250, 550, 760, 170);

			alert.draw();
			alert.stretched(2).drawFrame(2, 0, Palette::Black);
			alert.stretched(-2).drawFrame(2, 0, Palette::Black);
			font(Firstmessage).draw(310, 570, Palette::Black);
		}
	}
	private:
		bool rock_limit_defence = false;
		bool finish = false;
		Skill_Com skill_com;
		StatusMessage statusMessage;
		String targetCommand;
		int32 target = 0;
		Stopwatch timer = Stopwatch(StartImmediately::Yes);
		Font font = Font(40);
		bool turnFinish = false;

};



class Battle :public AllBattle
{
public:
	Battle(const InitData& init) : AllBattle(init)
	{
		AttackP = status.AttackPUp(getData().Level);
		DefenceP = status.DefencePUp(getData().Level);
		SpeedP = status.SpeedPUp(getData().Level);
		townM = AudioAsset(U"Town");
		AudioAsset(U"Town").setVolume(0.2);
		BattleM = AudioAsset(U"BattleM");
		AudioAsset(U"BattleM").setVolume(0.2);
		battle_com.setItem({ U"たたかう",U"にげる",U"",U"" });
		Image = std::make_unique<Images>(Images({ 0,0 }, { 1200,750 }, U"forest"));
		const auto enemyNumber = Random(1u, 2u);
		escapeMessage = String(U"逃げられる");
		Firstmessage = String(U"モンスターがあらわれた");
		for (uint32 i = 0; i < enemyNumber; i++)
		{
			uint32 typeNumber = Random(1, 3);

			//引数　左から　名前 HP スピード　ぼうぎょ力　こうげき力　経験値　金
			if (enemyNumber == 1)
			{
				if (typeNumber == 1)
				{
					enemies.push_back(EnemyData(U"ワーウルフ", 15, 15, 9, 10, 13, 8, { U"かみつく",U"つめとぎ",U"けいかい" }, { 500,250 }, { 250,250 }));
				}
				else if (typeNumber == 2)
				{
					enemies.push_back(EnemyData(U"納豆坊", 20, 7, 8, 12, 11, 9, { U"ねばねば",U"つきさす",U"こうげき" }, { 500 ,250 }, { 250,250 }));
				}
				else if (typeNumber == 3)
				{
					enemies.push_back(EnemyData(U"キャロットマン", 12, 8, 6, 7, 10, 5, { U"つきさす",U"様子",U"メーレ" }, { 500 ,250 }, { 250,250 }));
				}
			}
			else
			{
				if (typeNumber == 1)
				{
					enemies.push_back(EnemyData(U"ワーウルフ", 15, 15, 9, 10, 13, 8, { U"かみつく",U"つめとぎ",U"けいかい" }, { 200 + i * 300,250 }, { 250,250 }));
				}
				else if (typeNumber == 2)
				{
					enemies.push_back(EnemyData(U"納豆坊", 20, 7, 8, 12, 11, 9, { U"ねばねば",U"つきさす",U"こうげき" }, { 200 + i * 300,250 }, { 250,250 }));
				}
				else if (typeNumber == 3)
				{
					enemies.push_back(EnemyData(U"キャロットマン", 12, 8, 6, 7, 10, 5, { U"つきさす",U"様子",U"メーレ" }, { 200 + i * 300,250 }, { 250,250 }));
				}
			}

		}

		Scene.push_back(String(U"FirstField"));
	}
	void init()
	{
		
	}
};
	// 変わったように見えるが、実際には順番を入れ替えただけ.
	// 押されたキー中心の振り分けから mode 中心に変えて一連の処理を縦に見やすく.
	
class Battle2 :public AllBattle
{
public:
	Battle2(const InitData& init) : AllBattle(init)
	{
		Image = std::make_unique<Images>(Images({ 0,0 }, { 1200,750 }, U"rockBackground"));
		AttackP = status.AttackPUp(getData().Level);
		DefenceP = status.DefencePUp(getData().Level);
		SpeedP = status.SpeedPUp(getData().Level);
		townM = AudioAsset(U"Town");
		AudioAsset(U"Town").setVolume(0.2);
		BattleM = AudioAsset(U"BattleM");
		AudioAsset(U"BattleM").setVolume(0.2);
		battle_com.setItem({ U"たたかう",U"にげる",U"",U"" });
		Firstmessage = String(U"モンスターがあらわれた");
		escapeMessage = String(U"逃げられる");
		const auto enemyNumber = Random(1u, 2u);

		for (uint32 i = 0; i < enemyNumber; i++)
		{
			uint32 typeNumber = Random(1, 3);
			if (enemyNumber == 1)
			{
				//引数　左から　名前 HP スピード　ぼうぎょ力　こうげき力　経験値　金
				if (typeNumber == 1)
				{
					enemies.push_back(EnemyData(U"ワーウルフ", 24, 17, 9, 13, 15, 10, { U"かみつく",U"つめとぎ",U"けいかい" }, { 500 ,250 }, { 250,250 }));
				}

				else if (typeNumber == 2)
				{
					enemies.push_back(EnemyData(U"メタルエッグ", 15, 5, 17, 11, 18, 8, { U"のしかかり",U"ロックガード" }, { 500 ,250 }, { 250,250 }));
				}

				else if (typeNumber == 3)
				{
					enemies.push_back(EnemyData(U"とげボール", 20, 10, 7, 17, 16, 15, { U"とげラッシュ",U"様子" ,U"こうげき" }, { 500 ,250 }, { 250,250 }));
				}

			}
			else
			{
				//引数　左から　名前 HP スピード　ぼうぎょ力　こうげき力　経験値　金
				if (typeNumber == 1)
				{
					enemies.push_back(EnemyData(U"ワーウルフ", 24, 17, 9, 13, 15, 10, { U"かみつく",U"つめとぎ",U"けいかい" }, { 200 + i * 300 ,250 }, { 250,250 }));
				}

				else if (typeNumber == 2)
				{
					enemies.push_back(EnemyData(U"メタルエッグ", 15, 5, 17, 11, 18, 8, { U"のしかかり",U"ロックガード" }, { 200 + i * 300 ,250 }, { 250,250 }));
				}

				else if (typeNumber == 3)
				{
					enemies.push_back(EnemyData(U"とげボール", 20, 10, 7, 17, 16, 15, { U"とげラッシュ",U"様子" ,U"こうげき" }, { 200 + i * 300 ,250 }, { 250,250 }));
				}
			}
		}

		Scene.push_back(String(U"SecondField"));
	}
	void init()
	{

	}
};

class Battle3 :public AllBattle
{
public:
	Battle3(const InitData& init) : AllBattle(init)
	{
		Image = std::make_unique<Images>(Images({ 0,0 }, { 1200,750 }, U"rockBackground"));
		AttackP = status.AttackPUp(getData().Level);
		DefenceP = status.DefencePUp(getData().Level);
		SpeedP = status.SpeedPUp(getData().Level);
		townM = AudioAsset(U"Town");
		AudioAsset(U"Town").setVolume(0.2);
		BattleM = AudioAsset(U"BattleM");
		AudioAsset(U"BattleM").setVolume(0.2);
		battle_com.setItem({ U"たたかう",U"にげる",U"",U"" });
		escapeMessage = String(U"逃げられる");
		Firstmessage = String(U"モンスターがあらわれた");
		const auto enemyNumber = Random(2u, 3u);

		for (uint32 i = 0; i < enemyNumber; i++)
		{
			uint32 typeNumber = Random(1, 4);

			//引数　左から　名前 HP スピード　ぼうぎょ力　こうげき力　経験値　金
			if (typeNumber == 1)
			{
				enemies.push_back(EnemyData(U"ワーウルフ", 37, 23, 9, 20, 23, 15, { U"かみつく",U"つめとぎ",U"けいかい" }, { 200 + i * 300 ,250 }, { 250,250 }));
			}

			else if (typeNumber == 2)
			{
				enemies.push_back(EnemyData(U"メタルエッグ", 18, 5, 20, 16, 29, 11, { U"のしかかり",U"ロックガード",U"様子" }, { 200 + i * 300 ,250 }, { 250,250 }));
			}

			else if (typeNumber == 3)
			{
				enemies.push_back(EnemyData(U"とげボール", 30, 10, 7, 24, 25, 20, { U"とげラッシュ",U"様子" ,U"こうげき" }, { 200 + i * 300 ,250 }, { 250,250 }));
			}
			else if (typeNumber == 4)
			{
				enemies.push_back(EnemyData(U"納豆坊", 40, 7, 8, 18, 21, 18, { U"ねばねば",U"つきさす",U"こうげき" }, { 200 + i * 300,250 }, { 250,250 }));
			}
		}

		Scene.push_back(String(U"ThirdField"));
	}
	void init()
	{

	}
};
class Arisu :public AllBattle
{
public:
	Arisu(const InitData& init) : AllBattle(init)
	{
		Image = std::make_unique<Images>(Images({ 0,0 }, { 1200,750 }, U"forest"));
		Firstmessage = String(U"魔法使いのアリスが\n勝負をしかけてきた");
		AttackP = status.AttackPUp(getData().Level);
		DefenceP = status.DefencePUp(getData().Level);
		SpeedP = status.SpeedPUp(getData().Level);
		townM = AudioAsset(U"Town");
		AudioAsset(U"Town").setVolume(0.2);
		BattleM = AudioAsset(U"BattleM");
		AudioAsset(U"BattleM").setVolume(0.2);
		battle_com.setItem({ U"たたかう",U"にげる",U"",U"" });
		escapeMessage = String(U"逃げられない");
		//引数　左から　名前 HP スピード　ぼうぎょ力　こうげき力　経験値　金
		enemies.push_back(EnemyData(U"アリス", 42, 15, 12, 18, 35, 20, { U"フレア", U"ルノバス" ,U"メーレ2",U"杖" }, { 500 ,250 }, { 155,235 }));
		Scene.push_back(String(U"FirstField"));
	}
	void init()
	{
	
	}

private:

};

class Donald :public AllBattle
{
public:
	Donald(const InitData& init) : AllBattle(init)
	{
		Image = std::make_unique<Images>(Images({ 0,0 }, { 1200,750 }, U"rockBackground"));
		Firstmessage = String(U"ピエロのドナルドが\n勝負をしかけてきた");
		escapeMessage = String(U"逃げられない");
		AttackP = status.AttackPUp(getData().Level);
		DefenceP = status.DefencePUp(getData().Level);
		SpeedP = status.SpeedPUp(getData().Level);
		townM = AudioAsset(U"Town");
		AudioAsset(U"Town").setVolume(0.2);
		BattleM = AudioAsset(U"BattleM");
		AudioAsset(U"BattleM").setVolume(0.2);
		battle_com.setItem({ U"たたかう",U"にげる",U"",U"" });
		//引数　左から　名前 HP スピード　ぼうぎょ力　こうげき力　経験値　金
		enemies.push_back(EnemyData(U"とげボール", 24, 10, 7, 20, 13, 15, { U"とげラッシュ",U"様子" }, { 200 ,250 }, { 250,250 }));
		enemies.push_back(EnemyData(U"ドナルド", 53, 18, 13, 24, 52, 20, { U"ただのパンチ", U"イリュージョンダンス" ,U"火吹き",U"ステップ" }, { 500 ,250 }, { 155,235 }));
		Scene.push_back(String(U"SecondField"));
	}
	void init()
	{

	}

private:

};
class Yellow :public AllBattle
{
public:
	Yellow(const InitData& init) : AllBattle(init)
	{
		Image = std::make_unique<Images>(Images({ 0,0 }, { 1200,750 }, U"rockBackground"));
		Firstmessage = String(U"イエローが勝負をしかけてきた。");
		escapeMessage = String(U"逃げられない");
		AttackP = status.AttackPUp(getData().Level);
		DefenceP = status.DefencePUp(getData().Level);
		SpeedP = status.SpeedPUp(getData().Level);
		townM = AudioAsset(U"Town");
		AudioAsset(U"Town").setVolume(0.2);
		BattleM = AudioAsset(U"BattleM");
		AudioAsset(U"BattleM").setVolume(0.2);
		battle_com.setItem({ U"たたかう",U"にげる",U"",U"" });
		//引数　左から　名前 HP スピード　ぼうぎょ力　こうげき力　経験値　金
		enemies.push_back(EnemyData(U"ワーウルフ", 35, 26, 10, 21, 20, 20, { U"かみつく",U"つめとぎ",U"けいかい" }, { 200 ,250 }, { 250,250 }));
		enemies.push_back(EnemyData(U"イエロー", 65, 20, 15, 28, 60, 40, { U"フレア", U"ボルテックス",  U"はどうショット", U"幻惑の瞳" ,U"メーレ3" }, { 500 ,250 }, { 155,235 }));
		enemies.push_back(EnemyData(U"メタルエッグ", 21, 5, 22, 18, 20, 20, { U"のしかかり",U"ロックガード" ,U"ボディープレス" }, { 800 ,250 }, { 250,250 }));

		Scene.push_back(String(U"Clear"));
	}
	void init()
	{
		
	}
};



class GameOver :public SceneManager<String, Gamedata>::Scene
{
public:


	GameOver(const InitData& init) : IScene(init)
	{

	}
	void draw() const override
	{
		Scene::SetBackground(Palette::Blue);
		font(texts[0]).draw(600, 300);
		font(texts[1]).draw(600, 500);
	}
	void update() override
	{
		if (KeySpace.up())
		{
			changeScene(U"In3");
			getData().pos = { 0,400 };
			getData().Hp = status.MaxHp(getData().Level)/2;
			getData().Mp = status.MaxMp(getData().Level)/2;
		}
	}
private:
	const Array<String> texts = {
	 U"Game Over",
	 U"Please click Enter"
	};

	Font font = Font(60);
	Status status;
};

class Break :public SceneManager<String, Gamedata>::Scene
{
public:
	Break(const InitData& init) : IScene(init)
	{

	}
	void draw() const override
	{
		Scene::SetBackground(Palette::Blue);
		font(text).draw(600, 300);
	}

	void update() override
	{
		if (KeyEnter.up())
		{
			changeScene(U"In3");
			getData().Hp = status.MaxHp(getData().Level), getData().Mp = status.MaxMp(getData().Level);
		}
	}

private:
	const String text = U"Please click Enter";
	Font font = Font(60);
	Status status;
	Audio breakM, townM;
};
