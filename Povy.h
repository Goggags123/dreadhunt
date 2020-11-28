#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Floor.h"
#include <vector>
#include "Direct.h"
#include "Projectiles.h"
#include "Text_String.h"
#include "Explosion.h"
using namespace sf;
class Povy
{
public:
	enum Action { Idle, Shoot };
	Povy(Texture *Povy_Texture, Vector2u Size, float Switch_Time, Vector2f Position, Texture *SP_Texture);
	~Povy();
	void Update(float Difference, Vector2f Player_Position, std::vector <Projectiles> &Povy_Ball, RenderWindow &window, std::vector <Floor> &Platforms);
	Sprite& Get_Body()
	{
		return Povy_Body;
	}
	void Draw(RenderWindow &window)
	{
		window.draw(Povy_Body);
	}
	int Score = 80;
	float Povy_Health = 70;
	bool Povy_Visible = true;
	bool isSplashing = false;
	std::string name = "Taintfiend";
	bool isDying = false;

private:
	float Count_Time = 0, Total_Time = 0;
	int Row;
	Animation Povy_Animation;
	Sprite Povy_Body;
	float Switch_Time;
	Texture PovyBall_Texture,PovySP_Texture;
	bool isFiring = false, PovySP_Visible = false;
	RectangleShape HP_Bar;
	int game_frame = 0;
	Text Name;
	Font Title_Font;
};

