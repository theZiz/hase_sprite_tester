 /* This file is part of hase_sprite_tester.
  * hase_sprite_tester is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  * 
  * hase_sprite_tester is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  * 
  * You should have received a copy of the GNU General Public License
  * along with hase_sprite_tester.  If not, see <http://www.gnu.org/licenses/>
  * 
  * For feedback and questions about my Files and Projects please mail me,
  * Alexander Matthes (Ziz) , zizsdl_at_googlemail.com */

#include <sparrow3d.h>

SDL_Surface* screen;
spSpritePointer sprite;
int counter = 0;
int rad = 0;

void draw()
{
	int max_size = screen->h*3/4;
	spClearTarget( spGetHSV(counter*64,127,127) );
	spEllipseBorder(screen->w/2,screen->h/2,0,max_size/3+2,max_size/3+2,max_size/30,max_size/30,65535);
	
	sprite->rotation = 0;
	
		sprite->zoomX = sprite->zoomY = SP_ONE;
		spDrawSprite(screen->w/2-max_size/13,screen->h/2,0,sprite);
		
		sprite->zoomX = sprite->zoomY = SP_ONE/2;
		spDrawSprite(screen->w/2-max_size/5,screen->h/2,0,sprite);
		
		sprite->zoomX = sprite->zoomY = SP_ONE*2;
		spDrawSprite(screen->w/2+max_size/7,screen->h/2,0,sprite);
	
	sprite->rotation = -rad+SP_PI/2;
	
		int r = max_size/3 + 16 + (abs(spSin(-rad*6)) * 16 >> SP_ACCURACY);
		int x = spCos(-rad) * r >> SP_ACCURACY;
		int y = spSin(-rad) * r >> SP_ACCURACY;
		sprite->zoomX = sprite->zoomY = SP_ONE;
		spDrawSprite(screen->w/2+x,screen->h/2+y,0,sprite);
	
	sprite->rotation = -rad+SP_PI*2/3+SP_PI/2;
		
		r = max_size/3 + 8 + (abs(spSin((-rad+SP_PI*2/3)*6)) * 8 >> SP_ACCURACY);
		x = spCos(-rad+SP_PI*2/3) * r >> SP_ACCURACY;
		y = spSin(-rad+SP_PI*2/3) * r >> SP_ACCURACY;
		sprite->zoomX = sprite->zoomY = SP_ONE/2;
		spDrawSprite(screen->w/2+x,screen->h/2+y,0,sprite);
		
	sprite->rotation = -rad-SP_PI*2/3+SP_PI/2;
		
		r = max_size/3 + 32 + (abs(spSin((-rad-SP_PI*2/3)*6)) * 32 >> SP_ACCURACY);
		x = spCos(-rad-SP_PI*2/3) * r >> SP_ACCURACY;
		y = spSin(-rad-SP_PI*2/3) * r >> SP_ACCURACY;
		sprite->zoomX = sprite->zoomY = SP_ONE*2;
		spDrawSprite(screen->w/2+x,screen->h/2+y,0,sprite);
		
	spFlip();
}

int jump = -201;

int calc(Uint32 steps)
{
	counter += steps;
	int i;
	for (i = 0; i < steps; i++)
	{
		jump++;
		if (jump <= 0)
			spUpdateSprite(sprite,1);
		else
			rad += 128;
		if (jump > SP_PI/6/128)
			jump = -201;
		if (rad >= 2*SP_PI)
		{
			jump = -201;
			rad = 0;
			printf("%i\n",sprite->wholeDuration);
		}
	}
	if (spGetInput()->button[SP_BUTTON_START])
		return 1;
	if (spGetInput()->button[SP_BUTTON_SELECT])
		return 1;
	return 0;
}

void resize(Uint16 w,Uint16 h)
{
	spSelectRenderTarget(spGetWindowSurface());
}

int main(int argc, char **argv)
{
	if (argc <= 1)
	{
		printf("Usage: hase_sprite_tester image\n");
		return 1;
	}
	spInitCore();
	spSetAffineTextureHack(0); //We don't need it :)
	spInitMath();
	screen = spCreateWindow(320,320,0,1);
	resize(screen->w,screen->h);
	spSetZSet(0);
	spSetZTest(0);
	
	SDL_Surface* image = spLoadSurface( argv[1] );
	if (image == NULL)
	{
		printf("Couldn't load %s\n",argv[1]);
		return 1;
	}
	
	sprite = spNewSprite("hase");
	spNewSubSpriteTilingRow( sprite, image,   0, 0, 34, 34, 34, 34, 4, 40);
	spNewSubSpriteTilingRow( sprite, image, 136, 0, 34, 34, 34, 34, 2, 20);
	spLoop( draw, calc, 10, resize, NULL );
	spDeleteSprite(sprite);
	spQuitCore();
	return 0;
}
