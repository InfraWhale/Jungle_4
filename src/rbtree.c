#include "rbtree.h"
#include <stdlib.h>
#define SENTINEL nil_node

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));

  node_t *sentinel = malloc(sizeof(node_t));
  sentinel->color = RBTREE_BLACK;

  p->nil = sentinel;
  p->root = p->nil;
  
  return p;
}

void freeNode(node_t *node, rbtree *t) {
    if (node == t->nil) {
        return;
    }
    freeNode(node->left, t);
    freeNode(node->right, t);
    free(node);
  return;
}

void delete_rbtree(rbtree *t) {
  freeNode(t->root, t);

  free(t->nil);
  free(t);
}

void left_rotate(rbtree *t, node_t *x) {

  node_t *nil = t->nil; 
  node_t *y = x->right;

  // y의 left에 관한 로직 : x의 right에 연결한다.
  x->right = y->left; 
  if (y->left != nil) {
    y->left->parent = x;
  }
  
  // y에 관한 로직 -> x의 부모와 연결한다.
  y->parent = x->parent;
  if (x->parent == nil) {
    t->root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }

  // x에 관한 로직 -> y의 left에 연결한다.
  y->left = x;
  x->parent = y;
}

void right_rotate(rbtree *t, node_t *x) {

  node_t *nil = t->nil; 
  node_t *y = x->left;

  // y의 right에 관한 로직 : x의 left에 연결한다.
  x->left = y->right; 
  if (y->right != nil) {
    y->right->parent = x;
  }
  
  // y에 관한 로직 -> x의 부모와 연결한다.
  y->parent = x->parent;
  if (x->parent == nil) {
    t->root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }

  // x에 관한 로직 -> y의 right에 연결한다.
  y->right = x;
  x->parent = y;
}

