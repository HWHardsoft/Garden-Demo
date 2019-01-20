/*
 *  UzeGarden a Harvest Moon fan game for Uzebox 
 *  Version 1.0
 *  Copyright (C) 2015  Hartmut Wendt
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdbool.h>
#include <string.h>
#include <avr/io.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include "kernel/uzebox.h"


#include "data/garden_BGtiles.pic.inc"
#include "data/garden_font.pic.inc"
//#include "data/win8_BGintro.pic.inc"
//#include "data/sprites.pic.inc"
//#include "data/sprites.map.inc"
//#include "data/win8boot.inc"
//#include "data/patches.inc"



#define _FadingX



/* global definitons */
// program modes
enum {
	PM_Intro,		// program mode intro
	PM_Test,   		// program mode game play
};







// 8-bit, 255 period LFSR (for generating pseudo-random numbers)
#define PRNG_NEXT() (prng = ((u8)((prng>>1) | ((prng^(prng>>2)^(prng>>3)^(prng>>4))<<7))))
#define MAX(x,y) ((x)>(y) ? (x) : (y))




struct EepromBlockStruct ebs;






u8 prng; // Pseudo-random number generator

u8 program_mode;	// program mode (intro, 1 player mode, 2 player mode, ....



u8 PosY=120;
u8 PosX=112;



/*** function prototypes *****************************************************************/
void init(void);
void set_PM_mode(u8 mode);
void msg_window(u8 x1, u8 y1, u8 x2, u8 y2);

u8 GetTile(u8 x, u8 y);
void copy_buf(unsigned char *BUFA, unsigned char *BUFB, unsigned char ucANZ);
void fill_buf(u8 *BUFA, u8 content, u8 ucANZ);
void button_handler(u8 PosX, u8 PosY);



void init(void)
// init program
{
  // init tile table
  SetTileTable(BGTiles);
  // init font table
  SetFontTilesIndex(BGTILES_SIZE);
  // init Sprites
  //SetSpritesTileTable(sprites_tileset);	

  // init music	
  //InitMusicPlayer(patches);


  // load into screen
  set_PM_mode(PM_Test);
     		

}



int main(){
int ibuttons=0,ibuttons_old;
u8 uc1, uc2=0;

  // init program
  init();        
  
  // proceed Windows8 fake	
  while(1)
  {
    WaitVsync(1);	  
    // get controller state
    ibuttons_old = ibuttons;
	ibuttons = ReadJoypad(0);

	// handle cursor
    if ((BTN_LEFT & ibuttons) && (PosX>0)) PosX -= 1;
    else if ((BTN_RIGHT & ibuttons) && (PosX<231)) PosX += 1;
    if ((BTN_UP & ibuttons) && (PosY>0)) PosY -= 1;
    else if ((BTN_DOWN & ibuttons) && (PosY<191)) PosY += 1;		
	MoveSprite(1,PosX,PosY,1,2);
	if (BTN_A & ibuttons) {
		button_handler(PosX,PosY);
	    while (BTN_A & ReadJoypad(0));
	}

    switch(program_mode)
	{
	  // proceed intro mode	
	  case PM_Intro:	    

        break;

	  // proceed Windows8 screen
	  //case PM_Win8:
	  	// bunny animation and moving	
	  	// move the bunny left		
        //break;



	}
	

  }
  

} 


