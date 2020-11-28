#include "Projectiles.h"
#include <math.h>
#include <SFML\Graphics.hpp>
#include "Animation.h"
using namespace sf;
#define g 9.81

Projectiles::Projectiles(Texture *Bullet_Texture, Vector2f Distance, float Expected_BulletSpeed, Vector2u Size, float Switch_Time,float Damage)
	: Projectile_Animation(Bullet_Texture,Size,Switch_Time)
{
	Bullet_Texture->setSmooth(true);
	Bullet.setTexture(*Bullet_Texture);
	this->Expected_BulletSpeed = Expected_BulletSpeed;
	this->Distance = Distance;
	this->Damage = Damage;
	angle = atan(4.0*abs(Distance.y) / abs(Distance.x));
	Real_BulletSpeed = sqrt(g*abs(Distance.x) / 2.0 / sin(angle) / cos(angle));
	Bullet.setOrigin(Bullet.getTextureRect().width / 2.0f / (float)Size.x, Bullet.getTextureRect().height / 2.0f / (float)Size.y);
}

Projectiles::~Projectiles()
{
}
void Projectiles::Update(float Difference,RenderWindow &window)
{
	Projectile_Animation.Update(0, Difference);
	Bullet.setTextureRect(Projectile_Animation.uvReact);
	Bullet.setOrigin(Bullet.getTextureRect().width / 2.0f, Bullet.getTextureRect().height / 2.0f);
	window.draw(Bullet);
}
