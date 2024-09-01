#include <stdio.h>
#include <stdlib.h> // 표준 유틸리티 헤더파일 -> 동적할당, 난수생성, 정수 연산, 검색 및 정렬

// 구조체 정의
struct Node {
    int value;
    struct Node *parent, *left, *right;
};

// 루트 노드
struct Node *root = NULL;

void printTreeHelper(struct Node *node, int level, int indentSpace) {
    if (node == NULL) {
        return;
    }
    
    // 재귀 호출을 통해 오른쪽 자식을 먼저 출력
    printTreeHelper(node->right, level + 1, indentSpace);
    
    // 현재 노드를 출력
    for (int i = 0; i < level * indentSpace; i++) {
        printf(" ");
    }
    printf("%d\n", node->value);
    
    // 재귀 호출을 통해 왼쪽 자식을 출력
    printTreeHelper(node->left, level + 1, indentSpace);
}

void printTree() {
    int indentSpace = 4; // 노드 간의 간격 조정
    printTreeHelper(root, 0, indentSpace);
}

// 노드 검색
struct Node *findNode(int findVal) {
    struct Node *nowNode = root;
    while (nowNode != NULL) {
        if (findVal == nowNode->value) {
            return nowNode;
        } else if (findVal < nowNode->value) {
            nowNode = nowNode->left;
        } else {
            nowNode = nowNode->right;
        }
    }
    return NULL;
}

int countNodes(struct Node *node) {
    if (node == NULL) {
        return 0;
    }
    return 1 + countNodes(node->left) + countNodes(node->right);
}

// 왼쪽 서브트리에서 가장 큰 노드를 찾는 함수
struct Node *findMax(struct Node *node) {
    while (node && node->right != NULL) {
        node = node->right;
    }
    return node;
}

// 오른쪽 서브트리에서 가장 작은 노드를 찾는 함수
struct Node *findMin(struct Node *node) {
    while (node && node->left != NULL) {
        node = node->left;
    }
    return node;
}

// 노드를 삭제하는 함수
void deleteNode(int delVal) {
    struct Node *delNode = findNode(delVal);
    if (delNode == NULL) {
        return;
    }

    struct Node *child = NULL;
    struct Node *replacement = NULL;
    if (delNode->left == NULL || delNode->right == NULL) {
        // Case 1: No child (leaf node) or one child
        if (delNode->left != NULL) {
            child = delNode->left;
        } else {
            child = delNode->right;
        }
        if (delNode->parent == NULL) {
            // If deleting the root node
            root = child;
        } else if (delNode->parent->left == delNode) {
            delNode->parent->left = child;
        } else {
            delNode->parent->right = child;
        }
        if (child != NULL) {
            child->parent = delNode->parent;
        }
    } else {
        // Case 2: Two children
        int leftCount = countNodes(delNode->left);
        int rightCount = countNodes(delNode->right);
        
        if (leftCount >= rightCount) {
            replacement = findMax(delNode->left);
        } else {
            replacement = findMin(delNode->right);
        }
        int temp = replacement->value;
        deleteNode(temp);
        delNode->value = temp;

        return;
    }

    free(delNode);
}


void freeMemoryHelper(struct Node *node) {
    if (node == NULL) {
        return;
    }
    freeMemoryHelper(node->left);
    freeMemoryHelper(node->right);
    free(node);
}

void freeMemory() {
    freeMemoryHelper(root);
    root = NULL; // 루트 포인터를 NULL로 설정하여 메모리 해제 후 올바른 상태 유지
}

void insertNode(int insVal) {
    struct Node *insNode = malloc(sizeof(struct Node));
    insNode->value = insVal;
    insNode->left = NULL;
    insNode->right = NULL;
    if (root == NULL) {
        insNode->parent = NULL;
        root = insNode;
    } else {
        struct Node *nowNode = root;
        while (1) {
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

int main() {
    insertNode(50);
    insertNode(18);
    insertNode(79);
    insertNode(66);
    insertNode(23);
    insertNode(12);
    insertNode(2);
    insertNode(33);
    insertNode(25);
    insertNode(41);
    insertNode(82);
    insertNode(99);

    printTree();

    // deleteNode(12);
    // printTree();

    deleteNode(33);
    printTree();

    freeMemory();

    return 0;
}
