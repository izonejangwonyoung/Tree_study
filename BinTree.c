#include <stdio.h>
#include <stdlib.h>
#include "Member.h"
#include "BinTree.h"


static BinNode *AllocBinNode(void) {
    return calloc(1, sizeof(BinNode));
}

static void setBinNode(BinNode *n, const Member *x, const BinNode *left, const BinNode *right) {
    n->data = *x;
    n->left = left;
    n->right = right;
}

BinNode *Search(BinNode *p, const Member *x) {
    int cond;
    if (p == NULL) {
        return NULL;
    }
    else if ((cond = MemberNoCmp(x, &p->data)) == 0) {
        return p;
    }
    else if (cond < 0) {
        Search(p->left,x);
    }
    else
    {
        Search(p->right,x);
    }

}

BinNode *Add(BinNode *p, const Member *x) {
    int cond;
    if(p==NULL){
        p=AllocBinNode();
        setBinNode(p,x,NULL,NULL);
    }
    else if((cond= MemberNoCmp(x,&p->data))==0)
    {
        printf("[ERROR] %d는 이미 등록되어있습니다.\n",x->no);
    }
    else if (cond < 0) {
        p->left =Add(p-> left,x);
    }
    else
    {
        p->right= Add(p->right,x);
    }
}

/*--- 노드 삭제 ---*/
int Remove(BinNode **root, const Member *x)
{
    BinNode *next, *temp;
    BinNode **left;
    BinNode **p = root;

    while (1) {
        int cond;
        if (*p == NULL) {
            printf("【오류】 %d는 등록되어 있지 않습니다.\n", x->no);
            return -1;				/* 이 키는 없습니다. */
        }
        else if ((cond = MemberNoCmp(x, &(*p)->data)) == 0)
            break;					/* 검색 성공 */
        else if (cond < 0)
            p = &((*p)->left);		/* 왼쪽 서브 트리에서 검색 */
        else
            p = &((*p)->right);		/* 오른쪽 서브 트리에서 검색 */
    }

    if ((*p)->left == NULL)
        next = (*p)->right;
    else {
        left = &((*p)->left);
        while ((*left)->right != NULL)
            left = &(*left)->right;
        next = *left;
        *left = (*left)->left;
        next->left = (*p)->left;
        next->right = (*p)->right;
    }

    temp = *p;
    *p = next;

    free(temp);

    return 0;
}