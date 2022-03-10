//#include <future>
//#include <iostream>
//#include <algorithm>
//#include <unordered_map>
//using namespace std;
//
//typedef unsigned long long UINT64;
//
//unordered_map<int, int> aSum(unsigned int start, unsigned int end, int step) {
//	unordered_map<int, int> uMap;
//	UINT64 total = 0;
//	for (unsigned int i = start; i <= end; i += step) {
//		total += i;
//		uMap.insert(make_pair(i, total));
//	}
//	return uMap;
//}
//
//UINT64 aSumInt(unsigned int start, unsigned int end) {
//	UINT64 total = 0;
//	for (unsigned int i = start; i <= end; i ++) {
//		total += i;
//	}
//	return total;
//}
//
//UINT64 aSumVec(vector<int> vec) {
//	UINT64 total = 0;
//	for (int elem : vec) {
//		total += elem;
//	}
//	return total;
//}
//
//
//int main() {
//
//	int max = 3;
//
//	long start, stop;
//
//	start = clock();
//
//	
//	/*UINT64 total = 0;
//	for (unsigned int i = 0; i <= max; i += 1) {
//		total += i;
//	}
//	cout << total << endl;*/
//	
//	vector<int> vec(max + 1, 0);
//	for (int i = 0; i < vec.size(); i++) {
//		vec[i] = i;
//	};
//
//	stop = clock();
//	cout << "Time Taken: " << stop - start << "ms" << endl;
//
//	start = clock();
//	unsigned int half = max / 2;
//	unsigned int half_half = max / 4;
//
//	unordered_map<int, int> gMap;
//
//	/*auto f1 = async(aSumInt, 1, half_half - 1);
//	auto f2 = async(aSumInt, half_half, half - 1);
//	auto f3 = async(aSumInt, half, half + half_half - 1);
//	auto f4 = async(aSumInt, half + half_half, max);*/
//
//	auto f1 = async(aSumVec, vector<int>(vec.begin(), vec.begin() + max * 0.25));
//	auto f2 = async(aSumVec, vector<int>(vec.begin() + max * 0.25, vec.begin() + max * 0.5));
//	auto f3 = async(aSumVec, vector<int>(vec.begin() + max * 0.5, vec.begin() + max * 0.75));
//	auto f4 = async(aSumVec, vector<int>(vec.begin() + max * 0.75, vec.end()));
//
//	auto res1 = f1.get();
//	auto res2 = f2.get();
//	auto res3 = f3.get();
//	auto res4 = f4.get();
//
//	cout << res1 + res2 + res3 + res4 << endl;
//
//	stop = clock();
//	cout << "Time Taken: " << stop - start << "ms" << endl;
//
//	return 0;
//}