#pragma once
#include "SFML\Graphics.hpp"
#include "Animation.h"
using namespace sf;

class Barrel
{
public:
	enum Action {Idle,Die};
	Barrel(Texture *Barrel_Texture,Vector2f Position,float HP, Vector2u Size, float Switch_Time);
	~Barrel();
	int Barrel_Hp;
	bool Barrel_Visible = true;
	void Update(float Difference, RenderWindow &window);
	bool isDying = false;
	bool isIceShield = false;
	Sprite& Get_Body()
	{
		return Barrel_Body;
	}
private:
	int Row = Action::Idle;
	Sprite Barrel_Body;
	int game_frame = 0;
	Animation Barrel_Animation;
};

