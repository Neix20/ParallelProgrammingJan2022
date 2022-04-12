#include <omp.h>
#include <ppl.h>
#include <ctime>
#include <thread>
#include <future>
#include <vector>
#include <sstream>
#include <iostream>

using namespace Concurrency;
using namespace std;

// SubsetObj is used to store combinations of Parcel Array, and combinations of points Array respectively
// It is used to interchange between parcel array or point array based on current last node
struct SubsetObj {
	vector<int> parcel_arr;
	vector<int> point_arr;
	int size;

	SubsetObj(vector<int> parcel_arr, vector<int> point_arr) {
		this->parcel_arr = parcel_arr;
		this->point_arr = point_arr;
		this->size = parcel_arr.size() + point_arr.size();
	}

	SubsetObj() {
		this->parcel_arr = vector<int>();
		this->point_arr = vector<int>();
		this->size = 0;
	}

	string toString() {
		stringstream ss;
		ss << "(";

		ss << "[";
		for (auto elem : parcel_arr)
			ss << elem << ", ";
		ss << "]";

		ss << ", ";

		ss << "[";
		for (auto elem : point_arr)
			ss << elem << ", ";
		ss << "]";

		ss << ")";
		return ss.str();
	}
};

// Combination Without Duplicate => Self Written
// This function is used to generate combinations of a vector
// For example, given vector[1, 3, 5] and size 2
// The function will produce {[1, 3], [1, 5], [3, 5]}. The size of Combs will be 3C2 respectively.
vector<vector<int>> combinations(vector<int> col_list, int r) {
	vector<vector<int>> combs;

	int end = col_list.size();

	if (r > end) return combs;

	vector<int> a(r), b(r);
	for (int i = 0; i < r; i++) {
		a[i] = i;
		b[i] = col_list[i];
	}
	combs.push_back(b);

	for (int i = 0; i >= 0; ) {
		for (i = r - 1; i >= 0 && a[i] >= end + i - r; i--);

		if (i < 0) break;

		// One Loop
		for (int j = a[i] + 1; i < r; j++, i++) {
			a[i] = j;
			b[i] = col_list[j];
		}

		combs.push_back(b);
	}

	return combs;
}

// Dynamic Binomial Coefficient to get the total number of combinations and Subset
int binomialCoeff(int n, int k)
{
	vector<int> C(k + 1, 0);
	C[0] = 1; // nC0 is 1
	for (int i = 1; i <= n; i++) {
		for (int j = min(i, k); j > 0; j--) {
			C[j] = C[j] + C[j - 1];
		}
	}
	return C[k];
}

// This formula computes the total number of calculations needed
// This formula constructs the bottom root of the tree to the final subset
long gen_total_calculation(int gN, int rN) {
	long ans = 0;

	// 1 x 1
	ans += gN * rN;

	// 2 * 1, 2 * 2, 3 * 1, .... k * (l - 1) , k * l
	for (int k = 2; k < rN + 1; k++) {
		for (int l = k - 1; l < k + 1; l++) {
			ans += binomialCoeff(gN, k) * binomialCoeff(rN, l);
		}
	}
	return ans;
}

vector<vector<SubsetObj>> genSubsetArr(vector<int> parcel_arr, vector<int> point_arr) {
	const int gN = parcel_arr.size(), rN = point_arr.size();

	vector<vector<SubsetObj>> subset_arr(2 * rN - 1); // Generate Subset Array

	int subset_ind(0), subset_size(-1);

	vector<vector<vector<int>>> parcel_comb_arr(rN);
	for (int k = 1; k < rN + 1; k++) {
		parcel_comb_arr[k - 1] = combinations(parcel_arr, k);
	}

	vector<vector<vector<int>>> point_comb_arr(rN);
	for (int k = 1; k < rN + 1; k++) {
		point_comb_arr[k - 1] = combinations(point_arr, k);
	}

	subset_ind = 0;
	subset_arr[0].resize(gN * rN);
	for (vector<int> gSubset : parcel_comb_arr[0]) {
		for (vector<int> rSubset : point_comb_arr[0]) {
			subset_arr[0][subset_ind++] = SubsetObj(gSubset, rSubset);
		}
	}

	for (int k = 2; k < rN + 1; k++) {
		subset_ind = 0;
		subset_size = parcel_comb_arr[k - 1].size() * point_comb_arr[k - 2].size();
		subset_arr[2 * k - 3].resize(subset_size);
		for (vector<int> gSubset : parcel_comb_arr[k - 1]) {
			for (vector<int> rSubset : point_comb_arr[k - 2]) {
				subset_arr[2 * k - 3][subset_ind++] = SubsetObj(gSubset, rSubset);
			}
		}

		subset_ind = 0;
		subset_size = parcel_comb_arr[k - 1].size() * point_comb_arr[k - 1].size();
		subset_arr[2 * k - 2].resize(subset_size);
		for (vector<int> gSubset : parcel_comb_arr[k - 1]) {
			for (vector<int> rSubset : point_comb_arr[k - 1]) {
				subset_arr[2 * k - 2][subset_ind++] = SubsetObj(gSubset, rSubset);
			}
		}
	}

	return subset_arr;
}

