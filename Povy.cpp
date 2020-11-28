#include "Povy.h"
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Floor.h"
#include "Collision.h"
#include <math.h>
#include <vector>
#include "Text_String.h"
#include "Projectiles.h"
#include "Explosion.h"
std::vector <Explosion> Povy_Splash;
using namespace sf;

Povy::Povy(Texture *Povy_Texture,  Vector2u Size, float Switch_Time, Vector2f Position,Texture *PovySP_Texture)
	: Povy_Animation(Povy_Texture, Size, Switch_Time)
{
	Povy_Texture->setSmooth(true);
	this->PovySP_Texture = *PovySP_Texture;
	Povy_Body.setTexture(*Povy_Texture);
	Povy_Body.setScale(1.2, 1.2);
	Povy_Body.setOrigin(Povy_Body.getTextureRect().width / 2.0f / (float)Size.x, Povy_Body.getTextureRect().height / 2.0f / (float)Size.y);
	PovyBall_Texture.loadFromFile("Sprite/Monster/PovyBall.png");
	Povy_Body.setPosition(Position);
	HP_Bar.setSize(Vector2f(100, 10));
	HP_Bar.setFillColor(Color::Green);
	HP_Bar.setOutlineThickness(1);
	HP_Bar.setOutlineColor(Color::Black);
	Title_Font.loadFromFile("Sprite/Font/Title_Font.TTF");
}

Povy::~Povy()
{
}

void Povy::Update(float Difference, Vector2f Player_Position, std::vector <Projectiles> &Povy_Ball, RenderWindow &window,std::vector <Floor> &Platforms)
{
	if (Povy_Visible)
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

			/*Shooting*/

			if ((sqrt(pow(Player_Position.x - Povy_Body.getPosition().x, 2) + pow(Player_Position.y - Povy_Body.getPosition().y, 2)) <= 480) && Total_Time - Count_Time >= 1)
			{

				Row = Action::Shoot;
				Total_Time = 0;
				isFiring = true;
			}

			/*Idle*/

			else if (Total_Time >= Count_Time + 1.6f)
			{
				Row = Action::Idle;
				Total_Time = 0;
				Count_Time = 0;
			}
		}

		/*Shots*/

		if (isFiring)
		{
			Count_Time = Total_Time;
			Projectiles newBall(&PovyBall_Texture, Vector2f(Player_Position.x - Povy_Body.getPosition().x, 150.0f), 500.0f, Vector2u(1, 1), 0.0f, 8);
			newBall.setPos(Povy_Body.getPosition());
			Povy_Ball.push_back(newBall);
			isFiring = false;
		}

		if (Povy_Health <= 70/2)
		{
			HP_Bar.setFillColor(Color::Red);
		}		

		/*Die*/

		if (Povy_Health <= 0)
		{
			Povy_Health = 0;
			isDying = true;
			game_frame++;
			if (game_frame >= 50)
			{
				Povy_Visible = false;
				isDying = false;
			}
		}
		Povy_Animation.Update(Row, Difference);
		Povy_Body.setTextureRect(Povy_Animation.uvReact);
		Povy_Body.setOrigin(Povy_Body.getTextureRect().width / 2.0f, Povy_Body.getTextureRect().height / 2.0f);
		Name.setPosition(Vector2f(Povy_Body.getPosition().x- 45, Povy_Body.getPosition().y- 70));
		HP_Bar.setPosition(Vector2f(Povy_Body.getPosition().x - HP_Bar.getSize().x / 2, Povy_Body.getPosition().y - Povy_Body.getTextureRect().height / 2.0f - 20));
		HP_Bar.setSize(Vector2f((float)Povy_Health / 100 * 100, 10));
	}	

	/*Draw*/

	if (Povy_Visible&&game_frame%4==0)
	{
		window.draw(Povy_Body);
		window.draw(HP_Bar);
		window.draw(Name);
	}
	for (int i = 0; i < Povy_Ball.size(); i++) {

		Povy_Ball[i].fire(Difference);
		Povy_Ball[i].Draw(window);
	}

	/*Splash*/

	for (int i = 0; i < Platforms.size(); i++)
	{
		for (int j = 0; j < Povy_Ball.size(); j++)
		{
			if (Collision::PixelPerfectTest(Povy_Ball[j].Get_Body(), Platforms[i].Body(), 0))
			{
				Explosion newPovy_Splash(&PovySP_Texture, Vector2u(3, 1), 0.25f);
				newPovy_Splash.setPosition(Povy_Ball[j].Get_Body().getPosition());
				Povy_Splash.push_back(newPovy_Splash);
				Povy_Ball.erase(Povy_Ball.begin() + j);
			}
		}
	}
	
	/*Splashing*/

	for (int i = 0; i < Povy_Splash.size(); i++)
	{
		Povy_Splash[i].Update(Difference);
		if (Povy_Splash[i].Explosion_Visible)
		{
			window.draw(Povy_Splash[i].Explosion_Body);
		}
		else
		{
			Povy_Splash.erase(Povy_Splash.begin() + i);
		}
	}
}
