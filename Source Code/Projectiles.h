#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Animation.h"
using namespace sf;
class Projectiles
{
public:
	Projectiles(Texture *Bullet_Texture, Vector2f Distance, float Expected_BulletSpeed,Vector2u Size,float Switch_Time,float Damage);
	~Projectiles();
	void fire(float Difference)
	{
		float ratio = Expected_BulletSpeed / Real_BulletSpeed;
		xvelocity = Real_BulletSpeed * cos(angle);
		yvelocity = Real_BulletSpeed * sin(angle) - 9.81*t;
		if (Distance.x < 0) xvelocity *= -1;
		yvelocity *= -1.0f;
		t = t + Difference * ratio;
		if (!isMoving)
		{
			yvelocity = 0.0f;
			xvelocity = 0.0f;
		}
		Bullet.move(xvelocity*Difference*ratio, yvelocity*Difference*ratio);
	}
	void setPos(Vector2f Position)
	{
		Bullet.setPosition(Position);
	}
	Sprite& Get_Body()
	{
		return Bullet;
	}
	void Draw(RenderWindow &window)
	{
		window.draw(Bullet);
	}
	void Update(float Difference, RenderWindow &window);
	float xvelocity, yvelocity;
	bool isMoving = true;
	int Damage = 0; 
private:
	Sprite Bullet;
	Animation Projectile_Animation;
	Vector2f Directions;
	Vector2f Distance;
	float t = 0;
	float angle, Expected_BulletSpeed, Real_BulletSpeed;
};

