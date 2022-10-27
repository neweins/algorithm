## How to build c++ sources
- Change file name to compile in CMakeLists.txt

## Etc
- Use visual studio code

## theory

1. 그리디 알고리즘
  > - 모든 관계가 배수 관계가 성립하면 그리디 알고리즘 사용 가능하다.<br>
  ex> 동전 1, 5, 50원 중 선택해서 최소 또는 최대 동전 수를 내야할 때 1, 5, 50은 서로 배수 관계이다.
  
2. DFS
  > - 완전탐색에서 재귀함수로 구현시 모든 경우를 다 해봐야 한다면 리턴값은 필요없다.<br>
  <pre><code> 
  void DFS(...){
    ...
    DFS();
    ...
  }
  </code></pre>

