#if !defined(VX3_SIMULATION_MANAGER)
#define VX3_SIMULATION_MANAGER

#include <iostream>
#include <thread>
#include <utility> 
#include <vector>
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
namespace pt = boost::property_tree;

#include "VX3_VoxelyzeKernel.h"

class VX3_SimulationManager
{
private:
    /* data */
public:
    VX3_SimulationManager(fs::path input, fs::path output);
    ~VX3_SimulationManager();

    void start();
    void readVXA(std::vector<fs::path> files, int batch_index);
    std::vector<std::vector<fs::path>> splitIntoSubBatches();
    void startKernel(int num_tasks, int batch_index);
    void writeResults(int num_tasks);

    /* DATA */
    int num_of_devices;
    VX3_VoxelyzeKernel* d_voxelyze_3;
    fs::path input_directory;
    fs::path output_file;
    std::vector<cudaStream_t> streams;

};

#endif // VX3_SIMULATION_MANAGER
