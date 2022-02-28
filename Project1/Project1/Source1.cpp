//#include <time.h>
//#include <windows.h>
//#include <cmath>
//#include <limits>
//#include <string>
//#include <vector>
//#include <sstream>
//#include <fstream>
//#include <iostream>
//#include <algorithm>
//#include <unordered_map> 
//using namespace std;
//
//const double inf = numeric_limits<double>::infinity();
//
//struct Point {
//	string name;
//	int x;
//	int y;
//
//	// Constructor
//	Point(string name, int x, int y) {
//		this->name = name;
//		this->x = x;
//		this->y = y;
//	}
//
//	string toString() {
//		stringstream ss;
//		ss << "Name: " + name << "\n"
//			<< "X-Pos: " << x << "\n"
//			<< "Y-Pos: " << y << "\n";
//		return ss.str();
//	}
//};
//
//struct Path {
//	vector<string> path_arr;
//	double cost;
//
//	Path() {
//		this->path_arr = vector<string>();
//		this->cost = inf;
//	}
//
//	Path(vector<string> path_arr, double cost) {
//		this->path_arr = path_arr;
//		this->cost = cost;
//	}
//
//	string toString() {
//		stringstream ss;
//		ss << "Shortest Path: ";
//		for (int i = 0; i < path_arr.size(); i++) {
//			ss << path_arr[i];
//			if (i < path_arr.size() - 1) ss << " -> ";
//		}
//		ss << "\n"
//			<< "Minimum Cost: " << cost;
//		return ss.str();
//	}
//
//	void printPath(ostream& out) {
//		for (int i = 0; i < path_arr.size(); i++) {
//			out << path_arr[i] << endl;
//		}
//	}
//};
//
//Path minPath(Path pth1, Path pth2) {
//	return (pth1.cost < pth2.cost) ? pth1 : pth2;
//
//}
//
//double distance(Point p1, Point p2) {
//	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
//}
//
//vector<string> split(string str, string delim) {
//	vector<string> tmp_arr;
//	int ind = 0;
//	string token = "";
//	while ((ind = str.find(delim)) != string::npos) {
//		token = str.substr(0, ind);
//		tmp_arr.push_back(token);
//		str.erase(0, ind + delim.length());
//	}
//	tmp_arr.push_back(str);
//	return tmp_arr;
//}
//
//bool containsSubStr(string str, string str2) {
//	return str.find(str2) != string::npos;
//}
//
//// [To Optimize Start]
//// Create Adjacency Matrix
//vector<vector<double>> create_adj_mat(vector<Point> pt_arr) {
//	int x_ind(0), y_ind(0), n(pt_arr.size());
//
//	vector<vector<double>> adj_mat(n, vector<double>(n, inf));
//
//	bool flag = false;
//
//	for (Point pt : pt_arr) {
//		string name = pt.name;
//
//		y_ind = 0;
//
//		for (Point pt2 : pt_arr) {
//			flag = pt.name == pt2.name || (containsSubStr(pt.name, "Depot") && containsSubStr(pt2.name, "Point")) || (containsSubStr(pt.name, "Point") && containsSubStr(pt2.name, "Point"));
//			if (!flag) adj_mat[x_ind][y_ind] = distance(pt, pt2);
//			y_ind++;
//		}
//
//		x_ind++;
//	}
//	return adj_mat;
//}
//
//// Create Parcel Array
//vector<int> create_parcel_arr(vector<Point> pt_arr) {
//	vector<int> parcel_arr;
//
//	for (int i = 0; i < pt_arr.size(); i++) {
//		if (containsSubStr(pt_arr[i].name, "Parcel")) {
//			parcel_arr.push_back(i);
//		}
//	}
//
//	return parcel_arr;
//}
//
//// Create Point Array
//vector<int> create_point_arr(vector<Point> pt_arr) {
//	vector<int> point_arr;
//
//	for (int i = 0; i < pt_arr.size(); i++) {
//		if (containsSubStr(pt_arr[i].name, "Point")) {
//			point_arr.push_back(i);
//		}
//	}
//
//	return point_arr;
//}
//
//vector<vector<int>> combinations(int start, int end, int r) {
//	vector<vector<int>> combs;
//
//	if (r > end)
//		return combs;
//
//	vector<int> a(r);
//	for (int i = 0; i < r; ++i) {
//		a[i] = i;
//	}
//
//	if (a[0] >= start) {
//		combs.push_back(a);
//	}
//
//	while (true) {
//		int i = r - 1;
//		while (i >= 0 && a[i] >= end - 1 - (r - 1 - i)) {
//			i--;
//		}
//		if (i < 0) {
//			break;
//		}
//		for (int j = a[i] + 1; i < r; j++, i++) {
//			a[i] = j;
//		}
//		if (a[0] >= start) {
//			combs.push_back(a);
//		}
//	}
//
//	return combs;
//}
//
//// Combination Without Duplicate
//// Suspicious Point
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
//
//	while (true) {
//		combs.push_back(b);
//
//		int i = r - 1;
//
//		while (i >= 0 && a[i] >= end - 1 - (r - 1 - i)) {
//			i--;
//		}
//
//		if (i < 0) {
//			break;
//		}
//
//		for (int j = a[i] + 1; i < r; j++, i++) {
//			a[i] = j;
//			b[i] = col_list[j];
//		}
//	}
//
//	return combs;
//}
//
//// Held-Karp Algorithm
//// Uses bitmask Backtracking to make algorithm Run Faster
//Path HeldKarp(vector<vector<double>> distance, vector<int> parcel_arr, vector<int> point_arr, vector<string> name_arr) {
//	const int n = distance.size();
//
//	// Maps each subset of the nodes to the cost to reach that subset, as well
//	// as what node it passed before reaching this subset.
//	// Node subsets are represented as set bits.
//	unordered_map<string, pair <double, unsigned int>> umap;
//	vector<int> subset1, subset2;
//	string key;
//	unsigned long bits, prev, best_bits;
//	bool flag;
//
//	// Set transition cost from initial state
//	for (int k : parcel_arr) {
//		key = to_string(1 << k) + to_string(k); //key as string
//		umap[key] = make_pair(distance[0][k], 0);
//	}
//
//	bits = 0, prev = 0, best_bits = 0;
//	double opt = inf, tmp_opt = 0, best_opt = inf;
//	int parent = -1, best_parent = -1;
//
//	for (int k = 1; k < point_arr.size() + 1; k++) {
//		vector<vector<int>> gSubsetArr = combinations(parcel_arr, k);
//		for (vector<int> gSubset : gSubsetArr) {
//
//			for (int l = k - 1; l < k + 1; l++) {
//				if (l == 0) continue;
//
//				vector<vector<int>> rSubsetArr = combinations(point_arr, l);
//				for (vector<int> rSubset : rSubsetArr) {
//
//					bits = 0;
//
//					for (int bit : gSubset) {
//						bits |= 1 << bit;
//					}
//
//					for (int bit : rSubset) {
//						bits |= 1 << bit;
//					}
//
//					if (gSubset.size() == rSubset.size()) {
//						// The last node FROM THE PREVIOUS SUBSET will be a green point
//						subset2 = gSubset;
//					}
//					else {
//						// The last node FROM THE PREVIOUS SUBSET will be a red point
//						subset2 = rSubset;
//					}
//
//					subset1 = vector<int>(gSubset.size() + rSubset.size(), 0);
//
//					int ind = 0;
//
//					for (int elem : gSubset) {
//						subset1[ind++] = elem;
//					}
//
//					for (int elem : rSubset) {
//						subset1[ind++] = elem;
//					}
//
//					// Find the lowest cost to get to this subset
//					for (int k : subset1) {
//						prev = bits & ~(1 << k);
//
//						opt = inf;
//						parent = -1;
//						flag = false;
//
//						for (int m : subset2) {
//							key = to_string(prev) + to_string(m); // key prev
//
//							// Check if Key exist in our Map
//							if (umap.count(key)) {
//
//								flag = true;
//
//								tmp_opt = umap[key].first + distance[m][k];
//
//								// Replace Value if Current Cost is smaller than Best Cost
//								if (tmp_opt <= opt) {
//									opt = tmp_opt;
//									parent = m;
//								}
//							}
//						}
//
//						if (flag) {
//							key = to_string(bits) + to_string(k);
//							umap[key] = make_pair(opt, parent);
//						}
//					}
//
//					if (gSubset.size() + rSubset.size() == 2 * point_arr.size()) {
//						bits = 0;
//
//						for (int bit : gSubset) {
//							bits |= 1 << bit;
//						}
//
//						for (int bit : rSubset) {
//							bits |= 1 << bit;
//						}
//
//						for (int k : point_arr) {
//
//							key = to_string(bits) + to_string(k); // Prev Key
//							tmp_opt = umap[key].first + distance[k][0];
//
//							// Replace Value if Current Cost is smaller than Best Cost
//							if (tmp_opt <= best_opt) {
//								best_opt = tmp_opt;
//								best_parent = k;
//								best_bits = bits;
//							}
//						}
//
//					}
//				}
//			}
//		}
//	}
//
//	// Sort SubsetObj by Size of Subset
//	/*sort(subset_arr.begin(), subset_arr.end(), [](SubsetObj& a, SubsetObj& b) {
//		return a.size < b.size;
//	});*/
//
//	bits = best_bits;
//
//	// Backtrack to find full path
//	vector<string> path(2 * point_arr.size() + 2, "Depot");
//
//	for (int i = 2 * point_arr.size(); i > 0; i--) {
//		// Map Path Index-Element to Col List Index-Element
//		path[i] = name_arr[best_parent];
//
//		key = to_string(bits) + to_string(best_parent);
//
//		bits = bits & ~(1 << best_parent);
//
//		best_parent = umap[key].second;
//	}
//
//	return Path(path, best_opt);
//}
//
//int main() {
//	string fileName = "tsp.txt";
//
//	vector<Point> pt_arr;
//	vector<string> name_arr;
//
//	// 1. Read Text File and Create Point Array
//	ifstream inFile(fileName);
//
//	if (inFile) {
//		while (!inFile.eof()) {
//			string tmp = "";
//			getline(inFile, tmp);
//			if (tmp == "") break;
//
//			vector<string> tmp_arr = split(tmp, " ");
//
//			string pt_name = tmp_arr[0];
//			int x_pos = stoi(tmp_arr[1]);
//			int y_pos = stoi(tmp_arr[2]);
//
//			Point pt = Point(pt_name, x_pos, y_pos);
//
//			pt_arr.push_back(pt);
//			name_arr.push_back(pt_name);
//		}
//	}
//	else {
//		cout << "File " << fileName << " does not exist" << endl;
//	}
//	inFile.close();
//
//	// 2. Create Adjacency Matrix of Size name_arr.length * name_arr.length
//	vector<vector<double>> adj_mat = create_adj_mat(pt_arr);
//
//	// 3. Create Parcel Array and Point Array
//	vector<int> parcel_arr = create_parcel_arr(pt_arr);
//	vector<int> point_arr = create_point_arr(pt_arr);
//
//	/*cout << "Total Number of Points: " << pt_arr.size() << endl
//		<< "Depot: 1" << endl
//		<< "Number of Red Points: " << point_arr.size() << endl
//		<< "Number of Green Points: " << parcel_arr.size() << endl; */
//
//	clock_t start, stop;
//	start = clock();
//
//	// 4. Get Answer
//	Path ans = HeldKarp(adj_mat, parcel_arr, point_arr, name_arr);
//
//	cout << ans.toString() << endl;
//	stop = clock();
//	cout << "Time Taken: " << ((double)stop - start) << "ms" << endl;
//
//	system("pause");
//
//	// 5. Output Solution
//	ofstream outFile("solution.txt");
//	ans.printPath(outFile);
//	outFile.close();
//
//	// system("pause");
//
//	return 0;
//}