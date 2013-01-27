/*
text.cpp
ノベルゲーム風の表示を行う関数を定義

参考： http://karetta.jp/book-node/game-programming/235056
*/

#include "common.h"
#include "sysmain.h"

#define MSG_MAX_LINE 5
#define MSG_MAX_LEN 30

int chara_num;
int chara_side;

void DrawTextBox(){
	DrawBox(50,340,590,460,Cwhite,false);
}

void DrawCharaGraph(int num){
	switch(num){
	case 1:
		DrawGraph(400,50,h_chara[0],true);
		break;
	case 2:
		DrawGraph(50,50,h_chara[1],true);
		break;
	case 3:
		DrawGraph(200,50,h_chara[2],true);
		break;
	}
}

bool isJapaneseCharacter(unsigned char str){
	if((str>=0x81 && str<=0x9F ) || (str>=0xE0 && str<=0xFC)) return true;
	return false;
}

void WriteString(char* str,  int start, int len, int x, int y, int line){
	int i=0;
	int max=strlen(str);
	char buf[MSG_MAX_LINE][MSG_MAX_LEN];

	for(i=0; i<start && str[i]!='\0'; ){
		if(isJapaneseCharacter(str[i])){
			i+=2;
			start++;
		} else {
			i++;
		}
	}
	
	if(start>max){
		return;
	}

	for(i=0; i<len && str[start+i]!='\0'; ){

		if(isJapaneseCharacter(str[start+i])){
			buf[line][i]=str[start+i];
			buf[line][i+1]=str[start+i+1];
			len++;
			i+=2;
		} else {
			buf[line][i]=str[start+i];
			i++;
		}
	}
	
	buf[line][i]='\0';

	DrawString(x,y,buf[line],Cwhite);
}

void SetDrawChara(int num, int side){
	chara_num=num;
	chara_side=side;
}

void WriteNobelString(char* str){
	int line=0;
	int defx=60;
	int defy=360;

	for(int i=0; str[i]!='\0' && CheckHitKey(KEY_INPUT_LCONTROL)==0 ; i++){

		ClearDrawScreen();
		DrawCharaGraph(chara_num);
		DrawTextBox();

		if(i!=0 && i%MSG_MAX_LEN==0){
			line+=1;
		}

		for(int n=0; n<MSG_MAX_LINE; n++){
			if(n==line){
				WriteString(str, n*MSG_MAX_LEN, i-n*MSG_MAX_LEN, defx, defy+20*n,  n);
				break;
			} else {
				WriteString(str, n*MSG_MAX_LEN, MSG_MAX_LEN, defx, defy+20*n, n);
			}
		}

		Sleep(1);

		ScreenFlip();
	}
	while(ProcessMessage()==0 && (CheckHitKey(KEY_INPUT_Z)==0 && CheckHitKey(KEY_INPUT_LCONTROL)==0) ){

	}
}

//ここから下はゴミのたまり場---------------

void WriteNobelString(char* str, char* str2){
	int line=0;
	int defx=50;
	int defy=350;
	int past_n;
	int handle=LoadGraph("res\\null2.png");

	for(int i=0; str[i]!='\0' && CheckHitKey(KEY_INPUT_LCONTROL)==0 ; i++){
		ClearDrawScreen();
		DrawGraph(400,250,handle,true);

		if(i!=0 && i%MSG_MAX_LEN==0){
			line+=1;
		}

		for(int n=0; n<MSG_MAX_LINE; n++){
			if(n==line){
				WriteString(str, n*MSG_MAX_LEN, i-n*MSG_MAX_LEN, defx, defy+20*n,  n);
				break;
			} else {
				WriteString(str, n*MSG_MAX_LEN, MSG_MAX_LEN, defx, defy+20*n, n);
			}
		}
		Sleep(20);
		ScreenFlip();
	}

	WaitKey();
	line=0;

	for(int i=0; str[i]!='\0' && CheckHitKey(KEY_INPUT_LCONTROL)==0 ; i++){
		DrawGraph(400,250,handle,true);

		if(i!=0 && i%MSG_MAX_LEN==0){
			line+=1;
		}

		for(int n=0; n<MSG_MAX_LINE; n++){
			if(n==line){
				WriteString(str, n*MSG_MAX_LEN, i-n*MSG_MAX_LEN, defx, defy+20*n,  n);
				past_n=n;
				break;
			} else {
				WriteString(str, n*MSG_MAX_LEN, MSG_MAX_LEN, defx, defy+20*n, n);
			}
		}
	}

	for(int i=0; str2[i]!='\0' && CheckHitKey(KEY_INPUT_LCONTROL)==0 ; i++){
		DrawGraph(400,250,handle,true);

		if(i!=0 && i%MSG_MAX_LEN==0){
			line+=1;
		}

		for(int n=0; n<MSG_MAX_LINE; n++){
			if(n==line){
				WriteString(str2, n*MSG_MAX_LEN, i-n*MSG_MAX_LEN, defx, defy+20*(n+past_n+1),  n);
				break;
			} else {
				WriteString(str2, n*MSG_MAX_LEN, MSG_MAX_LEN, defx, defy+20*(n+past_n+1), n);
			}
		}
		ScreenFlip();
		Sleep(20);
	}

	WaitKey();
}

