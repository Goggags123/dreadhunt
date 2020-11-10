#include "Player.h"
#include "Animation.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <math.h>
#include "Direct.h"
#include <vector>
#include <Windows.h>
#include "Floor.h"
#include "Collision.h"
#include "Projectiles.h"
#define PI 3.14
using namespace sf;

Player::Player(Texture *Player_Texture,float speed, bool Face_Right, Vector2u Size, float Switch_Time)
	: Player_Animation(Player_Texture, Size, Switch_Time)
{
	Face_Right = true;
	Row = 0;
	this->speed = speed;
	Player_Texture->setSmooth(true);
	Body.setTexture(*Player_Texture);
	Bullet_Texture.loadFromFile("Sprite/Weapons/Pistol_Bullet.png");
	ProBullet_Texture.loadFromFile("Sprite/Weapons/Lob_Bullet.png");
	Wave_Texture.loadFromFile("Sprite/Weapons/Wave_Bullet.png");
	Arrow_Texture.loadFromFile("Sprite/Weapons/Arrow_Bullet.png");	
	Laser_Texture.loadFromFile("Sprite/Weapons/Laser.png");
	Normal_Sound.loadFromFile("Sprite/Sound/Normal_Shot.ogg");
	Normal.setBuffer(Normal_Sound);
	Normal.setVolume(100);
	Laser_Sound.loadFromFile("Sprite/Sound/Laser.ogg");
	Laser.setBuffer(Laser_Sound);
	Laser.setVolume(80);
	Lob_Sound.loadFromFile("Sprite/Sound/Lob.ogg");
	Lob.setBuffer(Lob_Sound);
	Lob.setVolume(40);
	Wave_Sound.loadFromFile("Sprite/Sound/Wave.ogg");
	Wave.setBuffer(Wave_Sound);
	Wave.setVolume(60);
	Arrow_Sound.loadFromFile("Sprite/Sound/Arrow.ogg");
	Arrow.setBuffer(Arrow_Sound);
	Arrow.setVolume(60);
	Ghost_Body.setTexture(*Player_Texture);
	Body.setOrigin(Body.getTextureRect().width / 2.0f / (float)Size.x, Body.getTextureRect().height / 2.0f / (float)Size.y);
	Ghost_Body.setOrigin(Ghost_Body.getTextureRect().width / 2.0f / (float)Size.x, Ghost_Body.getTextureRect().height / 2.0f / (float)Size.y);
}

