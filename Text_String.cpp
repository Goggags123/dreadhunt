#include "Text_String.h"
#include <SFML\Graphics.hpp>
using namespace sf;


Text_String::Text_String(std::string Text, Font &Font, Vector2f Position, float Size, Color color,float OutlineThickness, Color OutlineColor)
{
	Text_Body.setFillColor(color);
	Text_Body.setFont(Font);
	Text_Body.setCharacterSize(Size);
	Text_Body.setString(Text);
	Text_Body.setPosition(Position);
	Text_Body.setOutlineThickness(OutlineThickness);
	Text_Body.setOutlineColor(OutlineColor);
}


Text_String::~Text_String()
{
}
void Text_String::Update(float Difference,RenderWindow &window)
{
	Total_Time += Difference;
	if (Total_Time >= 2.0)
	{
		Text_Visible = false;
	}
	if (Text_Visible)
	{
		Text_Body.move(0, -20*Difference);
		window.draw(Text_Body);
	}
}
void Text_String::Update_Text(std::string Text)
{
	Text_Body.setString(Text);
}
