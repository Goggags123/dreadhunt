#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Player.h"
#include "Foulling.h"
#include "Metalbeing.h"
#include "Povy.h"
#include "Flowmon.h"
#include "Gloomthing.h"
#include "Floor.h"
#include "Collision.h"
#include "Animation.h"
#include "Direct.h"
#include "Projectiles.h"
#include "Text_String.h"
#include "Item.h"
#include "Thornseeker.h"
#include <vector>
#include <string>
#include <time.h>
#include "Gaspow.h"
#include "Clone.h"
#include "Barrel.h"
#include "Frostmirage.h"
#include "Warpscream.h"
#include "Vexling.h"
#include "WarpGate.h"
#include <iostream>
#include <fstream>
#include <sstream>
std::vector <Floor> Platforms;
std::vector <Direct> bulletVec;
std::vector <Direct> Flowmon_Ball;
std::vector <Projectiles> Povy_Ball;
std::vector <Flowmon> Flowmon_Body;
std::vector <Povy> Povy_Body;
std::vector <Gloomthing> Gloomthing_Body;
std::vector <Item> Food;
std::vector <Text_String> Enemy_Score;
std::vector <Text_String> GUI;
std::vector <Item> Items;
std::vector <Foulling> Foulling_Body;
std::vector <Projectiles> bullet;
std::vector <Metalbeing> Metalbeing_Body;
std::vector <Gaspow> Gaspow_Body;
std::vector <Direct> Gaspow_Ball;
std::vector <Direct> Firephoon;
std::vector <Explosion> Ice_Spike;
std::vector <Frostmirage> Frostmirage_Body;
std::vector <Clone> Frostmirage_Clone;
std::vector <Direct> Fireball_Clone;
std::vector <Warpscream> Warpscream_Body;
std::vector <Thornseeker> Thornseeker_Body;
std::vector <Explosion> White_force;
std::vector <Direct> Absorb;
std::vector <Barrel> Barrel_Body;
std::vector <Projectiles> Thorn;
std::vector <Explosion> Thorn_Spike;
std::vector <Explosion> Lightning_Bolt;
std::vector <Explosion> Black_Explosion;
std::vector <Vexling> Vexling_Body;
std::vector <Explosion> Piercing;
std::vector <Projectiles> Black_Bile;
std::vector <Direct> Shots;
std::vector <Item> Time_Items;
std::vector <WarpGate> Warpgate_Body;
using namespace sf;
using std::ofstream;
using std::ifstream;

