#ifndef __GAME_SITUATION_H__
#define __GAME_SITUATION_H__

#include "DataStruct.h"
#include "Array.hpp"

//�������  
#define HandCardMaxLen 20  
//��ֵ��Сֵ  
#define MinCardsValue -25  
//��ֵ���ֵ  
#define MaxCardsValue 106  

namespace zero {

	//��Ϸȫ����  
	class GameSituation
	{
	public:

		//���캯��  
		GameSituation();
		
		//��������  
		virtual ~GameSituation();


	public:
		//��ʼ��
		void init();

		//�������  
		int nDiZhuID ;
		//���ֽз�  
		int nLandScore;

		//��ǰ������ҡ�����δȷ��  
		int nNowDiZhuID;
		//��ǰ���ֽз֡�����δȷ��  
		int nNowLandScore;

 
		//���ŵ��� int DiPai[3]; ������ũ���������
		zero::Array<int> DiPai;

		//�Ѿ�������ơ���״̬��¼������һЩ���㣬ֵ��Ϊ��index�ƶ�Ӧ������0~4   int value_aAllOutCardList[18] = { 0 };
		zero::Array<int> value_aAllOutCardList;
 
		//��������Ѿ���������Ƽ�¼  int value_aUnitOutCardList[3][18] = { 0 };
		zero::MostArray<int> value_aUnitOutCardList;

		//��������Ѿ�ʣ�����Ƹ���  int value_aUnitHandCardCount[3] = { 0 };
		zero::Array<int> value_aUnitHandCardCount;


		//���ֵ�ǰ�׷ֱ���  
		int nMultiple = 0;
		//��ǰ���ֶ������������Ƿ����������������Լ��Ƿ�����Ѿ��������ƴӶ���ȥ�ܶ��ѣ�  
		int nCardDroit = 0;
		//��ǰ����Ƶ��������ݣ���������ʱ��Ҹ�����������ɸѡ  
		CardGroupData uctNowCardGroup;

		//������Ϸ�Ƿ����  
		bool Over;
	};
}


#endif
