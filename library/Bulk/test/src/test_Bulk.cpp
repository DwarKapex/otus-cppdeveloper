#include <Bulk/FormatUtil.h>
#include <Bulk/Bulk.h>
#include <Bulk/Reporter.h>

#include <gtest/gtest.h>

using namespace bulk;

TEST(Bulk, GeneralSequence) {
    std::stringstream cmds;

    cmds << "0\n1\n{\n2\n3\n4\n5\n6\n7\n8\n}\n9";
    constexpr size_t chunk = 3;
    auto bulk = std::make_shared<Bulk>(chunk);
    std::ostringstream received;
    PrintReportDefault a(bulk, received);
    cmds >> bulk;
    std::string expected = "bulk: 0, 1\nbulk: 2, 3, 4, 5, 6, 7, 8\nbulk: 9\n";
    EXPECT_EQ(expected, received.str());
}

TEST(Bulk, MultipleCurvedBraces) {
    std::stringstream cmds;
    cmds << "0\n1\n{\n2\n3\n{\n4\n5\n6\n}\n7\n8\n}\n9";
    constexpr size_t chunk = 3;
    auto bulk = std::make_shared<Bulk>(chunk);
    std::ostringstream received;
    PrintReportDefault a(bulk, received);

    cmds >> bulk;
    std::string expected = "bulk: 0, 1\nbulk: 2, 3, 4, 5, 6, 7, 8\nbulk: 9\n";
    EXPECT_EQ(expected, received.str());
}

TEST(Bulk, OpenCurvedBraces1) {
    std::stringstream cmds;
    cmds << "0\n1\n{\n2\n3\n{\n4\n5\n6\n7\n8\n9";
    constexpr size_t chunk = 3;
    auto bulk = std::make_shared<Bulk>(chunk);
    std::ostringstream received;
    PrintReportDefault a(bulk, received);
    cmds >> bulk;
    std::string expected = "bulk: 0, 1\n";
    EXPECT_EQ(expected, received.str());
}

TEST(Bulk, OpenCurvedBraces2) {
    std::stringstream cmds;
    cmds << "0\n1\n2\n3\n{\n4\n5\n6\n7\n8\n9";
    constexpr size_t chunk = 3;
    auto bulk = std::make_shared<Bulk>(chunk);
    std::ostringstream received;
    PrintReportDefault a(bulk, received);
    cmds >> bulk;
    std::string expected = "bulk: 0, 1, 2\nbulk: 3\n";
    
    EXPECT_EQ(expected,  received.str());
}

TEST(Bulk, OpenCurvedBraces3) {
    std::stringstream cmds;
    cmds << "0\n1\n2\n3\n{\n4\n5\n{6\n7\n8}\n9";
    constexpr size_t chunk = 3;
    auto bulk = std::make_shared<Bulk>(chunk);
    std::ostringstream received;
    PrintReportDefault a(bulk, received);
    cmds >> bulk;
    std::string expected = "bulk: 0, 1, 2\nbulk: 3\n";
    
    EXPECT_EQ(expected,  received.str());
}

TEST(Bulk, IncorrectInput) {
    std::stringstream cmds;
    cmds << "0\n1\n2\n3\n}\n4\n5\n6\n7\n8\n9";
    constexpr size_t chunk = 4;
    auto bulk = std::make_shared<Bulk>(chunk);
    std::ostringstream received;
    PrintReportDefault a(bulk, received);
    cmds >> bulk;
    std::string expected = "bulk: 0, 1, 2, 3\nbulk: 4, 5, 6, 7\nbulk: 8, 9\n";
    
    EXPECT_EQ(expected,  received.str());
}

TEST(Bulk, CrashTest1) {
    std::stringstream cmds;
    cmds << "{\n1\n}\n1";
    constexpr size_t chunk = 4;
    auto bulk = std::make_shared<Bulk>(chunk);
    std::ostringstream received;
    PrintReportDefault a(bulk, received);
    cmds >> bulk;
    std::string expected = "bulk: 1\nbulk: 1\n";
    
    EXPECT_EQ(expected,  received.str());
}

TEST(Bulk, CrashTest2) {
    std::stringstream cmds;
    cmds << "1\n{\n1\n}";
    constexpr size_t chunk = 4;
    auto bulk = std::make_shared<Bulk>(chunk);
    std::ostringstream received;
    PrintReportDefault a(bulk, received);
    cmds >> bulk;
    std::string expected = "bulk: 1\nbulk: 1\n";
    
    EXPECT_EQ(expected,  received.str());
}

TEST(Bulk, CmdWithParams) {
    std::stringstream cmds;
    cmds << "0 0\n{\n1 1\n}";
    constexpr size_t chunk = 4;
    auto bulk = std::make_shared<Bulk>(chunk);
    std::ostringstream received;
    PrintReportDefault a(bulk, received);
    cmds >> bulk;
    std::string expected = "bulk: 0 0\nbulk: 1 1\n";
    
    EXPECT_EQ(expected,  received.str());
}

TEST(Bulk, CmdWithParams2) {
    std::stringstream cmds;
    cmds << "0 0\n1 1\n2 2\n 3 3  \n { \n 1 1\n 2 2\n}\n 4 4";
    constexpr size_t chunk = 3;
    auto bulk = std::make_shared<Bulk>(chunk);
    std::ostringstream received;
    PrintReportDefault a(bulk, received);
    cmds >> bulk;
    std::string expected = "bulk: 0 0, 1 1, 2 2\nbulk: 3 3\nbulk: 1 1, 2 2\nbulk: 4 4\n";
    
    EXPECT_EQ(expected,  received.str());
}

TEST(Bulk, CmdWithParams3) {
    std::stringstream cmds;
    cmds << "0 0\n1 1\n2 2\n 3 3  \n { \n 1 1\n 2 2\n 4 4";
    constexpr size_t chunk = 3;
    auto bulk = std::make_shared<Bulk>(chunk);
    std::ostringstream received;
    PrintReportDefault a(bulk, received);
    cmds >> bulk;
    std::string expected = "bulk: 0 0, 1 1, 2 2\nbulk: 3 3\n";
    
    EXPECT_EQ(expected,  received.str());
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}