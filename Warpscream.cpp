#include "Warpscream.h"
#include "SFML\Graphics.hpp"
#include "Animation.h"
#include "Floor.h"
#include "Explosion.h"
#include "Direct.h"
#include "Barrel.h"
#include <math.h>
#include "Collision.h"
#define PI 3.14
using namespace sf;

Warpscream::Warpscream(Texture *Warpscream_Texture, Vector2u Size, float Switch_Time, Vector2f Position)
	: Warpscream_Animation (Warpscream_Texture,Size,Switch_Time)
{
	Warpscream_Texture->setSmooth(true);
	Warpscream_Body.setTexture(*Warpscream_Texture);
	Warpscream_Body.setScale(2.5, 2.5);
	Warpscream_Body.setOrigin(Warpscream_Body.getTextureRect().width / 2.0f / (float)Size.x, Warpscream_Body.getTextureRect().height / 2.0f / (float)Size.y);
	Warpscream_Body.setPosition(Position);
	Absorb_Texture.setSmooth(true);
	Absorb_Texture.loadFromFile("Sprite/Effects/Absorb.png");
	Shots_Texture.setSmooth(true);
	Shots_Texture.loadFromFile("Sprite/Effects/YellowFireBall.png");
	White_Texture.setSmooth(true);
	White_Texture.loadFromFile("Sprite/Boss/White_Force.png");
	IceSH_Effects.setSmooth(true);
	IceSH_Effects.loadFromFile("Sprite/Effects/Shield.png");
	Warpscream_Animation.Current_Image.x = 0;
	Warpscream_Animation.Visible = true;
	HP_Bar.setSize(Vector2f(15, 10));
	HP_Bar.setFillColor(Color::Green);
	HP_Bar.setOutlineThickness(1);
	HP_Bar.setOutlineColor(Color::Black);
	Title_Font.loadFromFile("Sprite/Font/Title_Font.TTF");
}


Warpscream::~Warpscream()
{
}

