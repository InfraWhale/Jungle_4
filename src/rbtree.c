#include "rbtree.h"

#include <stdlib.h>

#define SENTINEL nil_node

rbtree *new_rbtree(void) {
  // TODO: initialize struct if needed
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
  // TODO: reclaim the tree nodes's memory
  
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

      if (uncle->color = RBTREE_RED) { // 부모, 삼촌이 모두 빨간색 -> case 1
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

      if (uncle->color = RBTREE_RED) { // 부모, 삼촌이 모두 빨간색 -> case 1
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
  // TODO: implement insert
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

  // rbtree_insert_fixup(t, insnode); // 삽입 후 RB TREE 방식으로 정렬한다.
  return insnode;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
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
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
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
    
    if (child != nil) { // 자식노드가 하나인 경우
      child->parent = p->parent; 
    }
    free(p);
  } else {
    // case 2 : 삭제 노드의 자식 노드가 2개인 경우
    node_t *successor = find_successor(t, p);

    delete_color = successor->color; // RB용
    child = successor->right; // RB용

    p->key = successor->key;
    
    // successor의 경우 오른쪽 자식이 있을 수 있으므로 아래 처리
    if (successor->parent->left == successor) {
      successor->parent->left = successor->right;
    } else {
      successor->parent->right = successor->right;
    }

    if (successor->right != nil) {
      successor->right->parent = successor->parent;
    }
    free(successor);
  }

  if (delete_color == RBTREE_BLACK) { // RB용
    rbtree_delete_fixup(t, child);
  }

  return 1;
}

void rbtree_delete_fixup(rbtree *t, node_t *del_child) {

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


int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
