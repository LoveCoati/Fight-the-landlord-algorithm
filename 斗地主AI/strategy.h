

#ifndef __STRATEGY_H__
#define __STRATEGY_H__


#include <vector>
#include "HandCardData.h"


/*�����߼�˼ά��

0.�����²������������ִβ��������Բ��ٿ��ǲ�ּ�ֵ��
1.����������ֵ��������Ϊ10�����е�λ�ã���<10���Ƽ�ֵΪ��������10�ĵ��Ƽ�ֵΪ��
2.���ֵļ�ֵ���壺������Ϊһ�ο���Ȩ���Ե���һ��������С���ͣ���С���ͣ�3���ļ�ֵΪ-7�������Ƕ���һ�ο���Ȩ�ļ�ֵΪ7
3.���Ƶļ�ֵ���壺���ƵĻ�����ֵ
4.���Ƶļ�ֵ���壺������Ϊ�����뵥�Ƽ�ֵ��ȣ������Ա����ƴ����������ֵΪ���ƵĻ�����ֵ
5.���Ƶļ�ֵ���壺
��������     ���ƵĻ�����ֵ
����һ��     ������Ϊͨ������ȥ���Ƽ�ֵһ��������ֵ�����ֵΪ���ƵĻ�����ֵ
��������     ������Ϊͨ������ȥ���Ƽ�ֵһ��������ֵ�����ֵΪ���ƵĻ�����ֵ
6.���Ƶļ�ֵ���壺
ը����       ������Ϊը��������һ�ο���Ȩ����ը�����ܵĸ��ʼ�С�������޸���ֵ���Ǹ�������ֵ+7
�Ĵ�������   ������Ϊ�Ĵ����������뱻�ܵĸ��ʼ�С�������޸���ֵ�����ֵΪ�Ǹ�������ֵ/2����ֵ���Ϊ6С��һ���ִ�7)
�Ĵ����ԣ�   ������Ϊ�Ĵ����Թ����뱻�ܵĸ��ʼ�С�������޸���ֵ�����ֵΪ�Ǹ�������ֵ/2����ֵ���Ϊ6С��һ���ִ�7)
7.��ը�ļ�ֵ���壺��֪ը2��ֵΪ15-3+7=19�֣�����ը��ֵΪ20�֡�
8.˳�ӵļ�ֵ���壺
��˳��       ������Ϊ��˳�ļ�ֵ����������Ƶĵ����ֵ����2������˳�ӣ���˳�ӵ�Ȩֵ��������1
˫˳��       ������Ϊ˫˳�ļ�ֵ����������Ƶĵ����ֵ����2������˳�ӣ���˳�ӵ�Ȩֵ��������1
�ɻ�������   ���ڷɻ����͹����뱻�ܵĸ��ʼ�С�������޸���ֵ�����ֵΪ�Ǹ�������ֵ/2����ֵ���Ϊ6С��һ���ִ�7)
�ɻ���˫�᣺ ���ڷɻ����͹����뱻�ܵĸ��ʼ�С�������޸���ֵ�����ֵΪ�Ǹ�������ֵ/2����ֵ���Ϊ6С��һ���ִ�7)
�ɻ������᣺ ���ڷɻ����͹����뱻�ܵĸ��ʼ�С�������޸���ֵ�����ֵΪ�Ǹ�������ֵ/2����ֵ���Ϊ6С��һ���ִ�7)
9.������ֵ�ֲ��������ݶ���   <10���з֣�10-14��һ�֣�15-19�����֣�20���Ͻ�����

PS.�����߼�����������˭��˭SB����������
*/

namespace zero {

	/*
	��װ�õĻ�ȡ����������Ͻṹ����
	@prarm  {CardGroupType}	cgType������
	@prarm  {int}			MaxCard��������С����ֵ
	@prarm  {int}			Count������
	@return {CardGroupData} ����������ݽṹ 
	*/
	CardGroupData get_GroupData(CardGroupType cgType, int MaxCard, int Count);


	/*
	ͨ������dp�ķ�ʽ��ȡ���Ƽ�ֵ
	��get_PutCardList��Ϊ����ݹ����
	���أ���ֵ�ṹ��HandCardValue
	Ȩֵ�ļ������ο�ͷ�ļ������߼�˼ά
	*/
	HandCardValue get_HandCardValue(HandCardData &clsHandCardData);

	/* 
	���ʣ������Ƿ�ֻ��һ���� 
 
	�ǣ�  ���������������� 
	���ǣ����ش������ͣ�cgERROR�� 
	*/  
	CardGroupData ins_SurCardsType(int arr[]);  

	/*
	���ʣ������Ƿ�ֻ��һ���ƣ�vector���أ�

	�ǣ�  ����������������
	���ǣ����ش������ͣ�cgERROR��
	*/
	CardGroupData ins_SurCardsType(std::vector<int>list);


	/*
	2.0�汾����  ���ݳ������ƾ�����ǰԤ��������ơ�����������
	*/
	void get_PutCardList_2_limit(GameSituation &clsGameSituation, HandCardData &clsHandCardData);

	/*��װ�õ�  �����е��ƶ����*/
	void Put_All_SurCards(GameSituation &clsGameSituation, HandCardData &clsHandCardData, CardGroupData SurCardGroupData);
	

	void Put_All_SurCards(HandCardData &clsHandCardData, CardGroupData SurCardGroupData);
	
	void get_PutCardList_2(HandCardData &clsHandCardData);


	/*
	��ȡ�зֺ���
	*/
	int LandScore(GameSituation &clsGameSituation, HandCardData &clsHandCardData);


	//ϴ��  
	void InitCards(std::vector <int> &Cards);
	
	//ϴ�ƣ�ָ�����ͣ����ڲ��ԣ�  
	void InitCards_Appoint(std::vector <int> &Cards);


	//����  
	void SendCards(GameSituation & clsGameSituation, ALLCardsList &uctALLCardsList);
	
	
}




#endif

