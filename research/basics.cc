#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "menu.h"

using namespace std;

void kill_text(SDL_Texture*& object, MENU& item, SDL_Rect& rekt)
{
  item.set_values(0, 0, 0, 0);
  rekt = item.get_rect();
  SDL_DestroyTexture(object);
  object = nullptr;
}




const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//parameter till main() int argc, char* argv[]
int main()
{
// initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
  {
    cerr << "Error initializing SDL" << endl;
    exit(1);
  }

//initialize SDL_mixer
  if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
  {
    cerr << "SDL_mixer could not initialize! SDL_mixer Error:" << Mix_GetError() << endl;
  }
  
  //create window
  SDL_Window* window = SDL_CreateWindow( "SDL Test",
                                         SDL_WINDOWPOS_UNDEFINED,
                                         SDL_WINDOWPOS_UNDEFINED,
                                         SCREEN_WIDTH,
                                         SCREEN_HEIGHT,
                                         SDL_WINDOW_RESIZABLE );
  
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

  //Om man skalar upp skärmen görs det för allt på skärmen också.
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
  // render at a virtual resolution then stretch to actual resolution
  SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

  // Load start-menu items
  //menu backgrounds
  SDL_Texture* back{nullptr};
  SDL_Texture* front{nullptr};
  //menu items
  SDL_Texture* quit{nullptr};
  SDL_Texture* inst{nullptr};
  SDL_Texture* play{nullptr};
  
  int frontWidth{0};
  int frontHeight{0};
  
  int quitWidth{0};
  int quitHeight{0};
  
  int instWidth{0};
  int instHeight{0};
  
  int backWidth{0};
  int backHeight{0};
  
  int playWidth{0};
  int playHeight{0};
  
  //The music that will be played
  Mix_Music *gMusic = nullptr;
  // SOUNDS
  Mix_Chunk *gScratch = nullptr;

  //Load sound effects
  gScratch = Mix_LoadWAV( "yeha.wav" );
  if( gScratch == nullptr )
  {
    printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
  }
   //Load music
  gMusic = Mix_LoadMUS( "turkishdelight_rep_maby.wav" );
  if( gMusic == nullptr )
  {
    printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
  }
  
  {
    SDL_Surface* temp = IMG_Load("quit.png");

    quit = SDL_CreateTextureFromSurface( renderer, temp );
    quitWidth = temp->w;
    quitHeight = temp->h;

    SDL_FreeSurface( temp );
    
    temp = IMG_Load("Installningar.png");
    inst = SDL_CreateTextureFromSurface( renderer, temp );
    instWidth = temp->w;
    instHeight = temp->h;
    
    SDL_FreeSurface( temp );

    temp = IMG_Load("flag.png");
    back = SDL_CreateTextureFromSurface( renderer, temp );
    backWidth = temp->w;
    backHeight = temp->h;
    
    SDL_FreeSurface( temp );
    
    temp = IMG_Load("play.png");
    play = SDL_CreateTextureFromSurface( renderer, temp );
    playWidth = temp->w;
    playHeight = temp->h;
    
    SDL_FreeSurface( temp );
    
    temp = IMG_Load("backen.png");
    front = SDL_CreateTextureFromSurface( renderer, temp );
    frontWidth = temp->w;
    frontHeight = temp->h;
    
    SDL_FreeSurface( temp );
    
  }

  // set start position
  MENU frontRect(0, 0, frontHeight, frontWidth);
  SDL_Rect front_Rect = frontRect.get_rect();
  
  MENU playRect(100, 300, playHeight, playWidth);
  SDL_Rect play_Rect = playRect.get_rect();

  MENU quitRect(400, 300, quitHeight, quitWidth);
  SDL_Rect quit_Rect = quitRect.get_rect();

  MENU instRect(200, 300, instHeight, instWidth);
  SDL_Rect inst_Rect = instRect.get_rect();

  MENU backRect(0, 0, 0, 0);
  SDL_Rect back_Rect = backRect.get_rect();

  //setback
  bool isback = false;
  //SET CONTROLS
  //SDL_Keycode lol = event.key.keysym.sym;
  SDL_Keycode playmusic = SDLK_p;
  SDL_Keycode playsound = SDLK_o;
  SDL_Keycode pauseMusic = SDLK_i;
  // main loop
  bool running{true};
  while (running)
  {
    // clear screen, in this case earlier because the input-step also renders
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    //hantera event
    SDL_Event event;
    while( SDL_PollEvent(&event) )
    {
      if( event.type == SDL_QUIT )
      {
        running = false;
      }
      else if( event.type == SDL_KEYDOWN )
      {
        if ( event.key.keysym.sym == SDLK_ESCAPE )
        {
          running = false;
        }
        if ( event.key.keysym.sym == playsound )
        {
        //play sound effect
        Mix_PlayChannel( -1, gScratch, 0 );
        }
        if ( event.key.keysym.sym == playmusic )
        {
          //play music
          Mix_PlayMusic( gMusic, -1 );
        }
        if ( event.key.keysym.sym == pauseMusic )
        {
          Mix_HaltMusic();
        }
      }
      else if ( event.type == SDL_MOUSEBUTTONDOWN )
      {
        if ( isback && event.button.y > 300 && event.button.x > 400)
        {
          cout << "china" << endl;
        }
        if ( isback && event.button.y > 300 && event.button.x < 400)
        {
          cout << "arabia" << endl;
        }
        if ( isback && event.button.y < 300)
        {
          cout << "russia" << endl;
        }
        
        if ( quitRect.contain(event.button.x, event.button.y) )
        {
          running = false;
        }
        else if ( instRect.contain(event.button.x, event.button.y) )
        {
          std::cout << SDLK_l << std::endl;
        }
        else if ( playRect.contain(event.button.x, event.button.y) && !isback)
        {
          //bakgrunden
          isback = true;
          //döda menyknappar
          kill_text(quit, quitRect, quit_Rect);
          kill_text(inst, instRect, inst_Rect);
          kill_text(front, frontRect, front_Rect);
          kill_text(play, playRect, play_Rect);
          
          //sätt storlek på bakgrundsbild
          backRect.set_values(0, 0, backHeight, backWidth );
          back_Rect = backRect.get_rect();
        }
      }
    }
    
    const Uint8* keystates = SDL_GetKeyboardState(nullptr);
    if(keystates[SDL_SCANCODE_W])
    {
      inst_Rect.y -= 5;
    }
    if(keystates[SDL_SCANCODE_S])
    {
      inst_Rect.y += 5;
    }
    if(keystates[SDL_SCANCODE_A])
    {
      inst_Rect.x -= 5;
    }
    if(keystates[SDL_SCANCODE_D])
    {
      inst_Rect.x += 5;
    }
    
    // draw things
    SDL_RenderCopy( renderer, front, nullptr, &front_Rect );
    SDL_RenderCopy( renderer, inst, nullptr, &inst_Rect );
    SDL_RenderCopy( renderer, play, nullptr, &play_Rect );
    SDL_RenderCopy( renderer, quit, nullptr, &quit_Rect );
    SDL_RenderCopy( renderer, back, nullptr, &back_Rect );
    
    // show the newly drawn things
    SDL_RenderPresent(renderer);

    // wait before drawing the next frame
    SDL_Delay(10);
  }
  
  // free memory
  kill_text(quit, quitRect, quit_Rect);
  kill_text(inst, instRect, inst_Rect);
  kill_text(front, frontRect, front_Rect);
  kill_text(play, playRect, play_Rect);
  kill_text(back, backRect, back_Rect);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  //FREE MIX
  Mix_FreeChunk( gScratch );
  //FREE MUSIC
  Mix_FreeMusic( gMusic );
  gMusic = nullptr;
  
  Mix_Quit();
  SDL_Quit();
  return 0;
  
}
