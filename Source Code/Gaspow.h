#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Floor.h"
#include "Direct.h"
#include <vector>
using namespace sf;
class Gaspow
{
public:
	enum Action {Idle,Shoot,LIdle,LShoot };
	Gaspow(Texture *Gaspow_Texture, Vector2u Size, float Switch_Time, Vector2f Position);
	void Gaspow_Update(float Difference, Vector2f Player_Position, std::vector <Direct> &Gaspow_Ball, RenderWindow &window);
	Vector2f Get_Position()
	{
		return Gaspow_Body.getPosition();
	}
	Sprite& Get_Body()
	{
		return Gaspow_Body;
	}
	void Draw(RenderWindow &window)
	{
		window.draw(Gaspow_Body);
	}
	int Score = 50;
	int Gaspow_Health = 35;
	std::string name = "Gaspow";
	bool Gaspow_Visible = true, isDying = false;
	~Gaspow();
private:
	float Count_Time = 0, Total_Time = 0,angle;
	Sprite Gaspow_Body;
	Vector2f Direction_Bullet;
	Animation Gaspow_Animation;
	Texture GaspowBall_Texture;
	float Switch_Time;
	Vector2u Size;
	int Row;
	int game_frame = 0;
	bool isFiring = false;
	RectangleShape HP_Bar;
	Text Name;
	Font Title_Font;
};

