#include "RingBuffer.h"
// Front : �����͸� �� ��ġ
// Rear :  �����͸� ���� ��ġ
// Enqueue : Rear�� ����Ű�� �ڸ��� ������ �ְ� Rear + 1 (���� �������)
// Dequeue : Front�� ����Ű�� �ڸ��� ������ ���� Front + 1 (���� ä��������)
// Front�� �ڴ� ����־��Ѵ�. 
// Rear�� Front�� �ٷ� ���϶� Rear�� ���� �ִ´ٸ� Rear�� �����Ͽ� Front == Rear�� �Ǿ� ����ִ°Ͱ� ���� ���°� �ȴ�.

// Ringbuffer default size : 10000
CRingBuffer::CRingBuffer()
{
	m_RingBuffer = (char*)malloc(df_RINGBUFFER_SIZE);
	m_MemoryLast = m_RingBuffer + df_RINGBUFFER_SIZE - 1;


	m_Front = m_RingBuffer;
	m_Rear = m_RingBuffer;
	m_Size = df_RINGBUFFER_SIZE;
}

CRingBuffer::CRingBuffer(int iBufferSize)
{
	m_RingBuffer = (char*)malloc(iBufferSize);
	m_MemoryLast = m_RingBuffer + iBufferSize - 1;

	m_Front = m_RingBuffer;
	m_Rear = m_RingBuffer;
	m_Size = iBufferSize;
}
CRingBuffer::~CRingBuffer()
{
	free(m_RingBuffer);
}

void CRingBuffer::Resize(int size)
{
	// �̱���
}
int CRingBuffer::GetBufferSize(void)
{
	return m_Size;
}

int CRingBuffer::GetUseSize(void)
{

	if (m_Rear >= m_Front)
		return (m_Rear - m_Front);
	return (m_Rear - m_RingBuffer + 1) + (m_MemoryLast - m_Front);
	
}


int CRingBuffer::GetFreeSize(void)
{
	if (m_Rear >= m_Front)
		return (m_MemoryLast - m_Rear) + (m_Front - m_RingBuffer);
	return (m_Front - m_Rear) - 1;
}

int CRingBuffer::DirectEnqueueSize(void)
{

	if (m_Rear >= m_Front)
		return (m_MemoryLast - m_Rear + 1);
	else if (m_Rear < m_Front)
		return ((m_Front - m_Rear) - 1);


}
int CRingBuffer::DirectDequeueSize(void)
{
	if (m_Rear >= m_Front)
		return (m_Rear - m_Front);
	if (m_Rear < m_Front)
		return (m_MemoryLast - m_Front + 1);

}

int CRingBuffer::Enqueue(const char* chpDest, int iSize)
{
	if (iSize > GetFreeSize())
		return 0;
	char* tempRear = m_Rear;
	for (int i = 0; i < iSize; i++)
	{
		*tempRear = *chpDest;
		tempRear = tempRear + 1;
		if (tempRear > m_MemoryLast)
		{
			tempRear = m_RingBuffer;
		}
		chpDest++;
	}
	MoveRear(iSize);
	return iSize;
}

int CRingBuffer::Dequeue(char* chpDest, int iSize)
{
	if (GetUseSize() < iSize)
		return 0;
	char* tempFront = m_Front;
	for (int i = 0; i < iSize; i++)
	{
		*chpDest = *tempFront;
		tempFront = tempFront + 1;
		if (tempFront > m_MemoryLast)
		{
			tempFront = m_RingBuffer;
		}
		chpDest++;
	}
	MoveFront(iSize);
	return iSize;
}

int CRingBuffer::Peek(char* chpDest, int iSize)
{
	if (GetUseSize() < iSize)
		return 0;
	char* tempFront = m_Front;
	for (int i = 0; i < iSize; i++)
	{
		*chpDest = *tempFront;
		tempFront = tempFront + 1;
		if (tempFront > m_MemoryLast)
		{
			tempFront = m_RingBuffer;
		}
		chpDest++;
	}
	
	return iSize;
}

void CRingBuffer::MoveRear(int iSize)
{
	char* tempRear = m_Rear + iSize;
	if (tempRear > m_MemoryLast)
		tempRear = m_RingBuffer + (tempRear - m_MemoryLast - 1);
	m_Rear = tempRear;
}
void CRingBuffer::MoveFront(int iSize)
{
	char* tempFront = m_Front + iSize;
	if (tempFront > m_MemoryLast)
		tempFront = m_RingBuffer + (tempFront - m_MemoryLast - 1);
	m_Front = tempFront;
}

void CRingBuffer::ClearBuffer(void)
{
	m_Front = m_RingBuffer;
	m_Rear = m_RingBuffer;
}

char* CRingBuffer::GetFrontBufferPtr(void)
{
	return m_Front;
}


char* CRingBuffer::GetRearBufferPtr(void)
{
	return m_Rear;
}