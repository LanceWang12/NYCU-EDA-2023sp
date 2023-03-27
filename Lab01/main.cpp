#include <assert.h>

#include <cstdlib>
#include <ctime>
#include <string>

#include "src/FM.hpp"
#include "src/utils.hpp"

void get_hypergraph();

int main(int argc, char *argv[]) {
    srand(time(NULL));
    // -------- read hyperparameters and input file
    string in_filename, out_filename;
    int groups_num;
    double balance_factor;
    assert(argc == 4);
    in_filename = (string)argv[1];
    groups_num = stoi(argv[2]);
    balance_factor = stod(argv[3]);
    out_filename = (string) "out.hgr";
    // printf("%s, %d, %f\n", in_filename.c_str(), groups_num, balance_factor);
    HyperGraph graph;
    graph = get_hypergraph(in_filename);
    // cout << graph << endl;
    FM_Partition alg(balance_factor);
    alg.fit(graph);
    return 0;
}