vector<SubsetObj> parallelGenerateCombinations(vector<vector<int>> parcel_comb_arr, vector<vector<int>>& point_comb_arr, int size) {
	vector<SubsetObj> subset_arr(size);
	int subset_ind(0);
	for (vector<int> gSubset : parcel_comb_arr) {
		for (vector<int> rSubset : point_comb_arr) {
			subset_arr[subset_ind++] = SubsetObj(gSubset, rSubset);
		}
	}
	return subset_arr;
}

vector<vector<SubsetObj>> genSubsetArrAsync(vector<int> parcel_arr, vector<int> point_arr) {
	const int gN = parcel_arr.size(), rN = point_arr.size();

	vector<vector<SubsetObj>> subset_arr(2 * rN - 1); // Generate Subset Array

	int subset_ind(0);

	vector<vector<vector<int>>> parcel_comb_arr(rN);
	for (int k = 1; k < rN + 1; k++) {
		parcel_comb_arr[k - 1] = combinations(parcel_arr, k);
	}

	vector<vector<vector<int>>> point_comb_arr(rN);
	for (int k = 1; k < rN + 1; k++) {
		point_comb_arr[k - 1] = combinations(point_arr, k);
	}

	subset_ind = 0;
	subset_arr[0].resize(gN * rN);
	for (vector<int> gSubset : parcel_comb_arr[0]) {
		for (vector<int> rSubset : point_comb_arr[0]) {
			subset_arr[0][subset_ind++] = SubsetObj(gSubset, rSubset);
		}
	}

	int number_of_core = thread::hardware_concurrency(), cur_size(-1), subset_size(-1);
	vector<future<vector<SubsetObj>>> async_arr(number_of_core);
	vector<vector<int>> gSubset_arr, tmp_arr;
	for (int k = 2; k < rN + 1; k++) {

		gSubset_arr = parcel_comb_arr[k - 1];
		cur_size = gSubset_arr.size();

		// Async Here
		subset_size = point_comb_arr[k - 2].size();
		for (int i = 0; i < number_of_core; i++) {
			auto start = gSubset_arr.begin() + i * cur_size / number_of_core;
			auto end = gSubset_arr.begin() + (i + 1) * cur_size / number_of_core;
			tmp_arr = vector<vector<int>>(start, end);
			async_arr[i] = async(parallelGenerateCombinations, tmp_arr, ref(point_comb_arr[k - 2]), tmp_arr.size() * subset_size);
		}

		for (auto& action : async_arr) {
			auto tmp_subset_arr = action.get();
			subset_arr[2 * k - 3].insert(subset_arr[2 * k - 3].end(), tmp_subset_arr.begin(), tmp_subset_arr.end());
		}

		subset_size = point_comb_arr[k - 1].size();
		for (int i = 0; i < number_of_core; i++) {
			auto start = gSubset_arr.begin() + i * cur_size / number_of_core;
			auto end = gSubset_arr.begin() + (i + 1) * cur_size / number_of_core;
			tmp_arr = vector<vector<int>>(start, end);
			async_arr[i] = async(parallelGenerateCombinations, tmp_arr, ref(point_comb_arr[k - 1]), tmp_arr.size() * subset_size);
		}

		for (auto& action : async_arr) {
			auto tmp_subset_arr = action.get();
			subset_arr[2 * k - 2].insert(subset_arr[2 * k - 2].end(), tmp_subset_arr.begin(), tmp_subset_arr.end());
		}
	}

	return subset_arr;
}

vector<vector<SubsetObj>> genSubsetArrOMP(vector<int> parcel_arr, vector<int> point_arr) {
	const int gN = parcel_arr.size(), rN = point_arr.size();

	vector<vector<SubsetObj>> subset_arr(2 * rN - 1); // Generate Subset Array

	int subset_ind(0), subset_size(-1);

	vector<vector<vector<int>>> parcel_comb_arr(rN);
	for (int k = 1; k < rN + 1; k++) {
		parcel_comb_arr[k - 1] = combinations(parcel_arr, k);
	}

	vector<vector<vector<int>>> point_comb_arr(rN);
	for (int k = 1; k < rN + 1; k++) {
		point_comb_arr[k - 1] = combinations(point_arr, k);
	}

	int t_gN(-1), t_rN(-1);
	int number_of_core = thread::hardware_concurrency();

	subset_ind = 0;
	subset_arr[0].resize(gN * rN);
	t_gN = parcel_comb_arr[0].size();
	t_rN = point_comb_arr[0].size();
	#pragma omp parallel
	{
		int tId = omp_get_thread_num();
		for (int ij = 0 + tId; ij < t_gN * t_rN; ij += number_of_core) {
			vector<int> gSubset = parcel_comb_arr[0][ij / t_rN];
			vector<int> rSubset = point_comb_arr[0][ij % t_rN];
			subset_arr[0][ij] = SubsetObj(gSubset, rSubset);
		}
	}

	for (int k = 2; k < rN + 1; k++) {
		t_gN = parcel_comb_arr[k - 1].size();
		t_rN = point_comb_arr[k - 2].size();
		subset_size = t_gN * t_rN;
		subset_arr[2 * k - 3].resize(subset_size);
		#pragma omp parallel
		{
			int tId = omp_get_thread_num();
			for (int ij = 0 + tId; ij < t_gN * t_rN; ij += number_of_core) {
				vector<int> gSubset = parcel_comb_arr[k - 1][ij / t_rN];
				vector<int> rSubset = point_comb_arr[k - 2][ij % t_rN];
				subset_arr[2 * k - 3][ij] = SubsetObj(gSubset, rSubset);
			}
		}

		t_gN = parcel_comb_arr[k - 1].size();
		t_rN = point_comb_arr[k - 1].size();
		subset_size = t_gN * t_rN;
		subset_arr[2 * k - 2].resize(subset_size);
		#pragma omp parallel
		{
			int tId = omp_get_thread_num();
			for (int ij = 0 + tId; ij < t_gN * t_rN; ij += number_of_core) {
				vector<int> gSubset = parcel_comb_arr[k - 1][ij / t_rN];
				vector<int> rSubset = point_comb_arr[k - 1][ij % t_rN];
				subset_arr[2 * k - 2][ij] = SubsetObj(gSubset, rSubset);
			}
		}
	}

	return subset_arr;
}

