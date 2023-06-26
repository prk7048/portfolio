#include "RingBuffer.h"


//Test 코드
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
		// Enqueue를 실패하지 않게 하기 위한 로직
		// 링버퍼의 남은 크기가 81보다 크면 랜덤 수를 81이하에서 뽑고
		// 남은 크기가 81 이하이면 남은 크기에서 랜덤한 수를 뽑는다.
		if (RingBuffer.GetFreeSize() >= 81)
		{
			enqueue_num = rand() % 81;
		}
		else if (RingBuffer.GetFreeSize() < 81)
		{
			enqueue_num = rand() % RingBuffer.GetFreeSize();
		}

		// Enqueue 로직
		// rest_enqueue_num = str의 문자열 enqueue후 남은 크기
		// rest_enqueue_num이 enqueue할 갯수보다 작다면 남은 str의 크기만큼 넣는다.
		// rest_enqueue_num을 문자열의 크기만큼 초기화한다.
		if (rest_enqueue_num - enqueue_num < 1)
		{
			enqueue_num = rest_enqueue_num;
			RingBuffer.Enqueue(pStr, enqueue_num);
			rest_enqueue_num = 80;
			pStr = str;
		}
		// str에서 문자열을 넣고 남은 크기만큼 rest_enqueue_num을 수정한다.
		// rest_enqueue_num이 enqueue_num보다 크다면 rest_enqueue_num에서 enqueue_num을 뺀다.
		else
		{
			rest_enqueue_num -= enqueue_num;
			RingBuffer.Enqueue(pStr, enqueue_num);
			pStr = pStr + enqueue_num;
		}



		// Dequeue 
		// Ringbuffer가 비어있다면 Dequeue를 실행하지 않는다.
		if (RingBuffer.GetUseSize() == 0)
		{
			continue;
		}
		// Ringbuffer가 사용되고 있다면 사용중인 size중 80이하의 값으로 나눠
		// dequeue할 size를 결정한다.
		else
		{
			// val = 0 도 나옴, +1해서 0은 안나오게함
			int val = RingBuffer.GetUseSize() % 80 + 1;
			dequeue_num = rand() % val;
		}

		// Dequeue 로직
		// Peek와 Dequeue를 따로 빼서 저장해본다.
		memset(DequeueStr, 0, sizeof(DequeueStr));
		memset(PeekStr, 0, sizeof(PeekStr));
		RingBuffer.Peek(PeekStr, dequeue_num);
		RingBuffer.Dequeue(DequeueStr, dequeue_num);

		// Peek한 문자열과 Dequeue한 문자열이 다르다면 error 같다면 출력
		if (memcmp(PeekStr, DequeueStr, dequeue_num) == 0)
		{
			// NULL이 복사한 문자열에 포함되어있어서 %s로 출력시 NULL에서 끊겨버린다.
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
