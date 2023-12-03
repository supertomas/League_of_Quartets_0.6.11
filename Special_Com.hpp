#pragma once
# include <Siv3D.hpp>
# include"Object.hpp"
class Skill_Com
{
public:
	void setList(std::vector<String> _items)
	{
		items = _items;
	}

	String selected() const
	{
		return items[select];
	}
	void update()
	{
		if (KeyUp.up())
		{
			AudioAsset(U"セレクト音").play();
			if (select != 0)
			{
				select--;
			}
		}
		if (KeyDown.up())
		{
			AudioAsset(U"セレクト音").play();
			if (select != items.size() - 1)
			{
				select++;
			}
		}
	}
	void draw() const
	{
		Rect frame,explain_message_frame;
		frame = Rect(820, 200, 360, 520);
		explain_message_frame = Rect(420, 200, 360, 220);
		frame.draw();
		explain_message_frame.draw();
		frame.stretched(2).drawFrame(2, 0, Palette::Black);
		frame.stretched(-2).drawFrame(2, 0, Palette::Black);
		explain_message_frame.stretched(2).drawFrame(2, 0, Palette::Black);
		explain_message_frame.stretched(-2).drawFrame(2, 0, Palette::Black);
		for (uint32 i = 0; i < items.size(); i++)
		{

			//int offset = (200 - font(items[i]).region().w) / 2;
			Point pos
			{
				870, 210 + i * 80
			};
			font(items[i]).draw(pos, Palette::Black);
		}
		switch (select)
		{
		case 0:
			Triangle({ 830, 220 }, { 860, 240 }, { 830, 260 }).draw(Palette::Black);
			font(Explain_Skill[0]).draw(440,200, Palette::Black);
			break;
		case 1:
			Triangle({ 830, 300 }, { 860, 320 }, { 830, 340 }).draw(Palette::Black);
			font(Explain_Skill[1]).draw(440,200 , Palette::Black);
			break;
		case 2:
			Triangle({ 830, 380 }, { 860, 400 }, { 830, 420 }).draw(Palette::Black);
			font(Explain_Skill[2]).draw( 440,200 , Palette::Black);
			break;
		case 3:
			Triangle({ 830, 460 }, { 860, 480 }, { 830, 500 }).draw(Palette::Black);
			font(Explain_Skill[3]).draw(440,200 , Palette::Black);
			break;
		case 4:
			Triangle({ 830, 540 }, { 860, 560 }, { 830, 580 }).draw(Palette::Black);
			font(Explain_Skill[4]).draw( 440,200 , Palette::Black);
			break;
		case 5:
			Triangle({ 830, 620 }, { 860, 640 }, { 830, 660 }).draw(Palette::Black);
			font(Explain_Skill[5]).draw(440,200 , Palette::Black);
			break;
		}

	}


private:
	std::vector<String> items;
	uint32 select = 0;
	Font font = Font(40);

	Array<String> Explain_Skill = {
		U"消費MP : 3\nアベルの攻撃力を\n一定値上昇",
		U"消費MP : 3\nアベルのHPを回復",
		U"MP回復呪文\nアベルのMPを\n一定値上昇",
		U"消費MP : 3\nアベルの防御力を\n一定値上昇",
		U"消費MP : 4\n敵にダメージを\n与えつつ、\n素早さを上げる",
		U"消費MP : 5\n敵全体にダメージ"
	};
};

class StatusMessage
{
public:
	void setList(std::vector<String> _items)
	{
		items = _items;
	}
	String selected() const
	{
		return items[5];
	}
	void draw() const
	{
		Rect frame;
		frame = Rect(720, 80, 460, 420);
		frame.draw();
		frame.stretched(2).drawFrame(2, 0, Palette::Black);
		frame.stretched(-2).drawFrame(2, 0, Palette::Black);
		for (uint32 i = 0; i < 5; i++)
		{
			Point pos
			{
				770, 90 + i * 80
			};
			font(items[i]).draw(pos, Palette::Black);
		}
	}

private:
	std::vector<String> items;
	Font font = Font(45);
};
