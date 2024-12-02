//
// Created by Amaury Paillard on 02/12/2024.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

using report = std::vector<int>;

bool LoadListFromFile(const std::string& filename, std::vector<report>& reports) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error : unable to open file " << filename << std::endl;
    return false;
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    report single_report;
    int number;
    while (iss >> number) {
      single_report.push_back(number);
    }
    if (!single_report.empty()) {
      reports.push_back(single_report);
    }
  }

  file.close();
  return true;
}

bool IsSortedEitherWay(const std::vector<int>& vec) {
  return std::is_sorted(vec.begin(), vec.end()) ||
         std::is_sorted(vec.rbegin(), vec.rend());
}

bool CheckDifferences(const std::vector<int>& levels) {
  for (size_t i = 1; i < levels.size(); ++i) {
    if (const int diff = std::abs(levels[i] - levels[i - 1]); diff < 1 || diff > 3) {
      return false;
    }
  }
  return true;
}

bool IsReportSafe(const report& report) {
  return IsSortedEitherWay(report) && CheckDifferences(report);
}

bool CanBeDampened(const report& r) {
  for (size_t i = 0; i < r.size(); ++i) {
    report dampened_report = r;
    dampened_report.erase(dampened_report.begin() + static_cast<int>(i));
    if (IsReportSafe(dampened_report)) {
      return true;
    }
  }
  return false;
}


int main() {

  std::vector<report> reports;
  const auto start = std::chrono::high_resolution_clock::now();


  if(!LoadListFromFile("../day2Input.txt", reports)) {
    std::cerr << "Error : unable to load file " << std::endl;
  }

  int safeReportsAmount = 0;
  int safeReportsWithDampener = 0;

  for(const auto& report : reports) {
    if(IsReportSafe(report)) {
      ++safeReportsAmount;
    } else if (CanBeDampened(report)) {
      ++safeReportsWithDampener;
    }
  }

  const auto end = std::chrono::high_resolution_clock::now();
  const std::chrono::duration<double, std::milli> elapsed = end - start;


  std::cout  << "Total safe reports : " << safeReportsAmount << std::endl;
  std::cout << "Total safe reports with dampener: " << safeReportsWithDampener + safeReportsAmount << std::endl;
  std::cout << "Finished in: " << elapsed.count() << " ms" << std::endl;

  return 0;
}
