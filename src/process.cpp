#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID

Process::Process(int pid){
    Process::Pid(pid);
}

void Process::Pid(int pid) { Process::pid_ = pid; }

int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
    vector<string> utilizations = LinuxParser::CpuUtilization();
    return std::stof(utilizations[0]) / (std::stof(utilizations[0]) + std::stof(utilizations[3])); 
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
// TODO: Check what to compare
bool Process::operator<(Process const& a) const { 
    if(Process::pid_ < a.pid_) { return true; }
    else { return false; } 
}