vector<vector<SubsetObj>> genSubsetArrParallelWindows(vector<int> parcel_arr, vector<int> point_arr) {
	const int gN = parcel_arr.size(), rN = point_arr.size();

	vector<vector<SubsetObj>> subset_arr(2 * rN - 1); // Generate Subset Array

	int subset_ind(0), subset_size(-1), t_gN(-1), t_rN(-1);

	vector<vector<vector<int>>> parcel_comb_arr(rN);
	for (int k = 1; k < rN + 1; k++) {
		parcel_comb_arr[k - 1] = combinations(parcel_arr, k);
	}

	vector<vector<vector<int>>> point_comb_arr(rN);
	for (int k = 1; k < rN + 1; k++) {
		point_comb_arr[k - 1] = combinations(point_arr, k);
	}

	subset_ind = 0;
	subset_arr[0].resize(gN * rN);

	t_gN = parcel_comb_arr[0].size();
	t_rN = point_comb_arr[0].size();
	subset_size = t_gN * t_rN;
	parallel_for(int(0), subset_size, [&](int ij) {
		vector<int> gSubset = parcel_comb_arr[0][ij / t_rN];
		vector<int> rSubset = point_comb_arr[0][ij % t_rN];
		subset_arr[0][ij] = SubsetObj(gSubset, rSubset);
	});


	for (int k = 2; k < rN + 1; k++) {
		t_gN = parcel_comb_arr[k - 1].size();
		t_rN = point_comb_arr[k - 2].size();
		subset_size = t_gN * t_rN;
		subset_arr[2 * k - 3].resize(subset_size);

		parallel_for(int(0), subset_size, [&](int ij) {
			vector<int> gSubset = parcel_comb_arr[k - 1][ij / t_rN];
			vector<int> rSubset = point_comb_arr[k - 2][ij % t_rN];
			subset_arr[2 * k - 3][ij] = SubsetObj(gSubset, rSubset);
		});

		t_gN = parcel_comb_arr[k - 1].size();
		t_rN = point_comb_arr[k - 1].size();
		subset_size = t_gN * t_rN;
		subset_arr[2 * k - 2].resize(subset_size);

		parallel_for(int(0), subset_size, [&](int ij) {
			vector<int> gSubset = parcel_comb_arr[k - 1][ij / t_rN];
			vector<int> rSubset = point_comb_arr[k - 1][ij % t_rN];
			subset_arr[2 * k - 2][ij] = SubsetObj(gSubset, rSubset);
		});
	}

	return subset_arr;
}

int main() {

	long start, stop;

	vector<vector<SubsetObj>> subset_arr;

	vector<int> parcel_arr = { 1, 3, 5 ,7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31};
	vector<int> point_arr = { 2, 4, 6, 8, 10, 12, 14, 16};

	// Normal
	/*start = clock();
	subset_arr = genSubsetArr(parcel_arr, point_arr);
	stop = clock();
	cout << "Time Taken (Normal): " << stop - start << "ms" << endl;*/

	/*for (auto arr : subset_arr) {
		for (auto subset : arr) {
			cout << subset.toString() << endl;
		}
	}*/

	// Async
	start = clock();
	subset_arr = genSubsetArrAsync(parcel_arr, point_arr);
	stop = clock();
	cout << "Time Taken (Async): " << stop - start << "ms" << endl;


	// Open MP
	/*start = clock();
	subset_arr = genSubsetArrOMP(parcel_arr, point_arr);
	stop = clock();
	cout << "Time Taken (Open MP): " << stop - start << "ms" << endl;*/

	// Parallel Windows
	start = clock();
	subset_arr = genSubsetArrParallelWindows(parcel_arr, point_arr);
	stop = clock();
	cout << "Time Taken (Parallel Windows): " << stop - start << "ms" << endl;

	system("pause");
	return 0;
}