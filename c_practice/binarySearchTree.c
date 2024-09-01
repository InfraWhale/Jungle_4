#include <stdio.h>
#include <stdlib.h> // 표준 유틸리티 헤더파일 -> 동적할당, 난수생성, 정수 연산, 검색 및 정렬
#include <glib.h>

// 구조체 정의
struct Node {
    int value;
    struct Node *parent, *left, *right;
};

// 루트 노드
struct Node *root = NULL;
// TODO 삭제시엔 root 노드 직전값 혹은 root 노드 직후값이 필요하다.

// 노드 검색
struct Node *findNode(int findVal) {
    struct Node *nowNode = root;
        while(1) {
        if (findVal == nowNode->value) {
            return nowNode;
        } else if (findVal < nowNode->value) {
            if (nowNode->left == NULL) {
                return NULL;
            } else {
                nowNode = nowNode->left;
            }
        } else {
            if (nowNode->right == NULL) {
                return NULL;
            } else {
                nowNode = nowNode->right;
            }
        }
    }
}

void printTree() {

    if(root == NULL) {
        return;
    }

    GQueue *queue = g_queue_new();
    g_queue_push_tail(queue, root);
    while (!g_queue_is_empty(queue)) {

        for(int i=0; i<g_queue_get_length(queue); i++) {
            struct Node *cur = g_queue_pop_head(queue);
            printf("%d ", cur->value);
            if (cur->left !=NULL) {
                g_queue_push_tail(queue, cur->left);
            }
            if (cur->right !=NULL) {
                g_queue_push_tail(queue, cur->right);
            }
        }
    printf("\n");
    }

    free(queue);

}

// 노드 삽입
void insertNode(int insVal) {
    struct Node *insNode = malloc(sizeof(struct Node));
    insNode->value = insVal;
    insNode->left = NULL;
    insNode->right = NULL;
    if(root == NULL) {
        insNode->parent = NULL;
        root = insNode;
    } else {
        struct Node *nowNode = root;
        while(1) {
            if (insVal < nowNode->value) {
                if (nowNode->left == NULL) {
                    nowNode->left = insNode;
                    insNode->parent = nowNode;
                    break;
                } else {
                    nowNode = nowNode->left;
                }
            } else {
                if (nowNode->right == NULL) {
                    nowNode->right = insNode;
                    insNode->parent = nowNode;
                    break;
                } else {
                    nowNode = nowNode->right;
                }
            }
        }
    }
}

// 왼쪽 오른쪽중 어디가 더 많은지 반환
int checkBalance(struct Node *startNode) {
    int leftCount = 0;
    int rightCount = 0;

    GQueue *queue = g_queue_new();
    g_queue_push_tail(queue, startNode->left);
    while (!g_queue_is_empty(queue)) {
        struct Node *cur = g_queue_pop_head(queue);
        leftCount ++;
        if (cur->left !=NULL) {
            g_queue_push_tail(queue, cur->left);
        }
        if (cur->right !=NULL) {
            g_queue_push_tail(queue, cur->right);
        }
    }
    g_queue_push_tail(queue, startNode->right);
    while (!g_queue_is_empty(queue)) {
        struct Node *cur = g_queue_pop_head(queue);
        rightCount ++;
        if (cur->left !=NULL) {
            g_queue_push_tail(queue, cur->left);
        }
        if (cur->right !=NULL) {
            g_queue_push_tail(queue, cur->right);
        }
    }
    free(queue);
    if (leftCount >= rightCount) {
        return 1;
    } else {
        return 0;
    }
}

// 노드 식제
void deleteNode(int delVal) {
    struct Node *delNode = findNode(delVal);
    if (delNode == NULL) {
        return;
    }
    // 자식노드가 없을 경우
    if(delNode->left == NULL && delNode->right == NULL) {
        if(delNode->parent->left == delNode) { // 삭제하려는 노드가 부모노드의 왼쪽인 경우
            delNode->parent->left = NULL;
        } else { // 삭제하려는 노드가 부모노드의 오른쪽인 경우
            delNode->parent->right = NULL;
        }
    
    // 자식노드가 하나일 경우
    } else if(delNode->left != NULL && delNode->right == NULL) { // 자식노드가 왼쪽에
        if(delNode->parent->left == delNode) {
            delNode->parent->left = delNode->left;
            delNode->left->parent = delNode->parent;
        } else {
            delNode->parent->right = delNode->left;
            delNode->left->parent = delNode->parent;
        }
    } else if(delNode->left != NULL && delNode->right == NULL) { // 자식노드가 오른쪽에
        if(delNode->parent->left == delNode) {
            delNode->parent->left = delNode->right;
            delNode->right->parent = delNode->parent;
        } else {
            delNode->parent->right = delNode->right;
            delNode->right->parent = delNode->parent;
        }
    // 자식노드가 2개인 경우
    } else if(delNode->left != NULL && delNode->right != NULL) {
        struct Node *cur;
        if (checkBalance(delNode)) { // 왼쪽이 더 많거나 같은경우
            cur = delNode->left;
            while(cur->right != NULL) {
                cur = cur->right;
            }
            cur->parent->right =NULL;

        } else { // 오른쪽이 더 많은경우
            cur = delNode->right;
            while(cur->left != NULL) {
                cur = cur->left;
            }
            cur->parent->left =NULL;
        }
        cur->parent = delNode->parent;
        cur->left = delNode->left;
        cur->right = delNode->right;

        delNode->left->parent = cur;
        delNode->right->parent = cur;

        if (delNode->parent->value > delNode->value) {
            delNode->parent->left = cur;
        } else {
            delNode->parent->right = cur;
        }
    }
    free(delNode);
    return;
}

// 사용한 메모리 전부 free
void freeMemory() {
    if (root == NULL) {
        return;
    }
    
    GQueue *queue = g_queue_new();
    g_queue_push_tail(queue, root);

    while (!g_queue_is_empty(queue)) {
        struct Node *cur = g_queue_pop_head(queue);
        if (cur->left !=NULL) {
            g_queue_push_tail(queue, cur->left);
        }
        if (cur->right !=NULL) {
            g_queue_push_tail(queue, cur->right);
        }

        free(cur);
    }

    g_queue_free(queue);
}

int main() {

    insertNode(5);
    insertNode(10);
    insertNode(15);
    insertNode(20);

    printTree();

    freeMemory();

    return 0;
}

