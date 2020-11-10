#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include <vector>
#include "Floor.h"
#include "Collision.h"
#include "Projectiles.h"
#include "Explosion.h"
#include "Direct.h"
using namespace sf;
class Vexling
{
public:
	enum Action { Idle,Move,Attack,Pierce,Disappear,Appear,Black, LIdle, LMove, LAttack,LPierce, LDisappear, LAppear, LBlack};
	enum Moves { Piercing_Eye,ShotsM };
	Vexling(Texture *Vexling_Texture, Vector2u Size, float Switch_Time, Vector2f Position);
	~Vexling();
	bool Vexling_Visible = true, isDying = false;
	int Score = 250;
	float Vexling_Health = 450;
	int Row = Action::LIdle;
	bool Vexling_Dying = false;
	void Update(float Difference, Vector2f Player_Position, RenderWindow &window, std::vector <Floor> &Platforms, std::vector <Projectiles> &Black_Bile, std::vector <Explosion> &Black_Explosion, std::vector <Explosion> &Piercing, std::vector <Direct> &Shots);
	Sprite &Get_Body()
	{
		return Vexling_Body;
	}
	std::string name = "Vexling";
private:
	float GenerateT_Time = 0, Total_Time = 0,Count_Time = 0;
	Sprite Vexling_Body;
	Animation Vexling_Animation;
	Texture Black_BileT;
	Texture Black_ExplosionT;
	Texture Shots_Texture;
	Texture PiercingT;
	int moves;
	bool PhaseII = false;
	bool isShot = false,isGenerating = true, isFiring = false;
	Vector2f Absorb_Position, Direction_Bullet;
	float angle, Vector_Size;
	RectangleShape HP_Bar;
	Text Name;
	Font Title_Font;
};

