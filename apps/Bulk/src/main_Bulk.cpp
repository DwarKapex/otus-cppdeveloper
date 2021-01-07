/**
 * \brief Main application
 */
#include <iostream>
#include <Bulk/Bulk.h>
#include <Bulk/Reporter.h>


int main(int arg, char**args) {
    if (arg !=2) {
        std::cerr << "Wrong number of params. It should be exactly 1, but " << arg - 1 << " provided\n";
        return -1;
    }
    
    auto bulk = std::make_shared<bulk::Bulk>(std::atoi(args[1]));
    bulk::PrintReportDefault a(bulk);
    bulk::PrintReportToFile b(bulk);

    std::cin >> bulk;

    return 0;
}
