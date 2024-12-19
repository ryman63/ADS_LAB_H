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

	void dfs(int32_t node, int32_t parent) {
		parents[0][node] = parent;
		for (auto neighbor : graph[node]) {
			if (neighbor != parent) {
				depth[neighbor] = depth[node] + 1;
				dfs(neighbor, node);
			}
		}
	}

	int32_t lca(int32_t u, int32_t v) {
		assert(u <= n - 1 && u >= 0);
		assert(v <= n - 1 && v >= 0);

		if (depth[u] < depth[v])
			std::swap(u, v);

		int32_t diff = depth[u] - depth[v];
		int32_t maxLog = log2(n) + 1;

		for (int32_t i = 0; i < maxLog; i++) {
			if ((diff >> i) & 1) {
				u = parents[i][u];
			}
		}

		if (u == v) return u;

		for (int32_t i = maxLog - 1; i >= 0; i--) {
			if (parents[i][u] != parents[i][v]) {
				u = parents[i][u];
				v = parents[i][v];
			}
		}

		return parents[0][u];
	}

public:

	TimeTree(int32_t countNodes) : n(countNodes) {
		assert(n <= MAXN && n >= 1);
		graph.resize(n + 1);
		depth.resize(n + 1);
		parents.assign(log2(n) + 1, std::vector<int32_t>(n + 1, -1));
	}

	void AddEdge(int32_t u, int32_t v) {
		assert(u <= n - 1 && u >= 0);
		assert(v <= n - 1 && v >= 0);
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	void Initialize(int32_t root = 0) {
		dfs(root, -1);
		int32_t maxLog = log2(n) + 1;
		for (int i = 1; i < maxLog; i++) {
			for (int node = 1; node <= n; node++) {
				if (parents[i - 1][node] != -1) 
					parents[i][node] = parents[i - 1][parents[i - 1][node]];
			}
		}
	}

	int32_t Distance(int32_t u, int32_t v) {
		assert(u <= n - 1 && u >= 0);
		assert(v <= n - 1 && v >= 0);

		int32_t ancestor = lca(u, v);
		return depth[u] + depth[v] - (2 * depth[ancestor]);
	}
};

int main() {
	int32_t N;
	std::cin >> N;

	TimeTree timeTree(N);

	for (size_t i = 0; i < (size_t)N - 1; i++) {
		int32_t u, v;
		std::cin >> u >> v;
		timeTree.AddEdge(u, v);
	}

	timeTree.Initialize();

	int32_t Q;
	std::cin >> Q;

	std::vector<bool> results;
	while (Q--) {
		int32_t u, v;
		int32_t T;
		std::cin >> u >> v >> T;
		int32_t dist = timeTree.Distance(u, v);
		if (dist <= T) {
			results.push_back(true);
		}
		else {
			results.push_back(false);
		}
	}

	for (auto result : results) {
		if (result)
			std::cout << "Yes" << std::endl;
		else
			std::cout << "No" << std::endl;
	}

	return 0;
}
