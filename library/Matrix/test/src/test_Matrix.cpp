#include <Matrix/Matrix.h>

#include <gtest/gtest.h>
#include <string>
#include <sstream>

TEST(Matrix, OneDimentionalMatrix)
{
    constexpr int DefaultValue = -1;
    
    // non-const matrix
    Matrix::Matrix<int, DefaultValue, 1> m;

    EXPECT_EQ(m.size(), 0);
    auto a = m[0];
    EXPECT_EQ(m.size(), 0);
    EXPECT_EQ(a, DefaultValue);
    m[0] = 0;
    EXPECT_EQ(m.size(), 1);
    EXPECT_EQ(m[0], 0);
    EXPECT_EQ(m[1], DefaultValue);
    
    m[9] = 9;
    EXPECT_EQ(m[0], 0);
    EXPECT_EQ(m[1], DefaultValue);
    EXPECT_EQ(m[9], 9);
    EXPECT_EQ(m.size(), 2);
 
    std::string expected = "[ 0 ] : 0\n[ 9 ] : 9\n";
    std::stringstream str;
    for (const auto& item: m) {
        str << "[";
        for (const auto coord : item.first)
            str << " " << coord;
        str <<" ] : " << item.second << '\n';
    }
    EXPECT_EQ(expected, str.str());


    // const matrix -- no change available;
    const Matrix::Matrix<int, DefaultValue, 1> m_const;
    EXPECT_EQ(m_const.size(), 0);
    EXPECT_EQ(m_const[0], DefaultValue);
    EXPECT_EQ(m_const[1], DefaultValue);
    
    // Const matrix: construct from existing one (to pass to functions, for instance)
    const Matrix::Matrix<int, DefaultValue, 1> m_const2(m);
    EXPECT_EQ(m_const2.size(), 2);
    EXPECT_EQ(m_const2[0], 0);
    EXPECT_EQ(m_const2[1], DefaultValue);
    EXPECT_EQ(m_const2[9], 9);

    // const ref
    m[2] = 42;
    const auto& m_ref = m;
    EXPECT_EQ(m_ref.size(), 3);
    EXPECT_EQ(m_ref[0], 0);
    EXPECT_EQ(m_ref[1], DefaultValue);
    EXPECT_EQ(m_ref[9], 9);
    EXPECT_EQ(m_ref[2], 42);
}

TEST(Matix, TwoDimentionalMatrix) {
    constexpr int DefaultValue = -10;
    Matrix::Matrix<int, DefaultValue> m;
    
    EXPECT_EQ(m.size(), 0);
    
    auto a = m[0][0];
    EXPECT_EQ(a, DefaultValue);
    EXPECT_EQ(m.size(), 0); // expect still empty matrix
    
    m[100][100] = 314;
    EXPECT_EQ(m[100][100], 314);
    EXPECT_EQ(m.size(), 1);
    
    std::string expected = "[ 100 100 ] : 314\n";
    std::stringstream str;
    for (const auto& item: m) {
        str << "[";
        for (const auto coord : item.first)
            str << " " << coord;
        str <<" ] : " << item.second << '\n';
    }
    EXPECT_EQ(expected, str.str());

 
    // const matrix
    const Matrix::Matrix<int, DefaultValue> m_const;
    EXPECT_EQ(m_const.size(), 0);
    EXPECT_EQ(m_const[0][0], DefaultValue);
    EXPECT_EQ(m_const[0][1], DefaultValue);

    // Const matrix: construct from existing one (to pass to functions, for instance)
    const Matrix::Matrix<int, DefaultValue> m_const2(m);
    EXPECT_EQ(m_const2.size(), 1);
    EXPECT_EQ(m_const2[0][0], DefaultValue);
    EXPECT_EQ(m_const2[100][100], 314);
}


int main(int argc, char** argv) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}