#include "Clusterer.hpp"
#include <numeric>

void calcMean(vector<int>& means, const vector<vector<int>>& clstr);

void Clusterer::chooseStarter()
{
	this->starter.clear();
	srand(seed++);
	uint32_t _r;
	//define a pick vector to choose indicies from and remove so we guarantee no duplicates
	vector<int> pick(this->data);

	for (int x{}; x < this->K; ++x)
	{
		_r = rand() % pick.size();//random # between 0 and size - 1 inclusive
		this->starter.push_back(pick[_r]);
		pick.erase(pick.begin() + _r);
	}

}

uint32_t Clusterer::findClosest(uint32_t cindex, vector<int>& compare)
{
	uint32_t shortest_index = 0;
	uint32_t shortest_distance = abs(this->data[cindex] -
		compare[shortest_index]);
	for (int x = 1; x < compare.size(); ++x)
	{
		uint32_t cdist = abs(this->data[cindex] - 
			compare[x]);
		if (cdist < shortest_distance)
		{
			shortest_distance = cdist;
			shortest_index = x;
		}
	}
	return shortest_index;
}

void Clusterer::classify(vector<int>& compare)
{
	//clear previous clusters
	this->clusters.clear();
	//resize classification vector to store cluster information
	this->clusters.resize(this->K);
	//iterate through all data points and classify them by their proximity to compare points
	for (int x{}; x < this->data.size(); ++x)
	{
		uint32_t cluster_id = this->findClosest(x, compare);//find the index of the closest compare point
		this->clusters[cluster_id].push_back(this->data[x]);//add our data to its respective cluster classification
	}
}

void Clusterer::assignClusters(vector<int>& compare)
{
	//sort data into their respective clusters based on distance from compare points
	this->classify(compare);
	//calculate mean of each cluster
	vector<int> means(K);
	calcMean(means, this->clusters);
	//change compare points to be the mean of the previous clusters
	compare = means;
	//sort data into their respective clusters based on distance from compare points
	this->classify(compare);

	int total_variance = 0;
	

	for (int x{}; x < this->clusters.size(); ++x)
	{
		int smallest = *min_element(this->clusters[x].begin(), this->clusters[x].end());
		int largest = *max_element(this->clusters[x].begin(), this->clusters[x].end());
		total_variance += largest - smallest;
	}
	//store our clusters and their total variance
	this->variance_table[total_variance] = this->clusters;
}

void calcMean(vector<int>& means, const vector<vector<int>>& clstr)
{
	for (int x{}; x < means.size(); ++x)
	{
		int sum = accumulate(clstr[x].begin(), clstr[x].end(), 0.0);
		int mean = sum / (clstr[x].size() + 1);
		if(clstr[x].size() != 0)
			mean = sum / clstr[x].size();
		means[x] = mean;
	}
}

vector<vector<int>> Clusterer::fetchBest()
{
	auto it = min_element(this->variance_table.begin(), this->variance_table.end());
	cout << "best variance: " << it->first << endl;
	return it->second;
}