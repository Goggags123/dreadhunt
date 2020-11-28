#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include <vector>
#include "Floor.h"
#include "Collision.h"
using namespace sf;
class Foulling
{
public:
	enum Action {Walk,Rush,Die,LWalk, LRush, LDie};
	Foulling(Texture *Foulling_Texture,Vector2u Size,float Switch_Time,Vector2f Position,Vector2f xPos);
	~Foulling();
	bool Foulling_Visible = true, isDying = false;
	int Score = 70;
	float Foulling_Health = 30;
	void Update(float Difference, Vector2f Player_Position, RenderWindow &window, std::vector <Floor> &Platforms);
	Sprite &Get_Body()
	{
		return Foulling_Body;
	}
	std::string name = "Foulling";
private:
	float Count_Time = 0, Total_Time = 0;
	Sprite Foulling_Body,Ghost_Body;
	Animation Foulling_Animation;
	int Row = Action::Walk;
	float multiplier = 1;
	bool yes = true;
	float Speed = 100;
	Vector2f xPos,Position;
	RectangleShape HP_Bar;
	bool isMoving = false,isRushing = false,Can_Move = false;
	Text Name;
	Font Title_Font;
};

