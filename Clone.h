#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include <vector>
#include "Floor.h"
#include "Collision.h"
#include "Direct.h"
#include "Explosion.h"
using namespace sf;
class Clone
{
public:
	enum Action { Idle, Die, LIdle, LDie };
	Clone(Texture *Clone_Texture, Vector2u Size, float Switch_Time, Vector2f Position);
	~Clone();
	bool Clone_Visible = true,isDying = false;
	int Score = 0;
	float Clone_Health = 1;
	void Update(float Difference, Vector2f Player_Position, RenderWindow &window, std::vector <Floor> &Platforms, std::vector <Direct> &Firephoon);
	Sprite &Get_Body()
	{
		return Body;
	}
	int Count = 0;
private:
	float Count_Time = 0, Total_Time = 0, Vector_Size, angle;
	Sprite Body;
	int moves;
	Vector2f Direction_Bullet;
	Animation Clone_Animation;
	Texture Fireball_Texture;
	int Row;
	bool isFiring = false;

};

