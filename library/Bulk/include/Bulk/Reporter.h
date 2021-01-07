#pragma once

#include <Bulk/Bulk.h>

#include <string>
#include <vector>
#include <iostream>

namespace bulk {

//------------------------------------
#pragma mark Forward declararions
//------------------------------------

// class Bulk;

//------------------------------------
#pragma mark Reporters declaration
//------------------------------------

/// \brief Interface for reporters
class PrintReport {
public:
    PrintReport() = default;

    explicit PrintReport(const std::string& delimiter);
    virtual void Print(const std::vector<std::string>&) const = 0;
    virtual ~PrintReport() = default;
protected:
    std::string delimiter_;
};

/// \brief Report to std::cout
class PrintReportDefault : public PrintReport {
public:
    PrintReportDefault() = default;

    PrintReportDefault(std::shared_ptr<Bulk> bulk, std::ostream& source = std::cout);
    ~PrintReportDefault() = default;
    void Print(const std::vector<std::string>&) const override;
private:
    std::ostream& source_ = std::cout;
};


/// \brief Report to file
class PrintReportToFile : public PrintReport {
public:
    PrintReportToFile() = default;
    
    PrintReportToFile(std::shared_ptr<Bulk> bulk);
    ~PrintReportToFile() = default;
    void Print(const std::vector<std::string>&) const override;
private:
    std::shared_ptr<Bulk> bulk_ = nullptr;
};

} // namespace bulk
