#include "Animation.h"
#include <SFML\Graphics.hpp>
#include <iostream>
using namespace sf;


Animation::Animation(Texture* Texture, Vector2u Size, float Switch_Time)
{
	//this->faceRight = faceRight;
	this->Size = Size;
	this->Switch_Time = Switch_Time;
	Total_Time = 0.0f;
	Current_Image.x = 0;
	uvReact.width = int(Texture->getSize().x / Size.x);
	uvReact.height = int(Texture->getSize().y / Size.y);
	
	//printf("%d %d\n", Texture->getSize().x, Texture->getSize().y);
}
Animation::~Animation()
{
}
void Animation::Update(float Row, float Difference)
{
	
	Current_Image.y = Row;
	Total_Time += Difference;
	if (Total_Time >= Switch_Time)
	{
		Total_Time -= Switch_Time;
		Current_Image.x++;
		if (Current_Image.x >= Size.x)
		{
			Visible = false;
			Current_Image.x = 0;
		}
	}
	//uvReact.width = abs(uvReact.width);
	uvReact.left = Current_Image.x * uvReact.width;	
	uvReact.top = Current_Image.y * uvReact.height;
}
