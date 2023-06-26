#include "RingBuffer.h"


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

bool CRingBuffer::isEmpty(void)
{
	if (m_Rear == m_Front)
		return true;
	else
		return false;
}

int CRingBuffer::GetUseSize(void)
{
	if (isEmpty())
		return 0;
	else if (m_Rear > m_Front)
		return (m_Rear - m_Front);
	else if (m_Rear < m_Front)
		return ((m_MemoryLast - m_Front) + (m_Rear - m_RingBuffer + 1));
	// 디버그용
	else
		return (m_Size * 2);
}


int CRingBuffer::GetFreeSize(void)
{
	if (isEmpty())
		return m_Size;
	else if (m_Rear > m_Front)
		return ((m_MemoryLast - m_Rear) + (m_Front - m_RingBuffer));
	else if (m_Rear < m_Front)
		return ((m_Front - m_Rear) - 1);
	// 디버그용
	else
		return (m_Size * 2);
}

int CRingBuffer::DirectEnqueueSize(void)
{
	if (m_Rear >= m_Front)
		return (m_MemoryLast - m_Rear);
	else if (m_Rear < m_Front)
		return ((m_Front - m_Rear) - 1);
	// 디버그용
	else
		return (m_Size * 2);

}
int CRingBuffer::DirectDequeueSize(void)
{
	if (m_Rear >= m_Front)
		return (m_Rear - m_Front);
	if (m_Rear < m_Front)
		return (m_MemoryLast - m_Front);
	// 디버그용
	else
		return (m_Size * 2);

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
		//Rear위치 처음으로 옮기고
		m_Front = m_RingBuffer + (iSize - DirectDequeueSize() - 1);
	}
	else
	{
		m_Front = m_Front + iSize;
	}
}

void CRingBuffer::ClearBuffer(void)
{
	// 디버그용으로 front랑 rear만 처음으로 이동해버림
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