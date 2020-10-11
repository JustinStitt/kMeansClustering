#include "Clusterer.hpp"

using namespace std;



int main()
{
	uint32_t N = 50;//number of elements
	uint32_t R = 250;//range of values
	uint32_t tries = 80;
	vector<int> test; test.reserve(N);
	int _r;
	for (int x{}; x < N; ++x)
	{
		_r = rand() % R;
		test.push_back(_r);
	}

	Clusterer c(test);
	for (int x{}; x < tries; ++x)
		c.assignClusters();
	//c.printTable();
	cout << "Best Clustering: \n";
	vector<vector<int>> best = c.fetchBest();
	int cnt = 0;
	for (auto& row : best)
	{
		cout << "Cluster Group {" << cnt++ << "}: ";
		for (auto& col : row)
			cout << col << " ";
		cout << endl;
	}

	cin.get();
	return 0;
}