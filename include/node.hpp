#pragma once
#include <set>

using namespace std;

class node {
	private:
		int id;
		set<int> neighbor_ids;

	public:
		node();
		node(int id);
		node(int id,const set<int>& neighbor_ids);

		const int get_id() const;
		const set<int>& get_neighbor_ids() const;
		void add_neighbor(int neighbor_id);
		void remove_neighbor(int neighbor_id);
};
