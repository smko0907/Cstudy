// ���� �˻� Ʈ��

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

TreeNode* addNode(TreeNode* tree, TreeElement data); // Ʈ�� ��� �߰�
TreeNode* removeNode(TreeNode* tree, TreeElement data); // Ʈ�� ��� ����
TreeNode* searchNode(TreeNode* tree, TreeElement data); // Ʈ�� ��� Ž��
void displayInOrder(TreeNode* tree); // ���� ��ȸ
TreeNode* findMin(TreeNode* tree); // �ּҰ� Ž��
TreeNode* findMax(TreeNode* tree); // �ִ밪 Ž��
void freeTree(TreeNode* tree); // Ʈ�� ����

TreeNode* addNode(TreeNode* tree, TreeElement data) {
    if (!tree) {//����Ž�� ���� ��ġ�� ���� ��ġ & ��尡 ���� ��
        tree = (TreeNode*)malloc(sizeof(TreeNode));
        tree->value = data;
        tree->left = NULL;
        tree->right = NULL;
    }
    else if (data == tree->value) printf("\n\n\t\t%d�� �̹� ��� �� �� �Դϴ�.\n", data);
    else if (data < tree->value) tree->left = addNode(tree->left, data);
    else /* data > t->value */ tree->right = addNode(tree->right, data);
    return tree;
}

TreeNode* searchNode(TreeNode* tree, TreeElement data) {
    if (!tree) return NULL; //Ž�� ����
    if (data == tree->value) return tree; //Ž�� ����
    if (data < tree->value) return searchNode(tree->left, data); // ���� Ž��
    else /* data > tree->value */ return searchNode(tree->right, data); // ������ Ž��
}


TreeNode* removeNode(TreeNode* tree, TreeElement data) {
    TreeNode* temp = NULL;
    if (tree) {
        if (data == tree->value) { // ������ �� ��� ã��
            if (tree->left == NULL && tree->right == NULL) { //��尡 ������ ���
                free(tree);
                return NULL;
            }
            else {
                if (tree->left == NULL) { //������ �ڽĸ� �ִ�.
                    temp = tree->right;
                    free(tree);
                    return temp;
                }
                if (tree->right == NULL) { //���� �ڽĸ� �ִ�.
                    temp = tree->left;
                    free(tree);
                    return temp;
                }
                temp = findMax(tree->left); //������ & ���� ��� �ڽ��� �־�, ���� ���� ū �� ȣ��
                tree->value = temp->value; //���� ���� ū �� ����
                tree->left = removeNode(tree->left, temp->value); //���� ���� ū �� ���� ���
            }
        }
        else { // �� ã��, ���ȣ��
            if (data < tree->value) tree->left = removeNode(tree->left, data);
            else /* data > t->value */ tree->right = removeNode(tree->right, data);
        }
    }
    return tree;
}
