# Circular Queue + Verifide Code
## 설명
>전송 및 수신 중 입력되는 패킷 TCP 헤더의 양을 줄이고 사용자 수준에서 임시 저장을 위한 링버퍼입니다.  
개념적으로 링버퍼는 순환하지만 실제론 메모리에서 연속적인 공간에 직선적으로 할당될뿐 시작과 끝이 이어지진 않았으므로 로직를 이용해 회전하는 것처럼 구현됩니다.  
같은 ringbuffer에 대해 Enqueue와 Dequeue가 동시에 일어났을때 Lock없이 처리할수 있게 로직을 수정했습니다.

Verfide Code 수정, Readme 수정필요


## 느낀점
