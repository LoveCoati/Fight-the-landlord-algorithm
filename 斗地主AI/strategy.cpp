#include "strategy.h"

using std::vector;
using std::cout;
using std::endl;


/*
	��װ�õĻ�ȡ����������Ͻṹ����
	@prarm  {CardGroupType}	cgType������
	@prarm  {int}			MaxCard��������С����ֵ������ֵ��
	@prarm  {int}			Count������
	@return {CardGroupData} ����������ݽṹ
*/
zero::CardGroupData zero::get_GroupData(zero::CardGroupType cgType, int MaxCard, int Count)
{
	//����������ݽṹ ����
	CardGroupData uctCardGroupData;

	uctCardGroupData.cgType = cgType;		//����
	uctCardGroupData.nCount = Count;		//������С����ֵ����
	uctCardGroupData.nMaxCard = MaxCard;	//������С����ֵ

	//nValue �������Ƽ�ֵ

	//��������  
	if (cgType == cgZERO)
		uctCardGroupData.nValue = 0;
	//��������  
	else if (cgType == cgSINGLE)
		uctCardGroupData.nValue = MaxCard - 10;
	//��������  
	else if (cgType == cgDOUBLE)
		uctCardGroupData.nValue = MaxCard - 10;
	//��������  
	else if (cgType == cgTHREE)
		uctCardGroupData.nValue = MaxCard - 10;
	//��������  
	else if (cgType == cgSINGLE_LINE)
		uctCardGroupData.nValue = MaxCard - 10 + 1;
	//��������  
	else if (cgType == cgDOUBLE_LINE)
		uctCardGroupData.nValue = MaxCard - 10 + 1;
	//��������  
	else if (cgType == cgTHREE_LINE)
		uctCardGroupData.nValue = (MaxCard - 3 + 1) / 2;
	//����һ��  
	else if (cgType == cgTHREE_TAKE_ONE)
		uctCardGroupData.nValue = MaxCard - 10;
	//����һ��  
	else if (cgType == cgTHREE_TAKE_TWO)
		uctCardGroupData.nValue = MaxCard - 10;
	//����һ����  
	else if (cgType == cgTHREE_TAKE_ONE_LINE)
		uctCardGroupData.nValue = (MaxCard - 3 + 1) / 2;
	//����һ����  
	else if (cgType == cgTHREE_TAKE_TWO_LINE)
		uctCardGroupData.nValue = (MaxCard - 3 + 1) / 2;
	//�Ĵ�����  
	else if (cgType == cgFOUR_TAKE_ONE)
		uctCardGroupData.nValue = (MaxCard - 3) / 2;
	//�Ĵ�����  
	else if (cgType == cgFOUR_TAKE_TWO)
		uctCardGroupData.nValue = (MaxCard - 3) / 2;
	//ը������   
	else if (cgType == cgBOMB_CARD)
		uctCardGroupData.nValue = MaxCard - 3 + 7;
	//��ը����   
	else if (cgType == cgKING_CARD)
		uctCardGroupData.nValue = 20;
	//��������  
	else
		uctCardGroupData.nValue = 0;


	return uctCardGroupData;
}

