#include <Bulk/Bulk.h>
#include <Bulk/Reporter.h>
#include <Bulk/FormatUtil.h>

#include <memory>
#include <iostream>
#include <fstream>

namespace bulk{

//------------------------------------------
#pragma mark Interface for Reporter Implementation
//------------------------------------------

PrintReport::PrintReport(const std::string& delim):
    delimiter_(delim) {}

//------------------------------------------
#pragma mark Default Reporter Implementation
//------------------------------------------

                 // PrintReportDefault(std::shared_ptr<Bulk> bulk, std::ostream& source_);
PrintReportDefault::PrintReportDefault(std::shared_ptr<Bulk> bulk, std::ostream& source):
      PrintReport(", ")
    , source_(source) {
    if (bulk) {
        bulk->AddReporter(std::make_shared<PrintReportDefault>(*this));
    }
}

void PrintReportDefault::Print(const std::vector<std::string>& value) const  {
    if (!value.empty()) {
        std::string result = "bulk: ";
        result += FormatUtil::Format(value, delimiter_);
        source_ << result << std::endl;
    }
}

//------------------------------------------
#pragma mark Report to file Implementation
//------------------------------------------

PrintReportToFile::PrintReportToFile(std::shared_ptr<Bulk> bulk):
      PrintReport("\n")
    , bulk_(bulk) {
    if (bulk) {
        bulk_->AddReporter(std::make_shared<PrintReportToFile>(*this));
    }
}

void PrintReportToFile::Print(const std::vector<std::string>& value) const {
    if (!value.empty()) {
        std::ofstream file;
        file.open("bulk" + std::to_string(bulk_->GetTimestamp()) + ".log");
        if (file.is_open()){
            file << FormatUtil::Format(value, delimiter_);
        }
        file.close();
    }
}

} //namespace bulk
