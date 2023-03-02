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

void PlatformSetup(PlatformObject& Platform)
{
	Platform.PlImage = LoadImage("Sprites/Platform.png");
	Platform.Texture = LoadTextureFromImage(Platform.PlImage);
	UnloadImage(Platform.PlImage);
}

void PlatformReset(PlatformObject& Platform, bool Start)
{
	if(Start)
	{
		Platform.X = (rand() % 500) + 960;
		Platform.Speed = (rand() % 125) + 250;
	}
	else
	{
		Platform.X = (rand() % 500) + 960;
		Platform.Speed = (rand() % 125) + 375;
	}
}

void PlatformColliderUpdate(PlatformObject& Platform, PlayerObject& Player)
{
	Platform.Collider = {(float)Platform.X, (float)Platform.Y, 64.0f, 24.0f};
	Platform.Collision = CheckCollisionRecs(Player.Collider, Platform.Collider);
	if(Platform.Collision)
	{
		Player.Y = Platform.Y - 9;
		Player.Grounded = true;
	}
}

void BackgroundSetup(BackgroundObject& BackgroundTop, BackgroundObject& BackgroundBottom)
{
	BackgroundTop.BImage = LoadImage("Sprites/BackgroundTop.png");
	BackgroundTop.Texture = LoadTextureFromImage(BackgroundTop.BImage);
	BackgroundBottom.BImage = LoadImage("Sprites/BackgroundBottom.png");
	BackgroundBottom.Texture = LoadTextureFromImage(BackgroundBottom.BImage);
	UnloadImage(BackgroundTop.BImage);
	UnloadImage(BackgroundBottom.BImage);
}

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
	
	BackgroundSetup(BackgroundTop, BackgroundBottom);
	PlatformSetup(StartPlatform);
	PlatformSetup(Platform1);
	PlatformSetup(Platform2);
	PlatformSetup(Platform3);
	PlatformSetup(Platform4);
	PlatformSetup(Platform5);
	PlatformSetup(Platform6);
	PlatformSetup(Platform7);
	PlatformSetup(Platform8);
	PlatformSetup(Platform9);
	PlatformSetup(Platform10);
	PlatformSetup(Platform11);
	PlatformSetup(Platform12);
	PlatformSetup(Platform13);
	PlatformSetup(Platform14);
	PlatformSetup(Platform15);
	
	Player.PImage = LoadImage("Sprites/Player.png");
	Player.Texture = LoadTextureFromImage(Player.PImage);
	UnloadImage(Player.PImage);
	
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
				PlatformReset(Platform1, true);
				PlatformReset(Platform2, true);
				PlatformReset(Platform3, true);
				PlatformReset(Platform4, true);
				PlatformReset(Platform5, true);
				PlatformReset(Platform6, true);
				PlatformReset(Platform7, true);
				PlatformReset(Platform8, true);
				PlatformReset(Platform9, true);
				PlatformReset(Platform10, true);
				PlatformReset(Platform11, true);
				PlatformReset(Platform12, true);
				PlatformReset(Platform13, true);
				PlatformReset(Platform14, true);
				PlatformReset(Platform15, true);
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
				PlatformReset(Platform1, false);
			if(Platform2.X < -64)
				PlatformReset(Platform2, false);
			if(Platform3.X < -64)
				PlatformReset(Platform3, false);
			if(Platform4.X < -64)
				PlatformReset(Platform4, false);
			if(Platform5.X < -64)
				PlatformReset(Platform5, false);
			if(Platform6.X < -64)
				PlatformReset(Platform6, false);
			if(Platform7.X < -64)
				PlatformReset(Platform7, false);
			if(Platform8.X < -64)
				PlatformReset(Platform8, false);
			if(Platform9.X < -64)
				PlatformReset(Platform9, false);
			if(Platform10.X < -64)
				PlatformReset(Platform10, false);
			if(Platform11.X < -64)
				PlatformReset(Platform11, false);
			if(Platform12.X < -64)
				PlatformReset(Platform12, false);
			if(Platform13.X < -64)
				PlatformReset(Platform13, false);
			if(Platform14.X < -64)
				PlatformReset(Platform14, false);
			if(Platform15.X < -64)
				PlatformReset(Platform15, false);
			
			Player.Collider = {(float)Player.X, (float)Player.Y, 10.0f, 10.0f};
			PlatformColliderUpdate(StartPlatform, Player);
			PlatformColliderUpdate(Platform1, Player);
			PlatformColliderUpdate(Platform2, Player);
			PlatformColliderUpdate(Platform3, Player);
			PlatformColliderUpdate(Platform4, Player);
			PlatformColliderUpdate(Platform5, Player);
			PlatformColliderUpdate(Platform6, Player);
			PlatformColliderUpdate(Platform7, Player);
			PlatformColliderUpdate(Platform8, Player);
			PlatformColliderUpdate(Platform9, Player);
			PlatformColliderUpdate(Platform10, Player);
			PlatformColliderUpdate(Platform11, Player);
			PlatformColliderUpdate(Platform12, Player);
			PlatformColliderUpdate(Platform13, Player);
			PlatformColliderUpdate(Platform14, Player);
			PlatformColliderUpdate(Platform15, Player);
			
			if(!StartPlatform.Collision)
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
