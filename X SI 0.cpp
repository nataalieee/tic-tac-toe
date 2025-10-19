// X SI 0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"

using namespace std;
int harta[3][3],cnt,winner,mutare=-1,juc=1, fer=1,game_mode, mouse_ready,g_round=1;
int sumdig1, sumdig2, sumlin[3], sumcol[3], sumlin_2[3], sumcol_2[3],sd1,sd2;

class GAME
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isrunning = 0;
    int frame;
    SDL_Texture* a, * b, *xw, *ow, *draw, *window_1, *but_1, *but_2;
public:
    
    SDL_Texture* LoadTexture(const char* name)
    {
        char path[120] = "x64/debug/";
        strcat_s(path, name);
        SDL_Surface* temps = IMG_Load(path);
        SDL_Texture* tempt;
        tempt = SDL_CreateTextureFromSurface(renderer, temps);
        SDL_FreeSurface(temps);
        return tempt;
    }

    GAME() = default;
    bool running()
    {
        return isrunning;
    }
    void init(const char* title, int posx, int posy, int width, int height, bool fullscreen)
    {
        int flags = 0;
        if (fullscreen)flags = SDL_WINDOW_FULLSCREEN;
        if (SDL_Init(SDL_INIT_VIDEO) == 0)
        {
            cout << "SDL INITIALIZAT..." << '\n';
            window = SDL_CreateWindow("SDL2 Window", posx, posy, width, height, flags);
            if (window)
            {
                cout << "FEREASTRA INITIALIZATA..." << '\n';
                renderer = SDL_CreateRenderer(window, -1, 0);
                if (renderer)
                {
                    cout << "RENDERER INITIALIZAT..." << '\n';

                    SDL_Surface* temps = IMG_Load("x64/debug/x.png");
                    a = SDL_CreateTextureFromSurface(renderer, temps);
                    SDL_FreeSurface(temps);
                    temps = IMG_Load("x64/debug/o.png");
                    b = SDL_CreateTextureFromSurface(renderer, temps);
                    SDL_FreeSurface(temps);
                    xw = LoadTexture("x_win.png");
                    ow = LoadTexture("o_win.png");
                    draw = LoadTexture("draw.png");
                    window_1= LoadTexture("fer_1.png");
                    but_1 = LoadTexture("button_1.png");
                    but_2 = LoadTexture("button_2.png");
                    isrunning = 1;
                }
            }

        }

    }
    void HandleEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                isrunning = 0;
        }

        int x, y;
        Uint32 buttons = SDL_GetMouseState(&x, &y);

        if (fer == 1) {
            if (buttons & SDL_BUTTON(1)) {
                if (150 <= x && x <= 450 && 300 <= y && y <= 440) {
                    game_mode = 1;
                    fer = 2;
                    mouse_ready = 0; // don't allow input immediately
                }
                else if (150 <= x && x <= 450 && 440 < y && y <= 580) {
                    game_mode = 2;
                    fer = 2;
                    mouse_ready = 0;
                }
            }
        }
        else {
            // If mouse is NOT pressed, set mouse_ready
            if (!(buttons & SDL_BUTTON(1))) {
                mouse_ready = 1;
            }

            // Only allow clicks after releasing the button once
            if ((buttons & SDL_BUTTON(1)) && mouse_ready) {
                if (!harta[y / 200][x/ 200]) {
                    mutare = (y / 200) * 3 + x / 200;
                }
            }
        }


    }
    void check_win(int val, int juc)
    {
        if (harta[0][1] == val && harta[0][0] == val && harta[0][2] == val) winner = juc;
        else if (harta[1][0] == val && harta[1][1] == val && harta[1][2] == val) winner = juc;
        else if (harta[2][0] == val && harta[2][1] == val && harta[2][2] == val) winner = juc;
        else if (harta[0][0] == val && harta[1][0] == val && harta[2][0] == val) winner = juc;
        else if (harta[0][1] == val && harta[1][1] == val && harta[2][1] == val) winner = juc;
        else if (harta[0][2] == val && harta[1][2] == val && harta[2][2] == val) winner = juc;
        else if (harta[0][0] == val && harta[1][1] == val && harta[2][2] == val)winner = juc;
        else if (harta[2][0] == val && harta[1][1] == val && harta[0][2] == val) winner = juc;
    }
    void Update()
    {
        ///frame++;
        //cout << frame << '\n';
        if (game_mode == 2)
        {
            if (mutare != -1)
            {
                cnt++;
                int ox = mutare / 3;
                int oy = mutare % 3;
                if (juc == 1)
                {
                    juc = 2;
                    harta[ox][oy] = 1;
                    if (harta[ox][0] == 1 && harta[ox][1] == 1 && harta[ox][2] == 1)winner = 1;
                    if (harta[0][oy] == 1 && harta[1][oy] == 1 && harta[2][oy] == 1)winner = 1;
                    if (harta[0][0] == 1 && harta[1][1] == 1 && harta[2][2] == 1)winner = 1;
                    if (harta[0][2] == 1 && harta[1][1] == 1 && harta[2][0] == 1)winner = 1;
                }
                else
                {
                    harta[ox][oy] = 2;
                    juc = 1;
                    harta[ox][oy] = 2;
                    if (harta[ox][0] == 2 && harta[ox][1] == 2 && harta[ox][2] == 2)winner = 2;
                    if (harta[0][oy] == 2 && harta[1][oy] == 2 && harta[2][oy] == 2)winner = 2;
                    if (harta[0][0] == 2 && harta[1][1] == 2 && harta[2][2] == 2)winner = 2;
                    if (harta[0][2] == 2 && harta[1][1] == 2 && harta[2][0] == 2)winner = 2;
                }
                if (cnt == 9 && winner == 0)winner = 3;
                mutare = -1;
            }
        }

        else
        {
           
            if (mutare != -1)
            {
                cnt++;
                int ox = mutare / 3;
                sumlin[ox]++;
                int oy = mutare % 3;
                sumcol[oy]++;
                
                if ((ox == 0 && oy == 0) || (ox == 1 && oy == 1 )||( ox == 2 && oy == 2)) sumdig1++;
                if ((ox == 0 && oy == 2) || (ox == 1 && oy == 1 )|| (ox == 2 && oy == 0)) sumdig2++;

                harta[ox][oy] = 1;
                ///cout << sumlin[1] << '\n';
                if (harta[ox][0] == 1 && harta[ox][1] == 1 && harta[ox][2] == 1)winner = 1;
                if (harta[0][oy] == 1 && harta[1][oy] == 1 && harta [2][oy] == 1)winner = 1;
                if (harta[0][0] == 1 && harta[1][1] == 1 && harta[2][2] == 1)winner = 1;
                if (harta[0][2] == 1 && harta[1][1] == 1 && harta[2][0] == 1)winner = 1;

                if (cnt == 9 && winner == 0) winner = 3;
                else if (g_round%2  == 1) ///incepe playerul
                {
                   cnt++;
                   if (!winner)
                    {
                        bool am_ales = 0;
                        if (sd1 == 2 && !am_ales)
                        {
                            bool pus = 0;
                            for (int i = 0;i <= 2 &&!pus;i++) 
                                if (!harta[i][i])
                                {
                                     harta[i][i] = 2; am_ales = 1; pus = 1;
                                     sumlin_2[i]++; sumcol_2[i]++; sd1++;
                                     if (i == 1) sd2++;
                                }

                            if(sd1==3) 
                            {
                                winner = 2; 
                            }
                        }
                        if (sd2 == 2 && !am_ales)
                        {
                            bool pus = 0;
                            for (int i = 0;i <= 2 && !pus;i++) 
                                if (!harta[i][2 - i] )
                                {
                                    harta[i][2 - i] = 2; am_ales = 1; pus = 1;
                                    sumlin_2[i]++; sumcol_2[2 - i]++; sd2++;
                                    if (i == 1) sd1++;
                                    
                                }

                            if (sd2==3)
                            {
                                winner = 2;
                            }
                        }
                        if(!am_ales )
                        {
                            bool pus = 0;
                            for (int i = 0;i <= 2 && !pus;i++)
                            {
                                if (sumlin_2[i] == 2)
                                {
                                    for (int j = 0;j <= 2 && !pus;j++)
                                        if (!harta[i][j])
                                        {
                                            harta[i][j] = 2;
                                            pus = 1; am_ales = 1;
                                            sumlin_2[i]++; sumcol_2[j]++;
                                            if (i == j) sd1++;
                                            else if (i + j == 2) sd2++;
                                            
                                        }
                                }

                                if (sumlin_2[i] == 3) winner = 2;
                            }
                            for (int j = 0;j <= 2 && !pus;j++)
                            {
                                if (sumcol_2[j] == 2)
                                {
                                    for (int i = 0;i <= 2 && !pus;i++)
                                        if (!harta[i][j])
                                        {
                                            harta[i][j] = 2;
                                            pus = 1; am_ales = 1;
                                            sumlin_2[i]++; sumcol_2[j]++;
                                            if (i == j) sd1++;
                                            else if (i + j == 2) sd2++;

                                        }

                                }
                                if (sumcol_2[j] == 3) winner = 2;
                            }

                        }

                            if (sumdig1 == 2 && !am_ales)
                            {
                                
                                bool pus = 0;
                                for (int i = 0;i <= 2 && !pus ;i++) 
                                if (!harta[i][i])
                                {
                                    harta[i][i] = 2; am_ales = 1; pus = 1;
                                    sumlin_2[i]++; sumcol_2[i]++; sd1++;
                                    if (i == 1) sd2++;

                                }
                            }
                             if (sumdig2 == 2 && !am_ales)
                            {
                                bool pus = 0;
                                for (int i = 0;i <= 2 &&!pus;i++) 
                                    if (!harta[i][2 - i] )
                                    {
                                        harta[i][2 - i] = 2; am_ales = 1; pus = 1;
                                        sumlin_2[i]++; sumcol_2[2 - i]++; sd2++;
                                        if (i == 1) sd1++;
                                    }
                            }
                            if(!am_ales)
                            {
                                bool pus = 0;
                                for (int i = 0;i <= 2 && !pus;i++)
                                {
                                    
                                    if (sumlin[i] == 2)
                                    {
                                        for (int j = 0;j <= 2 && !pus;j++)
                                            if (!harta[i][j])
                                            {
                                                harta[i][j] = 2;
                                                pus = 1; am_ales = 1;
                                                sumlin_2[i]++; sumcol_2[j]++;
                                                if (i == j) sd1++;
                                                else if (i + j == 2) sd2++;
                                                
                                            }
                                    }
                                }
                                for (int j = 0;j <= 2 && !pus;j++)
                                {
                                    if (sumcol[j] == 2)
                                    {
                                        for (int i = 0;i <= 2 && !pus;i++)
                                            if (!harta[i][j])
                                            {
                                                harta[i][j] = 2;
                                                pus = 1; am_ales = 1;
                                                sumlin_2[i]++; sumcol_2[j]++;
                                                if (i == j) sd1++;
                                                else if (i + j == 2) sd2++;
                                               
                                            }
                                    }
                                }
                            }
                            check_win(2,2);
                            
                        
                        if (!am_ales)
                        {
                            if (!harta[1][1])
                            {
                                harta[1][1] = 2;
                                sd1++; sd2++; sumcol_2[1]++; sumlin_2[1]++;
                                am_ales = 1;

                            }
                            
                            else  if (!harta[0][0])
                            {
                                harta[0][0] = 2;am_ales = 1;
                                sumcol_2[0]++; sumlin_2[0]++;
                                sd1++; 
                            }
                            else  if (!harta[0][2])
                            {
                                harta[0][2] = 2; am_ales = 1;
                                sumcol_2[2]++; sumlin_2[0]++;
                                sd1++;
                            }
                            else  if (!harta[2][0])
                            {
                                harta[2][0] = 2;am_ales = 1;
                                sumcol_2[0]++; sumlin_2[2]++;
                                sd2++;
                            }
                            else  if (!harta[2][2]) 
                            {
                                harta[2][2] = 2; am_ales = 1;
                                sumcol_2[2]++; sumlin_2[2]++;
                                sd2++;
                            }

                            else  if (!harta[0][1])
                            {
                                harta[0][1] = 2; am_ales = 1;
                                sumlin_2[0]++; sumcol_2[1]++;
                            }
                            else  if (!harta[1][0])
                            {
                                harta[1][0] = 2; am_ales = 1;
                                sumlin_2[1]++; sumcol_2[0]++;
                            }
                            else  if (!harta[1][2])
                            {
                                harta[1][2] = 2; am_ales = 1;
                                sumlin_2[1]++; sumcol_2[2]++;
                            }
                            else  if (!harta[2][1])
                            {
                                harta[2][1] = 2; am_ales = 1;
                                sumlin_2[2]++; sumcol_2[1]++;
                            }

                        }
                       /// cout << sumdig1<< '\n';
                        check_win(2,2);   

                    }
                }
                /*else
                {
                    harta[ox][oy] = 2;
                    ///juc = 1;
                    harta[ox][oy] = 2;
                    if (harta[ox][0] == 2 && harta[ox][1] == 2 && harta[ox][2] == 2)winner = 2;
                    if (harta[0][oy] == 2 && harta[1][oy] == 2 && harta[2][oy] == 2)winner = 2;
                    if (harta[0][0] == 2 && harta[1][1] == 2 && harta[2][2] == 2)winner = 2;
                    if (harta[0][2] == 2 && harta[1][1] == 2 && harta[2][0] == 2)winner = 2;
                }*/
                
              
            }
            mutare = -1;
        }

        
    }
    void Render()
    {
        
        if (fer==1) 
        {
            SDL_Rect temp = {0,0,600,600};
            SDL_RenderCopy(renderer, window_1, NULL, &temp);
            SDL_RenderPresent(renderer);

            SDL_Rect temp2 = { 150,300,300,140 };
            SDL_RenderCopy(renderer, but_1, NULL, &temp2);
            SDL_RenderPresent(renderer);

            SDL_Rect temp3 = {150,436,300,140 };
            SDL_RenderCopy(renderer, but_2, NULL, &temp3);
            SDL_RenderPresent(renderer);

        }
        else
        {
            int x, y;
            x = 0; y = 0;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 122);
            SDL_RenderClear(renderer);
            SDL_Rect patrat = { x,y,600,600 };
            SDL_SetRenderDrawColor(renderer, 204, 229, 255, 200);///culoare patrat
            SDL_RenderFillRect(renderer, &patrat);
            ///SDL_SetRenderDrawColor(renderer, 50, 0,0, 150);


            SDL_Rect linie = { 197 + x,y, 6, 600 };
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 122);///culoare linie
            SDL_RenderFillRect(renderer, &linie);

            SDL_Rect linie2 = { 397 + x,y, 6, 600 };
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 122);///culoare linie
            SDL_RenderFillRect(renderer, &linie2);

            SDL_Rect linie3 = { x,197 + y, 600, 6 };
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 122);///culoare linie
            SDL_RenderFillRect(renderer, &linie3);

            SDL_Rect linie4 = { x,397 + y,600, 6 };
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 122);///culoare linie
            SDL_RenderFillRect(renderer, &linie4);

            for (int i = 0;i < 3;i++)
                for (int j = 0;j < 3;j++)
                {
                    SDL_Rect temp = { j * 200 + 3, i * 200 + 3, 190,190 };
                    if (harta[i][j] == 1)
                    {
                        SDL_RenderCopy(renderer, a, NULL, &temp);
                    }
                    else if (harta[i][j] == 2)
                    {
                        SDL_RenderCopy(renderer, b, NULL, &temp);
                    }

                }

            SDL_RenderPresent(renderer); ///AFISARE
            if (winner)
            {
                SDL_SetRenderDrawColor(renderer, 204, 229, 255, 255);
                SDL_RenderClear(renderer);
                SDL_Delay(400);
                SDL_Rect tempdest = { 0,0,600,600 };
                if (winner == 1)
                {
                    for (int i = 1; i <= 3; i++)
                    {
                        SDL_SetRenderDrawColor(renderer, 204, 229, 255, 255);
                        SDL_RenderClear(renderer);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(300);
                        SDL_RenderCopy(renderer, xw, NULL, &tempdest);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(500);
                    }

                }
                else if (winner == 2)
                {
                    for (int i = 1; i <= 3; i++)
                    {
                        SDL_SetRenderDrawColor(renderer, 204, 229, 255, 255);
                        SDL_RenderClear(renderer);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(300);
                        SDL_RenderCopy(renderer, ow, NULL, &tempdest);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(500);
                    }
                }
                else
                {
                    for (int i = 1; i <= 3; i++)
                    {
                        SDL_SetRenderDrawColor(renderer, 204, 229, 255, 255);
                        SDL_RenderClear(renderer);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(300);
                        SDL_RenderCopy(renderer, draw, NULL, &tempdest);

                        SDL_RenderPresent(renderer);
                        SDL_Delay(500);
                    }
                }
                memset(harta, 0, sizeof(harta));
                juc = 1;
                winner = 0;
                cnt = 0;
                sumdig1 = 0;
                sumdig2 = 0;
                memset(sumlin, 0, sizeof(sumlin));
                memset(sumcol, 0, sizeof(sumcol));
                memset(sumlin_2, 0, sizeof(sumlin_2));
                memset(sumcol_2, 0, sizeof(sumcol_2));
                sd1 = 0;
                sd2 = 0;
                return;

            }
        }
          ///animatie de final
          
         

    }
    void quit()
    {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        cout << "FEREASTRA INCHISA" << '\n';
    }

};
GAME* game = nullptr;
int frametime;
unsigned int framedelay, framestart;
const int fps = 60; 

int main(int argc, char* argv[])
{
   
    framedelay = 1000 / fps;
    game = new GAME();
    game->init("ECRAN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, 0);
    
    while (game->running())
    {
        framestart = SDL_GetTicks();
        game->HandleEvents();
        game->Update();
        game->Render();
        frametime = SDL_GetTicks() - framestart;
        if (framedelay > frametime)SDL_Delay(framedelay - frametime);

    }
    game->quit();
    return 0;
}