void WriteNobelString(char* str, char* str2, char* str3){
	int line=0;
	int defx=50;
	int defy=300;
	int past_n;
	int handle=LoadGraph("res\\null2.png");

	for(int i=0; str[i]!='\0' && CheckHitKey(KEY_INPUT_LCONTROL)==0 ; i++){
		ClearDrawScreen();
		DrawGraph(400,250,handle,true);

		if(i!=0 && i%MSG_MAX_LEN==0){
			line+=1;
		}

		for(int n=0; n<MSG_MAX_LINE; n++){
			if(n==line){
				WriteString(str, n*MSG_MAX_LEN, i-n*MSG_MAX_LEN, defx, defy+20*n,  n);
				break;
			} else {
				WriteString(str, n*MSG_MAX_LEN, MSG_MAX_LEN, defx, defy+20*n, n);
			}
		}
		Sleep(20);
		ScreenFlip();
	}

	WaitKey();
	line=0;

	for(int i=0; str[i]!='\0' && CheckHitKey(KEY_INPUT_LCONTROL)==0 ; i++){
		DrawGraph(400,250,handle,true);

		if(i!=0 && i%MSG_MAX_LEN==0){
			line+=1;
		}

		for(int n=0; n<MSG_MAX_LINE; n++){
			if(n==line){
				WriteString(str, n*MSG_MAX_LEN, i-n*MSG_MAX_LEN, defx, defy+20*n,  n);
				past_n=n;
				break;
			} else {
				WriteString(str, n*MSG_MAX_LEN, MSG_MAX_LEN, defx, defy+20*n, n);
			}
		}
	}

	for(int i=0; str2[i]!='\0' && CheckHitKey(KEY_INPUT_LCONTROL)==0 ; i++){
		DrawGraph(400,250,handle,true);

		if(i!=0 && i%MSG_MAX_LEN==0){
			line+=1;
		}

		for(int n=0; n<MSG_MAX_LINE; n++){
			if(n==line){
				WriteString(str2, n*MSG_MAX_LEN, i-n*MSG_MAX_LEN, defx, defy+20*(n+past_n+1),  n);
				break;
			} else {
				WriteString(str2, n*MSG_MAX_LEN, MSG_MAX_LEN, defx, defy+20*(n+past_n+1), n);
			}
		}
		ScreenFlip();
		Sleep(20);
	}
	WaitKey();
	line=0;

	for(int i=0; str[i]!='\0' && CheckHitKey(KEY_INPUT_LCONTROL)==0 ; i++){
		DrawGraph(400,250,handle,true);

		if(i!=0 && i%MSG_MAX_LEN==0){
			line+=1;
		}

		for(int n=0; n<MSG_MAX_LINE; n++){
			if(n==line){
				WriteString(str, n*MSG_MAX_LEN, i-n*MSG_MAX_LEN, defx, defy+20*n,  n);
				past_n=n;
				break;
			} else {
				WriteString(str, n*MSG_MAX_LEN, MSG_MAX_LEN, defx, defy+20*n, n);
			}
		}
	}

	for(int i=0; str2[i]!='\0' && CheckHitKey(KEY_INPUT_LCONTROL)==0 ; i++){
		DrawGraph(400,250,handle,true);

		if(i!=0 && i%MSG_MAX_LEN==0){
			line+=1;
		}

		for(int n=0; n<MSG_MAX_LINE; n++){
			if(n==line){
				WriteString(str2, n*MSG_MAX_LEN, i-n*MSG_MAX_LEN, defx, defy+20*(n+past_n+1),  n);
				past_n=n;
				break;
			} else {
				WriteString(str2, n*MSG_MAX_LEN, MSG_MAX_LEN, defx, defy+20*(n+past_n+1), n);
			}
		}
	}

	for(int i=0; str3[i]!='\0' && CheckHitKey(KEY_INPUT_LCONTROL)==0 ; i++){
		DrawGraph(400,250,handle,true);

		if(i!=0 && i%MSG_MAX_LEN==0){
			line+=1;
		}

		for(int n=0; n<MSG_MAX_LINE; n++){
			if(n==line){
				WriteString(str3, n*MSG_MAX_LEN, i-n*MSG_MAX_LEN, defx, defy+20*(n+past_n+2),  n);
				break;
			} else {
				WriteString(str3, n*MSG_MAX_LEN, MSG_MAX_LEN, defx, defy+20*(n+past_n+2), n);
			}
		}
		ScreenFlip();
		Sleep(20);
	}	
	WaitKey();
}