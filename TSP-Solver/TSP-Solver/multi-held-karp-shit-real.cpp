//#include <set>
//#include <ctime>
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
//			flag = pt.name == pt2.name || (containsSubStr(pt.name, "Depot") && containsSubStr(pt2.name, "Point")) || (containsSubStr(pt.name, "Point") && containsSubStr(pt2.name, "Point")) || (containsSubStr(pt.name, "Parcel") && containsSubStr(pt2.name, "Parcel")) || (containsSubStr(pt.name, "Parcel") && containsSubStr(pt2.name, "Depot"));
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
//// [To Optimize End]
//
//vector<vector<double>> gen_adj_mat(vector<vector<double>> adj_mat, vector<int> col_list) {
//
//	int n = col_list.size(), x_ind(0);
//
//	vector<vector<double>> tmp_adj_mat(n, vector<double>(n, inf));
//
//	for (int i = 0; i < adj_mat.size(); i++) {
//		if (find(col_list.begin(), col_list.end(), i) != col_list.end()) {
//			for (int j = 0; j < n; j++) {
//				int col_ind = col_list[j];
//				tmp_adj_mat[x_ind][j] = adj_mat[i][col_ind];
//			}
//			x_ind++;
//		}
//	}
//
//	return tmp_adj_mat;
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
//vector<vector<int>> combinations(vector<int> col_list, int r) {
//	vector<vector<int>> combs;
//
//	int end = col_list.size();
//
//	if (r > end)
//		return combs;
//
//	vector<int> a(r), b(r);
//	for (int i = 0; i < r; i++) {
//		a[i] = i;
//		b[i] = col_list[i];
//	}
//
//	while (true) {
//		combs.push_back(b);
//		int i = r - 1;
//		while (i >= 0 && a[i] >= end - 1 - (r - 1 - i)) {
//			i--;
//		}
//		if (i < 0) {
//			break;
//		}
//		for (int j = a[i] + 1; i < r; j++, i++) {
//			a[i] = j;
//			b[i] = col_list[j];
//		}
//	}
//
//	return combs;
//}
//
//vector<vector<int>> generateSubsets(vector<int> col_list, int r) {
//	// returns a std::vector of std::vectors with indexes of combinations n r by r
//	vector< vector<int> > combs;
//	int start = 0;
//	int end = col_list.size();
//	if (r > end) return combs;
//	vector<bool> v(end - start);
//	fill(v.end() - r, v.end(), true);
//	do {
//		int c = 0;
//		vector <int> line;
//		for (int i = 0; i < end - start; ++i) {
//			if (v[i]) {
//				line.push_back(col_list[i + start]);
//				++c;
//			}
//		}
//		combs.push_back(line);
//	} while (next_permutation(v.begin(), v.end()));
//	return combs;
//}
//
//// Held-Karp Algorithm
//// Uses bitmask Backtracking to make algorithm Run Faster
//Path HeldKarpShit(vector<vector<double>> distance, vector<int> col_list, vector<string> name_arr) {
//	const int n = distance.size();
//
//	// Maps each subset of the nodes to the cost to reach that subset, as well
//	// as what node it passed before reaching this subset.
//	// Node subsets are represented as set bits.
//	unordered_map<string, pair <double, unsigned int>> umap;
//	string key;
//	pair <double, unsigned int> value, best;
//	unsigned long bits, prev;
//
//	// Set transition cost from initial state
//	for (int k = 0; k < n; k++) {
//		key = to_string(1 << k) + to_string(k); //key as string
//		value = make_pair(distance[0][k], 0);
//		umap[key] = value;
//	}
//
//	// Iterate subsets of increasing length and store intermediate results in classic dynamic programming manner
//	for (int subsize = 2; subsize < n; subsize++) {
//		for (auto subset : combinations(1, n, subsize)) {
//			// A subset of nodes {0,2,3,5} can be represented by the 2^0+2^3+2^5=10101 in base 2
//
//			// Set bits for all nodes in this subset
//			bits = 0;
//			for (auto bit : subset) {
//				bits |= 1 << bit;
//			}
//
//			// Find the lowest cost to get to this subset
//			for (auto k : subset) {
//				prev = bits & ~(1 << k);
//				best = make_pair(inf, 0);
//				for (auto m : subset) {
//					if (m == k || m == 0) continue;
//					key = to_string(prev) + to_string(m); // key prev
//					value = make_pair(umap[key].first + distance[m][k], m); //new value
//					best = (best.first < value.first) ? best : value; // if best < value than best else value
//				}
//				key = to_string(bits) + to_string(k);
//				umap[key] = best;
//			}
//		}
//	}
//
//	// We're interested in all bits but the least significant (the start state)
//	bits = (1 << n) - 2;
//
//	// Calculate Optimal Cost
//	best = make_pair(inf, 0);
//
//	for (int k = 1; k < n - 1; k++) {
//		key = to_string(bits) + to_string(k); // key prev
//		value = make_pair(umap[key].first + distance[k][0], k); //new value
//		best = (best.first < value.first) ? best : value; // if best < value than best else value 
//	}
//
//	// Backtrack to find full path
//	vector<int> path(n + 1, 0);
//	vector<string> ans_path(n + 1, "Depot");
//	value = best;
//	for (int i = n - 1; i > 0; i--) {
//		path[i] = value.second;
//
//		// Map Path Index-Element to Col List Index-Element
//		ans_path[i] = name_arr[col_list[path[i]]];
//
//		key = to_string(bits) + to_string(path[i]);
//		value = umap[key];
//		bits = bits & ~(1 << path[i]);
//	}
//
//	return Path(ans_path, best.first);
//}
//
//Path multiHeldKarpShit(vector<vector<double>> adj_mat, vector<int> parcel_arr, vector<int> point_arr, vector<string> name_arr) {
//	// Initialize Answer with Largest Possible Cost
//	Path ans = Path(), p1 = Path();
//
//	// Generate Combinations of Possible Parcel Point
//	// For the final answer, the shortest path will always share the same number of green points and number of red Points
//	// To brute force the solution, we generate all possible combination of green points.
//	int num_of_parcel = point_arr.size();
//	vector<vector<int>> possible_parcel_arr = combinations(parcel_arr, num_of_parcel);
//
//	cout << "Total Number of Combinations: " << possible_parcel_arr.size() << endl;
//
//	// Start Timer to Calculate Time
//
//	vector<vector<double>> tmp_adj_mat;
//
//	vector<int> col_list = vector<int>(2 * num_of_parcel + 1, 0);
//
//	int ind = 1;
//
//	for (auto possible_parcel_set : possible_parcel_arr) {
//
//		// Use Col List
//		for (int i = 0; i < num_of_parcel; i++) {
//			col_list[2 * i + 1] = possible_parcel_set[i];
//			col_list[2 * i + 2] = point_arr[i];
//		}
//
//		sort(col_list.begin(), col_list.end());
//
//		tmp_adj_mat = gen_adj_mat(adj_mat, col_list);
//
//		p1 = HeldKarpShit(tmp_adj_mat, col_list, name_arr);
//
//		ans = minPath(ans, p1);
//
//		ind++;
//	}
//
//	return ans;
//}
//
//// [For Debug Purpose]
//
//int main() {
//
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
//
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
//
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
//	cout << "Total Number of Points: " << pt_arr.size() << endl
//		<< "Depot: 1" << endl
//		<< "Number of Red Points: " << point_arr.size() << endl
//		<< "Number of Green Points: " << parcel_arr.size() << endl;
//
//	// 4. Get Result
//	long start, stop;
//
//	start = clock();
//	cout << endl << "Multiple Held Karp Shit: " << endl;
//	Path ans = multiHeldKarpShit(adj_mat, parcel_arr, point_arr, name_arr);
//	cout << ans.toString() << endl;
//	stop = clock();
//	cout << "Time Taken: " << stop - start << "ms" << endl;
//
//	system("pause");
//
//	// ofstream outFile("solution.txt");
//	// ans.printPath(name_arr, outFile);
//	// outFile.close();
//
//	return 0;
//}