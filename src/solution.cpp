#include "lib.hpp"

template <typename T>
void print_matrix(T matrix) {
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[0].size(); ++j) 
            std::cout << matrix[i][j] << " ";
        std::cout << std::endl;    
    }
}

struct Node {
    union { ui64 least_time=0; ui64 t; };
    union { ui16 from_south; ui16 fs;};
    union { ui16 from_west; ui16 fw; };
    Node(ui16 fw_, ui16 fs_) {from_south = fs_; from_west = fw_;}

    friend std::ostream& operator<<(std::ostream& os, const Node& obj) {
        os << obj.t;
        return os;
    }
};

typedef std::vector<std::vector<Node>> grid_type;



ui64 find_optimal_path(grid_type grid) {
    //  [lh-1][0] is A     [0][lw-1] is B
    int lh = grid.size();
    int lw = grid[0].size();

    //  paths along border can be visited only one way
    grid[lh - 1][0].t = 0;  //  A
    for (int i = lh - 2; i >= 0; --i)   //  east border
        grid[i][0].least_time = grid[i + 1][0].t + grid[i][0].fs; 
    
    for (int j = 1; j < lw; ++j)        //  south border
        grid[lh - 1][j].least_time = grid[lh - 1][j - 1].t + grid[lh - 1][j].fw;

    //  dynamically updating every cells' fastest route 
    for (int i = lh - 2; i >= 0; --i) {
        for (int j = 1; j < lw; ++j) {
            Node *current = &grid[i][j];
            ui64 from_south = grid[i + 1][j].t + current->fs;
            ui64 from_west = grid[i][j - 1].t + current->fw;

            current->least_time = (from_south < from_west) ? from_south : from_west;
        }
    }
    std::cout << string(lw / 2, ' ') << lw << " x " << lh << '\n';
    print_matrix(grid);
    std::cout << "Answer:\t" << grid[0][lw - 1].least_time << std::endl;
    return grid[0][lw - 1].least_time;
}


