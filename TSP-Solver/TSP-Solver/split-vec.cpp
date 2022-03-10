//// Uses bitmask Backtracking to make algorithm Run Faster
//Path HeldKarp(vector<vector<double>> adj_mat, vector<int> parcel_arr, vector<int> point_arr, vector<string> name_arr) {
//	const int gN = parcel_arr.size(), rN = point_arr.size();
//
//	// Maps each subset of the nodes to the cost to reach that subset, as well
//	// as what node it passed before reaching this subset.
//	// Node subsets are represented as set bits.
//	unordered_map<string, pair <double, unsigned int>> umap;
//	string key;
//	unsigned long bits, prev;
//	bool flag;
//
//	// Set transition cost from initial state
//	for (int k : parcel_arr) {
//		key = to_string(1 << k) + to_string(k); //key as string
//		umap[key] = make_pair(adj_mat[0][k], 0);
//	}
//
//	vector<SubsetObj> subset_arr; // Generate Subset Array
//	// Generate All Possible Combinations and populate subset Array
//	for (int k : parcel_arr) {
//		vector<int> gSubset = { k };
//		for (int l : point_arr) {
//			vector<int> rSubset = { l };
//			subset_arr.emplace_back(SubsetObj(gSubset, rSubset));
//		}
//	}
//
//	for (int k = 2; k < rN + 1; k++) {
//		vector<vector<int>> gSubsetArr = combinations(parcel_arr, k);
//		for (vector<int> gSubset : gSubsetArr) {
//			for (int l = k - 1; l < k + 1; l++) {
//				vector<vector<int>> rSubsetArr = combinations(point_arr, l);
//				for (vector<int> rSubset : rSubsetArr) {
//					subset_arr.emplace_back(SubsetObj(gSubset, rSubset));
//				}
//			}
//		}
//	}
//
//	bits = 0;
//	double opt = inf, tmp_opt = 0;
//	int parent = 0;
//	vector<int> subset1, subset2;
//
//	// Iterate subsets of increasing length and store intermediate results in classic dynamic programming manner
//	for (SubsetObj obj : subset_arr) {
//		bits = 0;
//		for (int bit : obj.parcel_arr) { bits |= 1 << bit; }
//		for (int bit : obj.point_arr) { bits |= 1 << bit; }
//		if (obj.parcel_arr.size() == obj.point_arr.size()) {
//			// The last node FROM THE PREVIOUS SUBSET will be a green point
//			subset2 = obj.parcel_arr;
//		}
//		else {
//			// The last node FROM THE PREVIOUS SUBSET will be a red point
//			subset2 = obj.point_arr;
//		}
//		subset1 = vector<int>(obj.size);
//		int ind = 0;
//		for (int elem : obj.parcel_arr) { subset1[ind++] = elem; }
//		for (int elem : obj.point_arr) { subset1[ind++] = elem; }
//		// Find the lowest cost to get to this subset
//		for (int k : subset1) {
//			prev = bits & ~(1 << k);
//			opt = inf;
//			parent = -1;
//			flag = false;
//			for (int m : subset2) {
//				key = to_string(prev) + to_string(m); // key prev
//				// Check if Key exist in our Map
//				if (umap.find(key) != umap.end()) {
//					flag = true;
//					tmp_opt = umap.at(key).first + adj_mat[m][k];
//					// Replace Value if Current Cost is smaller than Best Cost
//					if (tmp_opt <= opt) {
//						opt = tmp_opt;
//						parent = m;
//					}
//				}
//			}
//			if (flag) {
//				key = to_string(bits) + to_string(k);
//				umap[key] = make_pair(opt, parent);
//			}
//		}
//	}
//
//	// Initialize Value
//	opt = inf;
//	tmp_opt = 0;
//	parent = 0;
//	bits = 0;
//
//	vector<int> route_arr;
//	for (SubsetObj obj : subset_arr) {
//		if (obj.size == 2 * rN) {
//			bits = 0;
//			for (int bit : obj.parcel_arr) { bits |= 1 << bit; }
//			for (int bit : obj.point_arr) { bits |= 1 << bit; }
//			route_arr.push_back(bits);
//		}
//	}
//
//	// Get All Possible Final Paths (E.g. [1 2 3 4], [1 2 4 5], [2 3 4 5])
//	for (int route_bits : route_arr) {
//		for (int k : point_arr) {
//			key = to_string(route_bits) + to_string(k); // Prev Key
//			tmp_opt = umap.at(key).first + adj_mat[k][0];
//			// Replace Value if Current Cost is smaller than Best Cost
//			if (tmp_opt <= opt) {
//				opt = tmp_opt;
//				parent = k;
//				bits = route_bits;
//			}
//		}
//	}
//
//	// Backtrack to find full path
//	vector<string> path(2 * rN + 2, "Depot");
//
//	for (int i = 2 * rN; i > 0; i--) {
//		// Map Path Index-Element to Col List Index-Element
//		path[i] = name_arr[parent];
//		key = to_string(bits) + to_string(parent);
//		bits = bits & ~(1 << parent);
//		parent = umap.at(key).second;
//	}
//
//	return Path(path, opt);
//}