#pragma once
#include <SFML\Graphics.hpp>
#include "Projectiles.h"
#include "Floor.h"
using namespace sf;
class Item
{
public:
	Item(Texture *Item_Texture,Vector2f Distance,float Bullet_Speed, Vector2u Size, float Switch_Time,int Score);
	~Item();
	Sprite &Body()
	{
		return Item_Body;
	}
	void Update(float Difference,RenderWindow &window);
	void draw(RenderWindow &window)
	{
		window.draw(Item_Body);
	}
	Sprite& Get_Body()
	{
		return Item_Body;
	}
	bool Item_Visible = true,isDropping = true;
	bool isShield = false;
	bool isWave = false;
	bool isArrow = false;
	bool isLob = false;
	bool isLaser = false;
	bool isFood = false;
	int Health = 0;
	Projectiles Item_Projectiles;
	int Score = 0;
private:
	Sprite Item_Body;
	Vector2f Distance;
};