zero::HandCardValue zero::get_HandCardValue(HandCardData & clsHandCardData)
{
	//������ճ��ƶ��У���Ϊ��֦ʱ�ǲ�����get_PutCardList��  
	clsHandCardData.ClearPutCardList();

	HandCardValue uctHandCardValue;
	//�������ˣ���ʵ�������ֻ��������ʣ���Ĵ����ұ������Ƶ��������Ϊ�Ĵ�����֦�������⴦��  
	if (clsHandCardData.nHandCardCount == 0)
	{
		uctHandCardValue.SumValue = 0;
		uctHandCardValue.NeedRound = 0;
		return uctHandCardValue;
	}
	//������������Ϊ��֦���ж��Ƿ����һ�ֳ�����  
	CardGroupData uctCardGroupData = ins_SurCardsType(clsHandCardData.value_aHandCardList);
	//�������������򲻵������Ƕ�������Ĵ�������������ը��  
	if (uctCardGroupData.cgType != cgERROR && uctCardGroupData.cgType != cgFOUR_TAKE_ONE && uctCardGroupData.cgType != cgFOUR_TAKE_TWO)
	{
		uctHandCardValue.SumValue = uctCardGroupData.nValue;
		uctHandCardValue.NeedRound = 1;
		return uctHandCardValue;
	}

	//�Ǽ�֦����������һ���ܳ������  

	/*ֻ�ǻ�ȡ���Ƶ����У���clsHandCardData.value_nPutCardList��clsHandCardData.uctPutCardType
	������Ա���޸ı䣬Ҳ������ó��ƺ�����get_PutCardList�������ŷ���*/
	get_PutCardList_2(clsHandCardData);

	//Ҫ���浱ǰ��clsHandCardData.value_nPutCardList��clsHandCardData.uctPutCardType���ڻ���  
	CardGroupData NowPutCardType = clsHandCardData.uctPutCardType;
	vector<int> NowPutCardList = clsHandCardData.value_nPutCardList;

	if (clsHandCardData.uctPutCardType.cgType == cgERROR)
	{
		cout << "PutCardType ERROR!" << endl;
	}



	//---���ݡ�  
	for (vector<int>::iterator iter = NowPutCardList.begin();
		iter != NowPutCardList.end(); iter++)
	{
		clsHandCardData.value_aHandCardList[*iter]--;
	}
	clsHandCardData.nHandCardCount -= NowPutCardType.nCount;
	//---���ݡ�  
	HandCardValue tmp_SurValue = get_HandCardValue(clsHandCardData);//�ݹ�ʣ���Ƽ�ֵ  

																	//---���ݡ�      
	for (vector<int>::iterator iter = NowPutCardList.begin();
		iter != NowPutCardList.end(); iter++)
	{
		clsHandCardData.value_aHandCardList[*iter]++;
	}
	clsHandCardData.nHandCardCount += NowPutCardType.nCount;
	//---���ݡ�  

	uctHandCardValue.SumValue = NowPutCardType.nValue + tmp_SurValue.SumValue;
	uctHandCardValue.NeedRound = tmp_SurValue.NeedRound + 1;





	return uctHandCardValue;
}

