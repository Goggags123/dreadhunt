#include "Vexling.h"
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include <vector>
#include "Floor.h"
#include "Collision.h"
#include "Projectiles.h"
#include "Explosion.h"
#include "Direct.h"
#include <math.h>
#define PI 3.14
using namespace sf;

Vexling::Vexling(Texture *Vexling_Texture, Vector2u Size, float Switch_Time, Vector2f Position)
	: Vexling_Animation(Vexling_Texture, Size, Switch_Time)
{
	Vexling_Texture->setSmooth(true);
	Vexling_Body.setTexture(*Vexling_Texture);
	Black_BileT.setSmooth(true);
	Black_BileT.loadFromFile("Sprite/Boss/Black_Bile.png");
	Black_ExplosionT.setSmooth(true);
	Black_ExplosionT.loadFromFile("Sprite/Boss/Black_Explosion.png");
	PiercingT.setSmooth(true);
	PiercingT.loadFromFile("Sprite/Boss/Piercing.png");
	Shots_Texture.setSmooth(true);
	Shots_Texture.loadFromFile("Sprite/Boss/VioletFireBall.png");
	Vexling_Body.setScale(2, 2);
	Vexling_Body.setOrigin(Vexling_Body.getTextureRect().width / 2.0f / (float)Size.x, Vexling_Body.getTextureRect().height / 2.0f / (float)Size.y);
	Vexling_Body.setPosition(Position);
	HP_Bar.setSize(Vector2f(25, 10));
	HP_Bar.setFillColor(Color::Green);
	HP_Bar.setOutlineThickness(1);
	HP_Bar.setOutlineColor(Color::Black);
	Title_Font.loadFromFile("Sprite/Font/Title_Font.TTF");
}


Vexling::~Vexling()
{
}

