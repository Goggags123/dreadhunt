#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Animation
{
public:
	Animation(Texture* Texture, Vector2u Size, float Switch_Time);
	~Animation();
	IntRect uvReact;
	void Update(float Row, float Difference);
	
	Vector2u Current_Image;
	Vector2u Size;
	bool Visible = true;
private:
	float Total_Time;
	float Switch_Time;
};
