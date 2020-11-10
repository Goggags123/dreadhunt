#include "Gaspow.h"
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Floor.h"
#include <vector>
#include "Direct.h"
#define PI 3.14
using namespace sf;

Gaspow::Gaspow(Texture * Gaspow_Texture, Vector2u Size, float Switch_Time, Vector2f Position)
	: Gaspow_Animation(Gaspow_Texture, Size, Switch_Time)
{
	Gaspow_Texture->setSmooth(true);
	Gaspow_Body.setTexture(*Gaspow_Texture);
	GaspowBall_Texture.loadFromFile("Sprite/Monster/Gaspow_Ball.png");
	Gaspow_Body.setOrigin(Gaspow_Body.getTextureRect().width / 2.0f / (float)Size.x, Gaspow_Body.getTextureRect().height / 2.0f / (float)Size.y);
	Gaspow_Body.setPosition(Position);
	HP_Bar.setSize(Vector2f(150, 10));
	HP_Bar.setFillColor(Color::Green);
	HP_Bar.setOutlineThickness(1);
	HP_Bar.setOutlineColor(Color::Black);
	Title_Font.loadFromFile("Sprite/Font/Title_Font.TTF");
}

void Gaspow::Gaspow_Update(float Difference, Vector2f Player_Position, std::vector <Direct> &Gaspow_Ball, RenderWindow &window)
{

	if (Gaspow_Visible)
	{
		if (!isDying)
		{
			Name.setFont(Title_Font);
			Name.setCharacterSize(12);
			Name.setFillColor(Color::White);
			Name.setOutlineThickness(1);
			Name.setOutlineColor(Color::Black);
			Name.setString(name);
			Total_Time += Difference;

			/*Crunching*/

			if ((sqrt(pow(Player_Position.x - Gaspow_Body.getPosition().x, 2) + pow(Player_Position.y - Gaspow_Body.getPosition().y, 2)) <= 450) && Total_Time - Count_Time >= 2.0)
			{
				if (Player_Position.x >= Gaspow_Body.getPosition().x)
				{
					Row = Action::Shoot;
					Direction_Bullet.x = 1;
					angle = 0;
				}
				else
				{
					Row = Action::LShoot;
					Direction_Bullet.x = -1;
					angle = 180;
				}
				Direction_Bullet.y = 0;
				Total_Time = 0;
				isFiring = true;
			}

			/*Idle*/

			else if (Total_Time >= Count_Time + 2.4f)
			{
				Count_Time = 0;
				Total_Time = 0;
				if (Player_Position.x >= Gaspow_Body.getPosition().x)	 Row = Action::Idle;
				else Row = Action::LIdle;
			}
		}

		/*Shots*/

		if (isFiring)
		{
			Count_Time = Total_Time;
			Direct newBall(&GaspowBall_Texture, angle, Direction_Bullet, 12, Vector2u(1, 1), 0.0f);
			newBall.setPos(Gaspow_Body.getPosition());
			Gaspow_Ball.push_back(newBall);
			isFiring = false;
		}
		

		/*Die*/
		if (Gaspow_Health <= 35 / 2)
		{
			HP_Bar.setFillColor(Color::Red);
		}
		if (Gaspow_Health <= 0)
		{
			isDying = true;
			Gaspow_Health = 0;
			game_frame++;
			if (game_frame >= 50)
			{
				Gaspow_Visible = false;
				isDying = false;
			}
		}
		Gaspow_Animation.Update(Row, Difference);
		Gaspow_Body.setTextureRect(Gaspow_Animation.uvReact);
		Gaspow_Body.setOrigin(Gaspow_Body.getTextureRect().width / 2.0f, Gaspow_Body.getTextureRect().height / 2.0f);
		HP_Bar.setPosition(Vector2f(Gaspow_Body.getPosition().x - HP_Bar.getSize().x / 2, Gaspow_Body.getPosition().y - Gaspow_Body.getTextureRect().height / 2.0f));
		HP_Bar.setSize(Vector2f((float)Gaspow_Health / 100 * 150, 10));
		Name.setPosition(Vector2f(Gaspow_Body.getPosition().x - 31, Gaspow_Body.getPosition().y - 120));
	}
	if (Gaspow_Visible&&game_frame%2==0)
	{
		window.draw(Gaspow_Body);
		window.draw(HP_Bar);
		window.draw(Name);
	}
	for (int i = 0; i < Gaspow_Ball.size(); i++)
	{
		Gaspow_Ball[i].fire(500, Difference, Gaspow_Ball[i].Get_Direction());
		Gaspow_Ball[i].Draw(window);
	}
}


Gaspow::~Gaspow()
{
}
