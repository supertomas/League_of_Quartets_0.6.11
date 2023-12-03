#include"TextManager.hpp"
#include"Text.hpp"

Text* TextManager::text;
void TextManager::Create()
{
	text = new Text();
}
