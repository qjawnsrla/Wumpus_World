## 회의내용에서 변경된 점
1. 사방이 갈 수 없는 경우 종료. 이 경우 금 찾기는 실패
2. 앞, 좌, 우로 갈 수 없는 경우 삭제. 다른 조건으로 모두 처리됨
3. 좌, 우, 뒤를 갈 수 없으면 왔던 길로 돌아가는데, 벽, 구덩이 외에 방문한 타일도 포함.
4. 괴물이 앞에 있는 경우가 없어서 추가. 이 경우는 냄새날 경우와 똑같이 행동.
5. shoot 메소드 삭제. 환경 변화만 체크하면 되기 때문에 agent에서는 메소드 불필요.
### ※위 변경점은 잘못되었을 수 있음
#