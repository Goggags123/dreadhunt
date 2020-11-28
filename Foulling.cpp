#include "Foulling.h"
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include <vector>
#include "Floor.h"
#include "Collision.h"
using namespace sf;

Foulling::Foulling(Texture *Foulling_Texture, Vector2u Size, float Switch_Time, Vector2f Position, Vector2f xPos)
	: Foulling_Animation(Foulling_Texture,Size,Switch_Time)
{
	Foulling_Texture->setSmooth(true);
	Ghost_Body.setTexture(*Foulling_Texture);
	Foulling_Body.setTexture(*Foulling_Texture);
	this->Speed = Speed;
	this->xPos = xPos;
	this->Position = Position;
	Foulling_Body.setScale(2, 2);
	Ghost_Body.setScale(2, 2);
	Foulling_Body.setOrigin(Foulling_Body.getTextureRect().width / 2.0f / (float)Size.x, Foulling_Body.getTextureRect().height / 2.0f / (float)Size.y);
	Ghost_Body.setOrigin(Ghost_Body.getTextureRect().width / 2.0f / (float)Size.x, Ghost_Body.getTextureRect().height / 2.0f / (float)Size.y);
	Foulling_Body.setPosition(Position);
	HP_Bar.setSize(Vector2f(200, 10));
	HP_Bar.setFillColor(Color::Green);
	HP_Bar.setOutlineThickness(1);
	HP_Bar.setOutlineColor(Color::Black);
	Title_Font.loadFromFile("Sprite/Font/Title_Font.TTF");
}


Foulling::~Foulling()
{
}

void Foulling::Update(float Difference,Vector2f Player_Position, RenderWindow &window,std::vector <Floor> &Platforms)
{
	if (Foulling_Visible)
	{
		if (!isDying)
		{
			Name.setFont(Title_Font);
			Name.setCharacterSize(12);
			Name.setFillColor(Color::White);
			Name.setOutlineThickness(1);
			Name.setOutlineColor(Color::Black);
			Name.setString(name);
			Ghost_Body.setPosition(Foulling_Body.getPosition().x, Foulling_Body.getPosition().y - 5);
			if (sqrt(pow(Player_Position.x - Foulling_Body.getPosition().x, 2) + pow(Player_Position.y - Foulling_Body.getPosition().y, 2)) <= 250)
			{
				if (Player_Position.x >= Foulling_Body.getPosition().x)	Row = Action::Rush;
				else Row = Action::LRush;
				isRushing = true;
				isMoving = false;
				yes = true;
				multiplier = 1.5;
			}

			/*Walk*/

			else
			{
				multiplier = 1;
				isRushing = false;
				isMoving = true;
				yes = true;
			}
		}

		/*Gravity*/

		for (int i = 0; i < Platforms.size(); i++)
		{
			if (!Collision::PixelPerfectTest(Platforms[i].Body(), Foulling_Body, 0))
			{
				Foulling_Body.move(0, 98.1*Difference);
				Can_Move = false;
			}
			else
			{
				Can_Move = true;
			}
		}

		/*Moving*/

		if (isMoving)
		{
			if (Foulling_Body.getPosition().x <= Position.x - xPos.x)
			{
				Speed = -Speed;
				Row = Action::Walk;
			}
			else if (Foulling_Body.getPosition().x >= Position.x + xPos.y)
			{
				Speed = -Speed;
				Row = Action::LWalk;
			}
		}		

		/*Rushing*/

		if (isRushing)
		{
			if (Player_Position.x < Foulling_Body.getPosition().x)
			{
				Speed = -abs(Speed);
			}
			else
			{
				Speed = abs(Speed);
			}
			if (Foulling_Body.getPosition().x <= Position.x-xPos.x&&Speed<0)
			{
				yes = false;
			}
			else if (Foulling_Body.getPosition().x >= Position.x + xPos.y&&Speed>=0)
			{
				yes = false;
			}
		}

		/*Dying*/
		if (Foulling_Health <= 30/2)
		{
			HP_Bar.setFillColor(Color::Red);
		}
		if (Foulling_Health <= 0 && !isDying)
		{
			Foulling_Health = 0;
			Foulling_Animation.Current_Image.x = 0;
			Foulling_Animation.Visible = true;
			isDying = true;
		}
		if (isDying)
		{
			if (Player_Position.x >= Foulling_Body.getPosition().x) Row = Action::Die;
			else Row = Action::LDie;
			Foulling_Animation.Update(Row, Difference);
			Foulling_Body.setTextureRect(Foulling_Animation.uvReact);
			if (!Foulling_Animation.Visible)
			{
				Foulling_Visible = false;
				isDying = false;
			}
		}

		/*Wall Collision*/

		Ghost_Body.move(Speed*multiplier*Difference, 0);
		for (int i = 0; i < Platforms.size(); i++)
		{
			if (!Collision::PixelPerfectTest(Platforms[i].Body(), Ghost_Body, 0) && yes&&Can_Move)
			{
				Foulling_Body.move(Speed*multiplier*Difference, 0);
			}
		}
		
		Foulling_Animation.Update(Row, Difference);
		Foulling_Body.setTextureRect(Foulling_Animation.uvReact);
		Foulling_Body.setOrigin(Foulling_Body.getTextureRect().width / 2.0f, Foulling_Body.getTextureRect().height / 2.0f);
		Ghost_Body.setTextureRect(Foulling_Animation.uvReact);
		Ghost_Body.setOrigin(Ghost_Body.getTextureRect().width / 2.0f, Ghost_Body.getTextureRect().height / 2.0f);
		HP_Bar.setPosition(Vector2f(Foulling_Body.getPosition().x - HP_Bar.getSize().x / 2, Foulling_Body.getPosition().y - Foulling_Body.getTextureRect().height / 2.0f));
		HP_Bar.setSize(Vector2f((float)Foulling_Health / 100 * 200, 10));
		Name.setPosition(Vector2f(Foulling_Body.getPosition().x - 38, Foulling_Body.getPosition().y - 70));
	}

	/*Draw*/

	if (Foulling_Visible)
	{
		window.draw(Foulling_Body);
		window.draw(HP_Bar);
		window.draw(Name);
	}
}
