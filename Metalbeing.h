#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include <vector>
#include "Floor.h"
#include "Collision.h"
using namespace sf;
class Metalbeing
{
public:
	enum Action { LIdle, LWalk, LDie, Idle, Walk, Die };
	Metalbeing(Texture *Metalbeing_Texture, Vector2u Size, float Switch_Time, Vector2f Position, Vector2f xPos);
	~Metalbeing();
	bool Metalbeing_Visible = true;
	int Score = 0;
	float Metalbeing_Health = 10;
	Sprite &Get_Body()
	{
		return Metalbeing_Body;
	}
	void Update(float Difference, Vector2f Player_Position, RenderWindow &window, std::vector <Floor> &Platforms);
	bool isDying = false;
	std::string name = "Metalbeing";
private:
	float Total_Time = 0;
	Sprite Metalbeing_Body, Ghost_Body;
	Animation Metalbeing_Animation;
	int Row;
	bool Can_Move = false;
	float Speed = 50;
	Vector2f movement;
	Vector2f xPos,Position;
	RectangleShape HP_Bar;
	Font Title_Font;
	Text Name;

};


