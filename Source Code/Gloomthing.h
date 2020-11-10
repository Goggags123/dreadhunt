#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
class Gloomthing
{
public:
	enum Action { Generate,LGenerate,Crunch,LCrunch,Idle,LIdle,Die,LDie};
	Gloomthing(Texture *Gloomthing_Texture, Vector2u Size, float Switch_Time, Vector2f Position);
	~Gloomthing();
	void Gloomthing_Update(float Difference, Vector2f Player_Position, RenderWindow &window);
	Sprite& Get_Body()
	{
		return Gloomthing_Body;
	}
	void Draw(RenderWindow &window)
	{
		window.draw(Gloomthing_Body);
	}
	int Score = 10;
	bool isDying = false;
	int Gloomthing_Health = 50;
	bool Gloomthing_Visible = false,Gloomthing_Dying = false;
	std::string name = "Gloomthing";
private:
	float Count_Time = 0, Total_Time = 0, GenerateT_Time = 0, Generate_Time = 0;
	Sprite Gloomthing_Body;
	Animation Gloomthing_Animation;
	int Row;
	bool isGenerating = true;
	RectangleShape HP_Bar;
	Text Name;
	Font Title_Font;
};


