#pragma once
#include "SFML\Graphics.hpp"
#include "Animation.h"
#include "Floor.h"
#include "Explosion.h"
#include "Barrel.h"
#include "Collision.h"
#include "Direct.h"
using namespace sf;
class Warpscream
{
public:
	enum Action {Idle,White_ForceM,AbsorbM,ShotsM,WarpM, LIdle, LWhite_Force, LAbsorb, LShots, LWarp};
	enum Moves {White_ForceMoves,ShotsMoves,AbsorbMoves};
	Warpscream(Texture *Warpscream_Texture,Vector2u Size,float Switch_Time, Vector2f Position);
	~Warpscream();
	void Update(float Difference, std::vector<Floor>& Platforms, std::vector<Explosion>& White_force, std::vector <Direct> &Absorb, Vector2f Player_Position, RenderWindow &window, std::vector <Barrel> &Barrel_Body);
	Sprite& Get_Body()
	{
		return Warpscream_Body;
	}
	void Draw(RenderWindow &window)
	{
		window.draw(Warpscream_Body);
	}
	int Score = 400;
	int Warpscream_Health = 700;
	bool Warpscream_Visible = false, Warpscream_Dying = false;
	bool Shieldable = true;
	std::string name = "Warpscream";
private:
	Texture White_Texture;
	Texture Shots_Texture;
	Texture Absorb_Texture;
	Texture IceSH_Effects;
	Sprite Warpscream_Body;
	Animation Warpscream_Animation;
	bool isAbsorb = false;
	float Count_Time = 0, Total_Time = 0, GenerateT_Time = 0, Generate_Time = 0;
	float Vector_Size,angle;
	Vector2f Direction_Bullet;
	int Row;
	bool isGenerating = true;
	float delay = 2.0f;
	bool isDying = false,isShot = false;
	int moves,game_frame = 0;
	RectangleShape HP_Bar;
	Vector2f Absorb_Position;
	Text Name;
	Font Title_Font;
};

