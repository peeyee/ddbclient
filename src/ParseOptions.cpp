#include "ParseOptions.h"
#include <string>
namespace po = boost::program_options;
extern string version;

ParseOptions::ParseOptions(){};

ParseOptions::~ParseOptions(){};

variables_map ParseOptions::parse(int argc, char* argv[]){

    po::options_description desc("DolphinDB client");
    desc.add_options()
        ("help", "show help message")
        ("host,h", "the ip/hostname connect to")
        ("port,p", "the port of DolphinDB node")
        ("username,u", "username")
        ("password", "password");
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    
    if(vm.count("help") || argc <= 4) cout<< desc << endl;
    if(vm.count("host")){
        cout<< "hostname is " << vm["host"].as<string>() << endl;
    }
    this.vm_ = vm;
}