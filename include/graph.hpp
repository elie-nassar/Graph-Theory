#pragma once
#include <map>
#include <unordered_map>
#include <set>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class vertex {
	private:
		int id;
		set<int> neighbor_ids;

	public:
		vertex();
		vertex(int id);
		vertex(int id,const set<int>& neighbor_ids);

		const int get_id() const;
		const set<int>& get_neighbor_ids() const;
		void add_neighbor(int neighbor_id);
		void remove_neighbor(int neighbor_id);
};

class graph {
    private:
        unordered_map<int,vertex> vertices;
        int next_id = 0;
        bool directed;

    public:
        graph();
        graph(bool directed);
        
        const unordered_map<int,vertex>& get_vertices() const;
        const vertex& get_vertex_by_id(int id) const;
        int add_vertex();
        void add_edge(int u,int v);
        void add_edge(vertex& u,vertex& v);
        bool is_well_formed() const;
        int size() const;
        int save(string filename) const;
        int save(string filename,const unordered_map<int,int>& coloring) const;
        string to_dot() const;
        string to_dot(const unordered_map<int,int>& coloring) const;
        friend ostream& operator<<(ostream& os, const graph& G);
        static graph random(int vertex_count, int edge_count);
};
