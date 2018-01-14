#include "GameSituation.h"

zero::GameSituation::GameSituation()
{
	this->init();
}

zero::GameSituation::~GameSituation()
{
}

void zero::GameSituation::init()
{
	nDiZhuID = -1;
	nLandScore = 0;
	nNowDiZhuID = -1;
	nNowLandScore = 0;

	this->DiPai.setDimension(3);
	this->DiPai.InitValue(0);
	this->value_aAllOutCardList.setDimension(18);
	this->value_aAllOutCardList.InitValue(0);
	this->value_aUnitOutCardList.setDimension(3, 18);
	this->value_aUnitOutCardList.InitValue(0);
	this->value_aUnitHandCardCount.setDimension(3);
	this->value_aUnitHandCardCount.InitValue(0);

	//���ֵ�ǰ�׷ֱ���  
	nMultiple = 0;
	//��ǰ���ֶ������������Ƿ����������������Լ��Ƿ�����Ѿ��������ƴӶ���ȥ�ܶ��ѣ�  
	nCardDroit = 0;

	//������Ϸ�Ƿ����  
	Over = false;
}
