#include "Item.h"
#include "Collision.h"
#include "Projectiles.h"
#include <SFML\Graphics.hpp>
#include "Floor.h"
using namespace sf;


Item::Item(Texture *Item_Texture,Vector2f Distance,float Bullet_Speed,Vector2u Size,float Switch_Time,int Score)
	: Item_Projectiles(Item_Texture,Distance,Bullet_Speed,Size,Switch_Time,0)
{
	Item_Texture->setSmooth(true);
	Item_Body.setTexture(*Item_Texture);
	this->Score = Score;
	this->Distance = Distance;
	Item_Body.setOrigin((float)Item_Body.getTextureRect().width/(float)Size.x/2.0f, (float)Item_Body.getTextureRect().height/ (float)Size.y/2.0f);
}


Item::~Item()
{
}

void Item::Update(float Difference,RenderWindow &window)
{	
	if (Item_Visible)
	{
		Item_Projectiles.Update(Difference, window);
		Item_Projectiles.fire(Difference);
	}
}
