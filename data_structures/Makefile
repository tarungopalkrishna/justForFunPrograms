CC=g++
CPPFLAGS=-Werror


binarysearch:
	$(CC) -Wall -Wextra -Wpedantic -std=c++11 -o binary_search binary_search.cpp

btree:
	$(CC) -Wall -Wextra -Wpedantic -std=c++11 -o btree btree.cpp

itreetraversal:
	$(CC) -Wall -Wextra -Wpedantic -std=c++11 -Lbtree -o inorder_tree_traversal inorder_tree_traversal.cpp

clean:
	rm -f binary_search
	rm -f btree