void set_PM_mode(u8 mode) {
// set parameters, tiles, background etc for choosed program mode
u8 uc1, uc2;

			
	switch (mode)
	{

	  case	PM_Intro:
		SetSpriteVisibility(false);
		StopSong();

		// init tile table
  		//SetTileTable(IntroTiles);
   		 
	    // cursor is invisible now
	    StopSong();
		ClearVram();

//		DrawMap2(9,8,Win8logo);
//		DrawMap2(9,24,Win8text);			
		break;

		
	  case	PM_Test:
	    // first mockup
		SetSpriteVisibility(false);
		StopSong();

		// init tile table
  		//SetTileTable(IntroTiles);
		
		ClearVram();
		// fill screen with background maps
		Fill(7,0,23,28,0x0D);   		 
		Fill(8,1,21,26,0x12);   		 


		

		// Beet 1
		DrawMap2(10,4,Field_seed_dry);   		 
		DrawMap2(10,6,Field_seed_dry);   		 
		DrawMap2(12,4,Field_seed_wet);   		 
		DrawMap2(12,6,Field_birds1);   		 
		DrawMap2(14,4,Field_empty_dry);   		 
		DrawMap2(14,6,Field_empty_dry);   		 


		// Beet 2
		DrawMap2(21,4,Field_tomato1_dry);   		 
		DrawMap2(21,6,Field_tomato1_dry);   		 
		DrawMap2(23,4,Field_corn1_wet);   		 
		DrawMap2(23,6,Field_corn1_wet);   		 
		DrawMap2(25,4,Field_marrot1);   		 
		DrawMap2(25,6,Field_potato1_dry);   		 


		// Beet 3
		DrawMap2(10,12,Field_corn_fin);   		 
		DrawMap2(10,14,Field_corn_fin);   		 
		DrawMap2(12,12,Field_corn3_wet);   		 
		DrawMap2(12,14,Field_corn3_dry);   		 
		DrawMap2(14,12,Field_corn2_wet);   		 
		DrawMap2(14,14,Field_corn2_dry);   		 


		// Beet 4
		DrawMap2(21,12,Field_turnip1_dry);   		 
		DrawMap2(21,14,Field_turnip1_dry);   		 
		DrawMap2(23,12,Field_turnip_fin);   		 
		DrawMap2(23,14,Field_turnip_fin);   		 
		DrawMap2(25,12,Field_carrot_fin);   		 
		DrawMap2(25,14,Field_carrot_fin);   		 


		// Beet 5
		DrawMap2(10,20,Field_eggplant_fin);   		 
		DrawMap2(10,22,Field_eggplant_fin);   		 
		DrawMap2(12,20,Field_potato_fin);   		 
		DrawMap2(12,22,Field_potato_fin);   		 
		DrawMap2(14,20,Field_tomato_fin);   		 
		DrawMap2(14,22,Field_tomato_fin);   		 


		// Beet 6
		DrawMap2(21,20,Field_broccoli_fin);   		 
		DrawMap2(21,22,Field_broccoli_fin);   		 
		DrawMap2(23,20,Field_broccoli2_dry);   		 
		DrawMap2(23,22,Field_broccoli2_wet);   		 
		DrawMap2(25,20,Field_broccoli1_dry);   		 
		DrawMap2(25,22,Field_broccoli1_wet);   	
		
		// Menu tools
		//msg_window(0,0,7,16); 
		//msg_window(1,0,29,5); 
		Fill(0,0,7,28,0);
		Print(1,1,PSTR("TOOLS"));
		
		DrawMap2(1,3,Tool_hoe);   		 
		DrawMap2(4,3,Tool_seed); 
		DrawMap2(1,6,Tool_watering_can); 
		DrawMap2(4,6,Tool_spray); 
		//DrawMap2(1,15,Tool_basket); 
		DrawMap2(1,9,Tool_basket); 
		
		DrawMap2(0,2,MARKER_UL);		
		DrawMap2(3,2,MARKER_UR);		
		DrawMap2(0,5,MARKER_DL);		
		DrawMap2(3,5,MARKER_DR);	
		
		Print(1,13,PSTR("SEEDS"));	
		DrawMap2(1,15,Fruit_potato);   		 
		DrawMap2(4,15,Fruit_corn); 
		DrawMap2(1,18,Fruit_eggplant); 
		DrawMap2(4,18,Fruit_tomato); 
		DrawMap2(1,21,Fruit_carrot); 
		DrawMap2(4,21,Fruit_peanut); 
		DrawMap2(1,24,Fruit_turnip); 
		DrawMap2(4,24,Fruit_broccoli); 


	    // cursor is invisible now
	    StopSong();
		//ClearVram();

//		DrawMap2(9,8,Win8logo);
//		DrawMap2(9,24,Win8text);			
		break;

/*
	  case	PM_Win8:

	   
		// init tile table
  		SetTileTable(BGTiles);
        ClearVram();


		DrawMap2(1,4,Icon_Explorer);		
		DrawMap2(1,11,Icon_Twitter);		
	    DrawMap2(8,4,Icon_Facebook);		
		DrawMap2(8,11,Icon_Google);		
		DrawMap2(1,18,Icon_Mail);		

		DrawMap2(15,4,Icon_Games);				
		DrawMap2(15,11,Icon_Skype);		
		DrawMap2(22,11,Icon_Video);		
		DrawMap2(15,18,Icon_Calendar);		
		DrawMap2(22,18,Icon_Shop);		

		MapSprite2(1,map_mouse,0);
		//MapSprite2(1,map_hCursor,0);
		SetSpriteVisibility(true);	
					
		break;
*/


	}



	program_mode = mode;

}






