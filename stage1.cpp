/*
stage1.cpp

�����X�e�[�W�ɑΉ������邽�߂́A�e�֐��𕪎U�����鎎�݂ł��B
�G�̈ړ��E�`��E�e���˂������ɒ�`���܂��B���̃t�@�C������֐����ĂԂɂ́Ainclude����w�b�_��extern����K�v������܂��B
�܂��A�e�̕ϐ��Ƃ������L���Ă�̂ŏՓ˖h�~��namespace�g���Ă܂����A�g�������w�^�Ȃ̂ňӖ��𐬂��Ă��܂���B
*/


#include "common.h"
#include "stage1_p.h"

using namespace chara;
using namespace sys;

void TekiMove_1(int *x,int *y){

	if(*x>framesize.right+30){
		*x=framesize.left-30;
	}else if(*x<framesize.left-30){
		*x=framesize.right+30;
	}else{
		*x+=3;
	}

}

void TekiDraw_1(int x,int y,bool flag){
	DrawBox(x-30,y-15,x+30,y+15,Cred,true);
	if(flag==true) DrawBox(x-30,y-15,x+30,y+15,GetColor(255,255,255),true);

}

bool TekiHit_1(){
	static bool result;
	result=false;
	for(int i=0;i<=199;i++){
		if(boss[0].x-30<jb[i].x && jb[i].x<boss[0].x+30 && boss[0].y-10<jb[i].y && jb[i].y<boss[0].y+10){
			result=true;
		}
	}
	return result;

}

void TekiBullet_1(){
	static int dist;
	static float angle;

	for(int i=0;i<100;i++){
		

		if(tb[i].avail==false){
			dist=2+GetRand(4);
			angle=1+GetRand(358);
			angle=angle/180;
			tmb[i].x= dist*cos(angle);
			tmb[i].y= dist*sin(angle);
			tb[i].avail=true;
			tb[i].x=boss[0].x;
			tb[i].y=boss[0].y;
		}
		
		if(tb[i].x > framesize.right+6 || tb[i].x < framesize.left-6 || tb[i].y < framesize.top-6 || tb[i].y > framesize.bottom+6){
			tb[i].avail=false;
		}else{

		}

		if(tb[i].avail==true){
			tb[i].x=tb[i].x+tmb[i].x;
			tb[i].y+=tmb[i].y;
		}

	}

}

void ShowNobel_1(){
	SetDrawChara(0,1);
	WriteNobelString("�e�X�g���b�Z�[�W�ł��B");
}