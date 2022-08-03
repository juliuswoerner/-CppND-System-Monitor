#include "processor.h"
#include "linux_parser.h"
#include <string>
#include <vector>
#include <iostream>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    vector<string> utilizations = LinuxParser::CpuUtilization();
    string test = utilizations.at(4);
    std::cout << test << std::endl;
    float test_float = std::stof("0.5");
    return test_float; 
}