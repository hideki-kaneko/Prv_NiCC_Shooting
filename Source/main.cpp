﻿
/*
main.cpp

基本的な処理を書きます。
sysmain.cppのWinMain関数から呼び出されます。
*/


#include "common.h"

int active_bullets;
bool talkphase=true;

namespace chara{
	bullet_t tb[200]; //敵弾
	bullet_t tmb[200]; //弾移動
	bullet_t jb[200]; //自機弾
	bullet_t jmb[200]; //使ってない
	jiki_t jiki={320,400,4,5,5,false,false};
	teki_t boss[20]={
		{320,30,100,100,false},
	};
}

namespace sys{
	//square_t framesize={0,0,420,480};
	square_t framesize={0,0,640,480};
}

using namespace chara;
using namespace sys;

//関数プロトタイプ宣言
void Move();
void TBulletMove();
void JBulletMove();
bool isJikiHit();
bool isTekiHit();
void Draw();

//メインループ---------------------------------
int main(){
	DrawGraph(0,0,graph::back[0],true);
	if(talkphase==true){
		ShowNobel();
		talkphase=false;
	}

	Move();
	JBulletMove();
	if(isJikiHit()==true){
		jiki.life.now-=1;
		jiki.damage=true;
	}else jiki.damage=false;
	TBulletMove();
	if(jiki.life.now <=0) return 1;
	if(boss[0].life.now<=0) return 2;
	if(isTekiHit()==true){
		boss[0].damage=true;
		boss[0].life.now-=1;
	}else boss[0].damage=false;

	active_bullets=0;
	for(int i=0;i<100;i++){
		if(tb[i].avail==true) active_bullets++;
	}
	Draw();
}
//---------------------------------------------


void Draw(){
	//ボス
	switch(stage){
	case 1:
		TekiDraw_1(boss[0].x,boss[0].y,boss[0].damage);
		break;
	}
	//自機
	if(key[KEY_INPUT_LEFT]==1){
		DrawGraph(jiki.x-50,jiki.y-50,graph::hdmaru[1],true);
	} else if(key[KEY_INPUT_RIGHT]==1){
		DrawGraph(jiki.x-50,jiki.y-50,graph::hdmaru[2],true);
	} else DrawGraph(jiki.x-50,jiki.y-50,graph::hdmaru[0],true);

	if(jiki.damage==true) DrawBox(jiki.x-10,jiki.y-10,jiki.x+10,jiki.y+10,Cred,true);
	if(jiki.ahantei==true){
		DrawCircle(jiki.x,jiki.y,2,Cred,true);
	}

	//弾
	for(int i=0;i<200;i++){
		if(tb[i].avail==true){
			DrawCircle(tb[i].x,tb[i].y,3,Cblue,true);
		}
	}
	for(int i=0;i<200;i++){
		if(jb[i].avail==true){
			DrawBox(jb[i].x-3,jb[i].y-3,jb[i].x+3,jb[i].y+3,GetColor(255,255,255),true);
		}
	}

	//GUI
	DrawBox(framesize.right,0,640,480,GetColor(255,255,255),true);
	DrawBox(0,0,640*boss[0].life.now/boss[0].life.max,10,Cred,true);
	DrawFormatString(framesize.right+20,20,Cred,"弾幕STG.Prototype");
	DrawFormatString(framesize.right+20,100,Cblack,"お前のやる気：%d",jiki.life.now);
	DrawFormatString(framesize.right+20,120,Cblack,"ボム：使えません");
	DrawFormatString(framesize.right+20,140,Cblack,"Score：すごい");
	DrawFormatString(framesize.right+20,160,Cblack,"HiScore：知らないです");

	DrawFormatString(framesize.right+20,180,Cblack,"座標：(%d,%d)",jiki.x,jiki.y);
	DrawFormatString(framesize.right+20,200,Cblack,"アクティブな弾:%d/100",active_bullets);

	DrawFormatString(framesize.right+20,240,Cblue,"移動：方向ｷｰ(ｼﾌﾄでｽﾛｰ)");
	DrawFormatString(framesize.right+20,260,Cblue,"ショット：Z");
	DrawFormatString(framesize.right+20,280,Cblue,"やめる：ESC");

	DrawFormatString(framesize.right+20,300,Cblack,"敵のやる気：%d",boss[0].life.now);
	DrawFormatString(framesize.right+20,340,Cred,"frame：%d",frame);
	

}

void Move(){
	//自機移動
	if(key[KEY_INPUT_LSHIFT]==1){
		jiki.speed=3;
		jiki.ahantei=true;
	}else{
		jiki.speed=6;
		jiki.ahantei=false;
	}
	if(key[KEY_INPUT_LEFT]==1){
		jiki.x-=jiki.speed;
	}
	if(key[KEY_INPUT_RIGHT]==1){
		jiki.x+=jiki.speed;
	}
	if(key[KEY_INPUT_UP]==1){
		jiki.y-=jiki.speed;
	}
	if(key[KEY_INPUT_DOWN]==1){
		jiki.y+=jiki.speed;
	}
	
	//敵移動
	switch(stage){
	case 1:
		TekiMove_1(&boss[0].x,&boss[0].y);
		break;

	}

	//自機画面外処理
	if(jiki.x>framesize.right) jiki.x=framesize.right;
	if(jiki.x<framesize.left) jiki.x=framesize.left;
	if(jiki.y>framesize.bottom) jiki.y=framesize.bottom;
	if(jiki.y<framesize.top) jiki.y=framesize.top;

}

