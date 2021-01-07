/**
 * \brief Class Bulk Declaration
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <ctime>
#include <memory>


namespace bulk {

//------------------------------------
#pragma mark Forward Declaration
//------------------------------------

class PrintReport;


//------------------------------------
#pragma mark Main Bulk class declaration
//------------------------------------

/// \brief Main class to work with input commands
class Bulk {
public:
    Bulk();
    explicit Bulk (const size_t chunk);
    
    friend std::istream& operator>>(std::istream& input, std::shared_ptr<Bulk> bulk);
    
    void AddReporter(std::shared_ptr<PrintReport>);
    
    void Process(std::string cmd);
    void ChopInput(std::string cmd);
    void AgregateInput(std::string cmd);
    
    std::time_t GetTimestamp() const;
    
    void DoReport();

private:
    enum class BehaviourStatus {
        Separate,
        AllinOne
    };

    BehaviourStatus status_ = BehaviourStatus::Separate;
    const size_t chunk_size_ = 1;
    std::vector<std::string> command_package_;
    std::queue<char> braces_balancer_;
    std::vector<std::shared_ptr<PrintReport>> reporters_;
    std::time_t timestamp_;
};

} // namespace bulk