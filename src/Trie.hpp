#include "lib.hpp"

typedef std::tuple<string, size_t, size_t> entry;

struct Node {
    std::unordered_map<char, Node*> children;
    Node* failure_link;
    std::unordered_set<string> dict_links;
    Node() {
        this->children = std::unordered_map<char, Node*>();
        this->failure_link = nullptr;
        this->dict_links = std::unordered_set<string>();
    }

    //  Children manipulation
    bool has_child(char key) {
        return (this->children.find(key) != this->children.end());
    }
    Node* get_child(char key) {
        return this->has_child(key) ? this->children[key] : nullptr;
    }
    void set_child(char key, Node* node) {
        this->children[key] = node;
    }

    //  Dictionary links
    void add_dict_link(string dict_link) {
        this->dict_links.insert(dict_link);
    }
    void copy_dict_links(Node* target) {
        for (string dict_link: target->dict_links)
            this->dict_links.insert(dict_link);    
    }
};


template<typename Collection>
class Trie {
protected:
    Node* Root;
    //  Add new pattern into the trie
    void add_pattern(string pattern) {
        Node *cur_node = Root;
        for (char key : pattern) {
            if (!(cur_node->has_child(key))) 
                cur_node->set_child(key, new Node());
            cur_node = cur_node->get_child(key);
        }
        cur_node->add_dict_link(pattern);
    }
    //  Create failure and dictionary links
    void InitializeLinks() {
        Node *cur_node;
        Root->failure_link = Root;
        std::queue<Node*> queue;
        //  '2nd layer' to the queue
        for (const auto& [_, c] : Root->children) {
            c->failure_link = Root;
            queue.push(c);
        }

        while(!queue.empty()) {
            cur_node = queue.front();
            queue.pop();     
            //  add next layer to the queue, while handling the parents    
            for (const auto& [key, child] : cur_node->children) {
                queue.push(child);

            /*  
            Trace back the failure link by searching until we:
                a) Find the Node with (key) as a child
                b) Get into a root self-loop
            */
                Node* Traceback = cur_node->failure_link;
                while (!Traceback->has_child(key) && (Traceback != Root)) 
                    Traceback = Traceback->failure_link;

                child->failure_link = 
                    Traceback->get_child(key) == nullptr 
                    ? Root 
                    : Traceback->get_child(key);    
                child->copy_dict_links(child->failure_link);
            }
        }
    }

public:
    Trie(Collection patterns) {
        this->Root = new Node();
        for (string pattern: patterns) 
            this->add_pattern(pattern);
        InitializeLinks();
    }

    
    std::vector<entry> search(string text) {
        std::vector<entry> found{};
        Node* state = Root;
        size_t i = 0;
        char c;
        while (i < text.size()) {
            c = text[i];
            if (state->has_child(c)) {
                state = state->get_child(c);
                ++i;

                if (!state->dict_links.empty()) 
                    for (string dict_link : state->dict_links) 
                        found.push_back(entry{ dict_link, i - dict_link.size(), i });                
            }
            else if (state == Root) 
                ++i;
            else 
                state = state->failure_link;
        }
        return found;
    }
};