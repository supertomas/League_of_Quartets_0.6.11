#pragma once
#include"Object.hpp"
class Text
{
public:

	bool onFinish = false;
	int32 duration = 40;
	Stopwatch stopwatch;
	String flag;
	Font font;
	int32 messageIndex;
	Array<String> messages;
	int32 index;
	bool all;
	Array<Array<String>> scenario = 
	{
		Array<String>
		{
			U"住民A「かがくの　ちからって　すげー！\nSiv3D を　つかうと　みじかい　コードで",
			U"えや　もじを　ひょうじしたり\nおんがくを　ならしたり　できるんだ！」"
		},
		Array<String>
		{
			U"ピエロ「ついに 旅に出るんだな。\nあたらしい であい やモンスターが",
			U"きみを まっているぞ !」"
		},
		Array<String>
		{
			U"住民B「ここは いなかだからな 村をでると\nすぐモンスターがおそってくる。",
			U"はやく都会に引っ越したいものだな」"
		},
		Array<String>
		{
			U"住民C「アベル。イエローとのバトルに\n挑むんだろ!?  あいつなら、",
			U"ここから北の砂漠にいるはずだぜ !!」"
		},
		Array<String>
		{
			U"アベル「今日 は 寝るか・・」",
			U"flag Break"
		},
		Array<String>
		{
			U"メアリー「このさき モンスターがでるけど \nあなたの パワーがあれば倒せるはずよ",
			U"つかれたら家のベッドで休むといいわ。」"
		},
		Array<String>
		{
			U"さっき落石があってな。このさき 通れない\nんだ。すまないがべつの道を行ってくれ。",
		},
		
		Array<String>
		{
			U"アリス「イエローからの挑戦を受ける\nのね。 それならうでだめしに",
			U" このわたしとバトルしましょ !」",
			U"flag Arisu"
		},
		Array<String>
		{
			U"イエロー「この俺を倒しに来たのか...\nせいぜい楽しませてくれよ !」",
			U"flag Yellow"
		},
		Array<String>
		{
			U"敵が群れでおそってきたらさすがの\nおれでもにげるしかないぜ",
			U"おれにもっとじゅもんの 才能があれば...."
		},
		Array<String>
		{
			U"アリス「なかなかやるわね。\n私の負けよ。」"
		},
		Array<String>
		{
			U"ドナルド「目があったらバトルです。\nいきますよ とげボール !!!」",
			U"flag Donald"
		},
		Array<String>
		{
			U"イエロー「俺とのバトルに挑みたいものは\n北の砂漠までこい !!」"
		},
		Array<String>
		{
			U"ドナルド「イエローは2体のモンスター\nを従えています。 レベルを上げて",
			U"全体攻撃の技を覚えた方が\nいいかもしれません」"
		},
		Array<String>
		{
			U"チャレンジャー「あのイエローってやつ...\n おいらじゃ手も足も出なかったぞ",
			U"お前も心して挑んだ方がいいぜ ！」"
		}
	};

	

	Text();

	String getFlag()
	{
		String flag2;
		flag2 = flag;
		flag = U"";
		return flag2;
	}

	Rect frame() const;

	void text();

	void update();

	void draw() const;

	void start(int32 phrase);

	bool isActive() const;

	void start(const Array<String> &text);
};
