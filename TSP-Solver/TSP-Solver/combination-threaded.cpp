//#include <iostream>
//#include <vector>
//#include <future>
//#include <ctime>
//#include <sstream>
//#include <algorithm>
//#include <mutex>
//using namespace std;
//
//struct SubsetObj {
//	vector<int> parcel_arr;
//	vector<int> point_arr;
//	int size;
//
//	SubsetObj(vector<int> parcel_arr, vector<int> point_arr) {
//		this->parcel_arr = parcel_arr;
//		this->point_arr = point_arr;
//		this->size = parcel_arr.size() + point_arr.size();
//	}
//
//	SubsetObj() {
//		this->parcel_arr = vector<int>();
//		this->point_arr = vector<int>();
//		this->size = 0;
//	}
//
//	string toString() {
//		stringstream ss;
//		ss << "(";
//
//		ss << "[";
//		for (auto elem : parcel_arr)
//			ss << elem << ", ";
//		ss << "]";
//
//		ss << ", ";
//
//		ss << "[";
//		for (auto elem : point_arr)
//			ss << elem << ", ";
//		ss << "]";
//
//		ss << ")";
//		return ss.str();
//	}
//};
//
//vector<vector<int>> combinations(vector<int> col_list, int r) {
//	vector<vector<int>> combs;
//
//	int end = col_list.size();
//
//	if (r > end) return combs;
//
//	vector<int> a(r), b(r);
//	for (int i = 0; i < r; i++) {
//		a[i] = i;
//		b[i] = col_list[i];
//	}
//	combs.push_back(b);
//
//	for (int i = 0; i >= 0; ) {
//		for (i = r - 1; i >= 0 && a[i] >= end + i - r; i--);
//
//		if (i < 0) break;
//
//		// One Loop
//		for (int j = a[i] + 1; i < r; j++, i++) {
//			a[i] = j;
//			b[i] = col_list[j];
//		}
//
//		combs.push_back(b);
//	}
//
//	return combs;
//}
//
//int binomialCoeff(int n, int k)
//{
//	vector<int> C(k + 1, 0);
//
//	C[0] = 1; // nC0 is 1
//
//	for (int i = 1; i <= n; i++)
//	{
//		for (int j = min(i, k); j > 0; j--) {
//			C[j] = C[j] + C[j - 1];
//		}
//	}
//	return C[k];
//}
//
//vector<vector<SubsetObj>> generateSubsetSingle(vector<int>& parcel_arr, vector<int>& point_arr) {
//	int gN = parcel_arr.size(), rN = point_arr.size();
//	int subset_ind;
//
//	vector<vector<SubsetObj>> subset_arr(2 * rN - 1, vector<SubsetObj>()); // Generate 2D Subset Array of increasing length
//
//	// Async Here
//	vector<vector<vector<int>>> parcel_comb_arr(rN);
//	for (int k = 1; k < rN + 1; k++) {
//		parcel_comb_arr[k - 1] = combinations(parcel_arr, k);
//	}
//
//	// Async Here
//	vector<vector<vector<int>>> point_comb_arr(rN);
//	for (int k = 1; k < rN + 1; k++) {
//		point_comb_arr[k - 1] = combinations(point_arr, k);
//	}
//
//	subset_ind = 0;
//	subset_arr[0].resize(gN * rN);
//	for (vector<int> gSubset : parcel_comb_arr[0]) {
//		for (vector<int> rSubset : point_comb_arr[0]) {
//			subset_arr[0][subset_ind++] = SubsetObj(gSubset, rSubset);
//		}
//	}
//
//	for (int k = 2; k < rN + 1; k++) {
//		subset_ind = 0;
//		subset_arr[2 * k - 3].resize(binomialCoeff(gN, k) * binomialCoeff(rN, k - 1));
//
//		// Async Here
//		for (vector<int> gSubset : parcel_comb_arr[k - 1]) {
//			for (vector<int> rSubset : point_comb_arr[k - 2]) {
//				subset_arr[2 * k - 3][subset_ind++] = SubsetObj(gSubset, rSubset);
//			}
//		}
//
//		subset_ind = 0;
//		subset_arr[2 * k - 2].resize(binomialCoeff(gN, k) * binomialCoeff(rN, k));
//
//		// Async Here
//		for (vector<int> gSubset : parcel_comb_arr[k - 1]) {
//			for (vector<int> rSubset : point_comb_arr[k - 1]) {
//				subset_arr[2 * k - 2][subset_ind++] = SubsetObj(gSubset, rSubset);
//			}
//		}
//	}
//
//	return subset_arr;
//}
//
//vector<SubsetObj> parallelGenerateCombinations(vector<vector<int>> parcel_comb_arr, vector<vector<int>>& point_comb_arr, int size) {
//	vector<SubsetObj> subset_arr(size);
//	int subset_ind(0);
//	for (vector<int> gSubset : parcel_comb_arr) {
//		for (vector<int> rSubset : point_comb_arr) {
//			subset_arr[subset_ind++] = SubsetObj(gSubset, rSubset);
//		}
//	}
//	return subset_arr;
//}
//
//vector<vector<SubsetObj>> generateSubsetParallel(vector<int>& parcel_arr, vector<int>& point_arr) {
//	int gN = parcel_arr.size(), rN = point_arr.size();
//	int subset_ind;
//
//	vector<vector<SubsetObj>> subset_arr(2 * rN - 1, vector<SubsetObj>()); // Generate 2D Subset Array of increasing length
//
//	// Async Here
//	vector<vector<vector<int>>> parcel_comb_arr(rN);
//	for (int k = 1; k < rN + 1; k++) {
//		parcel_comb_arr[k - 1] = combinations(parcel_arr, k);
//	}
//
//	// Async Here
//	vector<vector<vector<int>>> point_comb_arr(rN);
//	for (int k = 1; k < rN + 1; k++) {
//		point_comb_arr[k - 1] = combinations(point_arr, k);
//	}
//
//	subset_ind = 0;
//	subset_arr[0].resize(gN * rN);
//	for (vector<int> gSubset : parcel_comb_arr[0]) {
//		for (vector<int> rSubset : point_comb_arr[0]) {
//			subset_arr[0][subset_ind++] = SubsetObj(gSubset, rSubset);
//		}
//	}
//
//	int number_of_core = thread::hardware_concurrency(), cur_size(-1), subset_size(-1);
//	vector<future<vector<SubsetObj>>> async_arr(number_of_core);
//	vector<vector<int>> gSubset_arr, tmp_arr;
//	for (int k = 2; k < rN + 1; k++) {
//		
//		gSubset_arr = parcel_comb_arr[k - 1];
//		cur_size = gSubset_arr.size();
//
//		// Async Here
//		subset_size = point_comb_arr[k - 2].size();
//		for (int i = 0; i < number_of_core; i++) {
//			auto start = gSubset_arr.begin() + i * cur_size / number_of_core;
//			auto end = gSubset_arr.begin() + (i + 1) * cur_size / number_of_core;
//			tmp_arr = vector<vector<int>>(start, end);
//			async_arr[i] = async(parallelGenerateCombinations, tmp_arr, ref(point_comb_arr[k - 2]), tmp_arr.size() * subset_size);
//		}
//
//		for (auto& action : async_arr) {
//			auto tmp_subset_arr = action.get();
//			subset_arr[2 * k - 3].insert(subset_arr[2 * k - 3].end(), tmp_subset_arr.begin(), tmp_subset_arr.end());
//		}
//
//		subset_size = point_comb_arr[k - 1].size();
//		for (int i = 0; i < number_of_core; i++) {
//			auto start = gSubset_arr.begin() + i * cur_size / number_of_core;
//			auto end = gSubset_arr.begin() + (i + 1) * cur_size / number_of_core;
//			tmp_arr = vector<vector<int>>(start, end);
//			async_arr[i] = async(parallelGenerateCombinations, tmp_arr, ref(point_comb_arr[k - 1]), tmp_arr.size() * subset_size);
//		}
//
//		for (auto& action : async_arr) {
//			auto tmp_subset_arr = action.get();
//			subset_arr[2 * k - 2].insert(subset_arr[2 * k - 2].end(), tmp_subset_arr.begin(), tmp_subset_arr.end());
//		}
//	}
//
//	return subset_arr;
//}
//
//
//
//
//int main() {
//	long start, stop;
//
//	/*auto tmp_arr = combinations(vector<int>{1, 3, 5}, 2);
//	for (auto arr : tmp_arr) {
//		for (auto elem : arr) {
//			cout << elem << " ";
//		}
//		cout << endl;
//	}*/
//
//	vector<int> parcel_vec = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 18, 19, 20, 21, 22, 23, 24  };
//	vector<int> point_vec = { 2, 4, 6, 8, 10, 12, 14, 16 };
//
//	vector<long long> route_arr;
//
//	long long key;
//
//	for (int k : parcel_vec) {
//		key = ((long long)1 << k) * 100 + k;
//		route_arr.push_back(key);
//	}
//
//	for (long long route_bits : route_arr) {
//		for (int k : point_vec) {
//			cout << route_bits * 100 + k << (route_bits * 100 + k > INT32_MAX ? " true" : " false") << endl;
//		}
//	}
//
//
//	//vector<vector<SubsetObj>> subset_arr;
//
//	//start = clock();
//	//subset_arr = generateSubsetSingle(parcel_vec, point_vec);
//	////for (auto arr : subset_arr) {
//	////	for (auto elem : arr) {
//	////		cout << elem.toString() << endl;
//	////	}
//	////	cout << endl;
//	////}
//	//stop = clock();
//	//cout << "Time Taken: " << stop - start << "ms" << endl;
//
//	//start = clock();
//	//subset_arr = generateSubsetParallel(parcel_vec, point_vec);
//	////for (auto arr : subset_arr) {
//	////	for (auto elem : arr) {
//	////		cout << elem.toString() << endl;
//	////	}
//	////	cout << endl;
//	////}
//	//stop = clock();
//	//cout << "Time Taken: " << stop - satart << "ms" << endl;
//
//	/*vector<int> test_vec = { 1, 2, 3, 4, 5, 6 }, tmp_vec;
//	int number_of_core = 8;
//	int number_of_job(-1);
//
//	for (int i = 0; i < number_of_core; i++) {
//		number_of_job = test_vec.size();
//		auto start = test_vec.begin() + i * number_of_job / number_of_core;
//		auto end = test_vec.begin() + (i + 1) * number_of_job / number_of_core;
//		tmp_vec = vector<int>(start, end);
//		for (auto elem : tmp_vec) {
//			cout << elem << " ";
//		}
//		cout << endl;
//	}*/
//
//	return 0;
//}