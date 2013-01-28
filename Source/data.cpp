#include "common.h"

//グローバル変数
namespace graph{
	int chara[50];
	int hdmaru[3];
	int compterve;
	int textbox;
}
using namespace graph;

void LoadGraphics(){
	//gui
	textbox=LoadGraph("bin\\gui\\wakuwakusan.png");

	//craft
	hdmaru[0]=LoadGraph("bin\\craft\\hodakamaru.png");
	hdmaru[1]=LoadGraph("bin\\craft\\hodakamaru_left.png");
	hdmaru[2]=LoadGraph("bin\\craft\\hodakamaru_right.png");
	compterve=LoadGraph("bin\\craft\\COM_P_TERVE_03.png");

	//character
	chara[0]=LoadGraph("bin\\null_i.png");
	chara[1]=LoadGraph("bin\\jorry_t.png");
	chara[2]=LoadGraph("bin\\muri.png");

}