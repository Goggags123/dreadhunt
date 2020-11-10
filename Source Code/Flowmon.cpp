#include "Flowmon.h"
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Floor.h"
#include <vector>
#include "Direct.h"
#define PI 3.14
using namespace sf;

Flowmon::Flowmon(Texture * Flowmon_Texture, Vector2u Size, float Switch_Time,Vector2f Position)
	: Flowmon_Animation (Flowmon_Texture,Size,Switch_Time)
{
	Flowmon_Texture->setSmooth(true);
	Flowmon_Body.setTexture(*Flowmon_Texture);
	FlowmonBall_Texture.loadFromFile("Sprite/Monster/Ball.png");
	Flowmon_Body.setScale(1.5, 1.5);
	Flowmon_Body.setOrigin(Flowmon_Body.getTextureRect().width / 2.0f / (float)Size.x, Flowmon_Body.getTextureRect().height / 2.0f / (float)Size.y);
	Flowmon_Body.setPosition(Position);
	HP_Bar.setSize(Vector2f(150, 10));
	HP_Bar.setFillColor(Color::Green);
	HP_Bar.setOutlineThickness(1);
	HP_Bar.setOutlineColor(Color::Black);
	Title_Font.loadFromFile("Sprite/Font/Title_Font.TTF");
}

void Flowmon::Flowmon_Update(float Difference, Vector2f Player_Position,std::vector <Direct> &Flowmon_Ball,RenderWindow &window)
{
	
	if (Flowmon_Visible)
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

			if (sqrt(pow(Player_Position.x - Flowmon_Body.getPosition().x, 2) + pow(Player_Position.y - Flowmon_Body.getPosition().y, 2)) <= 150)
			{
				if (Player_Position.x >= Flowmon_Body.getPosition().x)	Row = Action::Crunch;
				else Row = Action::LCrunch;
				Total_Time = 0;
			}

			/*Shooting*/

			else if ((sqrt(pow(Player_Position.x - Flowmon_Body.getPosition().x, 2) + pow(Player_Position.y - Flowmon_Body.getPosition().y, 2)) <= 450) && Total_Time - Count_Time >= 1.5)
			{
				if (Player_Position.x >= Flowmon_Body.getPosition().x)	 Row = Action::Shoot;
				else Row = Action::LShoot;
				Total_Time = 0;
				Vector_Size = sqrt(pow(Player_Position.x - Flowmon_Body.getPosition().x, 2) + pow(Player_Position.y - Flowmon_Body.getPosition().y, 2));
				Direction_Bullet.x = (Player_Position.x - Flowmon_Body.getPosition().x) / (Vector_Size);
				Direction_Bullet.y = (Player_Position.y - Flowmon_Body.getPosition().y) / (Vector_Size);
				angle = atan2(Direction_Bullet.y, Direction_Bullet.x) * 180 / PI;
				isFiring = true;
			}

			/*Idle*/

			else if (Total_Time >= Count_Time + 1.6f)
			{
				Count_Time = 0;
				Total_Time = 0;
				if (Player_Position.x >= Flowmon_Body.getPosition().x)	 Row = Action::Idle;
				else Row = Action::LIdle;
			}
		}

		/*Shots*/

		if (isFiring)
		{
			Count_Time = Total_Time;
			Direct newBall(&FlowmonBall_Texture, angle, Direction_Bullet,10,Vector2u(1,1),0.0f);
			newBall.setPos(Flowmon_Body.getPosition());
			Flowmon_Ball.push_back(newBall);
			isFiring = false;
		}
		for (int i = 0; i < Flowmon_Ball.size(); i++)
		{
			Flowmon_Ball[i].fire(500, Difference, Flowmon_Ball[i].Get_Direction());
			Flowmon_Ball[i].Draw(window);
		}

		/*Die*/

		if (Flowmon_Health <= 40 / 2)
		{
			HP_Bar.setFillColor(Color::Red);
		}
		if (Flowmon_Health <= 0 && !isDying)
		{
			Flowmon_Health = 0;
			isDying = true;
			Flowmon_Animation.Current_Image.x = 0;
			Flowmon_Animation.Visible = true;
		}
		if (isDying)
		{
			if (Player_Position.x >= Flowmon_Body.getPosition().x)	 Row = Action::Die;
			else Row = Action::LDie;
			Flowmon_Animation.Update(Row, Difference);
			Flowmon_Body.setTextureRect(Flowmon_Animation.uvReact);
			if (!Flowmon_Animation.Visible)
			{
				Flowmon_Visible = false;
				isDying = false;
			}
		}
		Flowmon_Animation.Update(Row, Difference);
		Flowmon_Body.setTextureRect(Flowmon_Animation.uvReact);
		Flowmon_Body.setOrigin(Flowmon_Body.getTextureRect().width / 2.0f, Flowmon_Body.getTextureRect().height / 2.0f);
		HP_Bar.setPosition(Vector2f(Flowmon_Body.getPosition().x - HP_Bar.getSize().x / 2, Flowmon_Body.getPosition().y - Flowmon_Body.getTextureRect().height / 2.0f-15));
		HP_Bar.setSize(Vector2f((float)Flowmon_Health / 100 * 150, 10));
		Name.setPosition(Vector2f(Flowmon_Body.getPosition().x - 39, Flowmon_Body.getPosition().y - 70));
	}
	if (Flowmon_Visible)
	{	
		window.draw(Flowmon_Body);
		window.draw(HP_Bar);
		window.draw(Name);
	}
}


Flowmon::~Flowmon()
{
}
