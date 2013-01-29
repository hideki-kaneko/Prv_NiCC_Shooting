#include "common.h"

//グローバル変数
namespace graph{
	int chara[50];
	int hdmaru[3];
	int compterve;
	int textbox;
	int back[10];
}
using namespace graph;

void LoadGraphics(){
	//gui
	textbox=LoadGraph("res\\gui\\wakuwaku.png");
	
	//background
	back[0]=LoadGraph("res\\background\\back_beta.png");

	//craft
	hdmaru[0]=LoadGraph("res\\craft\\hodakamaru.png");
	hdmaru[1]=LoadGraph("res\\craft\\hodakamaru_left.png");
	hdmaru[2]=LoadGraph("res\\craft\\hodakamaru_right.png");
	compterve=LoadGraph("res\\craft\\COM_P_TERVE_03.png");

	//character
	chara[0]=LoadGraph("res\\null_i.png");
	chara[1]=LoadGraph("res\\jorry_t.png");
	chara[2]=LoadGraph("res\\muri.png");

}