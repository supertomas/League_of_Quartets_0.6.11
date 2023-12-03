#pragma once
# include <Siv3D.hpp>
#include<HamFramework.hpp>
#include"Object.hpp"
class Title :public MyApp::Scene
{
public:
	int choice = 0;
	Title(const InitData& init) :
		IScene(init)

	{
		TextureAsset::Register(U"sky", U"Images/sky.jpg");
		TextureAsset::Register(U"title2", U"Images/title2.png");
	}
	void init()
	{
		TextureAsset::Register(U"sky", U"Images/sky.jpg");
		TextureAsset::Register(U"title2", U"Images/title2.png");
	}
	void update() override
	{
		if (choice % 2 == 0 && KeyEnter.up())
		{
			changeScene(U"In3");
			AudioAsset(U"decide").play();
		}
		if (choice % 2 == 1 && KeyEnter.up())
		{
			changeScene(U"HowToPlay");
			AudioAsset(U"decide").play();
		}
		if (KeyDown.up())
		{
			choice = 1;
		}
		if (KeyUp.up())
		{
			choice = 0;
		}
	}
	void draw() const override
	{
		TextureAsset(U"sky").scaled(0.8, 0.8).draw();
		TextureAsset(U"title").scaled(1.0, 1.0).draw();
		fonts[0](U"ゲームスタート").draw(920, 480, Palette::Black);
		fonts[0](U"操作方法").draw(920, 580, Palette::Black);
		for (int i = 0; i < 2; i++)
		{
			if (choice == 0 + i * 1)
			{
				Triangle({ 820, 470 + i * 100 }, { 860, 500 + i * 100 }, { 820, 530 + i * 100 }).draw(Palette::Black);
			}
		}
		fonts[1](U"エンターキーをおしてね").draw(100, 550, Palette::Black);
	}
private:

	Array<Font> fonts = {
		Font(40),
		Font(60)
	};
};

class Images
{
public:
	Images(Point _pos, Point _size, String _texture)
	{
		pos = _pos;
		size = _size;
		texture = _texture;
	};
	
	Rect getBody() const
	{
		return Rect(pos.x, pos.y, size.x, size.y);
	}
	void draw()
	{
		getBody()(TextureAsset(texture)).draw();
	}
private:
	Point pos, size;
	String texture;
};

class HowToPlay :public MyApp::Scene
{
public:
	Array<std::unique_ptr <Images>> Image;
	HowToPlay(const InitData& init) :
		IScene(init)
	{
		TextureAsset::Register(U"sky", U"Images/sky.jpg");
		Image.push_back(std::make_unique<Images>(Images({ 100,50 }, { 150,150 }, U"cross")));
		Image.push_back(std::make_unique<Images>(Images({ 100,250 }, { 150,150 }, U"enter")));
		Image.push_back(std::make_unique<Images>(Images({ 100,450 }, { 180,100 }, U"space")));
	}

	void init()
	{

	}
	void update() override
	{
		Scene::SetBackground(Palette::White);
		if (KeySpace.up())
		{
			changeScene(U"Title");
		}
	}
	void draw() const override
	{
		fonts[0](U"主人公のいどうやこうもく\nの選択に使う").draw(300, 40, Palette::Black);
		fonts[0](U"決定する しらべる 話しかける\n話しをすすめるときに使う").draw(300, 240, Palette::Black);
		fonts[0](U"やめる もどるなどのときに使う").draw(300, 450, Palette::Black);
		fonts[1](U"スペースキーをおしてね").draw(150, 550, Palette::Black);
		for (auto& i : Image)
		{
			i->draw();
		}
	}
private:
	Array<Font> fonts = {
		Font(30),
		Font(40)
	};
};

