#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
using namespace sf;
class WarpGate
{
public:
	WarpGate(Texture *Warpgate_Texture,Vector2f Position,int to,Vector2u Size,float Switch_Time);
	void Update(float Difference, RenderWindow &window);
	~WarpGate();
	Sprite &Get_Body()
	{
		return Body;
	}
	int to;
private:
	Animation Warpgate_Animation;
	Sprite Body;
};

