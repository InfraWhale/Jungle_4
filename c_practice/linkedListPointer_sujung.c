#include <stdio.h>
#include <string.h> // 문자열 헤더파일
#include <stdlib.h> // 표준 유틸리티 헤더파일 -> 동적할당, 난수생성, 정수 연산, 검색 및 정렬

// StationList 구조체 정의
struct StationList {
    char name[20]; // 역 이름
    struct StationList *prev, *next; //포인터
};

// 마지막 지점
struct StationList *last;

// 연결 리스트의 요소를 표시하는 함수(정방향)
void printStationList(struct StationList *head) {
    struct StationList *cur = head->next; // head.getNext() 같은 느낌으로 사용

    while (cur != NULL) {
        if(cur->next == NULL) {
            printf("[%s]", cur->name);
        } else {
            printf("[%s] => ", cur->name);
        }
        cur = cur->next;
    }

    printf("\n");
}

// 이름으로 연결 리스트의 주소값을 찾는 함수
struct StationList *findStation(char findName[], struct StationList *head) {

    struct StationList *nowPos = head;

    while(nowPos != NULL) {
        if (strcmp(nowPos->name, findName) == 0) {
            return nowPos;
        }
        nowPos = nowPos->next;
    }
    return NULL;
}

void insertStationListHead(struct StationList *head, char newName[]) {
    struct StationList *insNode = malloc(sizeof(struct StationList));
    struct StationList *nNode = head->next;
    strcpy(insNode->name, newName);

    head->next = insNode;

    insNode->prev = head;
    insNode->next = nNode;
    
    if (nNode != NULL) {
        nNode->prev = insNode;
    } else {
        last = insNode;
    }
}

void insertStationList(struct StationList *head, char pName[], char newName[]) {
    struct StationList *pNode = findStation(pName, head);
    if (pNode == NULL) {
        return;
    }

    struct StationList *insNode = malloc(sizeof(struct StationList));
    struct StationList *nNode = pNode->next;
    strcpy(insNode->name, newName);

    pNode->next = insNode;

    insNode->prev = pNode;
    insNode->next = nNode;
    
    if (nNode != NULL) {
        nNode->prev = insNode;
    } else {
        last = insNode;
    }
}

void delStationList(char delName[], struct StationList *head) {

    struct StationList *delNode = findStation(delName, head);
    if (delNode == NULL) {
        return;
    }

    if (delNode == last) {
        last = delNode -> prev;
    }

    delNode -> prev -> next = delNode -> next; 
    delNode -> next -> prev = delNode -> prev;

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

    last = head;

    insertStationListHead(head, "부산");
    insertStationListHead(head, "대전");
    insertStationListHead(head, "서울");
    insertStationList(head, "서울", "동대구");
    insertStationList(head, "서울", "천안아산");

    printStationList(head);

    insertStationList(head, "서울", "광명");
    printStationList(head);

    delStationList("광명", head);
    printStationList(head);

    freeMemory(head);

    return 0;
}

