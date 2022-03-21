#include <ctime>
#include <cmath>
#include <limits>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_map> 
using namespace std;

const double inf = numeric_limits<double>::infinity();

// Point Object is used to create (X,Y) point from the tsp.txt file
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

// Path Object is used to store minimum cost and minimum tour value
struct Path {
	vector<string> path_arr;
	double cost;

	Path() {
		this->path_arr = vector<string>();
		this->cost = inf;
	}

	Path(vector<string> path_arr, double cost) {
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
		ss << "\n"
			<< "Minimum Cost: " << cost;
		return ss.str();
	}

	void printPath(ostream& out) {
		for (int i = 0; i < path_arr.size(); i++) {
			out << path_arr[i] << endl;
		}
	}
};

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

bool containsSubStr(string, string);

string formatLargeNum(int, string);
vector<string> split(string, string);

vector<int> create_point_arr(vector<Point>);
vector<int> create_parcel_arr(vector<Point>);
vector<vector<int>> combinations(vector<int>, int);

int binomialCoeff(int, int);
long gen_total_calculation(int, int);

double distance(Point, Point);
vector<vector<double>> create_adj_mat(vector<Point>);

Path minPath(Path, Path);

// Held-Karp Algorithm
// Uses bitmask Backtracking to make algorithm Run Faster
Path HeldKarpSingleThreadedInt(vector<vector<double>> adj_mat, vector<int> parcel_arr, vector<int> point_arr, vector<string> name_arr) {
	const int n = adj_mat.size(), gN = parcel_arr.size(), rN = point_arr.size();

	// Maps each subset of the nodes to the cost to reach that subset, as well
	// as what node it passed before reaching this subset.
	// Node subsets are represented as set bits.
	unordered_map<long long, pair <double, unsigned int>> umap;

	long subset_size = gen_total_calculation(parcel_arr.size(), point_arr.size());
	vector<SubsetObj> subset_arr(subset_size); // Generate Subset Array

	vector<int> subset1, subset2;

	long long bits, prev, key;
	vector<long long> route_arr;

	bool flag;

	int subset_ind(0), ind(0);

	// Set transition cost from initial state
	for (int k : parcel_arr) {
		key = ((long long)1 << k) * 100 + k; //key as string
		umap[key] = make_pair(adj_mat[0][k], 0);

		vector<int> gSubset = { k };

		for (int l : point_arr) {
			vector<int> rSubset = { l };

			subset_arr[subset_ind++] = SubsetObj(gSubset, rSubset);

			if (rN == 1) {
				bits = 0;

				for (int bit : gSubset) {
					bits |= ((long long)1 << bit);
				}

				for (int bit : rSubset) {
					bits |= ((long long)1 << bit);
				}

				route_arr.push_back(bits);
			}
		}
	}

	vector<vector<vector<int>>> point_comb_arr(rN);
	for (int k = 1; k < rN + 1; k++) {
		point_comb_arr[k - 1] = combinations(point_arr, k);
	}

	for (int k = 2; k < rN + 1; k++) {

		vector<vector<int>> gSubsetArr = combinations(parcel_arr, k);

		for (int l = k - 1; l < k + 1; l++) {

			vector<vector<int>> rSubsetArr = point_comb_arr[l - 1];

			for (vector<int> gSubset : gSubsetArr) {

				for (vector<int> rSubset : rSubsetArr) {

					subset_arr[subset_ind++] = SubsetObj(gSubset, rSubset);

					if ((l + k) == 2 * rN) {
						bits = 0;

						for (int bit : gSubset) {
							bits |= ((long long)1 << bit);
						}

						for (int bit : rSubset) {
							bits |= ((long long)1 << bit);
						}

						route_arr.push_back(bits);
					}
				}
			}
		}
	}

	bits = 0;
	double opt = inf, tmp_opt = 0;
	int parent = 0;

	// Iterate subsets of increasing length and store intermediate results in classic dynamic programming manner
	for (SubsetObj obj : subset_arr) {
		if (obj.parcel_arr.size() == obj.point_arr.size()) {
			// The last node FROM THE PREVIOUS SUBSET will be a green point
			subset2 = obj.parcel_arr;
		}
		else {
			// The last node FROM THE PREVIOUS SUBSET will be a red point
			subset2 = obj.point_arr;
		}

		subset1 = vector<int>(obj.size);

		ind = 0;
		bits = 0;

		for (int elem : obj.parcel_arr) {
			subset1[ind++] = elem;
			bits |= ((long long)1 << elem);
		}

		for (int elem : obj.point_arr) {
			subset1[ind++] = elem;
			bits |= ((long long)1 << elem);
		}

		// Find the lowest cost to get to this subset
		for (int k : subset1) {
			prev = bits & ~((long long)1 << k);

			opt = inf;
			parent = -1;
			flag = false;

			for (int m : subset2) {
				key = prev * 100 + m; //key as string

				// Check if Key exist in our Map
				if (umap.find(key) != umap.end()) {
					flag = true;

					tmp_opt = umap.at(key).first + adj_mat[m][k];

					// Replace Value if Current Cost is smaller than Best Cost
					if (tmp_opt <= opt) {
						opt = tmp_opt;
						parent = m;
					}
				}
			}

			if (flag) {
				key = bits * 100 + k;
				umap[key] = make_pair(opt, parent);
			}
		}
	}

	// Initialize Value
	opt = inf;
	tmp_opt = 0;
	parent = 0;
	bits = 0;

	// Get All Possible Final Paths (E.g. [1 2 3 4], [1 2 4 5], [2 3 4 5])
	for (long long route_bits : route_arr) {
		for (int k : point_arr) {
			key = route_bits * 100 + k;
			tmp_opt = umap.at(key).first + adj_mat[k][0];

			// Replace Value if Current Cost is smaller than Best Cost
			if (tmp_opt <= opt) {
				opt = tmp_opt;
				parent = k;
				bits = route_bits;
			}
		}
	}

	// Backtrack to find full path
	vector<string> path(2 * rN + 2, "Depot");

	for (int i = 2 * rN; i > 0; i--) {
		// Map Path Index-Element to Col List Index-Element
		path[i] = name_arr[parent];
		key = bits * 100 + parent;
		bits = bits & ~((long long)1 << parent);
		parent = umap.at(key).second;
	}

	return Path(path, opt);
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

	//cout << "Total Number of Points: " << pt_arr.size() << endl
	//	<< "Depot: 1" << endl
	//	<< "Number of Red Points: " << point_arr.size() << endl
	//	<< "Number of Green Points: " << parcel_arr.size() << endl;

	//// 4. Generate Total Number of Combinations
	//// PLEASE REMEMBER TO REMOVE THIS LINE OF CODE, IT GENERATES ALL POSSIBLE NUMBER OF CALCULATION NEEDED
	//// FOR DEBUGGING PURPOSE ONLY

	//int total = gen_total_calculation(parcel_arr.size(), point_arr.size());
	//cout << endl << "Total Number of Calculations: " << formatLargeNum(total, ",") << endl;

	long start, stop;
	start = clock();

	// 5. Get Answer
	Path ans = HeldKarpSingleThreadedInt(adj_mat, parcel_arr, point_arr, name_arr);

	stop = clock();
	cout << "Time Taken: " << stop - start << "ms" << endl;

	cout << ans.toString() << endl;

	system("pause");

	// 6. Output Solution
	ofstream outFile("solution.txt");
	ans.printPath(outFile);
	outFile.close();

	return 0;
}

