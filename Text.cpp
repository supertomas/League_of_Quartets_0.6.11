# include "Text.hpp"
Text::Text() :
	stopwatch(StartImmediately::No),
	font(42),
	index(0),
	messageIndex(0),
	all(false)
{}

Rect Text::frame() const
{
	return Rect(200, 480, 900, 200);
}

void Text::text()
{
	index = stopwatch.ms() / duration;
	all = index >= messages[messageIndex].length();
	if (KeyEnter.up() && stopwatch.ms() > 0)
	{
		
		if (all)
		{
			++messageIndex;

			stopwatch.restart();
			if (messageIndex == messages.size())
			{
				messageIndex = 0;
				stopwatch.reset();
				onFinish = true;
				return;
			}
			else
			{
				if (messages[messageIndex].starts_with(U"flag "))
				{
					flag = messages[messageIndex].substr(5);
					messageIndex = 0;
					stopwatch.reset();
					onFinish = true;
					return;
				}
			}
		}
		else
		{
			stopwatch.set(100000ms);
		}

	}
}
bool Text::isActive() const
{
	return stopwatch.isStarted() || onFinish;
}
void Text::update()
{
	if (isActive())
	{
		onFinish = false;
		text();
	}
}

void Text::draw() const
{
	if (isActive())
	{
		frame().draw();
		frame().stretched(3).drawFrame(3, 0, Palette::Black);
		frame().stretched(-3).drawFrame(3, 0, Palette::Black);
		font(messages[messageIndex].substr(0, index)).draw(frame().pos + Point(30, 20), Palette::Black);
		if (all && stopwatch.ms() % 1000 < 500)
		{
			Triangle(frame().br() - Point(38, 40), 40, 180_deg).draw(Palette::Black);
		}
	}
	Mat3x2::Identity();
}

void Text::start(int32 phrase)
{
	if (isActive() == false)
	{
		stopwatch.restart();
		messages = scenario[phrase];
	}
}

void Text::start(const Array<String> &text)
{
	if (isActive() == false)
	{
		stopwatch.restart();
		messages = text;
	}
}
