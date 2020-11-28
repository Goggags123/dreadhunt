#include "Direct.h"
#include <SFML/Graphics.hpp>
#include "Animation.h"
using namespace sf;


Direct::Direct(Texture *Bullet_Texture, float angle, Vector2f Direction, float Damage,Vector2u Size, float Switch_Time)
	: Bullet_Animation(Bullet_Texture,Size,Switch_Time)
{
	Bullet.setTexture(*Bullet_Texture);
	Bullet_Texture->setSmooth(true);
	this->Damage = Damage;
	Bullet.setRotation(angle);
	Directions = Direction;
	Bullet.setOrigin(Bullet.getTextureRect().width / 2.0f/(float)Size.x, Bullet.getTextureRect().height / 2.0f/ (float)Size.y);
}


Direct::~Direct()
{
}

void Direct::Update(float Difference,RenderWindow &window)
{
	if (!isWave)
	{
		Total_Time += Difference;
		Bullet_Animation.Update(0, Difference);
		Bullet.setTextureRect(Bullet_Animation.uvReact);
		Bullet.setOrigin(Bullet.getTextureRect().width / 2.0f, Bullet.getTextureRect().height / 2.0f);
		if (Total_Time <= 0.5f)
		{
			window.draw(Bullet);
		}
	}
	else
	{
		Bullet_Animation.Update(0, Difference);
		Bullet.setTextureRect(Bullet_Animation.uvReact);
		Bullet.setOrigin(Bullet.getTextureRect().width / 2.0f, Bullet.getTextureRect().height / 2.0f);
		window.draw(Bullet);
	}
}



