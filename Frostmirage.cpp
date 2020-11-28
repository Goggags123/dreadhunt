#include "Frostmirage.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Animation.h"
#include <vector>
#include "Floor.h"
#include "Collision.h"
#include "Direct.h"
#include "Explosion.h"
#include "Clone.h"
#define PI 3.14
using namespace sf;

Frostmirage::Frostmirage(Texture *Frostmirage_Texture, Vector2u Size, float Switch_Time, Vector2f Position, Vector2f xPos)
	: Frostmirage_Animation(Frostmirage_Texture, Size, Switch_Time)
{
	Frostmirage_Texture->setSmooth(true);
	Body.setTexture(*Frostmirage_Texture);
	this->xPos = xPos;
	this->Position = Position;
	Body.setScale(2.5, 2.5);
	this->Frostmirage_Texture = *Frostmirage_Texture;
	Fireball_Texture.loadFromFile("Sprite/Effects/Fireball.png");
	Fireball_Texture.setSmooth(true);
	Typhoon_Texture.loadFromFile("Sprite/Effects/Typhoon.png");
	Typhoon_Texture.setSmooth(true);
	IceSpike_Texture.loadFromFile("Sprite/Effects/Frost_Effect.png");
	IceSpike_Texture.setSmooth(true);
	Body.setOrigin(Body.getTextureRect().width / 2.0f / (float)Size.x, Body.getTextureRect().height / 2.0f / (float)Size.y);
	Body.setPosition(Position);
	HP_Bar.setSize(Vector2f(25, 10));
	HP_Bar.setFillColor(Color::Green);
	HP_Bar.setOutlineThickness(1);
	HP_Bar.setOutlineColor(Color::Black);
	Title_Font.loadFromFile("Sprite/Font/Title_Font.TTF");
}


Frostmirage::~Frostmirage()
{
}

