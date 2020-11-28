#include "Clone.h"
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include <vector>
#include "Floor.h"
#include "Collision.h"
#include "Direct.h"
#include "Explosion.h"
#define PI 3.14
using namespace sf;

Clone::Clone(Texture *Clone_Texture, Vector2u Size, float Switch_Time,Vector2f Position)
	: Clone_Animation(Clone_Texture, Size, Switch_Time)
{
	Clone_Texture->setSmooth(true);
	Body.setTexture(*Clone_Texture);
	Body.setScale(2, 2);
	Fireball_Texture.loadFromFile("Sprite/Effects/Fireball.png");
	Fireball_Texture.setSmooth(true);
	Body.setOrigin(Body.getTextureRect().width / 2.0f / (float)Size.x, Body.getTextureRect().height / 2.0f / (float)Size.y);
	Body.setPosition(Position);
}


Clone::~Clone()
{
}

void Clone::Update(float Difference, Vector2f Player_Position, RenderWindow &window, std::vector <Floor> &Platforms, std::vector <Direct> &Fireball_Clone)
{
	if (Clone_Visible)
	{
		if (!isDying)
		{
			Total_Time += Difference;
			if (Total_Time >= 3.0f)
			{
				Total_Time = 0;
				if (Player_Position.x >= Body.getPosition().x)	Row = Action::Idle;
				else Row = Action::LIdle;
				Vector_Size = sqrt(pow(Player_Position.x - Body.getPosition().x, 2) + pow(Player_Position.y - Body.getPosition().y, 2));
				Direction_Bullet.x = (Player_Position.x - Body.getPosition().x) / (Vector_Size);
				Direction_Bullet.y = (Player_Position.y - Body.getPosition().y) / (Vector_Size);
				angle = atan2(Direction_Bullet.y, Direction_Bullet.x) * 180 / PI;
				Total_Time = 0;
				isFiring = true;
			}
		}

		/*Direct Moves*/

		if (isFiring)
		{
			Count_Time = Total_Time;
			Direct newBall(&Fireball_Texture, angle, Direction_Bullet, 5, Vector2u(4, 1), 0.2);
			newBall.setPos(Body.getPosition());
			newBall.isWave = true;
			newBall.Bullet_Animation.Current_Image.x = 0;
			newBall.Bullet_Animation.Visible = true;
			Fireball_Clone.push_back(newBall);
			isFiring = false;
		}

		/*Dying*/

		if (Clone_Health <= 0 && !isDying)
		{
			Clone_Animation.Current_Image.x = 0;
			Clone_Animation.Visible = true;
			isDying = true;
		}
		if (isDying)
		{
			if (Player_Position.x >= Body.getPosition().x) Row = Action::Die;
			else Row = Action::LDie;
			Clone_Animation.Update(Row, Difference);
			Body.setTextureRect(Clone_Animation.uvReact);
			if (!Clone_Animation.Visible)
			{
				Count = 1;
				Clone_Visible = false;
				isDying = false;
			}
		}

		Clone_Animation.Update(Row, Difference);
		Body.setTextureRect(Clone_Animation.uvReact);
		Body.setOrigin(Body.getTextureRect().width / 2.0f, Body.getTextureRect().height / 2.0f);
	}

	/*Draw*/

	if (Clone_Visible)
	{
		window.draw(Body);
	}
	for (int i = 0; i < Platforms.size(); i++)
	{
		for (int j = 0; j < Fireball_Clone.size(); j++)
		{
			if (Collision::PixelPerfectTest(Fireball_Clone[j].Get_Body(), Platforms[i].Body(), 0) || Fireball_Clone[j].Get_Body().getPosition().x - abs(Fireball_Clone[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || Fireball_Clone[j].Get_Body().getPosition().x + abs(Fireball_Clone[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || Fireball_Clone[j].Get_Body().getPosition().y + abs(Fireball_Clone[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || Fireball_Clone[j].Get_Body().getPosition().y - abs(Fireball_Clone[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
			{
				Fireball_Clone.erase(Fireball_Clone.begin() + j);
				break;
			}
		}
	}
}
