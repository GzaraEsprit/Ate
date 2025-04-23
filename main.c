#include "personnage.h"

int main()
{
SDL_Surface *screen=NULL,*map=NULL;
SDL_Rect pos_map;
SDL_Event event;
int loop=1,standing,state,key_pressed=0;
int x_prev = 0, y_prev = 0;
Personne perso,perso2;
Mix_Music *musique;
Mix_Chunk *attack;
TTF_Init();
//FPS_FUNTION VARIABLES : 
Uint32 start;
int FPS=12;
// INIT SCREEN :
SDL_Init(SDL_INIT_VIDEO);
Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
musique = Mix_LoadMUS("music.mp3");
attack = Mix_LoadWAV("bref.mp3");	
SDL_WM_SetCaption("Personnage workshop",NULL);
   if(SDL_Init(SDL_INIT_VIDEO)!=0)
	{
	  printf("Unable to initialize SDL :%s \n",SDL_GetError());
	  return 1;
	}
	screen =SDL_SetVideoMode(2048,600,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
	if(screen==NULL)
	{
	  printf("Unable to Set video mode :%s \n",SDL_GetError());
	  return 1;
	}
  

//END INIT SCREEN.
//LOAD_image : 
map=IMG_Load("image/map.png");
//LOAD _ PERSO : 
initPerso(&perso);
initPerso2(&perso2);
perso2.pos_hero.x = -200; 
perso2.pos_hero.y = 502;
Mix_PlayMusic(musique,-1);
while(loop)
{
state=0;
pos_map.x=0;
pos_map.y=0;
start= SDL_GetTicks();
key_pressed=0;

	while(SDL_PollEvent(&event)){
			switch(event.type)
		   {
			case SDL_QUIT:
			loop=0;
			break;
			case SDL_KEYDOWN:
			if(event.key.keysym.sym==SDLK_ESCAPE)
			loop=0;
                        if(event.key.keysym.sym == SDLK_a) { 
                        perso2.pos_hero.x = 400;
                        }
			if(event.key.keysym.sym == SDLK_x&& event.type == SDL_KEYDOWN){
			
                	Mix_PlayChannel(-1, attack, 0);
			}
		
			break;
		   }
		}
	// EVENTS OF KEY_PRESSED : 
	if(!key_pressed)
	{
		if(perso.state!=JUMP && perso.state!=DOUBLEJUMP && perso.pos_hero.y==502 && perso.state!=DIE && perso.state!=DUCK)
		{
			perso.state=WAITING;
		}
                if(perso2.state!=JUMP && perso2.state!=DOUBLEJUMP && perso2.pos_hero.y==502 && perso2.state!=DIE && perso2.state!=DUCK)
		{
			perso2.state=WAITING;
		}
	}
	const Uint8 *key= SDL_GetKeyState(NULL);
if(!perso.death)
{
	if(key[SDLK_UP]) // JUMP
	{
		if((perso.jump_count>=0 && perso.jump_count<=1) && (perso.pos_hero.y<=502 && perso.pos_hero.y>=362))
		{
			perso.jump_count++; 
			saut(&perso);
			perso.score+=3;
		}
	}
	//THE HERO STATE WHILE JUMPING IN THE AIR :
	if(perso.jump_count>=2 && perso.pos_hero.y==502) perso.jump_count=0;
	if(perso.pos_hero.y<502 && perso.pos_hero.y>=432) 
	 {
		perso.state=JUMP;
	 }
	else if(perso.pos_hero.y<432 && perso.pos_hero.y>=362) 
	{
		perso.state=DOUBLEJUMP;
	}
	//---------------------------------------------|
	
	if(key[SDLK_RIGHT])// MOVE_RIGHT
	{
		perso.score+=1;
		key_pressed=1;
		if(perso.state!=JUMP && perso.state!=DOUBLEJUMP) perso.state=WALKING;
		perso.direction=0;
		deplacerPerso(&perso);
	}
	if(key[SDLK_LEFT]) // MOVE_LEFT
	{
		key_pressed=1;
		if(perso.state!=JUMP && perso.state!=DOUBLEJUMP) perso.state=WALKING;
		perso.direction=1;
		deplacerPerso(&perso);
	}
	if(key[SDLK_DOWN]) // DUCK
	{
		if(perso.frame_du==1) perso.frame_du=0;
		perso.state=DUCK;
	}
	if(key[SDLK_x]) // ATTACK
	{

		perso.state=ATTACKING;
		if(perso.direction==0)
		perso.pos_hero.x+=2;
		else if(perso.direction==1)
		perso.pos_hero.x-=2;
		perso.score+=2;
		
			
	}
	
	
	if(key[SDLK_SPACE]) // MOVE_FASTER
	{
		if(perso.acceleration<=4)
		 perso.acceleration+=1;
	}
	else
	{
		perso.acceleration=0;	
	}
	if(key[SDLK_h]) // TESTING_GETTING_HIT (NOTE : in the integration of the collision between the ennemi and the hero delete this condition and put it inside the collision statlent )
	{
		perso.state=HIT;
		perso.health-=10;
		
	}
}// if the HERO is Not dead
	if(key[SDLK_l])
	{
		perso.score+=17;
}
		
	if(key[SDLK_m]) // TESTING_GETTING_DIE (NOTE : in the integration the death of the hero start when his health became '0' delete this 'if' condition and put it inside a propre condition if(perso.health==0) i add it down in the death conditions )
	{
		perso.state=DIE;
		perso.death=1;
		perso.health=0;
	}
if(!perso2.death)
{
	if(key[SDLK_z]) // JUMP
	{
		if((perso2.jump_count>=0 && perso2.jump_count<=1) && (perso2.pos_hero.y<=502 && perso2.pos_hero.y>=362))
		{
			perso2.jump_count++; 
			saut(&perso2);
			perso2.score+=3;
		}
	}
	//THE HERO STATE WHILE JUMPING IN THE AIR :
	if(perso2.jump_count>=2 && perso2.pos_hero.y==502) perso2.jump_count=0;
	if(perso2.pos_hero.y<502 && perso2.pos_hero.y>=432) 
	 {
		perso2.state=JUMP;
	 }
	else if(perso2.pos_hero.y<432 && perso2.pos_hero.y>=362) 
	{
		perso2.state=DOUBLEJUMP;
	}
	//---------------------------------------------|
	
	if(key[SDLK_d])// MOVE_RIGHT
	{
		perso2.score+=1;
		key_pressed=1;
		if(perso2.state!=JUMP && perso2.state!=DOUBLEJUMP) perso2.state=WALKING;
		perso2.direction=0;
		deplacerPerso(&perso2);
	}
	if(key[SDLK_q]) // MOVE_LEFT
	{
		key_pressed=1;
		if(perso2.state!=JUMP && perso2.state!=DOUBLEJUMP) perso2.state=WALKING;
		perso2.direction=1;
		deplacerPerso(&perso2);
	}
	if(key[SDLK_s]) // DUCK
	{
		if(perso2.frame_du==1) perso2.frame_du=0;
		perso2.state=DUCK;
	}
	if(key[SDLK_y]) // ATTACK
	{
		
		perso2.state=ATTACKING;
		if(perso2.direction==0)
		perso2.pos_hero.x+=2;
		else if(perso2.direction==1)
		perso2.pos_hero.x-=2;
		perso2.score+=2;
	}
	 
	
	if(key[SDLK_p]) // MOVE_FASTER
	{
		if(perso2.acceleration<=4)
		 perso2.acceleration+=1;
	}
	else
	{
		perso2.acceleration=0;	
	}
	if(key[SDLK_r]) // TESTING_GETTING_HIT (NOTE : in the integration of the collision between the ennemi and the hero delete this condition and put it inside the collision statlent )
	{
		perso2.state=HIT;
		perso2.health-=10;
		
	}
}// if the HERO is Not dead
	if(key[SDLK_n])
	{
		perso2.score+=17;
}
	if(key[SDLK_o]) // TESTING_GETTING_DIE (NOTE : in the integration the death of the hero start when his health became '0' delete this 'if' condition and put it inside a propre condition if(perso.health==0) i add it down in the death conditions )
	{
		perso2.state=DIE;
		perso2.death=1;
		perso2.health=0;
	}
	// END_of_KEY_PRESSED_EVENTS
	gravity(&perso);
	gravity(&perso2);
SDL_BlitSurface(map,NULL,screen,&pos_map);
animerPerso(&perso);
animerPerso(&perso2);
afficherPerso(perso,screen);
afficherPerso(perso2,screen);
afficherScore_vie(perso,screen);
afficherScore_vie(perso2,screen);
SDL_Flip(screen); // SCREEN_FLIP
//DEATH_CONDITIONS :---------------|
if(perso.health<=0)perso.death=1;
if(perso.death==1)perso.state=DIE;
if(perso2.health<=0)perso2.death=1;
if(perso2.death==1)perso2.state=DIE;
//---------------------------------|
//FPS_FUNCTION :
if(1000/FPS > SDL_GetTicks()-start) 
	{
            SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
        }
} // END_OF_LOOP
SDL_FreeSurface(map);
free_perso(&perso);
free_perso(&perso2);
return 0;
}
