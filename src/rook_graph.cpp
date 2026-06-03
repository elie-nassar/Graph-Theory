#include "rook_graph.hpp"

int convert(int x,int y,int n) {
    return y*n+x;
}

int getX(int u,int n) {
    return std::floor(u/n);
}

int getY(int u,int n) {
    return u%n;
}

rook_graph::rook_graph(int n) : n(n) {
    directed=false;
    adjacency_list = std::vector<std::set<int>>(n*n,std::set<int>{});
    for(int uy=0;uy<n;uy++) {
        for(int ux=0;ux<n;ux++) {
            for(int v=uy+1;v<n;v++) add_edge(convert(ux,uy,n),convert(ux,v,n));
            for(int v=ux+1;v<n;v++) add_edge(convert(ux,uy,n),convert(v,uy,n));
        }
    }
}

rook_graph rook_graph::random_directed(int n) {
    rook_graph R(n);
    R.directed=true;
    for(int uy=0;uy<n;uy++) {
        for(int ux=0;ux<n;ux++) {
            for(int v=uy+1;v<n;v++) if(rand()%2==0) R.remove_edge(convert(ux,uy,n),convert(ux,v,n)); else R.remove_edge(convert(ux,v,n),convert(ux,uy,n));
            for(int v=ux+1;v<n;v++) if(rand()%2==0) R.remove_edge(convert(ux,uy,n),convert(v,uy,n)); else R.remove_edge(convert(v,uy,n),convert(ux,uy,n));
        }
    }
    return R;
}

std::string rook_graph::to_dot(const std::vector<int> &coloring) const{
    std::string s = directed ? "digraph {\n" : "graph {\n";
    s+="splines=true;\noverlap=false;\n";
    for(int u=0;u<(int)adjacency_list.size();u++) {
        s+= "  " + std::to_string(u)+" [";
        if(!coloring.empty()) s+= "fillcolor=\"/rdbu11/"+std::to_string(coloring[u]) + "\" style=filled overlap=\"prism1000\"";
        s+="pos=\""+std::to_string(getX(u,n)*1.5)+","+std::to_string(getY(u,n)*1.5)+"!\"]\n";

        for (int v:adjacency_list[u])
            if(!directed) {
                if (v > u) s += "  " + std::to_string(u) + "--" + std::to_string(v) + " \n";
            }else {
                s += "  " + std::to_string(u) + "->" + std::to_string(v) + "\n";
            }
    }
    s += "}";
    return s;
}

int rook_graph::save(std::string filename) const {
    return save(filename, {});
}

int rook_graph::save(std::string filename, const std::vector<int> &coloring) const {
    std::string dot_file = "./bin/" + filename + ".dot";
    std::string png_file = "./bin/" + filename + ".png";

    std::ofstream f(dot_file);
    f << this->to_dot(coloring);
    f.close();

    return system(("neato -Tpng " + dot_file + " -o " + png_file).c_str());
}