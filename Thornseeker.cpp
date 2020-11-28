#include "Thornseeker.h"
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include <vector>
#include "Floor.h"
#include "Collision.h"
#include "Projectiles.h"
#include "Explosion.h"
using namespace sf;

Thornseeker::Thornseeker(Texture *Thornseeker_Texture, Vector2u Size, float Switch_Time, Vector2f Position, Vector2f xPos)
	: Thornseeker_Animation(Thornseeker_Texture, Size, Switch_Time)
{
	Thornseeker_Texture->setSmooth(true);
	Thornseeker_Body.setTexture(*Thornseeker_Texture);
	this->xPos = xPos;
	this->Position = Position;
	Thorn_Texture.setSmooth(true);
	Thorn_Texture.loadFromFile("Sprite/Boss/Thorn_Projectiles.png");
	Lightning_Texture.setSmooth(true);
	Lightning_Texture.loadFromFile("Sprite/Effects/Single_Lightning.png");
	Thornseeker_Body.setScale(1.25, 1.25);
	Thornseeker_Body.setOrigin(Thornseeker_Body.getTextureRect().width / 2.0f / (float)Size.x, Thornseeker_Body.getTextureRect().height / 2.0f / (float)Size.y);
	Thornseeker_Body.setPosition(Position);
	HP_Bar.setSize(Vector2f(25, 10));
	HP_Bar.setFillColor(Color::Green);
	HP_Bar.setOutlineThickness(1);
	HP_Bar.setOutlineColor(Color::Black);
	Title_Font.loadFromFile("Sprite/Font/Title_Font.TTF");
}


Thornseeker::~Thornseeker()
{
}

