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
    return std::stof(utilizations[0]) / (std::stof(utilizations[0]) + std::stof(utilizations[3])); 
}

float Processor:Hertz() {
    float Hertz;
    std::ifstream stream("/proc" + "/" + "cpuinfo");
    while (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> attribute >> value;
        if(attribute == "cpu MHz"){
         Hertz = stof(value);
         return 1000000 * Hertz;
        }
    }

}