int main()
{
	enum Screen {Menu,Scoreboard,Name,How,First_Stage,First_Boss,Second_Stage,Second_Boss,Third_Stage,Third_Boss,Fourth_Stage,Fourth_Boss};
	int screen = Screen::Menu;

	RenderWindow Window(VideoMode(1366, 768), "Dreadhunt",Style::None);
	//RenderWindow Window(VideoMode(200, 200), "Dreadhunt", Style::Fullscreen);

	/*All the variables*/

	Texture Player_Texture, Background_Texture, Mouse_Texture, GUI_Texture,Warpgate_Texture,MainM_Texture,Pointer_Texture;

	Texture Flowmon_Texture,Vexling_Texture,Warpscream_Texture,Thornseeker_Texture, Spike_Texture,Povy_Texture, PovyBallSP_Texture,Metalbeing_Texture,Gloomthing_Texture,Gaspow_Texture,Foulling_Texture,Frostmirage_Texture;

	Texture Chicken, Soul,Soul1,Orange,Pizza,Cake,Ramen,Corn_Stick,Apple,Onigiri,Green_Apple,Cherry,Watermelon,Lemon,Shield_Texture,Wave_Gun,Arrow_Gun,Laser_Gun,Lob_Gun;
	
	Texture Shield_Effects, Button, Home_Texture, FlipHome_Texture, Scoreboard_Texture, Name_Texture,How_Texture,Exit_Texture;

	Texture FStage_Floor,FStage_Background,FBoss_Background,FBoss_Floor, SStage_Floor,SStage_Background,SBoss_Floor, SBoss_Background,FoStage_Background,FoStage_Floor, FoBoss_Background, FoBoss_Floor, TBoss_Background, TBoss_Floor,TStage_Floor,TStage_Background;

	Font GUI_Font, Score_Font,Title_Font;
	Sprite Shield,BMenu,BScoreboard, BQuit, BHow,Mouse_Pointer,Home,Flipped_Home,HowB;
	View Camera, Character, GUI_Place;
	Vector2f Mouse_Position, Direction_Bullet;
	float Difference = 0.0f;
	RectangleShape  Mouse_Cursor, GUI_Background,HP_Bar,Empty_Bar;
	int score = 0,num;
	bool isShieldON = false,onetime = true;
	int Metal_Count = 0;
	float Total_Item = 0,Count_Item = 0;
	float Time_Spawn = 0;
	float Total_Shield = 0 , Count_Shield = 0;
	bool Stop = false;
	
	int scoreRank[6];
	std::string user[6];
	String str;
	String text;
	sf::Text textUser("", GUI_Font, 30);
	textUser.setFillColor(Color::Red);
	ofstream writeUser;
	ofstream writeScore;
	ifstream userFile;
	ifstream scoreFile;
	bool Victory = false;

	Color Brown(252, 183, 88, 255);
	Image icon;
	icon.loadFromFile("Sprite/Environment/Icon.png");
	Window.setIcon(23, 23, icon.getPixelsPtr());

	/*Sound*/

	SoundBuffer FStage_Sound;
	FStage_Sound.loadFromFile("Sprite/Sound/FStage.ogg");
	Sound FStage;
	FStage.setBuffer(FStage_Sound);
	FStage.setLoop(true);
	FStage.setVolume(50);

	SoundBuffer SStage_Sound;
	SStage_Sound.loadFromFile("Sprite/Sound/SStage.ogg");
	Sound SStage;
	SStage.setBuffer(SStage_Sound);
	SStage.setLoop(true);
	SStage.setVolume(50);

	SoundBuffer TStage_Sound;
	TStage_Sound.loadFromFile("Sprite/Sound/TStage.ogg");
	Sound TStage;
	TStage.setBuffer(TStage_Sound);
	TStage.setLoop(true);
	TStage.setVolume(50);

	SoundBuffer FoStage_Sound;
	FoStage_Sound.loadFromFile("Sprite/Sound/FoStage.ogg");
	Sound FoStage;
	FoStage.setBuffer(FoStage_Sound);
	FoStage.setLoop(true);
	FoStage.setVolume(50);

	SoundBuffer Main_Song;
	Main_Song.loadFromFile("Sprite/Sound/Main.ogg");
	Sound Main_Theme;
	Main_Theme.setBuffer(Main_Song);
	Main_Theme.setLoop(true);
	Main_Theme.setVolume(50);

	SoundBuffer Click_Sound;
	Click_Sound.loadFromFile("Sprite/Sound/Click.ogg");
	Sound Click;
	Click.setBuffer(Click_Sound);
	Click.setVolume(80);

	SoundBuffer Win_Sound;
	Win_Sound.loadFromFile("Sprite/Sound/You_Win.flac");
	Sound Win;
	Win.setBuffer(Win_Sound);
	Win.setVolume(100);

	SoundBuffer Victory_Sound;
	Victory_Sound.loadFromFile("Sprite/Sound/Victory.ogg");
	Sound VictoryS;
	VictoryS.setBuffer(Victory_Sound);
	VictoryS.setVolume(50);

	SoundBuffer Key_Sound;
	Key_Sound.loadFromFile("Sprite/Sound/KeyPressed.ogg");
	Sound Key_Pressed;
	Key_Pressed.setBuffer(Key_Sound);
	Key_Pressed.setVolume(80);

	SoundBuffer Munch_Sound;
	Munch_Sound.loadFromFile("Sprite/Sound/Munch.ogg");
	Sound Munch;
	Munch.setBuffer(Munch_Sound);
	Munch.setVolume(50);

	SoundBuffer FBoss_Sound;
	FBoss_Sound.loadFromFile("Sprite/Sound/FBoss.ogg");
	Sound FBoss;
	FBoss.setBuffer(FBoss_Sound);
	FBoss.setLoop(true);
	FBoss.setVolume(50);

	SoundBuffer SBoss_Sound;
	SBoss_Sound.loadFromFile("Sprite/Sound/SBoss.ogg");
	Sound SBoss;
	SBoss.setBuffer(SBoss_Sound);
	SBoss.setLoop(true);
	SBoss.setVolume(50);

	SoundBuffer TBoss_Sound;
	TBoss_Sound.loadFromFile("Sprite/Sound/TBoss.ogg");
	Sound TBoss;
	TBoss.setBuffer(SBoss_Sound);
	TBoss.setLoop(true);
	TBoss.setVolume(50);

	SoundBuffer FoBoss_Sound;
	FoBoss_Sound.loadFromFile("Sprite/Sound/FoBoss.ogg");
	Sound FoBoss;
	FoBoss.setBuffer(FoBoss_Sound);
	FoBoss.setLoop(true);
	FoBoss.setVolume(50);

	SoundBuffer Die_Sound;
	Die_Sound.loadFromFile("Sprite/Sound/Gameover.ogg");
	Sound Die;
	Die.setBuffer(Die_Sound);
	Die.setVolume(30);

	SoundBuffer Item_Sound;
	Item_Sound.loadFromFile("Sprite/Sound/Item.ogg");
	Sound ItemSound;
	ItemSound.setBuffer(Item_Sound);
	ItemSound.setVolume(60);

	SoundBuffer Soul_Sound;
	Soul_Sound.loadFromFile("Sprite/Sound/Soul.ogg");
	Sound SoulSound;
	SoulSound.setBuffer(Soul_Sound);
	SoulSound.setVolume(200);

	/*Load all the Textures*/

	//Food
	Lemon.loadFromFile("Sprite/Items/Lemon.png");
	Watermelon.loadFromFile("Sprite/Items/Watermelon.png");
	Cherry.loadFromFile("Sprite/Items/Cherry.png");
	Apple.loadFromFile("Sprite/Items/Apple.png");
	Green_Apple.loadFromFile("Sprite/Items/Green_Apple.png");
	Pizza.loadFromFile("Sprite/Items/Pizza.png");
	Cake.loadFromFile("Sprite/Items/Cake.png");
	Corn_Stick.loadFromFile("Sprite/Items/Corn_Stick.png");
	Chicken.loadFromFile("Sprite/Items/Chicken.png");
	Orange.loadFromFile("Sprite/Items/Orange.png");
	Ramen.loadFromFile("Sprite/Items/Ramen.png");
	Onigiri.loadFromFile("Sprite/Items/Onigiri.png");

	//Font
	Score_Font.loadFromFile("Sprite/Font/Score_Font.TTF");
	GUI_Font.loadFromFile("Sprite/Font/GUI_Font.TTF");
	Title_Font.loadFromFile("Sprite/Font/Title_Font.TTF");

	//Items
	Shield_Effects.loadFromFile("Sprite/Effects/Shield.png");
	Shield_Texture.loadFromFile("Sprite/Items/Shield.png");
	Soul.loadFromFile("Sprite/Items/Soul.png");
	Soul1.loadFromFile("Sprite/Items/Soul1.png");
	Wave_Gun.loadFromFile("Sprite/Weapons/Wave_Gun.png");
	Lob_Gun.loadFromFile("Sprite/Weapons/Lob_Gun.png");
	Arrow_Gun.loadFromFile("Sprite/Weapons/Arrow_Gun.png");
	Laser_Gun.loadFromFile("Sprite/Weapons/Laser_Gun.png");

	//Monsters
	Warpscream_Texture.loadFromFile("Sprite/Boss/Warpscream.png");
	Frostmirage_Texture.loadFromFile("Sprite/Boss/Frostmirage.png");
	Gaspow_Texture.loadFromFile("Sprite/Monster/Gaspow.png");
	Gloomthing_Texture.loadFromFile("Sprite/Monster/Gloomthing.png");
	Metalbeing_Texture.loadFromFile("Sprite/Monster/Metalbeing.png");
	Flowmon_Texture.loadFromFile("Sprite/Monster/Flowmon.png");
	PovyBallSP_Texture.loadFromFile("Sprite/Monster/PovyBall_Splash.png");
	Povy_Texture.loadFromFile("Sprite/Monster/Povy.png");
	Foulling_Texture.loadFromFile("Sprite/Monster/Foulling.png");
	Thornseeker_Texture.loadFromFile("Sprite/Boss/Thornseeker.png");
	Vexling_Texture.loadFromFile("Sprite/Boss/Vexling.png");
	Spike_Texture.loadFromFile("Sprite/Boss/Thorn_Spike.png");

	//Others
	GUI_Texture.loadFromFile("Sprite/Environment/GUI.jpg");
	Player_Texture.loadFromFile("Sprite/Character/maincharacter.png");
	Warpgate_Texture.loadFromFile("Sprite/Effects/Black_Hole.png"); 
	Button.loadFromFile("Sprite/Environment/button.png");
	Mouse_Texture.loadFromFile("Sprite/Environment/Target.png");
	MainM_Texture.loadFromFile("Sprite/Environment/Mouse_Menu.png");
	Pointer_Texture.loadFromFile("Sprite/Environment/Mouse_Pointer.png");

	//Background

	FBoss_Floor.loadFromFile("Sprite/Stages/FBoss_Floor.png");
	FBoss_Background.loadFromFile("Sprite/Stages/FBoss_Background.png");
	SBoss_Floor.loadFromFile("Sprite/Stages/SBoss_Floor.png");
	SBoss_Background.loadFromFile("Sprite/Stages/SBoss_Background.png");
	TBoss_Floor.loadFromFile("Sprite/Stages/TBoss_Floor.png");
	TBoss_Background.loadFromFile("Sprite/Stages/TBoss_Background.png");
	FoBoss_Floor.loadFromFile("Sprite/Stages/FoBoss_Floor.png");
	FoBoss_Background.loadFromFile("Sprite/Stages/FoBoss_Background.png");
	FStage_Floor.loadFromFile("Sprite/Stages/FStage_Floor.png");
	FStage_Background.loadFromFile("Sprite/Stages/FStage_Background.png");
	FoStage_Background.loadFromFile("Sprite/Stages/FoStage_Background.png");
	FoStage_Floor.loadFromFile("Sprite/Stages/FoStage_Floor.png");
	TStage_Background.loadFromFile("Sprite/Stages/TStage_Background.png");
	TStage_Floor.loadFromFile("Sprite/Stages/TStage_Floor.png");
	SStage_Background.loadFromFile("Sprite/Stages/SStage_Background.png");
	SStage_Floor.loadFromFile("Sprite/Stages/SStage_Floor.png");
	Home_Texture.loadFromFile("Sprite/Environment/home.png");
	FlipHome_Texture.loadFromFile("Sprite/Environment/home_flipped.png");
	Scoreboard_Texture.loadFromFile("Sprite/Environment/Scoreboard.png");
	Name_Texture.loadFromFile("Sprite/Environment/Name.png");
	How_Texture.loadFromFile("Sprite/Environment/Howtoplay.png");
	Exit_Texture.loadFromFile("Sprite/Environment/Exit.png");

	/*Setting textures*/

	GUI_Background.setTexture(&GUI_Texture);
	Mouse_Cursor.setTexture(&Mouse_Texture);
	Mouse_Pointer.setTexture(Pointer_Texture);

	Empty_Bar.setSize(Vector2f(200, 20));
	Empty_Bar.setFillColor(Color::Black);
	HP_Bar.setFillColor(Color::Green);

	Shield_Effects.setSmooth(true);
	Shield.setTexture(Shield_Effects);
	Shield.setOrigin(Shield.getTextureRect().width/2.0f,Shield.getTextureRect().height/2.0f);
	Shield.setPosition(-100, -100);

	Player Player(&Player_Texture, 200, true, Vector2u(8, 16), 0.4f);
	Player.getBody().setPosition(500, 100);

	Home.setTexture(Home_Texture);
	Flipped_Home.setTexture(FlipHome_Texture);
	Home.scale((float)Window.getSize().x / Home_Texture.getSize().x, (float)Window.getSize().y / Home_Texture.getSize().y);
	Flipped_Home.scale((float)Window.getSize().x / FlipHome_Texture.getSize().x, (float)Window.getSize().y / FlipHome_Texture.getSize().y);
	Flipped_Home.setPosition(Home.getPosition().x+1366,0);

	Item Score_Soul(&Soul1, Vector2f(0.0f,0.0f), 0.0f, Vector2u(4, 1), 0.2f, 0.0f);
	Item Time_Shield(&Shield_Texture, Vector2f(0.0f, 0.0f), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
	Item Mouse_Menu(&MainM_Texture, Vector2f(-100, -100), 0.0f, Vector2u(4, 1), 0.2f, 0.0f);
	Item CharacterP(&Player_Texture, Vector2f(0.0f, 0.0f), 0.0f, Vector2u(8, 16), 0.2f, 0.0f);
	
	Mouse_Cursor.setSize(Vector2f(60, 60));
	Mouse_Cursor.setOrigin(Mouse_Cursor.getSize().x / 2, Mouse_Cursor.getSize().y / 2);
	Mouse_Cursor.setPosition(Vector2f(-100, -100));

	BMenu.setTexture(Button);
	BHow.setTexture(Button);
	BQuit.setTexture(Button);
	BScoreboard.setTexture(Button);
	HowB.setTexture(How_Texture);

	/*Text*/

	Text Title;
	Title.setFont(Title_Font);
	Title.setString("Dreadhunt");
	Title.setCharacterSize(90);
	Title.setFillColor(Color::Yellow);
	Title.setOutlineThickness(7);
	Title.setOutlineColor(Color::Black);
	Text Start_Text;
	Start_Text.setFont(Title_Font);
	Start_Text.setString("Start Game");
	Start_Text.setCharacterSize(30);
	Start_Text.setFillColor(Color::Black);
	Text Score_Text;
	Score_Text.setFont(Title_Font);
	Score_Text.setString("Scoreboard");
	Score_Text.setCharacterSize(30);
	Score_Text.setFillColor(Color::Black);
	Text How_Text;
	How_Text.setFont(Title_Font);
	How_Text.setString("How to play");
	How_Text.setCharacterSize(30);
	How_Text.setFillColor(Color::Black);
	Text Quit_Text;
	Quit_Text.setFont(Title_Font);
	Quit_Text.setString("Quit");
	Quit_Text.setCharacterSize(30);
	Quit_Text.setFillColor(Color::Black);
	Text Character_Text;
	Character_Text.setFont(Title_Font);
	Character_Text.setString("Character");
	Character_Text.setCharacterSize(90);
	Character_Text.setFillColor(Color::Black);
	Character_Text.setOutlineThickness(7);
	Character_Text.setOutlineColor(Color::White);
	Text Next_Text;
	Next_Text.setFont(Title_Font);
	Next_Text.setString("Press Enter");
	Next_Text.setCharacterSize(30);
	Next_Text.setFillColor(Color::White);
	Next_Text.setOutlineThickness(3);
	Text Name_Text;
	Name_Text.setFont(Title_Font);
	Name_Text.setString("Name");
	Name_Text.setCharacterSize(50);
	Name_Text.setFillColor(Color::White);
	Name_Text.setOutlineThickness(5);
	Name_Text.setOutlineColor(Color::Black);
	Texture Gold_Texture;
	Sprite Gold;
	Gold_Texture.loadFromFile("Sprite/Environment/Gold_Medal.png");
	Gold_Texture.setSmooth(true);
	Gold.setTexture(Gold_Texture);
	Gold.setScale(0.35, 0.35);
	Texture Silver_Texture;
	Sprite Silver;
	Silver_Texture.loadFromFile("Sprite/Environment/Silver_Medal.png");
	Silver_Texture.setSmooth(true);
	Silver.setTexture(Silver_Texture);
	Silver.setScale(0.35, 0.35);
	Texture Bronze_Texture;
	Sprite Bronze;
	Bronze_Texture.loadFromFile("Sprite/Environment/Bronze_Medal.png");
	Bronze_Texture.setSmooth(true);
	Bronze.setTexture(Bronze_Texture);
	Bronze.setScale(0.35, 0.35);
	Text Four;
	Four.setFont(Score_Font);
	Four.setString("4");
	Four.setFillColor(Color::White);
	Four.setOutlineThickness(2);
	Four.setOutlineColor(Color::Black);;
	Text Five;
	Five.setFont(Score_Font);
	Five.setString("5");
	Five.setFillColor(Color::White);
	Five.setOutlineThickness(2);
	Five.setOutlineColor(Color::Black);
	Text NS;
	NS.setFont(GUI_Font);
	NS.setString("Wongsakorn Taweesupmunkong 61010918");
	NS.setCharacterSize(20);
	NS.setFillColor(Color::White);
	NS.setOutlineThickness(2);
	NS.setOutlineColor(Color::Black);

	Sprite ScoreB;
	ScoreB.setTexture(Scoreboard_Texture);
	Sprite NameB;
	NameB.setTexture(Name_Texture);
	Sprite Exit_Button;
	Exit_Button.setTexture(Exit_Texture);

	Text_String Score(std::to_string(score), Score_Font, Vector2f(GUI_Place.getViewport().left + 645, GUI_Place.getViewport().top + 70), 25, Color::Yellow, 2, Color::Black);
	Text_String Health(std::to_string(Player.HP) + "/100", Score_Font, Vector2f(GUI_Place.getViewport().left + 310, GUI_Place.getViewport().top + 110), 20, Color::White, 1, Color::Black);
	Text_String Item_Time(std::to_string(10- (int)Count_Item),Score_Font,Vector2f(GUI_Place.getViewport().left + 645, GUI_Place.getViewport().top + 70),40,Color::Cyan,2,Color::Black);
	Text_String Shield_Time(std::to_string(10 - (int)Count_Item), Score_Font, Vector2f(GUI_Place.getViewport().left + 645, GUI_Place.getViewport().top + 70), 40, Color::Blue, 2, Color::Black);

	RectangleShape Background1, Background2, Background3, Background4, Background5, Background6, Background7, Background8;
	Window.setMouseCursorVisible(false);
	Background1.setSize(Vector2f(4000,700));
	Background2.setSize(Vector2f(1366, 645));
	Background3.setSize(Vector2f(4000, 700));
	Background4.setSize(Vector2f(1366, 645));
	Background5.setSize(Vector2f(4000, 700));
	Background6.setSize(Vector2f(1366, 645));
	Background7.setSize(Vector2f(4000, 700));
	Background8.setSize(Vector2f(1366, 645));
	
	srand(time(NULL));

	Clock clock;
	Main_Theme.play();

	while (Window.isOpen())
	{
		if (Player.HP <= 100 / 2)
		{
			HP_Bar.setFillColor(Color::Red);
		}
		else
		{
			HP_Bar.setFillColor(Color::Green);
		}
		Difference = clock.restart().asSeconds();
		if (Player.HP >= 100)
			Player.HP = 100;

		switch (screen)
		{
		case Screen::Menu:
		{
			Victory = false;
			isShieldON = false;
			Metal_Count = 0;
			Total_Item = 0, Count_Item = 0;
			Time_Spawn = 0;
			Total_Shield = 0, Count_Shield = 0;
			Stop = false;
			onetime = true;
			score = 0;
			Player.HP = 100;
			Shield.setPosition(-100, -100);
			Mouse_Cursor.setPosition(Vector2f(-100, -100));
			Mouse_Position = Window.mapPixelToCoords(Mouse::getPosition(Window));
			Event Window_Event;
			Camera.setViewport(FloatRect(0, 0, 1, 1));
			Camera.setSize(Window.getSize().x, Window.getSize().y);
			Camera.setCenter(Window.getSize().x/2, Window.getSize().y/2);
			BMenu.setPosition(Window.getSize().x / 2 - Button.getSize().x / 4, 360);
			BHow.setPosition(Window.getSize().x / 2 - Button.getSize().x / 4, 455);
			BScoreboard.setPosition(Window.getSize().x / 2 - Button.getSize().x / 4, 550);
			BQuit.setPosition(Window.getSize().x / 2 - Button.getSize().x / 4, 645);
			Title.setPosition(373,170);
			Start_Text.setPosition(569,379);
			Score_Text.setPosition(559,568);
			How_Text.setPosition(565, 473);
			Quit_Text.setPosition(643,663);
			NS.setPosition(0, 0);
			while (Window.pollEvent(Window_Event)) {}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				Click.play();
			}
			if (Mouse_Pointer.getGlobalBounds().intersects(BMenu.getGlobalBounds()))
			{
				BMenu.setTextureRect(IntRect(330, 0, 330, 84));
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					screen = Screen::Name;
					textUser.setString("");
				}
			}
			else
			{
				BMenu.setTextureRect(IntRect(0, 0, 330, 84));
			}
			if (Mouse_Pointer.getGlobalBounds().intersects(BScoreboard.getGlobalBounds()))
			{
				BScoreboard.setTextureRect(IntRect(330, 0, 330, 84));
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					screen = Screen::Scoreboard;
				}
			}
			else
			{
				BScoreboard.setTextureRect(IntRect(0, 0, 330, 84));
			}
			if (Mouse_Pointer.getGlobalBounds().intersects(BQuit.getGlobalBounds()))
			{
				BQuit.setTextureRect(IntRect(330, 0, 330, 84));
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					Main_Theme.stop();
					Window.close();
				}
			}
			else
			{
				BQuit.setTextureRect(IntRect(0, 0, 330, 84));
			}
			if (Mouse_Pointer.getGlobalBounds().intersects(BHow.getGlobalBounds()))
			{
				BHow.setTextureRect(IntRect(330, 0, 330, 84));
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					screen = Screen::How;
				}
			}
			else
			{
				BHow.setTextureRect(IntRect(0, 0, 330, 84));
			}
			if (Home.getPosition().x < -1366)
			{
				Home.setPosition(Flipped_Home.getPosition().x + 1366, 0);
			}
			if (Flipped_Home.getPosition().x < -1366)
			{
				Flipped_Home.setPosition(Home.getPosition().x + 1366, 0);
			}
			Home.move(-100 * Difference, 0);
			Flipped_Home.move(-100 * Difference, 0);

			Window.clear();
			Window.setView(Camera);
			Window.draw(Home);
			Window.draw(Flipped_Home);
			Window.draw(BMenu);
			Window.draw(BHow);
			Window.draw(BScoreboard);
			Window.draw(BQuit);
			Window.draw(Score_Text);
			Window.draw(Start_Text);
			Window.draw(How_Text);
			Window.draw(Title);
			Window.draw(Quit_Text);
			Window.draw(NS);
			Window.draw(Mouse_Pointer);
			Mouse_Menu.Item_Projectiles.setPos(Mouse_Position);
			Mouse_Pointer.setPosition(Vector2f(Mouse_Menu.Item_Projectiles.Get_Body().getPosition().x - Mouse_Menu.Body().getGlobalBounds().width / 2 / 4, Mouse_Menu.Item_Projectiles.Get_Body().getPosition().y - Mouse_Menu.Body().getTextureRect().height / 2));
			Mouse_Menu.Update(Difference,Window);
			Window.draw(Mouse_Cursor);
			Window.display();
			break;
		}
		case Screen::Scoreboard:
		{
			Score_Text.setPosition(Vector2f(567,52));
			Mouse_Position = Window.mapPixelToCoords(Mouse::getPosition(Window));
			Event Window_Event;
			Mouse_Cursor.setPosition(Vector2f(-100, -100));
			Shield.setPosition(-100, -100);
			Camera.setViewport(FloatRect(0, 0, 1, 1));
			Camera.setSize(Window.getSize().x, Window.getSize().y);
			Camera.setCenter(Window.getSize().x / 2, Window.getSize().y / 2);
			ScoreB.setPosition(305,35);
			Exit_Button.setPosition(25, 25);
			while (Window.pollEvent(Window_Event)) {}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				screen = Screen::Menu;
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				Click.play();
			}
			
			if (Home.getPosition().x < -1366)
			{
				Home.setPosition(Flipped_Home.getPosition().x + 1366, 0);
			}
			if (Flipped_Home.getPosition().x < -1366)
			{
				Flipped_Home.setPosition(Home.getPosition().x + 1366, 0);
			}
			if (Mouse_Pointer.getGlobalBounds().intersects(Exit_Button.getGlobalBounds()))
			{
				Exit_Button.setTextureRect(IntRect(92, 0, 92, 96));
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					screen = Screen::Menu;
				}
			}
			else
			{
				Exit_Button.setTextureRect(IntRect(0, 0, 92, 96));
			}
			Home.move(-100 * Difference, 0);
			Flipped_Home.move(-100 * Difference, 0);

			Window.clear();

			scoreFile.open("Sprite/Text/Highscore.txt");
			scoreFile >> scoreRank[1] >> scoreRank[2] >> scoreRank[3] >> scoreRank[4] >> scoreRank[5];
			scoreFile.close();

			userFile.open("Sprite/Text/Username.txt");
			userFile >> user[1] >> user[2] >> user[3] >> user[4] >> user[5];
			userFile.close();

			std::stringstream first;
			first << scoreRank[1];
			std::stringstream second;
			second << scoreRank[2];
			std::stringstream third;
			third << scoreRank[3];
			std::stringstream fourth;
			fourth << scoreRank[4];
			std::stringstream fifth;
			fifth << scoreRank[5];

			Text firstscore(first.str(), Score_Font, 30);
			Text secondscore(second.str(), Score_Font, 30);
			Text thirdscore(third.str(), Score_Font, 30);
			Text fourthscore(fourth.str(), Score_Font, 30);
			Text fifthscore(fifth.str(), Score_Font, 30);

			firstscore.setFillColor(Color::Yellow);
			secondscore.setFillColor(Color::Yellow);
			thirdscore.setFillColor(Color::Yellow);
			fourthscore.setFillColor(Color::Yellow);
			fifthscore.setFillColor(Color::Yellow);
			firstscore.setOutlineColor(Color::Black);
			secondscore.setOutlineColor(Color::Black);
			thirdscore.setOutlineColor(Color::Black);
			fourthscore.setOutlineColor(Color::Black);
			fifthscore.setOutlineThickness(2);
			firstscore.setOutlineThickness(2);
			secondscore.setOutlineThickness(2);
			thirdscore.setOutlineThickness(2);
			fourthscore.setOutlineThickness(2);
			fifthscore.setOutlineThickness(2);

			Text firstuser(user[1], Score_Font, 30);
			Text seconduser(user[2], Score_Font, 30);
			Text thirduser(user[3], Score_Font, 30);
			Text fourthuser(user[4], Score_Font, 30);
			Text fifthuser(user[5], Score_Font, 30);

			firstuser.setFillColor(Brown);
			seconduser.setFillColor(Brown);
			thirduser.setFillColor(Brown);
			fourthuser.setFillColor(Brown);
			fifthuser.setFillColor(Brown);
			firstuser.setOutlineColor(Color::Black);
			seconduser.setOutlineColor(Color::Black);
			thirduser.setOutlineColor(Color::Black);
			fourthuser.setOutlineColor(Color::Black);
			fifthuser.setOutlineThickness(2);
			firstuser.setOutlineThickness(2);
			seconduser.setOutlineThickness(2);
			thirduser.setOutlineThickness(2);
			fourthuser.setOutlineThickness(2);
			fifthuser.setOutlineThickness(2);

			firstscore.setPosition(ScoreB.getPosition().x + 570, ScoreB.getPosition().y + 200);
			secondscore.setPosition(ScoreB.getPosition().x + 570, ScoreB.getPosition().y + 260);
			thirdscore.setPosition(ScoreB.getPosition().x + 570, ScoreB.getPosition().y + 320);
			fourthscore.setPosition(ScoreB.getPosition().x + 570, ScoreB.getPosition().y + 380);
			fifthscore.setPosition(ScoreB.getPosition().x + 570, ScoreB.getPosition().y + 440);
			Gold.setPosition(ScoreB.getPosition().x + 137, ScoreB.getPosition().y+193);
			Silver.setPosition(ScoreB.getPosition().x + 137, ScoreB.getPosition().y + 253);
			Bronze.setPosition(ScoreB.getPosition().x + 137, ScoreB.getPosition().y + 313);			
			Four.setPosition(ScoreB.getPosition().x + 150, ScoreB.getPosition().y+380);
			Five.setPosition(ScoreB.getPosition().x + 150, ScoreB.getPosition().y+440);

			firstuser.setPosition(ScoreB.getPosition().x + 200, ScoreB.getPosition().y + 200);
			seconduser.setPosition(ScoreB.getPosition().x + 200, ScoreB.getPosition().y + 260);
			thirduser.setPosition(ScoreB.getPosition().x + 200, ScoreB.getPosition().y + 320);
			fourthuser.setPosition(ScoreB.getPosition().x + 200, ScoreB.getPosition().y + 380);
			fifthuser.setPosition(ScoreB.getPosition().x + 200, ScoreB.getPosition().y + 440);
			Window.setView(Camera);
			Window.draw(Home);
			Window.draw(Flipped_Home);
			Window.draw(ScoreB);
			Window.draw(Exit_Button);
			Window.draw(firstscore);
			Window.draw(secondscore);
			Window.draw(thirdscore);
			Window.draw(fourthscore);
			Window.draw(fifthscore);
			Window.draw(firstuser);
			Window.draw(seconduser);
			Window.draw(thirduser);
			Window.draw(fourthuser);
			Window.draw(fifthuser);
			Window.draw(Gold);
			Window.draw(Silver);
			Window.draw(Bronze);
			Window.draw(Four);
			Window.draw(Five);
			Window.draw(Score_Text);
			Window.draw(Mouse_Pointer);
			Mouse_Menu.Item_Projectiles.setPos(Mouse_Position);
			Mouse_Pointer.setPosition(Vector2f(Mouse_Menu.Item_Projectiles.Get_Body().getPosition().x - Mouse_Menu.Body().getGlobalBounds().width / 2 / 4, Mouse_Menu.Item_Projectiles.Get_Body().getPosition().y - Mouse_Menu.Body().getTextureRect().height / 2));
			Mouse_Menu.Update(Difference, Window);
			Window.draw(Mouse_Cursor);
			Window.display();
			break;
		}
		case Screen::Name:
		{
			Mouse_Position = Window.mapPixelToCoords(Mouse::getPosition(Window));
			Event Window_Event;
			Camera.setViewport(FloatRect(0, 0, 1, 1));
			Camera.setSize(Window.getSize().x, Window.getSize().y);
			Camera.setCenter(Window.getSize().x / 2, Window.getSize().y / 2);
			Character_Text.setPosition(350,20);
			Next_Text.setPosition(1020, 625);
			Name_Text.setPosition(650,250);
			CharacterP.Item_Projectiles.Get_Body().setPosition(300, 430);
			CharacterP.Item_Projectiles.Get_Body().setScale(4.5,4.5);
			while (Window.pollEvent(Window_Event))
			{				
					if(Keyboard::isKeyPressed(Keyboard::Enter))
					{
						onetime = true;
						screen = Screen::First_Stage;
					}
					switch (Window_Event.type)
					{
					case sf::Event::TextEntered:
					
						if (Window_Event.type == sf::Event::TextEntered)
						{
							Key_Pressed.play();
							if ((Window_Event.text.unicode <= 132 && Window_Event.text.unicode >= 65) || (Window_Event.text.unicode <= 122 && Window_Event.text.unicode >= 97) || (Window_Event.text.unicode <= 57 && Window_Event.text.unicode >= 48) && Window_Event.text.unicode != 8)
							{
								str += static_cast<char>(Window_Event.text.unicode);
								textUser.setString(str);
							}
						}
						if ((Window_Event.text.unicode == '\b' || str.getSize() == 15) && str.getSize() != 0)
						{
							str.erase(str.getSize() - 1, 1);
							textUser.setString(str);
						}
						break;
					
				}
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				Click.play();
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			{
				screen = Screen::Menu;
			}

			Window.clear();
			
			Window.setView(Camera);
			Window.draw(NameB);
			Window.draw(Next_Text);
			Window.draw(Name_Text);
			Window.draw(Character_Text);
			CharacterP.Update(Difference, Window);
			textUser.setCharacterSize(50);
			textUser.setFillColor(Color::Black);
			textUser.setPosition(Window.getSize().x / 2, Window.getSize().y / 2);
			Window.draw(textUser);
			Window.draw(Mouse_Pointer);
			Mouse_Menu.Item_Projectiles.setPos(Mouse_Position);
			Mouse_Pointer.setPosition(Vector2f(Mouse_Menu.Item_Projectiles.Get_Body().getPosition().x - Mouse_Menu.Body().getGlobalBounds().width / 2 / 4, Mouse_Menu.Item_Projectiles.Get_Body().getPosition().y - Mouse_Menu.Body().getTextureRect().height / 2));
			Mouse_Menu.Update(Difference, Window);
			Window.draw(Mouse_Cursor);
			Window.display();
			break;
		}
		case Screen::How:
		{
			Mouse_Position = Window.mapPixelToCoords(Mouse::getPosition(Window));
			Event Window_Event;
			Camera.setViewport(FloatRect(0, 0, 1, 1));
			Camera.setSize(Window.getSize().x, Window.getSize().y);
			Camera.setCenter(Window.getSize().x / 2, Window.getSize().y / 2);
			HowB.setPosition(0,0);
			Exit_Button.setPosition(25, 25);
			while (Window.pollEvent(Window_Event)) {}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				Click.play();
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			{
				screen = Screen::Menu;
			}
			if (Mouse_Pointer.getGlobalBounds().intersects(Exit_Button.getGlobalBounds()))
			{
				Exit_Button.setTextureRect(IntRect(92, 0, 92, 96));
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					screen = Screen::Menu;
				}
			}
			else
			{
				Exit_Button.setTextureRect(IntRect(0, 0, 92, 96));
			}
			Window.clear();
			Window.setView(Camera);
			Window.draw(HowB);
			Window.draw(Exit_Button);
			Window.draw(Mouse_Pointer);
			Mouse_Menu.Item_Projectiles.setPos(Mouse_Position);
			Mouse_Pointer.setPosition(Vector2f(Mouse_Menu.Item_Projectiles.Get_Body().getPosition().x - Mouse_Menu.Body().getGlobalBounds().width / 2 / 4, Mouse_Menu.Item_Projectiles.Get_Body().getPosition().y - Mouse_Menu.Body().getTextureRect().height / 2));
			Mouse_Menu.Update(Difference, Window);
			Window.draw(Mouse_Cursor);
			Window.display();
			break;
		}
		case Screen::Third_Stage:
		{
			if (Player.HP <= 0)
			{
				Die.play();
				TStage.stop();
				Main_Theme.play();
				screen = Screen::Scoreboard;
				Player.HP = 0;
				scoreRank[0] = score;
				int i, j, temp;
				user[0] = str;
				scoreFile.open("Sprite/Text/Highscore.txt");
				scoreFile >> scoreRank[1] >> scoreRank[2] >> scoreRank[3] >> scoreRank[4] >> scoreRank[5];
				scoreFile.close();

				userFile.open("Sprite/Text/Username.txt");
				userFile >> user[1] >> user[2] >> user[3] >> user[4] >> user[5];
				userFile.close();
				std::string strtemp;
				for (i = 0; i < 6; i++)
				{
					for (j = i + 1; j < 6; j++)
					{
						if (scoreRank[i] < scoreRank[j])
						{
							temp = scoreRank[i];
							scoreRank[i] = scoreRank[j];
							scoreRank[j] = temp;
							strtemp = user[i];
							user[i] = user[j];
							user[j] = strtemp;
						}
					}
				}
				writeUser.open("Sprite/Text/Username.txt");
				for (i = 0; i < 5; i++)
				{
					writeUser << user[i] << std::endl;
				}
				writeUser.close();

				writeScore.open("Sprite/Text/Highscore.txt");
				for (i = 0; i < 5; i++)
				{
					writeScore << scoreRank[i] << std::endl;
				}
				writeScore.close();
			}
			Event Window_Event;
			Total_Item += Difference;
			Time_Spawn += Difference;
			Total_Shield += Difference;

			/*Default_View*/

			Camera.setViewport(FloatRect(0, 0, 1, 625.0 / Window.getSize().y));
			Camera.setSize(Window.getSize().x, Window.getSize().y* 625.0 / Window.getSize().y);

			/*Character_View*/

			Character.setViewport(FloatRect(25.0 / Window.getSize().x, 645.0 / Window.getSize().y, 150.0 / Window.getSize().x, 103.0 / Window.getSize().y));
			Character.setSize(Window.getSize().x*150.0 / Window.getSize().x, Window.getSize().y*103.0 / Window.getSize().y);
			Character.setCenter(Player.GetPosition().x, Player.GetPosition().y + 15);

			/*GUI_View*/

			GUI_Place.setViewport(FloatRect(0, 625.0 / Window.getSize().y, 1, 143.0 / Window.getSize().y));
			GUI_Place.setSize(Window.getSize().x, Window.getSize().y*143.0 / Window.getSize().y);
			GUI_Place.setCenter(GUI_Place.getSize().x / 2, GUI_Place.getSize().y / 2);

			GUI_Background.setSize(GUI_Place.getSize());
			Empty_Bar.setPosition(Vector2f(GUI_Place.getViewport().left + 250, GUI_Place.getViewport().top + 75));
			GUI_Background.setPosition(GUI_Place.getViewport().left, GUI_Place.getViewport().top);
			HP_Bar.setPosition(Vector2f(GUI_Place.getViewport().left + 250, GUI_Place.getViewport().top + 75));
			HP_Bar.setSize(Vector2f(Player.HP*Empty_Bar.getSize().x / 100.0, 20));

			textUser.setPosition(Vector2f(GUI_Place.getViewport().left + 310, GUI_Place.getViewport().top + 20));
			textUser.setFillColor(Color::Black);
			textUser.setCharacterSize(25);
			if (onetime)
			{
				GUI.clear();
				Platforms.clear();
				bullet.clear();
				bulletVec.clear();
				Metalbeing_Body.clear();
				Items.clear();
				Enemy_Score.clear();
				Time_Items.clear();
				Flowmon_Ball.clear();
				Flowmon_Body.clear();
				Foulling_Body.clear();
				Gaspow_Body.clear();
				Gaspow_Ball.clear();
				Warpgate_Body.clear();

				Floor NewPlatforms(&TStage_Floor, Vector2f(0, 0));
				Platforms.push_back(NewPlatforms);
				Player.getBody().setPosition(200, -10);
				WarpGate Warpgate1(&Warpgate_Texture,Vector2f(3872,241),Screen::Third_Boss,Vector2u(20,1),0.2f );
				Warpgate_Body.push_back(Warpgate1);
				Metalbeing Metalbeing1(&Metalbeing_Texture, Vector2u(6, 6), 0.2f, Vector2f(174,50), Vector2f(100, 100));
				Metalbeing_Body.push_back(Metalbeing1);
				Metalbeing Metalbeing2(&Metalbeing_Texture, Vector2u(6, 6), 0.2f, Vector2f(2545, 410), Vector2f(20, 500));
				Metalbeing_Body.push_back(Metalbeing2);
				Flowmon Flowmon1(&Flowmon_Texture,Vector2u(14,8),0.2f,Vector2f(1686,0));
				Flowmon_Body.push_back(Flowmon1);
				Flowmon Flowmon2(&Flowmon_Texture, Vector2u(14, 8), 0.2f, Vector2f(3381,80));
				Flowmon_Body.push_back(Flowmon2);
				Foulling Foulling1(&Foulling_Texture, Vector2u(4, 6), 0.2f, Vector2f(958, 494), Vector2f(80, 350));
				Foulling_Body.push_back(Foulling1);
				Foulling Foulling2(&Foulling_Texture, Vector2u(4, 6), 0.2f, Vector2f(1490, 425), Vector2f(0, 700));
				Foulling_Body.push_back(Foulling2);
				Gaspow Gaspow1(&Gaspow_Texture,Vector2u(6,4),0.2f,Vector2f(2121,-200));
				Gaspow_Body.push_back(Gaspow1);
				Text_String GUI1("Name", GUI_Font, Vector2f(GUI_Place.getViewport().left + 200, GUI_Place.getViewport().top + 20), 25, Color::White, 2, Color::Black);
				GUI.push_back(GUI1);
				Text_String GUI2("HP", GUI_Font, Vector2f(GUI_Place.getViewport().left + 200, GUI_Place.getViewport().top + 70), 25, Color::Red, 2, Color::Black);
				GUI.push_back(GUI2);
				Text_String GUI3("Score", GUI_Font, Vector2f(GUI_Place.getViewport().left + 500, GUI_Place.getViewport().top + 70), 25, Color::Magenta, 2, Color::Black);
				GUI.push_back(GUI3);
				Background5.setTexture(&TStage_Background);
				TStage.play();
				SBoss.stop();
				Background5.setPosition(0, 0);
				Camera.setCenter(Camera.getSize().x/2,645/2);
				onetime = false;
			}
			if (Player.GetPosition().x >= Background5.getPosition().x + Camera.getSize().x / 2 && Player.GetPosition().x <= Background5.getPosition().x + Background5.getSize().x - Camera.getSize().x / 2)
				Camera.setCenter(Player.GetPosition().x, 645 / 2);

			/*Window Event*/
			while (Window.pollEvent(Window_Event)) {}
			if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			{
				Main_Theme.play();
				TStage.stop();
				screen = Screen::Menu;
				scoreRank[0] = score;
				int i, j, temp;
				user[0] = str;
				scoreFile.open("Sprite/Text/Highscore.txt");
				scoreFile >> scoreRank[1] >> scoreRank[2] >> scoreRank[3] >> scoreRank[4] >> scoreRank[5];
				scoreFile.close();

				userFile.open("Sprite/Text/Username.txt");
				userFile >> user[1] >> user[2] >> user[3] >> user[4] >> user[5];
				userFile.close();
				std::string strtemp;
				for (i = 0; i < 6; i++)
				{
					for (j = i + 1; j < 6; j++)
					{
						if (scoreRank[i] < scoreRank[j])
						{
							temp = scoreRank[i];
							scoreRank[i] = scoreRank[j];
							scoreRank[j] = temp;
							strtemp = user[i];
							user[i] = user[j];
							user[j] = strtemp;
						}
					}
				}
				writeUser.open("Sprite/Text/Username.txt");
				for (i = 0; i < 5; i++)
				{
					writeUser << user[i] << std::endl;
				}
				writeUser.close();

				writeScore.open("Sprite/Text/Highscore.txt");
				for (i = 0; i < 5; i++)
				{
					writeScore << scoreRank[i] << std::endl;
				}
				writeScore.close();
			}

			/*Bullet_Collision*/

			for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Metalbeing_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Metalbeing_Body[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Metalbeing_Body[j].isDying)
						{
							Metalbeing_Body[j].Metalbeing_Health -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Metalbeing_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Metalbeing_Body[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Metalbeing_Body[j].isDying)
						{
							Metalbeing_Body[j].Metalbeing_Health -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Foulling_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Foulling_Body[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Foulling_Body[j].isDying)
						{
							Foulling_Body[j].Foulling_Health -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Foulling_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Foulling_Body[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Foulling_Body[j].isDying)
						{
							Foulling_Body[j].Foulling_Health -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Gaspow_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Gaspow_Body[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Gaspow_Body[j].isDying)
						{
							Gaspow_Body[j].Gaspow_Health -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Gaspow_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Gaspow_Body[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Gaspow_Body[j].isDying)
						{
							Gaspow_Body[j].Gaspow_Health -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Flowmon_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Flowmon_Body[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Flowmon_Body[j].isDying)
						{
							Flowmon_Body[j].Flowmon_Health -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Flowmon_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Flowmon_Body[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Flowmon_Body[j].isDying)
						{
							Flowmon_Body[j].Flowmon_Health -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}

			/*Platform_Collision*/

			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < bulletVec.size(); j++)
				{
					if (Collision::PixelPerfectTest(bulletVec[j].Get_Body(), Platforms[i].Body(), 0) || bulletVec[j].Get_Body().getPosition().x - abs(bulletVec[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || bulletVec[j].Get_Body().getPosition().x + abs(bulletVec[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || bulletVec[j].Get_Body().getPosition().y + abs(bulletVec[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || bulletVec[j].Get_Body().getPosition().y - abs(bulletVec[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						if (!Player.isWave)
						{
							bulletVec.erase(bulletVec.begin() + j);
							break;
						}
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < bullet.size(); j++)
				{
					if (Collision::PixelPerfectTest(bullet[j].Get_Body(), Platforms[i].Body(), 0) || bullet[j].Get_Body().getPosition().x - abs(bullet[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || bullet[j].Get_Body().getPosition().x + abs(bullet[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || bullet[j].Get_Body().getPosition().y + abs(bullet[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || bullet[j].Get_Body().getPosition().y - abs(bullet[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						bullet.erase(bullet.begin() + j);
						break;
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Items.size(); j++)
				{
					if (Collision::PixelPerfectTest(Items[j].Item_Projectiles.Get_Body(), Platforms[i].Body(), 0))
					{
						Items[j].Item_Projectiles.isMoving = false;
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Flowmon_Body.size(); j++)
				{
					if (!Collision::PixelPerfectTest(Flowmon_Body[j].Get_Body(), Platforms[i].Body(), 0))
					{
						Flowmon_Body[j].Get_Body().move(0, 98.1*Difference);
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Flowmon_Ball.size(); j++)
				{
					if (Collision::PixelPerfectTest(Flowmon_Ball[j].Get_Body(), Platforms[i].Body(), 0) || Flowmon_Ball[j].Get_Body().getPosition().x - abs(Flowmon_Ball[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || Flowmon_Ball[j].Get_Body().getPosition().x + abs(Flowmon_Ball[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || Flowmon_Ball[j].Get_Body().getPosition().y + abs(Flowmon_Ball[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || Flowmon_Ball[j].Get_Body().getPosition().y - abs(Flowmon_Ball[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						Flowmon_Ball.erase(Flowmon_Ball.begin() + j);
						break;
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Gaspow_Body.size(); j++)
				{
					if (!Collision::PixelPerfectTest(Gaspow_Body[j].Get_Body(), Platforms[i].Body(), 0))
					{
						Gaspow_Body[j].Get_Body().move(0, 98.1*Difference);
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Gaspow_Ball.size(); j++)
				{
					if (Collision::PixelPerfectTest(Gaspow_Ball[j].Get_Body(), Platforms[i].Body(), 0) || Gaspow_Ball[j].Get_Body().getPosition().x - abs(Gaspow_Ball[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || Gaspow_Ball[j].Get_Body().getPosition().x + abs(Gaspow_Ball[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || Gaspow_Ball[j].Get_Body().getPosition().y + abs(Gaspow_Ball[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || Gaspow_Ball[j].Get_Body().getPosition().y - abs(Gaspow_Ball[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						Gaspow_Ball.erase(Gaspow_Ball.begin() + j);
						break;
					}
				}
			}

			/*Player Collision*/

			for (int i = 0; i < Items.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Items[i].Item_Projectiles.Get_Body(), 0))
				{
					if (!Player.isDying)
					{
						if (Items[i].isArrow)
						{
							Player.isWave = false;
							Player.isDirect = false;
							Player.isLaser = false;
							Player.isLob = false;
							Player.isArrow = true;
							Time_Items.clear();
							ItemSound.play();
							Count_Item = Total_Item;
							Item NewItems(&Arrow_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isLob)
						{
							ItemSound.play();
							Player.isWave = false;
							Player.isDirect = false;
							Player.isLaser = false;
							Player.isLob = true;
							Player.isArrow = false;
							Count_Item = Total_Item;
							Time_Items.clear();
							Item NewItems(&Lob_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isWave)
						{
							ItemSound.play();
							Player.isWave = true;
							Player.isDirect = false;
							Player.isLaser = false;
							Player.isLob = false;
							Player.isArrow = false;
							Time_Items.clear();
							Count_Item = Total_Item;
							Item NewItems(&Wave_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isLaser)
						{
							ItemSound.play();
							Player.isWave = false;
							Player.isDirect = false;
							Player.isLaser = true;
							Player.isLob = false;
							Player.isArrow = false;
							Time_Items.clear();
							Count_Item = Total_Item;
							Item NewItems(&Laser_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isShield) { isShieldON = true; Count_Shield = Total_Shield; }
						else if (Items[i].isFood) { Player.HP += Items[i].Health; Munch.play(); }
						else {SoulSound.play(); }
						Items[i].Item_Visible = false;
						score += Items[i].Score;
						Items.erase(Items.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < Flowmon_Ball.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Flowmon_Ball[i].Get_Body(), 0))
				{
					if (!Player.isHurting && !Player.isDying)
					{
						Player.HP -= Flowmon_Ball[i].Damage;
						Player.Player_Animation.Visible = true;
						Player.isHurting = true;
						Player.Player_Animation.Current_Image.x = 0;
						Flowmon_Ball.erase(Flowmon_Ball.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < Flowmon_Ball.size(); i++)
			{
				if (Collision::PixelPerfectTest(Flowmon_Ball[i].Get_Body(), Shield, 0))
				{
					Flowmon_Ball.erase(Flowmon_Ball.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Flowmon_Body.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Flowmon_Body[i].Get_Body(), 0) && !Player.isHurting && !Player.isDying)
				{
					Player.HP -= 5;
					Player.isHurting = true;
					Player.Player_Animation.Visible = true;
					Player.Player_Animation.Current_Image.x = 0;
				}
			}
			for (int i = 0; i < Gaspow_Ball.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Gaspow_Ball[i].Get_Body(), 0))
				{
					if (!Player.isHurting && !Player.isDying)
					{
						Player.HP -= Gaspow_Ball[i].Damage;
						Player.Player_Animation.Visible = true;
						Player.isHurting = true;
						Player.Player_Animation.Current_Image.x = 0;
						Gaspow_Ball.erase(Gaspow_Ball.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < Gaspow_Ball.size(); i++)
			{
				if (Collision::PixelPerfectTest(Gaspow_Ball[i].Get_Body(), Shield, 0))
				{
					Gaspow_Ball.erase(Gaspow_Ball.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Gaspow_Body.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Gaspow_Body[i].Get_Body(), 0) && !Player.isHurting && !Player.isDying)
				{
					Player.HP -= 5;
					Player.isHurting = true;
					Player.Player_Animation.Visible = true;
					Player.Player_Animation.Current_Image.x = 0;
				}
			}
			for (int i = 0; i < Foulling_Body.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Foulling_Body[i].Get_Body(), 0) && !Player.isHurting && !Player.isDying)
				{
					Player.HP -= 5;
					Player.isHurting = true;
					Player.Player_Animation.Visible = true;
					Player.Player_Animation.Current_Image.x = 0;
				}
			}
			for (int i = 0; i < Warpgate_Body.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Warpgate_Body[i].Get_Body()) && !Player.isHurting && !Player.isDying)
				{
					if (Keyboard::isKeyPressed(Keyboard::Space))
					{
						screen = Warpgate_Body[i].to;
						onetime = true;
						break;
					}
				}
			}

			/*Items*/

			for (int i = 0; i < Metalbeing_Body.size(); i++)
			{
				if (!Metalbeing_Body[i].Metalbeing_Visible)
				{
					num = rand() % 5;
					if (num == 0)
					{
						Item newItem(&Shield_Texture, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isShield = true;
						newItem.Item_Projectiles.Get_Body().setScale(2,2);
						Items.push_back(newItem);
					}
					else if (num == 1)
					{
						Item newItem(&Arrow_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isArrow = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					else if (num == 2)
					{
						Item newItem(&Laser_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isLaser = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					else if (num == 3)
					{
						Item newItem(&Wave_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isWave = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05,1.05);
						Items.push_back(newItem);
					}
					else if (num == 4)
					{
						Item newItem(&Lob_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isLob = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					Metalbeing_Body.erase(Metalbeing_Body.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Flowmon_Body.size(); i++)
			{
				if (!Flowmon_Body[i].Flowmon_Visible)
				{
					score += Flowmon_Body[i].Score;
					Text_String newScore(std::to_string(Flowmon_Body[i].Score), Score_Font, Vector2f(Flowmon_Body[i].Get_Body().getPosition().x, Flowmon_Body[i].Get_Body().getPosition().y - 20), 20, Color::Yellow, 1, Color::Black);
					Enemy_Score.push_back(newScore);
					num = rand() % 12 + 1;
					if (num >= 8)
					{
						Item newItem(&Apple, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 15);
						newItem.Item_Projectiles.setPos(Vector2f(Flowmon_Body[i].Get_Body().getPosition().x, Flowmon_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 25;
						newItem.Item_Projectiles.Get_Body().setScale(2,2);
						Items.push_back(newItem);
					}
					else if (num >= 6)
					{
						Item newItem(&Green_Apple, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 20);
						newItem.Item_Projectiles.setPos(Vector2f(Flowmon_Body[i].Get_Body().getPosition().x, Flowmon_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 10;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					else
					{
						Item newItem(&Ramen, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 10);
						newItem.Item_Projectiles.setPos(Vector2f(Flowmon_Body[i].Get_Body().getPosition().x, Flowmon_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 30;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					num = rand() % 5+1;
					for (int j = 1; j <= num; j++)
					{
						Item newItem(&Soul, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(4, 1), 0.2f, 5);
						newItem.Item_Projectiles.setPos(Vector2f(Flowmon_Body[i].Get_Body().getPosition().x, Flowmon_Body[i].Get_Body().getPosition().y - 20));
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					Flowmon_Body.erase(Flowmon_Body.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Gaspow_Body.size(); i++)
			{
				if (!Gaspow_Body[i].Gaspow_Visible)
				{
					score += Gaspow_Body[i].Score;
					Text_String newScore(std::to_string(Gaspow_Body[i].Score), Score_Font, Vector2f(Gaspow_Body[i].Get_Body().getPosition().x, Gaspow_Body[i].Get_Body().getPosition().y - 20), 20, Color::Yellow, 1, Color::Black);
					Enemy_Score.push_back(newScore);
					num = rand() % 12 + 1;
					if (num >= 8)
					{
						Item newItem(&Corn_Stick, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 15);
						newItem.Item_Projectiles.setPos(Vector2f(Gaspow_Body[i].Get_Body().getPosition().x, Gaspow_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 25;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					else if (num >= 6)
					{
						Item newItem(&Chicken, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 20);
						newItem.Item_Projectiles.setPos(Vector2f(Gaspow_Body[i].Get_Body().getPosition().x, Gaspow_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 10;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					else
					{
						Item newItem(&Lemon, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 10);
						newItem.Item_Projectiles.setPos(Vector2f(Gaspow_Body[i].Get_Body().getPosition().x, Gaspow_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 30;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					num = rand() % 5 + 1;
					for (int j = 1; j <= num; j++)
					{
						Item newItem(&Soul, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(4, 1), 0.2f, 5);
						newItem.Item_Projectiles.setPos(Vector2f(Gaspow_Body[i].Get_Body().getPosition().x, Gaspow_Body[i].Get_Body().getPosition().y - 20));
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					Gaspow_Body.erase(Gaspow_Body.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Foulling_Body.size(); i++)
			{
				if (!Foulling_Body[i].Foulling_Visible)
				{
					score += Foulling_Body[i].Score;
					Text_String newScore(std::to_string(Foulling_Body[i].Score), Score_Font, Vector2f(Foulling_Body[i].Get_Body().getPosition().x, Foulling_Body[i].Get_Body().getPosition().y - 20), 20, Color::Yellow, 1, Color::Black);
					Enemy_Score.push_back(newScore);
					num = rand() % 15 + 1;
					for (int j = 1; j <= num; j++)
					{
						Item newItem(&Soul, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(4, 1), 0.2f, 5);
						newItem.Item_Projectiles.setPos(Vector2f(Foulling_Body[i].Get_Body().getPosition().x, Foulling_Body[i].Get_Body().getPosition().y - 20));
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					Foulling_Body.erase(Foulling_Body.begin() + i);
					break;
				}
			}

			/*Items Active*/
			if (isShieldON)
			{
				Shield.setPosition(Player.GetPosition());
			}
			else
			{
				Shield.setPosition(-100, -100);
			}
			if (Total_Item - Count_Item >= 10.0f)
			{
				Player.isArrow = false;
				Player.isLaser = false;
				Player.isLob = false;
				Player.isWave = false;
				Player.isDirect = true;
				Total_Item = 0;
				Count_Item = 0;
				Time_Items.clear();
			}
			if (Total_Shield - Count_Shield >= 10.0f)
			{
				isShieldON = false;
				Total_Shield = 0;
				Count_Shield = 0;
			}

			
			Window.clear();

			/*GUI_View*/

			Window.setView(GUI_Place);
			Window.draw(GUI_Background);
			for (int i = 0; i < GUI.size(); i++)
			{
				GUI[i].Draw(Window);
			}
			Score.Update_Text(std::to_string(score));
			Health.Update_Text(std::to_string(Player.HP) + "/100");
			Window.draw(Empty_Bar);
			Window.draw(HP_Bar);
			Score.Draw(Window);
			Health.Draw(Window);
			Score_Soul.Item_Projectiles.setPos(Vector2f(GUI_Place.getViewport().left + 620.0f, GUI_Place.getViewport().top + 80.0f));
			Score_Soul.Update(Difference, Window);
			if (Player.isArrow || Player.isLob || Player.isLaser || Player.isWave)
			{
				for (int i = 0; i < Time_Items.size(); i++)
				{
					Time_Items[i].Item_Projectiles.setPos(Vector2f(GUI_Place.getViewport().left + 1200, GUI_Place.getViewport().top + 42));
					Time_Items[i].Update(Difference, Window);
				}
				Item_Time.Text_Body.setPosition(Vector2f(GUI_Place.getViewport().left + 1250, GUI_Place.getViewport().top + 20));
				Item_Time.Update_Text(std::to_string(10 - abs((int)Count_Item - (int)Total_Item)));
				Window.draw(Item_Time.Text_Body);
			}
			if (isShieldON)
			{
				Time_Shield.Item_Projectiles.Get_Body().setScale(2, 2);
				Time_Shield.Item_Projectiles.setPos(Vector2f(GUI_Place.getViewport().left + 1200, GUI_Place.getViewport().top + 110));
				Time_Shield.Update(Difference, Window);
				Shield_Time.Text_Body.setPosition(Vector2f(GUI_Place.getViewport().left + 1250, GUI_Place.getViewport().top + 85));
				Shield_Time.Update_Text(std::to_string(10 - abs((int)Count_Shield - (int)Total_Shield)));
				Window.draw(Shield_Time.Text_Body);
			}
			Window.draw(textUser);

			/*Default_View*/

			Window.setView(Camera);
			Mouse_Position = Window.mapPixelToCoords(Mouse::getPosition(Window));
			Window.draw(Background5);
			for (int i = 0; i < Platforms.size(); i++)
			{
				Platforms[i].Draw(Window);
			}
			for (int i = 0; i < Metalbeing_Body.size(); i++)
			{
				Metalbeing_Body[i].Update(Difference, Player.GetPosition(), Window, Platforms);
			}
			for (int i = 0; i < Flowmon_Body.size(); i++)
			{
				Flowmon_Body[i].Flowmon_Update(Difference,Player.GetPosition(),Flowmon_Ball,Window);
			}
			for (int i = 0; i < Gaspow_Body.size(); i++)
			{
				Gaspow_Body[i].Gaspow_Update(Difference, Player.GetPosition(),Gaspow_Ball,Window);
			}
			for (int i = 0; i < Foulling_Body.size(); i++)
			{
				Foulling_Body[i].Update(Difference, Player.GetPosition(), Window, Platforms);
			}
			for (int i = 0; i < Items.size(); i++)
			{
				Items[i].Update(Difference, Window);
			}
			for (int i = 0; i < Enemy_Score.size(); i++)
			{
				Enemy_Score[i].Update(Difference, Window);
			}
			for (int i = 0; i < Warpgate_Body.size(); i++)
			{
				Warpgate_Body[i].Update(Difference, Window);
			}
			Player.Update(Difference, Mouse_Position, Window, Platforms, bulletVec, bullet);			
			if (isShieldON)
			{
				Window.draw(Shield);
			}
			Mouse_Cursor.setPosition(Mouse_Position);
			Window.draw(Mouse_Cursor);

			/*Chacter_View*/

			Window.setView(Character);
			Window.draw(Background5);
			for (int i = 0; i < Platforms.size(); i++)
			{
				Platforms[i].Draw(Window);
			}
			if (Player.Player_Visible)
				Player.Draw(Window);
			Window.display();
			break;
		}
		case Screen::Third_Boss:
		{
			if (Player.HP <= 0)
			{
				Die.play();
				TBoss.stop();
				Main_Theme.play();
				scoreRank[0] = score;
				screen = Screen::Scoreboard;
				Player.HP = 0; int i, j, temp;
				user[0] = str;
				scoreFile.open("Sprite/Text/Highscore.txt");
				scoreFile >> scoreRank[1] >> scoreRank[2] >> scoreRank[3] >> scoreRank[4] >> scoreRank[5];
				scoreFile.close();

				userFile.open("Sprite/Text/Username.txt");
				userFile >> user[1] >> user[2] >> user[3] >> user[4] >> user[5];
				userFile.close();
				std::string strtemp;
				for (i = 0; i < 6; i++)
				{
					for (j = i + 1; j < 6; j++)
					{
						if (scoreRank[i] < scoreRank[j])
						{
							temp = scoreRank[i];
							scoreRank[i] = scoreRank[j];
							scoreRank[j] = temp;
							strtemp = user[i];
							user[i] = user[j];
							user[j] = strtemp;
						}
					}
				}
				writeUser.open("Sprite/Text/Username.txt");
				for (i = 0; i < 5; i++)
				{
					writeUser << user[i] << std::endl;
				}
				writeUser.close();

				writeScore.open("Sprite/Text/Highscore.txt");
				for (i = 0; i < 5; i++)
				{
					writeScore << scoreRank[i] << std::endl;
				}
				writeScore.close();
			}
			Event Window_Event;
			Total_Shield += Difference;
			Total_Item += Difference;
			Time_Spawn += Difference;

			/*Default_View*/

			Camera.setViewport(FloatRect(0, 0, 1, 625.0 / Window.getSize().y));
			Camera.setSize(Window.getSize().x, Window.getSize().y* 625.0 / Window.getSize().y);

			/*Character_View*/

			Character.setViewport(FloatRect(25.0 / Window.getSize().x, 645.0 / Window.getSize().y, 150.0 / Window.getSize().x, 103.0 / Window.getSize().y));
			Character.setSize(Window.getSize().x*150.0 / Window.getSize().x, Window.getSize().y*103.0 / Window.getSize().y);
			Character.setCenter(Player.GetPosition().x, Player.GetPosition().y + 15);

			/*GUI_View*/

			GUI_Place.setViewport(FloatRect(0, 625.0 / Window.getSize().y, 1, 143.0 / Window.getSize().y));
			GUI_Place.setSize(Window.getSize().x, Window.getSize().y*143.0 / Window.getSize().y);
			GUI_Place.setCenter(GUI_Place.getSize().x / 2, GUI_Place.getSize().y / 2);

			GUI_Background.setSize(GUI_Place.getSize());
			Empty_Bar.setPosition(Vector2f(GUI_Place.getViewport().left + 250, GUI_Place.getViewport().top + 75));
			GUI_Background.setPosition(GUI_Place.getViewport().left, GUI_Place.getViewport().top);
			HP_Bar.setPosition(Vector2f(GUI_Place.getViewport().left + 250, GUI_Place.getViewport().top + 75));
			HP_Bar.setSize(Vector2f(Player.HP*Empty_Bar.getSize().x / 100.0, 20));

			textUser.setPosition(Vector2f(GUI_Place.getViewport().left + 310, GUI_Place.getViewport().top + 20));
			textUser.setFillColor(Color::Black);
			textUser.setCharacterSize(25);
			if (onetime)
			{
				Thornseeker_Body.clear();
				GUI.clear();
				Platforms.clear();
				Thorn_Spike.clear();
				bullet.clear();
				bulletVec.clear();
				Thorn.clear();
				Lightning_Bolt.clear();
				Metalbeing_Body.clear();
				Items.clear();
				Enemy_Score.clear();
				Time_Items.clear();

				TStage.stop();
				TBoss.play();
				Floor NewPlatforms(&TBoss_Floor, Vector2f(0, 0));
				Platforms.push_back(NewPlatforms);
				Player.getBody().setPosition(200, 0);
				Metalbeing NewMetalbeing(&Metalbeing_Texture, Vector2u(6, 6), 0.2f, Vector2f(rand() % 767 + 400, 450), Vector2f(500, 500));
				Metalbeing_Body.push_back(NewMetalbeing);
				Thornseeker NewThornseeker(&Thornseeker_Texture, Vector2u(10, 14), 0.2f, Vector2f(683, 400), Vector2f(600, 600));
				Thornseeker_Body.push_back(NewThornseeker);
				Text_String GUI1("Name", GUI_Font, Vector2f(GUI_Place.getViewport().left + 200, GUI_Place.getViewport().top + 20), 25, Color::White, 2, Color::Black);
				GUI.push_back(GUI1);
				Text_String GUI2("HP", GUI_Font, Vector2f(GUI_Place.getViewport().left + 200, GUI_Place.getViewport().top + 70), 25, Color::Red, 2, Color::Black);
				GUI.push_back(GUI2);
				Text_String GUI3("Score", GUI_Font, Vector2f(GUI_Place.getViewport().left + 500, GUI_Place.getViewport().top + 70), 25, Color::Magenta, 2, Color::Black);
				GUI.push_back(GUI3);
				Background6.setPosition(0, 0);
				Background6.setTexture(&TBoss_Background);
				
				Camera.setCenter(Platforms[0].Get_Size().width / 2.0f, Platforms[0].Get_Size().height / 2.0f);
				Time_Spawn = 0;
				Stop = false;
				onetime = false;
			}

			if (Time_Spawn >= 20.0f && !Stop)
			{
				Metalbeing NewMetalbeing(&Metalbeing_Texture, Vector2u(6, 6), 0.2f, Vector2f(rand() % 767 + 400, 450), Vector2f(500, 500));
				Metalbeing_Body.push_back(NewMetalbeing);
				Time_Spawn = 0;
				Metal_Count++;
			}

			/*Window Event*/

			while (Window.pollEvent(Window_Event)) {}
			if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			{
				Main_Theme.play();
				TBoss.stop();
				scoreRank[0] = score;
				int i, j, temp;
				user[0] = str;
				scoreFile.open("Sprite/Text/Highscore.txt");
				scoreFile >> scoreRank[1] >> scoreRank[2] >> scoreRank[3] >> scoreRank[4] >> scoreRank[5];
				scoreFile.close();

				userFile.open("Sprite/Text/Username.txt");
				userFile >> user[1] >> user[2] >> user[3] >> user[4] >> user[5];
				userFile.close();
				std::string strtemp;
				for (i = 0; i < 6; i++)
				{
					for (j = i + 1; j < 6; j++)
					{
						if (scoreRank[i] < scoreRank[j])
						{
							temp = scoreRank[i];
							scoreRank[i] = scoreRank[j];
							scoreRank[j] = temp;
							strtemp = user[i];
							user[i] = user[j];
							user[j] = strtemp;
						}
					}
				}
				writeUser.open("Sprite/Text/Username.txt");
				for (i = 0; i < 5; i++)
				{
					writeUser << user[i] << std::endl;
				}
				writeUser.close();

				writeScore.open("Sprite/Text/Highscore.txt");
				for (i = 0; i < 5; i++)
				{
					writeScore << scoreRank[i] << std::endl;
				}
				writeScore.close();
				screen = Screen::Menu;
			}

			/*Bullet_Collision*/

			for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Metalbeing_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Metalbeing_Body[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Metalbeing_Body[j].isDying)
						{
							Metalbeing_Body[j].Metalbeing_Health -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Metalbeing_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Metalbeing_Body[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Metalbeing_Body[j].isDying)
						{
							Metalbeing_Body[j].Metalbeing_Health -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Thornseeker_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Thornseeker_Body[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Thornseeker_Body[j].isDying&&Thornseeker_Body[j].Row != Thornseeker_Body[j].LStable&& Thornseeker_Body[j].Row != Thornseeker_Body[j].Stable)
						{
							Thornseeker_Body[j].Thornseeker_Health -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Thornseeker_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Thornseeker_Body[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Thornseeker_Body[j].isDying&&Thornseeker_Body[j].Row != Thornseeker_Body[j].LStable&& Thornseeker_Body[j].Row != Thornseeker_Body[j].Stable)
						{
							Thornseeker_Body[j].Thornseeker_Health -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}

			/*Platform_Collision*/

			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < bulletVec.size(); j++)
				{
					if (Collision::PixelPerfectTest(bulletVec[j].Get_Body(), Platforms[i].Body(), 0) || bulletVec[j].Get_Body().getPosition().x - abs(bulletVec[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || bulletVec[j].Get_Body().getPosition().x + abs(bulletVec[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || bulletVec[j].Get_Body().getPosition().y + abs(bulletVec[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || bulletVec[j].Get_Body().getPosition().y - abs(bulletVec[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						if (!Player.isWave)
						{
							bulletVec.erase(bulletVec.begin() + j);
							break;
						}
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Thorn.size(); j++)
				{
					if (Collision::PixelPerfectTest(Thorn[j].Get_Body(), Platforms[i].Body(), 0))
					{
						Explosion newPovy_Splash(&Spike_Texture, Vector2u(31, 1), 0.2f);
						newPovy_Splash.setPosition(Thorn[j].Get_Body().getPosition());
						Thorn_Spike.push_back(newPovy_Splash);
						Thorn.erase(Thorn.begin() + j);
						break;
					}
					if (Thorn[j].Get_Body().getPosition().x - abs(Thorn[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || Thorn[j].Get_Body().getPosition().x + abs(Thorn[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || Thorn[j].Get_Body().getPosition().y + abs(Thorn[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || Thorn[j].Get_Body().getPosition().y - abs(Thorn[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						Thorn.erase(Thorn.begin() + j);
						break;
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < bullet.size(); j++)
				{
					if (Collision::PixelPerfectTest(bullet[j].Get_Body(), Platforms[i].Body(), 0) || bullet[j].Get_Body().getPosition().x - abs(bullet[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || bullet[j].Get_Body().getPosition().x + abs(bullet[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || bullet[j].Get_Body().getPosition().y + abs(bullet[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || bullet[j].Get_Body().getPosition().y - abs(bullet[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						bullet.erase(bullet.begin() + j);
						break;
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Items.size(); j++)
				{
					if (Collision::PixelPerfectTest(Items[j].Item_Projectiles.Get_Body(), Platforms[i].Body(), 0))
					{
						Items[j].Item_Projectiles.isMoving = false;
					}
				}
			}

			/*Player Collision*/

			for (int i = 0; i < Items.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Items[i].Item_Projectiles.Get_Body(), 0))
				{
					if (!Player.isDying)
					{
						if (Items[i].isArrow)
						{
							Player.isWave = false;
							Player.isDirect = false;
							Player.isLaser = false;
							Player.isLob = false;
							Player.isArrow = true;
							Time_Items.clear();
							ItemSound.play();
							Count_Item = Total_Item;
							Item NewItems(&Arrow_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isLob)
						{
							ItemSound.play();
							Player.isWave = false;
							Player.isDirect = false;
							Player.isLaser = false;
							Player.isLob = true;
							Player.isArrow = false;
							Count_Item = Total_Item;
							Time_Items.clear();
							Item NewItems(&Lob_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isWave)
						{
							ItemSound.play();
							Player.isWave = true;
							Player.isDirect = false;
							Player.isLaser = false;
							Player.isLob = false;
							Player.isArrow = false;
							Time_Items.clear();
							Count_Item = Total_Item;
							Item NewItems(&Wave_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isLaser)
						{
							ItemSound.play();
							Player.isWave = false;
							Player.isDirect = false;
							Player.isLaser = true;
							Player.isLob = false;
							Player.isArrow = false;
							Time_Items.clear();
							Count_Item = Total_Item;
							Item NewItems(&Laser_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isShield) { isShieldON = true; Count_Shield = Total_Shield; }
						else if (Items[i].isFood) { Player.HP += Items[i].Health; Munch.play(); }
						else { SoulSound.play(); }
						Items[i].Item_Visible = false;
						score += Items[i].Score;
						Items.erase(Items.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < Lightning_Bolt.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Lightning_Bolt[i].Explosion_Body, 0))
				{
					if (Lightning_Bolt[i].Damagable)
					{
						if (!Player.isHurting && !Player.isDying)
						{
							Player.HP -= Lightning_Bolt[i].Damage;
							Player.Player_Animation.Visible = true;
							Player.isHurting = true;
							Player.Player_Animation.Current_Image.x = 0;
						}
					}
				}
			}
			for (int i = 0; i < Thorn_Spike.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Thorn_Spike[i].Explosion_Body, 0))
				{
					if (Thorn_Spike[i].Damagable)
					{
						if (!Player.isHurting && !Player.isDying)
						{
							Player.HP -= Thorn_Spike[i].Damage;
							Player.Player_Animation.Visible = true;
							Player.isHurting = true;
							Player.Player_Animation.Current_Image.x = 0;
						}
					}
				}
			}
			for (int i = 0; i < Thornseeker_Body.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Thornseeker_Body[i].Get_Body(), 0) && !Player.isHurting && !Player.isDying)
				{
					if (Thornseeker_Body[i].Row == Thornseeker_Body[i].Spark || Thornseeker_Body[i].Row == Thornseeker_Body[i].LSpark)
						Player.HP -= 20;
					else if (Thornseeker_Body[i].Row == Thornseeker_Body[i].Idle || Thornseeker_Body[i].Row == Thornseeker_Body[i].LIdle)
						Player.HP -= 10;
					else
						Player.HP -= 5;
					Player.isHurting = true;
					Player.Player_Animation.Visible = true;
					Player.Player_Animation.Current_Image.x = 0;
				}
			}
			for (int i = 0; i < Warpgate_Body.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Warpgate_Body[i].Get_Body()) && !Player.isHurting && !Player.isDying)
				{
					if (Keyboard::isKeyPressed(Keyboard::Space))
					{
						screen = Warpgate_Body[i].to;
						onetime = true;
						break;
					}
				}
			}

			/*Items*/

			for (int i = 0; i < Metalbeing_Body.size(); i++)
			{
				if (!Metalbeing_Body[i].Metalbeing_Visible)
				{
					num = rand() % 5;
					if (num == 0)
					{
						Item newItem(&Shield_Texture, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isShield = true;
						newItem.Item_Projectiles.Get_Body().setScale(2,2);
						Items.push_back(newItem);
					}
					else if (num == 1)
					{
						Item newItem(&Arrow_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isArrow = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05,1.05);
						Items.push_back(newItem);
					}
					else if (num == 2)
					{
						Item newItem(&Laser_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isLaser = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05,1.05);
						Items.push_back(newItem);
					}
					else if (num == 3)
					{
						Item newItem(&Wave_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isWave = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05,1.05);
						Items.push_back(newItem);
					}
					else if (num == 4)
					{
						Item newItem(&Lob_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isLob = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05,1.05);
						Items.push_back(newItem);
					}
					Metalbeing_Body.erase(Metalbeing_Body.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Thornseeker_Body.size(); i++)
			{
				if (!Thornseeker_Body[i].Thornseeker_Visible)
				{
					score += Thornseeker_Body[i].Score;
					Text_String newScore(std::to_string(Thornseeker_Body[i].Score), Score_Font, Vector2f(Thornseeker_Body[i].Get_Body().getPosition().x, Thornseeker_Body[i].Get_Body().getPosition().y - 20), 20, Color::Yellow, 1, Color::Black);
					Enemy_Score.push_back(newScore);
					num = rand() % 12 + 1;
					if (num >= 8)
					{
						Item newItem(&Ramen, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 15);
						newItem.Item_Projectiles.setPos(Vector2f(Thornseeker_Body[i].Get_Body().getPosition().x, Thornseeker_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 45;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					else if (num >= 6)
					{
						Item newItem(&Cake, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 20);
						newItem.Item_Projectiles.setPos(Vector2f(Thornseeker_Body[i].Get_Body().getPosition().x, Thornseeker_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 100;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					else
					{
						Item newItem(&Apple, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 10);
						newItem.Item_Projectiles.setPos(Vector2f(Thornseeker_Body[i].Get_Body().getPosition().x, Thornseeker_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 70;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					num = rand() % 41 + 10;
					for (int j = 1; j <= num; j++)
					{
						Item newItem(&Soul, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(4, 1), 0.2f, 5);
						newItem.Item_Projectiles.setPos(Vector2f(Thornseeker_Body[i].Get_Body().getPosition().x, Thornseeker_Body[i].Get_Body().getPosition().y - 20));
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					Stop = true;
					WarpGate WarpGate1(&Warpgate_Texture,Vector2f(1252,511),Screen::Fourth_Stage,Vector2u(20,1),0.2f);
					Warpgate_Body.push_back(WarpGate1);
					Thornseeker_Body.erase(Thornseeker_Body.begin() + i);
					break;
				}
			}

			/*Items Active*/

			if (isShieldON)
			{
				Shield.setPosition(Player.GetPosition());
			}
			else
			{
				Shield.setPosition(-100, -100);
			}
			if (Total_Item - Count_Item >= 10.0f)
			{
				Player.isArrow = false;
				Player.isLaser = false;
				Player.isLob = false;
				Player.isWave = false;
				Player.isDirect = true;
				Total_Item = 0;
				Count_Item = 0;
				Time_Items.clear();
			}
			if (Total_Shield - Count_Shield >= 10.0f)
			{
				isShieldON = false;
				Total_Shield = 0;
				Count_Shield = 0;
			}

			
			Window.clear();

			/*GUI_View*/

			Window.setView(GUI_Place);
			Window.draw(GUI_Background);
			for (int i = 0; i < GUI.size(); i++)
			{
				GUI[i].Draw(Window);
			}
			Score.Update_Text(std::to_string(score));
			Health.Update_Text(std::to_string(Player.HP) + "/100");
			Window.draw(Empty_Bar);
			Window.draw(HP_Bar);
			Score.Draw(Window);
			Health.Draw(Window);
			Score_Soul.Item_Projectiles.setPos(Vector2f(GUI_Place.getViewport().left + 620.0f, GUI_Place.getViewport().top + 80.0f));
			Score_Soul.Update(Difference, Window);
			if (Player.isArrow || Player.isLob || Player.isLaser || Player.isWave)
			{
				for (int i = 0; i < Time_Items.size(); i++)
				{
					Time_Items[i].Item_Projectiles.setPos(Vector2f(GUI_Place.getViewport().left + 1200, GUI_Place.getViewport().top + 42));
					Time_Items[i].Update(Difference, Window);
				}
				Item_Time.Text_Body.setPosition(Vector2f(GUI_Place.getViewport().left + 1250, GUI_Place.getViewport().top + 20));
				Item_Time.Update_Text(std::to_string(10 - abs((int)Count_Item - (int)Total_Item)));
				Window.draw(Item_Time.Text_Body);
			}
			if (isShieldON)
			{
				Time_Shield.Item_Projectiles.Get_Body().setScale(2, 2);
				Time_Shield.Item_Projectiles.setPos(Vector2f(GUI_Place.getViewport().left + 1200, GUI_Place.getViewport().top + 110));
				Time_Shield.Update(Difference, Window);
				Shield_Time.Text_Body.setPosition(Vector2f(GUI_Place.getViewport().left + 1250, GUI_Place.getViewport().top + 85));
				Shield_Time.Update_Text(std::to_string(10 - abs((int)Count_Shield - (int)Total_Shield)));
				Window.draw(Shield_Time.Text_Body);
			}
			Window.draw(textUser);

			/*Default_View*/

			Window.setView(Camera);
			Mouse_Position = Window.mapPixelToCoords(Mouse::getPosition(Window));
			Window.draw(Background6);
			for (int i = 0; i < Platforms.size(); i++)
			{
				Platforms[i].Draw(Window);
			}
			for (int i = 0; i < Metalbeing_Body.size(); i++)
			{
				Metalbeing_Body[i].Update(Difference, Player.GetPosition(), Window, Platforms);
			}
			for (int i = 0; i < Items.size(); i++)
			{
				Items[i].Update(Difference, Window);
			}
			for (int i = 0; i < Enemy_Score.size(); i++)
			{
				Enemy_Score[i].Update(Difference, Window);
			}
			for (int i = 0; i < Warpgate_Body.size(); i++)
			{
				Warpgate_Body[i].Update(Difference,Window);
			}
			Player.Update(Difference, Mouse_Position, Window, Platforms, bulletVec, bullet);
			for (int i = 0; i < Thornseeker_Body.size(); i++)
			{
				Thornseeker_Body[i].Update(Difference, Player.GetPosition(), Window, Platforms, Thorn, Thorn_Spike, Lightning_Bolt);
			}
			for (int i = 0; i < Thorn_Spike.size(); i++)
			{
				Thorn_Spike[i].Damage = 10;
				Thorn_Spike[i].Damagable = true;
				Thorn_Spike[i].Update(Difference);
				if (Thorn_Spike[i].Explosion_Visible)
				{
					Window.draw(Thorn_Spike[i].Explosion_Body);
				}
				else 
				{
					Thorn_Spike.erase(Thorn_Spike.begin() + i);
				}
			}
			if (isShieldON)
			{
				Window.draw(Shield);
			}
			Mouse_Cursor.setPosition(Mouse_Position);
			Window.draw(Mouse_Cursor);

			/*Chacter_View*/

			Window.setView(Character);
			Window.draw(Background6);
			for (int i = 0; i < Platforms.size(); i++)
			{
				Platforms[i].Draw(Window);
			}
			if (Player.Player_Visible)
				Player.Draw(Window);
			Window.display();
			break;
		}
		case Screen::First_Stage:
		{
			if (Player.HP <= 0)
			{
				Die.play();
				FStage.stop();
				Main_Theme.play();
				scoreRank[0] = score;
				screen = Screen::Scoreboard;
				Player.HP = 0; int i, j, temp;
				user[0] = str;
				scoreFile.open("Sprite/Text/Highscore.txt");
				scoreFile >> scoreRank[1] >> scoreRank[2] >> scoreRank[3] >> scoreRank[4] >> scoreRank[5];
				scoreFile.close();

				userFile.open("Sprite/Text/Username.txt");
				userFile >> user[1] >> user[2] >> user[3] >> user[4] >> user[5];
				userFile.close();
				std::string strtemp;
				for (i = 0; i < 6; i++)
				{
					for (j = i + 1; j < 6; j++)
					{
						if (scoreRank[i] < scoreRank[j])
						{
							temp = scoreRank[i];
							scoreRank[i] = scoreRank[j];
							scoreRank[j] = temp;
							strtemp = user[i];
							user[i] = user[j];
							user[j] = strtemp;
						}
					}
				}
				writeUser.open("Sprite/Text/Username.txt");
				for (i = 0; i < 5; i++)
				{
					writeUser << user[i] << std::endl;
				}
				writeUser.close();

				writeScore.open("Sprite/Text/Highscore.txt");
				for (i = 0; i < 5; i++)
				{
					writeScore << scoreRank[i] << std::endl;
				}
				writeScore.close();
			}
			Event Window_Event;
			Total_Item += Difference;
			Time_Spawn += Difference;
			Total_Shield += Difference;

			/*Default_View*/

			Camera.setViewport(FloatRect(0, 0, 1, 625.0 / Window.getSize().y));
			Camera.setSize(Window.getSize().x, Window.getSize().y* 625.0 / Window.getSize().y);

			/*Character_View*/

			Character.setViewport(FloatRect(25.0 / Window.getSize().x, 645.0 / Window.getSize().y, 150.0 / Window.getSize().x, 103.0 / Window.getSize().y));
			Character.setSize(Window.getSize().x*150.0 / Window.getSize().x, Window.getSize().y*103.0 / Window.getSize().y);
			Character.setCenter(Player.GetPosition().x, Player.GetPosition().y + 15);

			/*GUI_View*/

			GUI_Place.setViewport(FloatRect(0, 625.0 / Window.getSize().y, 1, 143.0 / Window.getSize().y));
			GUI_Place.setSize(Window.getSize().x, Window.getSize().y*143.0 / Window.getSize().y);
			GUI_Place.setCenter(GUI_Place.getSize().x / 2, GUI_Place.getSize().y / 2);

			GUI_Background.setSize(GUI_Place.getSize());
			Empty_Bar.setPosition(Vector2f(GUI_Place.getViewport().left + 250, GUI_Place.getViewport().top + 75));
			GUI_Background.setPosition(GUI_Place.getViewport().left, GUI_Place.getViewport().top);
			HP_Bar.setPosition(Vector2f(GUI_Place.getViewport().left + 250, GUI_Place.getViewport().top + 75));
			HP_Bar.setSize(Vector2f(Player.HP*Empty_Bar.getSize().x / 100.0, 20));

			textUser.setPosition(Vector2f(GUI_Place.getViewport().left + 310, GUI_Place.getViewport().top + 20));
			textUser.setFillColor(Color::Black);
			textUser.setCharacterSize(25);

			if (onetime)
			{
				Player.HP = 105;
				GUI.clear();
				Platforms.clear();
				bullet.clear();
				bulletVec.clear();
				Metalbeing_Body.clear();
				Items.clear();
				Enemy_Score.clear();
				Time_Items.clear();
				Flowmon_Ball.clear();
				Flowmon_Body.clear();
				Foulling_Body.clear();
				Gaspow_Body.clear();
				Gaspow_Ball.clear();
				Warpgate_Body.clear();

				FStage.play();
				Main_Theme.stop();
				Floor NewPlatforms(&FStage_Floor, Vector2f(0, 0));
				Platforms.push_back(NewPlatforms);
				Player.getBody().setPosition(200, 300);
				WarpGate Warpgate1(&Warpgate_Texture, Vector2f(3852, 261), Screen::First_Boss, Vector2u(20, 1), 0.2f);
				Warpgate_Body.push_back(Warpgate1);
				Metalbeing Metalbeing1(&Metalbeing_Texture, Vector2u(6, 6), 0.2f, Vector2f(1814, 240), Vector2f(190, 10));
				Metalbeing_Body.push_back(Metalbeing1);
				Metalbeing Metalbeing2(&Metalbeing_Texture, Vector2u(6, 6), 0.2f, Vector2f(2672,468), Vector2f(0,0));
				Metalbeing_Body.push_back(Metalbeing2);
				Flowmon Flowmon1(&Flowmon_Texture, Vector2u(14, 8), 0.2f, Vector2f(1425, 300));
				Flowmon_Body.push_back(Flowmon1);
				Flowmon Flowmon2(&Flowmon_Texture, Vector2u(14, 8), 0.2f, Vector2f(2778, 200));
				Flowmon_Body.push_back(Flowmon2);
				Foulling Foulling1(&Foulling_Texture, Vector2u(4, 6), 0.2f, Vector2f(883,300), Vector2f(120,80));
				Foulling_Body.push_back(Foulling1);
				Foulling Foulling2(&Foulling_Texture, Vector2u(4, 6), 0.2f, Vector2f(3109,	460), Vector2f(200, 400));
				Foulling_Body.push_back(Foulling2);
				Foulling Foulling3(&Foulling_Texture, Vector2u(4, 6), 0.2f, Vector2f(3841, 450), Vector2f(100, 100));
				Foulling_Body.push_back(Foulling3);
				Gaspow Gaspow1(&Gaspow_Texture, Vector2u(6, 4), 0.2f, Vector2f(2228, 200));
				Gaspow_Body.push_back(Gaspow1);
				Text_String GUI1("Name", GUI_Font, Vector2f(GUI_Place.getViewport().left + 200, GUI_Place.getViewport().top + 20), 25, Color::White, 2, Color::Black);
				GUI.push_back(GUI1);
				Text_String GUI2("HP", GUI_Font, Vector2f(GUI_Place.getViewport().left + 200, GUI_Place.getViewport().top + 70), 25, Color::Red, 2, Color::Black);
				GUI.push_back(GUI2);
				Text_String GUI3("Score", GUI_Font, Vector2f(GUI_Place.getViewport().left + 500, GUI_Place.getViewport().top + 70), 25, Color::Magenta, 2, Color::Black);
				GUI.push_back(GUI3);
				Background1.setTexture(&FStage_Background);
				Background1.setPosition(0, 0);
				Camera.setCenter(Camera.getSize().x / 2, 645 / 2);
				onetime = false;

			}
			if (Player.GetPosition().x >= Background1.getPosition().x + Camera.getSize().x / 2 && Player.GetPosition().x <= Background1.getPosition().x + Background1.getSize().x - Camera.getSize().x / 2)
				Camera.setCenter(Player.GetPosition().x, 645 / 2);

			/*Window Event*/
			while (Window.pollEvent(Window_Event)) {}
			if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			{
				Main_Theme.play();
				FStage.stop();
				scoreRank[0] = score;
				int i, j, temp;
				user[0] = str;
				scoreFile.open("Sprite/Text/Highscore.txt");
				scoreFile >> scoreRank[1] >> scoreRank[2] >> scoreRank[3] >> scoreRank[4] >> scoreRank[5];
				scoreFile.close();

				userFile.open("Sprite/Text/Username.txt");
				userFile >> user[1] >> user[2] >> user[3] >> user[4] >> user[5];
				userFile.close();
				std::string strtemp;
				for (i = 0; i < 6; i++)
				{
					for (j = i + 1; j < 6; j++)
					{
						if (scoreRank[i] < scoreRank[j])
						{
							temp = scoreRank[i];
							scoreRank[i] = scoreRank[j];
							scoreRank[j] = temp;
							strtemp = user[i];
							user[i] = user[j];
							user[j] = strtemp;
						}
					}
				}
				writeUser.open("Sprite/Text/Username.txt");
				for (i = 0; i < 5; i++)
				{
					writeUser << user[i] << std::endl;
				}
				writeUser.close();

				writeScore.open("Sprite/Text/Highscore.txt");
				for (i = 0; i < 5; i++)
				{
					writeScore << scoreRank[i] << std::endl;
				}
				writeScore.close();
				screen = Screen::Menu;
			}

			/*Bullet_Collision*/

			for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Metalbeing_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Metalbeing_Body[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Metalbeing_Body[j].isDying)
						{
							Metalbeing_Body[j].Metalbeing_Health -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Metalbeing_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Metalbeing_Body[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Metalbeing_Body[j].isDying)
						{
							Metalbeing_Body[j].Metalbeing_Health -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Foulling_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Foulling_Body[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Foulling_Body[j].isDying)
						{
							Foulling_Body[j].Foulling_Health -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Foulling_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Foulling_Body[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Foulling_Body[j].isDying)
						{
							Foulling_Body[j].Foulling_Health -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Gaspow_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Gaspow_Body[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Gaspow_Body[j].isDying)
						{
							Gaspow_Body[j].Gaspow_Health -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Gaspow_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Gaspow_Body[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Gaspow_Body[j].isDying)
						{
							Gaspow_Body[j].Gaspow_Health -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Flowmon_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Flowmon_Body[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Flowmon_Body[j].isDying)
						{
							Flowmon_Body[j].Flowmon_Health -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Flowmon_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Flowmon_Body[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Flowmon_Body[j].isDying)
						{
							Flowmon_Body[j].Flowmon_Health -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}

			/*Platform_Collision*/

			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < bulletVec.size(); j++)
				{
					if (Collision::PixelPerfectTest(bulletVec[j].Get_Body(), Platforms[i].Body(), 0) || bulletVec[j].Get_Body().getPosition().x - abs(bulletVec[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || bulletVec[j].Get_Body().getPosition().x + abs(bulletVec[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || bulletVec[j].Get_Body().getPosition().y + abs(bulletVec[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || bulletVec[j].Get_Body().getPosition().y - abs(bulletVec[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						if (!Player.isWave)
						{
							bulletVec.erase(bulletVec.begin() + j);
							break;
						}
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < bullet.size(); j++)
				{
					if (Collision::PixelPerfectTest(bullet[j].Get_Body(), Platforms[i].Body(), 0) || bullet[j].Get_Body().getPosition().x - abs(bullet[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || bullet[j].Get_Body().getPosition().x + abs(bullet[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || bullet[j].Get_Body().getPosition().y + abs(bullet[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || bullet[j].Get_Body().getPosition().y - abs(bullet[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						bullet.erase(bullet.begin() + j);
						break;
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Items.size(); j++)
				{
					if (Collision::PixelPerfectTest(Items[j].Item_Projectiles.Get_Body(), Platforms[i].Body(), 0))
					{
						Items[j].Item_Projectiles.isMoving = false;
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Flowmon_Body.size(); j++)
				{
					if (!Collision::PixelPerfectTest(Flowmon_Body[j].Get_Body(), Platforms[i].Body(), 0))
					{
						Flowmon_Body[j].Get_Body().move(0, 98.1*Difference);
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Flowmon_Ball.size(); j++)
				{
					if (Collision::PixelPerfectTest(Flowmon_Ball[j].Get_Body(), Platforms[i].Body(), 0) || Flowmon_Ball[j].Get_Body().getPosition().x - abs(Flowmon_Ball[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || Flowmon_Ball[j].Get_Body().getPosition().x + abs(Flowmon_Ball[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || Flowmon_Ball[j].Get_Body().getPosition().y + abs(Flowmon_Ball[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || Flowmon_Ball[j].Get_Body().getPosition().y - abs(Flowmon_Ball[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						Flowmon_Ball.erase(Flowmon_Ball.begin() + j);
						break;
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Gaspow_Body.size(); j++)
				{
					if (!Collision::PixelPerfectTest(Gaspow_Body[j].Get_Body(), Platforms[i].Body(), 0))
					{
						Gaspow_Body[j].Get_Body().move(0, 98.1*Difference);
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Gaspow_Ball.size(); j++)
				{
					if (Collision::PixelPerfectTest(Gaspow_Ball[j].Get_Body(), Platforms[i].Body(), 0) || Gaspow_Ball[j].Get_Body().getPosition().x - abs(Gaspow_Ball[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || Gaspow_Ball[j].Get_Body().getPosition().x + abs(Gaspow_Ball[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || Gaspow_Ball[j].Get_Body().getPosition().y + abs(Gaspow_Ball[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || Gaspow_Ball[j].Get_Body().getPosition().y - abs(Gaspow_Ball[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						Gaspow_Ball.erase(Gaspow_Ball.begin() + j);
						break;
					}
				}
			}

			/*Player Collision*/

			for (int i = 0; i < Items.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Items[i].Item_Projectiles.Get_Body(), 0))
				{
					if (!Player.isDying)
					{
						if (Items[i].isArrow)
						{
							Player.isWave = false;
							Player.isDirect = false;
							Player.isLaser = false;
							Player.isLob = false;
							Player.isArrow = true;
							Time_Items.clear();
							ItemSound.play();
							Count_Item = Total_Item;
							Item NewItems(&Arrow_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isLob)
						{
							ItemSound.play();
							Player.isWave = false;
							Player.isDirect = false;
							Player.isLaser = false;
							Player.isLob = true;
							Player.isArrow = false;
							Count_Item = Total_Item;
							Time_Items.clear();
							Item NewItems(&Lob_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isWave)
						{
							ItemSound.play();
							Player.isWave = true;
							Player.isDirect = false;
							Player.isLaser = false;
							Player.isLob = false;
							Player.isArrow = false;
							Time_Items.clear();
							Count_Item = Total_Item;
							Item NewItems(&Wave_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isLaser)
						{
							ItemSound.play();
							Player.isWave = false;
							Player.isDirect = false;
							Player.isLaser = true;
							Player.isLob = false;
							Player.isArrow = false;
							Time_Items.clear();
							Count_Item = Total_Item;
							Item NewItems(&Laser_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isShield) { isShieldON = true; Count_Shield = Total_Shield; }
						else if (Items[i].isFood) { Player.HP += Items[i].Health; Munch.play(); }
						else { SoulSound.play(); }
						Items[i].Item_Visible = false;
						score += Items[i].Score;
						Items.erase(Items.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < Flowmon_Ball.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Flowmon_Ball[i].Get_Body(), 0))
				{
					if (!Player.isHurting && !Player.isDying)
					{
						Player.HP -= Flowmon_Ball[i].Damage;
						Player.Player_Animation.Visible = true;
						Player.isHurting = true;
						Player.Player_Animation.Current_Image.x = 0;
						Flowmon_Ball.erase(Flowmon_Ball.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < Flowmon_Ball.size(); i++)
			{
				if (Collision::PixelPerfectTest(Flowmon_Ball[i].Get_Body(), Shield, 0))
				{
					Flowmon_Ball.erase(Flowmon_Ball.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Flowmon_Body.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Flowmon_Body[i].Get_Body(), 0) && !Player.isHurting && !Player.isDying)
				{
					Player.HP -= 5;
					Player.isHurting = true;
					Player.Player_Animation.Visible = true;
					Player.Player_Animation.Current_Image.x = 0;
				}
			}
			for (int i = 0; i < Gaspow_Ball.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Gaspow_Ball[i].Get_Body(), 0))
				{
					if (!Player.isHurting && !Player.isDying)
					{
						Player.HP -= Gaspow_Ball[i].Damage;
						Player.Player_Animation.Visible = true;
						Player.isHurting = true;
						Player.Player_Animation.Current_Image.x = 0;
						Gaspow_Ball.erase(Gaspow_Ball.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < Gaspow_Ball.size(); i++)
			{
				if (Collision::PixelPerfectTest(Gaspow_Ball[i].Get_Body(), Shield, 0))
				{
					Gaspow_Ball.erase(Gaspow_Ball.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Gaspow_Body.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Gaspow_Body[i].Get_Body(), 0) && !Player.isHurting && !Player.isDying)
				{
					Player.HP -= 5;
					Player.isHurting = true;
					Player.Player_Animation.Visible = true;
					Player.Player_Animation.Current_Image.x = 0;
				}
			}
			for (int i = 0; i < Foulling_Body.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Foulling_Body[i].Get_Body(), 0) && !Player.isHurting && !Player.isDying)
				{
					Player.HP -= 5;
					Player.isHurting = true;
					Player.Player_Animation.Visible = true;
					Player.Player_Animation.Current_Image.x = 0;
				}
			}
			for (int i = 0; i < Warpgate_Body.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Warpgate_Body[i].Get_Body()) && !Player.isHurting && !Player.isDying)
				{
					if (Keyboard::isKeyPressed(Keyboard::Space))
					{
						screen = Warpgate_Body[i].to;
						onetime = true;
						break;
					}
				}
			}

			/*Items*/

			for (int i = 0; i < Metalbeing_Body.size(); i++)
			{
				if (!Metalbeing_Body[i].Metalbeing_Visible)
				{
					num = rand() % 5;
					if (num == 0)
					{
						Item newItem(&Shield_Texture, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isShield = true;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					else if (num == 1)
					{
						Item newItem(&Arrow_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isArrow = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					else if (num == 2)
					{
						Item newItem(&Laser_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isLaser = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					else if (num == 3)
					{
						Item newItem(&Wave_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isWave = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					else if (num == 4)
					{
						Item newItem(&Lob_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isLob = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					Metalbeing_Body.erase(Metalbeing_Body.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Flowmon_Body.size(); i++)
			{
				if (!Flowmon_Body[i].Flowmon_Visible)
				{
					score += Flowmon_Body[i].Score;
					Text_String newScore(std::to_string(Flowmon_Body[i].Score), Score_Font, Vector2f(Flowmon_Body[i].Get_Body().getPosition().x, Flowmon_Body[i].Get_Body().getPosition().y - 20), 20, Color::Yellow, 1, Color::Black);
					Enemy_Score.push_back(newScore);
					num = rand() % 12 + 1;
					if (num >= 8)
					{
						Item newItem(&Apple, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 15);
						newItem.Item_Projectiles.setPos(Vector2f(Flowmon_Body[i].Get_Body().getPosition().x, Flowmon_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 25;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					else if (num >= 6)
					{
						Item newItem(&Green_Apple, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 20);
						newItem.Item_Projectiles.setPos(Vector2f(Flowmon_Body[i].Get_Body().getPosition().x, Flowmon_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 10;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					else
					{
						Item newItem(&Ramen, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 10);
						newItem.Item_Projectiles.setPos(Vector2f(Flowmon_Body[i].Get_Body().getPosition().x, Flowmon_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 30;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					num = rand() % 5 + 1;
					for (int j = 1; j <= num; j++)
					{
						Item newItem(&Soul, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(4, 1), 0.2f, 5);
						newItem.Item_Projectiles.setPos(Vector2f(Flowmon_Body[i].Get_Body().getPosition().x, Flowmon_Body[i].Get_Body().getPosition().y - 20));
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					Flowmon_Body.erase(Flowmon_Body.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Gaspow_Body.size(); i++)
			{
				if (!Gaspow_Body[i].Gaspow_Visible)
				{
					score += Gaspow_Body[i].Score;
					Text_String newScore(std::to_string(Gaspow_Body[i].Score), Score_Font, Vector2f(Gaspow_Body[i].Get_Body().getPosition().x, Gaspow_Body[i].Get_Body().getPosition().y - 20), 20, Color::Yellow, 1, Color::Black);
					Enemy_Score.push_back(newScore);
					num = rand() % 12 + 1;
					if (num >= 8)
					{
						Item newItem(&Corn_Stick, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 15);
						newItem.Item_Projectiles.setPos(Vector2f(Gaspow_Body[i].Get_Body().getPosition().x, Gaspow_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 25;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					else if (num >= 6)
					{
						Item newItem(&Chicken, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 20);
						newItem.Item_Projectiles.setPos(Vector2f(Gaspow_Body[i].Get_Body().getPosition().x, Gaspow_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 10;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					else
					{
						Item newItem(&Lemon, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 10);
						newItem.Item_Projectiles.setPos(Vector2f(Gaspow_Body[i].Get_Body().getPosition().x, Gaspow_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 30;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					num = rand() % 5 + 1;
					for (int j = 1; j <= num; j++)
					{
						Item newItem(&Soul, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(4, 1), 0.2f, 5);
						newItem.Item_Projectiles.setPos(Vector2f(Gaspow_Body[i].Get_Body().getPosition().x, Gaspow_Body[i].Get_Body().getPosition().y - 20));
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					Gaspow_Body.erase(Gaspow_Body.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Foulling_Body.size(); i++)
			{
				if (!Foulling_Body[i].Foulling_Visible)
				{
					score += Foulling_Body[i].Score;
					Text_String newScore(std::to_string(Foulling_Body[i].Score), Score_Font, Vector2f(Foulling_Body[i].Get_Body().getPosition().x, Foulling_Body[i].Get_Body().getPosition().y - 20), 20, Color::Yellow, 1, Color::Black);
					Enemy_Score.push_back(newScore);
					num = rand() % 15 + 1;
					for (int j = 1; j <= num; j++)
					{
						Item newItem(&Soul, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(4, 1), 0.2f, 5);
						newItem.Item_Projectiles.setPos(Vector2f(Foulling_Body[i].Get_Body().getPosition().x, Foulling_Body[i].Get_Body().getPosition().y - 20));
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					Foulling_Body.erase(Foulling_Body.begin() + i);
					break;
				}
			}

			/*Items Active*/
			if (isShieldON)
			{
				Shield.setPosition(Player.GetPosition());
			}
			else
			{
				Shield.setPosition(-100, -100);
			}
			if (Total_Item - Count_Item >= 10.0f)
			{
				Player.isArrow = false;
				Player.isLaser = false;
				Player.isLob = false;
				Player.isWave = false;
				Player.isDirect = true;
				Total_Item = 0;
				Count_Item = 0;
				Time_Items.clear();
			}
			if (Total_Shield - Count_Shield >= 10.0f)
			{
				isShieldON = false;
				Total_Shield = 0;
				Count_Shield = 0;
			}


			Window.clear();

			/*GUI_View*/

			Window.setView(GUI_Place);
			Window.draw(GUI_Background);
			for (int i = 0; i < GUI.size(); i++)
			{
				GUI[i].Draw(Window);
			}
			Score.Update_Text(std::to_string(score));
			Health.Update_Text(std::to_string(Player.HP) + "/100");
			Window.draw(Empty_Bar);
			Window.draw(HP_Bar);
			Score.Draw(Window);
			Health.Draw(Window);
			Score_Soul.Item_Projectiles.setPos(Vector2f(GUI_Place.getViewport().left + 620.0f, GUI_Place.getViewport().top + 80.0f));
			Score_Soul.Update(Difference, Window);
			if (Player.isArrow || Player.isLob || Player.isLaser || Player.isWave)
			{
				for (int i = 0; i < Time_Items.size(); i++)
				{
					Time_Items[i].Item_Projectiles.setPos(Vector2f(GUI_Place.getViewport().left + 1200, GUI_Place.getViewport().top + 42));
					Time_Items[i].Update(Difference, Window);
				}
				Item_Time.Text_Body.setPosition(Vector2f(GUI_Place.getViewport().left + 1250, GUI_Place.getViewport().top + 20));
				Item_Time.Update_Text(std::to_string(10 - abs((int)Count_Item - (int)Total_Item)));
				Window.draw(Item_Time.Text_Body);
			}
			if (isShieldON)
			{
				Time_Shield.Item_Projectiles.Get_Body().setScale(2, 2);
				Time_Shield.Item_Projectiles.setPos(Vector2f(GUI_Place.getViewport().left + 1200, GUI_Place.getViewport().top + 110));
				Time_Shield.Update(Difference, Window);
				Shield_Time.Text_Body.setPosition(Vector2f(GUI_Place.getViewport().left + 1250, GUI_Place.getViewport().top + 85));
				Shield_Time.Update_Text(std::to_string(10 - abs((int)Count_Shield - (int)Total_Shield)));
				Window.draw(Shield_Time.Text_Body);
			}
			Window.draw(textUser);

			/*Default_View*/

			Window.setView(Camera);
			Mouse_Position = Window.mapPixelToCoords(Mouse::getPosition(Window));
			Window.draw(Background1);
			for (int i = 0; i < Platforms.size(); i++)
			{
				Platforms[i].Draw(Window);
			}
			for (int i = 0; i < Metalbeing_Body.size(); i++)
			{
				Metalbeing_Body[i].Update(Difference, Player.GetPosition(), Window, Platforms);
			}
			for (int i = 0; i < Flowmon_Body.size(); i++)
			{
				Flowmon_Body[i].Flowmon_Update(Difference, Player.GetPosition(), Flowmon_Ball, Window);
			}
			for (int i = 0; i < Gaspow_Body.size(); i++)
			{
				Gaspow_Body[i].Gaspow_Update(Difference, Player.GetPosition(), Gaspow_Ball, Window);
			}
			for (int i = 0; i < Foulling_Body.size(); i++)
			{
				Foulling_Body[i].Update(Difference, Player.GetPosition(), Window, Platforms);
			}
			for (int i = 0; i < Items.size(); i++)
			{
				Items[i].Update(Difference, Window);
			}
			for (int i = 0; i < Enemy_Score.size(); i++)
			{
				Enemy_Score[i].Update(Difference, Window);
			}
			for (int i = 0; i < Warpgate_Body.size(); i++)
			{
				Warpgate_Body[i].Update(Difference, Window);
			}
			Player.Update(Difference, Mouse_Position, Window, Platforms, bulletVec, bullet);
			if (isShieldON)
			{
				Window.draw(Shield);
			}
			Mouse_Cursor.setPosition(Mouse_Position);
			Window.draw(Mouse_Cursor);

			/*Chacter_View*/

			Window.setView(Character);
			Window.draw(Background1);
			for (int i = 0; i < Platforms.size(); i++)
			{
				Platforms[i].Draw(Window);
			}
			if (Player.Player_Visible)
				Player.Draw(Window);
			Window.display();
			break;
		}
		case Screen::First_Boss:
		{
			if (Player.HP <= 0)
			{
				Die.play();
				FBoss.stop();
				Main_Theme.play();
				scoreRank[0] = score;
				screen = Screen::Scoreboard;
				Player.HP = 0; int i, j, temp;
				user[0] = str;
				scoreFile.open("Sprite/Text/Highscore.txt");
				scoreFile >> scoreRank[1] >> scoreRank[2] >> scoreRank[3] >> scoreRank[4] >> scoreRank[5];
				scoreFile.close();

				userFile.open("Sprite/Text/Username.txt");
				userFile >> user[1] >> user[2] >> user[3] >> user[4] >> user[5];
				userFile.close();
				std::string strtemp;
				for (i = 0; i < 6; i++)
				{
					for (j = i + 1; j < 6; j++)
					{
						if (scoreRank[i] < scoreRank[j])
						{
							temp = scoreRank[i];
							scoreRank[i] = scoreRank[j];
							scoreRank[j] = temp;
							strtemp = user[i];
							user[i] = user[j];
							user[j] = strtemp;
						}
					}
				}
				writeUser.open("Sprite/Text/Username.txt");
				for (i = 0; i < 5; i++)
				{
					writeUser << user[i] << std::endl;
				}
				writeUser.close();

				writeScore.open("Sprite/Text/Highscore.txt");
				for (i = 0; i < 5; i++)
				{
					writeScore << scoreRank[i] << std::endl;
				}
				writeScore.close();
			}
			Event Window_Event;
			Total_Shield += Difference;
			Total_Item += Difference;
			Time_Spawn += Difference;

			/*Default_View*/

			Camera.setViewport(FloatRect(0, 0, 1, 625.0 / Window.getSize().y));
			Camera.setSize(Window.getSize().x, Window.getSize().y* 625.0 / Window.getSize().y);

			/*Character_View*/

			Character.setViewport(FloatRect(25.0 / Window.getSize().x, 645.0 / Window.getSize().y, 150.0 / Window.getSize().x, 103.0 / Window.getSize().y));
			Character.setSize(Window.getSize().x*150.0 / Window.getSize().x, Window.getSize().y*103.0 / Window.getSize().y);
			Character.setCenter(Player.GetPosition().x, Player.GetPosition().y + 15);

			/*GUI_View*/

			GUI_Place.setViewport(FloatRect(0, 625.0 / Window.getSize().y, 1, 143.0 / Window.getSize().y));
			GUI_Place.setSize(Window.getSize().x, Window.getSize().y*143.0 / Window.getSize().y);
			GUI_Place.setCenter(GUI_Place.getSize().x / 2, GUI_Place.getSize().y / 2);

			GUI_Background.setSize(GUI_Place.getSize());
			Empty_Bar.setPosition(Vector2f(GUI_Place.getViewport().left + 250, GUI_Place.getViewport().top + 75));
			GUI_Background.setPosition(GUI_Place.getViewport().left, GUI_Place.getViewport().top);
			HP_Bar.setPosition(Vector2f(GUI_Place.getViewport().left + 250, GUI_Place.getViewport().top + 75));
			HP_Bar.setSize(Vector2f(Player.HP*Empty_Bar.getSize().x / 100.0, 20));

			textUser.setPosition(Vector2f(GUI_Place.getViewport().left + 310, GUI_Place.getViewport().top + 20));
			textUser.setFillColor(Color::Black);
			textUser.setCharacterSize(25);
			if (onetime)
			{
				GUI.clear();
				Platforms.clear();
				bullet.clear();
				bulletVec.clear();
				Metalbeing_Body.clear();
				Items.clear();
				Frostmirage_Body.clear();
				Fireball_Clone.clear();
				Enemy_Score.clear();
				Firephoon.clear();
				Ice_Spike.clear();
				Frostmirage_Clone.clear();
				Warpgate_Body.clear();

				FBoss.play();
				FStage.stop();
				Floor NewPlatforms(&FBoss_Floor, Vector2f(0, 0));
				Platforms.push_back(NewPlatforms);
				Player.getBody().setPosition(200, 0);
				Frostmirage NewFrostmirage(&Frostmirage_Texture, Vector2u(7, 4), 0.2f, Vector2f(683, 400), Vector2f(600, 600));
				Frostmirage_Body.push_back(NewFrostmirage);
				Metalbeing NewMetalbeing(&Metalbeing_Texture, Vector2u(6, 6), 0.2f, Vector2f(rand() % 767 + 400, 450), Vector2f(500, 500));
				Metalbeing_Body.push_back(NewMetalbeing);
				Text_String GUI1("Name", GUI_Font, Vector2f(GUI_Place.getViewport().left + 200, GUI_Place.getViewport().top + 20), 25, Color::White, 2, Color::Black);
				GUI.push_back(GUI1);
				Text_String GUI2("HP", GUI_Font, Vector2f(GUI_Place.getViewport().left + 200, GUI_Place.getViewport().top + 70), 25, Color::Red, 2, Color::Black);
				GUI.push_back(GUI2);
				Text_String GUI3("Score", GUI_Font, Vector2f(GUI_Place.getViewport().left + 500, GUI_Place.getViewport().top + 70), 25, Color::Magenta, 2, Color::Black);
				GUI.push_back(GUI3);
				Background2.setTexture(&FBoss_Background);
				Background2.setPosition(0, 0);
				Camera.setCenter(Platforms[0].Get_Size().width / 2.0f, Platforms[0].Get_Size().height / 2.0f);
				Time_Spawn = 0;
				Stop = false;
				onetime = false;
			}

			if (Time_Spawn >= 20.0f && !Stop)
			{
				Metalbeing NewMetalbeing(&Metalbeing_Texture, Vector2u(6, 6), 0.2f, Vector2f(rand() % 767 + 400, 450), Vector2f(500, 500));
				Metalbeing_Body.push_back(NewMetalbeing);
				Time_Spawn = 0;
				Metal_Count++;
			}

			/*Window Event*/

			while (Window.pollEvent(Window_Event)) {}
			if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			{
				scoreRank[0] = score;
				int i, j, temp;
				user[0] = str;
				scoreFile.open("Sprite/Text/Highscore.txt");
				scoreFile >> scoreRank[1] >> scoreRank[2] >> scoreRank[3] >> scoreRank[4] >> scoreRank[5];
				scoreFile.close();

				userFile.open("Sprite/Text/Username.txt");
				userFile >> user[1] >> user[2] >> user[3] >> user[4] >> user[5];
				userFile.close();
				std::string strtemp;
				for (i = 0; i < 6; i++)
				{
					for (j = i + 1; j < 6; j++)
					{
						if (scoreRank[i] < scoreRank[j])
						{
							temp = scoreRank[i];
							scoreRank[i] = scoreRank[j];
							scoreRank[j] = temp;
							strtemp = user[i];
							user[i] = user[j];
							user[j] = strtemp;
						}
					}
				}
				writeUser.open("Sprite/Text/Username.txt");
				for (i = 0; i < 5; i++)
				{
					writeUser << user[i] << std::endl;
				}
				writeUser.close();

				writeScore.open("Sprite/Text/Highscore.txt");
				for (i = 0; i < 5; i++)
				{
					writeScore << scoreRank[i] << std::endl;
				}
				writeScore.close();
				FBoss.stop();
				Main_Theme.play();
				screen = Screen::Menu;
			}

			/*Bullet_Collision*/

			for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Metalbeing_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Metalbeing_Body[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Metalbeing_Body[j].isDying)
						{
							Metalbeing_Body[j].Metalbeing_Health -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Metalbeing_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Metalbeing_Body[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Metalbeing_Body[j].isDying)
						{
							Metalbeing_Body[j].Metalbeing_Health -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Frostmirage_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Frostmirage_Body[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Frostmirage_Body[j].isDying)
						{
							Frostmirage_Body[j].Frostmirage_Health -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Frostmirage_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Frostmirage_Body[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Frostmirage_Body[j].isDying)
						{
							Frostmirage_Body[j].Frostmirage_Health -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Frostmirage_Clone.size(); j++)
				{
					if (Collision::PixelPerfectTest(Frostmirage_Clone[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Frostmirage_Clone[j].isDying)
						{
							Frostmirage_Clone[j].Clone_Health -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Frostmirage_Clone.size(); j++)
				{
					if (Collision::PixelPerfectTest(Frostmirage_Clone[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Frostmirage_Clone[j].isDying)
						{
							Frostmirage_Clone[j].Clone_Health -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}

			/*Platform_Collision*/

			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < bulletVec.size(); j++)
				{
					if (Collision::PixelPerfectTest(bulletVec[j].Get_Body(), Platforms[i].Body(), 0) || bulletVec[j].Get_Body().getPosition().x - abs(bulletVec[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || bulletVec[j].Get_Body().getPosition().x + abs(bulletVec[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || bulletVec[j].Get_Body().getPosition().y + abs(bulletVec[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || bulletVec[j].Get_Body().getPosition().y - abs(bulletVec[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						if (!Player.isWave)
						{
							bulletVec.erase(bulletVec.begin() + j);
							break;
						}
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Firephoon.size(); j++)
				{
					if (Collision::PixelPerfectTest(Firephoon[j].Get_Body(), Platforms[i].Body(), 0) || Firephoon[j].Get_Body().getPosition().x - abs(Firephoon[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || Firephoon[j].Get_Body().getPosition().x + abs(Firephoon[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || Firephoon[j].Get_Body().getPosition().y + abs(Firephoon[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || Firephoon[j].Get_Body().getPosition().y - abs(Firephoon[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						Firephoon.erase(Firephoon.begin() + j);
						break;
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < bullet.size(); j++)
				{
					if (Collision::PixelPerfectTest(bullet[j].Get_Body(), Platforms[i].Body(), 0) || bullet[j].Get_Body().getPosition().x - abs(bullet[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || bullet[j].Get_Body().getPosition().x + abs(bullet[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || bullet[j].Get_Body().getPosition().y + abs(bullet[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || bullet[j].Get_Body().getPosition().y - abs(bullet[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						bullet.erase(bullet.begin() + j);
						break;
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Items.size(); j++)
				{
					if (Collision::PixelPerfectTest(Items[j].Item_Projectiles.Get_Body(), Platforms[i].Body(), 0))
					{
						Items[j].Item_Projectiles.isMoving = false;
					}
				}
			}

			/*Player Collision*/

			for (int i = 0; i < Items.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Items[i].Item_Projectiles.Get_Body(), 0))
				{
					if (!Player.isDying)
					{
						if (Items[i].isArrow)
						{
							Player.isWave = false;
							Player.isDirect = false;
							Player.isLaser = false;
							Player.isLob = false;
							Player.isArrow = true;
							Time_Items.clear();
							ItemSound.play();
							Count_Item = Total_Item;
							Item NewItems(&Arrow_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isLob)
						{
							ItemSound.play();
							Player.isWave = false;
							Player.isDirect = false;
							Player.isLaser = false;
							Player.isLob = true;
							Player.isArrow = false;
							Count_Item = Total_Item;
							Time_Items.clear();
							Item NewItems(&Lob_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isWave)
						{
							ItemSound.play();
							Player.isWave = true;
							Player.isDirect = false;
							Player.isLaser = false;
							Player.isLob = false;
							Player.isArrow = false;
							Time_Items.clear();
							Count_Item = Total_Item;
							Item NewItems(&Wave_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isLaser)
						{
							ItemSound.play();
							Player.isWave = false;
							Player.isDirect = false;
							Player.isLaser = true;
							Player.isLob = false;
							Player.isArrow = false;
							Time_Items.clear();
							Count_Item = Total_Item;
							Item NewItems(&Laser_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isShield) { isShieldON = true; Count_Shield = Total_Shield; }
						else if (Items[i].isFood) { Player.HP += Items[i].Health; Munch.play(); }
						else { SoulSound.play(); }
						Items[i].Item_Visible = false;
						score += Items[i].Score;
						Items.erase(Items.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < Ice_Spike.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Ice_Spike[i].Explosion_Body, 0))
				{
					if (Ice_Spike[i].Damagable)
					{
						if (!Player.isHurting && !Player.isDying)
						{
							Player.HP -= Ice_Spike[i].Damage;
							Player.Player_Animation.Visible = true;
							Player.isHurting = true;
							Player.Player_Animation.Current_Image.x = 0;
						}
					}
				}
			}
			for (int i = 0; i < Firephoon.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Firephoon[i].Get_Body(), 0))
				{
					if (!Player.isHurting && !Player.isDying)
					{
						Player.HP -= Firephoon[i].Damage;
						Player.Player_Animation.Visible = true;
						Player.isHurting = true;
						Player.Player_Animation.Current_Image.x = 0;
						Firephoon.erase(Firephoon.begin()+i);
						break;
					}
				}
			}
			for (int i = 0; i < Firephoon.size(); i++)
			{
				if (Collision::PixelPerfectTest(Firephoon[i].Get_Body(), Shield, 0))
				{
					Firephoon.erase(Firephoon.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Frostmirage_Body.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Frostmirage_Body[i].Get_Body(), 0) && !Player.isHurting && !Player.isDying)
				{
					Player.HP -= 5;
					Player.isHurting = true;
					Player.Player_Animation.Visible = true;
					Player.Player_Animation.Current_Image.x = 0;
				}
			}
			for (int i = 0; i < Frostmirage_Clone.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Frostmirage_Clone[i].Get_Body(), 0) && !Player.isHurting && !Player.isDying)
				{
					Player.HP -= 5;
					Player.isHurting = true;
					Player.Player_Animation.Visible = true;
					Player.Player_Animation.Current_Image.x = 0;
				}
			}

			for (int i = 0; i < Warpgate_Body.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Warpgate_Body[i].Get_Body()) && !Player.isHurting && !Player.isDying)
				{
					if (Keyboard::isKeyPressed(Keyboard::Space))
					{
						screen = Warpgate_Body[i].to;
						onetime = true;
						break;
					}
				}
			}

			/*Items*/

			for (int i = 0; i < Metalbeing_Body.size(); i++)
			{
				if (!Metalbeing_Body[i].Metalbeing_Visible)
				{
					num = rand() % 5;
					if (num == 0)
					{
						Item newItem(&Shield_Texture, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isShield = true;
						newItem.Item_Projectiles.Get_Body().setScale(2,2);
						Items.push_back(newItem);
					}
					else if (num == 1)
					{
						Item newItem(&Arrow_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isArrow = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05,1.05);
						Items.push_back(newItem);
					}
					else if (num == 2)
					{
						Item newItem(&Laser_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isLaser = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					else if (num == 3)
					{
						Item newItem(&Wave_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isWave = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					else if (num == 4)
					{
						Item newItem(&Lob_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isLob = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					Metalbeing_Body.erase(Metalbeing_Body.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Frostmirage_Body.size(); i++)
			{
				if (!Frostmirage_Body[i].Frostmirage_Visible)
				{
					score += Frostmirage_Body[i].Score;
					Text_String newScore(std::to_string(Frostmirage_Body[i].Score), Score_Font, Vector2f(Frostmirage_Body[i].Get_Body().getPosition().x, Frostmirage_Body[i].Get_Body().getPosition().y - 20), 20, Color::Yellow, 1, Color::Black);
					Enemy_Score.push_back(newScore);
					num = rand() % 12 + 1;
					if (num >= 8)
					{
						Item newItem(&Corn_Stick, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 15);
						newItem.Item_Projectiles.setPos(Vector2f(Frostmirage_Body[i].Get_Body().getPosition().x, Frostmirage_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 35;
						newItem.Item_Projectiles.Get_Body().setScale(2,2);
						Items.push_back(newItem);
					}
					else if (num >= 6)
					{
						Item newItem(&Cake, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 20);
						newItem.Item_Projectiles.setPos(Vector2f(Frostmirage_Body[i].Get_Body().getPosition().x, Frostmirage_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 100;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					else
					{
						Item newItem(&Onigiri, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 10);
						newItem.Item_Projectiles.setPos(Vector2f(Frostmirage_Body[i].Get_Body().getPosition().x, Frostmirage_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 20;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					num = rand() % 41 + 10;
					for (int j = 1; j <= num; j++)
					{
						Item newItem(&Soul, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(4, 1), 0.2f, 5);
						newItem.Item_Projectiles.setPos(Vector2f(Frostmirage_Body[i].Get_Body().getPosition().x, Frostmirage_Body[i].Get_Body().getPosition().y - 20));
						newItem.Item_Projectiles.Get_Body().setScale(1.05,1.05);
						Items.push_back(newItem);
					}
					Stop = true;
					WarpGate WarpGate1(&Warpgate_Texture, Vector2f(1252, 511), Screen::Second_Stage, Vector2u(20, 1), 0.2f);
					Warpgate_Body.push_back(WarpGate1);
					Frostmirage_Body.erase(Frostmirage_Body.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Frostmirage_Clone.size(); i++)
			{
				if (!Frostmirage_Clone[i].Clone_Visible)
				{
					Frostmirage_Clone.erase(Frostmirage_Clone.begin() + i);
					break;
				}
			}

			/*Items Active*/
			if (isShieldON)
			{
				Shield.setPosition(Player.GetPosition());
			}
			else
			{
				Shield.setPosition(-100, -100);
			}
			if (Total_Item - Count_Item >= 10.0f)
			{
				Player.isArrow = false;
				Player.isLaser = false;
				Player.isLob = false;
				Player.isWave = false;
				Player.isDirect = true;
				Total_Item = 0;
				Count_Item = 0;
				Time_Items.clear();
			}
			if (Total_Shield - Count_Shield >= 10.0f)
			{
				isShieldON = false;
				Total_Shield = 0;
				Count_Shield = 0;
			}

			Window.clear();

			/*GUI_View*/

			Window.setView(GUI_Place);
			Window.draw(GUI_Background);
			for (int i = 0; i < GUI.size(); i++)
			{
				GUI[i].Draw(Window);
			}
			Score.Update_Text(std::to_string(score));
			Health.Update_Text(std::to_string(Player.HP) + "/100");
			Window.draw(Empty_Bar);
			Window.draw(HP_Bar);
			Score.Draw(Window);
			Health.Draw(Window);
			Score_Soul.Item_Projectiles.setPos(Vector2f(GUI_Place.getViewport().left + 620.0f, GUI_Place.getViewport().top + 80.0f));
			Score_Soul.Update(Difference, Window);
			if (Player.isArrow || Player.isLob || Player.isLaser || Player.isWave)
			{
				for (int i = 0; i < Time_Items.size(); i++)
				{
					Time_Items[i].Item_Projectiles.setPos(Vector2f(GUI_Place.getViewport().left + 1200, GUI_Place.getViewport().top + 42));
					Time_Items[i].Update(Difference, Window);
				}
				Item_Time.Text_Body.setPosition(Vector2f(GUI_Place.getViewport().left + 1250, GUI_Place.getViewport().top + 20));
				Item_Time.Update_Text(std::to_string(10 - abs((int)Count_Item - (int)Total_Item)));
				Window.draw(Item_Time.Text_Body);
			}
			if (isShieldON)
			{
				Time_Shield.Item_Projectiles.Get_Body().setScale(2, 2);
				Time_Shield.Item_Projectiles.setPos(Vector2f(GUI_Place.getViewport().left + 1200, GUI_Place.getViewport().top + 110));
				Time_Shield.Update(Difference, Window);
				Shield_Time.Text_Body.setPosition(Vector2f(GUI_Place.getViewport().left + 1250, GUI_Place.getViewport().top + 85));
				Shield_Time.Update_Text(std::to_string(10 - abs((int)Count_Shield - (int)Total_Shield)));
				Window.draw(Shield_Time.Text_Body);
			}
			Window.draw(textUser);

			/*Default_View*/

			Window.setView(Camera);
			Mouse_Position = Window.mapPixelToCoords(Mouse::getPosition(Window));
			Window.draw(Background2);
			for (int i = 0; i < Platforms.size(); i++)
			{
				Platforms[i].Draw(Window);
			}
			for (int i = 0; i < Metalbeing_Body.size(); i++)
			{
				Metalbeing_Body[i].Update(Difference, Player.GetPosition(), Window, Platforms);
			}
			for (int i = 0; i < Items.size(); i++)
			{
				Items[i].Update(Difference, Window);
			}
			for (int i = 0; i < Enemy_Score.size(); i++)
			{
				Enemy_Score[i].Update(Difference, Window);			
			}
			for (int i = 0; i < Warpgate_Body.size(); i++)
			{
				Warpgate_Body[i].Update(Difference,Window);
			}
			Player.Update(Difference, Mouse_Position, Window, Platforms, bulletVec, bullet);	
			for (int i = 0; i < Frostmirage_Body.size(); i++)
			{
				Frostmirage_Body[i].Update(Difference, Player.GetPosition(), Window, Platforms, Firephoon, Ice_Spike, Frostmirage_Clone);
			}
			for (int i = 0; i < Frostmirage_Clone.size(); i++)
			{
				Frostmirage_Clone[i].Update(Difference, Player.GetPosition(), Window, Platforms, Firephoon);
			}
			for (int i = 0; i < Fireball_Clone.size(); i++)
			{
				Fireball_Clone[i].fire(500, Difference, Fireball_Clone[i].Get_Direction());
				Fireball_Clone[i].Update(Difference, Window);
			}
			if (isShieldON)
			{
				Window.draw(Shield);
			}
			Mouse_Cursor.setPosition(Mouse_Position);
			Window.draw(Mouse_Cursor);

			/*Chacter_View*/

			Window.setView(Character);
			Window.draw(Background2);
			for (int i = 0; i < Platforms.size(); i++)
			{
				Platforms[i].Draw(Window);
			}
			if (Player.Player_Visible)
				Player.Draw(Window);
			Window.display();
			break;
		}
		case Screen::Second_Stage:
		{
			if (Player.HP <= 0)
			{
				Die.play();
				Main_Theme.play();
				SStage.stop();
				scoreRank[0] = score;
				screen = Screen::Scoreboard;
				Player.HP = 0; int i, j, temp;
				user[0] = str;
				scoreFile.open("Sprite/Text/Highscore.txt");
				scoreFile >> scoreRank[1] >> scoreRank[2] >> scoreRank[3] >> scoreRank[4] >> scoreRank[5];
				scoreFile.close();

				userFile.open("Sprite/Text/Username.txt");
				userFile >> user[1] >> user[2] >> user[3] >> user[4] >> user[5];
				userFile.close();
				std::string strtemp;
				for (i = 0; i < 6; i++)
				{
					for (j = i + 1; j < 6; j++)
					{
						if (scoreRank[i] < scoreRank[j])
						{
							temp = scoreRank[i];
							scoreRank[i] = scoreRank[j];
							scoreRank[j] = temp;
							strtemp = user[i];
							user[i] = user[j];
							user[j] = strtemp;
						}
					}
				}
				writeUser.open("Sprite/Text/Username.txt");
				for (i = 0; i < 5; i++)
				{
					writeUser << user[i] << std::endl;
				}
				writeUser.close();

				writeScore.open("Sprite/Text/Highscore.txt");
				for (i = 0; i < 5; i++)
				{
					writeScore << scoreRank[i] << std::endl;
				}
				writeScore.close();
			}
			Event Window_Event;
			Total_Item += Difference;
			Time_Spawn += Difference;
			Total_Shield += Difference;

			/*Default_View*/

			Camera.setViewport(FloatRect(0, 0, 1, 625.0 / Window.getSize().y));
			Camera.setSize(Window.getSize().x, Window.getSize().y* 625.0 / Window.getSize().y);

			/*Character_View*/

			Character.setViewport(FloatRect(25.0 / Window.getSize().x, 645.0 / Window.getSize().y, 150.0 / Window.getSize().x, 103.0 / Window.getSize().y));
			Character.setSize(Window.getSize().x*150.0 / Window.getSize().x, Window.getSize().y*103.0 / Window.getSize().y);
			Character.setCenter(Player.GetPosition().x, Player.GetPosition().y + 15);

			/*GUI_View*/

			GUI_Place.setViewport(FloatRect(0, 625.0 / Window.getSize().y, 1, 143.0 / Window.getSize().y));
			GUI_Place.setSize(Window.getSize().x, Window.getSize().y*143.0 / Window.getSize().y);
			GUI_Place.setCenter(GUI_Place.getSize().x / 2, GUI_Place.getSize().y / 2);

			GUI_Background.setSize(GUI_Place.getSize());
			Empty_Bar.setPosition(Vector2f(GUI_Place.getViewport().left + 250, GUI_Place.getViewport().top + 75));
			GUI_Background.setPosition(GUI_Place.getViewport().left, GUI_Place.getViewport().top);
			HP_Bar.setPosition(Vector2f(GUI_Place.getViewport().left + 250, GUI_Place.getViewport().top + 75));
			HP_Bar.setSize(Vector2f(Player.HP*Empty_Bar.getSize().x / 100.0, 20));

			textUser.setPosition(Vector2f(GUI_Place.getViewport().left + 310, GUI_Place.getViewport().top + 20));
			textUser.setFillColor(Color::Black);
			textUser.setCharacterSize(25);
			if (onetime)
			{
				GUI.clear();
				Platforms.clear();
				bullet.clear();
				bulletVec.clear();
				Metalbeing_Body.clear();
				Items.clear();
				Enemy_Score.clear();
				Time_Items.clear();
				Warpgate_Body.clear();
				Flowmon_Ball.clear();
				Flowmon_Body.clear();
				Gloomthing_Body.clear();
				Povy_Ball.clear();
				Povy_Body.clear();

				FBoss.stop();
				SStage.play();
				Floor NewPlatforms(&SStage_Floor, Vector2f(0, 0));
				Platforms.push_back(NewPlatforms);
				Player.getBody().setPosition(200, 0);
				WarpGate Warpgate1(&Warpgate_Texture, Vector2f(3899, 540), Screen::Second_Boss, Vector2u(20, 1), 0.2f);
				Warpgate_Body.push_back(Warpgate1);
				Metalbeing Metalbeing1(&Metalbeing_Texture, Vector2u(6, 6), 0.2f, Vector2f(761, 240), Vector2f(110, 100));
				Metalbeing_Body.push_back(Metalbeing1);
				Gloomthing Gloomthing1(&Gloomthing_Texture, Vector2u(11, 8), 0.2f, Vector2f(3491, 300));
				Gloomthing_Body.push_back(Gloomthing1);
				Povy Povy1(&Povy_Texture, Vector2u(4, 2), 0.2f, Vector2f(2449, 0), &PovyBallSP_Texture);
				Povy_Body.push_back(Povy1);
				Flowmon Flowmon1(&Flowmon_Texture, Vector2u(14, 8), 0.2f, Vector2f(1748, 50));
				Flowmon_Body.push_back(Flowmon1);
				Flowmon Flowmon2(&Flowmon_Texture, Vector2u(14, 8), 0.2f, Vector2f(1272, 150));
				Flowmon_Body.push_back(Flowmon2);
				Text_String GUI1("Name", GUI_Font, Vector2f(GUI_Place.getViewport().left + 200, GUI_Place.getViewport().top + 20), 25, Color::White, 2, Color::Black);
				GUI.push_back(GUI1);
				Text_String GUI2("HP", GUI_Font, Vector2f(GUI_Place.getViewport().left + 200, GUI_Place.getViewport().top + 70), 25, Color::Red, 2, Color::Black);
				GUI.push_back(GUI2);
				Text_String GUI3("Score", GUI_Font, Vector2f(GUI_Place.getViewport().left + 500, GUI_Place.getViewport().top + 70), 25, Color::Magenta, 2, Color::Black);
				GUI.push_back(GUI3);
				Background3.setTexture(&SStage_Background);
				Background3.setPosition(0, 0);
				Camera.setCenter(Camera.getSize().x / 2, 645 / 2);
				onetime = false;
			}

			if (Player.GetPosition().x >= Background3.getPosition().x + Camera.getSize().x / 2 && Player.GetPosition().x <= Background3.getPosition().x + Background3.getSize().x - Camera.getSize().x / 2)
				Camera.setCenter(Player.GetPosition().x, 645 / 2);
			/*Window Event*/

			while (Window.pollEvent(Window_Event)) {}
			if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			{
				SStage.stop();
				scoreRank[0] = score;
				int i, j, temp;
				user[0] = str;
				scoreFile.open("Sprite/Text/Highscore.txt");
				scoreFile >> scoreRank[1] >> scoreRank[2] >> scoreRank[3] >> scoreRank[4] >> scoreRank[5];
				scoreFile.close();

				userFile.open("Sprite/Text/Username.txt");
				userFile >> user[1] >> user[2] >> user[3] >> user[4] >> user[5];
				userFile.close();
				std::string strtemp;
				for (i = 0; i < 6; i++)
				{
					for (j = i + 1; j < 6; j++)
					{
						if (scoreRank[i] < scoreRank[j])
						{
							temp = scoreRank[i];
							scoreRank[i] = scoreRank[j];
							scoreRank[j] = temp;
							strtemp = user[i];
							user[i] = user[j];
							user[j] = strtemp;
						}
					}
				}
				writeUser.open("Sprite/Text/Username.txt");
				for (i = 0; i < 5; i++)
				{
					writeUser << user[i] << std::endl;
				}
				writeUser.close();

				writeScore.open("Sprite/Text/Highscore.txt");
				for (i = 0; i < 5; i++)
				{
					writeScore << scoreRank[i] << std::endl;
				}
				writeScore.close();
				Main_Theme.play();
				screen = Screen::Menu;
			}

			/*Bullet_Collision*/

			for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Metalbeing_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Metalbeing_Body[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Metalbeing_Body[j].isDying)
						{
							Metalbeing_Body[j].Metalbeing_Health -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Metalbeing_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Metalbeing_Body[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Metalbeing_Body[j].isDying)
						{
							Metalbeing_Body[j].Metalbeing_Health -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Flowmon_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Flowmon_Body[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Flowmon_Body[j].isDying)
						{
							Flowmon_Body[j].Flowmon_Health -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Flowmon_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Flowmon_Body[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Flowmon_Body[j].isDying)
						{
							Flowmon_Body[j].Flowmon_Health -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Gloomthing_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Gloomthing_Body[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Gloomthing_Body[j].isDying)
						{
							Gloomthing_Body[j].Gloomthing_Health -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Gloomthing_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Gloomthing_Body[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Gloomthing_Body[j].isDying)
						{
							Gloomthing_Body[j].Gloomthing_Health -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Povy_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Povy_Body[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Povy_Body[j].isDying)
						{
							Povy_Body[j].Povy_Health -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Povy_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Povy_Body[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Povy_Body[j].isDying)
						{
							Povy_Body[j].Povy_Health -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}

			/*Platform_Collision*/

			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < bulletVec.size(); j++)
				{
					if (Collision::PixelPerfectTest(bulletVec[j].Get_Body(), Platforms[i].Body(), 0) || bulletVec[j].Get_Body().getPosition().x - abs(bulletVec[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || bulletVec[j].Get_Body().getPosition().x + abs(bulletVec[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || bulletVec[j].Get_Body().getPosition().y + abs(bulletVec[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || bulletVec[j].Get_Body().getPosition().y - abs(bulletVec[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						if (!Player.isWave)
						{
							bulletVec.erase(bulletVec.begin() + j);
							break;
						}
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < bullet.size(); j++)
				{
					if (Collision::PixelPerfectTest(bullet[j].Get_Body(), Platforms[i].Body(), 0) || bullet[j].Get_Body().getPosition().x - abs(bullet[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || bullet[j].Get_Body().getPosition().x + abs(bullet[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || bullet[j].Get_Body().getPosition().y + abs(bullet[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || bullet[j].Get_Body().getPosition().y - abs(bullet[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						bullet.erase(bullet.begin() + j);
						break;
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Items.size(); j++)
				{
					if (Collision::PixelPerfectTest(Items[j].Item_Projectiles.Get_Body(), Platforms[i].Body(), 0))
					{
						Items[j].Item_Projectiles.isMoving = false;
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Povy_Body.size(); j++)
				{
					if (!Collision::PixelPerfectTest(Povy_Body[j].Get_Body(), Platforms[i].Body(), 0))
					{
						Povy_Body[j].Get_Body().move(0, 98.1*Difference);
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Povy_Ball.size(); j++)
				{
					if (Collision::PixelPerfectTest(Povy_Ball[j].Get_Body(), Platforms[i].Body(), 0) || Povy_Ball[j].Get_Body().getPosition().x - abs(Povy_Ball[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || Povy_Ball[j].Get_Body().getPosition().x + abs(Povy_Ball[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || Povy_Ball[j].Get_Body().getPosition().y + abs(Povy_Ball[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || Povy_Ball[j].Get_Body().getPosition().y - abs(Povy_Ball[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						Povy_Ball.erase(Povy_Ball.begin() + j);
						break;
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Gloomthing_Body.size(); j++)
				{
					if (!Collision::PixelPerfectTest(Gloomthing_Body[j].Get_Body(), Platforms[i].Body(), 0))
					{
						Gloomthing_Body[j].Get_Body().move(0, 98.1*Difference);
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Flowmon_Body.size(); j++)
				{
					if (!Collision::PixelPerfectTest(Flowmon_Body[j].Get_Body(), Platforms[i].Body(), 0))
					{
						Flowmon_Body[j].Get_Body().move(0, 98.1*Difference);
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Flowmon_Ball.size(); j++)
				{
					if (Collision::PixelPerfectTest(Flowmon_Ball[j].Get_Body(), Platforms[i].Body(), 0) || Flowmon_Ball[j].Get_Body().getPosition().x - abs(Flowmon_Ball[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || Flowmon_Ball[j].Get_Body().getPosition().x + abs(Flowmon_Ball[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || Flowmon_Ball[j].Get_Body().getPosition().y + abs(Flowmon_Ball[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || Flowmon_Ball[j].Get_Body().getPosition().y - abs(Flowmon_Ball[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						Flowmon_Ball.erase(Flowmon_Ball.begin() + j);
						break;
					}
				}
			}

			/*Player Collision*/

			for (int i = 0; i < Items.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Items[i].Item_Projectiles.Get_Body(), 0))
				{
					if (!Player.isDying)
					{
						if (Items[i].isArrow)
						{
							Player.isWave = false;
							Player.isDirect = false;
							Player.isLaser = false;
							Player.isLob = false;
							Player.isArrow = true;
							Time_Items.clear();
							ItemSound.play();
							Count_Item = Total_Item;
							Item NewItems(&Arrow_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isLob)
						{
							ItemSound.play();
							Player.isWave = false;
							Player.isDirect = false;
							Player.isLaser = false;
							Player.isLob = true;
							Player.isArrow = false;
							Count_Item = Total_Item;
							Time_Items.clear();
							Item NewItems(&Lob_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isWave)
						{
							ItemSound.play();
							Player.isWave = true;
							Player.isDirect = false;
							Player.isLaser = false;
							Player.isLob = false;
							Player.isArrow = false;
							Time_Items.clear();
							Count_Item = Total_Item;
							Item NewItems(&Wave_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isLaser)
						{
							ItemSound.play();
							Player.isWave = false;
							Player.isDirect = false;
							Player.isLaser = true;
							Player.isLob = false;
							Player.isArrow = false;
							Time_Items.clear();
							Count_Item = Total_Item;
							Item NewItems(&Laser_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isShield) { isShieldON = true; Count_Shield = Total_Shield; }
						else if (Items[i].isFood) { Player.HP += Items[i].Health; Munch.play(); }
						else { SoulSound.play(); }
						Items[i].Item_Visible = false;
						score += Items[i].Score;
						Items.erase(Items.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < Povy_Ball.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Povy_Ball[i].Get_Body(), 0))
				{
					if (!Player.isHurting && !Player.isDying)
					{
						Player.HP -= Povy_Ball[i].Damage;
						Player.Player_Animation.Visible = true;
						Player.isHurting = true;
						Player.Player_Animation.Current_Image.x = 0;
						Povy_Ball.erase(Povy_Ball.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < Povy_Ball.size(); i++)
			{
				if (Collision::PixelPerfectTest(Povy_Ball[i].Get_Body(), Shield, 0))
				{
					Povy_Ball.erase(Povy_Ball.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Povy_Body.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Povy_Body[i].Get_Body(), 0) && !Player.isHurting && !Player.isDying)
				{
					Player.HP -= 5;
					Player.isHurting = true;
					Player.Player_Animation.Visible = true;
					Player.Player_Animation.Current_Image.x = 0;
				}
			}
			for (int i = 0; i < Flowmon_Ball.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Flowmon_Ball[i].Get_Body(), 0))
				{
					if (!Player.isHurting && !Player.isDying)
					{
						Player.HP -= Flowmon_Ball[i].Damage;
						Player.Player_Animation.Visible = true;
						Player.isHurting = true;
						Player.Player_Animation.Current_Image.x = 0;
						Flowmon_Ball.erase(Flowmon_Ball.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < Flowmon_Ball.size(); i++)
			{
				if (Collision::PixelPerfectTest(Flowmon_Ball[i].Get_Body(), Shield, 0))
				{
					Flowmon_Ball.erase(Flowmon_Ball.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Flowmon_Body.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Flowmon_Body[i].Get_Body(), 0) && !Player.isHurting && !Player.isDying)
				{
					Player.HP -= 5;
					Player.isHurting = true;
					Player.Player_Animation.Visible = true;
					Player.Player_Animation.Current_Image.x = 0;
				}
			}
			for (int i = 0; i < Gloomthing_Body.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Gloomthing_Body[i].Get_Body(), 0) && !Player.isHurting && !Player.isDying)
				{
					Player.HP -= 5;
					Player.isHurting = true;
					Player.Player_Animation.Visible = true;
					Player.Player_Animation.Current_Image.x = 0;
				}
			}
			for (int i = 0; i < Warpgate_Body.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Warpgate_Body[i].Get_Body()) && !Player.isHurting && !Player.isDying)
				{
					if (Keyboard::isKeyPressed(Keyboard::Space))
					{
						screen = Warpgate_Body[i].to;
						onetime = true;
						break;
					}
				}
			}

			/*Items*/

			for (int i = 0; i < Metalbeing_Body.size(); i++)
			{
				if (!Metalbeing_Body[i].Metalbeing_Visible)
				{
					num = rand() % 5;
					if (num == 0)
					{
						Item newItem(&Shield_Texture, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isShield = true;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					else if (num == 1)
					{
						Item newItem(&Arrow_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isArrow = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					else if (num == 2)
					{
						Item newItem(&Laser_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isLaser = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					else if (num == 3)
					{
						Item newItem(&Wave_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isWave = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					else if (num == 4)
					{
						Item newItem(&Lob_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isLob = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					Metalbeing_Body.erase(Metalbeing_Body.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Povy_Body.size(); i++)
			{
				if (!Povy_Body[i].Povy_Visible)
				{
					score += Povy_Body[i].Score;
					Text_String newScore(std::to_string(Povy_Body[i].Score), Score_Font, Vector2f(Povy_Body[i].Get_Body().getPosition().x, Povy_Body[i].Get_Body().getPosition().y - 20), 20, Color::Yellow, 1, Color::Black);
					Enemy_Score.push_back(newScore);
					num = rand() % 12 + 1;
					if (num >= 8)
					{
						Item newItem(&Lemon, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 15);
						newItem.Item_Projectiles.setPos(Vector2f(Povy_Body[i].Get_Body().getPosition().x, Povy_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 10;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					else if (num >= 6)
					{
						Item newItem(&Cherry, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 20);
						newItem.Item_Projectiles.setPos(Vector2f(Povy_Body[i].Get_Body().getPosition().x, Povy_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 20;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					else
					{
						Item newItem(&Corn_Stick, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 10);
						newItem.Item_Projectiles.setPos(Vector2f(Povy_Body[i].Get_Body().getPosition().x, Povy_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 40;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					num = rand() % 5 + 1;
					for (int j = 1; j <= num; j++)
					{
						Item newItem(&Soul, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(4, 1), 0.2f, 5);
						newItem.Item_Projectiles.setPos(Vector2f(Povy_Body[i].Get_Body().getPosition().x, Povy_Body[i].Get_Body().getPosition().y - 20));
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					Povy_Body.erase(Povy_Body.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Flowmon_Body.size(); i++)
			{
				if (!Flowmon_Body[i].Flowmon_Visible)
				{
					score += Flowmon_Body[i].Score;
					Text_String newScore(std::to_string(Flowmon_Body[i].Score), Score_Font, Vector2f(Flowmon_Body[i].Get_Body().getPosition().x, Flowmon_Body[i].Get_Body().getPosition().y - 20), 20, Color::Yellow, 1, Color::Black);
					Enemy_Score.push_back(newScore);
					num = rand() % 12 + 1;
					if (num >= 8)
					{
						Item newItem(&Orange, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 15);
						newItem.Item_Projectiles.setPos(Vector2f(Flowmon_Body[i].Get_Body().getPosition().x, Flowmon_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 50;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					else if (num >= 6)
					{
						Item newItem(&Onigiri, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 20);
						newItem.Item_Projectiles.setPos(Vector2f(Flowmon_Body[i].Get_Body().getPosition().x, Flowmon_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 35;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					else
					{
						Item newItem(&Green_Apple, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 10);
						newItem.Item_Projectiles.setPos(Vector2f(Flowmon_Body[i].Get_Body().getPosition().x, Flowmon_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 15;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					num = rand() % 5 + 1;
					for (int j = 1; j <= num; j++)
					{
						Item newItem(&Soul, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(4, 1), 0.2f, 5);
						newItem.Item_Projectiles.setPos(Vector2f(Flowmon_Body[i].Get_Body().getPosition().x, Flowmon_Body[i].Get_Body().getPosition().y - 20));
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					Flowmon_Body.erase(Flowmon_Body.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Gloomthing_Body.size(); i++)
			{
				if (Gloomthing_Body[i].Gloomthing_Dying)
				{
					score += Gloomthing_Body[i].Score;
					Text_String newScore(std::to_string(Gloomthing_Body[i].Score), Score_Font, Vector2f(Gloomthing_Body[i].Get_Body().getPosition().x, Gloomthing_Body[i].Get_Body().getPosition().y - 20), 20, Color::Yellow, 1, Color::Black);
					Enemy_Score.push_back(newScore);
					num = rand() % 21+10;
					for (int j = 1; j <= num; j++)
					{
						Item newItem(&Soul, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(4, 1), 0.2f, 5);
						newItem.Item_Projectiles.setPos(Vector2f(Gloomthing_Body[i].Get_Body().getPosition().x, Gloomthing_Body[i].Get_Body().getPosition().y - 20));
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					Gloomthing_Body.erase(Gloomthing_Body.begin() + i);
					break;
				}
			}

			/*Items Active*/
			if (isShieldON)
			{
				Shield.setPosition(Player.GetPosition());
			}
			else
			{
				Shield.setPosition(-100, -100);
			}
			if (Total_Item - Count_Item >= 10.0f)
			{
				Player.isArrow = false;
				Player.isLaser = false;
				Player.isLob = false;
				Player.isWave = false;
				Player.isDirect = true;
				Total_Item = 0;
				Count_Item = 0;
				Time_Items.clear();
			}
			if (Total_Shield - Count_Shield >= 10.0f)
			{
				isShieldON = false;
				Total_Shield = 0;
				Count_Shield = 0;
			}

			Window.clear();

			/*GUI_View*/

			Window.setView(GUI_Place);
			Window.draw(GUI_Background);
			for (int i = 0; i < GUI.size(); i++)
			{
				GUI[i].Draw(Window);
			}
			Score.Update_Text(std::to_string(score));
			Health.Update_Text(std::to_string(Player.HP) + "/100");
			Window.draw(Empty_Bar);
			Window.draw(HP_Bar);
			Score.Draw(Window);
			Health.Draw(Window);
			Score_Soul.Item_Projectiles.setPos(Vector2f(GUI_Place.getViewport().left + 620.0f, GUI_Place.getViewport().top + 80.0f));
			Score_Soul.Update(Difference, Window);
			if (Player.isArrow || Player.isLob || Player.isLaser || Player.isWave)
			{
				for (int i = 0; i < Time_Items.size(); i++)
				{
					Time_Items[i].Item_Projectiles.setPos(Vector2f(GUI_Place.getViewport().left + 1200, GUI_Place.getViewport().top + 42));
					Time_Items[i].Update(Difference, Window);
				}
				Item_Time.Text_Body.setPosition(Vector2f(GUI_Place.getViewport().left + 1250, GUI_Place.getViewport().top + 20));
				Item_Time.Update_Text(std::to_string(10 - abs((int)Count_Item - (int)Total_Item)));
				Window.draw(Item_Time.Text_Body);
			}
			if (isShieldON)
			{
				Time_Shield.Item_Projectiles.Get_Body().setScale(2, 2);
				Time_Shield.Item_Projectiles.setPos(Vector2f(GUI_Place.getViewport().left + 1200, GUI_Place.getViewport().top + 110));
				Time_Shield.Update(Difference, Window);
				Shield_Time.Text_Body.setPosition(Vector2f(GUI_Place.getViewport().left + 1250, GUI_Place.getViewport().top + 85));
				Shield_Time.Update_Text(std::to_string(10 - abs((int)Count_Shield - (int)Total_Shield)));
				Window.draw(Shield_Time.Text_Body);
			}
			Window.draw(textUser);

			/*Default_View*/

			Window.setView(Camera);
			Mouse_Position = Window.mapPixelToCoords(Mouse::getPosition(Window));
			Window.draw(Background3);
			for (int i = 0; i < Platforms.size(); i++)
			{
				Platforms[i].Draw(Window);
			}
			for (int i = 0; i < Metalbeing_Body.size(); i++)
			{
				Metalbeing_Body[i].Update(Difference, Player.GetPosition(), Window, Platforms);
			}
			for (int i = 0; i < Povy_Body.size(); i++)
			{
				Povy_Body[i].Update(Difference, Player.GetPosition(), Povy_Ball, Window, Platforms);
			}
			for (int i = 0; i < Gloomthing_Body.size(); i++)
			{
				Gloomthing_Body[i].Gloomthing_Update(Difference, Player.GetPosition(), Window);
			}
			for (int i = 0; i < Flowmon_Body.size(); i++)
			{
				Flowmon_Body[i].Flowmon_Update(Difference, Player.GetPosition(),Flowmon_Ball,Window);
			}
			for (int i = 0; i < Items.size(); i++)
			{
				Items[i].Update(Difference, Window);
			}
			for (int i = 0; i < Enemy_Score.size(); i++)
			{
				Enemy_Score[i].Update(Difference, Window);
			}
			for (int i = 0; i < Warpgate_Body.size(); i++)
			{
				Warpgate_Body[i].Update(Difference, Window);
			}
			Player.Update(Difference, Mouse_Position, Window, Platforms, bulletVec, bullet);
			if (isShieldON)
			{
				Window.draw(Shield);
			}
			Mouse_Cursor.setPosition(Mouse_Position);
			Window.draw(Mouse_Cursor);

			/*Chacter_View*/

			Window.setView(Character);
			Window.draw(Background3);
			for (int i = 0; i < Platforms.size(); i++)
			{
				Platforms[i].Draw(Window);
			}
			if (Player.Player_Visible)
				Player.Draw(Window);
			Window.display();
			break;
		}
		case Screen::Second_Boss:
		{
			if (Player.HP <= 0)
			{
				Die.play();
				SBoss.stop();
				Main_Theme.play();
				scoreRank[0] = score;
				screen = Screen::Scoreboard;
				Player.HP = 0; int i, j, temp;
				user[0] = str;
				scoreFile.open("Sprite/Text/Highscore.txt");
				scoreFile >> scoreRank[1] >> scoreRank[2] >> scoreRank[3] >> scoreRank[4] >> scoreRank[5];
				scoreFile.close();

				userFile.open("Sprite/Text/Username.txt");
				userFile >> user[1] >> user[2] >> user[3] >> user[4] >> user[5];
				userFile.close();
				std::string strtemp;
				for (i = 0; i < 6; i++)
				{
					for (j = i + 1; j < 6; j++)
					{
						if (scoreRank[i] < scoreRank[j])
						{
							temp = scoreRank[i];
							scoreRank[i] = scoreRank[j];
							scoreRank[j] = temp;
							strtemp = user[i];
							user[i] = user[j];
							user[j] = strtemp;
						}
					}
				}
				writeUser.open("Sprite/Text/Username.txt");
				for (i = 0; i < 5; i++)
				{
					writeUser << user[i] << std::endl;
				}
				writeUser.close();

				writeScore.open("Sprite/Text/Highscore.txt");
				for (i = 0; i < 5; i++)
				{
					writeScore << scoreRank[i] << std::endl;
				}
				writeScore.close();
			}
			Event Window_Event;
			Total_Shield += Difference;
			Total_Item += Difference;
			Time_Spawn += Difference;

			/*Default_View*/

			Camera.setViewport(FloatRect(0, 0, 1, 625.0 / Window.getSize().y));
			Camera.setSize(Window.getSize().x, Window.getSize().y* 625.0 / Window.getSize().y);

			/*Character_View*/

			Character.setViewport(FloatRect(25.0 / Window.getSize().x, 645.0 / Window.getSize().y, 150.0 / Window.getSize().x, 103.0 / Window.getSize().y));
			Character.setSize(Window.getSize().x*150.0 / Window.getSize().x, Window.getSize().y*103.0 / Window.getSize().y);
			Character.setCenter(Player.GetPosition().x, Player.GetPosition().y + 15);

			/*GUI_View*/

			GUI_Place.setViewport(FloatRect(0, 625.0 / Window.getSize().y, 1, 143.0 / Window.getSize().y));
			GUI_Place.setSize(Window.getSize().x, Window.getSize().y*143.0 / Window.getSize().y);
			GUI_Place.setCenter(GUI_Place.getSize().x / 2, GUI_Place.getSize().y / 2);

			GUI_Background.setSize(GUI_Place.getSize());
			Empty_Bar.setPosition(Vector2f(GUI_Place.getViewport().left + 250, GUI_Place.getViewport().top + 75));
			GUI_Background.setPosition(GUI_Place.getViewport().left, GUI_Place.getViewport().top);
			HP_Bar.setPosition(Vector2f(GUI_Place.getViewport().left + 250, GUI_Place.getViewport().top + 75));
			HP_Bar.setSize(Vector2f(Player.HP*Empty_Bar.getSize().x / 100.0, 20));

			textUser.setPosition(Vector2f(GUI_Place.getViewport().left + 310, GUI_Place.getViewport().top + 20));
			textUser.setFillColor(Color::Black);
			textUser.setCharacterSize(25);
			if (onetime)
			{
				GUI.clear();
				Enemy_Score.clear();
				Platforms.clear();
				bullet.clear();
				bulletVec.clear();
				Metalbeing_Body.clear();
				Items.clear();
				Vexling_Body.clear();
				Black_Bile.clear();
				Black_Explosion.clear();
				Piercing.clear();
				Shots.clear();
				Time_Items.clear();
				Warpgate_Body.clear();

				SStage.stop();
				SBoss.play();
				Floor NewPlatforms(&SBoss_Floor, Vector2f(0, 0));
				Platforms.push_back(NewPlatforms);
				Player.getBody().setPosition(200, -50);
				Vexling NewVexling(&Vexling_Texture, Vector2u(14,14), 0.2f, Vector2f(100, 100));
				Vexling_Body.push_back(NewVexling);
				Metalbeing NewMetalbeing(&Metalbeing_Texture, Vector2u(6, 6), 0.2f, Vector2f(rand() % 767 + 400, 450), Vector2f(500, 500));
				Metalbeing_Body.push_back(NewMetalbeing);
				Text_String GUI1("Name", GUI_Font, Vector2f(GUI_Place.getViewport().left + 200, GUI_Place.getViewport().top + 20), 25, Color::White, 2, Color::Black);
				GUI.push_back(GUI1);
				Text_String GUI2("HP", GUI_Font, Vector2f(GUI_Place.getViewport().left + 200, GUI_Place.getViewport().top + 70), 25, Color::Red, 2, Color::Black);
				GUI.push_back(GUI2);
				Text_String GUI3("Score", GUI_Font, Vector2f(GUI_Place.getViewport().left + 500, GUI_Place.getViewport().top + 70), 25, Color::Magenta, 2, Color::Black);
				GUI.push_back(GUI3);
				Background4.setTexture(&SBoss_Background);
				Background4.setPosition(0, 0);
				Camera.setCenter(Platforms[0].Get_Size().width / 2.0f, Platforms[0].Get_Size().height / 2.0f);
				Time_Spawn = 0;
				Stop = false;
				onetime = false;
			}

			if (Time_Spawn >= 20.0f && !Stop)
			{
				Metalbeing NewMetalbeing(&Metalbeing_Texture, Vector2u(6, 6), 0.2f, Vector2f(rand() % 767 + 400, 450), Vector2f(500, 500));
				Metalbeing_Body.push_back(NewMetalbeing);
				Time_Spawn = 0;
			}

			/*Window Event*/

			while (Window.pollEvent(Window_Event)) {}
			if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			{
				SBoss.stop();
				scoreRank[0] = score;
				int i, j, temp;
				user[0] = str;
				scoreFile.open("Sprite/Text/Highscore.txt");
				scoreFile >> scoreRank[1] >> scoreRank[2] >> scoreRank[3] >> scoreRank[4] >> scoreRank[5];
				scoreFile.close();

				userFile.open("Sprite/Text/Username.txt");
				userFile >> user[1] >> user[2] >> user[3] >> user[4] >> user[5];
				userFile.close();
				std::string strtemp;
				for (i = 0; i < 6; i++)
				{
					for (j = i + 1; j < 6; j++)
					{
						if (scoreRank[i] < scoreRank[j])
						{
							temp = scoreRank[i];
							scoreRank[i] = scoreRank[j];
							scoreRank[j] = temp;
							strtemp = user[i];
							user[i] = user[j];
							user[j] = strtemp;
						}
					}
				}
				writeUser.open("Sprite/Text/Username.txt");
				for (i = 0; i < 5; i++)
				{
					writeUser << user[i] << std::endl;
				}
				writeUser.close();

				writeScore.open("Sprite/Text/Highscore.txt");
				for (i = 0; i < 5; i++)
				{
					writeScore << scoreRank[i] << std::endl;
				}
				writeScore.close();
				Main_Theme.play();
				screen = Screen::Menu;
			}

			/*Bullet_Collision*/

			for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Metalbeing_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Metalbeing_Body[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Metalbeing_Body[j].isDying)
						{
							Metalbeing_Body[j].Metalbeing_Health -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Metalbeing_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Metalbeing_Body[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Metalbeing_Body[j].isDying)
						{
							Metalbeing_Body[j].Metalbeing_Health -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Vexling_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Vexling_Body[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Vexling_Body[j].isDying)
						{
							Vexling_Body[j].Vexling_Health -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Vexling_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Vexling_Body[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Vexling_Body[j].isDying)
						{
							Vexling_Body[j].Vexling_Health -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}

			/*Platform_Collision*/

			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < bulletVec.size(); j++)
				{
					if (Collision::PixelPerfectTest(bulletVec[j].Get_Body(), Platforms[i].Body(), 0) || bulletVec[j].Get_Body().getPosition().x - abs(bulletVec[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || bulletVec[j].Get_Body().getPosition().x + abs(bulletVec[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || bulletVec[j].Get_Body().getPosition().y + abs(bulletVec[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || bulletVec[j].Get_Body().getPosition().y - abs(bulletVec[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						if (!Player.isWave)
						{
							bulletVec.erase(bulletVec.begin() + j);
							break;
						}
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Black_Bile.size(); j++)
				{
					if (Collision::PixelPerfectTest(Black_Bile[j].Get_Body(), Platforms[i].Body(), 0) || Black_Bile[j].Get_Body().getPosition().x - abs(Black_Bile[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || Black_Bile[j].Get_Body().getPosition().x + abs(Black_Bile[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || Black_Bile[j].Get_Body().getPosition().y + abs(Black_Bile[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || Black_Bile[j].Get_Body().getPosition().y - abs(Black_Bile[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						Black_Bile.erase(Black_Bile.begin() + j);
						break;
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Items.size(); j++)
				{
					if (Collision::PixelPerfectTest(Items[j].Item_Projectiles.Get_Body(), Platforms[i].Body(), 0))
					{
						Items[j].Item_Projectiles.isMoving = false;
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Shots.size(); j++)
				{
					if (Collision::PixelPerfectTest(Shots[j].Get_Body(), Platforms[i].Body(), 0) || Shots[j].Get_Body().getPosition().x - abs(Shots[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || Shots[j].Get_Body().getPosition().x + abs(Shots[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || Shots[j].Get_Body().getPosition().y + abs(Shots[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || Shots[j].Get_Body().getPosition().y - abs(Shots[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						Shots.erase(Shots.begin() + j);
						break;
					}
				}
			}

			/*Player Collision*/

			for (int i = 0; i < Items.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Items[i].Item_Projectiles.Get_Body(), 0))
				{
					if (!Player.isDying)
					{
						if (Items[i].isArrow)
						{
							Player.isWave = false;
							Player.isDirect = false;
							Player.isLaser = false;
							Player.isLob = false;
							Player.isArrow = true;
							Time_Items.clear();
							ItemSound.play();
							Count_Item = Total_Item;
							Item NewItems(&Arrow_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isLob)
						{
							ItemSound.play();
							Player.isWave = false;
							Player.isDirect = false;
							Player.isLaser = false;
							Player.isLob = true;
							Player.isArrow = false;
							Count_Item = Total_Item;
							Time_Items.clear();
							Item NewItems(&Lob_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isWave)
						{
							ItemSound.play();
							Player.isWave = true;
							Player.isDirect = false;
							Player.isLaser = false;
							Player.isLob = false;
							Player.isArrow = false;
							Time_Items.clear();
							Count_Item = Total_Item;
							Item NewItems(&Wave_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isLaser)
						{
							ItemSound.play();
							Player.isWave = false;
							Player.isDirect = false;
							Player.isLaser = true;
							Player.isLob = false;
							Player.isArrow = false;
							Time_Items.clear();
							Count_Item = Total_Item;
							Item NewItems(&Laser_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isShield) { isShieldON = true; Count_Shield = Total_Shield; }
						else if (Items[i].isFood) { Player.HP += Items[i].Health; Munch.play(); }
						else { SoulSound.play(); }
						Items[i].Item_Visible = false;
						score += Items[i].Score;
						Items.erase(Items.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < Black_Explosion.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Black_Explosion[i].Explosion_Body, 0))
				{
					if (Black_Explosion[i].Damagable)
					{
						if (!Player.isHurting && !Player.isDying)
						{
							Player.HP -= Black_Explosion[i].Damage;
							Player.Player_Animation.Visible = true;
							Player.isHurting = true;
							Player.Player_Animation.Current_Image.x = 0;
						}
					}
				}
			}
			for (int i = 0; i < Piercing.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Piercing[i].Explosion_Body, 0))
				{
					if (Piercing[i].Damagable)
					{
						if (!Player.isHurting && !Player.isDying)
						{
							Player.HP -= Piercing[i].Damage;
							Player.Player_Animation.Visible = true;
							Player.isHurting = true;
							Player.Player_Animation.Current_Image.x = 0;
						}
					}
				}
			}
			for (int i = 0; i < Black_Bile.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Black_Bile[i].Get_Body(), 0))
				{
					if (!Player.isHurting && !Player.isDying)
					{
						Player.HP -= Black_Bile[i].Damage;
						Player.Player_Animation.Visible = true;
						Player.isHurting = true;
						Player.Player_Animation.Current_Image.x = 0;
					}
					Black_Bile.erase(Black_Bile.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Black_Bile.size(); i++)
			{
				if (Collision::PixelPerfectTest(Black_Bile[i].Get_Body(), Shield, 0))
				{
					Black_Bile.erase(Black_Bile.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Shots.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Shots[i].Get_Body(), 0))
				{
					if (!Player.isHurting && !Player.isDying)
					{
						Player.HP -= Shots[i].Damage;
						Player.Player_Animation.Visible = true;
						Player.isHurting = true;
						Player.Player_Animation.Current_Image.x = 0;
					}
					Shots.erase(Shots.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Shots.size(); i++)
			{
				if (Collision::PixelPerfectTest(Shots[i].Get_Body(), Shield, 0))
				{
					Shots.erase(Shots.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Warpgate_Body.size(); i++)
			{
				if (Collision::PixelPerfectTest(Warpgate_Body[i].Get_Body(), Player.getBody(), 0))
				{
					if (Keyboard::isKeyPressed(Keyboard::Space))
					{
						screen = Warpgate_Body[i].to;
						onetime = true;
						break;
					}
				}
			}

			/*Items*/

			for (int i = 0; i < Metalbeing_Body.size(); i++)
			{
				if (!Metalbeing_Body[i].Metalbeing_Visible)
				{
					num = rand() % 5;
					if (num == 0)
					{
						Item newItem(&Shield_Texture, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isShield = true;
						newItem.Item_Projectiles.Get_Body().setScale(2,2);
						Items.push_back(newItem);
					}
					else if (num == 1)
					{
						Item newItem(&Arrow_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isArrow = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					else if (num == 2)
					{
						Item newItem(&Laser_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isLaser = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					else if (num == 3)
					{
						Item newItem(&Wave_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isWave = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					else if (num == 4)
					{
						Item newItem(&Lob_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isLob = true;
						Items.push_back(newItem);
					}
					Metalbeing_Body.erase(Metalbeing_Body.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Vexling_Body.size(); i++)
			{
				if (Vexling_Body[i].Vexling_Dying)
				{
					score += Vexling_Body[i].Score;
					Text_String newScore(std::to_string(Vexling_Body[i].Score), Score_Font, Vector2f(Vexling_Body[i].Get_Body().getPosition().x, Vexling_Body[i].Get_Body().getPosition().y - 20), 20, Color::Yellow, 1, Color::Black);
					Enemy_Score.push_back(newScore);
					num = rand() % 12 + 1;
					if (num >= 8)
					{
						Item newItem(&Apple, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 15);
						newItem.Item_Projectiles.setPos(Vector2f(Vexling_Body[i].Get_Body().getPosition().x, Vexling_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 30;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					else if (num >= 6)
					{
						Item newItem(&Cake, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 20);
						newItem.Item_Projectiles.setPos(Vector2f(Vexling_Body[i].Get_Body().getPosition().x, Vexling_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 100;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					else
					{
						Item newItem(&Lemon, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 10);
						newItem.Item_Projectiles.setPos(Vector2f(Vexling_Body[i].Get_Body().getPosition().x, Vexling_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 10;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					num = rand() % 41 + 10;
					for (int j = 1; j <= num; j++)
					{
						Item newItem(&Soul, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(4, 1), 0.2f, 5);
						newItem.Item_Projectiles.setPos(Vector2f(Vexling_Body[i].Get_Body().getPosition().x, Vexling_Body[i].Get_Body().getPosition().y - 20));
						newItem.Item_Projectiles.Get_Body().setScale(1.05,1.05);
						Items.push_back(newItem);
					}
					Stop = true;
					WarpGate WarpGate1(&Warpgate_Texture, Vector2f(1252, 511), Screen::Third_Stage, Vector2u(20, 1), 0.2f);
					Warpgate_Body.push_back(WarpGate1);
					Vexling_Body.erase(Vexling_Body.begin() + i);
					break;
				}
			}

			/*Items Active*/

			if (isShieldON)
			{
				Shield.setPosition(Player.GetPosition());
			}
			else
			{
				Shield.setPosition(-100, -100);
			}
			if (Total_Item - Count_Item >= 10.0f)
			{
				Player.isArrow = false;
				Player.isLaser = false;
				Player.isLob = false;
				Player.isWave = false;
				Player.isDirect = true;
				Total_Item = 0;
				Count_Item = 0;
				Time_Items.clear();
			}
			if (Total_Shield - Count_Shield >= 10.0f)
			{
				isShieldON = false;
				Total_Shield = 0;
				Count_Shield = 0;
			}
			Window.clear();

			/*GUI_View*/

			Window.setView(GUI_Place);
			Window.draw(GUI_Background);
			for (int i = 0; i < GUI.size(); i++)
			{
				GUI[i].Draw(Window);
			}
			Score.Update_Text(std::to_string(score));
			Health.Update_Text(std::to_string(Player.HP) + "/100");
			Window.draw(Empty_Bar);
			Window.draw(HP_Bar);
			Score.Draw(Window);
			Health.Draw(Window);
			Score_Soul.Item_Projectiles.setPos(Vector2f(GUI_Place.getViewport().left + 620.0f, GUI_Place.getViewport().top + 80.0f));
			Score_Soul.Update(Difference, Window);
			if (Player.isArrow || Player.isLob || Player.isLaser || Player.isWave)
			{
				for (int i = 0; i < Time_Items.size(); i++)
				{
					Time_Items[i].Item_Projectiles.setPos(Vector2f(GUI_Place.getViewport().left + 1200, GUI_Place.getViewport().top + 42));
					Time_Items[i].Update(Difference, Window);
				}
				Item_Time.Text_Body.setPosition(Vector2f(GUI_Place.getViewport().left + 1250, GUI_Place.getViewport().top + 20));
				Item_Time.Update_Text(std::to_string(10 - abs((int)Count_Item - (int)Total_Item)));
				Window.draw(Item_Time.Text_Body);
			}
			if (isShieldON)
			{
				Time_Shield.Item_Projectiles.Get_Body().setScale(2, 2);
				Time_Shield.Item_Projectiles.setPos(Vector2f(GUI_Place.getViewport().left + 1200, GUI_Place.getViewport().top + 110));
				Time_Shield.Update(Difference, Window);
				Shield_Time.Text_Body.setPosition(Vector2f(GUI_Place.getViewport().left + 1250, GUI_Place.getViewport().top + 85));
				Shield_Time.Update_Text(std::to_string(10 - abs((int)Count_Shield - (int)Total_Shield)));
				Window.draw(Shield_Time.Text_Body);
			}
			Window.draw(textUser);

			/*Default_View*/

			Window.setView(Camera);
			Mouse_Position = Window.mapPixelToCoords(Mouse::getPosition(Window));
			Window.draw(Background4);
			for (int i = 0; i < Platforms.size(); i++)
			{
				Platforms[i].Draw(Window);
			}
			for (int i = 0; i < Metalbeing_Body.size(); i++)
			{
				Metalbeing_Body[i].Update(Difference, Player.GetPosition(), Window, Platforms);
			}
			for (int i = 0; i < Items.size(); i++)
			{
				Items[i].Update(Difference, Window);
			}
			for (int i = 0; i < Enemy_Score.size(); i++)
			{
				Enemy_Score[i].Update(Difference, Window);
			}
			
			for (int i = 0; i < Warpgate_Body.size(); i++)
			{
				Warpgate_Body[i].Update(Difference, Window);
			}
			Player.Update(Difference, Mouse_Position, Window, Platforms, bulletVec, bullet);
			for (int i = 0; i < Vexling_Body.size(); i++)
			{
				Vexling_Body[i].Update(Difference, Player.GetPosition(), Window, Platforms, Black_Bile, Black_Explosion, Piercing, Shots);
			}
			if (isShieldON)
			{
				Window.draw(Shield);
			}
			Mouse_Cursor.setPosition(Mouse_Position);
			Window.draw(Mouse_Cursor);

			/*Chacter_View*/

			Window.setView(Character);
			Window.draw(Background4);
			for (int i = 0; i < Platforms.size(); i++)
			{
				Platforms[i].Draw(Window);
			}
			if (Player.Player_Visible)
				Player.Draw(Window);
			Window.display();
			break;
		}
		case Screen::Fourth_Stage:
		{
			if (Player.HP <= 0)
			{
				Die.play();
				FoStage.stop();
				Main_Theme.play();
				scoreRank[0] = score;
				screen = Screen::Scoreboard;
				Player.HP = 0; int i, j, temp;
				user[0] = str;
				scoreFile.open("Sprite/Text/Highscore.txt");
				scoreFile >> scoreRank[1] >> scoreRank[2] >> scoreRank[3] >> scoreRank[4] >> scoreRank[5];
				scoreFile.close();

				userFile.open("Sprite/Text/Username.txt");
				userFile >> user[1] >> user[2] >> user[3] >> user[4] >> user[5];
				userFile.close();
				std::string strtemp;
				for (i = 0; i < 6; i++)
				{
					for (j = i + 1; j < 6; j++)
					{
						if (scoreRank[i] < scoreRank[j])
						{
							temp = scoreRank[i];
							scoreRank[i] = scoreRank[j];
							scoreRank[j] = temp;
							strtemp = user[i];
							user[i] = user[j];
							user[j] = strtemp;
						}
					}
				}
				writeUser.open("Sprite/Text/Username.txt");
				for (i = 0; i < 5; i++)
				{
					writeUser << user[i] << std::endl;
				}
				writeUser.close();

				writeScore.open("Sprite/Text/Highscore.txt");
				for (i = 0; i < 5; i++)
				{
					writeScore << scoreRank[i] << std::endl;
				}
				writeScore.close();
			}
			Event Window_Event;
			Total_Item += Difference;
			Time_Spawn += Difference;
			Total_Shield += Difference;

			/*Default_View*/

			Camera.setViewport(FloatRect(0, 0, 1, 625.0 / Window.getSize().y));
			Camera.setSize(Window.getSize().x, Window.getSize().y* 625.0 / Window.getSize().y);

			/*Character_View*/

			Character.setViewport(FloatRect(25.0 / Window.getSize().x, 645.0 / Window.getSize().y, 150.0 / Window.getSize().x, 103.0 / Window.getSize().y));
			Character.setSize(Window.getSize().x*150.0 / Window.getSize().x, Window.getSize().y*103.0 / Window.getSize().y);
			Character.setCenter(Player.GetPosition().x, Player.GetPosition().y + 15);

			/*GUI_View*/

			GUI_Place.setViewport(FloatRect(0, 625.0 / Window.getSize().y, 1, 143.0 / Window.getSize().y));
			GUI_Place.setSize(Window.getSize().x, Window.getSize().y*143.0 / Window.getSize().y);
			GUI_Place.setCenter(GUI_Place.getSize().x / 2, GUI_Place.getSize().y / 2);

			GUI_Background.setSize(GUI_Place.getSize());
			Empty_Bar.setPosition(Vector2f(GUI_Place.getViewport().left + 250, GUI_Place.getViewport().top + 75));
			GUI_Background.setPosition(GUI_Place.getViewport().left, GUI_Place.getViewport().top);
			HP_Bar.setPosition(Vector2f(GUI_Place.getViewport().left + 250, GUI_Place.getViewport().top + 75));
			HP_Bar.setSize(Vector2f(Player.HP*Empty_Bar.getSize().x / 100.0, 20));

			textUser.setPosition(Vector2f(GUI_Place.getViewport().left + 310, GUI_Place.getViewport().top + 20));
			textUser.setFillColor(Color::Black);
			textUser.setCharacterSize(25);
			if (onetime)
			{
				GUI.clear();
				Platforms.clear();
				bullet.clear();
				bulletVec.clear();
				Metalbeing_Body.clear();
				Items.clear();
				Enemy_Score.clear();
				Time_Items.clear();
				Foulling_Body.clear();
				Gaspow_Body.clear();
				Gaspow_Ball.clear();
				Warpgate_Body.clear();
				Gloomthing_Body.clear();
				Povy_Ball.clear();

				FoStage.play();
				TBoss.stop();
				Floor NewPlatforms(&FoStage_Floor, Vector2f(0, 0));
				Platforms.push_back(NewPlatforms);
				Player.getBody().setPosition(200, 300);
				WarpGate Warpgate1(&Warpgate_Texture, Vector2f(3899,540), Screen::Fourth_Boss, Vector2u(20, 1), 0.2f);
				Warpgate_Body.push_back(Warpgate1);
				Metalbeing Metalbeing1(&Metalbeing_Texture, Vector2u(6, 6), 0.2f, Vector2f(2483,490), Vector2f(0,300));
				Metalbeing_Body.push_back(Metalbeing1);				
				Foulling Foulling1(&Foulling_Texture, Vector2u(4, 6), 0.2f, Vector2f(925, 480), Vector2f(400,300));
				Foulling_Body.push_back(Foulling1);
				Foulling Foulling2(&Foulling_Texture, Vector2u(4, 6), 0.2f, Vector2f(1774,490), Vector2f(300,400));
				Foulling_Body.push_back(Foulling2);
				Gaspow Gaspow1(&Gaspow_Texture, Vector2u(6, 4), 0.2f, Vector2f(3443, -50));
				Gaspow_Body.push_back(Gaspow1);
				Povy Povy1(&Povy_Texture, Vector2u(4, 2), 0.2f, Vector2f(932, 200),&PovyBallSP_Texture);
				Povy_Body.push_back(Povy1);
				Text_String GUI1("Name", GUI_Font, Vector2f(GUI_Place.getViewport().left + 200, GUI_Place.getViewport().top + 20), 25, Color::White, 2, Color::Black);
				GUI.push_back(GUI1);
				Text_String GUI2("HP", GUI_Font, Vector2f(GUI_Place.getViewport().left + 200, GUI_Place.getViewport().top + 70), 25, Color::Red, 2, Color::Black);
				GUI.push_back(GUI2);
				Text_String GUI3("Score", GUI_Font, Vector2f(GUI_Place.getViewport().left + 500, GUI_Place.getViewport().top + 70), 25, Color::Magenta, 2, Color::Black);
				GUI.push_back(GUI3);
				Background7.setTexture(&FoStage_Background);
				Background7.setPosition(0, 0);
				Camera.setCenter(Camera.getSize().x/2,645/2);
				onetime = false;
			}
			
			if(Player.GetPosition().x>=Background7.getPosition().x+Camera.getSize().x/2&& Player.GetPosition().x <= Background7.getPosition().x + Background7.getSize().x-Camera.getSize().x/2)
				Camera.setCenter(Player.GetPosition().x, 645 / 2);

			/*Window Event*/

			while (Window.pollEvent(Window_Event)) {}
			if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			{
				Main_Theme.play();
				scoreRank[0] = score;
				int i, j, temp;
				user[0] = str;
				scoreFile.open("Sprite/Text/Highscore.txt");
				scoreFile >> scoreRank[1] >> scoreRank[2] >> scoreRank[3] >> scoreRank[4] >> scoreRank[5];
				scoreFile.close();

				userFile.open("Sprite/Text/Username.txt");
				userFile >> user[1] >> user[2] >> user[3] >> user[4] >> user[5];
				userFile.close();
				std::string strtemp;
				for (i = 0; i < 6; i++)
				{
					for (j = i + 1; j < 6; j++)
					{
						if (scoreRank[i] < scoreRank[j])
						{
							temp = scoreRank[i];
							scoreRank[i] = scoreRank[j];
							scoreRank[j] = temp;
							strtemp = user[i];
							user[i] = user[j];
							user[j] = strtemp;
						}
					}
				}
				writeUser.open("Sprite/Text/Username.txt");
				for (i = 0; i < 5; i++)
				{
					writeUser << user[i] << std::endl;
				}
				writeUser.close();

				writeScore.open("Sprite/Text/Highscore.txt");
				for (i = 0; i < 5; i++)
				{
					writeScore << scoreRank[i] << std::endl;
				}
				writeScore.close();
				FoStage.stop();
				screen = Screen::Menu;
			}

			/*Bullet_Collision*/

			for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Metalbeing_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Metalbeing_Body[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Metalbeing_Body[j].isDying)
						{
							Metalbeing_Body[j].Metalbeing_Health -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Metalbeing_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Metalbeing_Body[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Metalbeing_Body[j].isDying)
						{
							Metalbeing_Body[j].Metalbeing_Health -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Foulling_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Foulling_Body[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Foulling_Body[j].isDying)
						{
							Foulling_Body[j].Foulling_Health -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Foulling_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Foulling_Body[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Foulling_Body[j].isDying)
						{
							Foulling_Body[j].Foulling_Health -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Gaspow_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Gaspow_Body[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Gaspow_Body[j].isDying)
						{
							Gaspow_Body[j].Gaspow_Health -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Gaspow_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Gaspow_Body[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Gaspow_Body[j].isDying)
						{
							Gaspow_Body[j].Gaspow_Health -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Povy_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Povy_Body[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Povy_Body[j].isDying)
						{
							Povy_Body[j].Povy_Health -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Povy_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Povy_Body[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Povy_Body[j].isDying)
						{
							Povy_Body[j].Povy_Health -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}

			/*Platform_Collision*/

			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < bulletVec.size(); j++)
				{
					if (Collision::PixelPerfectTest(bulletVec[j].Get_Body(), Platforms[i].Body(), 0) || bulletVec[j].Get_Body().getPosition().x - abs(bulletVec[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || bulletVec[j].Get_Body().getPosition().x + abs(bulletVec[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || bulletVec[j].Get_Body().getPosition().y + abs(bulletVec[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || bulletVec[j].Get_Body().getPosition().y - abs(bulletVec[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						if (!Player.isWave)
						{
							bulletVec.erase(bulletVec.begin() + j);
							break;
						}
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < bullet.size(); j++)
				{
					if (Collision::PixelPerfectTest(bullet[j].Get_Body(), Platforms[i].Body(), 0) || bullet[j].Get_Body().getPosition().x - abs(bullet[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || bullet[j].Get_Body().getPosition().x + abs(bullet[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || bullet[j].Get_Body().getPosition().y + abs(bullet[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || bullet[j].Get_Body().getPosition().y - abs(bullet[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						bullet.erase(bullet.begin() + j);
						break;
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Items.size(); j++)
				{
					if (Collision::PixelPerfectTest(Items[j].Item_Projectiles.Get_Body(), Platforms[i].Body(), 0))
					{
						Items[j].Item_Projectiles.isMoving = false;
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Povy_Body.size(); j++)
				{
					if (!Collision::PixelPerfectTest(Povy_Body[j].Get_Body(), Platforms[i].Body(), 0))
					{
						Povy_Body[j].Get_Body().move(0, 98.1*Difference);
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Povy_Ball.size(); j++)
				{
					if (Collision::PixelPerfectTest(Povy_Ball[j].Get_Body(), Platforms[i].Body(), 0) || Povy_Ball[j].Get_Body().getPosition().x - abs(Povy_Ball[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || Povy_Ball[j].Get_Body().getPosition().x + abs(Povy_Ball[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || Povy_Ball[j].Get_Body().getPosition().y + abs(Povy_Ball[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || Povy_Ball[j].Get_Body().getPosition().y - abs(Povy_Ball[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						Povy_Ball.erase(Povy_Ball.begin() + j);
						break;
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Gaspow_Body.size(); j++)
				{
					if (!Collision::PixelPerfectTest(Gaspow_Body[j].Get_Body(), Platforms[i].Body(), 0))
					{
						Gaspow_Body[j].Get_Body().move(0, 98.1*Difference);
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Gaspow_Ball.size(); j++)
				{
					if (Collision::PixelPerfectTest(Gaspow_Ball[j].Get_Body(), Platforms[i].Body(), 0) || Gaspow_Ball[j].Get_Body().getPosition().x - abs(Gaspow_Ball[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || Gaspow_Ball[j].Get_Body().getPosition().x + abs(Gaspow_Ball[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || Gaspow_Ball[j].Get_Body().getPosition().y + abs(Gaspow_Ball[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || Gaspow_Ball[j].Get_Body().getPosition().y - abs(Gaspow_Ball[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						Gaspow_Ball.erase(Gaspow_Ball.begin() + j);
						break;
					}
				}
			}

			/*Player Collision*/

			for (int i = 0; i < Items.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Items[i].Item_Projectiles.Get_Body(), 0))
				{
					if (!Player.isDying)
					{
						if (Items[i].isArrow)
						{
							Player.isWave = false;
							Player.isDirect = false;
							Player.isLaser = false;
							Player.isLob = false;
							Player.isArrow = true;
							Time_Items.clear();
							ItemSound.play();
							Count_Item = Total_Item;
							Item NewItems(&Arrow_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isLob)
						{
							ItemSound.play();
							Player.isWave = false;
							Player.isDirect = false;
							Player.isLaser = false;
							Player.isLob = true;
							Player.isArrow = false;
							Count_Item = Total_Item;
							Time_Items.clear();
							Item NewItems(&Lob_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isWave)
						{
							ItemSound.play();
							Player.isWave = true;
							Player.isDirect = false;
							Player.isLaser = false;
							Player.isLob = false;
							Player.isArrow = false;
							Time_Items.clear();
							Count_Item = Total_Item;
							Item NewItems(&Wave_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isLaser)
						{
							ItemSound.play();
							Player.isWave = false;
							Player.isDirect = false;
							Player.isLaser = true;
							Player.isLob = false;
							Player.isArrow = false;
							Time_Items.clear();
							Count_Item = Total_Item;
							Item NewItems(&Laser_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isShield) { isShieldON = true; Count_Shield = Total_Shield; }
						else if (Items[i].isFood) { Player.HP += Items[i].Health; Munch.play(); }
						else { SoulSound.play(); }
						Items[i].Item_Visible = false;
						score += Items[i].Score;
						Items.erase(Items.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < Povy_Ball.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Povy_Ball[i].Get_Body(), 0))
				{
					if (!Player.isHurting && !Player.isDying)
					{
						Player.HP -= Povy_Ball[i].Damage;
						Player.Player_Animation.Visible = true;
						Player.isHurting = true;
						Player.Player_Animation.Current_Image.x = 0;
						Povy_Ball.erase(Povy_Ball.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < Povy_Ball.size(); i++)
			{
				if (Collision::PixelPerfectTest(Povy_Ball[i].Get_Body(), Shield, 0))
				{
					Povy_Ball.erase(Povy_Ball.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Povy_Body.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Povy_Body[i].Get_Body(), 0) && !Player.isHurting && !Player.isDying)
				{
					Player.HP -= 5;
					Player.isHurting = true;
					Player.Player_Animation.Visible = true;
					Player.Player_Animation.Current_Image.x = 0;
				}
			}
			for (int i = 0; i < Gaspow_Ball.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Gaspow_Ball[i].Get_Body(), 0))
				{
					if (!Player.isHurting && !Player.isDying)
					{
						Player.HP -= Gaspow_Ball[i].Damage;
						Player.Player_Animation.Visible = true;
						Player.isHurting = true;
						Player.Player_Animation.Current_Image.x = 0;
						Gaspow_Ball.erase(Gaspow_Ball.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < Gaspow_Ball.size(); i++)
			{
				if (Collision::PixelPerfectTest(Gaspow_Ball[i].Get_Body(), Shield, 0))
				{
					Gaspow_Ball.erase(Gaspow_Ball.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Gaspow_Body.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Gaspow_Body[i].Get_Body(), 0) && !Player.isHurting && !Player.isDying)
				{
					Player.HP -= 5;
					Player.isHurting = true;
					Player.Player_Animation.Visible = true;
					Player.Player_Animation.Current_Image.x = 0;
				}
			}
			for (int i = 0; i < Foulling_Body.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Foulling_Body[i].Get_Body(), 0) && !Player.isHurting && !Player.isDying)
				{
					Player.HP -= 5;
					Player.isHurting = true;
					Player.Player_Animation.Visible = true;
					Player.Player_Animation.Current_Image.x = 0;
				}
			}
			for (int i = 0; i < Warpgate_Body.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Warpgate_Body[i].Get_Body()) && !Player.isHurting && !Player.isDying)
				{
					if (Keyboard::isKeyPressed(Keyboard::Space))
					{
						screen = Warpgate_Body[i].to;
						onetime = true;
						break;
					}
				}
			}

			/*Items*/

			for (int i = 0; i < Metalbeing_Body.size(); i++)
			{
				if (!Metalbeing_Body[i].Metalbeing_Visible)
				{
					num = rand() % 5;
					if (num == 0)
					{
						Item newItem(&Shield_Texture, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isShield = true;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					else if (num == 1)
					{
						Item newItem(&Arrow_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isArrow = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					else if (num == 2)
					{
						Item newItem(&Laser_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isLaser = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					else if (num == 3)
					{
						Item newItem(&Wave_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isWave = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					else if (num == 4)
					{
						Item newItem(&Lob_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isLob = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					Metalbeing_Body.erase(Metalbeing_Body.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Povy_Body.size(); i++)
			{
				if (!Povy_Body[i].Povy_Visible)
				{
					score += Povy_Body[i].Score;
					Text_String newScore(std::to_string(Povy_Body[i].Score), Score_Font, Vector2f(Povy_Body[i].Get_Body().getPosition().x, Povy_Body[i].Get_Body().getPosition().y - 20), 20, Color::Yellow, 1, Color::Black);
					Enemy_Score.push_back(newScore);
					num = rand() % 12 + 1;
					if (num >= 8)
					{
						Item newItem(&Lemon, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 15);
						newItem.Item_Projectiles.setPos(Vector2f(Povy_Body[i].Get_Body().getPosition().x, Povy_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 10;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					else if (num >= 6)
					{
						Item newItem(&Cherry, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 20);
						newItem.Item_Projectiles.setPos(Vector2f(Povy_Body[i].Get_Body().getPosition().x, Povy_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 20;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					else
					{
						Item newItem(&Corn_Stick, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 10);
						newItem.Item_Projectiles.setPos(Vector2f(Povy_Body[i].Get_Body().getPosition().x, Povy_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 40;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					num = rand() % 5 + 1;
					for (int j = 1; j <= num; j++)
					{
						Item newItem(&Soul, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(4, 1), 0.2f, 5);
						newItem.Item_Projectiles.setPos(Vector2f(Povy_Body[i].Get_Body().getPosition().x, Povy_Body[i].Get_Body().getPosition().y - 20));
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					Povy_Body.erase(Povy_Body.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Gaspow_Body.size(); i++)
			{
				if (!Gaspow_Body[i].Gaspow_Visible)
				{
					score += Gaspow_Body[i].Score;
					Text_String newScore(std::to_string(Gaspow_Body[i].Score), Score_Font, Vector2f(Gaspow_Body[i].Get_Body().getPosition().x, Gaspow_Body[i].Get_Body().getPosition().y - 20), 20, Color::Yellow, 1, Color::Black);
					Enemy_Score.push_back(newScore);
					num = rand() % 12 + 1;
					if (num >= 8)
					{
						Item newItem(&Corn_Stick, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 15);
						newItem.Item_Projectiles.setPos(Vector2f(Gaspow_Body[i].Get_Body().getPosition().x, Gaspow_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 25;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					else if (num >= 6)
					{
						Item newItem(&Chicken, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 20);
						newItem.Item_Projectiles.setPos(Vector2f(Gaspow_Body[i].Get_Body().getPosition().x, Gaspow_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 10;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					else
					{
						Item newItem(&Lemon, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 10);
						newItem.Item_Projectiles.setPos(Vector2f(Gaspow_Body[i].Get_Body().getPosition().x, Gaspow_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Health = 30;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					num = rand() % 5 + 1;
					for (int j = 1; j <= num; j++)
					{
						Item newItem(&Soul, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(4, 1), 0.2f, 5);
						newItem.Item_Projectiles.setPos(Vector2f(Gaspow_Body[i].Get_Body().getPosition().x, Gaspow_Body[i].Get_Body().getPosition().y - 20));
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					Gaspow_Body.erase(Gaspow_Body.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Foulling_Body.size(); i++)
			{
				if (!Foulling_Body[i].Foulling_Visible)
				{
					score += Foulling_Body[i].Score;
					Text_String newScore(std::to_string(Foulling_Body[i].Score), Score_Font, Vector2f(Foulling_Body[i].Get_Body().getPosition().x, Foulling_Body[i].Get_Body().getPosition().y - 20), 20, Color::Yellow, 1, Color::Black);
					Enemy_Score.push_back(newScore);
					num = rand() % 15 + 1;
					for (int j = 1; j <= num; j++)
					{
						Item newItem(&Soul, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(4, 1), 0.2f, 5);
						newItem.Item_Projectiles.setPos(Vector2f(Foulling_Body[i].Get_Body().getPosition().x, Foulling_Body[i].Get_Body().getPosition().y - 20));
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					Foulling_Body.erase(Foulling_Body.begin() + i);
					break;
				}
			}

			/*Items Active*/
			if (isShieldON)
			{
				Shield.setPosition(Player.GetPosition());
			}
			else
			{
				Shield.setPosition(-100, -100);
			}
			if (Total_Item - Count_Item >= 10.0f)
			{
				Player.isArrow = false;
				Player.isLaser = false;
				Player.isLob = false;
				Player.isWave = false;
				Player.isDirect = true;
				Total_Item = 0;
				Count_Item = 0;
				Time_Items.clear();
			}
			if (Total_Shield - Count_Shield >= 10.0f)
			{
				isShieldON = false;
				Total_Shield = 0;
				Count_Shield = 0;
			}

			Window.clear();

			/*GUI_View*/

			Window.setView(GUI_Place);
			Window.draw(GUI_Background);
			for (int i = 0; i < GUI.size(); i++)
			{
				GUI[i].Draw(Window);
			}
			Score.Update_Text(std::to_string(score));
			Health.Update_Text(std::to_string(Player.HP) + "/100");
			Window.draw(Empty_Bar);
			Window.draw(HP_Bar);
			Score.Draw(Window);
			Health.Draw(Window);
			Score_Soul.Item_Projectiles.setPos(Vector2f(GUI_Place.getViewport().left + 620.0f, GUI_Place.getViewport().top + 80.0f));
			Score_Soul.Update(Difference, Window);
			if (Player.isArrow || Player.isLob || Player.isLaser || Player.isWave)
			{
				for (int i = 0; i < Time_Items.size(); i++)
				{
					Time_Items[i].Item_Projectiles.setPos(Vector2f(GUI_Place.getViewport().left + 1200, GUI_Place.getViewport().top + 42));
					Time_Items[i].Update(Difference, Window);
				}
				Item_Time.Text_Body.setPosition(Vector2f(GUI_Place.getViewport().left + 1250, GUI_Place.getViewport().top + 20));
				Item_Time.Update_Text(std::to_string(10 - abs((int)Count_Item - (int)Total_Item)));
				Window.draw(Item_Time.Text_Body);
			}
			if (isShieldON)
			{
				Time_Shield.Item_Projectiles.Get_Body().setScale(2, 2);
				Time_Shield.Item_Projectiles.setPos(Vector2f(GUI_Place.getViewport().left + 1200, GUI_Place.getViewport().top + 110));
				Time_Shield.Update(Difference, Window);
				Shield_Time.Text_Body.setPosition(Vector2f(GUI_Place.getViewport().left + 1250, GUI_Place.getViewport().top + 85));
				Shield_Time.Update_Text(std::to_string(10 - abs((int)Count_Shield - (int)Total_Shield)));
				Window.draw(Shield_Time.Text_Body);
			}
			Window.draw(textUser);

			/*Default_View*/

			Window.setView(Camera);
			Mouse_Position = Window.mapPixelToCoords(Mouse::getPosition(Window));
			Window.draw(Background7);
			for (int i = 0; i < Platforms.size(); i++)
			{
				Platforms[i].Draw(Window);
			}
			for (int i = 0; i < Metalbeing_Body.size(); i++)
			{
				Metalbeing_Body[i].Update(Difference, Player.GetPosition(), Window, Platforms);
			}
			for (int i = 0; i < Povy_Body.size(); i++)
			{
				Povy_Body[i].Update(Difference, Player.GetPosition(), Povy_Ball, Window,Platforms);
			}
			for (int i = 0; i < Gaspow_Body.size(); i++)
			{
				Gaspow_Body[i].Gaspow_Update(Difference, Player.GetPosition(), Gaspow_Ball, Window);
			}
			for (int i = 0; i < Foulling_Body.size(); i++)
			{
				Foulling_Body[i].Update(Difference, Player.GetPosition(), Window, Platforms);
			}
			for (int i = 0; i < Items.size(); i++)
			{
				Items[i].Update(Difference, Window);
			}
			for (int i = 0; i < Enemy_Score.size(); i++)
			{
				Enemy_Score[i].Update(Difference, Window);
			}
			for (int i = 0; i < Warpgate_Body.size(); i++)
			{
				Warpgate_Body[i].Update(Difference, Window);
			}
			Player.Update(Difference, Mouse_Position, Window, Platforms, bulletVec, bullet);
			if (isShieldON)
			{
				Window.draw(Shield);
			}
			Mouse_Cursor.setPosition(Mouse_Position);
			Window.draw(Mouse_Cursor);

			/*Chacter_View*/

			Window.setView(Character);
			Window.draw(Background7);
			for (int i = 0; i < Platforms.size(); i++)
			{
				Platforms[i].Draw(Window);
			}
			if (Player.Player_Visible)
				Player.Draw(Window);
			Window.display();
			break;
		}
		case Screen::Fourth_Boss:
		{
			if (Player.HP <= 0)
			{
				Die.play();
				scoreRank[0] = score;
				screen = Screen::Scoreboard;
				Main_Theme.play();
				FoBoss.stop();
				Player.HP = 0;
				int i, j, temp;
				user[0] = str;
				scoreFile.open("Sprite/Text/Highscore.txt");
				scoreFile >> scoreRank[1] >> scoreRank[2] >> scoreRank[3] >> scoreRank[4] >> scoreRank[5];
				scoreFile.close();

				userFile.open("Sprite/Text/Username.txt");
				userFile >> user[1] >> user[2] >> user[3] >> user[4] >> user[5];
				userFile.close();
				std::string strtemp;
				for (i = 0; i < 6; i++)
				{
					for (j = i + 1; j < 6; j++)
					{
						if (scoreRank[i] < scoreRank[j])
						{
							temp = scoreRank[i];
							scoreRank[i] = scoreRank[j];
							scoreRank[j] = temp;
							strtemp = user[i];
							user[i] = user[j];
							user[j] = strtemp;
						}
					}
				}
				writeUser.open("Sprite/Text/Username.txt");
				for (i = 0; i < 5; i++)
				{
					writeUser << user[i] << std::endl;
				}
				writeUser.close();

				writeScore.open("Sprite/Text/Highscore.txt");
				for (i = 0; i < 5; i++)
				{
					writeScore << scoreRank[i] << std::endl;
				}
				writeScore.close();
			}
			if (Victory)
			{
				Win.play();
				scoreRank[0] = score;
				screen = Screen::Scoreboard;
				Main_Theme.play();
				FoBoss.stop();
				Player.HP = 0;
				int i, j, temp;
				user[0] = str;
				scoreFile.open("Sprite/Text/Highscore.txt");
				scoreFile >> scoreRank[1] >> scoreRank[2] >> scoreRank[3] >> scoreRank[4] >> scoreRank[5];
				scoreFile.close();

				userFile.open("Sprite/Text/Username.txt");
				userFile >> user[1] >> user[2] >> user[3] >> user[4] >> user[5];
				userFile.close();
				std::string strtemp;
				for (i = 0; i < 6; i++)
				{
					for (j = i + 1; j < 6; j++)
					{
						if (scoreRank[i] < scoreRank[j])
						{
							temp = scoreRank[i];
							scoreRank[i] = scoreRank[j];
							scoreRank[j] = temp;
							strtemp = user[i];
							user[i] = user[j];
							user[j] = strtemp;
						}
					}
				}
				writeUser.open("Sprite/Text/Username.txt");
				for (i = 0; i < 5; i++)
				{
					writeUser << user[i] << std::endl;
				}
				writeUser.close();

				writeScore.open("Sprite/Text/Highscore.txt");
				for (i = 0; i < 5; i++)
				{
					writeScore << scoreRank[i] << std::endl;
				}
				writeScore.close();
			}
			Event Window_Event;
			Total_Shield += Difference;
			Total_Item += Difference;
			Time_Spawn += Difference;

			/*Default_View*/

			Camera.setViewport(FloatRect(0, 0, 1, 625.0 / Window.getSize().y));
			Camera.setSize(Window.getSize().x, Window.getSize().y* 625.0 / Window.getSize().y);

			/*Character_View*/

			Character.setViewport(FloatRect(25.0 / Window.getSize().x, 645.0 / Window.getSize().y, 150.0 / Window.getSize().x, 103.0 / Window.getSize().y));
			Character.setSize(Window.getSize().x*150.0 / Window.getSize().x, Window.getSize().y*103.0 / Window.getSize().y);
			Character.setCenter(Player.GetPosition().x, Player.GetPosition().y + 15);

			/*GUI_View*/

			GUI_Place.setViewport(FloatRect(0, 625.0 / Window.getSize().y, 1, 143.0 / Window.getSize().y));
			GUI_Place.setSize(Window.getSize().x, Window.getSize().y*143.0 / Window.getSize().y);
			GUI_Place.setCenter(GUI_Place.getSize().x / 2, GUI_Place.getSize().y / 2);

			GUI_Background.setSize(GUI_Place.getSize());
			Empty_Bar.setPosition(Vector2f(GUI_Place.getViewport().left + 250, GUI_Place.getViewport().top + 75));
			GUI_Background.setPosition(GUI_Place.getViewport().left, GUI_Place.getViewport().top);
			HP_Bar.setPosition(Vector2f(GUI_Place.getViewport().left + 250, GUI_Place.getViewport().top + 75));
			HP_Bar.setSize(Vector2f(Player.HP*Empty_Bar.getSize().x / 100.0, 20));

			textUser.setPosition(Vector2f(GUI_Place.getViewport().left + 310, GUI_Place.getViewport().top + 20));
			textUser.setFillColor(Color::Black);
			textUser.setCharacterSize(25);
			if (onetime)
			{
				GUI.clear();
				Enemy_Score.clear();
				Platforms.clear();
				bullet.clear();
				bulletVec.clear();
				Metalbeing_Body.clear();
				Items.clear();
				Warpscream_Body.clear();
				Absorb.clear();
				Barrel_Body.clear();
				White_force.clear();
				Time_Items.clear();
				Warpgate_Body.clear();

				FoStage.stop();
				FoBoss.play();
				Floor NewPlatforms(&FoBoss_Floor, Vector2f(0, 0));
				Platforms.push_back(NewPlatforms);
				Player.getBody().setPosition(200, 0);
				Warpscream NewWarpscream(&Warpscream_Texture,Vector2u(5,10),0.2f,Vector2f(100,100));
				Warpscream_Body.push_back(NewWarpscream);
				Metalbeing NewMetalbeing(&Metalbeing_Texture, Vector2u(6, 6), 0.2f, Vector2f(rand() % 767 + 400, 450), Vector2f(500, 500));
				Metalbeing_Body.push_back(NewMetalbeing);
				Text_String GUI1("Name", GUI_Font, Vector2f(GUI_Place.getViewport().left + 200, GUI_Place.getViewport().top + 20), 25, Color::White, 2, Color::Black);
				GUI.push_back(GUI1);
				Text_String GUI2("HP", GUI_Font, Vector2f(GUI_Place.getViewport().left + 200, GUI_Place.getViewport().top + 70), 25, Color::Red, 2, Color::Black);
				GUI.push_back(GUI2);
				Text_String GUI3("Score", GUI_Font, Vector2f(GUI_Place.getViewport().left + 500, GUI_Place.getViewport().top + 70), 25, Color::Magenta, 2, Color::Black);
				GUI.push_back(GUI3);
				Background8.setTexture(&FoBoss_Background);
				Background8.setPosition(0, 0);
				Camera.setCenter(Platforms[0].Get_Size().width / 2.0f, Platforms[0].Get_Size().height / 2.0f);
				Time_Spawn = 0;
				Stop = false;
				Victory = false;
				onetime = false;
			}

			if (Time_Spawn >= 20.0f && !Stop)
			{
				Metalbeing NewMetalbeing(&Metalbeing_Texture, Vector2u(6, 6), 0.2f, Vector2f(rand() % 767 + 400, 450), Vector2f(500, 500));
				Metalbeing_Body.push_back(NewMetalbeing);
				Time_Spawn = 0;
				Metal_Count++;
			}

			/*Window Event*/

			while (Window.pollEvent(Window_Event)) {}
			if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			{
				FoBoss.stop();
				Main_Theme.play();
				scoreRank[0] = score;
				int i, j, temp;
				user[0] = str;
				scoreFile.open("Sprite/Text/Highscore.txt");
				scoreFile >> scoreRank[1] >> scoreRank[2] >> scoreRank[3] >> scoreRank[4] >> scoreRank[5];
				scoreFile.close();

				userFile.open("Sprite/Text/Username.txt");
				userFile >> user[1] >> user[2] >> user[3] >> user[4] >> user[5];
				userFile.close();
				std::string strtemp;
				for (i = 0; i < 6; i++)
				{
					for (j = i + 1; j < 6; j++)
					{
						if (scoreRank[i] < scoreRank[j])
						{
							temp = scoreRank[i];
							scoreRank[i] = scoreRank[j];
							scoreRank[j] = temp;
							strtemp = user[i];
							user[i] = user[j];
							user[j] = strtemp;
						}
					}
				}
				writeUser.open("Sprite/Text/Username.txt");
				for (i = 0; i < 5; i++)
				{
					writeUser << user[i] << std::endl;
				}
				writeUser.close();

				writeScore.open("Sprite/Text/Highscore.txt");
				for (i = 0; i < 5; i++)
				{
					writeScore << scoreRank[i] << std::endl;
				}
				writeScore.close();
				screen = Screen::Menu;
			}

			/*Bullet_Collision*/

			for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Metalbeing_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Metalbeing_Body[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Metalbeing_Body[j].isDying)
						{
							Metalbeing_Body[j].Metalbeing_Health -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Metalbeing_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Metalbeing_Body[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Metalbeing_Body[j].isDying)
						{
							Metalbeing_Body[j].Metalbeing_Health -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Barrel_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Barrel_Body[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Barrel_Body[j].isDying)
						{
							Barrel_Body[j].Barrel_Hp -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Barrel_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Barrel_Body[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Barrel_Body[j].isDying)
						{
							Barrel_Body[j].Barrel_Hp -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bulletVec.size(); i++)
			{
				for (int j = 0; j < Warpscream_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Warpscream_Body[j].Get_Body(), bulletVec[i].Get_Body(), 0))
					{
						if (!Warpscream_Body[j].Warpscream_Dying)
						{
							Warpscream_Body[j].Warpscream_Health -= bulletVec[i].Damage;
						}
						bulletVec.erase(bulletVec.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < bullet.size(); i++)
			{
				for (int j = 0; j < Warpscream_Body.size(); j++)
				{
					if (Collision::PixelPerfectTest(Warpscream_Body[j].Get_Body(), bullet[i].Get_Body(), 0))
					{
						if (!Warpscream_Body[j].Warpscream_Dying)
						{
							Warpscream_Body[j].Warpscream_Health -= bullet[i].Damage;
						}
						bullet.erase(bullet.begin() + i);
						break;
					}
				}
			}

			/*Platform_Collision*/

			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < bulletVec.size(); j++)
				{
					if (Collision::PixelPerfectTest(bulletVec[j].Get_Body(), Platforms[i].Body(), 0) || bulletVec[j].Get_Body().getPosition().x - abs(bulletVec[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || bulletVec[j].Get_Body().getPosition().x + abs(bulletVec[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || bulletVec[j].Get_Body().getPosition().y + abs(bulletVec[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || bulletVec[j].Get_Body().getPosition().y - abs(bulletVec[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						if (!Player.isWave)
						{
							bulletVec.erase(bulletVec.begin() + j);
							break;
						}
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Absorb.size(); j++)
				{
					if (Collision::PixelPerfectTest(Absorb[j].Get_Body(), Platforms[i].Body(), 0) || Absorb[j].Get_Body().getPosition().x - abs(Absorb[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || Absorb[j].Get_Body().getPosition().x + abs(Absorb[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || Absorb[j].Get_Body().getPosition().y + abs(Absorb[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || Absorb[j].Get_Body().getPosition().y - abs(Absorb[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						Absorb.erase(Absorb.begin() + j);
						break;
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < bullet.size(); j++)
				{
					if (Collision::PixelPerfectTest(bullet[j].Get_Body(), Platforms[i].Body(), 0) || bullet[j].Get_Body().getPosition().x - abs(bullet[j].Get_Body().getTextureRect().width) / 2.0f < Platforms[i].Position().x || bullet[j].Get_Body().getPosition().x + abs(bullet[j].Get_Body().getTextureRect().width) / 2.0f > Platforms[i].Get_Size().width || bullet[j].Get_Body().getPosition().y + abs(bullet[j].Get_Body().getTextureRect().height) / 2.0f < Platforms[i].Position().y || bullet[j].Get_Body().getPosition().y - abs(bullet[j].Get_Body().getTextureRect().height) / 2.0f> Platforms[i].Get_Size().height)
					{
						bullet.erase(bullet.begin() + j);
						break;
					}
				}
			}
			for (int i = 0; i < Platforms.size(); i++)
			{
				for (int j = 0; j < Items.size(); j++)
				{
					if (Collision::PixelPerfectTest(Items[j].Item_Projectiles.Get_Body(), Platforms[i].Body(), 0))
					{
						Items[j].Item_Projectiles.isMoving = false;
					}
				}
			}

			/*Player Collision*/

			for (int i = 0; i < Items.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Items[i].Item_Projectiles.Get_Body(), 0))
				{
					if (!Player.isDying)
					{
						if (Items[i].isArrow)
						{
							Player.isWave = false;
							Player.isDirect = false;
							Player.isLaser = false;
							Player.isLob = false;
							Player.isArrow = true;
							Time_Items.clear();
							ItemSound.play();
							Count_Item = Total_Item;
							Item NewItems(&Arrow_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isLob)
						{
							ItemSound.play();
							Player.isWave = false;
							Player.isDirect = false;
							Player.isLaser = false;
							Player.isLob = true;
							Player.isArrow = false;
							Count_Item = Total_Item;
							Time_Items.clear();
							Item NewItems(&Lob_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isWave)
						{
							ItemSound.play();
							Player.isWave = true;
							Player.isDirect = false;
							Player.isLaser = false;
							Player.isLob = false;
							Player.isArrow = false;
							Time_Items.clear();
							Count_Item = Total_Item;
							Item NewItems(&Wave_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isLaser)
						{
							ItemSound.play();
							Player.isWave = false;
							Player.isDirect = false;
							Player.isLaser = true;
							Player.isLob = false;
							Player.isArrow = false;
							Time_Items.clear();
							Count_Item = Total_Item;
							Item NewItems(&Laser_Gun, Vector2f(0, 0), 0.0f, Vector2u(20, 1), 0.2f, 0.0f);
							Time_Items.push_back(NewItems);
						}
						else if (Items[i].isShield) { isShieldON = true; Count_Shield = Total_Shield; }
						else if (Items[i].isFood) { Player.HP += Items[i].Health; Munch.play(); }
						else { SoulSound.play(); }
						Items[i].Item_Visible = false;
						score += Items[i].Score;
						Items.erase(Items.begin() + i);
						break;
					}
				}
			}
			for (int i = 0; i < White_force.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), White_force[i].Explosion_Body, 0))
				{
					if (White_force[i].Damagable)
					{
						if (!Player.isHurting && !Player.isDying)
						{
							Player.HP -= White_force[i].Damage;
							Player.Player_Animation.Visible = true;
							Player.isHurting = true;
							Player.Player_Animation.Current_Image.x = 0;
						}
					}
				}
			}
			for (int i = 0; i < Absorb.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Absorb[i].Get_Body(), 0))
				{
					if (!Player.isHurting && !Player.isDying)
					{
						Warpscream_Body[0].Warpscream_Health += 5;
						Player.HP -= Absorb[i].Damage;
						Player.Player_Animation.Visible = true;
						Player.isHurting = true;
						Player.Player_Animation.Current_Image.x = 0;
					}
					Absorb.erase(Absorb.begin()+i);
					break;
				}
			}
			for (int i = 0; i < Absorb.size(); i++)
			{
				if (Collision::PixelPerfectTest(Absorb[i].Get_Body(), Shield, 0))
				{
					Absorb.erase(Absorb.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Warpgate_Body.size(); i++)
			{
				if (Collision::PixelPerfectTest(Player.getBody(), Warpgate_Body[i].Get_Body()) && !Player.isHurting && !Player.isDying)
				{
					if (Keyboard::isKeyPressed(Keyboard::Space))
					{
						screen = Warpgate_Body[i].to;
						onetime = true;
						break;
					}
				}
			}

			/*Items*/

			for (int i = 0; i < Metalbeing_Body.size(); i++)
			{
				if (!Metalbeing_Body[i].Metalbeing_Visible)
				{
					num = rand() % 5;
					if (num == 0)
					{
						Item newItem(&Shield_Texture, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isShield = true;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						Items.push_back(newItem);
					}
					else if (num == 1)
					{
						Item newItem(&Arrow_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isArrow = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					else if (num == 2)
					{
						Item newItem(&Laser_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isLaser = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					else if (num == 3)
					{
						Item newItem(&Wave_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isWave = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					else if (num == 4)
					{
						Item newItem(&Lob_Gun, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 0);
						newItem.Item_Projectiles.setPos(Vector2f(Metalbeing_Body[i].Get_Body().getPosition().x, Metalbeing_Body[i].Get_Body().getPosition().y - 20));
						newItem.isLob = true;
						newItem.Item_Projectiles.Get_Body().setScale(1.05, 1.05);
						Items.push_back(newItem);
					}
					Metalbeing_Body.erase(Metalbeing_Body.begin() + i);
					break;
				}
			}
			for (int i = 0; i < Warpscream_Body.size(); i++)
			{
				if (Warpscream_Body[i].Warpscream_Dying)
				{
					score += Warpscream_Body[i].Score;
					Text_String newScore(std::to_string(Warpscream_Body[i].Score), Score_Font, Vector2f(Warpscream_Body[i].Get_Body().getPosition().x, Warpscream_Body[i].Get_Body().getPosition().y - 20), 20, Color::Yellow, 1, Color::Black);
					Enemy_Score.push_back(newScore);
					num = rand() % 12 + 1;
					if (num >= 8)
					{
						Item newItem(&Pizza, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 15);
						newItem.Item_Projectiles.setPos(Vector2f(Warpscream_Body[i].Get_Body().getPosition().x, Warpscream_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						newItem.Health = 50;
						Items.push_back(newItem);
					}
					else if (num >= 6)
					{
						Item newItem(&Cake, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 20);
						newItem.Item_Projectiles.setPos(Vector2f(Warpscream_Body[i].Get_Body().getPosition().x, Warpscream_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						newItem.Health = 100;
						Items.push_back(newItem);
					}
					else
					{
						Item newItem(&Green_Apple, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(20, 1), 0.2f, 10);
						newItem.Item_Projectiles.setPos(Vector2f(Warpscream_Body[i].Get_Body().getPosition().x, Warpscream_Body[i].Get_Body().getPosition().y - 20));
						newItem.isFood = true;
						newItem.Item_Projectiles.Get_Body().setScale(2, 2);
						newItem.Health = 75;
						Items.push_back(newItem);
					}
					num = rand() % 41 + 10;
					for (int j = 1; j <= num; j++)
					{
						Item newItem(&Soul, Vector2f((float)(rand() % 21 - 10)*10.0, 100), 250.0f, Vector2u(4, 1), 0.2f, 5);
						newItem.Item_Projectiles.setPos(Vector2f(Warpscream_Body[i].Get_Body().getPosition().x, Warpscream_Body[i].Get_Body().getPosition().y - 20));
						newItem.Item_Projectiles.Get_Body().setScale(1.05,1.05);
						Items.push_back(newItem);
					}
					FoBoss.stop();
					VictoryS.play();
					Stop = true;
					Warpscream_Body.erase(Warpscream_Body.begin() + i);
					break;
				}
			}
			
			for (int i = 0; i < Barrel_Body.size(); i++)
			{
				if (!Barrel_Body[i].Barrel_Visible)
				{
					if (Barrel_Body[i].isIceShield)
						Warpscream_Body[0].Shieldable = true;
					Barrel_Body.erase(Barrel_Body.begin()  + i);
					break;
				}
			}

			/*Items Active*/

			if (isShieldON)
			{
				Shield.setPosition(Player.GetPosition());
			}
			else
			{
				Shield.setPosition(-100, -100);
			}
			if (Total_Item - Count_Item >= 10.0f)
			{
				Player.isArrow = false;
				Player.isLaser = false;
				Player.isLob = false;
				Player.isWave = false;
				Player.isDirect = true;
				Total_Item = 0;
				Count_Item = 0;
				Time_Items.clear();
			}
			if (Total_Shield - Count_Shield >= 10.0f)
			{
				isShieldON = false;
				Total_Shield = 0;
				Count_Shield = 0;
			}
			if (VictoryS.getStatus() == Music::Status::Stopped&&Stop)
			{
				Victory = true;
			}
			Window.clear();

			/*GUI_View*/

			Window.setView(GUI_Place);
			Window.draw(GUI_Background);
			for (int i = 0; i < GUI.size(); i++)
			{
				GUI[i].Draw(Window);
			}
			Score.Update_Text(std::to_string(score));
			Health.Update_Text(std::to_string(Player.HP) + "/100");
			Window.draw(Empty_Bar);
			Window.draw(HP_Bar);
			Score.Draw(Window);
			Health.Draw(Window);
			Score_Soul.Item_Projectiles.setPos(Vector2f(GUI_Place.getViewport().left + 620.0f, GUI_Place.getViewport().top + 80.0f));
			Score_Soul.Update(Difference, Window);
			if (Player.isArrow || Player.isLob || Player.isLaser || Player.isWave)
			{
				for (int i = 0; i < Time_Items.size(); i++)
				{
					Time_Items[i].Item_Projectiles.setPos(Vector2f(GUI_Place.getViewport().left + 1200, GUI_Place.getViewport().top + 42));
					Time_Items[i].Update(Difference, Window);
				}
				Item_Time.Text_Body.setPosition(Vector2f(GUI_Place.getViewport().left + 1250, GUI_Place.getViewport().top + 20));
				Item_Time.Update_Text(std::to_string(10 - abs((int)Count_Item - (int)Total_Item)));
				Window.draw(Item_Time.Text_Body);
			}
			if (isShieldON)
			{
				Time_Shield.Item_Projectiles.Get_Body().setScale(2, 2);
				Time_Shield.Item_Projectiles.setPos(Vector2f(GUI_Place.getViewport().left + 1200, GUI_Place.getViewport().top + 110));
				Time_Shield.Update(Difference, Window);
				Shield_Time.Text_Body.setPosition(Vector2f(GUI_Place.getViewport().left + 1250, GUI_Place.getViewport().top + 85));
				Shield_Time.Update_Text(std::to_string(10 - abs((int)Count_Shield - (int)Total_Shield)));
				Window.draw(Shield_Time.Text_Body);
			}
			Window.draw(textUser);

			/*Default_View*/

			Window.setView(Camera);
			Mouse_Position = Window.mapPixelToCoords(Mouse::getPosition(Window));
			Window.draw(Background8);
			for (int i = 0; i < Platforms.size(); i++)
			{
				Platforms[i].Draw(Window);
			}
			for (int i = 0; i < Metalbeing_Body.size(); i++)
			{
				Metalbeing_Body[i].Update(Difference, Player.GetPosition(), Window, Platforms);
			}
			for (int i = 0; i < Items.size(); i++)
			{
				Items[i].Update(Difference, Window);
			}
			for (int i = 0; i < Enemy_Score.size(); i++)
			{
				Enemy_Score[i].Update(Difference, Window);
			}			
			for (int i = 0; i < Warpgate_Body.size(); i++)
			{
				Warpgate_Body[i].Update(Difference, Window);
			}
			Player.Update(Difference, Mouse_Position, Window, Platforms, bulletVec, bullet);
			for (int i = 0; i < Warpscream_Body.size(); i++)
			{
				Warpscream_Body[i].Update(Difference, Platforms, White_force, Absorb, Player.GetPosition(), Window, Barrel_Body);
			}
			for (int i = 0; i < Barrel_Body.size(); i++)
			{
				Barrel_Body[i].Update(Difference,Window);
				if (Barrel_Body[i].isIceShield)
				{
					Barrel_Body[i].Get_Body().setPosition(Warpscream_Body[0].Get_Body().getPosition());
				}
			}
			if (isShieldON)
			{
				Window.draw(Shield);
			}
			Mouse_Cursor.setPosition(Mouse_Position);
			Window.draw(Mouse_Cursor);

			/*Chacter_View*/

			Window.setView(Character);
			Window.draw(Background8);
			for (int i = 0; i < Platforms.size(); i++)
			{
				Platforms[i].Draw(Window);
			}
			if (Player.Player_Visible)
				Player.Draw(Window);
			Window.display();
			break;
		}
		}
	}
	return 0;
}