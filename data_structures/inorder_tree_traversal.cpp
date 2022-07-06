#include<btree.h>


int main(){
    BTreeNode *root = new BTreeNode(10);
    root->insert(5);
    root->insert(15);
    root->insert(2);
    root->insert(7);
    root->insert(13);
    root->insert(17);
    root->insert(1);
    root->insert(3);
    root->insert(6);
    root->insert(8);
}




