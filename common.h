/*
common.h

���ʃw�b�_�t�@�C��
*/

/*
_________________________
�@�@�@�@������
�@�@�@�@�@�a�@
�@�@�@�@ ����
���܂����I�����͋��ʃw�b�_�t�@�C�����I
�I�����~�߂Ă��邤���ɑ��̃t�@�C���֓�����I
�����I�����I�I���ɍ\�킸������I 
*/

#pragma once

#include <DxLib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "main.h"
#include "sysmain.h"
#include "ui.h"
#include "text.h"
#include "data.h"

#include "stage1.h"

//�e�N���X
typedef struct{
	float x;
	float y;
	bool avail;
}bullet_t;

//���N���X
typedef struct{
	int now;
	int max;
}life_t;

//�l�p�`�N���X
typedef struct{
	int left;
	int top;
	int right;
	int bottom;
}square_t;

//���@�N���X
typedef struct{
	int x,y;
	int speed;
	life_t life;
	bool ahantei; //�����蔻��\���t���O
	bool damage; //�_���[�W�t���O
}jiki_t;

//�G�N���X
typedef struct{
	int x,y;
	life_t life;
	bool damage;
}teki_t;

