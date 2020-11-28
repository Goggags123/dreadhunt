#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
using namespace sf;
class Explosion
{
public:
	Explosion(Texture *Explostion_Texture, Vector2u Size, float Switch_Time);
	~Explosion();
	void setPosition(Vector2f Position)
	{
		Explosion_Body.setPosition(Position);
	}
	void Update(float Difference);
	Animation Explosion_Animation;
	Sprite Explosion_Body;
	bool Explosion_Visible =true;
	int Damage = 0;
	bool Damagable = false;
};

