#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <filesystem>

static const int NUM = 1000000;

void writeToFile(std::filesystem::path fileName, const std::map<int, int> &data) {

    std::ofstream file(fileName);

    if (!file) {
        std::cerr << "Could not open the file " << fileName << ".";
        exit(EXIT_FAILURE);
    }

    // print the datapoints to the file
    for (auto mapIt: data) file << mapIt.first << " " << mapIt.second << std::endl;

}

int random() {


    std::filesystem::path pathName =
            std::filesystem::current_path().parent_path() / "AdvancedCPP" / "Part6"; // change file path if necessary

    std::random_device seed;

    // default generator
    std::mt19937 engine(seed());

    // distributions

    // min= 0; max= 20
    std::uniform_int_distribution<> uniformDist(0, 20);
    // mean= 50; sigma= 8
    std::normal_distribution<> normDist(50, 8);
    // mean= 6;
    std::poisson_distribution<> poiDist(6);
    // alpha= 1;
    std::gamma_distribution<> gammaDist;

    std::map<int, int> uniformFrequency;
    std::map<int, int> normFrequency;
    std::map<int, int> poiFrequency;
    std::map<int, int> gammaFrequency;

    for (int i = 1; i <= NUM; ++i) {
        ++uniformFrequency[uniformDist(engine)];
        ++normFrequency[round(normDist(engine))];
        ++poiFrequency[poiDist(engine)];
        ++gammaFrequency[round(gammaDist(engine))];
    }

    writeToFile(pathName / "uniform_int_distribution.txt", uniformFrequency);
    writeToFile(pathName / "normal_distribution.txt", normFrequency);
    writeToFile(pathName / "poisson_distribution.txt", poiFrequency);
    writeToFile(pathName / "gamma_distribution.txt", gammaFrequency);
    return 0;
}