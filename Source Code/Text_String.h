#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;
class Text_String
{
public:
	Text_String(std::string Text, Font &Font, Vector2f Position, float Size, Color color, float OutlineThickness, Color OutlineColor);
	~Text_String();
	void Update(float Difference, RenderWindow &window);
	void Update_Text(std::string Text);
	void Draw(RenderWindow &window)
	{
		window.draw(Text_Body);
	}
	Text Text_Body;
private:
	float Count_Time = 0, Total_Time = 0;
	bool Text_Visible = true;
};

