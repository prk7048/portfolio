#include "RingBuffer.h"


//Test �ڵ�
int main(void)
{
	const char* str = "1234567890 abcdefghijklmnopqrstuvwxyz 1234567890abcdefghijklmnopqrstuvwxyz 12345";
	char str2[81];
	char DequeueStr[df_RINGBUFFER_SIZE];
	char PeekStr[df_RINGBUFFER_SIZE];
	const char* pStr = str;
	CRingBuffer RingBuffer(df_RINGBUFFER_SIZE);
	int enqueue_num = 0;
	int rest_enqueue_num = 80;
	int dequeue_num = 0;
	srand(100);
	while (1)
	{
		// Enqueue
		// Enqueue�� �������� �ʰ� �ϱ� ���� ����
		// �������� ���� ũ�Ⱑ 81���� ũ�� ���� ���� 81���Ͽ��� �̰�
		// ���� ũ�Ⱑ 81 �����̸� ���� ũ�⿡�� ������ ���� �̴´�.
		if (RingBuffer.GetFreeSize() >= 81)
		{
			enqueue_num = rand() % 81;
		}
		else if (RingBuffer.GetFreeSize() < 81)
		{
			enqueue_num = rand() % RingBuffer.GetFreeSize();
		}

		// Enqueue ����
		// rest_enqueue_num = str�� ���ڿ� enqueue�� ���� ũ��
		// rest_enqueue_num�� enqueue�� �������� �۴ٸ� ���� str�� ũ�⸸ŭ �ִ´�.
		// rest_enqueue_num�� ���ڿ��� ũ�⸸ŭ �ʱ�ȭ�Ѵ�.
		if (rest_enqueue_num - enqueue_num < 1)
		{
			enqueue_num = rest_enqueue_num;
			RingBuffer.Enqueue(pStr, enqueue_num);
			rest_enqueue_num = 80;
			pStr = str;
		}
		// str���� ���ڿ��� �ְ� ���� ũ�⸸ŭ rest_enqueue_num�� �����Ѵ�.
		// rest_enqueue_num�� enqueue_num���� ũ�ٸ� rest_enqueue_num���� enqueue_num�� ����.
		else
		{
			rest_enqueue_num -= enqueue_num;
			RingBuffer.Enqueue(pStr, enqueue_num);
			pStr = pStr + enqueue_num;
		}



		// Dequeue 
		// Ringbuffer�� ����ִٸ� Dequeue�� �������� �ʴ´�.
		if (RingBuffer.GetUseSize() == 0)
		{
			continue;
		}
		// Ringbuffer�� ���ǰ� �ִٸ� ������� size�� 80������ ������ ����
		// dequeue�� size�� �����Ѵ�.
		else
		{
			// val = 0 �� ����, +1�ؼ� 0�� �ȳ�������
			int val = RingBuffer.GetUseSize() % 80 + 1;
			dequeue_num = rand() % val;
		}

		// Dequeue ����
		// Peek�� Dequeue�� ���� ���� �����غ���.
		memset(DequeueStr, 0, sizeof(DequeueStr));
		memset(PeekStr, 0, sizeof(PeekStr));
		RingBuffer.Peek(PeekStr, dequeue_num);
		RingBuffer.Dequeue(DequeueStr, dequeue_num);

		// Peek�� ���ڿ��� Dequeue�� ���ڿ��� �ٸ��ٸ� error ���ٸ� ���
		if (memcmp(PeekStr, DequeueStr, dequeue_num) == 0)
		{
			// NULL�� ������ ���ڿ��� ���ԵǾ��־ %s�� ��½� NULL���� ���ܹ�����.
			for (int i = 0; i < dequeue_num; i++)
				printf("%c", DequeueStr[i]);
		}
		else
		{
			printf("error");
			break;
		}
	}
}
