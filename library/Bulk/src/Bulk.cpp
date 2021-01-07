/**
 * \brief main library
 *
 */

#include <Bulk/Bulk.h>
#include <Bulk/Reporter.h>
#include <Bulk/FormatUtil.h>

#include <iostream>
#include <string>
#include <algorithm>

namespace bulk {

//---------------------------------
#pragma mark Bulk Implementation
//---------------------------------

Bulk::Bulk() = default;

Bulk::Bulk(const size_t chunk_size):
    chunk_size_(chunk_size) {
}

void Bulk::Process(std::string cmd) {
    FormatUtil::StripString(cmd);
    if (cmd == "{") {
        if (braces_balancer_.empty()){
            DoReport();
        }
        braces_balancer_.push('{');
        status_ = BehaviourStatus::AllinOne;
    }
    else if (cmd == "}"){
        if (!braces_balancer_.empty())
            braces_balancer_.pop();
        
        if (braces_balancer_.empty()) {
            DoReport();
            status_ =  BehaviourStatus::Separate;
        }
    }
    else {
        if (command_package_.empty()) {
            timestamp_ = std::time(0);
        }
        switch (status_) {
            case BehaviourStatus::Separate:
                ChopInput(std::move(cmd));
                break;
            case BehaviourStatus::AllinOne:
                AgregateInput(std::move(cmd));
                break;
        }
    }
}

void Bulk::ChopInput(std::string cmd) {
    if (chunk_size_ == command_package_.size()) {
        DoReport();
        timestamp_ = std::time(0);
    }
    command_package_.push_back(cmd);
}

void Bulk::AgregateInput(std::string cmd) {
    command_package_.push_back(cmd);
}

void Bulk::DoReport() {
    if (braces_balancer_.empty()) {
        for (const auto& reporter: reporters_)
            reporter->Print(command_package_);
    }
    command_package_.clear();
}
              
std::time_t Bulk::GetTimestamp() const {
        return timestamp_;
}
              
void Bulk::AddReporter(std::shared_ptr<PrintReport> new_reporter) {
    if (new_reporter) {
        reporters_.push_back(new_reporter);
    }
}

std::istream& operator>>(std::istream& input, std::shared_ptr<Bulk> bulk) {
    std::string cmd;
    while (std::getline(input, cmd)) {
        FormatUtil::StripString(cmd);
        bulk->Process(cmd);
    }
    // for the last input
    bulk->DoReport();
    return input;
}

} // namespace bulk