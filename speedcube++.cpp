#include "raylib.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

#define BACKGROUND (Color){151, 151, 151, 255}

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

class BackgroundObject
{
	public:
		int X = 0;
		int Y = 0;
		Image BImage;
		Texture2D Texture;
};
class PlayerObject
{
	public:
		int X = 0;
		int Y = 0;
		int YForce = 0;
		bool Grounded = false;
		bool Dead = false;
		Image PImage;
		Texture2D Texture;
		Rectangle Collider;
};
class PlatformObject
{
	public:
		int X = 0;
		int Y = 450;
		int Speed = 0;
		bool Collision = false;
		Image PlImage;
		Texture2D Texture;
		Rectangle Collider;
};

int main(void)
{
	printf("\n -- SpeedCube++ -- \nVersion 1.0.0\n\n");
	const int ScreenWidth = 960;
	const int ScreenHeight = 540;
	const int Gravity = 100;
	int Score = 0;
	int HighScore = 0;
	float DeltaTime;
	int StartTime = 0;
	int CurrentTime = 0;
	int ElapsedTime = 0;
	bool Title = true;
	
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(ScreenWidth, ScreenHeight, "SpeedCube++");
	Image WindowIcon = LoadImage("Sprites/Icon.png");
	SetWindowIcon(WindowIcon);
	InitAudioDevice();
	SetTargetFPS(60);
	SetExitKey(KEY_F12);
	
	RenderTexture2D Target = LoadRenderTexture(ScreenWidth, ScreenHeight);
	SetTextureFilter(Target.texture, TEXTURE_FILTER_BILINEAR);
	
	Font LargeFont = LoadFontEx("RalewayBold.ttf", 170, NULL, 0);
	Font MediumFont = LoadFontEx("RalewayBold.ttf", 120, NULL, 0);
	Font SmallFont = LoadFontEx("RalewayBold.ttf", 80, NULL, 0);
		
	BackgroundObject BackgroundTop;
	BackgroundObject BackgroundBottom;
	PlayerObject Player;
	PlatformObject StartPlatform;
	PlatformObject Platform1;
	PlatformObject Platform2;
	PlatformObject Platform3;
	PlatformObject Platform4;
	PlatformObject Platform5;
	PlatformObject Platform6;
	PlatformObject Platform7;
	PlatformObject Platform8;
	PlatformObject Platform9;
	PlatformObject Platform10;
	PlatformObject Platform11;
	PlatformObject Platform12;
	PlatformObject Platform13;
	PlatformObject Platform14;
	PlatformObject Platform15;
	
	BackgroundTop.BImage = LoadImage("Sprites/BackgroundTop.png");
	BackgroundBottom.BImage = LoadImage("Sprites/BackgroundBottom.png");
	Player.PImage = LoadImage("Sprites/Player.png");
	StartPlatform.PlImage = LoadImage("Sprites/Platform.png");
	Platform1.PlImage = LoadImage("Sprites/Platform.png");
	Platform2.PlImage = LoadImage("Sprites/Platform.png");
	Platform3.PlImage = LoadImage("Sprites/Platform.png");
	Platform4.PlImage = LoadImage("Sprites/Platform.png");
	Platform5.PlImage = LoadImage("Sprites/Platform.png");
	Platform6.PlImage = LoadImage("Sprites/Platform.png");
	Platform7.PlImage = LoadImage("Sprites/Platform.png");
	Platform8.PlImage = LoadImage("Sprites/Platform.png");
	Platform9.PlImage = LoadImage("Sprites/Platform.png");
	Platform10.PlImage = LoadImage("Sprites/Platform.png");
	Platform11.PlImage = LoadImage("Sprites/Platform.png");
	Platform12.PlImage = LoadImage("Sprites/Platform.png");
	Platform13.PlImage = LoadImage("Sprites/Platform.png");
	Platform14.PlImage = LoadImage("Sprites/Platform.png");
	Platform15.PlImage = LoadImage("Sprites/Platform.png");
	
	BackgroundTop.Texture = LoadTextureFromImage(BackgroundTop.BImage);
	BackgroundBottom.Texture = LoadTextureFromImage(BackgroundBottom.BImage);
	Player.Texture = LoadTextureFromImage(Player.PImage);
	StartPlatform.Texture = LoadTextureFromImage(StartPlatform.PlImage);
	Platform1.Texture = LoadTextureFromImage(Platform1.PlImage);
	Platform2.Texture = LoadTextureFromImage(Platform2.PlImage);
	Platform3.Texture = LoadTextureFromImage(Platform3.PlImage);
	Platform4.Texture = LoadTextureFromImage(Platform4.PlImage);
	Platform5.Texture = LoadTextureFromImage(Platform5.PlImage);
	Platform6.Texture = LoadTextureFromImage(Platform6.PlImage);
	Platform7.Texture = LoadTextureFromImage(Platform7.PlImage);
	Platform8.Texture = LoadTextureFromImage(Platform8.PlImage);
	Platform9.Texture = LoadTextureFromImage(Platform9.PlImage);
	Platform10.Texture = LoadTextureFromImage(Platform10.PlImage);
	Platform11.Texture = LoadTextureFromImage(Platform11.PlImage);
	Platform12.Texture = LoadTextureFromImage(Platform12.PlImage);
	Platform13.Texture = LoadTextureFromImage(Platform13.PlImage);
	Platform14.Texture = LoadTextureFromImage(Platform14.PlImage);
	Platform15.Texture = LoadTextureFromImage(Platform15.PlImage);
	
	UnloadImage(BackgroundTop.BImage);
	UnloadImage(BackgroundBottom.BImage);
	UnloadImage(Player.PImage);
	UnloadImage(StartPlatform.PlImage);
	UnloadImage(Platform1.PlImage);
	UnloadImage(Platform2.PlImage);
	UnloadImage(Platform3.PlImage);
	UnloadImage(Platform4.PlImage);
	UnloadImage(Platform5.PlImage);
	UnloadImage(Platform6.PlImage);
	UnloadImage(Platform7.PlImage);
	UnloadImage(Platform8.PlImage);
	UnloadImage(Platform9.PlImage);
	UnloadImage(Platform10.PlImage);
	UnloadImage(Platform11.PlImage);
	UnloadImage(Platform12.PlImage);
	UnloadImage(Platform13.PlImage);
	UnloadImage(Platform14.PlImage);
	UnloadImage(Platform15.PlImage);
	
	Music BackgroundMusic = LoadMusicStream("Audio/BackgroundMusic.ogg");
	PlayMusicStream(BackgroundMusic);
	
	Sound GameStart = LoadSound("Audio/GameStart.wav");
	Sound PlayerDeath = LoadSound("Audio/PlayerDeath.wav");
	
	while(!WindowShouldClose())
	{
		DeltaTime = GetFrameTime();

		UpdateMusicStream(BackgroundMusic);
		
		float scale = MIN((float)GetScreenWidth()/ScreenWidth, (float)GetScreenHeight()/ScreenHeight);
		
		if(Title)
		{
			if(IsKeyDown(KEY_ENTER))
			{
				PlaySound(GameStart);
				Title = false;
				StartTime = time(0);
				ElapsedTime = 0;
				Score = 0;
				Player.X = 147;
				Player.Y = 80;
				Player.YForce = 0;
				Player.Dead = false;
				StartPlatform.X = 120;
				StartPlatform.Y = 90;
				StartPlatform.Speed = 65;
				Platform1.X = (rand() % 500) + 960;
				Platform1.Speed = (rand() % 125) + 375;
				Platform2.X = (rand() % 500) + 960;
				Platform2.Speed = (rand() % 125) + 250;
				Platform3.X = (rand() % 500) + 960;
				Platform3.Speed = (rand() % 125) + 250;
				Platform4.X = (rand() % 500) + 960;
				Platform4.Speed = (rand() % 125) + 250;
				Platform5.X = (rand() % 500) + 960;
				Platform5.Speed = (rand() % 125) + 250;
				Platform6.X = (rand() % 500) + 960;
				Platform6.Speed = (rand() % 125) + 250;
				Platform7.X = (rand() % 500) + 960;
				Platform7.Speed = (rand() % 125) + 250;
				Platform8.X = (rand() % 500) + 960;
				Platform8.Speed = (rand() % 125) + 250;
				Platform9.X = (rand() % 500) + 960;
				Platform9.Speed = (rand() % 125) + 250;
				Platform10.X = (rand() % 500) + 960;
				Platform10.Speed = (rand() % 125) + 250;
				Platform11.X = (rand() % 500) + 960;
				Platform11.Speed = (rand() % 125) + 250;
				Platform12.X = (rand() % 500) + 960;
				Platform12.Speed = (rand() % 125) + 250;
				Platform13.X = (rand() % 500) + 960;
				Platform13.Speed = (rand() % 125) + 250;
				Platform14.X = (rand() % 500) + 960;
				Platform14.Speed = (rand() % 125) + 250;
				Platform15.X = (rand() % 500) + 960;
				Platform15.Speed = (rand() % 125) + 250;
			}
		}
		else
 		{
			if(IsKeyDown(KEY_LEFT))
				if(!IsKeyDown(KEY_RIGHT))
					Player.X = (int)Player.X - (625 * DeltaTime);
			if(IsKeyDown(KEY_RIGHT))
				if(!IsKeyDown(KEY_LEFT))
					Player.X = (int)Player.X + (625 * DeltaTime);
			
			if(IsKeyDown(KEY_UP))
				if(Player.Grounded)
				{
					Player.Y = Player.Y - 2;
					Player.YForce = (int)Player.YForce - (1250 * DeltaTime);
					Player.Grounded = false;
				}
			
			StartPlatform.X = (int)StartPlatform.X - (StartPlatform.Speed * DeltaTime);
			Platform1.X = (int)Platform1.X - (Platform1.Speed * DeltaTime);
			Platform2.X = (int)Platform2.X - (Platform2.Speed * DeltaTime);
			Platform3.X = (int)Platform3.X - (Platform3.Speed * DeltaTime);
			Platform4.X = (int)Platform4.X - (Platform4.Speed * DeltaTime);
			Platform5.X = (int)Platform5.X - (Platform5.Speed * DeltaTime);
			Platform6.X = (int)Platform6.X - (Platform6.Speed * DeltaTime);
			Platform7.X = (int)Platform7.X - (Platform7.Speed * DeltaTime);
			Platform8.X = (int)Platform8.X - (Platform8.Speed * DeltaTime);
			Platform9.X = (int)Platform9.X - (Platform9.Speed * DeltaTime);
			Platform10.X = (int)Platform10.X - (Platform10.Speed * DeltaTime);
			Platform11.X = (int)Platform11.X - (Platform11.Speed * DeltaTime);
			Platform12.X = (int)Platform12.X - (Platform12.Speed * DeltaTime);
			Platform13.X = (int)Platform13.X - (Platform13.Speed * DeltaTime);
			Platform14.X = (int)Platform14.X - (Platform14.Speed * DeltaTime);
			Platform15.X = (int)Platform15.X - (Platform15.Speed * DeltaTime);
			
			if(StartPlatform.X < -64)
			{
				if(StartPlatform.Speed == 65)
				{
					StartPlatform.X = (rand() % 500) + 960;
					StartPlatform.Y = 450;
					StartPlatform.Speed = 425;
				}
				else
				{
				StartPlatform.X = (rand() % 500) + 960;
				StartPlatform.Speed = (rand() % 125) + 375;
				}
			}
			if(Platform1.X < -64)
			{
				Platform1.X = (rand() % 500) + 960;
				Platform1.Speed = (rand() % 125) + 375;
			}
			if(Platform2.X < -64)
			{
				Platform2.X = (rand() % 500) + 960;
				Platform2.Speed = (rand() % 125) + 375;
			}
			if(Platform3.X < -64)
			{
				Platform3.X = (rand() % 500) + 960;
				Platform3.Speed = (rand() % 125) + 375;
			}
			if(Platform4.X < -64)
			{
				Platform4.X = (rand() % 500) + 960;
				Platform4.Speed = (rand() % 125) + 375;
			}
			if(Platform5.X < -64)
			{
				Platform5.X = (rand() % 500) + 960;
				Platform5.Speed = (rand() % 125) + 375;
			}
			if(Platform6.X < -64)
			{
				Platform6.X = (rand() % 500) + 960;
				Platform6.Speed = (rand() % 125) + 375;
			}
			if(Platform7.X < -64)
			{
				Platform7.X = (rand() % 500) + 960;
				Platform7.Speed = (rand() % 125) + 375;
			}
			if(Platform8.X < -64)
			{
				Platform8.X = (rand() % 500) + 960;
				Platform8.Speed = (rand() % 125) + 375;
			}
			if(Platform9.X < -64)
			{
				Platform9.X = (rand() % 500) + 960;
				Platform9.Speed = (rand() % 125) + 375;
			}
			if(Platform10.X < -64)
			{
				Platform10.X = (rand() % 500) + 960;
				Platform10.Speed = (rand() % 125) + 375;
			}
			if(Platform11.X < -64)
			{
				Platform11.X = (rand() % 500) + 960;
				Platform11.Speed = (rand() % 125) + 375;
			}
			if(Platform12.X < -64)
			{
				Platform12.X = (rand() % 500) + 960;
				Platform12.Speed = (rand() % 125) + 375;
			}
			if(Platform13.X < -64)
			{
				Platform13.X = (rand() % 500) + 960;
				Platform13.Speed = (rand() % 125) + 375;
			}
			if(Platform14.X < -64)
			{
				Platform14.X = (rand() % 500) + 960;
				Platform14.Speed = (rand() % 125) + 375;
			}
			if(Platform15.X < -64)
			{
				Platform15.X = (rand() % 500) + 960;
				Platform15.Speed = (rand() % 125) + 375;
			}
			
			Player.Collider = {(float)Player.X, (float)Player.Y, 10.0f, 10.0f};
			StartPlatform.Collider = {(float)StartPlatform.X, (float)StartPlatform.Y, 64.0f, 24.0f};
			Platform1.Collider = {(float)Platform1.X, (float)Platform1.Y, 64.0f, 24.0f};
			Platform2.Collider = {(float)Platform2.X, (float)Platform2.Y, 64.0f, 24.0f};
			Platform3.Collider = {(float)Platform3.X, (float)Platform3.Y, 64.0f, 24.0f};
			Platform4.Collider = {(float)Platform4.X, (float)Platform4.Y, 64.0f, 24.0f};
			Platform5.Collider = {(float)Platform5.X, (float)Platform5.Y, 64.0f, 24.0f};
			Platform6.Collider = {(float)Platform6.X, (float)Platform6.Y, 64.0f, 24.0f};
			Platform7.Collider = {(float)Platform7.X, (float)Platform7.Y, 64.0f, 24.0f};
			Platform8.Collider = {(float)Platform8.X, (float)Platform8.Y, 64.0f, 24.0f};
			Platform9.Collider = {(float)Platform9.X, (float)Platform9.Y, 64.0f, 24.0f};
			Platform10.Collider = {(float)Platform10.X, (float)Platform10.Y, 64.0f, 24.0f};
			Platform11.Collider = {(float)Platform11.X, (float)Platform11.Y, 64.0f, 24.0f};
			Platform12.Collider = {(float)Platform12.X, (float)Platform12.Y, 64.0f, 24.0f};
			Platform13.Collider = {(float)Platform13.X, (float)Platform13.Y, 64.0f, 24.0f};
			Platform14.Collider = {(float)Platform14.X, (float)Platform14.Y, 64.0f, 24.0f};
			Platform15.Collider = {(float)Platform15.X, (float)Platform15.Y, 64.0f, 24.0f};
			
			StartPlatform.Collision = CheckCollisionRecs(Player.Collider, StartPlatform.Collider);
			Platform1.Collision = CheckCollisionRecs(Player.Collider, Platform1.Collider);
			Platform2.Collision = CheckCollisionRecs(Player.Collider, Platform2.Collider);
			Platform3.Collision = CheckCollisionRecs(Player.Collider, Platform3.Collider);
			Platform4.Collision = CheckCollisionRecs(Player.Collider, Platform4.Collider);
			Platform5.Collision = CheckCollisionRecs(Player.Collider, Platform5.Collider);
			Platform6.Collision = CheckCollisionRecs(Player.Collider, Platform6.Collider);
			Platform7.Collision = CheckCollisionRecs(Player.Collider, Platform7.Collider);
			Platform8.Collision = CheckCollisionRecs(Player.Collider, Platform8.Collider);
			Platform9.Collision = CheckCollisionRecs(Player.Collider, Platform9.Collider);
			Platform10.Collision = CheckCollisionRecs(Player.Collider, Platform10.Collider);
			Platform11.Collision = CheckCollisionRecs(Player.Collider, Platform11.Collider);
			Platform12.Collision = CheckCollisionRecs(Player.Collider, Platform12.Collider);
			Platform13.Collision = CheckCollisionRecs(Player.Collider, Platform13.Collider);
			Platform14.Collision = CheckCollisionRecs(Player.Collider, Platform14.Collider);
			Platform15.Collision = CheckCollisionRecs(Player.Collider, Platform15.Collider);
			
			if(StartPlatform.Collision)
			{
				Player.Y = StartPlatform.Y - 9;
				Player.Grounded = true;
			}
			else if(Platform1.Collision)
			{
				Player.Y = Platform1.Y - 9;
				Player.Grounded = true;
			}
			else if(Platform2.Collision)
			{
				Player.Y = Platform2.Y - 9;
				Player.Grounded = true;
			}
			else if(Platform3.Collision)
			{
				Player.Y = Platform3.Y - 9;
				Player.Grounded = true;
			}
			else if(Platform4.Collision)
			{
				Player.Y = Platform4.Y - 9;
				Player.Grounded = true;
			}
			else if(Platform5.Collision)
			{
				Player.Y = Platform5.Y - 9;
				Player.Grounded = true;
			}
			else if(Platform6.Collision)
			{
				Player.Y = Platform6.Y - 9;
				Player.Grounded = true;
			}
			else if(Platform7.Collision)
			{
				Player.Y = Platform7.Y - 9;
				Player.Grounded = true;
			}
			else if(Platform8.Collision)
			{
				Player.Y = Platform8.Y - 9;
				Player.Grounded = true;
			}
			else if(Platform9.Collision)
			{
				Player.Y = Platform9.Y - 9;
				Player.Grounded = true;
			}
			else if(Platform10.Collision)
			{
				Player.Y = Platform10.Y - 9;
				Player.Grounded = true;
			}
			else if(Platform11.Collision)
			{
				Player.Y = Platform11.Y - 9;
				Player.Grounded = true;
			}
			else if(Platform12.Collision)
			{
				Player.Y = Platform12.Y - 9;
				Player.Grounded = true;
			}
			else if(Platform13.Collision)
			{
				Player.Y = Platform13.Y - 9;
				Player.Grounded = true;
			}
			else if(Platform14.Collision)
			{
				Player.Y = Platform14.Y - 9;
				Player.Grounded = true;
			}
			else if(Platform15.Collision)
			{
				Player.Y = Platform15.Y - 9;
				Player.Grounded = true;
			}
			
			if(!StartPlatform.Collision)
			{
				if(!Platform1.Collision)
					if(!Platform2.Collision)
						if(!Platform3.Collision)
							if(!Platform4.Collision)
								if(!Platform5.Collision)
									if(!Platform6.Collision)
										if(!Platform7.Collision)
											if(!Platform8.Collision)
												if(!Platform9.Collision)
													if(!Platform10.Collision)
														if(!Platform11.Collision)
															if(!Platform12.Collision)
																if(!Platform13.Collision)
																	if(!Platform14.Collision)
																		if(!Platform15.Collision)
																			Player.Grounded = false;
			}
			
			if(Player.Grounded)
				Player.YForce = 0;
			else
				Player.YForce = (int)Player.YForce + (Gravity * DeltaTime);
			
			Player.Y = Player.Y + Player.YForce;
			
			if(Player.Y > 530 || Player.X < -10)
				Player.Dead = true;
			
			CurrentTime = time(0);
			ElapsedTime = CurrentTime - StartTime;
			
			if(ElapsedTime == 1)
			{
				Score = Score + 1;
				StartTime = time(0);
			}
			
			if(Score > HighScore)
				HighScore = Score;
			
			if(Player.Dead)
			{
				PlaySound(PlayerDeath);
				Title = true;
			}
		}
		
		BeginTextureMode(Target);
		
		ClearBackground(BACKGROUND);
		
		DrawTexture(BackgroundTop.Texture, 0, 0, WHITE);
		DrawTexture(BackgroundBottom.Texture, 0, 390, WHITE);
		
		if(Title)
		{
			DrawTextEx(LargeFont, "SpeedCube", (Vector2){270.0f, 100.0f}, 85, 3, WHITE);
			DrawTextEx(SmallFont, "++", (Vector2){700.0f, 115.0f}, 40, 3, WHITE);
			DrawTextEx(SmallFont, "Enter to Start", (Vector2){365.0f, 225.0f}, 40, 1, WHITE);
			DrawTextEx(SmallFont, "https://the-gaminggamer.itch.io", (Vector2){25.0f, 510.0f}, 20, 1, WHITE);
		}
		else
		{
			DrawTexture(Player.Texture, Player.X, Player.Y, BACKGROUND);
			if(StartPlatform.X < 960)
				DrawTexture(StartPlatform.Texture, StartPlatform.X, StartPlatform.Y, WHITE);
			DrawTextEx(MediumFont, TextFormat("Score: %i", Score), (Vector2){25.0f, 10.0f}, 60, 1, WHITE);
			DrawTextEx(MediumFont, TextFormat("High Score: %i", HighScore), (Vector2){25.0f, 65.0f}, 30, 1, WHITE);
			if(Platform1.X < 960)
				DrawTexture(Platform1.Texture, Platform1.X, Platform1.Y, WHITE);
			if(Platform2.X < 960)
				DrawTexture(Platform2.Texture, Platform2.X, Platform2.Y, WHITE);
			if(Platform3.X < 960)
				DrawTexture(Platform3.Texture, Platform3.X, Platform3.Y, WHITE);
			if(Platform4.X < 960)
				DrawTexture(Platform4.Texture, Platform4.X, Platform4.Y, WHITE);
			if(Platform5.X < 960)
				DrawTexture(Platform5.Texture, Platform5.X, Platform5.Y, WHITE);
			if(Platform6.X < 960)
				DrawTexture(Platform1.Texture, Platform6.X, Platform6.Y, WHITE);
			if(Platform7.X < 960)
				DrawTexture(Platform2.Texture, Platform7.X, Platform7.Y, WHITE);
			if(Platform8.X < 960)
				DrawTexture(Platform3.Texture, Platform8.X, Platform8.Y, WHITE);
			if(Platform9.X < 960)
				DrawTexture(Platform4.Texture, Platform9.X, Platform9.Y, WHITE);
			if(Platform10.X < 960)
				DrawTexture(Platform5.Texture, Platform10.X, Platform10.Y, WHITE);
			if(Platform11.X < 960)
				DrawTexture(Platform1.Texture, Platform11.X, Platform11.Y, WHITE);
			if(Platform12.X < 960)
				DrawTexture(Platform2.Texture, Platform12.X, Platform12.Y, WHITE);
			if(Platform13.X < 960)
				DrawTexture(Platform3.Texture, Platform13.X, Platform13.Y, WHITE);
			if(Platform14.X < 960)
				DrawTexture(Platform4.Texture, Platform14.X, Platform14.Y, WHITE);
			if(Platform15.X < 960)
				DrawTexture(Platform5.Texture, Platform15.X, Platform15.Y, WHITE);
		}
		
		EndTextureMode();
		
		BeginDrawing();
		
		ClearBackground(BLACK);
		
		DrawTexturePro(Target.texture, (Rectangle){ 0.0f, 0.0f, (float)Target.texture.width, (float)-Target.texture.height },
                           (Rectangle){ (GetScreenWidth() - ((float)ScreenWidth*scale))*0.5f, (GetScreenHeight() - ((float)ScreenHeight*scale))*0.5f,
                           (float)ScreenWidth*scale, (float)ScreenHeight*scale }, (Vector2){ 0, 0 }, 0.0f, WHITE);
		
		EndDrawing();
	}
	
	UnloadTexture(Player.Texture);
	UnloadTexture(BackgroundTop.Texture);
	UnloadTexture(BackgroundBottom.Texture);
	UnloadTexture(StartPlatform.Texture);
	UnloadTexture(Platform1.Texture);
	UnloadTexture(Platform2.Texture);
	UnloadTexture(Platform3.Texture);
	UnloadTexture(Platform4.Texture);
	UnloadTexture(Platform5.Texture);
	UnloadTexture(Platform6.Texture);
	UnloadTexture(Platform7.Texture);
	UnloadTexture(Platform8.Texture);
	UnloadTexture(Platform9.Texture);
	UnloadTexture(Platform10.Texture);
	UnloadTexture(Platform11.Texture);
	UnloadTexture(Platform12.Texture);
	UnloadTexture(Platform13.Texture);
	UnloadTexture(Platform14.Texture);
	UnloadTexture(Platform15.Texture);
	
	UnloadRenderTexture(Target);
	
	CloseWindow();
	CloseAudioDevice();
	
	return 0;
}
