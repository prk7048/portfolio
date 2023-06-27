#include "RingBuffer.h"
// Front : 데이터를 뺄 위치
// Rear :  데이터를 넣을 위치
// Enqueue : Rear가 가리키는 자리에 데이터 넣고 Rear + 1 (여긴 비어있음)
// Dequeue : Front가 가리키는 자리에 데이터 빼고 Front + 1 (여긴 채워져있음)
// Front의 뒤는 비워둬야한다. 
// Rear가 Front의 바로 뒤일때 Rear에 값을 넣는다면 Rear가 증가하여 Front == Rear가 되어 비어있는것과 같은 상태가 된다.

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
	// 미구현
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
	// Enqueue시 rear를 넣은 데이터의 마지막 주소를 가르킬까? <- 지금은 이거 기준으로
	// 아니면 rear를 넣은 데이터 +1의 주소를 가르킬까?

	if (iSize > GetFreeSize())
		return 0;
	if (iSize > DirectEnqueueSize())
	{
		int size = DirectEnqueueSize();
		memcpy_s(m_Rear + 1, size, chpDest, size);

		//Rear위치 처음으로 옮기고
		m_Rear = m_RingBuffer;
		memcpy_s(m_Rear, DirectEnqueueSize(), chpDest + size, iSize - size);
		m_Rear = m_Rear + (iSize - size - 1);
		return iSize;
	}
	else
	{
		memcpy_s(m_Rear + 1, GetFreeSize(), chpDest, iSize);
		m_Rear = m_Rear + iSize;
		return iSize;
	}
}

int CRingBuffer::Dequeue(char* chpDest, int iSize)
{
	// 조건 체크
	if (iSize > GetUseSize())
		return 0;
	if (iSize > DirectDequeueSize())
	{
		int size = DirectDequeueSize();
		memcpy_s(chpDest, iSize, m_Front + 1, size);

		//Front위치 처음으로 옮기고
		m_Front = m_RingBuffer;
		memcpy_s(chpDest + size, iSize - size, m_Front, iSize - size);
		m_Front = m_Front + (iSize - size - 1);
		return iSize;
	}
	else
	{
		memcpy_s(chpDest, iSize, m_Front + 1, iSize);
		m_Front = m_Front + iSize;
		return iSize;
	}
}

int CRingBuffer::Peek(char* chpDest, int iSize)
{
	// 조건 체크
	if (iSize > GetUseSize())
		return 0;
	if (iSize > DirectDequeueSize())
	{
		int size = DirectDequeueSize();
		memcpy_s(chpDest, iSize, m_Front + 1, size);
		memcpy_s(chpDest + size, iSize - size, m_RingBuffer, iSize - size);
		return iSize;
	}
	else
	{
		memcpy_s(chpDest, iSize, m_Front + 1, iSize);
		return iSize;
	}
}

void CRingBuffer::MoveRear(int iSize)
{
	if (iSize > DirectEnqueueSize())
	{
		//Rear위치 처음으로 옮기고
		m_Rear = m_RingBuffer + (iSize - DirectEnqueueSize() - 1);
	}
	else
	{
		m_Rear = m_Rear + iSize;
	}
}
void CRingBuffer::MoveFront(int iSize)
{
	if (iSize > DirectDequeueSize())
	{
		m_Front = m_RingBuffer + (iSize - DirectDequeueSize() - 1);
	}
	else
	{
		m_Front = m_Front + iSize;
	}
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