void Player::Update(float Difference,Vector2f Mouse_Position,RenderWindow &window, std::vector <Floor> &Platforms, std::vector <Direct> &bulletVec,std::vector <Projectiles> &bullet)
{
	if (Player_Visible)
	{
		if (!isDying)
		{
			movement.x = 0;
			movement.y = 0;
			Ghost_Body.setPosition(Body.getPosition().x, Body.getPosition().y - 10);
			Count_Time += Difference;
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				movement.x += speed;
				Ghost_Body.move(movement.x*Difference, 0);
				for (int i = 0; i < Platforms.size(); i++)
				{
					if (Collision::PixelPerfectTest(Ghost_Body, Platforms[i].Body(), 0))
					{
						movement.x = 0;
					}
				}
				Row = Action::Walk_Gun;
				Face_Right = true;
			}
			else if (Keyboard::isKeyPressed(Keyboard::A))
			{
				movement.x -= speed;
				Ghost_Body.move(movement.x*Difference, 0);
				for (int i = 0; i < Platforms.size(); i++)
				{
					if (Collision::PixelPerfectTest(Ghost_Body, Platforms[i].Body(), 0))
					{
						movement.x = 0;
					}
				}
				Row = Action::LWalk_Gun;
				Face_Right = false;
			}
			else
			{
				if (krang == 0)
				{
					Point_Time = Count_Time;
					krang = 1;
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::W) && Can_Jump)
			{
				Can_Jump = false;
				isJumping = true;
				height = abs(Body.getPosition().y) - abs(Jump_Height);
				Count_Time = 0;
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (Count_Time - Timer >= 0.5||isLaser)
				{					
					if (Face_Right)
						Row = Action::Shoot;
					else Row = Action::LShoot;
					Count_Time = 0;
					if (isDirect) Normal.play();
					if (isLaser) Laser.play();
					if (isLob) Lob.play();
					if (isWave)Wave.play();
					if (isArrow) Arrow.play();
					Vector_Size = sqrt(pow(Mouse_Position.x - Body.getPosition().x, 2) + pow(Mouse_Position.y - Body.getPosition().y, 2));
					Direction_Bullet.x = (Mouse_Position.x - Body.getPosition().x) / (Vector_Size);
					Direction_Bullet.y = (Mouse_Position.y - Body.getPosition().y) / (Vector_Size);
					angle = atan2(Direction_Bullet.y, Direction_Bullet.x) * 180 / PI;
					isFiring = true;
				}
			}
			if (Count_Time >= Point_Time + 1.6f&&krang == 1)
			{
				if (Face_Right)
					Row = Action::Idle;
				else Row = Action::LIdle;
				krang = 0;
				Count_Time = 0;
				Point_Time = 0;
			}
		}

		/*Shots*/

		if (isFiring)
		{
			Timer = Count_Time;
			if (isDirect)
			{
				Direct newBullet(&Bullet_Texture, angle, Direction_Bullet, 10,Vector2u(1,1),0.0f);
				newBullet.setPos(Body.getPosition());
				bulletVec.push_back(newBullet);
			}
			else if (isLob)
			{
				Projectiles newBullet(&ProBullet_Texture, Vector2f(Mouse_Position.x - Body.getPosition().x, 140), 500, Vector2u(1, 1), 0.0f, 20);
				newBullet.setPos(Body.getPosition());
				bullet.push_back(newBullet);
			}
			else if (isWave)
			{
				Direct newBullet(&Wave_Texture, angle, Direction_Bullet, 15, Vector2u(4, 1), 0.2f);
				newBullet.setPos(Body.getPosition());
				newBullet.Bullet_Animation.Current_Image.x = 0;
				newBullet.Bullet_Animation.Visible = true;
				bulletVec.push_back(newBullet);
			}
			else if (isArrow)
			{
				Direct newBullet(&Arrow_Texture, angle, Direction_Bullet, 30, Vector2u(1, 1), 0.0f);
				newBullet.setPos(Body.getPosition());
				bulletVec.push_back(newBullet);
			}
			else if (isLaser)
			{
				Direct newBullet(&Laser_Texture, angle, Direction_Bullet, 1, Vector2u(1, 1), 0.0f);
				newBullet.setPos(Body.getPosition());
				bulletVec.push_back(newBullet);
			}
			isFiring = false;
		}
		for (int i = 0; i < bulletVec.size(); i++)
		{
			bulletVec[i].fire(1000, Difference, bulletVec[i].Get_Direction());
			if (isWave)
			{
				bulletVec[i].Update(Difference,window);
			}
			else
			{
				bulletVec[i].Draw(window);
			}
		}
		for (int i = 0; i < bullet.size(); i++)
		{
			bullet[i].fire(Difference);
			bullet[i].Draw(window);
		}
		printf("%f %f\n", Body.getPosition().x, Body.getPosition().y);

		/*Smooth Jumping*/

		if (isJumping)
		{
			if (Body.getPosition().y >= height)
			{
				movement.y -= sqrt(Jump_Height * 1000 * 2);
				Ghost_Body.move(movement*Difference);
				for (int i = 0; i < Platforms.size(); i++)
				{
					if (Collision::PixelPerfectTest(Ghost_Body, Platforms[i].Body(), 0)||Ghost_Body.getPosition().y - abs(Ghost_Body.getTextureRect().height) / 4 < Platforms[i].Position().y || Ghost_Body.getPosition().y + abs(Ghost_Body.getTextureRect().height) / 4 > Platforms[i].Get_Size().height)
					{
						movement.y = 0;
						isJumping = false;
					}
				}
			}
			else
			{
				isJumping = false;
				height = Body.getPosition().y;
			}
		}
		for (int i = 0; i < Platforms.size(); i++)
		{
			
			if (Collision::PixelPerfectTest(Body, Platforms[i].Body(), 0))
			{
				Can_Jump = true;
				isJumping = false;
			}
			else
			{
				movement.y += 200;
			}
			if (Ghost_Body.getPosition().x - abs(Ghost_Body.getTextureRect().width) / 4 < Platforms[i].Position().x || Ghost_Body.getPosition().x + abs(Ghost_Body.getTextureRect().width) / 4 > Platforms[i].Get_Size().width)
			{
				movement.x = 0;
			}
		}
		if (HP <= 0 && !isDying)
		{
			isDying = true;
			Player_Animation.Visible = true;
			Player_Animation.Current_Image.x = 0;
		}

		/*if (Slashing)
		{
			if (Face_Right)
				Row = Action::Slash;
			else Row = Action::LSlash;
			Player_Animation.Update(Row, Difference);
			Body.setTextureRect(Player_Animation.uvReact);
			if (Player_Animation.Current_Image.x == 4 || Player_Animation.Current_Image.x == 5)
				isSlashing = true;
			else
				isSlashing = false;
			if (!Player_Animation.Visible)
			{
				if (Face_Right)
					Row = Action::Idle;
				else Row = Action::LIdle;
				Slashing = false;
			}
		}*/

		/*Hurting Animation*/

		if (isHurting)
		{
			if (Face_Right) Row = Action::Hurt;
			else Row = Action::LHurt;
			Player_Animation.Update(Row, Difference);
			Body.setTextureRect(Player_Animation.uvReact);
			if (!Player_Animation.Visible)
			{
				if (Face_Right)
					Row = Action::Idle;
				else Row = Action::LIdle;
				isHurting = false;
			}
		}

		/*Dying Animation*/

		if (isDying)
		{
			if (Face_Right) Row = Action::Die;
			else Row = Action::LDie;
			Player_Animation.Update(Row, Difference);
			Body.setTextureRect(Player_Animation.uvReact);
			if (!Player_Animation.Visible)
			{
				Player_Visible = false;
				isDying = false;
			}
		}

		Player_Animation.Update(Row, Difference);
		Body.setTextureRect(Player_Animation.uvReact);
		Ghost_Body.setTextureRect(Player_Animation.uvReact);
		Body.setOrigin(Body.getTextureRect().width / 2.0f, Body.getTextureRect().height / 2.0f);
		Ghost_Body.setOrigin(Ghost_Body.getTextureRect().width / 2.0f, Ghost_Body.getTextureRect().height / 2.0f);
		Body.move(movement*Difference);
	}
	if (Player_Visible)
	{
		
		window.draw(Body);
	}
}

void Player::Draw(RenderWindow &Window)
{
	Window.draw(Body);
}


Player::~Player()
{
}
