#include "solution.cpp"

int main() {    
    /*  Indexation  */

    std::cout << string(29, '-') << std::endl;    
    std::vector<std::vector<ui64>> a(10, std::vector<ui64>(10,0));
    for (int i = 0; i < 10; ++i) 
        for (int j = 0; j < 10; ++j) 
            a[i][j] = 10 * i + j;
        
    std::cout << "ij" << "\n";
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 10; ++j) 
            (a[i][j] < 10) ? std::cout << 0 << a[i][j] << " " : std::cout << a[i][j] << " ";
        std::cout << std::endl;    
    }
  
    /*  Grid structure  */
    /*
        o's are nodes
        spaces are 'squares'
        arrows are 'streets'
    */
   
    std::cout << string(29, '-') << std::endl;  
    std::vector<std::vector<char>> test = 
    {
        { 'o', '>', 'o', '>', 'o', '>', 'o', '>', 'o', '>', 'B', },
        { '^', ' ', '^', ' ', '^', ' ', '^', ' ', '^', ' ', '^', },
        { 'o', '>', 'o', '>', 'o', '>', 'o', '>', 'o', '>', 'o', },
        { '^', ' ', '^', ' ', '^', ' ', '^', ' ', '^', ' ', '^', },
        { 'o', '>', 'o', '>', 'o', '>', 'o', '>', 'o', '>', 'o', },
        { '^', ' ', '^', ' ', '^', ' ', '^', ' ', '^', ' ', '^', },
        { 'o', '>', 'o', '>', 'o', '>', 'o', '>', 'o', '>', 'o', },
        { '^', ' ', '^', ' ', '^', ' ', '^', ' ', '^', ' ', '^', },
        { 'A', '>', 'o', '>', 'o', '>', 'o', '>', 'o', '>', 'o', },
    };
    print_matrix(test);
    
    /*  Test */
    std::cout << string(29, '-') << std::endl;    

    grid_type test_data = 
    {
        { Node(0, 1), Node(1, 1), Node(1, 1), Node(1, 1), Node(1, 1), Node(1, 1) },
        { Node(0, 1), Node(1, 1), Node(1, 1), Node(1, 1), Node(1, 1), Node(1, 1) },
        { Node(0, 1), Node(1, 1), Node(1, 1), Node(1, 1), Node(1, 1), Node(1, 1) },
        { Node(0, 1), Node(1, 1), Node(1, 1), Node(1, 1), Node(1, 1), Node(1, 1) },
        { Node(0, 0), Node(1, 0), Node(1, 0), Node(1, 0), Node(1, 0), Node(1, 0) },
    };
    ui64 res = find_optimal_path(test_data);
}