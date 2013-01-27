/*
ui.cpp

スタート画面などのUIを呼び出す関数です。

*/



#include "common.h"

typedef struct{
	char name[20];
	int color;
	int x;
	int y;
} menuelm;


int StartScreen(){
	char key[256];
	int sel=0;
	int decision=-2;
	int title_h=LoadGraph("res\\title.png");
	bool past_push=false;
	int ELEMNUM=5;
	int STRLINE=400;

	static menuelm menu[]={
		{"Start",Cwhite,STRLINE,200,},
		{"Exit",Cwhite,STRLINE,250,},
		{"Element Sample",Cwhite,STRLINE,300,},
		{"[insert text here]",Cwhite,STRLINE,350,},
		{"example",Cwhite,STRLINE,400,},
	};

	while(ProcessMessage()==0 && decision==-2){
		ClearDrawScreen();
		GetHitKeyStateAll(key);
		if(past_push==false){
			if(key[KEY_INPUT_UP]==1) sel-=1;
			if(key[KEY_INPUT_DOWN]==1) sel+=1;
			if(key[KEY_INPUT_Z]==1){
				past_push=true;
				decision=sel;
			}
			if(sel < 0) sel=ELEMNUM-1;
			if(sel > ELEMNUM-1) sel=0;
		}
			if(CheckHitKeyAll()==0) past_push=false; else past_push=true;
			
			
			for(int i=0; i<ELEMNUM; i++){
				if(i==sel) {
					DrawFormatString(menu[i].x-20,menu[i].y,Cred,menu[i].name);
					menu[i].x-=5;
					if(STRLINE-menu[i].x > 20) menu[i].x=STRLINE-20;
				}
				else {
					DrawFormatString(menu[i].x,menu[i].y,menu[i].color,menu[i].name);
					menu[i].x+=5;
					if(STRLINE <= menu[i].x) menu[i].x=STRLINE;
				}
			}
			
			DrawGraph(20,40,title_h,true);
			DrawStringToHandle(270,90,"(C) Nicc",Cwhite,Fsmall);
			DrawStringToHandle(10,460,"Press arrow key to move, Z key to select ",Cwhite,Fnorm);
			ScreenFlip();
	}

	DeleteGraph(title_h);
	if(ProcessMessage()==-1) decision=-1;
	return decision;
}


void ShowNobel(){
	switch(stage){
	case 1:
		ShowNobel_1();
		break;

	default:
		break;
	}
}