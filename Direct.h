#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
using namespace sf;
class Direct
{
public:
	Direct(Texture *Bullet_Texture, float angle, Vector2f Direction, float Damage, Vector2u Size, float Switch_Time);
	~Direct();
	void Draw(RenderWindow &window)
	{
		window.draw(Bullet);
	}
	void setPos(Vector2f Position)
	{
		Bullet.setPosition(Position);
	}
	void fire(float Bullet_Speed,float Difference, Vector2f Direction)
	{
		Bullet.move(Bullet_Speed*Difference*Direction);
	}
	Vector2f Get_Direction()
	{
		return Directions;
	}
	Sprite& Get_Body()
	{
		return Bullet;
	}
	void Update(float Difference, RenderWindow &window);
	int Damage;
	bool Visible = true;
	Animation Bullet_Animation;
	bool isWave = false;
	bool isAbsorb = false;
private:
	Texture Bullet_Texture;
	float angle,Bullet_Speed;
	Sprite Bullet;
	Vector2f Directions;
	float Total_Time = 0, Current_Time = 0;
};

