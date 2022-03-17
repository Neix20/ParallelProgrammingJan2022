#include <iostream>
#include <vector>
#include <future>
#include <ctime>
#include <sstream>
#include <algorithm>
using namespace std;

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

int binomialCoeff(int n, int k)
{
	vector<int> C(k + 1, 0);

	C[0] = 1; // nC0 is 1

	for (int i = 1; i <= n; i++)
	{
		for (int j = min(i, k); j > 0; j--) {
			C[j] = C[j] + C[j - 1];
		}
	}
	return C[k];
}

vector<vector<SubsetObj>> generateSubset(vector<int>& parcel_arr, vector<int>& point_arr) {
	int gN = parcel_arr.size(), rN = point_arr.size();
	int subset_ind;

	vector<vector<SubsetObj>> subset_arr(2 * rN - 1, vector<SubsetObj>()); // Generate 2D Subset Array of increasing length

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
		subset_arr[2 * k - 3].resize(binomialCoeff(gN, k) * binomialCoeff(rN, k - 1));
		for (vector<int> rSubset : point_comb_arr[k - 2]) {
			for (vector<int> gSubset : parcel_comb_arr[k - 1]) {
				subset_arr[2 * k - 3][subset_ind++] = SubsetObj(gSubset, rSubset);
			}
		}

		subset_ind = 0;
		subset_arr[2 * k - 2].resize(binomialCoeff(gN, k) * binomialCoeff(rN, k));
		for (vector<int> rSubset : point_comb_arr[k - 1]) {
			for (vector<int> gSubset : parcel_comb_arr[k - 1]) {
				subset_arr[2 * k - 2][subset_ind++] = SubsetObj(gSubset, rSubset);
			}
		}
	}

	return subset_arr;
}

int main() {
	long start, stop;

	/*auto tmp_arr = combinations(vector<int>{1, 3, 5}, 2);
	for (auto arr : tmp_arr) {
		for (auto elem : arr) {
			cout << elem << " ";
		}
		cout << endl;
	}*/

	start = clock();
	vector<int> parcel_vec = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31 };
	vector<int> point_vec = { 2, 4, 6, 8, 10, 12, 14, 16 };

	auto subset_arr = generateSubset(parcel_vec, point_vec);
	stop = clock();
	cout << "Time Taken: " << stop - start << "ms" << endl;

	/*vector<int> test_vec = { 1, 2, 3, 4, 5, 6 }, tmp_vec;
	int number_of_core = 8;
	int number_of_job(-1);

	for (int i = 0; i < number_of_core; i++) {
		number_of_job = test_vec.size();
		auto start = test_vec.begin() + i * number_of_job / number_of_core;
		auto end = test_vec.begin() + (i + 1) * number_of_job / number_of_core;
		tmp_vec = vector<int>(start, end);
		for (auto elem : tmp_vec) {
			cout << elem << " ";
		}
		cout << endl;
	}*/

	return 0;
}