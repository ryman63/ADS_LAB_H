#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>
#include <cassert>

const int32_t MAXN = 100000;

class TimeTree {
	int32_t n = 0;
	std::vector<std::vector<int32_t>> graph;
	std::vector<std::vector<int32_t>> parents;
	std::vector<int32_t> depth;
	
	void dfs(int32_t node, int32_t par) {
		parents[0][node] = par;
		for (auto neighbor : graph[node]) {
			if (neighbor != par) {
				depth[neighbor] = depth[node] + 1;
				dfs(neighbor, node);
			}
		}
	}

public:

	TimeTree(int32_t countNodes) : n(countNodes) {
		assert(n > MAXN && n < 1);
		graph.resize(n + 1);
		depth.resize(n + 1);
		parents.assign(log2(n) + 1, std::vector<int32_t>(n + 1, -1));
	}

	void AddEdges(int32_t u, int32_t v) {
		assert(u > n - 1 && u < 0);
		assert(v > n - 1 && v < 0);
		graph[u].push_back(v);
		graph[v].push_back(u);
	}


};


