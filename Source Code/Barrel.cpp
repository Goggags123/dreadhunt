#include "Barrel.h"
#include "SFML\Graphics.hpp"
#include "Animation.h"
using namespace sf;

Barrel::Barrel(Texture *Barrel_Texture, Vector2f Position, float HP,Vector2u Size,float Switch_Time)
	: Barrel_Animation(Barrel_Texture,Size,Switch_Time)
{
	this->Barrel_Hp = HP;
	Barrel_Texture->setSmooth(true);
	Barrel_Body.setTexture(*Barrel_Texture);
	Barrel_Body.setOrigin(Barrel_Body.getTextureRect().width / 2.0f / (float)Size.x, Barrel_Body.getTextureRect().height / 2.0f / (float)Size.y);
	Barrel_Body.setPosition(Position);
}


Barrel::~Barrel()
{
}

void Barrel::Update(float Difference,RenderWindow &window)
{
	if (Barrel_Visible)
	{
		if (Barrel_Hp <= 0)
		{
			isDying = true;
			game_frame++;
			if (game_frame >= 50)
			{
				Barrel_Visible = false;
				isDying = false;
			}
		}
		Barrel_Animation.Update(0, Difference);
		Barrel_Body.setTextureRect(Barrel_Animation.uvReact);
		Barrel_Body.setOrigin(Barrel_Body.getTextureRect().width / 2.0f, Barrel_Body.getTextureRect().height / 2.0f);
	}
	
	if (Barrel_Visible&&game_frame%4==0)
	{
		window.draw(Barrel_Body);
	}
}
