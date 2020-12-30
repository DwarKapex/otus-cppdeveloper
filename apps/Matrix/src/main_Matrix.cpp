/**
 * \brief Main application
 */
#include <iostream>
#include <Matrix/Matrix.h>



int main() {
    constexpr int def_value = 0;
    Matrix::Matrix<int, def_value, 2> matrix;
    const int N = 10;
    
    auto a = matrix[0][0];
    
    for (int i = 0; i < N; ++i)
        matrix[i][i] = matrix[N-1-i][i] = i;

    for (int row = 1; row <= 8; ++row) {
        for (int col = 1; col <= 8; ++col){
            std::cout << matrix[row][col];
            col == 8 ? std::cout << std::endl : std::cout << " ";
        }
    }
    std::cout << matrix.size() << std::endl;
    
    for (const auto& [key, value]: matrix){
        std::string t;
        for (const auto& c: key) {
            t += std::to_string(c) + " ";
        }
        t = t.substr(0, t.size()-1);
        std::cout << "[" <<  t << "] : " << value << std::endl;
    }
}
