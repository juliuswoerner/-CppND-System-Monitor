#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "system.h"
#include "process.h"
#include "processor.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  float max_memory = 0.0, free_memory = 0.0;
  string attribute, value, line;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  while (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> attribute >> value;
    if(attribute == "MemTotal:"){
      max_memory = stof(value);
    }
    else if(attribute == "MemFree:"){
      free_memory = stof(value);
    }
    else if(max_memory != 0.0 && free_memory != 0.0){ return 1.0 - (free_memory / max_memory); }
  }
  return 0.0; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  long up_time;
  string line, start, end;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> start >> end;
    up_time = stol(end) - stol(start);
  }
  return up_time; 
  }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { return pid; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> cpu_utilizations;
  string cpu[5]={"","","","",""};
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu[0] >> cpu[1] >> cpu[2] >> cpu[3] >> cpu[4];
    for(int i=1; i<5; i++){
      cpu_utilizations.push_back(cpu[i]);
    }
    return cpu_utilizations;
  }
  return cpu_utilizations; 
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string attribute, value, line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  while (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> attribute >> value;
    if(attribute == "processes"){
      return stoi(value);
    }
  }
  return 0; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string attribute, value, line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  while (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> attribute >> value;
    if(attribute == "procs_running"){
      return stoi(value);
    }
  }
  return 0; 
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string command, line;
  std::ifstream stream(kProcDirectory + "/" + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> command;
  }
  return command; 
  }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { return std::to_string(pid); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { return std::to_string(pid); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { return std::to_string(pid); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { return pid; }