void Vexling::Update(float Difference, Vector2f Player_Position, RenderWindow &window, std::vector <Floor> &Platforms, std::vector <Projectiles> &Black_Bile, std::vector <Explosion> &Black_Explosion, std::vector <Explosion> &Piercing,std::vector <Direct> &Shots)
{
	if (Vexling_Visible)
	{
		if (!isDying)
		{
			Name.setFont(Title_Font);
			Name.setCharacterSize(12);
			Name.setFillColor(Color::White);
			Name.setOutlineThickness(1);
			Name.setOutlineColor(Color::Black);
			Name.setString(name);
			GenerateT_Time += Difference;
			if (!isGenerating)
			{
				Total_Time += Difference;
				if (Total_Time >= 5.0f)
				{
					Total_Time = 0;
					if (Vexling_Health <= 200)
					{
						moves = rand() % 3;
						isFiring = true;
					}
					else
					{
						moves = rand() % 2;
					}
					switch (moves)
					{
					case Moves::ShotsM:
					{
						if (Player_Position.x >= Vexling_Body.getPosition().x)	Row = Action::Attack;
						else Row = Action::LAttack;
						isShot = true;
						break;
					}
					case Moves::Piercing_Eye:
					{
						if (Player_Position.x >= Vexling_Body.getPosition().x)	Row = Action::Pierce;
						else Row = Action::LPierce; 
						Explosion newIce(&PiercingT, Vector2u(24, 1), 0.05f);
						newIce.setPosition(Player_Position);
						Piercing.push_back(newIce);						
						break;
					}
					}
				}
			}
		}
		if (isFiring)
		{
			if (Player_Position.x >= Vexling_Body.getPosition().x)	Row = Action::Black;
			else Row = Action::LBlack;
			Count_Time += Difference;
			if (Count_Time >= 0.5f)
			{
				Count_Time = 0;
				Projectiles NewThorn(&Black_BileT, Vector2f(rand() % 1001 - 500, 150.0f), 500, Vector2u(6, 1), 0.2f, 10);
				NewThorn.setPos(Vexling_Body.getPosition());
				Black_Bile.push_back(NewThorn);
			}
		}		

		if (isShot)
		{
			if (Player_Position.x >= Vexling_Body.getPosition().x)	Row = Action::Attack;
			else Row = Action::LAttack;
			for (int i = 1; i <= 8; i++)
			{
				int num = rand() % 2;
				if (num == 0)
				{
					num = rand() % 2;
					if (num == 0)
						Absorb_Position.x = 0;
					else
						Absorb_Position.x = 1366;
					Absorb_Position.y = rand() % 769;
				}
				else
				{
					num = rand() % 2;
					if (num == 0)
						Absorb_Position.y = 0;
					else
						Absorb_Position.y = 768;
					Absorb_Position.x = rand() % 1367;
				}
				Vector_Size = sqrt(pow(Absorb_Position.x - Vexling_Body.getPosition().x, 2) + pow(Absorb_Position.y - Vexling_Body.getPosition().y, 2));
				Direction_Bullet.x = (Absorb_Position.x - Vexling_Body.getPosition().x) / (Vector_Size);
				Direction_Bullet.y = (Absorb_Position.y - Vexling_Body.getPosition().y) / (Vector_Size);
				angle = atan2(Direction_Bullet.y, Direction_Bullet.x) * 180 / PI;
				Direct NewAbsorb(&Shots_Texture, angle, Direction_Bullet, 15, Vector2u(4, 1), 0.2f);
				NewAbsorb.setPos(Vexling_Body.getPosition());
				NewAbsorb.isWave = true;
				Shots.push_back(NewAbsorb);
			}
			isShot = false;
		}

		
		/*Generating*/

		if (GenerateT_Time >= 5.0f && !isDying)
		{
			GenerateT_Time = 0;
			Vexling_Body.setPosition(Vector2f(rand() % 767 + 400, rand() % 401 + 100));
			isGenerating = true;
			Vexling_Animation.Visible = true;
			Vexling_Animation.Current_Image.x = 0;
		}

		/*Die*/
		if (Vexling_Health <= 200)
		{
			HP_Bar.setFillColor(Color::Red);
		}
		if (Vexling_Health <= 0&&!isDying)
		{
			Vexling_Health = 0;
			isDying = true;
			Vexling_Animation.Current_Image.x = 0;
			Vexling_Animation.Visible = true;
		}
		if (isDying)
		{
			if (Player_Position.x >= Vexling_Body.getPosition().x) Row = Action::Disappear;
			else Row = Action::LDisappear;
			Vexling_Animation.Update(Row, Difference);
			Vexling_Body.setTextureRect(Vexling_Animation.uvReact);
			if (!Vexling_Animation.Visible)
			{
				Vexling_Visible = false;
				Vexling_Dying = true;
				isDying = false;
			}
		}
		Vexling_Animation.Update(Row, Difference);
		Vexling_Body.setTextureRect(Vexling_Animation.uvReact);
		Vexling_Body.setOrigin(Vexling_Body.getTextureRect().width / 2.0f, Vexling_Body.getTextureRect().height / 2.0f);
		HP_Bar.setPosition(Vector2f(Vexling_Body.getPosition().x - HP_Bar.getSize().x / 2, Vexling_Body.getPosition().y - Vexling_Body.getTextureRect().height / 2.0f -20));
		HP_Bar.setSize(Vector2f((float)Vexling_Health / 100 * 25, 10));
		Name.setPosition(Vector2f(Vexling_Body.getPosition().x - 32, Vexling_Body.getPosition().y - 95));
	}

	/*Generating*/

	if (isGenerating)
	{
		if (Player_Position.x >= Vexling_Body.getPosition().x)	Row = Action::Appear;
		else Row = Action::LAppear;
		Vexling_Animation.Update(Row, Difference);
		Vexling_Body.setTextureRect(Vexling_Animation.uvReact);
		if (!Vexling_Animation.Visible)
		{
			Vexling_Visible = true;
			isGenerating = false;
		}
	}

	/*Drawing*/

	if (Vexling_Visible)
	{
		window.draw(Vexling_Body);
		window.draw(HP_Bar);
		window.draw(Name);
	}

	/*Absorbing*/

	for (int i = 0; i < Shots.size(); i++)
	{
		Shots[i].fire(250, Difference, Shots[i].Get_Direction());
		Shots[i].Update(Difference, window);
	}

	for (int i = 0; i < Black_Bile.size(); i++)
	{
		Black_Bile[i].fire(Difference);
		Black_Bile[i].Update(Difference, window);
	}

	/*Splashing*/

	for (int i = 0; i < Platforms.size(); i++)
	{
		for (int j = 0; j < Black_Bile.size(); j++)
		{
			if (Collision::PixelPerfectTest(Black_Bile[j].Get_Body(), Platforms[i].Body(), 0))
			{
				Explosion newPovy_Splash(&Black_ExplosionT, Vector2u(12, 1), 0.2f);
				newPovy_Splash.setPosition(Black_Bile[j].Get_Body().getPosition());
				newPovy_Splash.Explosion_Animation.Current_Image.x = 0;
				newPovy_Splash.Explosion_Animation.Visible = true;
				Black_Explosion.push_back(newPovy_Splash);
				Black_Bile.erase(Black_Bile.begin() + j);
			}
		}
	}

	for (int i = 0; i < Black_Explosion.size(); i++)
	{
		Black_Explosion[i].Update(Difference);
		if (Black_Explosion[i].Explosion_Visible)
		{
			for (int j = 0; j < Platforms.size(); j++)
			{
				if (!Collision::PixelPerfectTest(Platforms[j].Body(), Black_Explosion[i].Explosion_Body, 0))
				{
					Black_Explosion[i].Explosion_Body.move(0, 98.1*Difference);
				}
			}
			if (Black_Explosion[i].Explosion_Animation.Current_Image.x <= 3)
			{
				Black_Explosion[i].Damagable = true;
				Black_Explosion[i].Damage = 30;
			}
			else
			{
				Black_Explosion[i].Damagable = false;

			}
			window.draw(Black_Explosion[i].Explosion_Body);
		}
		else
		{
			Black_Explosion.erase(Black_Explosion.begin() + i);
		}
	}
	for (int i = 0; i < Piercing.size(); i++)
	{
		Piercing[i].Update(Difference);
		if (Piercing[i].Explosion_Visible)
		{
			if (Piercing[i].Explosion_Animation.Current_Image.x >= 6)
			{
				Piercing[i].Damagable = true;
				Piercing[i].Damage = 20;
			}
			else
			{
				Piercing[i].Damagable = false;

			}
			window.draw(Piercing[i].Explosion_Body);
		}
		else
		{
			Piercing.erase(Piercing.begin() + i);
		}
	}
}
