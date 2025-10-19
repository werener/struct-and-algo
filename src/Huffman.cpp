#include "lib.hpp"

struct Node {
    union { char c; char ch; char character; };
    union { ui64 f; ui64 freq; ui64 frequency; };
    union { Node *left = nullptr; Node *l;} ;
    union { Node *right = nullptr; Node *r;} ;

    Node(char c, ui64 f) { this->c = c; this->f = f; }

    Node(char c, ui64 f, Node *left, Node *right) {
        this->c = c; this->f = f; 
        this->left = left; this->right = right;
    }    
};

struct compare {
    bool operator()(Node *n1, Node *n2) {
        return n1->freq > n2->freq;
    }
};

void fill_codetable(Node *root, string current_code, std::unordered_map<char, string>& codetable) {
    if (root == nullptr)
        return;

    //  check for leaf
    if (!root->l && !root->r)
        codetable[root->character] = current_code;

    fill_codetable(root->l, current_code + "0", codetable);
    fill_codetable(root->r, current_code + "1", codetable);
}

Node* create_huffman_tree(string text) {
    std::unordered_map<char, ui64> frequency_map;
    for (char c : text)
        frequency_map[c]++;

    std::priority_queue<Node*, std::vector<Node*>, compare> pq;
    for (auto char_freq : frequency_map)
        pq.push(new Node(char_freq.first, char_freq.second));
    
    while (pq.size() != 1) {
        Node *left = pq.top();  pq.pop();
        Node *right = pq.top(); pq.pop();
        
        ui64 sum = left->freq + right->freq;
        pq.push(new Node('\0', sum, left, right));
    }
    Node *root = pq.top();
    return root;
}

std::unordered_map<char, string> create_codetable(Node *root) {
    std::unordered_map<char, string> codetable;
    fill_codetable(root, "", codetable);
    return codetable;
}


string encode(string data, Node *root=nullptr) {
    if (root == nullptr) 
        root = create_huffman_tree(data);
    std::unordered_map<char, string> table = create_codetable(root);

    string encoded_data = "";
    for (char c : data) 
        encoded_data += table[c];
    return encoded_data;
};

string decode(string encoded_data, Node *root) {
    Node *cur = root;
    string decoded_data = "";
    for (char bit : encoded_data) {
        if (bit == '0') 
            cur = cur->left;
        else 
            cur = cur->right;
        
        if (!cur->left && !cur->right) {
            decoded_data.push_back(cur->character);
            cur = root;
        }
    }
    return decoded_data;
};
