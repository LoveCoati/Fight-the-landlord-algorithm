#include "GameSituation.h"
#include <vector>
#include "DataStruct.h"
#include "Array.hpp"
#include "config.h"

namespace zero {

	class HandCardData
	{
	public:
		//���캯��
		HandCardData();

		//��������
		virtual ~HandCardData();

	public:
		//�������С����޻�ɫ��ֵ��3~17
		std::vector <int> value_nHandCardList;

		//int[18] �������С���״̬��¼������һЩ���㣬ֵ��Ϊ��index�ƶ�Ӧ������0~4
		zero::Array<int> value_aHandCardList;

		//�������С����л�ɫ�����մӴ�С������  56��52������С������4~0����3��3��3��3
		std::vector <int> color_nHandCardList;

		//���Ƹ��� ��ʼ = 17
		int nHandCardCount ;

		//��ҽ�ɫ��λ       0������    1��ũ�񡪡������¼�   2��ũ�񡪡������ϼ�
		int nGameRole;

		//�����λID 
		int nOwnIndex;

		//���Ҫ���ȥ��������
		zero::CardGroupData uctPutCardType;
		//Ҫ���ȥ���ơ����޻�ɫ(����ֵ��������)
		std::vector <int> value_nPutCardList;
		//Ҫ���ȥ���ơ����л�ɫ(����ɫ��������)
		std::vector <int> color_nPutCardList;
		//��ǰ����Ƶ��������ݣ���������ʱ��Ҹ�����������ɸѡ  
		HandCardValue uctHandCardValue;


	public:

		//Ҫ��������������
		void ClearPutCardList();

		//�������򣬴��ƿ�ǰ(���������� �Ӵ�С)
		void SortAsList(std::vector <int> &arr);

		//��һ���ƣ����ز����Ƿ�Ϸ�  //�ṩ��PutCards ʹ��
		bool PutOneCard(int value_nCard, int &clear_nCard);

		//��һ���ƣ����ز����Ƿ�Ϸ�
		bool PutCards();

		/**
		 * ͨ���л�ɫ���ƻ�ȡ�޻�ɫ���ƣ��������ֽṹ��
		 * color_nHandCardList���������� ת��Ϊvalue_nHandCardList��value_aHandCardList����
		 */
		void get_valueHandCardList();

		//��ʼ��
		void Init();

#ifdef  __DEBUG__

		//������г�Ա���������ڲ���
		void PrintAll();

#endif

	};
}
/**
 color_nHandCardList ���ݽṹ 
	00:A���� 01:A�ݻ� 02:A���� 03:A���� 04:2���� 05:2�ݻ� 06:2���� 07:2���� 08:3���� 09:3�ݻ� 10:3���� 11:3���� .....

 value_nHandCardList ���ݽṹ
	0:�� 1:�� 2:�� 3:A(���顢�ݻ� �����ġ����� �ϲ�) 4:1(���顢�ݻ� �����ġ����Һϲ�)  ......

 value_aHandCardList  ���ݽṹ 
	(0:A)<=4 (1:2)<=4 (2:3)<=4

 */