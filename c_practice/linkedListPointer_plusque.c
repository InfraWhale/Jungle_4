#include <stdio.h>
#include <string.h> // 문자열 헤더파일
#include <stdlib.h> // 표준 유틸리티 헤더파일 -> 동적할당, 난수생성, 정수 연산, 검색 및 정렬

// StationList 구조체 정의
struct StationList {
    char name[20]; // 역 이름
    struct StationList *prev, *next; //포인터
};

// 첫 지점
struct StationList *head;

// 마지막 지점
struct StationList *last;

// 연결 리스트의 요소를 표시하는 함수(정방향)
void printStationList() {
    struct StationList *cur = head;

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

// 연결 리스트의 요소를 표시하는 함수(역방향)
void printStationListRev() {
    struct StationList *cur = last;

    while (cur != NULL) {
        if(cur->prev == NULL) {
            printf("[%s]", cur->name);
        } else {
            printf("[%s] => ", cur->name);
        }
        cur = cur->prev;
    }
    printf("\n");
}

// 이름으로 연결 리스트의 주소값을 찾는 함수
struct StationList *findStation(char findName[]) {

    struct StationList *nowPos = head;

    while(nowPos != NULL) {
        if (strcmp(nowPos->name, findName) == 0) {
            return nowPos;
        }
        nowPos = nowPos->next;
    }
    return NULL;
}

// 맨앞에 삽입
void insertStationListHead(char newName[]) { 
    struct StationList *insNode = malloc(sizeof(struct StationList));
    strcpy(insNode->name, newName);

    if (head == NULL) { // 요소가 하나도 없었을 때
        insNode->prev = NULL;
        insNode->next = NULL;
        head = insNode;
        last = insNode;
    } else { // 요소가 있을때
        insNode->prev = NULL;
        insNode->next = head;

        head->prev = insNode;

        head = insNode;
    }
}

// 중간에 삽입
void insertStationList(char pName[], char newName[]) { 
    struct StationList *pNode = findStation(pName);
    if (pNode == NULL) {
        return;
    }

    struct StationList *insNode = malloc(sizeof(struct StationList));
    strcpy(insNode->name, newName);
    
    struct StationList *nNode = pNode->next;

    pNode->next = insNode;

    insNode->prev = pNode;
    insNode->next = nNode;

    if (last == pNode) { // 마지막 요소 뒤에 삽입이 일어난 경우
        last = insNode;
    } else {
        nNode->prev = insNode;
    }
}

// 마지막에 삽입
void insertStationListLast(char newName[]) { 

    struct StationList *insNode = malloc(sizeof(struct StationList));
    strcpy(insNode->name, newName);

    if (head == NULL) { // 요소가 하나도 없었을 때
        insNode->prev = NULL;
        insNode->next = NULL;
        head = insNode;
        last = insNode;
    } else { // 요소가 있을때
        insNode->prev = last;
        insNode->next = NULL;

        last->next = insNode;

        last = insNode;
    }
}

void delStationListHead() {

    struct StationList *delNode = head;
    if (delNode == NULL) {
        return;
    }

    head = delNode -> next;

    delNode -> next -> prev = delNode -> prev;

    free(delNode);
}

void delStationListLast() {

    struct StationList *delNode = last;
    if (delNode == NULL) {
        return;
    }
    
    last = delNode -> prev;

    delNode -> prev -> next = delNode -> next; 

    free(delNode);
}

void delStationList(char delName[]) {

    struct StationList *delNode = findStation(delName);
    if (delNode == NULL) {
        return;
    }

    if (delNode == head) {
        head = delNode -> next;
    } else if (delNode == last) {
        last = delNode -> prev;
    }

    delNode -> prev -> next = delNode -> next; 
    delNode -> next -> prev = delNode -> prev;

    free(delNode);
}

void freeMemory() {
    struct StationList *cur = head -> next;

    while (cur != NULL) {
        struct StationList *next = cur->next;
        free(cur);
        cur = next;
    }

    free(head);
}

int main() {

    head = NULL;
    last = NULL;

    insertStationListHead("부산");
    insertStationListHead("대전");
    insertStationListHead("서울");
    insertStationList("서울", "동대구");
    insertStationList("서울", "천안아산");

    printStationList();

    insertStationList("서울", "광명");
    insertStationListLast("제주");

    printStationList();
    printStationListRev();
    printf("head : %s \n", head->name);
    printf("last : %s \n", last->name);

    delStationList("광명");
    delStationListHead();
    delStationListLast();
    printStationList();
    printf("head : %s \n", head->name);
    printf("last : %s \n", last->name);

    freeMemory();

    return 0;
}

