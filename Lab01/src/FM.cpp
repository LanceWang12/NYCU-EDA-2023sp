#include "FM.hpp"

void FM_Partition::fit(const HyperGraph &g) {
    graph = g;
    nlst = NetLst(graph);
    clst = CellLst(graph);
}

void FM_Partition::initial_partition() {
}