void button_handler(u8 PosX, u8 PosY) {
/*
if (program_mode == PM_Win8) {
	// button explorer
	if ((PosX>= 1*8) && (PosX<= 7*8) &&
		(PosY>= 4*8) && (PosY<= 10*8)) {
		set_PM_mode(PM_Explorer);

	} 
	// button Twitter
	else if ((PosX>= 1*8) && (PosX<= 7*8) &&
		(PosY>= 11*8) && (PosY<= 17*8)) {
		set_PM_mode(PM_Twitter);

	}
	// button Facebook
	else if ((PosX>= 8*8) && (PosX<= 14*8) &&
		(PosY>= 4*8) && (PosY<= 10*8)) {
		set_PM_mode(PM_Facebook);

	}
	// button Google+
	else if ((PosX>= 8*8) && (PosX<= 14*8) &&
		(PosY>= 11*8) && (PosY<= 17*8)) {
		set_PM_mode(PM_Google);

	}
	// button mail
	else if ((PosX>= 1*8) && (PosX<= 14*8) &&
		(PosY>= 18*8) && (PosY<= 24*8)) {
		set_PM_mode(PM_Mail);

	}
	// button Games
	else if ((PosX>= 15*8) && (PosX<= 28*8) &&
		(PosY>= 4*8) && (PosY<= 10*8)) {
		set_PM_mode(PM_UzeboxGames);

	}
	// button Skype
	else if ((PosX>= 15*8) && (PosX<= 21*8) &&
		(PosY>= 11*8) && (PosY<= 17*8)) {
		set_PM_mode(PM_Skype);

	}
	// button Video
	else if ((PosX>= 22*8) && (PosX<= 28*8) &&
		(PosY>= 11*8) && (PosY<= 17*8)) {
		set_PM_mode(PM_Video);

	}
	// button Calendar
	else if ((PosX>= 15*8) && (PosX<= 21*8) &&
		(PosY>= 18*8) && (PosY<= 24*8)) {
		set_PM_mode(PM_Calendar);

	}
	// button Shop
	else if ((PosX>= 22*8) && (PosX<= 28*8) &&
		(PosY>= 18*8) && (PosY<= 24*8)) {
		set_PM_mode(PM_Shop);

	}

} else if ((program_mode == PM_Twitter) || (program_mode == PM_Facebook)|| (program_mode == PM_Video)|| (program_mode == PM_Google)) {
	// button exit
	if ((PosX>= 24*8) && (PosX<= 26*8) &&
		(PosY>= 5*8) && (PosY<= 7*8)) {
		set_PM_mode(PM_Win8);
		
	} 

} else if (program_mode != PM_Intro) {
	// button exit
	if ((PosX>= 23*8) && (PosX<= 25*8) &&
		(PosY>= 5*8) && (PosY<= 7*8)) {
		set_PM_mode(PM_Win8);
		
	} 
	
}

*/
}




/**** S T U F F ********************************************************************/


void msg_window(u8 x1, u8 y1, u8 x2, u8 y2) {
// draw a window with frame and black backgound on the screen
u8 uc1,uc2;
    // window backgound
	for(uc1 = 1; uc1 < (x2 - x1 - 1); uc1++) 
	for(uc2 = 1; uc2 < (y2 - y1); uc2++) SetTile(x1 + uc1,y1 + uc2,0);
	// lower + upper frame 
	for(uc1 = 1; uc1 < (x2 - x1); uc1++) {
	   DrawMap2(x1 + uc1,y1,Frame_UH);
	   DrawMap2(x1 + uc1,y2,Frame_DH);
    }
	// left & rightframe
    for(uc1 = 1; uc1 < (y2 - y1); uc1++) {
	  DrawMap2(x1,y1 + uc1,Frame_VL);	// left
	  DrawMap2(x2 - 1,y1 + uc1,Frame_VR);	// right	
	}
	// upper, left corner
	DrawMap2(x1,y1,Frame_UL);
	// upper, right corner
	DrawMap2(x2 - 1,y1,Frame_UR);
	// lower, left corner
	DrawMap2(x1,y2,Frame_DL);
	// lower, right corner
	DrawMap2(x2 - 1,y2,Frame_DR);

	// place headline
	uc1 = x2 - x1;
	uc1 = uc1 / 2;
	uc1 -= 3;
	//DrawMap2(x1 + uc1,y1,Window_headline);

}	








/**
copy a buffer into another buffer 
@param source buffer
@param target buffer
@param count of copied bytes
@return none
*/
void copy_buf(unsigned char *BUFA, unsigned char *BUFB, unsigned char ucANZ)
{
 for(;ucANZ>0 ; ucANZ--)
 {
  *(BUFB++) = *(BUFA++);
 }   
}


/**
fill a buffer 
@param target buffer
@param byte to fill
@param count of copied bytes
@return none
*/
void fill_buf(u8 *BUFA, u8 content, u8 ucANZ)
{
 for(;ucANZ>0 ; ucANZ--)
 {
  *(BUFA++) = content;
 }   
}



