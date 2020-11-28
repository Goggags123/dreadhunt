#include "Floor.h"
#include <SFML\Graphics.hpp>
using namespace sf;



Floor::Floor(Texture *Platform_Texture,Vector2f Position)
{
	Platform.setTexture(*Platform_Texture);

	Platform.setPosition(Position);
}


Floor::~Floor()
{
}
