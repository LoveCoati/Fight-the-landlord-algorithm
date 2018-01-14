#ifndef __DATA_STRUCT_H__
#define __DATA_STRUCT_H__

#include "config.h"

namespace zero {
	//��������
	//�������ö��  
	enum CardGroupType
	{
		cgERROR = -1,                                   //��������  
		cgZERO = 0,                                     //��������  
		cgSINGLE = 1,                                   //��������  
		cgDOUBLE = 2,                                   //��������  
		cgTHREE = 3,                                    //��������  
		cgSINGLE_LINE = 4,                              //��������  
		cgDOUBLE_LINE = 5,                              //��������  
		cgTHREE_LINE = 6,                               //��������  
		cgTHREE_TAKE_ONE = 7,                           //����һ��  
		cgTHREE_TAKE_TWO = 8,                           //����һ��  
		cgTHREE_TAKE_ONE_LINE = 9,                      //����һ����  
		cgTHREE_TAKE_TWO_LINE = 10,                     //����һ����  
		cgFOUR_TAKE_ONE = 11,                           //�Ĵ�����  
		cgFOUR_TAKE_TWO = 12,                           //�Ĵ�����  
		cgBOMB_CARD = 13,                               //ը������  
		cgKING_CARD = 14                                //��ը����  
	};
	
	//����Ȩֵ�ṹ  
	struct HandCardValue
	{
		int SumValue;        //�����ܼ�ֵ  
		int NeedRound;       // ��Ҫ������  
	};

	//����������ݽṹ  
	struct CardGroupData
	{
		//ö������  
		CardGroupType cgType = cgERROR;
		//���Ƶļ�ֵ  
		int  nValue = 0;
		//���Ƶĸ���  
		int  nCount = 0;
		//���о�����С����ֵ�����ڶԱ�  
		int nMaxCard = 0;

	};
#ifdef __DEBUG__

	//�·���������ҵ��������У�������ֻ���ڲ��ԣ���ΪAIʱ�����ȡ  
	struct ALLCardsList
	{
		vector <int>  arrCardsList[3];
	};

#endif
  
	

}
#endif


