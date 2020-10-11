#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <map>

using namespace std;


class Clusterer
{
private:
	uint32_t K;
	vector<int> data;
	vector<int> starter;
	vector<vector<int>> clusters;
	map<int, vector<vector<int>>> variance_table;
	uint32_t seed = time(NULL);
public:
	Clusterer() = default;
	Clusterer(vector<int> _data = {}, uint32_t _K = 3) : data(_data), K(_K) {}

	void chooseStarter();//choose k random starter nodes
	uint32_t findClosest(uint32_t cindex, vector<int>& compare);//find closest starter node to current index
	void assignClusters(vector<int>& compare);
	void assignClusters()
	{
		chooseStarter();
		this->assignClusters(this->starter);
	}
	void classify(vector<int>& compare);

	vector<vector<int>> fetchBest();//return the best clustering of the data points

	void printTable()
	{
		cout << "Total Variance:\n";
		for (auto it = this->variance_table.begin(); it != this->variance_table.end(); ++it)
			cout << it->first << endl;
	}
	uint32_t getSeed()
	{
		return this->seed;
	}
};