void Warpscream::Update(float Difference, std::vector<Floor>& Platforms, std::vector<Explosion>& White_force,std::vector <Direct> &Absorb,Vector2f Player_Position,RenderWindow &window,std::vector <Barrel> &Barrel_Body)
{
	if (Warpscream_Visible)
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
				if (Total_Time >= delay)
				{
					Total_Time = 0;
					if (Warpscream_Health <= 300)
					{
						moves = rand() % 3;
						delay = 1.5f;
					}
					else
						moves = rand() % 2;
					switch (moves)
					{
					case Moves::White_ForceMoves:
					{
						if (Player_Position.x >= Warpscream_Body.getPosition().x)	Row = Action::White_ForceM;
						else Row = Action::LWhite_Force;
						Explosion newIce(&White_Texture, Vector2u(3, 1), 0.2f);
						newIce.setPosition(Player_Position);
						newIce.Explosion_Body.setScale(2, 2);
						White_force.push_back(newIce);
						break;
					}
					case Moves::ShotsMoves:
					{
						if (Player_Position.x >= Warpscream_Body.getPosition().x)	Row = Action::ShotsM;
						else Row = Action::LShots;
						isShot = true;
						break;
					}
					case Moves::AbsorbMoves:
					{
						if (Player_Position.x >= Warpscream_Body.getPosition().x)	Row = Action::AbsorbM;
						else Row = Action::LAbsorb;
						if (Shieldable)
						{
							Barrel Ice_Shield(&IceSH_Effects, Warpscream_Body.getPosition(), 20, Vector2u(1, 1), 0.0f);
							Ice_Shield.isIceShield = true;
							Ice_Shield.Get_Body().setScale(1.5, 1.5);
							Barrel_Body.push_back(Ice_Shield);
							Shieldable = false;
						}
						isAbsorb = true;
						break;
					}
					}
				}
			}
		}
		
		
		if (isAbsorb)
		{
			if (Player_Position.x >= Warpscream_Body.getPosition().x)	Row = Action::AbsorbM;
			else Row = Action::LAbsorb;
			for (int i = 1; i <= 10; i++)
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
				Vector_Size = sqrt(pow(Player_Position.x - Absorb_Position.x, 2) + pow(Player_Position.y - Absorb_Position.y, 2));
				Direction_Bullet.x = (Player_Position.x - Absorb_Position.x) / (Vector_Size);
				Direction_Bullet.y = (Player_Position.y - Absorb_Position.y) / (Vector_Size);
				angle = atan2(Direction_Bullet.y, Direction_Bullet.x) * 180 / PI;
				Direct NewAbsorb(&Absorb_Texture, angle, Direction_Bullet, 5, Vector2u(1, 1), 0.0f);
				NewAbsorb.setPos(Absorb_Position);
				NewAbsorb.isAbsorb = true;
				Absorb.push_back(NewAbsorb);
			}
			isAbsorb = false;
		}

		if (isShot)
		{
			if (Player_Position.x >= Warpscream_Body.getPosition().x)	Row = Action::ShotsM;
			else Row = Action::LShots;
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
				Vector_Size = sqrt(pow(Absorb_Position.x - Warpscream_Body.getPosition().x, 2) + pow(Absorb_Position.y - Warpscream_Body.getPosition().y, 2));
				Direction_Bullet.x = (Absorb_Position.x - Warpscream_Body.getPosition().x) / (Vector_Size);
				Direction_Bullet.y = (Absorb_Position.y - Warpscream_Body.getPosition().y) / (Vector_Size);
				angle = atan2(Direction_Bullet.y, Direction_Bullet.x) * 180 / PI;
				Direct NewAbsorb(&Shots_Texture, angle, Direction_Bullet, 15, Vector2u(4, 1), 0.2f);
				NewAbsorb.setPos(Warpscream_Body.getPosition());
				NewAbsorb.isWave = true;
				Absorb.push_back(NewAbsorb);
			}
			isShot = false;
		}

		
		/*Generating*/

		if (GenerateT_Time >= 5.0f && !isDying)
		{
			GenerateT_Time = 0;
			Warpscream_Body.setPosition(Vector2f(rand() % 767 + 400, rand()%401+100));
			isGenerating = true;
			Warpscream_Animation.Visible = true;
			Warpscream_Animation.Current_Image.x = 0;			
		}

		if (Warpscream_Health <= 700 / 2)
		{
			HP_Bar.setFillColor(Color::Red);
		}
		else
		{
			HP_Bar.setFillColor(Color::Green);
		}

		/*Die*/

		if (Warpscream_Health <= 0)
		{
			Warpscream_Health = 0;
			isDying = true;
			game_frame++;
			if (game_frame >= 50)
			{
				Warpscream_Visible = false;
				Warpscream_Dying = true;
				isDying = false;
			}
		}
		Warpscream_Animation.Update(Row, Difference);
		Warpscream_Body.setTextureRect(Warpscream_Animation.uvReact);
		Warpscream_Body.setOrigin(Warpscream_Body.getTextureRect().width / 2.0f, Warpscream_Body.getTextureRect().height / 2.0f);
		HP_Bar.setPosition(Vector2f(Warpscream_Body.getPosition().x - HP_Bar.getSize().x / 2, Warpscream_Body.getPosition().y - Warpscream_Body.getTextureRect().height / 2.0f - 50));
		HP_Bar.setSize(Vector2f((float)Warpscream_Health / 100 * 15, 10));
		Name.setPosition(Vector2f(Warpscream_Body.getPosition().x - 53, Warpscream_Body.getPosition().y - 120));
	}

	/*Generating*/

	if (isGenerating)
	{
		if (Player_Position.x >= Warpscream_Body.getPosition().x)	Row = Action::WarpM;
		else Row = Action::LWarp;
		Warpscream_Animation.Update(Row, Difference);
		Warpscream_Body.setTextureRect(Warpscream_Animation.uvReact);
		if (!Warpscream_Animation.Visible)
		{
			Warpscream_Visible = true;
			isGenerating = false;
		}
	}

	/*Drawing*/

	if (Warpscream_Visible&&game_frame%4==0)
	{
		window.draw(Warpscream_Body);
		window.draw(HP_Bar);
		window.draw(Name);
	}
	for (int i = 0; i < White_force.size(); i++)
	{
		White_force[i].Update(Difference);
		if (White_force[i].Explosion_Visible)
		{
			if (White_force[i].Explosion_Animation.Current_Image.x == 2)
			{
				White_force[i].Damagable = true;
				White_force[i].Damage = 15;
			}
			else
			{
				White_force[i].Damagable = false;

			}
			window.draw(White_force[i].Explosion_Body);
		}
		else
		{
			White_force.erase(White_force.begin() + i);
			break;
		}
	}
	for (int i = 0; i < Absorb.size(); i++)
	{
		Absorb[i].fire(250, Difference, Absorb[i].Get_Direction());
		if (Absorb[i].isWave)
			Absorb[i].Update(Difference, window);
		else
			Absorb[i].Draw(window);
	}
}