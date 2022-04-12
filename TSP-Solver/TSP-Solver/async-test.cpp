//#include <future>
//#include <iostream>
//#include <algorithm>
//#include <omp.h>
//#include <ppl.h>
//using namespace concurrency;
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
//UINT64 aSumInt(UINT64 start, UINT64 end) {
//	UINT64 total = 0;
//	for (UINT64 i = start; i <= end; i++) {
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
//	UINT64 max = (UINT64) 1 << 34;
//	cout << max << endl;
//	int num_of_core = thread::hardware_concurrency();
//	atomic<UINT64> total;
//	long start, stop;
//
//	/*start = clock();
//	total = 0;
//	for (int i = 1; i <= max; i++) {
//		total += i;
//	}
//	cout << total << endl;
//	stop = clock();
//	cout << "Time Taken: " << stop - start << "ms" << endl; */
//
//	start = clock();
//	total = 0;
//	#pragma omp parallel for
//	for (int i = 0; i < num_of_core; i++) {
//		UINT64 start_ind = i * max / num_of_core;
//		UINT64 end_ind = (i + 1) * max / num_of_core - 1;
//		total += aSumInt(start_ind, end_ind);
//	}
//	total += max;
//	cout << total << endl;
//	stop = clock();
//	cout << "Time Taken: " << stop - start << "ms" << endl;
//	
//	start = clock();
//
//	total = 0;
//	vector<future<UINT64>> async_arr(num_of_core);
//
//	for (int i = 0; i < num_of_core; i++) {
//		UINT64 start_ind = i * max / num_of_core;
//		UINT64 end_ind = (i + 1) * max / num_of_core - 1;
//		async_arr[i] = async(aSumInt, start_ind, end_ind);
//	}
//
//	for (auto& action : async_arr) {
//		total += action.get();
//	}
//
//	total += max;
//	cout << total << endl;
//
//	stop = clock();
//	cout << "Time Taken: " << stop - start << "ms" << endl;
//
//	/*start = clock();
//
//	total = parallel_for()
//	total += max;
//	cout << total << endl;
//
//	stop = clock();
//	cout << "Time Taken: " << stop - start << "ms" << endl;*/
//
//	return 0;
//}