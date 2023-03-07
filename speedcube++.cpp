#include "raylib.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

#define BACKGROUND (Color){151, 151, 151, 255}

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
		int X;
		int Y;
		int Speed;
		bool Collision;
		Rectangle Collider;
};

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
	printf("\n -- SpeedCube++ -- \nVersion 1.1.0\n\n");
	
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
	UnloadImage(WindowIcon);
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
	PlatformObject Platforms[16] = {{0}, {1}, {2}, {3}, {4}, {5}, 
	{6}, {7}, {8}, {9}, {10}, {11}, {12}, {13}, {14}, {15}};
	
	for(int i = 0; i <= 15; i++)
		Platforms[i].Y = 425;
	
	Texture2D PlatformTexture;
	
	BackgroundSetup(BackgroundTop, BackgroundBottom);
	PlatformTexture = LoadTexture("Sprites/Platform.png");
	
	Player.Texture = LoadTexture("Sprites/Player.png");
	
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
				for(int i = 1; i <=15; i++)
				{
					PlatformReset(Platforms[i], true);
				}
				Platforms[0].X = 120;
				Platforms[0].Y = 90;
				Platforms[0].Speed = 65;
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
			
			for(int i = 0; i <= 15; i++)
			{
				Platforms[i].X = (int)Platforms[i].X - (Platforms[i].Speed * DeltaTime);
			}
			
			if(Platforms[0].X < -64)
			{
				if(Platforms[0].Speed == 65)
				{
					Platforms[0].X = (rand() % 500) + 960;
					Platforms[0].Y = 425;
					Platforms[0].Speed = 425;
				}
				else
				{
					Platforms[0].X = (rand() % 500) + 960;
					Platforms[0].Speed = (rand() % 125) + 375;
				}
			}
			
			for(int i = 1; i <= 15; i++)
			{
				if(Platforms[i].X < -64)
					PlatformReset(Platforms[i], false);
			}
			
			Player.Collider = {(float)Player.X, (float)Player.Y, 10.0f, 10.0f};
			
			for(int i = 0; i <= 15; i++)
			{
				PlatformColliderUpdate(Platforms[i], Player);
			}
			
			if(!Platforms[0].Collision)
				if(!Platforms[1].Collision)
					if(!Platforms[2].Collision)
						if(!Platforms[3].Collision)
							if(!Platforms[4].Collision)
								if(!Platforms[5].Collision)
									if(!Platforms[6].Collision)
										if(!Platforms[7].Collision)
											if(!Platforms[8].Collision)
												if(!Platforms[9].Collision)
													if(!Platforms[10].Collision)
														if(!Platforms[11].Collision)
															if(!Platforms[12].Collision)
																if(!Platforms[13].Collision)
																	if(!Platforms[14].Collision)
																		if(!Platforms[15].Collision)
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
				
				if(Platforms[0].X < 960)
					DrawTexture(PlatformTexture, Platforms[0].X, Platforms[0].Y, WHITE);
					
				DrawTextEx(MediumFont, TextFormat("Score: %i", Score), (Vector2){25.0f, 10.0f}, 60, 1, WHITE);
				DrawTextEx(MediumFont, TextFormat("High Score: %i", HighScore), (Vector2){25.0f, 65.0f}, 30, 1, WHITE);
				
				for(int i = 1; i <= 15; i++)
				{
					if(Platforms[i].X < 960)
						DrawTexture(PlatformTexture, Platforms[i].X, Platforms[i].Y, WHITE);
				}
			}
			DrawText(TextFormat("%i", GetFPS()), 900, 25, 50, WHITE);
        
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
	UnloadTexture(PlatformTexture);
	
	UnloadRenderTexture(Target);
	
	UnloadFont(LargeFont);
	UnloadFont(MediumFont);
	UnloadFont(SmallFont);
	
	UnloadSound(GameStart);
	UnloadSound(PlayerDeath);
	
	UnloadMusicStream(BackgroundMusic);
	
	CloseWindow();
	CloseAudioDevice();
	
	return 0;
}