zero::CardGroupData zero::ins_SurCardsType(int arr[])
{
	int nCount = 0;
	for (int i = 3; i < 18; i++)
	{
		nCount += arr[i];
	}

	CardGroupData retCardGroupData;
	retCardGroupData.nCount = nCount;


	//��������  
	if (nCount == 1)
	{
		//������֤�ı���  
		int prov = 0;
		int SumValue = 0;
		for (int i = 3; i < 18; i++)
		{
			if (arr[i] == 1)
			{
				SumValue = i - 10;
				prov++;
				retCardGroupData.nMaxCard = i;
			}
		}
		if (prov == 1)
		{
			retCardGroupData.cgType = cgSINGLE;
			retCardGroupData.nValue = SumValue;
			return retCardGroupData;
		}
	}
	//��������  
	if (nCount == 2)
	{
		//������֤�ı���  
		int prov = 0;
		int SumValue = 0;
		int i = 0;
		for (i = 3; i < 16; i++)
		{
			if (arr[i] == 2)
			{
				SumValue = i - 10;
				prov++;
				retCardGroupData.nMaxCard = i;
			}
		}
		if (prov == 1)
		{
			retCardGroupData.cgType = cgDOUBLE;
			retCardGroupData.nValue = SumValue;
			return retCardGroupData;
		}
	}
	//��������  
	if (nCount == 3)
	{
		//������֤�ı���  
		int prov = 0;
		int SumValue = 0;
		int i = 0;
		for (i = 3; i < 16; i++)
		{
			if (arr[i] == 3)
			{
				SumValue = i - 10;
				prov++;
				retCardGroupData.nMaxCard = i;
			}
		}
		if (prov == 1)
		{
			retCardGroupData.cgType = cgTHREE;
			retCardGroupData.nValue = SumValue;
			return retCardGroupData;
		}
	}
	//����һ��  
	if (nCount == 4)
	{
		//������֤�ı���  
		int prov1 = 0;
		int prov2 = 0;
		int SumValue = 0;
		for (int i = 3; i < 18; i++)
		{
			if (arr[i] == 3)
			{
				SumValue = i - 10;
				prov1++;
				retCardGroupData.nMaxCard = i;

			}
			if (arr[i] == 1)
			{
				prov2++;
			}

		}
		if (prov1 == 1 && prov2 == 1)
		{
			retCardGroupData.cgType = cgTHREE_TAKE_ONE;
			retCardGroupData.nValue = SumValue;
			return retCardGroupData;
		}
	}
	//����һ��  
	if (nCount == 5)
	{
		//������֤�ı���  
		int prov1 = 0;
		int prov2 = 0;
		int SumValue = 0;
		for (int i = 3; i < 16; i++)
		{
			if (arr[i] == 3)
			{
				SumValue = i - 10;
				prov1++;
				retCardGroupData.nMaxCard = i;

			}
			if (arr[i] == 2)
			{
				prov2++;

			}
		}
		if (prov1 == 1 && prov2 == 1)
		{
			retCardGroupData.cgType = cgTHREE_TAKE_TWO;
			retCardGroupData.nValue = SumValue;
			return retCardGroupData;
		}
	}
	//�Ĵ�����  
	if (nCount == 6)
	{
		//������֤�ı���  
		int prov1 = 0;
		int prov2 = 0;
		int SumValue = 0;
		for (int i = 3; i < 18; i++)
		{
			if (arr[i] == 4)
			{
				SumValue = (i - 3) / 2;
				prov1++;
				retCardGroupData.nMaxCard = i;

			}
			if (arr[i] == 1 || arr[i] == 2)
			{
				prov2 += arr[i];
			}
		}

		if (prov1 == 1 && prov2 == 2)
		{
			retCardGroupData.cgType = cgFOUR_TAKE_ONE;
			retCardGroupData.nValue = SumValue;
			return retCardGroupData;
		}
	}
	//�Ĵ�����  
	if (nCount == 8)
	{
		//������֤�ı���  
		int prov1 = 0;
		int prov2 = 0;
		int SumValue = 0;
		for (int i = 3; i < 16; i++)
		{
			if (arr[i] == 4)
			{
				SumValue = (i - 3) / 2;

				prov1++;
				retCardGroupData.nMaxCard = i;
			}
			if (arr[i] == 2 || arr[i] == 4)
			{
				prov2 += arr[i] / 2;

			}
		}
		//ע������prov2==4��Ϊ����Ҳ��������  
		if (prov1 == 1 && prov2 == 4)
		{
			retCardGroupData.cgType = cgFOUR_TAKE_TWO;
			retCardGroupData.nValue = SumValue;
			return retCardGroupData;
		}
	}
	//ը������  
	if (nCount == 4)
	{
		//������֤�ı���  
		int prov = 0;
		int SumValue = 0;
		for (int i = 3; i < 16; i++)
		{
			if (arr[i] == 4)
			{
				SumValue += i - 3 + 7;
				prov++;
				retCardGroupData.nMaxCard = i;
			}
		}
		if (prov == 1)
		{
			retCardGroupData.cgType = cgBOMB_CARD;
			retCardGroupData.nValue = SumValue;
			return retCardGroupData;
		}
	}
	//��ը����  
	if (nCount == 2)
	{
		int SumValue = 0;
		if (arr[17] > 0 && arr[16] > 0)
		{
			SumValue = 20;
			retCardGroupData.nMaxCard = 17;
			retCardGroupData.cgType = cgKING_CARD;
			retCardGroupData.nValue = SumValue;
			return retCardGroupData;
		}
	}
	//��������  
	if (nCount >= 5)
	{
		//������֤�ı���  
		int prov = 0;
		int SumValue = 0;
		int i;
		for (i = 3; i < 15; i++)
		{
			if (arr[i] == 1)
			{
				prov++;
			}
			else
			{
				if (prov != 0)
				{
					break;
				}

			}
		}
		SumValue = i - 10;

		if (prov == nCount)
		{
			retCardGroupData.nMaxCard = i - 1;
			retCardGroupData.cgType = cgSINGLE_LINE;
			retCardGroupData.nValue = SumValue;
			return retCardGroupData;
		}
	}
	//��������  
	if (nCount >= 6)
	{
		//������֤�ı���  
		int prov = 0;
		int SumValue = 0;
		int i;
		for (i = 3; i < 15; i++)
		{
			if (arr[i] == 2)
			{
				prov++;
			}
			else
			{
				if (prov != 0)
				{
					break;
				}

			}
		}
		SumValue = i - 10;

		if (prov * 2 == nCount)
		{
			retCardGroupData.nMaxCard = i - 1;
			retCardGroupData.cgType = cgDOUBLE_LINE;
			retCardGroupData.nValue = SumValue;
			return retCardGroupData;
		}
	}
	//��������  
	if (nCount >= 6)
	{
		//������֤�ı���  
		int prov = 0;

		int SumValue = 0;
		int i;
		for (i = 3; i < 15; i++)
		{
			if (arr[i] == 3)
			{
				prov++;
			}
			else
			{
				if (prov != 0)
				{
					break;
				}

			}
		}
		SumValue = (i - 3) / 2;

		if (prov * 3 == nCount)
		{
			retCardGroupData.nMaxCard = i - 1;
			retCardGroupData.cgType = cgTHREE_LINE;
			retCardGroupData.nValue = SumValue;
			return retCardGroupData;
		}
	}
	//����һ������  
	if (nCount >= 8)
	{
		//������֤�ı���  
		int prov1 = 0;
		int SumValue = 0;
		int i, j;
		for (i = 3; i < 15; i++)
		{
			if (arr[i] >= 3)
			{
				prov1++;
			}
			else
			{
				if (prov1 != 0)
				{
					break;
				}

			}
		}
		SumValue = (i - 3) / 2;
		if (prov1 * 4 == nCount)
		{
			retCardGroupData.nMaxCard = i - 1;
			retCardGroupData.cgType = cgTHREE_TAKE_ONE_LINE;
			retCardGroupData.nValue = SumValue;
			return retCardGroupData;
		}

	}
	//������������  
	if (nCount >= 10)
	{
		//������֤�ı���  
		int prov1 = 0;
		int prov2 = 0;
		int SumValue = 0;
		int i, j;
		for (i = 3; i < 15; i++)
		{
			if (arr[i] == 3)
			{
				prov1++;
			}
			else
			{
				if (prov1 != 0)
				{
					break;
				}
			}
		}
		for (j = 3; j < 16; j++)
		{
			if (arr[j] == 2 || arr[j] == 4)
			{
				prov2 += arr[j] / 2;
			}
		}
		SumValue = (i - 3) / 2;
		if (prov1 == prov2 && prov1 * 5 == nCount)
		{
			retCardGroupData.nMaxCard = i - 1;
			retCardGroupData.cgType = cgTHREE_TAKE_TWO_LINE;
			retCardGroupData.nValue = SumValue;
			return retCardGroupData;
		}
	}

	retCardGroupData.cgType = cgERROR;
	return retCardGroupData;
}

