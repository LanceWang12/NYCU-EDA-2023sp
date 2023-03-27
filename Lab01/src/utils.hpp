#pragma once
#include <csignal>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>

#include "FM.hpp"
using namespace std;

HyperGraph get_hypergraph(string in_filename);
void handle_file_not_found(string in_filename);