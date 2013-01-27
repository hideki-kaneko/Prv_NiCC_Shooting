/*
sysmain.cpp

������WinMain�֐�����X�^�[�g���܂��B
main.cpp��main�ŕ`�悵�����e���A���[�v���ƂɃt���b�v�E�������܂��B
main�ł́AWaitKey�ȂǂŃ��[�v����E�o���Ȃ��ꍇ������ScreenFlip���s���K�v�͂���܂���B
*/

/*

�� void�^�ȊO�̊֐������ꍇ�̒��ӓ_ ��


�@�@�@)�.�Q�l�Q�l__,.�C.�._�l�Q�l�Q�l
�@ ���L �@�@ �l�@�ԁ@���@�ā@���@�I�@�@�@��
�@�@ �� v'�܁Rr -��Q ,r v'�܁Rr ' �܁Rr
// // //�^::�@<�@�@ �Q,�m�M' �A�R��Q�@�m �@;;;�R�@ //
///// /::::�@�@�@�iy��'�j�M�R) ( �L�iy��'�j�@ �@�@;;|�@�@/
// //,|:::�@�@�@�@�@�i (�@/�@�@�@�@�R) �j+�@�@�@ �@;| /
/ // |:::�@ �@�@�@+�@ ) �j|~�P�P~.|�i (�@�@ �@ �@ ;;;|// ////
/// :|::�@�@�@�@ �@�@�i (||||! i: |||! !| |) �j�@ �@ �@ ;;;|// ///
////|::::�@�@�@�@+�@�@ U | |||| !! !!||| :U�@�@�@;;; ;;;|�@///
////|:::::�@�@�@�@�@�@�@| |!!||l ll|| !! !!| | �@�@�@;;;;;;|�@////
// / �R:::::�@�@ �@ �@�@| !�@|| |�@||!!|�@�@�@�@;;;;;;/// //
// // �T::::::::�@:�@�@�@| �M�[----�|'�@|�Q_�^///
*/

#include "common.h"

//�O���[�o���ϐ�
unsigned short int frame=0; //�t���[���p�ϐ�
double fps=0.0; //FPS
char key[256]; //�L�[�̓��͏�Ԋi�[
int Cred, Cblack, Cblue, Cwhite; //�F��`
int Fsmall,Fnorm;
int stage=1; //�X�e�[�W�ԍ�

int h_chara[50];

//�֐��v���g�^�C�v�錾
double GetFPS(); 
void SetColor();
void SetFont();


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow ){

	//������-----
	srand((unsigned)time(NULL)); //�����̃V�[�h�l�������_���Ɏw��
	ChangeWindowMode(true);
	if(DxLib_Init()==-1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	SetColor();
	SetFont();
	LoadCharacterGraph();
	//�������I��-----

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
		DrawFormatString(200,220,Cblue,"ERROR: �t���O����`����ĂȂ��悤�c");
		ScreenFlip();
		WaitKey();
		goto end;
		break;
	}

	//���C�����[�v
	start:

	while(ProcessMessage()==0 && CheckHitKey(KEY_INPUT_ESCAPE)==0){

		fps=GetFPS();

		GetHitKeyStateAll(key);
		ClearDrawScreen();

		//main�֐����Ăяo���A�Ԃ�l��0�ȊO�Ȃ牽�����s
		switch(main()){
		case 1:
			DrawFormatString(320,200,GetColor(255,255,255),"����");
			ScreenFlip();
			WaitKey();
			var_init();
			goto start;
			break;
		case 2:
			DrawFormatString(320,220,GetColor(255,255,255),"������");
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

	//�I������
	DxLib_End();
	return 0;
}

double GetFPS(){
	//FPS���擾����֐�
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

�����̈ꌾ

�E2012/11/24	�Ȃ񂩁@�˂ނ�
�E2012/11/25	�����Q���n���X���ɍ��󂪖���炵��
�E2012/11/26	�A������Ă������ĂȂ��ċ�����
�E2012/11/28	�f�o�b�O����jiki.life.max�Ƃ����E�H�b�`�ɒǉ����悤�Ƃ�����CX0017�G���[�f���ꂽ
�E2012/11/29	�������ȈՐ���N�[���[�����������ȁB����ϐ�����āi�Ȃ�ƂȂ��j������ˁI
�E2012/12/08	�ς����񂪁@�������@�ł��@������́@�߂�ǂ�
�E2012/12/11 �C���e���Z���X���Ԉ���ĂȂ��Ƃ����G���[�w�E���Ă����B�h�W���q�Ȃ񂾂�
�E2013/01/23 ���Ȃ�VS2012�̔z�F�́I�HIDE�܂Ń��_��UI���ӎ����Ȃ��ł���I�I
*/