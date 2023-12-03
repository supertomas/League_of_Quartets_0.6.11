# include <Siv3D.hpp>
#include"Battle.hpp"
#include"InScene.hpp"
#include"Title.hpp"
#include"Field_Scene.hpp"
#include"stdafx.h"

void Main()
{
	Window::SetTitle(U"リーグオブカルテット");
	Window::Resize(1200, 750);

	MyApp manager;
	manager.add<Title>(U"Title");
	manager.add<HowToPlay>(U"HowToPlay");
	manager.add<In3>(U"In3");
	manager.add<In1>(U"In");
	manager.add<In2>(U"In2");
	manager.add<firstCity>(U"FirstCity");
	manager.add<firstField>(U"FirstField");
	manager.add<GameOver>(U"Gameover");
	manager.add<Break>(U"Break");
	manager.add<secondField>(U"SecondField");
	manager.add<thirdField>(U"ThirdField");
	manager.add<Clear>(U"Clear");
	manager.add<Battle>(U"Battle");
	manager.add<Battle2>(U"Battle2");
	manager.add<Battle3>(U"Battle3");
	manager.add<Yellow>(U"Yellow");
	manager.add<Arisu>(U"Arisu");
	manager.add<Donald>(U"Donald");


	//オブジェクト
	TextureAsset::Register(U"blackboard", U"Images/blackboard.png");
	TextureAsset::Register(U"floor", U"Images/floor.png");
	TextureAsset::Register(U"wallR", U"Images/wallRight.jpg");
	TextureAsset::Register(U"wallL", U"Images/wallLeft.jpg");
	TextureAsset::Register(U"wall", U"Images/wall.jpg");
	TextureAsset::Register(U"ground", U"Images/ground.png");
	TextureAsset::Register(U"school", U"Images/school.png");
	TextureAsset::Register(U"tree1", U"Images/tree1.png");
	TextureAsset::Register(U"building", U"Images/building.png");
	TextureAsset::Register(U"wallL", U"Images/wallL.png");
	TextureAsset::Register(U"wallR", U"Images/wallR.png");
	TextureAsset::Register(U"cross", U"Images/cross.png");
	TextureAsset::Register(U"enter", U"Images/enter.jpg");
	TextureAsset::Register(U"space", U"Images/space.png");

	//家や背景
	TextureAsset::Register(U"house", U"Images/house.png");
	TextureAsset::Register(U"indoor", U"Images/indoor2.png");
	TextureAsset::Register(U"house2", U"Images/house2.png");
	TextureAsset::Register(U"mainHouse", U"Images/AberuIndoor.png");
	TextureAsset::Register(U"desk", U"Images/desk.png");
	TextureAsset::Register(U"chair", U"Images/chair.png");


	TextureAsset::Register(U"flower", U"Images/flower.png");
	TextureAsset::Register(U"grass", U"Images/grass.png");
	TextureAsset::Register(U"soil", U"Images/soil.jpg");
	TextureAsset::Register(U"soil2", U"Images/soil2.png");
	TextureAsset::Register(U"stone", U"Images/stone1.png");
	TextureAsset::Register(U"title", U"Images/title.png");
	TextureAsset::Register(U"title2", U"Images/title2.png");
	TextureAsset::Register(U"forest", U"Images/forest.png");
	TextureAsset::Register(U"rockBackground", U"Images/rockBackground.png");
	//キャラ
	TextureAsset::Register(U"CharaL", U"Images/chara/CharaL.png");
	TextureAsset::Register(U"CharaR", U"Images/chara/CharaR.png");
	TextureAsset::Register(U"CharaB", U"Images/chara/CharaB.png");
	TextureAsset::Register(U"CharaF", U"Images/chara/CharaF.png");

	TextureAsset::Register(U"AberuL", U"Images/chara/AberuL.png");
	TextureAsset::Register(U"AberuR", U"Images/chara/AberuR.png");
	TextureAsset::Register(U"AberuB", U"Images/chara/AberuB.png");
	TextureAsset::Register(U"AberuF", U"Images/chara/AberuF.png");

	TextureAsset::Register(U"Mobu1L", U"Images/chara/Mobu1L.png");
	TextureAsset::Register(U"Mobu1R", U"Images/chara/Mobu1R.png");
	TextureAsset::Register(U"Mobu1B", U"Images/chara/Mobu1B.png");
	TextureAsset::Register(U"Mobu1F", U"Images/chara/Mobu1F.png");

	TextureAsset::Register(U"Mobu2L", U"Images/chara/Mobu2L.png");
	TextureAsset::Register(U"Mobu2R", U"Images/chara/Mobu2R.png");
	TextureAsset::Register(U"Mobu2B", U"Images/chara/Mobu2B.png");
	TextureAsset::Register(U"Mobu2F", U"Images/chara/Mobu2F.png");

	TextureAsset::Register(U"DoctorL", U"Images/chara/DoctorL.png");
	TextureAsset::Register(U"DoctorR", U"Images/chara/DoctorR.png");
	TextureAsset::Register(U"DoctorB", U"Images/chara/DoctorB.png");
	TextureAsset::Register(U"DoctorF", U"Images/chara/DoctorF.png");

	TextureAsset::Register(U"Lady1L", U"Images/chara/Lady1L.png");
	TextureAsset::Register(U"Lady1R", U"Images/chara/Lady1R.png");
	TextureAsset::Register(U"Lady1B", U"Images/chara/Lady1B.png");
	TextureAsset::Register(U"Lady1F", U"Images/chara/Lady1F.png");

	TextureAsset::Register(U"PieroL", U"Images/chara/PieroL.png");
	TextureAsset::Register(U"PieroR", U"Images/chara/PieroR.png");
	TextureAsset::Register(U"PieroB", U"Images/chara/PieroB.png");
	TextureAsset::Register(U"PieroF", U"Images/chara/PieroF.png");

	TextureAsset::Register(U"MajyoL", U"Images/chara/MajyoL.png");
	TextureAsset::Register(U"MajyoR", U"Images/chara/MajyoR.png");
	TextureAsset::Register(U"MajyoB", U"Images/chara/MajyoB.png");
	TextureAsset::Register(U"MajyoF", U"Images/chara/MajyoF.png");
	//敵
	TextureAsset::Register(U"ワーウルフ", U"Images/Enemy/wolf.png");
	TextureAsset::Register(U"キャロットマン", U"Images/Enemy/carotman.png");
	TextureAsset::Register(U"とげボール", U"Images/Enemy/togebo.png");
	TextureAsset::Register(U"メタルエッグ", U"Images/Enemy/metaruEgg.png");
	TextureAsset::Register(U"ピエロ", U"Images/Enemy/piero.png");
	TextureAsset::Register(U"納豆坊", U"Images/Enemy/natto.png");
	TextureAsset::Register(U"イエロー", U"Images/Enemy/a.png");
	TextureAsset::Register(U"アリス", U"Images/Enemy/majyo.png");
	TextureAsset::Register(U"ドナルド", U"Images/Enemy/piero.png");
	//音
	AudioAsset::Register(U"wall", U"Sound/wall.wav");
	AudioAsset::Register(U"damage", U"Sound/damage.wav");
	AudioAsset::Register(U"カーソル音", U"Sound/カーソル音.mp3");
	AudioAsset::Register(U"セレクト音", U"Sound/セレクト音.mp3");
	AudioAsset::Register(U"キャンセル", U"Sound/キャンセル.mp3");
	AudioAsset::Register(U"fire", U"Sound/fire.wav");
	AudioAsset::Register(U"decide", U"Sound/choice.mp3");
	AudioAsset::Register(U"話しかける", U"Sound/話しかける.mp3");
	AudioAsset::Register(U"Town", U"Sound/town.mp3", AudioLoopTiming(true));
	AudioAsset::Register(U"BattleM", U"Sound/battle.wav", AudioLoopTiming(true));
	AudioAsset::Register(U"break", U"Sound/break.mp3", AudioLoopTiming(true));
	//攻撃エフェクト
	TextureAsset::Register(U"effect", U"Images/攻撃effect.png");

	TextManager::Create();
	while (System::Update())
	{
		manager.updateScene();
		manager.drawScene();
	}

}

