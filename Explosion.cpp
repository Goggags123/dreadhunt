#include "Explosion.h"
#include "Animation.h"
#include <SFML\Graphics.hpp>
using namespace sf;
Explosion::Explosion(Texture *Explostion_Texture,Vector2u Size,float Switch_Time) : Explosion_Animation (Explostion_Texture,Size, Switch_Time)
{
	Explostion_Texture->setSmooth(true);
	Explosion_Body.setTexture(*Explostion_Texture);
	Explosion_Body.setOrigin(Explosion_Body.getTextureRect().width / 2.0f / (float)Size.x, Explosion_Body.getTextureRect().height / 2.0f / (float)Size.y);
	Explosion_Animation.Current_Image.x = 0;
	Explosion_Animation.Visible = true;
}


Explosion::~Explosion()
{
}

void Explosion::Update(float Difference)
{
	Explosion_Animation.Update(0, Difference);
	Explosion_Body.setTextureRect(Explosion_Animation.uvReact);
	Explosion_Body.setOrigin(Explosion_Body.getTextureRect().width / 2.0f, Explosion_Body.getTextureRect().height / 2.0f);
	if (!Explosion_Animation.Visible)
	{
		Explosion_Visible = false;
	}
}
