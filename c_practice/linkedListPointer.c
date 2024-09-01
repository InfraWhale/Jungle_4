#include <stdio.h>
#include <string.h> // 문자열 헤더파일
#include <stdlib.h> // 표준 유틸리티 헤더파일 -> 동적할당, 난수생성, 정수 연산, 검색 및 정렬

#define LENGTH 10

// StationList 구조체 정의
struct StationList {
    char name[20]; // 역 이름
    struct StationList *prev, *next; //포인터
};

// 연결 리스트의 실체가 되는 배열
// struct StationList list[LENGTH]; // 포인터변수 사용 -> 안씀

// 선두 포인터 선언 -> main()에서 직접
//int head;

// 연결 리스트의 초기 상태를 만드는 함수 // -> main()에서 직접
// void initStationList() {}

// 연결 리스트의 요소를 표시하는 함수
void printStationList(struct StationList *head) {
    struct StationList *cur = head->next; // head.getNext() 같은 느낌으로 사용

    while (cur != NULL) {
        printf("[%s] => ", cur->name);
        cur = cur->next;
    }

    printf("\n");
}

void insertStationList(struct StationList *pNode, char newName[]) {
    struct StationList *insNode = malloc(sizeof(struct StationList));
    struct StationList *nNode = pNode->next;
    strcpy(insNode->name, newName);

    pNode->next = insNode;
    insNode->next = nNode;
}

void delStationList(struct StationList *pNode) {
    struct StationList *delNode = pNode -> next;
    pNode ->next = delNode->next; 

    free(delNode);
}

void freeMemory(struct StationList * head) {
    struct StationList *cur = head -> next;

    while (cur != NULL) {
        struct StationList *next = cur->next;
        free(cur);
        cur = next;
    }

    free(head);
}


int main() {
    // 헤드 포인터 선언
    struct StationList *head = malloc(sizeof(struct StationList));

    struct StationList *sta0 = malloc(sizeof(struct StationList));
    strcpy(sta0->name, "부산");

    struct StationList *sta1 = malloc(sizeof(struct StationList));
    strcpy(sta1->name, "대전");

    struct StationList *sta2 = malloc(sizeof(struct StationList));
    strcpy(sta2->name, "서울");

    struct StationList *sta3 = malloc(sizeof(struct StationList));
    strcpy(sta3->name, "동대구");
    
    struct StationList *sta4 = malloc(sizeof(struct StationList));
    strcpy(sta4->name, "천안아산");

    head -> next = sta2;
    sta2 -> next = sta4; 
    sta4 -> next = sta1; 
    sta1 -> next = sta3;
    sta3 -> next = sta0;
    sta0 -> next = NULL;
    printStationList(head);

    insertStationList(sta2, "광명");
    printStationList(head);

    delStationList(sta2);
    printStationList(head);

    freeMemory(head);

    return 0;
}

