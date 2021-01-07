#include <Bulk/FormatUtil.h>

#include <gtest/gtest.h>

using namespace bulk::FormatUtil;

TEST(BulkFormatUtil, Format) {
    EXPECT_EQ("", Format({}, ""));

    std::vector<std::string> v{"cmd1", "cmd2"};
    EXPECT_EQ("cmd1, cmd2", Format(v, ", "));
}

TEST(BulkFormatUtil, StripStringTest) {
    std::string s = " 1123   ";
    StripString(s);
    EXPECT_EQ("1123", s);

    s = " 11{ 2 3   ";
    StripString(s);
    EXPECT_EQ("11{ 2 3", s);
}
