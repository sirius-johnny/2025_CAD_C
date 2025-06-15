#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <limits.h>
#include <algorithm>

int main() {
    std::ifstream infile("../testcase/aes_cipher_top/aes_cipher_top.nets");
    // aes_cipher_top.nets //
    // #_NETs = 10177
    // MAX_DEGREE = 531
    // MIN_DEGREE = 2
    // AVG_DEGREE = 3.70876
    // MED_DEGREE = 2

    std::string line;
    std::unordered_map<std::string, int> netDegrees;
    std::vector<int> degrees;

    int maxDegree = INT_MIN;
    int minDegree = INT_MAX;
    float avgDegree = 0;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string token;

        if (line.find("NetDegree") != std::string::npos) {
            // Line format: NetDegree : 531 clk
            std::string label;
            int degree;
            std::string netName;

            iss >> label >> token >> degree >> netName;
            netDegrees[netName] = degree;
            degrees.push_back(degree);
            avgDegree += degree;
            maxDegree = (degree>maxDegree)? degree: maxDegree;
            minDegree = (degree<minDegree)? degree: minDegree;
        }
    }

    std::cout << "#_NETs = " << netDegrees.size() <<std::endl;
    std::cout << "MAX_DEGREE = " << maxDegree <<std::endl;
    std::cout << "MIN_DEGREE = " << minDegree <<std::endl;
    std::cout << "AVG_DEGREE = " << avgDegree/netDegrees.size() <<std::endl;
    
    std::sort(degrees.begin(), degrees.end());
    int deSize = degrees.size();
    if(deSize%2){
        std::cout << "MED_DEGREE = " << degrees[deSize/2] <<std::endl;
    }
    else{
        std::cout << "MED_DEGREE = " << 0.5*(degrees[deSize/2-1]+degrees[deSize/2]) <<std::endl;
    }

    // Print results
    // for (const auto& entry : netDegrees) {
    //     std::cout << entry.first << " : " << entry.second << std::endl;
    // }

    return 0;
}