zero::CardGroupData zero::ins_SurCardsType(std::vector<int> list)
{
	int arr[18];
	memset(arr, 0, sizeof(arr));
	for (vector<int>::iterator iter = list.begin(); iter != list.end(); iter++)
	{
		arr[*iter]++;
	}
	return ins_SurCardsType(arr);
}

void zero::get_PutCardList_2_limit(GameSituation & clsGameSituation, HandCardData & clsHandCardData)
{
	clsHandCardData.ClearPutCardList();


	/*��ը������ǰ����ֻ������ը��Ϊ�����ڶ��ֵ����ȳ����߼��������汾���ڴ˻������Ż�*/
	if (clsHandCardData.value_aHandCardList[17] > 0 && clsHandCardData.value_aHandCardList[16] > 0)
	{

		clsHandCardData.value_aHandCardList[17] --;
		clsHandCardData.value_aHandCardList[16] --;
		clsHandCardData.nHandCardCount -= 2;
		HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
		clsHandCardData.value_aHandCardList[16] ++;
		clsHandCardData.value_aHandCardList[17] ++;
		clsHandCardData.nHandCardCount += 2;
		if (tmpHandCardValue.NeedRound == 1)
		{
			clsHandCardData.value_nPutCardList.push_back(17);
			clsHandCardData.value_nPutCardList.push_back(16);
			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgKING_CARD, 17, 2);
			return;
		}
	}


	//��������  ����  
	if (clsGameSituation.uctNowCardGroup.cgType == cgERROR)
	{
		clsHandCardData.uctPutCardType = get_GroupData(cgERROR, 0, 0);
		return;
	}
	//�������ͣ��ڱ������Ʋ�����Ҳ�Ǵ������� ����  
	else if (clsGameSituation.uctNowCardGroup.cgType == cgZERO)
	{
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//��������  
	else if (clsGameSituation.uctNowCardGroup.cgType == cgSINGLE)
	{
		//�ܲ���  
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;

	}
	//��������  
	else if (clsGameSituation.uctNowCardGroup.cgType == cgDOUBLE)
	{
		//�ܲ���  
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//��������  
	else if (clsGameSituation.uctNowCardGroup.cgType == cgTHREE)
	{

		//�ܲ���  
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//��������  
	else if (clsGameSituation.uctNowCardGroup.cgType == cgSINGLE_LINE)
	{
		//�ܲ���  
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//��������  
	else if (clsGameSituation.uctNowCardGroup.cgType == cgDOUBLE_LINE)
	{
		//�ܲ���  
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;

	}
	//��������  
	else if (clsGameSituation.uctNowCardGroup.cgType == cgTHREE_LINE)
	{
		//�ܲ���  
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//����һ��  
	else if (clsGameSituation.uctNowCardGroup.cgType == cgTHREE_TAKE_ONE)
	{
		//�ܲ���  
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//����һ��  
	else if (clsGameSituation.uctNowCardGroup.cgType == cgTHREE_TAKE_TWO)
	{
		//�ܲ���  
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//����һ����  
	else if (clsGameSituation.uctNowCardGroup.cgType == cgTHREE_TAKE_ONE_LINE)
	{
		//�ܲ���  
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//����һ����  
	else if (clsGameSituation.uctNowCardGroup.cgType == cgTHREE_TAKE_TWO_LINE)
	{
		//�ܲ���  
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//�Ĵ�����  
	else if (clsGameSituation.uctNowCardGroup.cgType == cgFOUR_TAKE_ONE)
	{
		//�ܲ���  
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//�Ĵ�����  
	else if (clsGameSituation.uctNowCardGroup.cgType == cgFOUR_TAKE_TWO)
	{
		//�ܲ���  
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//ը������   
	else if (clsGameSituation.uctNowCardGroup.cgType == cgBOMB_CARD)
	{
		//�ܲ���  
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//��ը���� �˶���ը���㻹����ë  
	else if (clsGameSituation.uctNowCardGroup.cgType == cgKING_CARD)
	{
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//�쳣���� ����  
	else
	{
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
	}
	return;

}

void zero::Put_All_SurCards(GameSituation & clsGameSituation, HandCardData & clsHandCardData, CardGroupData SurCardGroupData)
{
	/*ȫ������*/
	for (int i = 0; i < 18; i++)
		for (int j = 0; j < clsHandCardData.value_aHandCardList[i]; j++)
			clsHandCardData.value_nPutCardList.push_back(i);
	/**********/
	clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = SurCardGroupData;
	return;
}

void zero::Put_All_SurCards(HandCardData & clsHandCardData, CardGroupData SurCardGroupData)
{
	/*ȫ������*/
	for (int i = 0; i < 18; i++)
		for (int j = 0; j < clsHandCardData.value_aHandCardList[i]; j++)
			clsHandCardData.value_nPutCardList.push_back(i);
	/**********/
	clsHandCardData.uctPutCardType = SurCardGroupData;
	return;
}

void zero::get_PutCardList_2(HandCardData & clsHandCardData)
{
	clsHandCardData.ClearPutCardList();

	//��֦������ܳ�ȥ���һ����ֱ�ӳ�  
	CardGroupData SurCardGroupData = ins_SurCardsType(clsHandCardData.value_aHandCardList);
	//�����һ���Գ�ȥ�Ҳ����Ĵ�������Ϊ��������������ʣ�Ĵ����ƵĻ����Կ����ȴ�һ��Ȼ��ը�����˫������  
	if (SurCardGroupData.cgType != cgERROR && SurCardGroupData.cgType != cgFOUR_TAKE_ONE && SurCardGroupData.cgType != cgFOUR_TAKE_TWO)
	{
	}

	/*��ը������ǰ����ֻ������ը��Ϊ�����ڶ��ֵ����ȳ����߼��������汾���ڴ˻������Ż�*/
	if (clsHandCardData.value_aHandCardList[17] > 0 && clsHandCardData.value_aHandCardList[16] > 0)
	{
	}

	//�ݴ���ѵļ�ֵ  
	HandCardValue BestHandCardValue;
	BestHandCardValue.NeedRound = 20;
	BestHandCardValue.SumValue = MinCardsValue;
	//������Ϊ�����ƵĻ����ö���һ���ִΣ�����һ�֣�Ȩֵ����7�����ں����ĶԱȲο���  
	BestHandCardValue.NeedRound += 1;

	//�ݴ���ѵ����  
	CardGroupData BestCardGroup;

	//����ȥ����  
	int tmp_1 = 0;
	int tmp_2 = 0;
	int tmp_3 = 0;
	int tmp_4 = 0;
	//���ȴ������ơ��ɻ�����  
	for (int i = 3; i < 16; i++)
	{
	}
	//�ⲿ�ֳ��ƴ���ŵ�ѭ����  
	if (BestCardGroup.cgType == cgTHREE_TAKE_ONE)
	{

	}
	else if (BestCardGroup.cgType == cgTHREE_TAKE_TWO)
	{

	}
	else if (BestCardGroup.cgType == cgTHREE_TAKE_ONE_LINE)
	{

	}
	else if (BestCardGroup.cgType == cgTHREE_TAKE_TWO_LINE)
	{

	}


	//��֮����ǰ��ֵ��͵��ƣ����ڲ����ٿ��������ƿ��ܱ����ƴ��������  
	for (int i = 3; i < 16; i++)
	{
	}
	//���û��3-2�ķ�ը�ƣ��򿴿���û�е���  
	if (clsHandCardData.value_aHandCardList[16] == 1 && clsHandCardData.value_aHandCardList[17] == 0)
	{
	}
	if (clsHandCardData.value_aHandCardList[16] == 0 && clsHandCardData.value_aHandCardList[17] == 1)
	{
	}
	//����Ҳû�У���ը��  
	for (int i = 3; i < 16; i++)
	{
	}

	//�쳣����  
	clsHandCardData.uctPutCardType = get_GroupData(cgERROR, 0, 0);
	return;
}

int zero::LandScore(GameSituation & clsGameSituation, HandCardData & clsHandCardData)
{
	int SumValue = 0;

	clsHandCardData.uctHandCardValue = get_HandCardValue(clsHandCardData);

	SumValue = clsHandCardData.uctHandCardValue.SumValue;

	cout << "SumValue is :" << SumValue << ",";

	cout << "NeedRound is :" << clsHandCardData.uctHandCardValue.NeedRound << endl;

	if (SumValue < 10)
	{
		return 0;
	}
	else if (SumValue < 15)
	{
		return 1;
	}
	else if (SumValue < 20)
	{
		return 2;
	}
	else
	{
		return 3;
	}
}

void zero::InitCards(std::vector<int>& Cards)
{
	//�����Cards  
	Cards.clear();

	vector <int> tmpCards;
	int i;

	//����56��С��52��û��53��54��55����  
	for (i = 0; i < 53; i++) {
		tmpCards.push_back(i);
	}
	tmpCards.push_back(56);


	//˳���������  
	for (i = tmpCards.size(); i > 0; i--) {
		srand(unsigned(time(NULL)));
		// ѡ�е�����±�  
		int index = rand() % i;
		Cards.push_back(tmpCards[index]);
		tmpCards.erase(tmpCards.begin() + index);
	}

}

void zero::InitCards_Appoint(std::vector<int>& Cards)
{
	//�����Cards  
	Cards.clear();

	/***********�ɻ���ը����������߼�����**********/

	Cards.push_back(48); Cards.push_back(50); Cards.push_back(49);
	Cards.push_back(44); Cards.push_back(47); Cards.push_back(35);
	Cards.push_back(40); Cards.push_back(46); Cards.push_back(34);
	Cards.push_back(36); Cards.push_back(45); Cards.push_back(33);
	Cards.push_back(23); Cards.push_back(43); Cards.push_back(31);
	Cards.push_back(22); Cards.push_back(42);  Cards.push_back(30);
	Cards.push_back(21); Cards.push_back(41); Cards.push_back(29);
	Cards.push_back(19); Cards.push_back(39); Cards.push_back(27);
	Cards.push_back(18); Cards.push_back(38); Cards.push_back(26);
	Cards.push_back(17); Cards.push_back(37); Cards.push_back(25);
	Cards.push_back(15); Cards.push_back(32);  Cards.push_back(20);
	Cards.push_back(14); Cards.push_back(28); Cards.push_back(16);
	Cards.push_back(13); Cards.push_back(24); Cards.push_back(12);
	Cards.push_back(11); Cards.push_back(3); Cards.push_back(7);
	Cards.push_back(10); Cards.push_back(2); Cards.push_back(6);
	Cards.push_back(9); Cards.push_back(1); Cards.push_back(5);
	Cards.push_back(8); Cards.push_back(0); Cards.push_back(4);
	Cards.push_back(51); Cards.push_back(52); Cards.push_back(56);


}

void zero::SendCards(GameSituation & clsGameSituation, ALLCardsList & uctALLCardsList)
{
	//ϴ��  
	vector <int> Cards;
	InitCards(Cards);
	//InitCards_Appoint(Cards);  
	int i, j, k;
	j = 0;
	for (k = 0; k < 17; k++) {
		for (i = 0; i < 3; i++, j++)
		{
			uctALLCardsList.arrCardsList[i].push_back(Cards[j]);
		}
	}

	//���ŵ���  
	clsGameSituation.DiPai[0] = Cards[j];
	clsGameSituation.DiPai[1] = Cards[j + 1];
	clsGameSituation.DiPai[2] = Cards[j + 2];

	return;
}