void Frostmirage::Update(float Difference, Vector2f Player_Position, RenderWindow &window, std::vector <Floor> &Platforms,std::vector <Direct> &Firephoon,std::vector <Explosion> &Ice_Spike,std::vector <Clone> &Frostmirage_Clone)
{
	if (Frostmirage_Visible)
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
			if (Total_Time >= 1.2f)
			{
				Total_Time = 0;
				if (Frostmirage_Health<=250&&!isClone)
					moves = Moves::Mirage;
				else
					moves = rand() % 3 ;
				switch (moves)
				{
				case Moves::Typhoon:
				{
					if (Player_Position.x >= Body.getPosition().x)
					{
						Row = Action::Idle;
						Direction_Bullet.x = 1;
					}
					else
					{
						Row = Action::LIdle;
						Direction_Bullet.x = -1;
					}
					Direction_Bullet.y = 0;
					Total_Time = 0;
					isFiring = true;
					break;
				}
				case Moves::Fireball:
				{
					if (Player_Position.x >= Body.getPosition().x)	Row = Action::Idle;
					else Row = Action::LIdle;
					Vector_Size = sqrt(pow(Player_Position.x - Body.getPosition().x, 2) + pow(Player_Position.y - Body.getPosition().y, 2));
					Direction_Bullet.x = (Player_Position.x - Body.getPosition().x) / (Vector_Size);
					Direction_Bullet.y = (Player_Position.y - Body.getPosition().y) / (Vector_Size);
					angle = atan2(Direction_Bullet.y, Direction_Bullet.x) * 180 / PI;
					Total_Time = 0;
					isFiring = true;
					break;
				}
				case Moves::Ice_Spike:
				{
					if (Player_Position.x >= Body.getPosition().x)	Row = Action::Idle;
					else Row = Action::LIdle;
					Explosion newIce(&IceSpike_Texture,Vector2u(16,1),0.2f);
					newIce.setPosition(Player_Position);
					Ice_Spike.push_back(newIce);					
					break;
				}
				case Moves::Mirage:
				{
					if (!isClone)
					{
						Clone NewClone1(&Frostmirage_Texture, Vector2u(7, 4), 0.2f, Vector2f(300, 150));
						Frostmirage_Clone.push_back(NewClone1);
						Clone NewClone2(&Frostmirage_Texture, Vector2u(7, 4), 0.2f, Vector2f(500, 150));
						Frostmirage_Clone.push_back(NewClone2);
						Clone NewClone3(&Frostmirage_Texture, Vector2u(7, 4), 0.2f, Vector2f(700, 150));
						Frostmirage_Clone.push_back(NewClone3);
						Clone NewClone4(&Frostmirage_Texture, Vector2u(7, 4), 0.2f, Vector2f(900, 150));
						Frostmirage_Clone.push_back(NewClone4);
						Clone NewClone5(&Frostmirage_Texture, Vector2u(7, 4), 0.2f, Vector2f(1100, 150));
						Frostmirage_Clone.push_back(NewClone5);
						isClone = true;
						Count_Clone = 5;
					}
					break;
				}
				}
			}
		}

		/*Moving*/

		if (Body.getPosition().x <= Position.x - xPos.x)
		{
			Speed = -Speed;
			Row = Action::Idle;
		}
		else if (Body.getPosition().x >= Position.x + xPos.y)
		{
			Speed = -Speed;
			Row = Action::LIdle;
		}

		/*Direct Moves*/

		if (isFiring)
		{
			Count_Time = Total_Time;
			if (moves == Moves::Fireball)
			{
				Direct newBall(&Fireball_Texture, angle, Direction_Bullet, 10, Vector2u(4, 1), 0.2f);
				newBall.setPos(Body.getPosition());
				newBall.isWave = true;
				newBall.Bullet_Animation.Current_Image.x = 0;
				newBall.Bullet_Animation.Visible = true;
				Firephoon.push_back(newBall);
			}
			else if (moves == Moves::Typhoon)
			{
				Direct newBall(&Typhoon_Texture, 0, Direction_Bullet, 15, Vector2u(6, 1), 0.2f);
				newBall.setPos(Body.getPosition());
				newBall.isWave = true;
				newBall.Bullet_Animation.Current_Image.x = 0;
				newBall.Bullet_Animation.Visible = true;
				Firephoon.push_back(newBall);
			}
			isFiring = false;
		}

		/*Dying*/
		if (Frostmirage_Health <= 250)
		{
			HP_Bar.setFillColor(Color::Red);
		}
		if (Frostmirage_Health <= 0 && !isDying)
		{
			Frostmirage_Animation.Current_Image.x = 0;
			Frostmirage_Animation.Visible = true;
			isDying = true;
		}
		
		if (isDying)
		{
			if (Player_Position.x >= Body.getPosition().x) Row = Action::Die;
			else Row = Action::LDie;
			Frostmirage_Animation.Update(Row, Difference);
			Body.setTextureRect(Frostmirage_Animation.uvReact);
			if (!Frostmirage_Animation.Visible)
			{
				Frostmirage_Visible = false;
				isDying = false;
			}
		}

		/*Gravity*/

		for (int i = 0; i < Platforms.size(); i++)
		{
			if (!Collision::PixelPerfectTest(Platforms[i].Body(), Body, 0))
			{
				Body.move(0, 98.1*Difference);
				Can_Move = false;
			}
			else
			{
				Can_Move = true;
			}
		}

		/*Wall Collision*/

		if(Can_Move)
		Body.move(Speed*Difference,0);

		Frostmirage_Animation.Update(Row, Difference);
		Body.setTextureRect(Frostmirage_Animation.uvReact);
		Body.setOrigin(Body.getTextureRect().width / 2.0f, Body.getTextureRect().height / 2.0f);
		HP_Bar.setPosition(Vector2f(Body.getPosition().x - HP_Bar.getSize().x / 2, Body.getPosition().y - Body.getTextureRect().height / 2.0f - 50));
		HP_Bar.setSize(Vector2f((float)Frostmirage_Health / 100 * 25, 10));
		Name.setPosition(Vector2f(Body.getPosition().x - 54, Body.getPosition().y - 100));
	}

	/*Draw*/

	if (Frostmirage_Visible)
	{
		window.draw(Body);
		window.draw(HP_Bar);
		window.draw(Name);
	}

	for (int i = 0; i < Ice_Spike.size(); i++)
	{
		Ice_Spike[i].Update(Difference);
		if (Ice_Spike[i].Explosion_Visible)
		{
			for (int j = 0; j < Platforms.size(); j++)
			{
				if (!Collision::PixelPerfectTest(Platforms[j].Body(), Ice_Spike[i].Explosion_Body, 0))
				{
					Ice_Spike[i].Explosion_Body.move(0, 98.1*Difference);
				}
			}
			if (Ice_Spike[i].Explosion_Animation.Current_Image.x == 10)
			{
				Ice_Spike[i].Damagable = true;
				Ice_Spike[i].Damage = 20;
			}
			else
			{
				Ice_Spike[i].Damagable = false;

			}
			window.draw(Ice_Spike[i].Explosion_Body);
		}
		else
		{
			Ice_Spike.erase(Ice_Spike.begin() + i);
			break;
		}
	}
	for (int i = 0; i < Firephoon.size(); i++)
	{
		Firephoon[i].fire(500, Difference, Firephoon[i].Get_Direction());
		Firephoon[i].Update(Difference, window);
	}

}
