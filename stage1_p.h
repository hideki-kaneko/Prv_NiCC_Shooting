/*
stage1_p.h

�w�b�_�t�@�C�����ɃA���_�[�X�R�A�{P (Private)�����Ă�����̂́A�Ή��������O��cpp�t�@�C����������include����悤�Ɂi�v���O���}���Łj���܂��B
���Ƃ��΁A���̏ꍇ��stage1.cpp����stage1_p.h��ǂݍ��݂܂����A����cpp����͎Q�Ƃ���܂���B
�t�ɁAstage1.h��stage1.cpp����͓ǂݍ��܂ꂸ��common.h����include����܂��B

�ϐ����ނ�݂ɃO���[�o��������͖̂��Ȃ̂ŁA�Ƃ���cpp�ł����ϐ����g�p�������Ƃ��Ƀv���C�x�[�g�p�w�b�_���g���A������extern���Ďg���܂��B
�t�ɁAcpp�Œ�`�����֐������J�������ꍇ�� _p�����Ă��Ȃ��w�b�_��extern���Acommon.h�ɒǉ����Ďg���܂��B
*/

namespace chara{
	extern bullet_t tb[200]; /*�G�e*/
	extern bullet_t tmb[200]; /*�e�ړ�*/
	extern bullet_t jb[200]; /*���@�e*/
	extern bullet_t jmb[200];
	extern jiki_t jiki;
	extern teki_t boss[20];
}

namespace sys{
	extern square_t framesize;
}