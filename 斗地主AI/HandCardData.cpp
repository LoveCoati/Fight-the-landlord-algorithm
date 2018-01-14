#include "HandCardData.h"
#include<algorithm>

zero::HandCardData::HandCardData():nHandCardCount(17), nGameRole(-1), nOwnIndex(-1)
{
	value_aHandCardList.setDimension(18).InitValue(0);
}

zero::HandCardData::~HandCardData()
{
}

void zero::HandCardData::ClearPutCardList()
{
	//��ճ��ƶ���
	color_nPutCardList.clear();		//Ҫ���ȥ���ơ����л�ɫ ���ƶ���
	value_nPutCardList.clear();		//Ҫ���ȥ���ơ����޻�ɫ ���ƶ���

	//��ʼ�����ݽṹ
	uctPutCardType.cgType = cgERROR;	//��ö������  
	uctPutCardType.nCount = 0;			//���Ƶĸ���  
	uctPutCardType.nMaxCard = -1;		//���о�����С����ֵ�����ڶԱ� 
	uctPutCardType.nValue = 0;			//���Ƶļ�ֵ

	return;
}

/*��������Ա�*/
int cmp(int a, int b) { return a > b ? 1 : 0; }


void zero::HandCardData::SortAsList(std::vector <int> & arr)
{
	std::sort(arr.begin(), arr.end(), cmp);
	return;
}

void zero::HandCardData::get_valueHandCardList()
{
 
	value_nHandCardList.clear(); //�������С����޻�ɫ ���

	//��ʼ�� value_aHandCardList ����
	memset(value_aHandCardList.GetPointer(), 0, value_aHandCardList.GetBytesSize());

	//���� �������С����л�ɫ
	for (std::vector<int>::iterator iter = color_nHandCardList.begin(); iter != color_nHandCardList.end(); iter++)
	{
		auto index = (*iter / 4) + 3;
		value_nHandCardList.push_back(index);
		value_aHandCardList[index]++;
	}


}

void zero::HandCardData::Init()
{
	//���ݻ�ɫ���ƻ�ȡȨֵ����  
	get_valueHandCardList();

	//���� ����  
	SortAsList(color_nHandCardList);
	SortAsList(value_nHandCardList);

	//��ǰ���Ƹ���  
	nHandCardCount = value_nHandCardList.size();

}


#ifdef  __DEBUG__
/*
char* get_CardsName(int type) {
	//����ÿ���Ƶ�����
	return "assa  ";
}*/

void zero::HandCardData::PrintAll()
{


	std::cout << "color_nHandCardList:" << std::endl;

	for (std::vector<int>::iterator iter = color_nHandCardList.begin(); iter != color_nHandCardList.end(); iter++)
		std::cout << /*get_CardsName(*iter)*/" " << (iter == color_nHandCardList.end() - 1 ? '\n' : ',');

	std::cout << std::endl;


	std::cout << "value_nHandCardList��" << std::endl;
	for (std::vector<int>::iterator iter = value_nHandCardList.begin(); iter != value_nHandCardList.end(); iter++)
		std::cout << *iter << (iter == value_nHandCardList.end() - 1 ? '\n' : ',');

	std::cout << std::endl;

	std::cout << "value_aHandCardList��" << std::endl;
	for (int i = 0; i < 18; i++)
	{
		std::cout << value_aHandCardList[i] << (i == 17 ? '\n' : ',');
	}

	std::cout << std::endl;


	std::cout << "nHandCardCount:" << nHandCardCount << std::endl;

	std::cout << std::endl;

	std::cout << "nGameRole:" << nGameRole << std::endl;

	std::cout << std::endl;
}

#endif



bool  zero::HandCardData::PutCards()
{
	// value_nPutCardList   ����   ---���ݽṹ0:�� 1:�� 2:�� 3:A(���顢�ݻ� �����ġ����� �ϲ�) 4:1(���顢�ݻ� �����ġ����Һϲ�)  ......
	for (std::vector<int>::iterator iter = value_nPutCardList.begin(); iter != value_nPutCardList.end(); iter++)
	{
		int color_nCard = -1;
		if (PutOneCard(*iter, color_nCard))
		{
			//�ɳ��� ����
			color_nPutCardList.push_back(color_nCard);
		}
		else
		{
			return false;
		}
	}

	nHandCardCount -= value_nPutCardList.size();
	return true;
}

bool  zero::HandCardData::PutOneCard(int value_nCard, int &color_nCard)
{
	bool ret = false;

	//value״̬���鴦��  
	//ȥ��һ����
	value_aHandCardList[value_nCard]= value_aHandCardList[value_nCard]-1;

	//����Ƿ� ʣ�������Ƿ� >= 0
	if (value_aHandCardList[value_nCard] < 0)
	{
		//û�д����� ֱ�ӷ���false
		return false;
	}

	//value_nHandCardList�б����鴦��  
	for (std::vector<int>::iterator iter = value_nHandCardList.begin(); iter != value_nHandCardList.end(); iter++)
	{
		if (*iter == value_nCard)
		{
			value_nHandCardList.erase(iter);
			ret = true;
			break;
		}
	}


	// color�б����鴦��  
	int k = (value_nCard - 3) * 4;      //��ֵת��  

	//ɾ���л�ɫ �б��е�������
	for (std::vector<int>::iterator iter = color_nHandCardList.begin(); iter != color_nHandCardList.end(); iter++)
	{

		for (int i = k; i < k + 4; i++)
		{
			if (*iter == i)
			{
				color_nCard = i;
				color_nHandCardList.erase(iter);
				return ret;

			}
		}
	}
	return false;
}