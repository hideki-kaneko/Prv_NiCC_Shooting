/*
sysmain.cpp

ここのWinMain関数からスタートします。
main.cppのmainで描画した内容を、ループごとにフリップ・消去します。
mainでは、WaitKeyなどでループから脱出しない場合を除きScreenFlipを行う必要はありません。
*/

/*

○ void型以外の関数を作る場合の注意点 ○


　　　)､.＿人＿人__,.イ.､._人＿人＿人
　 ＜´ 　　 値　返　し　て　っ　！　　　＞
　　 ⌒ v'⌒ヽr -､＿ ,r v'⌒ヽr ' ⌒ヽr
// // //／::　<　　 ＿,ノ｀' 、ヽ､＿　ノ 　;;;ヽ　 //
///// /::::　　　（y○'）｀ヽ) ( ´（y○'）　 　　;;|　　/
// //,|:::　　　　　（ (　/　　　　ヽ) ）+　　　 　;| /
/ // |:::　 　　　+　 ) ）|~￣￣~.|（ (　　 　 　 ;;;|// ////
/// :|::　　　　 　　（ (||||! i: |||! !| |) ）　 　 　 ;;;|// ///
////|::::　　　　+　　 U | |||| !! !!||| :U　　　;;; ;;;|　///
////|:::::　　　　　　　| |!!||l ll|| !! !!| | 　　　;;;;;;|　////
// / ヽ:::::　　 　 　　| !　|| |　||!!|　　　　;;;;;;/// //
// // ゝ::::::::　:　　　| ｀ー----－'　|＿_／///
*/

#include "common.h"

//グローバル変数
unsigned short int frame=0; //フレーム用変数
double fps=0.0; //FPS
char key[256]; //キーの入力状態格納
int Cred, Cblack, Cblue, Cwhite; //色定義
int Fsmall,Fnorm;
int stage=1; //ステージ番号

int h_chara[50];

//関数プロトタイプ宣言
double GetFPS(); 
void SetColor();
void SetFont();


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow ){

	//初期化-----
	srand((unsigned)time(NULL)); //乱数のシード値をランダムに指定
	ChangeWindowMode(true);
	if(DxLib_Init()==-1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	SetColor();
	SetFont();
	LoadCharacterGraph();
	//初期化終了-----

	title:
	switch(StartScreen()){
	case -1:
		goto end;
		break;
	case 0:
		break;
	case 1:
		goto end;
		break;
	default:
		DrawFormatString(200,220,Cblue,"ERROR: フラグが定義されてないよう…");
		ScreenFlip();
		WaitKey();
		goto end;
		break;
	}

	//メインループ
	start:

	while(ProcessMessage()==0 && CheckHitKey(KEY_INPUT_ESCAPE)==0){

		fps=GetFPS();

		GetHitKeyStateAll(key);
		ClearDrawScreen();

		//main関数を呼び出し、返り値が0以外なら何か実行
		switch(main()){
		case 1:
			DrawFormatString(320,200,GetColor(255,255,255),"死んだ");
			ScreenFlip();
			WaitKey();
			var_init();
			goto start;
			break;
		case 2:
			DrawFormatString(320,220,GetColor(255,255,255),"すごい");
			ScreenFlip();
			WaitKey();
			var_init();
			goto start;
			break;
		}

		DrawFormatString(0,450,GetColor(255,255,255),"%.1f FPS",fps);

		ScreenFlip();
	}

end:

	//終了処理
	DxLib_End();
	return 0;
}

double GetFPS(){
	//FPSを取得する関数
	static double result=0;
	static double tmptime[2];

	if(frame==0){
		tmptime[0]=GetNowCount();
	}
	
	if(frame>=29){
		tmptime[1]=GetNowCount();
		result=1000.0f/((tmptime[1]-tmptime[0])/30.0f);
		frame=0;
	}else frame++;

	return result;
}

void SetColor(){
	Cred = GetColor(200,0,0);
	Cblack = GetColor(0,0,0);
	Cblue = GetColor(0,200,0);
	Cwhite = GetColor(255,255,255);
}

void SetFont(){
	Fsmall=CreateFontToHandle(NULL,12,4);
	Fnorm=CreateFontToHandle(NULL,14,4);
}

/*

今日の一言

・2012/11/24	なんか　ねむい
・2012/11/25	ランゲルハンス島に財宝が眠るらしい
・2012/11/26	帰ったら米が炊けてなくて泣いた
・2012/11/28	デバッグ中にjiki.life.maxとかをウォッチに追加しようとしたらCX0017エラー吐かれた
・2012/11/29	部員が簡易水冷クーラー買ったそうな。やっぱ水冷って（なんとなく）いいよね！
・2012/12/08	ぱそこんが　おもい　でも　いじるの　めんどい
・2012/12/11 インテリセンスが間違ってないとこをエラー指摘してきた。ドジっ子なんだね
・2013/01/23 何なんだVS2012の配色は！？IDEまでモダンUIを意識しないでくれ！！
*/