Path minPath(Path pth1, Path pth2) {
	return (pth1.cost < pth2.cost) ? pth1 : pth2;
}

// This Function is based on Eucildean Distance between 2 points
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

// [To Optimize Start]
// Create Adjacency Matrix
vector<vector<double>> create_adj_mat(vector<Point> pt_arr) {
	int x_ind(0), y_ind(0), n(pt_arr.size());

	vector<vector<double>> adj_mat(n, vector<double>(n, inf));

	bool flag = false;

	for (Point pt : pt_arr) {
		string name = pt.name;

		y_ind = 0;

		for (Point pt2 : pt_arr) {
			// We set the values to infinity for 4 possible combinations
			// Depot => Point
			// Point => Point
			// Parcel => Parcel
			// Parcel => Depot
			// This is because if any of the subset violates this condition, it is confirmed to not be the shortest path
			// Therefore, initializing these values as infinity helps to reduce the problem search space.
			flag = pt.name == pt2.name
				|| (containsSubStr(pt.name, "Depot") && containsSubStr(pt2.name, "Point"))
				|| (containsSubStr(pt.name, "Point") && containsSubStr(pt2.name, "Point"))
				|| (containsSubStr(pt.name, "Parcel") && containsSubStr(pt2.name, "Parcel"))
				|| (containsSubStr(pt.name, "Parcel") && containsSubStr(pt2.name, "Depot"));
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

string formatLargeNum(int v, string delim) {
	string s = to_string(v);

	int end = (v >= 0) ? 0 : 1; // Support for negative numbers
	for (int n = s.length() - 3; n > end; n -= 3) {
		s.insert(n, delim);
	}

	return s;
}

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

	while (true) {
		combs.push_back(b);

		int i = r - 1;

		while (i >= 0 && a[i] >= end - 1 - (r - 1 - i)) {
			i--;
		}

		if (i < 0) {
			break;
		}

		for (int j = a[i] + 1; i < r; j++, i++) {
			a[i] = j;
			b[i] = col_list[j];
		}
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