/*
----AA��\�違�\������ɂ�----
�c�[�����I�v�V�����������t�H���g����ѐF���e�L�X�g�G�f�B�^�[�@�Ńt�H���g�� MSP�S�V�b�N�ɕύX�B
�Ȃ񂩌��ɂ����C�����܂����A���̂�������܂��B�l�����Ă�����������ł��B
*/

/*
main.cpp

��{�I�ȏ����������܂��B
sysmain.cpp��WinMain�֐�����Ăяo����܂��B
*/

/*

Q.�R�[�h�̏����������ꂳ��ĂȂ��ĕ�����ɂ����ł�

A.
�@':,�@�@�@�@ ',�@�@�@_____,,.. -�] ''"�L�P�P�M"'' ��@�.,�@�@�@�@�@�@�@�@ �@�^
�@�@':,�@�@�@�@',�@�@ ��'�@�L�@�@�@�@�@�@�@�@�@�@�@�@�@�M�R.�@�@�@�@�@�@ /�@�@�@�@�m
�@�@�@':,�@�@�@�@ �^�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@ �@ �R.�@�@�@�@ ,'�@�@    �@ ��
�@�@�@�@':,�@�@ ,:' �^�@�@ �^�@ �@,'�L�@�@�@�@�@�@�@ �R.�@�@ �@ ':,/Ti�@ i.�@�@���@��
.�@�_�@�@�@�@,' /�@�@�@/�@ ,'�@�@!�@�@�@�@ �@;�@ �@',�@ �R__�@�^::::| |�@|�@�@ ��@��
�@�@�@�_�@ / ,'�@�@�@,'!�@ /!�@�@!�@ �@;�@�@/!�@�@�@i�@ �u:::|'�L::::::::| |�@.!.�@ ��  ��
�@�@�@�@ ��__,!�@�@ / !����v_,,./| �@ /!�@/�@!�@�@ �!�@|__�v��:::::�v�v�@|.�@�@ ��  ��
�M"''�@ �..,,_�@ !�@ /�@,�7�L, `i�R|�@/�@|�R��vƃC��@|�@ !�@|^�R��v�v �@|.�@�@ ��
�@�@�@�@�@�@�@i,�^ڲ�@i���@i.�@�' �@ '��L!_�v �n�R|�@�@�@|�@�@�@| �ځ@�@�@ ! !
��--�@ �@ �@/�@�@ !�@ �T- '�@�@�@�@ �@�@! �@�@ !�@!�@�@�@|�@�@�@|�@�@�M�R.
�@�@�@�@�@�@/�@ �@7/l/l/�@�@�@��@�@ �@�@`'��] '_�m!�@�@�@|�@ i�@ |�@ �@�@�M ' �---
,. -����-'��@�@,�l�@�@�@�@�Mi`��-- ��@�@/l/l/l |�@�@�@ !.�@|�@ |
�@�@�@�@�@�@ �R.��@ `: �. �@�@�'�@�@�@�@', �@ u�@,/|�@�@�@ |�@ !�@ |
�@�Ɓ@�@���@�@i�@�@/��= � '��@�@�@�@Ɂ@�@,.�C,��@�@�@ !�@ |�@ |
�@���@�@�C  �@.|�./|�^���ցM��-r�@ =�i�L�.,_�@|�@ i�@ ʁ@ !�@,'
�@��@�@���@�@ !�@�@�@�@ _,.�C�L�R.7�@�@ �^�@ /:::|�@/�'�@ �'�'
�@�ȁ@�@���@�@ | �@�@�^7:::::!�@�@���n'�L�@�@/::::::�'�R.
�@�́@  �ā@�@.|�@ /�@ /:::::::��'/���R.�@�@/::::::::/ �@ �R.
�@! !�@�@��@�@ ! ./�@ ,':::::::::::!/�@�n:::::�M�L:::::::::::;'�@�@�@�@',

*/



#include "common.h"

int tmp;
bool talkphase=true;

namespace chara{
	bullet_t tb[200]; //�G�e
	bullet_t tmb[200]; //�e�ړ�
	bullet_t jb[200]; //���@�e
	bullet_t jmb[200]; //�g���ĂȂ�
	jiki_t jiki={320,400,4,5,5,false,false};
	teki_t boss[20]={
		{320,30,100,100,false},
	};
}

namespace sys{
	square_t framesize={0,0,420,480};
}

using namespace chara;
using namespace sys;

//�֐��v���g�^�C�v�錾
void Move();
void TBulletMove();
void JBulletMove();
bool Jatari();
bool Tatari(); //����܂���
void Draw();

//���C�����[�v---------------------------------
int main(){

	if(talkphase==true){
		ShowNobel();
		talkphase=false;
	}

	Move();
	JBulletMove();
	if(Jatari()==true){
		jiki.life.now-=1;
		jiki.damage=true;
	}else jiki.damage=false;
	TBulletMove();
	if(jiki.life.now <=0) return 1;
	if(boss[0].life.now<=0) return 2;
	if(Tatari()==true){
		boss[0].damage=true;
		boss[0].life.now-=1;
	}else boss[0].damage=false;

	tmp=0;
	for(int i=0;i<100;i++){
		if(tb[i].avail==true) tmp++;
	}
	Draw();
}
//---------------------------------------------