void Thornseeker::Update(float Difference, Vector2f Player_Position, RenderWindow &window, std::vector <Floor> &Platforms, std::vector <Projectiles> &Thorn,std::vector <Explosion> &Thorn_Spike, std::vector <Explosion> &Lightning_Bolt)
{
	if (Thornseeker_Visible)
	{
		/*Gravity*/

		for (int i = 0; i < Platforms.size(); i++)
		{
			if (!Collision::PixelPerfectTest(Platforms[i].Body(), Thornseeker_Body, 0))
			{
				Thornseeker_Body.move(0, 98.1*Difference);
				Can_Move = false;
			}
			else
			{
				Can_Move = true;
			}
		}
		if (!isDying)
		{
			Name.setFont(Title_Font);
			Name.setCharacterSize(12);
			Name.setFillColor(Color::White);
			Name.setOutlineThickness(1);
			Name.setOutlineColor(Color::Black);
			Name.setString(name);
			Total_Time += Difference;
			if (Thornseeker_Health <= 300)
			{
				Lightning_Time += Difference;
				isSparking = true;
				if (Lightning_Time >= 0.5f)
				{
					Explosion NewLightning(&Lightning_Texture, Vector2u(5, 1), 0.2f);
					NewLightning.setPosition(Vector2f(rand() % 967 + 400, 786));
					NewLightning.Explosion_Animation.Visible = true;
					NewLightning.Damagable = false;
					NewLightning.Damage = 0;
					Lightning_Bolt.push_back(NewLightning);
					Lightning_Time = 0;
				}
			}
			moves = rand() % 5;
			if (moves >= 3)
				moves = Moves::Spark_Rush;
			else if (moves >= 1)
				moves = Moves::Thorn_Spikeja;
			else
				moves = Moves::WalkState;
			if (Total_Time >= delay)
			{
				Total_Time = 0;				
				switch (moves)
				{
				case Moves::Spark_Rush:
				{
					if (Speed >= 0)	Row = Action::Spark;
					else Row = Action::LSpark;
					delay = 3.0f;
					isRushing = true;
					multiplier = 2.5;
					Can_Move = true;
					isFiring = false;
					isFirst = false;
					isSecond = false;
					break;
				}
				case Moves::Thorn_Spikeja:
				{
					if (Speed >= 0)	Row = Action::PreThorn;
					else Row = Action::LPreThorn;
					delay = 8.0f;
					multiplier = 1;
					isRushing = false;
					Can_Move = false;
					isFirst = true;
					Thornseeker_Animation.Visible = true;
					Thornseeker_Animation.Current_Image.x = 0;
					break;
				}
				case Moves::WalkState:
				{
					if (!isSparking)
					{
						if (Speed >= 0)	Row = Action::Walk;
						else Row = Action::LWalk;
					}
					else
					{
						if (Speed >= 0)	Row = Action::Idle;
						else Row = Action::LIdle;
					}
					delay = 2.5f;
					isRushing = false;
					Can_Move = true;
					multiplier = 1;
					break;
				}
				}
			}
			if (isFirst)
			{
				Can_Move = false;
				if (Player_Position.x >= Thornseeker_Body.getPosition().x)	Row = Action::PreThorn;
				else Row = Action::LPreThorn;
				Thornseeker_Animation.Update(Row, Difference);
				Thornseeker_Body.setTextureRect(Thornseeker_Animation.uvReact);
				if (!Thornseeker_Animation.Visible)
				{
					if (Player_Position.x >= Thornseeker_Body.getPosition().x)	Row = Action::Thorn;
					else Row = Action::LThorn;
					isSecond = true;
					isFirst = false;
					Thornseeker_Animation.Visible = true;
					Thornseeker_Animation.Current_Image.x = 0;
				}
			}
			if (isSecond)
			{
				Can_Move = false;
				if (Player_Position.x >= Thornseeker_Body.getPosition().x)	Row = Action::Thorn;
				else Row = Action::LThorn;
				Thornseeker_Animation.Update(Row, Difference);
				Thornseeker_Body.setTextureRect(Thornseeker_Animation.uvReact);
				if (!Thornseeker_Animation.Visible)
				{
					if (Player_Position.x >= Thornseeker_Body.getPosition().x)	Row = Action::Thorn;
					else Row = Action::LThorn;
					Thornseeker_Animation.Visible = true;
					Thornseeker_Animation.Current_Image.x = 0;
					isFiring = true;
					isSecond = false;
				}
			}
			if (isFiring)
			{
				if (Player_Position.x >= Thornseeker_Body.getPosition().x)	Row = Action::Stable;
				else Row = Action::LStable;
				Can_Move = false;
				Count_Time += Difference;
				if (Count_Time >= 0.5f)
				{
					Count_Time = 0;
					Projectiles NewThorn(&Thorn_Texture, Vector2f(rand() % 2001 - 1000, 150.0f), 500, Vector2u(1, 1), 0.0f, 0);
					NewThorn.setPos(Thornseeker_Body.getPosition());
					Thorn.push_back(NewThorn);
				}
			}

			/*Moving*/

			if (Thornseeker_Body.getPosition().x <= Position.x - xPos.x)
			{
				Speed = -Speed;
				if (isRushing)
					Row = Action::Spark;
				else if (isSparking)
					Row = Action::Idle;
				else
					Row = Action::Walk;
			}
			else if (Thornseeker_Body.getPosition().x >= Position.x + xPos.y)
			{
				Speed = -Speed;
				if (isRushing)
					Row = Action::LSpark;
				else if (isSparking)
					Row = Action::LIdle;
				else
					Row = Action::LWalk;
			}
		}

		/*Dying*/

		if (Thornseeker_Health <= 300)
		{
			HP_Bar.setFillColor(Color::Red);
		}
		if (Thornseeker_Health <= 0 )
		{
			Thornseeker_Health = 0;
			isDying = true;
			Can_Move = false;
			game_frame++;
			if (game_frame >= 50)
			{
				Thornseeker_Visible = false;
				isDying = false;
			}
		}
		
		if(Can_Move)
		Thornseeker_Body.move(Speed*multiplier*Difference, 0);
		if (isFiring)
		{
			if (Player_Position.x >= Thornseeker_Body.getPosition().x)	Row = Action::Stable;
			else Row = Action::LStable;
		}
		Thornseeker_Animation.Update(Row, Difference);
		Thornseeker_Body.setTextureRect(Thornseeker_Animation.uvReact);
		Thornseeker_Body.setOrigin(Thornseeker_Body.getTextureRect().width / 2.0f, Thornseeker_Body.getTextureRect().height / 2.0f);
		HP_Bar.setPosition(Vector2f(Thornseeker_Body.getPosition().x - HP_Bar.getSize().x / 2, Thornseeker_Body.getPosition().y - Thornseeker_Body.getTextureRect().height / 2.0f+20));
		HP_Bar.setSize(Vector2f((float)Thornseeker_Health / 100 * 25, 10));
		Name.setPosition(Vector2f(Thornseeker_Body.getPosition().x - 58, Thornseeker_Body.getPosition().y - 95));
	}

	/*Draw*/

	if (Thornseeker_Visible&&game_frame%4==0)
	{
		window.draw(Thornseeker_Body);
		window.draw(HP_Bar);
		window.draw(Name);
	}

	for (int i = 0; i < Lightning_Bolt.size(); i++)
	{
		Lightning_Bolt[i].Update(Difference);
		if (Lightning_Bolt[i].Explosion_Animation.Current_Image.x < 3)
		{
			Lightning_Bolt[i].Damagable = true;
			Lightning_Bolt[i].Damage = 5;
		}
		else
			Lightning_Bolt[i].Damagable = false;
		if (Lightning_Bolt[i].Explosion_Visible)
		{
			window.draw(Lightning_Bolt[i].Explosion_Body);
		}
		else
		{
			Lightning_Bolt.erase(Lightning_Bolt.begin() + i);
			break;
		}
	}
	for (int i = 0; i < Thorn.size(); i++)
	{
		Thorn[i].fire(Difference);
		Thorn[i].Draw(window);
	}
}
