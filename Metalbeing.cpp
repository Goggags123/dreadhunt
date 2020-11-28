#include "Metalbeing.h"
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include <vector>
#include "Floor.h"
#include "Collision.h"
using namespace sf;

Metalbeing::Metalbeing(Texture *Metalbeing_Texture, Vector2u Size, float Switch_Time, Vector2f Position, Vector2f xPos)
	: Metalbeing_Animation(Metalbeing_Texture, Size, Switch_Time)
{
	Metalbeing_Texture->setSmooth(true);
	Metalbeing_Body.setTexture(*Metalbeing_Texture);
	Ghost_Body.setTexture(*Metalbeing_Texture);
	this->xPos = xPos;
	this->Position = Position;
	Metalbeing_Body.setScale(2,2);
	Ghost_Body.setScale(2, 2);
	Metalbeing_Body.setOrigin(Metalbeing_Body.getTextureRect().width / 2.0f / (float)Size.x, Metalbeing_Body.getTextureRect().height / 2.0f / (float)Size.y);
	Ghost_Body.setOrigin(Ghost_Body.getTextureRect().width / 2.0f / (float)Size.x, Ghost_Body.getTextureRect().height / 2.0f / (float)Size.y);
	Metalbeing_Body.setPosition(Position);
	HP_Bar.setSize(Vector2f(500, 10));
	HP_Bar.setFillColor(Color::Green);
	HP_Bar.setOutlineThickness(1);
	HP_Bar.setOutlineColor(Color::Black);
	Title_Font.loadFromFile("Sprite/Font/Title_Font.TTF");
}


Metalbeing::~Metalbeing()
{
}

void Metalbeing::Update(float Difference, Vector2f Player_Position, RenderWindow &window, std::vector <Floor> &Platforms)
{
	if (Metalbeing_Visible)
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
			Ghost_Body.setPosition(Metalbeing_Body.getPosition().x, Metalbeing_Body.getPosition().y - 5);
			if (Total_Time >= (rand() % 5 / 2.0 + 0.5))
			{
				Total_Time = 0;
				int direction = rand() % 3;
				switch (direction)
				{
				case 0:
				{
					movement.x = -Speed;
					Row = Action::LWalk;
					if (Metalbeing_Body.getPosition().x <= Position.x - xPos.x)
					{
						movement.x = 0;
						Row = Action::Idle;
					}
					break;
				}
				case 1:
				{
					movement.x = 0;
					Row = Action::Idle;
					break;
				}
				case 2:
				{
					movement.x = Speed;
					Row = Action::Walk;
					if (Metalbeing_Body.getPosition().x >= Position.x + xPos.y)
					{
						movement.x = 0;
						Row = Action::Idle;
					}
					break;
				}
				}
			}
		}
		
		/*Dying*/

		if (Metalbeing_Health <= 10 / 2)
		{
			HP_Bar.setFillColor(Color::Red);
		}
		if (Metalbeing_Health <= 0 && !isDying)
		{
			Metalbeing_Health = 0;
			Metalbeing_Animation.Current_Image.x = 0;
			Metalbeing_Animation.Visible = true;
			isDying = true;
		}
		if (isDying)
		{
			if (Player_Position.x >= Metalbeing_Body.getPosition().x) Row = Action::Die;
			else Row = Action::LDie;
			Metalbeing_Animation.Update(Row, Difference);
			Metalbeing_Body.setTextureRect(Metalbeing_Animation.uvReact);
			if (!Metalbeing_Animation.Visible)
			{
				Metalbeing_Visible = false;
				isDying = false;
			}
		}

		/*Wall Collision*/
		
		Ghost_Body.move(movement*Difference);
		for (int i = 0; i < Platforms.size(); i++)
		{
			if (!Collision::PixelPerfectTest(Platforms[i].Body(), Ghost_Body, 0)&&Can_Move)
			{
				Metalbeing_Body.move(movement*Difference);
			}
		}

		/*Gravity*/

		for (int i = 0; i < Platforms.size(); i++)
		{
			if (!Collision::PixelPerfectTest(Platforms[i].Body(), Metalbeing_Body, 0)&&Can_Move)
			{
				Metalbeing_Body.move(0, 98.1*Difference);
				Can_Move = false;
			}
			else
			{
				Can_Move = true;
			}
		}

		Metalbeing_Animation.Update(Row, Difference);
		Metalbeing_Body.setTextureRect(Metalbeing_Animation.uvReact);
		Ghost_Body.setTextureRect(Metalbeing_Animation.uvReact);
		Metalbeing_Body.setOrigin(Metalbeing_Body.getTextureRect().width / 2.0f, Metalbeing_Body.getTextureRect().height / 2.0f);
		Ghost_Body.setOrigin(Ghost_Body.getTextureRect().width / 2.0f, Ghost_Body.getTextureRect().height / 2.0f);
		HP_Bar.setPosition(Vector2f(Metalbeing_Body.getPosition().x - HP_Bar.getSize().x / 2, Metalbeing_Body.getPosition().y - Metalbeing_Body.getTextureRect().height / 2.0f-20));
		HP_Bar.setSize(Vector2f((float)Metalbeing_Health / 100 * 500, 10));
		Name.setPosition(Vector2f(Metalbeing_Body.getPosition().x - 45, Metalbeing_Body.getPosition().y - 70));
	}
	
	/*Draw*/

	if (Metalbeing_Visible)
	{
		window.draw(Metalbeing_Body);
		window.draw(HP_Bar);
		window.draw(Name);
	}
}
