#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <limits>
using namespace std;

const double inf = numeric_limits<double>::infinity();

struct Point {
	string name;
	int x;
	int y;

	// Constructor
	Point(string name, int x, int y) {
		this->name = name;
		this->x = x;
		this->y = y;
	}

	string toString() {
		stringstream ss;
		ss << "Name: " + name << "\n"
			<< "X-Pos: " << x << "\n"
			<< "Y-Pos: " << y << "\n";
		return ss.str();
	}
};

struct Path {
	vector<int> path_arr;
	double cost;

	Path() {
		this->path_arr = vector<int>();
		this->cost = 0;
	}

	Path(vector<int> path_arr, double cost) {
		this->path_arr = path_arr;
		this->cost = cost;
	}

	string toString() {
		stringstream ss;
		ss << "Shortest Path: ";
		for (int i = 0; i < path_arr.size(); i++) {
			ss << path_arr[i];
			if (i < path_arr.size() - 1) ss << " -> ";
		}
		ss << "\n";

		ss << "Minimum Cost: " << cost;
		return ss.str();
	}

	string toNodeString(vector<string> name_arr) {
		stringstream ss;
		ss << "Shortest Path: ";
		for (int i = 0; i < path_arr.size(); i++) {
			int ind = path_arr[i];
			ss << name_arr[ind];
			if (i < path_arr.size() - 1) ss << " -> ";
		}
		ss << "\n";

		ss << "Minimum Cost: " << cost;
		return ss.str();
	}

	void printPath(vector<string> name_arr, ostream& out) {
		for (int i = 0; i < path_arr.size(); i++) {
			int ind = path_arr[i];
			out << name_arr[ind] << endl;
		}
	}
};

Path minPath(Path pth1, Path pth2) {
	if (pth1.cost < pth2.cost) return pth1;
	return pth2;
}

double distance(Point p1, Point p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

vector<string> split(string str, string delim) {
	vector<string> tmp_arr;
	int ind = 0;
	string token = "";
	while ((ind = str.find(delim)) != string::npos) {
		token = str.substr(0, ind);
		tmp_arr.push_back(token);
		str.erase(0, ind + delim.length());
	}
	tmp_arr.push_back(str);
	return tmp_arr;
}

bool containsSubStr(string str, string str2) {
	return str.find(str2) != string::npos;
}

// Create Adjacency Matrix
vector<vector<double>> create_adj_mat(vector<Point> pt_arr) {
	int x_ind(0), y_ind(0), n(pt_arr.size());

	vector<vector<double>> adj_mat(n, vector<double>(n, inf));

	bool flag = false;

	for (Point pt : pt_arr) {
		string name = pt.name;

		y_ind = 0;

		for (Point pt2 : pt_arr) {
			flag = pt.name == pt2.name || (containsSubStr(pt.name, "Depot") && containsSubStr(pt2.name, "Point")) || (containsSubStr(pt.name, "Point") && containsSubStr(pt2.name, "Point")) || (containsSubStr(pt.name, "Parcel") && containsSubStr(pt2.name, "Parcel")) || (containsSubStr(pt.name, "Parcel") && containsSubStr(pt2.name, "Depot"));
			if (!flag) adj_mat[x_ind][y_ind] = distance(pt, pt2);
			y_ind++;
		}

		x_ind++;
	}
	return adj_mat;
}

// Create Parcel Array
vector<int> create_parcel_arr(vector<Point> pt_arr) {
	vector<int> parcel_arr;

	for (int i = 0; i < pt_arr.size(); i++) {
		if (containsSubStr(pt_arr[i].name, "Parcel")) {
			parcel_arr.push_back(i);
		}
	}

	return parcel_arr;
}

// Create Point Array
vector<int> create_point_arr(vector<Point> pt_arr) {
	vector<int> point_arr;

	for (int i = 0; i < pt_arr.size(); i++) {
		if (containsSubStr(pt_arr[i].name, "Point")) {
			point_arr.push_back(i);
		}
	}

	return point_arr;
}

Path calcMinPath2(vector<vector<double>> adj_mat, vector<bool> visited_arr, vector<int> path_arr, double cost, int src, int condition) {
	visited_arr[src] = true;
	path_arr.push_back(src);

	Path min_path(vector<int>(), inf);

	int path_arr_len = path_arr.size();

	if (path_arr_len > 1) {
		int x = path_arr[path_arr_len - 2];
		cost += adj_mat[x][src];
	}

	if (path_arr_len > condition) {
		cost += adj_mat[src][0];

		path_arr.push_back(0);
		min_path = Path(path_arr, cost);
	}
	else {
		for (int i = 0; i < adj_mat[src].size(); i++) {
			if (visited_arr[i] == false && adj_mat[src][i] != inf) {
				Path pth2 = calcMinPath2(adj_mat, visited_arr, path_arr, cost, i, condition);
				min_path = minPath(min_path, pth2);
			}
		}
	}

	path_arr.pop_back();
	visited_arr[src] = false;

	return min_path;
}

Path calcMinPath(vector<vector<double>> adj_mat, vector<string> name_arr, int start_ind) {
	vector<bool> visited_arr(adj_mat.size());
	for (int i = 0; i < visited_arr.size(); i++) visited_arr[i] = false;

	vector<int> path_arr;

	int condition = 0;
	for (string name : name_arr) if (containsSubStr(name, "Point")) condition += 1;
	condition *= 2;

	double cost = 0;

	return calcMinPath2(adj_mat, visited_arr, path_arr, cost, start_ind, condition);
}

int main() {
	string fileName = "tsp.txt";

	vector<Point> pt_arr;
	vector<string> name_arr;

	// 1. Read Text File and Create Point Array
	ifstream inFile(fileName);

	if (inFile) {
		while (!inFile.eof()) {

			string tmp = "";
			getline(inFile, tmp);
			if (tmp == "") break;

			vector<string> tmp_arr = split(tmp, " ");

			string pt_name = tmp_arr[0];
			int x_pos = stoi(tmp_arr[1]);
			int y_pos = stoi(tmp_arr[2]);

			Point pt = Point(pt_name, x_pos, y_pos);

			pt_arr.push_back(pt);
			name_arr.push_back(pt_name);
		}

	}
	else {
		cout << "File " << fileName << " does not exist" << endl;
	}
	inFile.close();


	// 2. Create Adjacency Matrix of Size name_arr.length * name_arr.length
	vector<vector<double>> adj_mat = create_adj_mat(pt_arr);

	// 3. Create Parcel Array and Point Array
	vector<int> parcel_arr = create_parcel_arr(pt_arr);
	vector<int> point_arr = create_point_arr(pt_arr);

	cout << "Total Number of Points: " << pt_arr.size() << endl
		<< "Depot: 1" << endl
		<< "Number of Red Points: " << point_arr.size() << endl
		<< "Number of Green Points: " << parcel_arr.size() << endl;

	// 3. DFS
	long start, stop;
	start = clock();
	Path ans = calcMinPath(adj_mat, name_arr, 0);
	cout << ans.toNodeString(name_arr) << endl;

	stop = clock();

	cout << "Time Taken: " << stop - start << "ms" << endl;

	// ofstream outFile("solution.txt");
	// ans.printPath(name_arr, cout);
	// ans.printPath(name_arr, outFile);
	// outFile.close();
	return 0;
}