void rbtree_insert_fixup(rbtree *t, node_t *ins) {
  while (ins->parent->color == RBTREE_RED) { // 삽입된 노드의 부모가 빨간색 -> 4번규칙 위반
    if (ins->parent == ins->parent->parent->left) { // ins의 부모가 왼쪽자식인 경우

      node_t *uncle = ins->parent->parent->right; // 삼촌 노드

      if (uncle->color == RBTREE_RED) { // 부모, 삼촌이 모두 빨간색 -> case 1
        ins->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        ins->parent->parent->color = RBTREE_RED;
        ins = ins->parent->parent;
      } else {

        if(ins == ins->parent->right) { // 할아버지~부모~자식이 꺾인 모양인경우 : case 3 해주기 위해 회전으로 펴준다 -> case 2
          ins = ins->parent;
          left_rotate(t, ins);
        }
      
        ins->parent->color = RBTREE_BLACK; // 할아버지~부모~ 자식이 펴진 모양인 경우 : 할아버지와 부모의 색 바꿔주고 회전을 해준다 -> case 3
        ins->parent->parent->color = RBTREE_RED;
        right_rotate(t, ins->parent->parent);
      }

    } else { // ins의 부모가 오른쪽자식인 경우 (위와 로직이 유사하다. 방향만 조금 다를뿐)

      node_t *uncle = ins->parent->parent->left; // 삼촌 노드

      if (uncle->color == RBTREE_RED) { // 부모, 삼촌이 모두 빨간색 -> case 1
        ins->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        ins->parent->parent->color = RBTREE_RED;
        ins = ins->parent->parent;
      } else {
        
        if(ins == ins->parent->left) { // 할아버지~부모~자식이 꺾인 모양인경우 : case 3 해주기 위해 회전으로 펴준다 -> case 2
          ins = ins->parent;
          right_rotate(t, ins);
        }
      
        ins->parent->color = RBTREE_BLACK; // 할아버지~부모~ 자식이 펴진 모양인 경우 : 할아버지와 부모의 색 바꿔주고 회전을 해준다 -> case 3
        ins->parent->parent->color = RBTREE_RED;
        left_rotate(t, ins->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *insnode = malloc(sizeof(node_t));
  node_t *nil = t->nil;
  insnode->key = key;
  insnode->color = RBTREE_RED;
  insnode->left = nil;
  insnode->right = nil;

  if (t->root == nil) { // 루트노드가 비어있는 경우
    t->root = insnode;
    insnode->parent = nil;
  } else { // 루트노드가 차있는 경우
    node_t *cur = t->root;
    while(cur != nil) {
      if (cur->key > key) { // 현재 노드보다 삽입노드가 작으면
        if (cur->left == nil) { // 현재노드 왼쪽이 nil : 삽입
          cur->left = insnode;
          insnode->parent = cur;
          break;
        } else {
          cur = cur->left;
        }
      } else { // 현재 노드보다 삽입노드가 크면
        if (cur->right == nil) { // 현재노드 오른쪽이 nil : 삽입
          cur->right = insnode;
          insnode->parent = cur;
          break;
        } else {
          cur = cur->right;
        }
      }
    }
  }

  rbtree_insert_fixup(t, insnode); // 삽입 후 RB TREE 방식으로 정렬한다.
  return insnode;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t *nil = t->nil;
  node_t *cur = t->root;
  while(cur != nil) {
    if (cur->key == key) { // 검색하는 값을 찾으면
      return cur;
    } else if (cur->key > key) { // 현재 노드의 값보다 검색값이 작으면
      cur = cur->left;
    } else { // 현재 노드의 값보다 검색값이 크면
      cur = cur->right;
    }
  }
  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  node_t *nil = t->nil;
  node_t *cur = t->root;
  while(cur != nil) {
    if (cur->left == nil) { // 최솟값 찾았을 때
      return cur;
    } else { // 더 작은 값이 있으면
      cur = cur->left;
    }
  }
}

node_t *rbtree_max(const rbtree *t) {
  node_t *nil = t->nil;
  node_t *cur = t->root;
  while(cur != nil) {
    if (cur->right == nil) { // 최댓값 찾았을 때
      return cur;
    } else { // 더 큰 값이 있으면
      cur = cur->right;
    }
  }
}

node_t *find_successor(rbtree *t, node_t *node) {
  node_t *nil = t->nil;
  node_t *cur = node->right;

  while(cur != nil) {
    if(cur->left == nil) {
      return cur;
    } else {
      cur = cur->left;
    }
  }
  return NULL;
}

void rbtree_delete_fixup(rbtree *t, node_t *del_pos) {
  while (del_pos != t->root && del_pos->color ==  RBTREE_BLACK) {
    if(del_pos == del_pos->parent->left) { // 삭제위치 노드가 왼쪽 자식일 때

      node_t *bro = del_pos->parent->right; // 형제노드

      if (bro->color == RBTREE_RED) { //형제노드 색상이 빨강 -> case1 (즉 이 아래 case 2,3,4는 형제노드의 색이 검정) 
        bro->color = RBTREE_BLACK;
        del_pos->parent->color = RBTREE_RED;
        left_rotate(t, del_pos->parent);
        bro = del_pos->parent->right;
      }
      if(bro->left->color == RBTREE_BLACK && bro->right->color == RBTREE_BLACK) { // 형제노드의 모든 자식 색깔이 검정 -> case 2
        bro->color = RBTREE_RED;
        del_pos = del_pos->parent;
      } else {
        if (bro->right->color == RBTREE_BLACK) { // 형제 노드의 오른쪽 자식이 검정 (case2 만족 안하므로 왼쪽 자식은 빨강)
          bro->left->color = RBTREE_BLACK;
          bro->color = RBTREE_RED;
          right_rotate(t, bro);
          bro = del_pos->parent->right; // case3의 경우 이후 case4를 수행하여 해결한다.
        }
        // 남은 경우 : 형제 노드의 오른쪽 자식이 빨강 -> case4
        bro->color = del_pos->parent->color;
        del_pos->parent->color = RBTREE_BLACK;
        bro->right->color = RBTREE_BLACK;
        left_rotate(t, del_pos->parent);
        del_pos = t->root;
      }
    } else { // 삭제위치 노드가 오른쪽 자식일 때
      
      node_t *bro = del_pos->parent->left; // 형제노드

      if (bro->color == RBTREE_RED) { //형제노드 색상이 빨강 -> case1 (즉 이 아래 case 2,3,4는 형제노드의 색이 검정) 
        bro->color = RBTREE_BLACK;
        del_pos->parent->color = RBTREE_RED;
        right_rotate(t, del_pos->parent);
        bro = del_pos->parent->left;
      }
      if(bro->right->color == RBTREE_BLACK && bro->left->color == RBTREE_BLACK) { // 형제노드의 모든 자식 색깔이 검정 -> case 2
        bro->color = RBTREE_RED;
        del_pos = del_pos->parent;
      } else {
        if (bro->left->color == RBTREE_BLACK) { // 형제 노드의 왼쪽 자식이 검정 (case2 만족 안하므로 오른쪽 자식은 빨강)
          bro->right->color = RBTREE_BLACK;
          bro->color = RBTREE_RED;
          left_rotate(t, bro);
          bro = del_pos->parent->left; // case3의 경우 이후 case4를 수행하여 해결한다.
        }
        // 남은 경우 : 형제 노드의 왼쪽 자식이 빨강 -> case4
        bro->color = del_pos->parent->color;
        del_pos->parent->color = RBTREE_BLACK;
        bro->left->color = RBTREE_BLACK;
        right_rotate(t, del_pos->parent);
        del_pos = t->root;
      }
    }
  }
  del_pos->color=RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *p) {
  node_t *nil = t->nil;

  color_t delete_color = p->color; // RB용

  node_t *child = nil;
  if(p->left == nil || p->right == nil) {
    // case 1 : 삭제 노드의 자식 노드가 없는 경우 or 자식노드가 하나인 경우
    if (p->left != nil) {
      child = p->left;
    } else {
      child = p->right;
    } // 두개의 경우 모두 해당되지 않으면 child = nil

    if (p->parent == nil) { // 삭제 노드가 루트인 경우
      t->root = child;
    } else if (p->parent->left == p) { // p가 왼쪽자식인 경우
      p->parent->left = child;
    } else { // p가 오른쪽자식인 경우
      p->parent->right = child;
    }
    
    child->parent = p->parent;

  } else {
    // case 2 : 삭제 노드의 자식 노드가 2개인 경우
    node_t *successor = find_successor(t, p);

    delete_color = successor->color; // RB용

    // child를 삭제위치에 옮기는 로직
    child = successor->right;
    if (successor->parent->left == successor) {
      successor->parent->left = child;
    } else {
      successor->parent->right = child;
    }
    child->parent = successor->parent;

    // successor를 p로 올리는 로직c
    if (p->parent == nil) { // p가 루트인 경우
      t->root = successor;
    } else if (p->parent->left == p) { // p가 왼쪽자식인 경우
      p->parent->left = successor;
    } else { // p가 오른쪽자식인 경우
      p->parent->right = successor;
    }
    successor->parent = p->parent;
    successor->left = p->left;
    successor->right = p->right;
    p->left->parent = successor;
    p->right->parent = successor;
    successor->color = p->color; 
  }
  free(p);

  if (delete_color == RBTREE_BLACK) {
    rbtree_delete_fixup(t, child);
  }

  return 1;
}

void rbtree_inorder(const rbtree *t, key_t *arr, const size_t n, node_t *cur, size_t *cnt) {
  if (cur == t->nil || *cnt >= n) {
    return;
  }

  rbtree_inorder(t, arr, n, cur->left, cnt);

  if (*cnt < n) {
    arr[*cnt] = cur->key;
    (*cnt)++;
  }

  rbtree_inorder(t, arr, n, cur->right, cnt);
  return;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  size_t cnt = 0;
  rbtree_inorder(t, arr, n, t->root, &cnt);

  return 0;
}
