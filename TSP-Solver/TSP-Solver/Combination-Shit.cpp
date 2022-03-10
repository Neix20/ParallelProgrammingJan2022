//#include <ctime>
//#include <set>
//#include <iostream>
//#include <string>
//#include <sstream>
//#include <vector>
//#include <algorithm>
//#include <fstream>
//#include <cmath>
//#include <limits>
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
//	if (pth1.cost < pth2.cost) return pth1;
//	return pth2;
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
//
//// Combination Shit Cpp
//vector<vector<int>> getPossiblePath3(vector<int> arr, set<int> visited, vector<int> path, int cur, int range){
//	visited.insert(cur);
//	path.push_back(cur);
//
//	vector<vector<int>> final_path;
//
//	if(path.size() == range){
//		final_path.push_back(path);
//	} else{
//		for(int val : arr){
//			if(visited.find(val) == visited.end()){
//				auto tmp_arr = getPossiblePath3(arr, visited, path, val, range);
//				final_path.insert(final_path.end(), tmp_arr.begin(), tmp_arr.end());
//			}
//		}
//	}
//
//	path.pop_back();
//	visited.erase(cur);
//
//	return final_path;
//}
//
//vector<vector<int>> getPossiblePath2(vector<int> arr, int start, int range){
//	set<int> visited;
//
//	vector<int> path;
//
//	return getPossiblePath3(arr, visited, path, start, range);
//}
//
//vector<vector<int>> getPossiblePath(vector<int> arr, int range){
//	vector<vector<int>> combs;
//	for(int val : arr){
//		auto tmp_arr = getPossiblePath2(arr, val, range);
//		combs.insert(combs.end(), tmp_arr.begin(), tmp_arr.end());
//	}
//	return combs;
//}
//
//Path combination_shit(vector<vector<double>> adj_mat, vector<int> parcel_arr, vector<int> point_arr, vector<string> name_arr) {
//	vector<vector<int>> p_possible = getPossiblePath(parcel_arr, point_arr.size());
//	vector<vector<int>> p_point = getPossiblePath(point_arr, point_arr.size());
//
//	cout << "Total Number of Combinations: " << p_possible.size() * p_point.size() << endl;
//
//	bool flag;
//	double cost = 0, min_cost = inf;
//	vector<int> min_path;
//	for (auto parcel_point : p_possible) {
//		for (auto point_point : p_point) {
//			flag = false;
//
//			vector<int> path_arr(2 * point_arr.size() + 2, 0);
//			for (int i = 0; i < parcel_point.size(); i++) {
//				path_arr[2 * i + 1] = parcel_point[i];
//				path_arr[2 * i + 2] = point_point[i];
//			}
//
//			cost = 0;
//			for (int i = 0; i < path_arr.size() - 1; i++) {
//				cost += adj_mat[path_arr[i]][path_arr[i + 1]];
//				if (cost >= min_cost) {
//					flag = true;
//					break;
//				}
//			}
//
//			if (flag) continue;
//
//			min_cost = cost;
//			min_path = path_arr;
//		}
//	}
//
//	vector<string> ans_path(2 * point_arr.size() + 2);
//	for (int i = 0; i < min_path.size(); i++) {
//		ans_path[i] = name_arr[min_path[i]];
//	}
//
//	return Path(ans_path, min_cost);
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
//	// 4. Compute Solution
//	long start, stop;
//
//	start = clock();
//	Path ans_comb_shit = combination_shit(adj_mat, parcel_arr, point_arr, name_arr);
//	cout << ans_comb_shit.toString() << endl;
//	stop = clock();
//
//	cout << "Time Taken: " << stop - start << "ms" << endl;
//
//	system("pause");
//
//
//
//	// ofstream outFile("solution.txt");
//	// ans.printPath(name_arr, cout);
//	// ans.printPath(name_arr, outFile);
//	// outFile.close();
//	return 0;
//}