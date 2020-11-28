#include "Gloomthing.h"
#include <SFML\Graphics.hpp>
#include "Animation.h"
using namespace sf;


Gloomthing::Gloomthing(Texture *Gloomthing_Texture,Vector2u Size,float Switch_Time, Vector2f Position)
	: Gloomthing_Animation (Gloomthing_Texture,Size,Switch_Time)
{
	Gloomthing_Texture->setSmooth(true);
	Gloomthing_Body.setTexture(*Gloomthing_Texture);
	HP_Bar.setSize(Vector2f(100, 10));
	HP_Bar.setFillColor(Color::Red);
	Gloomthing_Body.setScale(2,2);
	Gloomthing_Body.setOrigin(Gloomthing_Body.getTextureRect().width / 2.0f / (float)Size.x, Gloomthing_Body.getTextureRect().height / 2.0f / (float)Size.y);
	Gloomthing_Body.setPosition(Position);
	Gloomthing_Animation.Current_Image.x = 0;
	Gloomthing_Animation.Visible = true;
	HP_Bar.setSize(Vector2f(190, 10));
	HP_Bar.setFillColor(Color::Green);
	HP_Bar.setOutlineThickness(1);
	HP_Bar.setOutlineColor(Color::Black);
	Title_Font.loadFromFile("Sprite/Font/Title_Font.TTF");
}


Gloomthing::~Gloomthing()
{
}

void Gloomthing::Gloomthing_Update(float Difference, Vector2f Player_Position, RenderWindow & window)
{

	if (Gloomthing_Visible)
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

				/*Crunching*/

				if (sqrt(pow(Player_Position.x - Gloomthing_Body.getPosition().x, 2) + pow(Player_Position.y - Gloomthing_Body.getPosition().y, 2)) <= 150)
				{
					if (Player_Position.x >= Gloomthing_Body.getPosition().x)	Row = Action::Crunch;
					else Row = Action::LCrunch;
				}

				/*Idle*/

				else
				{
					if (Player_Position.x >= Gloomthing_Body.getPosition().x)	 Row = Action::Idle;
					else Row = Action::LIdle;
				}
			}
		}

		/*Generating*/

		if (GenerateT_Time >= Generate_Time+5.0f&&!isDying)
		{
			Generate_Time = GenerateT_Time;
			int num = rand()%3;
			switch (num)
			{
			case 1:
				if (Gloomthing_Body.getPosition().x != 3491)
				{
					Gloomthing_Body.setPosition(Vector2f(3491,300));
					isGenerating = true;
					Gloomthing_Animation.Visible = true;
					Gloomthing_Animation.Current_Image.x = 0;
				}
				break;
			case 2:
				if (Gloomthing_Body.getPosition().x != 3250)
				{
					Gloomthing_Body.setPosition(Vector2f(3250, 300));
					isGenerating = true;
					Gloomthing_Animation.Visible = true;
					Gloomthing_Animation.Current_Image.x = 0;
				}
				break;
			case 0:
				if (Gloomthing_Body.getPosition().x != 3028)
				{
					Gloomthing_Body.setPosition(Vector2f(3028, 300));
					isGenerating = true;
					Gloomthing_Animation.Visible = true;
					Gloomthing_Animation.Current_Image.x = 0;
				}
				break;
			}
		}

		/*Die*/
		if (Gloomthing_Health <= 50/2)
		{
			HP_Bar.setFillColor(Color::Red);
		}
		if (Gloomthing_Health <= 0&&!isDying)
		{
			Gloomthing_Health = 0;
			isDying = true;
			Gloomthing_Animation.Visible = true;
			Gloomthing_Animation.Current_Image.x = 0;
		}
		if (isDying)
		{
			if (Player_Position.x >= Gloomthing_Body.getPosition().x)	Row = Action::Die;
			else Row = Action::LDie;
			Gloomthing_Animation.Update(Row, Difference);
			Gloomthing_Body.setTextureRect(Gloomthing_Animation.uvReact);
			if (!Gloomthing_Animation.Visible)
			{
				Gloomthing_Visible = false;
				Gloomthing_Dying = true;
			}

		}
		Gloomthing_Animation.Update(Row, Difference);
		Gloomthing_Body.setTextureRect(Gloomthing_Animation.uvReact);
		Gloomthing_Body.setOrigin(Gloomthing_Body.getTextureRect().width / 2.0f, Gloomthing_Body.getTextureRect().height / 2.0f);
		HP_Bar.setPosition(Vector2f(Gloomthing_Body.getPosition().x - HP_Bar.getSize().x / 2, Gloomthing_Body.getPosition().y - Gloomthing_Body.getTextureRect().height / 2.0f - 30));
		HP_Bar.setSize(Vector2f((float)Gloomthing_Health / 100 * 190, 10));
		Name.setPosition(Vector2f(Gloomthing_Body.getPosition().x - 44, Gloomthing_Body.getPosition().y - 70));
	}

	/*Generating*/

	if (isGenerating)
	{
		if (Player_Position.x >= Gloomthing_Body.getPosition().x) Row = Action::Generate;
		else Row = Action::LGenerate;
		Gloomthing_Animation.Update(Row, Difference);
		Gloomthing_Body.setTextureRect(Gloomthing_Animation.uvReact);
		if (!Gloomthing_Animation.Visible)
		{
			Gloomthing_Visible = true;
			isGenerating = false;
		}
	}

	/*Drawing*/

	if (Gloomthing_Visible)
	{
		window.draw(Gloomthing_Body);
		window.draw(HP_Bar);
		window.draw(Name);
	}
}
