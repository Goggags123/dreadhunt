#include "WarpGate.h"
#include "Animation.h"
#include <SFML\Graphics.hpp>
using namespace sf;

WarpGate::WarpGate(Texture *Warpgate_Texture, Vector2f Position, int to, Vector2u Size, float Switch_Time)
	: Warpgate_Animation(Warpgate_Texture,Size,Switch_Time)
{
	Warpgate_Texture->setSmooth(true);
	Body.setTexture(*Warpgate_Texture);
	this->to = to;
	Body.setOrigin(Body.getTextureRect().width / 2.0f / (float)Size.x, Body.getTextureRect().height / 2.0f / (float)Size.y);
	Body.setPosition(Position);
}

void WarpGate::Update(float Difference, RenderWindow & window)
{
	Warpgate_Animation.Update(0, Difference);
	Body.setTextureRect(Warpgate_Animation.uvReact);
	Body.setOrigin(Body.getTextureRect().width / 2.0f, Body.getTextureRect().height / 2.0f);
	window.draw(Body);
}


WarpGate::~WarpGate()
{
}
