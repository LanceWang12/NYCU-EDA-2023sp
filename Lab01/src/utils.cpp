#include "utils.hpp"

HyperGraph get_hypergraph(string in_filename) {
    ifstream input_fp;
    ofstream output_fp;
    input_fp.open(in_filename);
    string tmp_string;
    int nets_num, nodes_num, tmp;
    stringstream ss;
    if (input_fp.is_open()) {
        input_fp >> nets_num >> nodes_num;
        input_fp.get();  // remove '\n'
        HyperGraph graph(nets_num, nodes_num);
        for (int i = 0; i < nets_num; i++) {
            getline(input_fp, tmp_string);
            ss << tmp_string;
            while (ss >> tmp) {
                graph(tmp - 1, i) = true;
            }
            ss.clear();
        }
        // cout << graph << endl;
        input_fp.close();
        return graph;
    } else {
        handle_file_not_found(in_filename);
    }
    return HyperGraph(0, 0);
}

void handle_file_not_found(string in_filename) {
    printf("File: %s not found...\n", in_filename.c_str());
    exit(1);
}