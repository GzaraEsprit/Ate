#include "personnage.h"

void initPerso(Personne *p)
{
	p->hero_d = IMG_Load("image/heroD.png");
	p->hero_g = IMG_Load("image/heroG.png");	
	p->bar_score=NULL;
	p->bar_health=NULL;
	p->pos_vie.x=50;
	p->pos_vie.y=50;
	p->pos_score.x=380;
	p->pos_score.y=50;
	p->score=0;
	p->health=100;
	p->death=0;
	p->direction=0;
	p->vitesse = 12;
	p->jump=70;
	p->jump_count=0;
	p->acceleration = 0;
	p->state=WAITING;
	p->pos_hero.x=60;
	p->pos_hero.y=502;
	p->pos_hero.w=40;
	p->pos_hero.h=70;
	p->frame_w=0;p->frame_wl=0;p->frame_j=0;p->frame_dj=0;p->frame_a=0;p->frame_a2=0;p->frame_h=0;p->frame_d=0;p->frame_du = 0;
	p->police = TTF_OpenFont("ttf_police/School & COLLEGE Outline.ttf",20);
	//init annimation DROITE: 
	for(int i=0;i<4;i++) // Waiting :
	{
		p->annimation_hero_d[0][i].x= (10+(i*60));
		p->annimation_hero_d[0][i].y= 0;
		p->annimation_hero_d[0][i].w= 60;
		p->annimation_hero_d[0][i].h= 85;
	}
	for(int i=0;i<8;i++) // Walking :
	{
		p->annimation_hero_d[1][i].x= (10+(i*62));
		p->annimation_hero_d[1][i].y= 100;
		p->annimation_hero_d[1][i].w= 60;
		p->annimation_hero_d[1][i].h= 85;
	}
		for(int i=0;i<8;i++) // Jumping :
	{
		p->annimation_hero_d[2][i].x= (0+(i*67));
		p->annimation_hero_d[2][i].y= 190;
		p->annimation_hero_d[2][i].w= 65;
		p->annimation_hero_d[2][i].h= 95;
	}
		for(int i=0;i<8;i++) // Double-Jumping :
	{
		p->annimation_hero_d[3][i].x= (0+(i*67));
		p->annimation_hero_d[3][i].y= 190;
		p->annimation_hero_d[3][i].w= 65;
		p->annimation_hero_d[3][i].h= 95;
	}
	for(int i=0;i<2;i++) // Duck :
	{
		p->annimation_hero_d[4][i].x= (0+(i*70));
		p->annimation_hero_d[4][i].y= 290;
		p->annimation_hero_d[4][i].w= 65;
		p->annimation_hero_d[4][i].h= 85;
	}
		for(int i=0;i<3;i++) // Attack#1:
	{
		p->annimation_hero_d[5][i].x= (0+(i*81));
		p->annimation_hero_d[5][i].y= 385;
		p->annimation_hero_d[5][i].w= 80;
		p->annimation_hero_d[5][i].h= 85;
	}
		for(int i=0;i<6;i++) // Attack#2:
	{
		p->annimation_hero_d[6][i].x= (0+(i*70));
		p->annimation_hero_d[6][i].y= 485;
		p->annimation_hero_d[6][i].w= 70;
		p->annimation_hero_d[6][i].h= 85;
	}
	
	for(int i=0;i<1;i++) // HIT :
	{
		p->annimation_hero_d[7][i].x= (0+(i*70));
		p->annimation_hero_d[7][i].y= 585;
		p->annimation_hero_d[7][i].w= 70;
		p->annimation_hero_d[7][i].h= 80;
	}
	for(int i=0;i<3;i++) // Death#1 :
	{
		p->annimation_hero_d[8][i].x= (0+(i*75));
		p->annimation_hero_d[8][i].y= 585;
		p->annimation_hero_d[8][i].w= 75;
		p->annimation_hero_d[8][i].h= 80;
	}
	 // Death#2 :
	
	p->annimation_hero_d[8][3].x= 250;
	p->annimation_hero_d[8][3].y= 585;
	p->annimation_hero_d[8][3].w= 90;
	p->annimation_hero_d[8][3].h= 85;
	
	

	//init annimation Gauche: -----------------------------------------
	for(int i=0;i<6;i++) // Waiting :
	{
		p->annimation_hero_g[0][i].x= (450-(i*60));
		p->annimation_hero_g[0][i].y= 0;
		p->annimation_hero_g[0][i].w= 60;
		p->annimation_hero_g[0][i].h= 85;
	}
	for(int i=0;i<8;i++) // Walking :
	{
		p->annimation_hero_g[1][i].x= (450-(i*62));
		p->annimation_hero_g[1][i].y= 100;
		p->annimation_hero_g[1][i].w= 60;
		p->annimation_hero_g[1][i].h= 85;
	}
	for(int i=0;i<8;i++) // Jumping :
	{
		p->annimation_hero_g[2][i].x= (450-(i*65));
		p->annimation_hero_g[2][i].y= 190;
		p->annimation_hero_g[2][i].w= 65;
		p->annimation_hero_g[2][i].h= 95;
	}
		for(int i=0;i<8;i++) // Double-Jumping :
	{
		p->annimation_hero_g[3][i].x= (450-(i*65));
		p->annimation_hero_g[3][i].y= 190;
		p->annimation_hero_g[3][i].w= 65;
		p->annimation_hero_g[3][i].h= 95;
	}
	for(int i=0;i<2;i++) // Duck :
	{
		p->annimation_hero_g[4][i].x= (450-(i*65));
		p->annimation_hero_g[4][i].y= 290;
		p->annimation_hero_g[4][i].w= 65;
		p->annimation_hero_g[4][i].h= 85;
	}
	for(int i=0;i<3;i++) // Attack#1:
	{
		p->annimation_hero_g[5][i].x= (440-(i*81));
		p->annimation_hero_g[5][i].y= 385;
		p->annimation_hero_g[5][i].w= 80;
		p->annimation_hero_g[5][i].h= 85;
	}
	for(int i=0;i<6;i++) // Attack#2:
	{
		p->annimation_hero_g[6][i].x= (450-(i*70));
		p->annimation_hero_g[6][i].y= 485;
		p->annimation_hero_g[6][i].w= 70;
		p->annimation_hero_g[6][i].h= 85;
		
	}
	
	for(int i=0;i<1;i++) // HIT :
	{
		p->annimation_hero_g[7][i].x= (450-(i*70));
		p->annimation_hero_g[7][i].y= 585;
		p->annimation_hero_g[7][i].w= 70;
		p->annimation_hero_g[7][i].h= 80;
	}
	for(int i=0;i<3;i++) // Death#1 :
	{
		p->annimation_hero_g[8][i].x= (450-(i*75));
		p->annimation_hero_g[8][i].y= 585;
		p->annimation_hero_g[8][i].w= 75;
		p->annimation_hero_g[8][i].h= 80;
	}
	 // Death#2 :
	
	p->annimation_hero_g[8][3].x= 180;
	p->annimation_hero_g[8][3].y= 585;
	p->annimation_hero_g[8][3].w= 90;
	p->annimation_hero_g[8][3].h= 85;
}
void initPerso2(Personne *p2)
{
	p2->hero_d = IMG_Load("image/heroD.png");
	p2->hero_g = IMG_Load("image/heroG.png");	
	p2->bar_score=NULL;
	p2->bar_health=NULL;
	p2->pos_vie.x=600;
	p2->pos_vie.y=50;
	p2->pos_score.x=800;
	p2->pos_score.y=50;
	p2->score=0;
	p2->health=100;
	p2->death=0;
	p2->direction=0;
	p2->vitesse = 12;
	p2->jump=70;
	p2->jump_count=0;
	p2->acceleration = 0;
	p2->state=WAITING;
	p2->pos_hero.x=60;
	p2->pos_hero.y=502;
	p2->pos_hero.w=40;
	p2->pos_hero.h=70;
	p2->frame_w=0;p2->frame_wl=0;p2->frame_j=0;p2->frame_dj=0;p2->frame_a=0;p2->frame_a2=0;p2->frame_h=0;p2->frame_d=0;p2->frame_du = 0;
	p2->police = TTF_OpenFont("ttf_police/School & COLLEGE Outline.ttf",20);
	//init annimation DROITE: 
	for(int i=0;i<4;i++) // Waiting :
	{
		p2->annimation_hero_d[0][i].x= (10+(i*60));
		p2->annimation_hero_d[0][i].y= 0;
		p2->annimation_hero_d[0][i].w= 60;
		p2->annimation_hero_d[0][i].h= 85;
	}
	for(int i=0;i<8;i++) // Walking :
	{
		p2->annimation_hero_d[1][i].x= (10+(i*62));
		p2->annimation_hero_d[1][i].y= 100;
		p2->annimation_hero_d[1][i].w= 60;
		p2->annimation_hero_d[1][i].h= 85;
	}
		for(int i=0;i<8;i++) // Jumping :
	{
		p2->annimation_hero_d[2][i].x= (0+(i*67));
		p2->annimation_hero_d[2][i].y= 190;
		p2->annimation_hero_d[2][i].w= 65;
		p2->annimation_hero_d[2][i].h= 95;
	}
		for(int i=0;i<8;i++) // Double-Jumping :
	{
		p2->annimation_hero_d[3][i].x= (0+(i*67));
		p2->annimation_hero_d[3][i].y= 190;
		p2->annimation_hero_d[3][i].w= 65;
		p2->annimation_hero_d[3][i].h= 95;
	}
	for(int i=0;i<2;i++) // Duck :
	{
		p2->annimation_hero_d[4][i].x= (0+(i*70));
		p2->annimation_hero_d[4][i].y= 290;
		p2->annimation_hero_d[4][i].w= 65;
		p2->annimation_hero_d[4][i].h= 85;
	}
		for(int i=0;i<3;i++) // Attack#1:
	{
		p2->annimation_hero_d[5][i].x= (0+(i*81));
		p2->annimation_hero_d[5][i].y= 385;
		p2->annimation_hero_d[5][i].w= 80;
		p2->annimation_hero_d[5][i].h= 85;
	}
		for(int i=0;i<6;i++) // Attack#2:
	{
		p2->annimation_hero_d[6][i].x= (0+(i*70));
		p2->annimation_hero_d[6][i].y= 485;
		p2->annimation_hero_d[6][i].w= 70;
		p2->annimation_hero_d[6][i].h= 85;
	}
	
	for(int i=0;i<1;i++) // HIT :
	{
		p2->annimation_hero_d[7][i].x= (0+(i*70));
		p2->annimation_hero_d[7][i].y= 585;
		p2->annimation_hero_d[7][i].w= 70;
		p2->annimation_hero_d[7][i].h= 80;
	}
	for(int i=0;i<3;i++) // Death#1 :
	{
		p2->annimation_hero_d[8][i].x= (0+(i*75));
		p2->annimation_hero_d[8][i].y= 585;
		p2->annimation_hero_d[8][i].w= 75;
		p2->annimation_hero_d[8][i].h= 80;
	}
	 // Death#2 :
	
	p2->annimation_hero_d[8][3].x= 250;
	p2->annimation_hero_d[8][3].y= 585;
	p2->annimation_hero_d[8][3].w= 90;
	p2->annimation_hero_d[8][3].h= 85;
	
	

	//init annimation Gauche: -----------------------------------------
	for(int i=0;i<6;i++) // Waiting :
	{
		p2->annimation_hero_g[0][i].x= (450-(i*60));
		p2->annimation_hero_g[0][i].y= 0;
		p2->annimation_hero_g[0][i].w= 60;
		p2->annimation_hero_g[0][i].h= 85;
	}
	for(int i=0;i<8;i++) // Walking :
	{
		p2->annimation_hero_g[1][i].x= (450-(i*62));
		p2->annimation_hero_g[1][i].y= 100;
		p2->annimation_hero_g[1][i].w= 60;
		p2->annimation_hero_g[1][i].h= 85;
	}
	for(int i=0;i<8;i++) // Jumping :
	{
		p2->annimation_hero_g[2][i].x= (450-(i*65));
		p2->annimation_hero_g[2][i].y= 190;
		p2->annimation_hero_g[2][i].w= 65;
		p2->annimation_hero_g[2][i].h= 95;
	}
		for(int i=0;i<8;i++) // Double-Jumping :
	{
		p2->annimation_hero_g[3][i].x= (450-(i*65));
		p2->annimation_hero_g[3][i].y= 190;
		p2->annimation_hero_g[3][i].w= 65;
		p2->annimation_hero_g[3][i].h= 95;
	}
	for(int i=0;i<2;i++) // Duck :
	{
		p2->annimation_hero_g[4][i].x= (450-(i*65));
		p2->annimation_hero_g[4][i].y= 290;
		p2->annimation_hero_g[4][i].w= 65;
		p2->annimation_hero_g[4][i].h= 85;
	}
	for(int i=0;i<3;i++) // Attack#1:
	{
		p2->annimation_hero_g[5][i].x= (440-(i*81));
		p2->annimation_hero_g[5][i].y= 385;
		p2->annimation_hero_g[5][i].w= 80;
		p2->annimation_hero_g[5][i].h= 85;
	}
	for(int i=0;i<6;i++) // Attack#2:
	{
		p2->annimation_hero_g[6][i].x= (450-(i*70));
		p2->annimation_hero_g[6][i].y= 485;
		p2->annimation_hero_g[6][i].w= 70;
		p2->annimation_hero_g[6][i].h= 85;
		
	}
	
	for(int i=0;i<1;i++) // HIT :
	{
		p2->annimation_hero_g[7][i].x= (450-(i*70));
		p2->annimation_hero_g[7][i].y= 585;
		p2->annimation_hero_g[7][i].w= 70;
		p2->annimation_hero_g[7][i].h= 80;
	}
	for(int i=0;i<3;i++) // Death#1 :
	{
		p2->annimation_hero_g[8][i].x= (450-(i*75));
		p2->annimation_hero_g[8][i].y= 585;
		p2->annimation_hero_g[8][i].w= 75;
		p2->annimation_hero_g[8][i].h= 80;
	}
	 // Death#2 :
	
	p2->annimation_hero_g[8][3].x= 180;
	p2->annimation_hero_g[8][3].y= 585;
	p2->annimation_hero_g[8][3].w= 90;
	p2->annimation_hero_g[8][3].h= 85;
}		
void animerPerso (Personne* p)
{
	if((p->direction==0 || p->direction==1) && p->state==WAITING)
	{
		p->frame_w++;
		if(p->frame_w==4)
		p->frame_w=0;
	}
	if((p->direction==0 || p->direction==1) && p->state==WALKING)
	{
		p->frame_wl++;
		if(p->frame_wl==8)
		p->frame_wl=0;
	}
	if((p->direction==0 || p->direction==1) && p->state==JUMP)
	{
		p->frame_j++;
		if(p->frame_j==8)
		p->frame_j=0;
	}
	if((p->direction==0 || p->direction==1) && p->state==DOUBLEJUMP)
	{
		p->frame_dj++;
		if(p->frame_dj==8)
		p->frame_dj=0;
	}
	if((p->direction==0 || p->direction==1) && p->state==DUCK)
	{
		p->frame_du++;
		if(p->frame_du==2)
		p->frame_du=1;
	}
	if((p->direction==0 || p->direction==1) && p->state==ATTACKING)
	{
		p->frame_a++;
		if(p->frame_a==3)
		p->frame_a=0;
	}
	if((p->direction==0 || p->direction==1) && p->state==ATTACKING2)
	{
		p->frame_a2++;
		if(p->frame_a2==6)
		p->frame_a2=0;
	}
	if((p->direction==0 || p->direction==1) && p->state==HIT)
	{
		p->frame_h++;
		if(p->frame_h==1)
		p->frame_h=0;
	}
	if((p->direction==0 || p->direction==1) && p->state==DIE)
	{
		p->frame_d++;
		if(p->frame_d>=4)
		p->frame_d=3;
	}
}
void deplacerPerso (Personne *p)
{
	if(p->direction==0)
	{
		p->pos_hero.x+=(p->vitesse+p->acceleration);
	}
	else if(p->direction==1)
	{
		p->pos_hero.x-=(p->vitesse+p->acceleration);
	}
}
void saut (Personne* p)
{
	if(p->jump_count==1 || p->jump_count==2)
	{
		p->pos_hero.y-=p->jump;
	}
}
void gravity(Personne* p)
{
	if(p->pos_hero.y <502)
	{
		p->pos_hero.y+=7;	
	}
	if(p->pos_hero.y>=502 && (p->state==JUMP || p->state==DOUBLEJUMP ||  p->state==DIE))
	{
		p->pos_hero.y=502;
		if(p->state!=DIE)
		p->state=WAITING;
	}
}
void afficherPerso(Personne p, SDL_Surface * screen_p)
{
	if(p.direction==0 && p.state==WAITING) SDL_BlitSurface(p.hero_d,&p.annimation_hero_d[WAITING][p.frame_w],screen_p,&p.pos_hero);
	else if(p.direction==1 && p.state==WAITING) SDL_BlitSurface(p.hero_g,&p.annimation_hero_g[WAITING][p.frame_w],screen_p,&p.pos_hero);
	if(p.direction==0 && p.state==WALKING) SDL_BlitSurface(p.hero_d,&p.annimation_hero_d[WALKING][p.frame_wl],screen_p,&p.pos_hero);
	else if(p.direction==1 && p.state==WALKING) SDL_BlitSurface(p.hero_g,&p.annimation_hero_g[WALKING][p.frame_wl],screen_p,&p.pos_hero);
	if(p.direction==0 && p.state==JUMP) SDL_BlitSurface(p.hero_d,&p.annimation_hero_d[JUMP][p.frame_j],screen_p,&p.pos_hero);
	else if(p.direction==1 && p.state==JUMP) SDL_BlitSurface(p.hero_g,&p.annimation_hero_g[JUMP][p.frame_j],screen_p,&p.pos_hero);
	if(p.direction==0 && p.state==DOUBLEJUMP) SDL_BlitSurface(p.hero_d,&p.annimation_hero_d[DOUBLEJUMP][p.frame_dj],screen_p,&p.pos_hero);
	else if(p.direction==1 && p.state==DOUBLEJUMP) SDL_BlitSurface(p.hero_g,&p.annimation_hero_g[DOUBLEJUMP][p.frame_dj],screen_p,&p.pos_hero);
	if(p.direction==0 && p.state==DUCK) SDL_BlitSurface(p.hero_d,&p.annimation_hero_d[DUCK][p.frame_du],screen_p,&p.pos_hero);
	else if(p.direction==1 && p.state==DUCK) SDL_BlitSurface(p.hero_g,&p.annimation_hero_g[DUCK][p.frame_du],screen_p,&p.pos_hero);
	if(p.direction==0 && p.state==ATTACKING) SDL_BlitSurface(p.hero_d,&p.annimation_hero_d[ATTACKING][p.frame_a],screen_p,&p.pos_hero);
	else if(p.direction==1 && p.state==ATTACKING) SDL_BlitSurface(p.hero_g,&p.annimation_hero_g[ATTACKING][p.frame_a],screen_p,&p.pos_hero);
	if(p.direction==0 && p.state==ATTACKING2) SDL_BlitSurface(p.hero_d,&p.annimation_hero_d[ATTACKING2][p.frame_a2],screen_p,&p.pos_hero);
	else if(p.direction==1 && p.state==ATTACKING2) SDL_BlitSurface(p.hero_g,&p.annimation_hero_g[ATTACKING2][p.frame_a2],screen_p,&p.pos_hero);
	if(p.direction==0 && p.state==HIT) SDL_BlitSurface(p.hero_d,&p.annimation_hero_d[HIT][p.frame_h],screen_p,&p.pos_hero);
	else if(p.direction==1 && p.state==HIT) SDL_BlitSurface(p.hero_g,&p.annimation_hero_g[HIT][p.frame_h],screen_p,&p.pos_hero);
	if(p.direction==0 && p.state==DIE) SDL_BlitSurface(p.hero_d,&p.annimation_hero_d[DIE][p.frame_d],screen_p,&p.pos_hero);
	else if(p.direction==1 && p.state==DIE) SDL_BlitSurface(p.hero_g,&p.annimation_hero_g[DIE][p.frame_d],screen_p,&p.pos_hero);
}
void afficherScore_vie(Personne p, SDL_Surface * screen_s)
{
	SDL_Color olive ={13,91,225};
	//DISPLAY HEALTH BAR :
	char tab2[80];
	sprintf(tab2,"Health : %d %%",p.health);
	p.bar_health=TTF_RenderText_Blended(p.police,tab2,olive);
	SDL_BlitSurface(p.bar_health,NULL,screen_s,&p.pos_vie);
	//DISPLAY SCORE : 
	char tab[80];
	sprintf(tab,"Score : %d",p.score);
	p.bar_score=TTF_RenderText_Blended(p.police,tab,olive);
	SDL_BlitSurface(p.bar_score,NULL,screen_s,&p.pos_score);
}
void free_perso(Personne *p)
{
	SDL_FreeSurface(p->bar_score);
	SDL_FreeSurface(p->bar_health);
	SDL_FreeSurface(p->hero_d);
	SDL_FreeSurface(p->hero_g);
	TTF_CloseFont(p->police);
}
