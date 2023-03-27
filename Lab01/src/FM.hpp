#pragma once
#include <omp.h>

#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <vector>

using namespace std;

// row: node number, col: cell number
class HyperGraph {
   private:
    bool **data;
    int row, col;

   public:
    HyperGraph() : col(0), row(0) {}

    HyperGraph(int nets, int nodes) : col(nets), row(nodes) {
        data = new bool *[row];
        for (int i = 0; i < row; i++) {
            data[i] = new bool[col];
            for (int j = 0; j < col; j++)
                data[i][j] = false;
        }
    }

    HyperGraph(HyperGraph const &rhs) : row(rhs.row), col(rhs.col) {
        // cout << "copy" << endl;
        data = new bool *[row];
        for (int i = 0; i < row; i++) {
            data[i] = new bool[col];
            for (int j = 0; j < col; j++)
                data[i][j] = rhs(i, j);
        }
    }

    ~HyperGraph() {
        for (int i = 0; i < row; i++)
            delete[] data[i];
        delete[] data;
        row = 0;
        col = 0;
    }

    // HyperGraph(HyperGraph &&rhs) : row(rhs.row), col(rhs.col) {
    //     data = new bool *[row];
    //     for (int i = 0; i < row; i++) {
    //         data[i] = new bool[col];
    //         for (int j = 0; j < col; j++)
    //             data[i][j] = false;
    //     }
    // }

    HyperGraph &operator=(HyperGraph const &rhs) {
        // cout << "====" << endl;
        if (this != &rhs) {
            row = rhs.row;
            col = rhs.col;
            data = new bool *[row];
            for (int i = 0; i < row; i++) {
                data[i] = new bool[col];
                for (int j = 0; j < col; j++)
                    data[i][j] = rhs(i, j);
            }
        }
        return *this;
    }

    // HyperGraph &operator=(HyperGraph &&rhs) {
    //     if (this != &rhs) {
    //         *this = move(rhs);
    //     }

    //     return *this;
    // }

    bool const &operator()(size_t i, size_t j) const {
        return this->data[i][j];
    }

    bool &operator()(size_t i, size_t j) {
        return this->data[i][j];
    }

    friend ostream &operator<<(ostream &os, const HyperGraph &graph) {
        os << "HyperGraph: (" << graph.row << ", " << graph.col << ")" << endl;
        for (int row = 0; row < graph.row; row++) {
            for (int col = 0; col < graph.col; col++)
                os << std::setprecision(4) << std::fixed << graph(row, col) << " ";

            if (row != graph.row - 1)
                os << endl;
        }

        return os;
    }

    friend class NetLst;
    friend class CellLst;
};

class CellLst {
   private:
    int nets_num, cell_num, p_max;
    vector<vector<int>> lst;

   public:
    CellLst() : nets_num(0), cell_num(0), p_max(0) {}

    CellLst(const HyperGraph &graph) : nets_num(graph.col), cell_num(graph.row), p_max(0) {
        for (int i = 0; i < cell_num; i++) {
            vector<int> tmp;
            for (int j = 0; j < nets_num; j++) {
                if (graph(i, j))
                    tmp.push_back(j);
            }
            if (p_max < tmp.size()) p_max = tmp.size();
            lst.push_back(tmp);
        }
    }

    friend ostream &operator<<(ostream &os, const CellLst &celllst) {
        os << "CellLst: (" << celllst.cell_num << ", " << celllst.nets_num << ")" << endl;
        for (int row = 0; row < celllst.cell_num; row++) {
            for (int col = 0; col < celllst.lst[row].size(); col++)
                os << std::setprecision(4) << std::fixed << celllst.lst[row][col] << " ";

            if (row != celllst.cell_num - 1)
                os << endl;
        }

        return os;
    }

    friend class FM_Partition;
};

class NetLst {
   private:
    int nets_num, cell_num;
    vector<vector<int>> lst;

   public:
    NetLst() : nets_num(0), cell_num(0) {}

    NetLst(const HyperGraph &graph) : nets_num(graph.col), cell_num(graph.row) {
        for (int i = 0; i < nets_num; i++) {
            vector<int> tmp;
            for (int j = 0; j < cell_num; j++) {
                if (graph(j, i))
                    tmp.push_back(j);
            }
            lst.push_back(tmp);
        }
    }

    friend ostream &operator<<(ostream &os, const NetLst &netslst) {
        os << "NetsLst: (" << netslst.nets_num << ", " << netslst.cell_num << ")" << endl;
        for (int row = 0; row < netslst.nets_num; row++) {
            for (int col = 0; col < netslst.lst[row].size(); col++)
                os << std::setprecision(4) << std::fixed << netslst.lst[row][col] << " ";

            if (row != netslst.nets_num - 1)
                os << endl;
        }

        return os;
    }
};

class FM_Partition {
   private:
    // Hyperparameters
    double balance_factor;

    // Internal Data structures
    map<int, list<int>> left, right;
    HyperGraph graph;
    NetLst nlst;
    CellLst clst;

    void initial_partition();

   public:
    FM_Partition() : balance_factor(1) {}
    FM_Partition(double f) : balance_factor(f) {}

    void fit(const HyperGraph &g);
};