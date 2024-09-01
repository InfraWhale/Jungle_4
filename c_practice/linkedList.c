#include <stdio.h>
#include <string.h> // 문자열 라이브러리

#define LENGTH 10

// StationList 구조체 정의
struct StationList {
    char name[20]; // 역 이름
    int next; //포인터
};

// 연결 리스트의 실체가 되는 배열 (요소 수 10)
struct StationList list[LENGTH]; // StationList라는 구조체로 타입을 주려면 struct StationList 이런 식으로 해줘야하는것 같다.

// 선두 포인터 선언
int head;

// 연결 리스트의 초기 상태를 만드는 함수
void initStationList() {
    // 역 이름과 포인터를 설정
    strcpy(list[0].name, "부산");
    list[0].next = -1;
    
    strcpy(list[1].name, "대전");
    list[1].next = 3;
    
    strcpy(list[2].name, "서울");
    list[2].next = 4;
    
    strcpy(list[3].name, "동대구");
    list[3].next = 0;

    strcpy(list[4].name, "천안아산");
    list[4].next = 1;

    // 선두 포인터 설정
    head = 2;
}

// 연결 리스트의 요소를 표시하는 함수
void printStationList() {
    int idx = head;
    while (idx != -1) {
        if (list[idx].next != -1) {
            printf("[%s] -> ", list[idx].name);
        } else {
            printf("[%s]", list[idx].name);
        }
        idx = list[idx].next;
    }

    printf("\n");
}

// 연결 리스트에[ 요소를 삽입하는 함수
void insertStationList(int insIdx, char insName[], int prevIdx) {
    strcpy(list[insIdx].name, insName);
    list[insIdx].next = list[prevIdx].next;
    list[prevIdx].next = insIdx;
}

//연결 리스트에 요소를 삭제하는 함수
void deleteStationList(int delIdx, int prevIdx) {
    list[prevIdx].next = list[delIdx].next;
}

int main() {
    // 초기 상태의 연결 리스트를 작성해 표시
    initStationList();
    printStationList();

    // 연결 리스트에 요소를 삽입 & 표시
    insertStationList(5, "광명", 2);
    printStationList();

    // 연결 리스트에 요소를 삭제 & 표시
    deleteStationList(5,2);
    printStationList();

    return 0; // 정상적인 종료. 다른 값 넣어도 크게 바뀌는건 없다. 다만 0이 관례
}

