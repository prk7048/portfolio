# Circular Queue + Verifide Code
## 설명
>전송 및 수신 중 입력되는 패킷 TCP 헤더의 양을 줄이고 사용자 수준에서 임시 저장을 위한 링버퍼입니다.  
개념적으로 링버퍼는 순환하지만 실제론 메모리에서 연속적인 공간에 직선적으로 할당될뿐 시작과 끝이 이어지진 않았으므로 로직를 이용해 회전하는 것처럼 구현됩니다.  
링버퍼가 제대로 작동하는지 확인하기 위한 코드가 포함되어 있으며, 확인하는 방법은 Enqueue 및 Dequeue를 반복적으로 시행하고, Dequeue에서 콘솔 창으로 출력하여 지정된 문자열이 왜곡되었는지 확인합니다.  

## 느낀점
