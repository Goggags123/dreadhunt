#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include <vector>
#include "Floor.h"
#include "Collision.h"
#include "Projectiles.h"
#include "Explosion.h"
using namespace sf;
class Thornseeker
{
public:
	enum Action { Walking, Spark, Idle,Walk, PreThorn, Thorn,Stable, LWalking, LSpark, LIdle, LWalk, LPreThorn, LThorn,LStable};
	enum Moves {Spark_Rush,Thorn_Spikeja,WalkState};
	Thornseeker(Texture *Thornseeker_Texture, Vector2u Size, float Switch_Time, Vector2f Position, Vector2f xPos);
	~Thornseeker();
	bool Thornseeker_Visible = true, isDying = false;
	int Score = 300;
	float Thornseeker_Health = 500;
	int Row = Action::LWalk;
	void Update(float Difference, Vector2f Player_Position, RenderWindow &window, std::vector <Floor> &Platforms,std::vector <Projectiles> &Thorn, std::vector <Explosion> &Thorn_Spike,std::vector <Explosion> &Lightning_Bolt);
	Sprite &Get_Body()
	{
		return Thornseeker_Body;
	}
	std::string name = "Thornseeker";
private:
	float Count_Time = 0, Total_Time = 0,Lightning_Time = 0;
	Sprite Thornseeker_Body;
	Animation Thornseeker_Animation;
	Texture Thorn_Texture;
	Texture Spike_Texture;
	Texture Lightning_Texture;
	float multiplier = 1;
	float Speed = -100;
	Vector2f xPos, Position;
	bool isSparking = false;
	int moves;
	float delay = 3.0f;
	int game_frame = 0;
	bool isRushing = false, Can_Move = false;
	bool isFiring = false,isFirst =false,isSecond = false;
	Text Name;
	Font Title_Font;
	RectangleShape HP_Bar;

};

