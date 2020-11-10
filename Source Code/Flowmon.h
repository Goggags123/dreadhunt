#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Floor.h"
#include "Direct.h"
#include <vector>
using namespace sf;
class Flowmon
{
public:
	enum Action { LIdle, LCrunch, LShoot, LDie, Idle, Crunch, Shoot, Die };
	Flowmon(Texture *Flowmon_Texture, Vector2u Size, float Switch_Time, Vector2f Position);
	void Flowmon_Update(float Difference, Vector2f Player_Position, std::vector <Direct> &Flowmon_Ball, RenderWindow &window);
	Vector2f Get_Position()
	{
		return Flowmon_Body.getPosition();
	}
	Sprite& Get_Body()
	{
		return Flowmon_Body;
	}
	void Draw(RenderWindow &window)
	{
		window.draw(Flowmon_Body);
	}
	int Score = 50;
	int Flowmon_Health = 40;
	std::string name = "Doomvine";
	bool Flowmon_Visible = true, isDying = false;
	~Flowmon();
private:
	float Count_Time=0,Total_Time=0,Vector_Size,angle;
	Sprite Flowmon_Body;
	Vector2f Direction_Bullet;
	Animation Flowmon_Animation;
	Texture FlowmonBall_Texture;
	float Switch_Time;
	Vector2u Size;
	int Row;
	bool isFiring = false;
	RectangleShape HP_Bar;
	Font Title_Font;
	Text Name;
};

