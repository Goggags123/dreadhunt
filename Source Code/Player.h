#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Animation.h"
#include <iostream>
#include "Floor.h"
#include <vector>
#include "Direct.h"
#include "Flowmon.h"
#include "Povy.h"
#include "Projectiles.h"
using namespace sf;
class Player
{
public:
	enum Action { Idle, Walk, Jump, Walk_Gun, Shoot, Slash, Hurt, Die, LIdle, LWalk, LJump, LWalk_Gun, LShoot, LSlash, LHurt, LDie };
	~Player();
	Player(Texture *Player_Texture, float speed, bool Face_Right, Vector2u Size, float Switch_Time);
	void Update(float Difference, Vector2f Mouse_Position, RenderWindow &window, std::vector <Floor> &Platforms, std::vector <Direct> &DirectBullet, std::vector <Projectiles> &bullet);
	void Draw(RenderWindow &Window);
	Vector2f GetPosition()
	{
		return Body.getPosition();
	}
	Sprite& getBody()
	{
		return Body;
	}
	bool Face_Right = true, isHurting = false, isSlashing = false, isDying = false, Player_Visible = true;
	bool isWave = false, isLob = false, isArrow = false, isDirect = true,isLaser = false;
	Vector2f movement;
	int Row = 0;
	Animation Player_Animation;
	int HP = 100;
private:
	unsigned int LastRow;
	float speed, Vector_Size, angle;
	bool isFiring = false,Can_Jump,isJumping = false;
	float Switch_Time,Jump_Height = 200;
	float Timer = 0,height;
	bool Slashing = false;
	Vector2f Direction_Bullet;
	Texture Bullet_Texture,ProBullet_Texture,Arrow_Texture,Wave_Texture,Laser_Texture;
	float Point_Time,Count_Time = 0,velocity = 0;
	int krang = 0;
	Sound Normal;
	SoundBuffer Normal_Sound;
	Sound Laser;
	SoundBuffer Laser_Sound;
	Sound Lob;
	SoundBuffer Lob_Sound;
	Sound Wave;
	SoundBuffer Wave_Sound;
	Sound Arrow;
	SoundBuffer Arrow_Sound;
	Sprite Body,Ghost_Body;
};

