#include "lib.hpp"

struct Node {
    char value;
    Node* left = nullptr;
    Node* right = nullptr;
    Node() {};
    Node(char value) {  this->value = value;  } 
    bool is_leaf() {    return (left == nullptr && right == nullptr);   } 
};

struct Tree {
protected:
    Node* root = nullptr;

    Node* createNode(char value) {
        Node* newNode = new Node();
        newNode->value = value;
        newNode->left = newNode->right = nullptr;
        return newNode;
    }

    Node* insert_private(Node* cur, char value) {
        if (cur == nullptr)             
            return createNode(value);
        if (value < cur->value) 
            cur->left = insert_private(cur->left, value);
        else if (value > cur->value) 
            cur->right = insert_private(cur->right, value);
        return cur;
    }
    
    void traverse_private(Node* cur) {
        if (cur != nullptr) {
            traverse_private(cur->left);
            if (cur->value == '\t') 
                std::cout << "\\t";
            else if (cur->value == 0) 
                std::cout << "\\0";
            else
                std::cout << cur->value;
            std::cout << "(" << (int)cur->value << ") ";
            traverse_private(cur->right);
        }
    }

    ui64 sum_of_leaves_private(Node* cur) {
        if (cur == nullptr)
            return 0;

        ui64 s = cur->value;
        //  if cur isnt leaf, we need to add sum from his children
        if (!cur->is_leaf()) 
            s += sum_of_leaves_private(cur->left) + sum_of_leaves_private(cur->right);
        return s;
    }
    
    ui64 height_private(Node* cur) {
        if (cur == nullptr) 
            return 0;
        int dl = height_private(cur->left), dr = height_private(cur->right);
        return (1 + (dl > dr ? dl : dr));
    }

    void print_private(const std::string& prefix, const Node* node, bool isLeft) {
        if( node != nullptr ) {
            std::cout << prefix << (isLeft ? "├──" : "└──" );
            if (node->value == '\t')
                std::cout << "\\t";
            else if (node->value == 0)
                std::cout << "\\0";
            else
                std::cout << node->value;

            std::cout << "("<< (int)node->value << ")" << std::endl;
            print_private( prefix + (isLeft ? "│     " : "      "), node->left, true);
            print_private( prefix + (isLeft ? "│     " : "      "), node->right, false);
        }
    }
    
public:
    Tree(){}

    Tree(char value) {  root = new Node(value); }

    Tree(string values) {
        root = new Node(values[0]);
        for (int i = 1; i < values.length(); ++i)
            this->insert(values[i]);
    }    

    void insert(char value) {
        root = insert_private(root, value);
    }
    void traverse() {
        traverse_private(root);
        std::cout << std::endl;
    }
    ui64 sum_of_leaves() {
        return sum_of_leaves_private(root);
    }
    int height() {
        return height_private(root);
    }
    void print() {
        print_private("", root, false);
        std::cout << std::endl;
    }
};