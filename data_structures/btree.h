class BTreeNode {
public:
    int key;
    BTreeNode *left, *right;
    BTreeNode(int k) {
        key = k;
        left = right = nullptr;
    }

    // Insert element into the tree
    void insert(int k) {
        if (k < key) {
            if (left == nullptr) {
                left = new BTreeNode(k);
            } else {
                left->insert(k);
            }
        } else {
            if (right == nullptr) {
                right = new BTreeNode(k);
            } else {
                right->insert(k);
            }
        }
    }

    // Delete element from the tree
    void remove(int k) {
        if (k < key) {
            if (left != nullptr) {
                left->remove(k);
            }
        } else if (k > key) {
            if (right != nullptr) {
                right->remove(k);
            }
        } else {
            if (left != nullptr && right != nullptr) {
                key = right->minValue();
                right->remove(key);
            } else if (left != nullptr) {
                BTreeNode *temp = left;
                left = right;
                right = temp;
            } else if (right != nullptr) {
                BTreeNode *temp = right;
                right = left;
                left = temp;
            } else {
                key = 0;
            }
        }
    }


    // Find the minimum value in the tree
    int minValue() {
        if (left == nullptr) {
            return key;
        } else {
            return left->minValue();
        }
    }
};


// int main(int argc, char *argv[]){
    // BTreeNode *root = new BTreeNode(10);
    // root->insert(5);
    // root->insert(15);
    // root->insert(2);
    // root->insert(7);
    // root->insert(13);
    // root->insert(17);
    // root->insert(1);
    // root->insert(3);
    // root->insert(6);
    // root->insert(8);
//     root->insert(11);
//     root->insert(14);
//     root->insert(16);
//     root->insert(18);
//     root->insert(4);
//     root->insert(9);
//     root->insert(12);
//     root->insert(19);
//     root->insert(20);
//     root->insert(21);
//     root->insert(22);
//     root->insert(23);
//     root->insert(24);
//     root->insert(25);
//     root->insert(26);
//     root->insert(27);
//     root->insert(28);
//     root->insert(29);
//     root->insert(30);
// }