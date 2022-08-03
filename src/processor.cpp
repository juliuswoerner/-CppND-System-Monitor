#include "processor.h"
#include "linux_parser.h"
#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    vector<string> utilizations = LinuxParser::CpuUtilization();
    string test = utilizations.at(4);
    float test_float = std::stof(utilizations[4]);
    return test_float; 
}