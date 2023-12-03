#pragma once
# include <Siv3D.hpp>
class Battle_Escape_Com
{
public:
	std::array<String, 4> items;
	void setItem(std::array<String, 4> _items)
	{
		items = _items;
		select = 0;
	}
	String selected() const
	{
		return items[select];
	}
	void update()
	{
		if (KeyRight.up() && select == 0 || KeyUp.up() && select == 3)
		{
			AudioAsset(U"セレクト音").play();
			if (!items[1].isEmpty())
			{
				select = 1;
			}
		}
		else if (KeyLeft.up() && select == 1 || KeyUp.up() && select == 2)
		{
			AudioAsset(U"セレクト音").play();
			if (!items[0].isEmpty())
			{
				select = 0;
			}
		}
		else if (KeyDown.up()&& select == 0 || KeyLeft.up() && select == 3)
		{
			AudioAsset(U"セレクト音").play();
			if (!items[2].isEmpty())
			{
				select = 2;
			}
		}
		else if (KeyDown.up() && select == 1 || KeyRight.up() && select == 2)
		{
			AudioAsset(U"セレクト音").play();
			if (!items[3].isEmpty())
			{
				select = 3;
			}
		}
	}

	void draw() const
	{
		Rect frame;
		if (!items[2].isEmpty() || !items[3].isEmpty())
		{
			frame = Rect(250, 550, 520, 170);
		}
		else
		{
			frame = Rect(250, 550, 520, 100);
		}
		frame.draw();
		frame.stretched(2).drawFrame(2, 0, Palette::Black);
		frame.stretched(-2).drawFrame(2, 0, Palette::Black);
		for (uint32 i = 0; i < items.size(); i++)
		{
			int offset = (200 - font(items[i]).region().w) / 2;
			Point pos
			{
				(i % 2) * 280 + 290 + offset, (i / 2) * 90 + 560
			};
			font(items[i]).draw(pos, Palette::Black);
		}

		switch (select)
		{
		case 0:
			Triangle({ 260, 570 }, { 290, 590 }, { 260, 610 }).draw(Palette::Black);
			break;
		case 1:
			Triangle({ 540, 570 }, { 570, 590 }, { 540, 610 }).draw(Palette::Black);
			break;
		case 2:
			Triangle({ 260, 660 }, { 290, 680 }, { 260,700 }).draw(Palette::Black);
			break;
		case 3:
			Triangle({ 540, 660 }, { 570, 680 }, { 540, 700 }).draw(Palette::Black);
			break;
		}
	}

private:
	Font font = Font(40);
	int select = 0;
};


