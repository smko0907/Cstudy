// 이진 검색 트리

#include <stdio.h>
#include <stdlib.h>
#include 
#include <"Memory Leak.h">

typedef int TreeElement;
typedef struct TreeNode {
    TreeElement value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* addNode(TreeNode* tree, TreeElement data); // 트리 노드 추가
TreeNode* removeNode(TreeNode* tree, TreeElement data); // 트리 노드 삭제
TreeNode* searchNode(TreeNode* tree, TreeElement data); // 트리 노드 탐색
void displayInOrder(TreeNode* tree); // 중위 순회
TreeNode* findMin(TreeNode* tree); // 최소값 탐색
TreeNode* findMax(TreeNode* tree); // 최대값 탐색
void freeTree(TreeNode* tree); // 트리 제거

TreeNode* addNode(TreeNode* tree, TreeElement data) {
    if (!tree) {//이진탐색 실패 위치가 삽입 위치 & 노드가 없을 때
        tree = (TreeNode*)malloc(sizeof(TreeNode));
        tree->value = data;
        tree->left = NULL;
        tree->right = NULL;
    }
    else if (data == tree->value) printf("\n\n\t\t%d는 이미 등록 된 값 입니다.\n", data);
    else if (data < tree->value) tree->left = addNode(tree->left, data);
    else /* data > t->value */ tree->right = addNode(tree->right, data);
    return tree;
}

TreeNode* searchNode(TreeNode* tree, TreeElement data) {
    if (!tree) return NULL; //탐색 실패
    if (data == tree->value) return tree; //탐색 성공
    if (data < tree->value) return searchNode(tree->left, data); // 왼쪽 탐색
    else /* data > tree->value */ return searchNode(tree->right, data); // 오른쪽 탐색
}


TreeNode* removeNode(TreeNode* tree, TreeElement data) {
    TreeNode* temp = NULL;
    if (tree) {
        if (data == tree->value) { // 삭제할 값 노드 찾기
            if (tree->left == NULL && tree->right == NULL) { //노드가 리프인 경우
                free(tree);
                return NULL;
            }
            else {
                if (tree->left == NULL) { //오른쪽 자식만 있다.
                    temp = tree->right;
                    free(tree);
                    return temp;
                }
                if (tree->right == NULL) { //왼쪽 자식만 있다.
                    temp = tree->left;
                    free(tree);
                    return temp;
                }
                temp = findMax(tree->left); //오른쪽 & 왼쪽 모두 자식이 있어, 왼쪽 가장 큰 값 호출
                tree->value = temp->value; //왼쪽 가장 큰 값 저장
                tree->left = removeNode(tree->left, temp->value); //왼쪽 가장 큰 값 삭제 재귀
            }
        }
        else { // 값 찾기, 재귀호출
            if (data < tree->value) tree->left = removeNode(tree->left, data);
            else /* data > t->value */ tree->right = removeNode(tree->right, data);
        }
    }
    return tree;
}
