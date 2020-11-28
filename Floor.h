#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;
class Floor
{
public:
	Floor(Texture *Platform_Texture, Vector2f Position);
	~Floor();
	void Draw(RenderWindow &window)
	{
		window.draw(Platform);
	}
	Sprite& Body()
	{
		return Platform;
	}
	Vector2f Position()
	{
		return Platform.getPosition();
	}
	FloatRect Get_Size()
	{
		return Platform.getGlobalBounds();
	}
		
private:
	Sprite Platform;
};