void Draw(){
	//�{�X
	switch(stage){
	case 1:
		TekiDraw_1(boss[0].x,boss[0].y,boss[0].damage);
		break;
	}
	//���@
	DrawBox(jiki.x-10,jiki.y-10,jiki.x+10,jiki.y+10,GetColor(255,255,255),true);
	if(jiki.damage==true) DrawBox(jiki.x-10,jiki.y-10,jiki.x+10,jiki.y+10,Cred,true);
	if(jiki.ahantei==true){
		DrawCircle(jiki.x,jiki.y,2,Cred,true);
	}

	//�e
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

	//HUD
	//�F��`�I��
	DrawBox(framesize.right,0,640,480,GetColor(255,255,255),true);
	DrawBox(0,0,640*boss[0].life.now/boss[0].life.max,10,Cred,true);
	DrawFormatString(framesize.right+20,20,Cred,"�e��STG.Prototype");
	DrawFormatString(framesize.right+20,100,Cblack,"���O�̂��C�F%d",jiki.life.now);
	DrawFormatString(framesize.right+20,120,Cblack,"�{���F�g���܂���");
	DrawFormatString(framesize.right+20,140,Cblack,"Score�F������");
	DrawFormatString(framesize.right+20,160,Cblack,"HiScore�F�m��Ȃ��ł�");

	DrawFormatString(framesize.right+20,180,Cblack,"���W�F(%d,%d)",jiki.x,jiki.y);
	DrawFormatString(framesize.right+20,200,Cblack,"�A�N�e�B�u�Ȓe:%d/100",tmp);

	DrawFormatString(framesize.right+20,240,Cblue,"�ړ��F������(��ĂŽ۰)");
	DrawFormatString(framesize.right+20,260,Cblue,"�V���b�g�FZ");
	DrawFormatString(framesize.right+20,280,Cblue,"��߂�FESC");

	DrawFormatString(framesize.right+20,300,Cblack,"�G�̂��C�F%d",boss[0].life.now);
	DrawFormatString(framesize.right+20,340,Cred,"frame�F%d",frame);
	

}

void Move(){


	//���@�ړ�
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
	
	//�G�ړ�
	switch(stage){
	case 1:
		TekiMove_1(&boss[0].x,&boss[0].y);
		break;

	}

	//���@��ʊO����
	if(jiki.x>framesize.right) jiki.x=framesize.right;
	if(jiki.x<framesize.left) jiki.x=framesize.left;
	if(jiki.y>framesize.bottom) jiki.y=framesize.bottom;
	if(jiki.y<framesize.top) jiki.y=framesize.top;

}

void TBulletMove(){

	//�G�e����
	switch(stage){
	case 1:
		TekiBullet_1();
		break;

	}

}

void JBulletMove(){
	//���@�e���ˊ֐�
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

bool Jatari(){
	//���@�����蔻��

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

bool Tatari(){
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
	//�ϐ�������

	jiki.x=320,jiki.y=400;
	boss[0].x=320,boss[0].y=30;
	jiki.speed=4;
	jiki.ahantei=false; /*�����蔻��\���t���O*/
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
�����̃y�b�g�֕���

���[�t�@�X�I���[�t�@�X�I���[�t�@�X�I���[�t�@�X�����������킟����������������������������������������������I�I�I
�������������c�����c���������[�I�����������������I�I�I���[�t�@�X���[�t�@�X���[�t�@�X���������킟���������I�I�I
�����N���J�N���J�I�N���J�N���J�I�X�[�n�[�X�[�n�[�I�X�[�n�[�X�[�n�[�I�����������Ȃ��c���񂭂�
��͂����I���[�t�@�X����̃u���b�h���b�h�̓����N���J�N���J���������I�N���J�N���J�I�������I�I
�ԈႦ���I���t���t���������I���t���t�I���t���t�I�E�E���t���t�I�J���J�����t���t�c����񂫂�񂫂ア�I�I
�ʐ^�̃��[�t�@�X���񂩂킢�������患�I�I�����������c�������c�����������������I�I�ӂ��������������I�I
�t�g�A�S���Ԃ�CM�o�����ėǂ������˃��[�t�@�X����I���������������I���킢���I���[�t�@�X����I���킢���I���������������I
�n�[�l�X����������Ċ����c���₟�������������I�I�I�ɂႠ����������������I�I���Ⴀ���������������I�I
�������������������������I�I�I�U���Ȃ�Č�������Ȃ��I�I�I�I���c�ӎv�a�ʂ��X�L���V�b�v���悭�l������c
�� �[ �t �@ �X �� �� �� �� ���� �� �� �� ���H�ɂႠ��������������������������I�I�������������������������I�I
����Ȃ��������������I�I���₟�����������������������I�I�͂���������������I�I���v��645�����������I�I
���́I��������[�I��߂Ă��I�I�����Ȃ񂩂�߁c�āc���I�H���c�Ă�H�ʐ^�̃��[�t�@�X����񂪖l�����Ă�H
jpg�̃��[�t�@�X����񂪖l�����Ă邼�I���[�t�@�X����񂪖l�����Ă邼�I�����̃��[�t�@�X����񂪖l�����Ă邼�I�I
��̂Ђ�̃��[�t�@�X����񂪖l�ɘb�������Ă邼�I�I�I�悩�����c���̒��܂��܂��̂Ă���������Ȃ��񂾂˂��I
������ق����������������I�I�I�l�ɂ̓��[�t�@�X����񂪂���I�I������惌�I�p�I�I�ЂƂ�łł������I�I�I
���A�u���O�̃��[�t�@�X���Ⴀ����������������������������I�I���₟�������������������������������I�I�I�I
�������񂠂��������񂠃��[���b�p�C�G�R�I���M�����I�I�R�A�R�[���X�l�[�N�I�I�R���h�I�I�g�J�Q���������������I�I�I�O���[���C�O�A�i���������I�I
���������������I�I���̑z���惋�[�t�@�X�֓͂��I�I���v��645�̃��[�t�@�X�֓͂��I
*/

