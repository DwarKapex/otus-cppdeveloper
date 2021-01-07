#include <Bulk/Reporter.h>
#include <Bulk/Bulk.h>

#include <gtest/gtest.h>
#include <sstream>
#include <algorithm>

using namespace bulk;

TEST(BulkReporter, PrintReporter) {
    {
        std::ostringstream received;
        PrintReportDefault a(nullptr, received);

        a.Print({});
        EXPECT_EQ("", received.str());
        a.Print({"1", "2"});
        EXPECT_EQ("bulk: 1, 2\n", received.str());
    }
    
    {
        constexpr size_t chunk = 3;
        auto bulk = std::make_shared<Bulk>(chunk);
        std::ostringstream received;
        PrintReportDefault a(bulk, received);

        a.Print({"0", "1"});
        EXPECT_EQ("bulk: 0, 1\n", received.str());
        received.str("");
        
        a.Print({"0", "1", "2", "3"});
        EXPECT_EQ("bulk: 0, 1, 2, 3\n", received.str());
    }
}

