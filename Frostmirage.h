#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Animation.h"
#include <vector>
#include "Floor.h"
#include "Collision.h"
#include "Direct.h"
#include "Explosion.h"
#include "Clone.h"
using namespace sf;
class Frostmirage
{
public:
	enum Action {Idle,Die,LIdle,LDie};
	enum Moves {Typhoon,Fireball,Ice_Spike,Mirage};
	Frostmirage(Texture *Frostmirage_Texture, Vector2u Size, float Switch_Time, Vector2f Position, Vector2f xPos);
	~Frostmirage();
	bool Frostmirage_Visible = true;
	int Score = 350;
	float Frostmirage_Health = 450;
	void Update(float Difference, Vector2f Player_Position, RenderWindow &window, std::vector <Floor> &Platforms, std::vector <Direct> &Firephoon, std::vector <Explosion> &Ice_Spike, std::vector <Clone> &Frostmirage_Clone);
	Sprite &Get_Body()
	{
		return Body;
	}
	bool isClone = false, isDying = false;
	std::string name = "Frostmirage";
private:
	float Count_Time = 0, Total_Time = 0, Vector_Size, angle;
	Sprite Body;
	Vector2f movement;
	int moves;
	Vector2f Direction_Bullet;
	Animation Frostmirage_Animation;
	Texture Typhoon_Texture, Fireball_Texture, IceSpike_Texture,Frostmirage_Texture;
	int Row = Action::LIdle;
	float Speed = -100;
	Vector2f xPos, Position;
	RectangleShape HP_Bar;
	int Count_Clone = 0;
	bool isMoving = false, isFiring = false, Can_Move = false;
	Text Name;
	Font Title_Font;
};