void TBulletMove(){

	//敵弾発射
	switch(stage){
	case 1:
		TekiBullet_1();
		break;

	}

}

void JBulletMove(){
	//自機弾発射関数
	static int max=0;

	if(key[KEY_INPUT_Z]==1 && frame%2==1){
		if(max >=199) max=0;
		max+=1;
	}else if(key[KEY_INPUT_Z]==0){
		max=0;
	}


	if(key[KEY_INPUT_Z]==1 && jb[max].avail==false){
		jb[max].x=jiki.x;
		jb[max].y=jiki.y;
		jb[max].avail=true;
	}


	for(int i=0;i<200;i++){
		if(jb[i].x > framesize.right+6 || jb[i].x < framesize.left-6 || jb[i].y < framesize.top-6 || jb[i].y > framesize.bottom+6){
			jb[i].avail=false;
		}else{
			jb[i].y-=15;
		}
	}

}

bool isJikiHit(){
	//自機当たり判定
	static bool result;
	result=false;
	for(int i=0;i<=199;i++){
		if(sqrt(pow(tb[i].x-jiki.x,2)+pow(tb[i].y-jiki.y,2)) < 6){
			tb[i].avail=false;
			result=true;
		}
	}
	return result;
}

bool isTekiHit(){
	switch(stage){
	case 1:
		return TekiHit_1();
		break;

	default:
		return false;
		break;
	}
}

void var_init(){
	//変数初期化

	jiki.x=320,jiki.y=400;
	boss[0].x=320,boss[0].y=30;
	jiki.speed=4;
	jiki.ahantei=false; /*当たり判定表示フラグ*/
	jiki.life.now=jiki.life.max;
	boss[0].life.now=boss[0].life.max;

	for(int i=0;i<200;i++){
		jb[i].x=-1;
		jb[i].y=-1;
		jb[i].avail=false;
		tb[i].x=-1;
		tb[i].y=-1;
		tb[i].avail=false;
	}
}

/*

Q.コードの書き方が統一されてなくて分かりにくいです

A.
　':,　　　　 ',　　　_____,,.. -‐ ''"´￣￣｀"'' ｰ　､.,　　　　　　　　 　／
　　':,　　　　',　　 ＞'　´　　　　　　　　　　　　　｀ヽ.　　　　　　 /　　　　知
　　　':,　　　　 ／　　　　　　　　　　　　　　　　　 　 ヽ.　　　　 ,'　　    　 っ
　　　　':,　　 ,:' ／　　 ／　 　,'´　　　　　　　 ヽ.　　 　 ':,/Ti　 i.　　そ　て
.　＼　　　　,' /　　　/　 ,'　　!　　　　 　;　 　',　 ヽ__　／::::| |　|　　 ん　る
　　　＼　 / ,'　　　,'!　 /!　　!　 　;　　/!　　　i　 「:::|'´::::::::| |　.!.　 な  わ
　　　　 ∠__,!　　 / !メ､」_,,./| 　 /!　/　!　　 ﾊ!　|__」＜:::::」」　|.　　 こ  よ
｀"''　 ､..,,_　 !　 /　,ｧ7´, `iヽ|　/　|ヽ､」ﾆイ､　|　 !　|^ヽ､」」 　|.　　 と
　　　　　　　i,／ﾚｲ　i┘　i.　ﾚ' 　 'ｱ´!_」 ハヽ|　　　|　　　| ∠　　　 ! !
─--　 　 　/　　 !　 ゝ- '　　　　 　　! 　　 !　!　　　|　　　|　　｀ヽ.
　　　　　　/　 　7/l/l/　　　､　　 　　`'ｰ‐ '_ノ!　　　|　 i　 |　 　　｀ ' ｰ---
,. -──-'､　　,人　　　　｀i`ｧｰ-- ､　　/l/l/l |　　　 !.　|　 |
　　　　　　 ヽ.ｿ　 `: ､. 　　ﾚ'　　　　', 　 u　,/|　　　 |　 !　 |
　と　　今　　i　　/ｰﾅ= ､ '､　　　　ﾉ　　,.イ,ｶ　　　 !　 |　 |
　こ　　修  　.|ﾍ./|／レへ｀＞-r　 =ﾆi´､.,_　|　 i　 ﾊ　 !　,'
　ろ　　正　　 !　　　　 _,.イ´ヽ.7　　 ／　 /:::|　/ﾚ'　 ﾚ'ﾚ'
　な　　し　　 | 　　／7:::::!　　○Ｏ'´　　/::::::ﾚ'ヽ.
　の　  て　　.|　 /　 /:::::::レ'/ムヽ.　　/::::::::/ 　 ヽ.
　! !　　る　　 ! ./　 ,':::::::::::!/　ハ:::::｀´:::::::::::;'　　　　',

*/