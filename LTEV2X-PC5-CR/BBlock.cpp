#include "BBlock.h"

/*Ϊ�������������Ϣ��������ID,λ�úͿտ����Ӷ������н���λ��Ϊ��������λ��*/
void BBlock::blockInitial(int idTemp, Pos posTemp, Radio* radioTemp)
{
	id = idTemp;
	pos.x = posTemp.x;
	pos.y = posTemp.y;
	radio = radioTemp;
}