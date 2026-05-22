#pragma once
#include <set>

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
