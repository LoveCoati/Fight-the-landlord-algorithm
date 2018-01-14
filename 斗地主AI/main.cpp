#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Array.hpp"
#include "config.h"


/*
��Ȼ�����ģ����Ϸ���̣����ȶ�����Ϸȫ���࣬��������ҵ�������Ϣ�ࡣ���÷��ƺ�����ɷ��ƻ��ڣ�������������Ϣ�������PrintAll�������Ҫ��������Ϣ��
*/
void process1() {
	GameSituation clsGameSituation;

	ALLCardsList  uctALLCardsList;

	//����  
	SendCards(clsGameSituation, uctALLCardsList);

	HandCardData arrHandCardData[3];

	arrHandCardData[0].color_nHandCardList = uctALLCardsList.arrCardsList[0];
	arrHandCardData[1].color_nHandCardList = uctALLCardsList.arrCardsList[1];
	arrHandCardData[2].color_nHandCardList = uctALLCardsList.arrCardsList[2];

	for (int i = 0; i < 3; i++)
	{
		arrHandCardData[i].Init();
		arrHandCardData[i].nOwnIndex = i;
	}

	cout << "0�������Ϊ��" << endl;
	arrHandCardData[0].PrintAll();
	cout << "1�������Ϊ��" << endl;
	arrHandCardData[1].PrintAll();
	cout << "2�������Ϊ��" << endl;
	arrHandCardData[2].PrintAll();

	cout << "����Ϊ��" << endl;
	cout << get_CardsName(clsGameSituation.DiPai[0]) << ','
		<< get_CardsName(clsGameSituation.DiPai[1]) << ','
		<< get_CardsName(clsGameSituation.DiPai[2]) << endl;

	cout << endl;
}
/*
�����ƺ�ʼ�е���������LandScore����������еķ�ֵ��ֻ�бȵ�ǰ�ѽеķ�ֵ���߲ſ���ˢ�½е�����¼�������˽е������¿�һ�֣��������ŵ��Ƹ�������ͬʱˢ�µ������ƣ��ҽ��������óɽ�Ҫ���Ƶ����
*/
void process2() {
	for (int i = 0; i < 3; i++)
	{
		int  tmpLandScore = LandScore(clsGameSituation, arrHandCardData[i]);
		if (tmpLandScore > clsGameSituation.nNowLandScore)
		{
			clsGameSituation.nNowLandScore = tmpLandScore;
			clsGameSituation.nNowDiZhuID = i;
		}
	}

	if (clsGameSituation.nNowDiZhuID == -1)
	{
		cout << "���˽е���" << endl;
		return;
	}

	cout << clsGameSituation.nNowDiZhuID << "������ǵ������з�Ϊ��" << clsGameSituation.nNowLandScore << endl;
	clsGameSituation.nDiZhuID = clsGameSituation.nNowDiZhuID;
	clsGameSituation.nLandScore = clsGameSituation.nNowLandScore;


	//�����ŵ��Ƹ�����  
	arrHandCardData[clsGameSituation.nDiZhuID].color_nHandCardList.push_back(clsGameSituation.DiPai[0]);
	arrHandCardData[clsGameSituation.nDiZhuID].color_nHandCardList.push_back(clsGameSituation.DiPai[1]);
	arrHandCardData[clsGameSituation.nDiZhuID].color_nHandCardList.push_back(clsGameSituation.DiPai[2]);

	//��������ˢ��  
	arrHandCardData[clsGameSituation.nDiZhuID].Init();

	//�������ID  
	int indexID = clsGameSituation.nDiZhuID;

	cout << endl;


	cout << "0�������Ϊ��" << endl;
	arrHandCardData[0].PrintAll();
	cout << "1�������Ϊ��" << endl;
	arrHandCardData[1].PrintAll();
	cout << "2�������Ϊ��" << endl;
	arrHandCardData[2].PrintAll();
	//��ǰ���������Ϊ����  
	clsGameSituation.nCardDroit = indexID;
}


/*
����������ѭ�����г����ˡ�����Ϸȫ����������������һ����־�Ƿ�����ı������������ڿ���ѭ��������ʱ����ֻ�����get_PutCardList���ƺ������ɡ���ĳ����ҳ����ƺ�����Ϊ0������Ϸ����������ҳ����ƣ���ˢ����Ϸȫ�������浱ǰ������Ϣ��
*/
void process3() {

	while (!clsGameSituation.Over)
	{
		get_PutCardList_2(clsGameSituation, arrHandCardData[indexID]);//��ȡ��������  
		arrHandCardData[indexID].PutCards();
		cout << indexID << "����ҳ��ƣ�" << endl;
		for (vector<int>::iterator iter = arrHandCardData[indexID].color_nPutCardList.begin();
			iter != arrHandCardData[indexID].color_nPutCardList.end(); iter++)
			cout << get_CardsName(*iter) << (iter == arrHandCardData[indexID].color_nPutCardList.end() - 1 ? '\n' : ',');
		cout << endl;

		if (arrHandCardData[indexID].nHandCardCount == 0)
		{
			clsGameSituation.Over = true;

			if (indexID == clsGameSituation.nDiZhuID)
			{
				cout << "����" << indexID << "����һ�ʤ" << endl;
			}
			else
			{
				for (int i = 0; i < 3; i++) {
					if (i != clsGameSituation.nDiZhuID)
					{
						cout << "ũ��" << i << "����һ�ʤ" << endl;
					}
				}
			}

		}

		if (arrHandCardData[indexID].uctPutCardType.cgType != cgZERO)
		{
			clsGameSituation.nCardDroit = indexID;
			clsGameSituation.uctNowCardGroup = arrHandCardData[indexID].uctPutCardType;
		}

		indexID == 2 ? indexID = 0 : indexID++;

	}
}



int main() {
	



	 getchar();
	 return 0;
}