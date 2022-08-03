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
    return 1 - (std::stof(utilizations[0]) / std::stof(utilizations[1])); 
}