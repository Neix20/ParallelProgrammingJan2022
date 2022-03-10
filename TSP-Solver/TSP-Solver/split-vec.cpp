//#include <iostream>
//#include <vector>
//using namespace std;
//
//void printVec(vector<int> vec)
//{
//    for (int elem : vec)
//    {
//        cout << elem << " ";
//    }
//    cout << endl;
//}
//
//int main()
//{
//    int max = 11;
//
//    vector<int> vec(max, 0);
//    for (int i = 1; i <= max; i++)
//    {
//        vec[i - 1] = i;
//    }
//
//    // Split into 4 Vectors
//    int num_of_thread = 4;
//    printVec(vector<int>(vec.begin() + 0 * max / 4, vec.begin() + 1 * max / 4));
//    printVec(vector<int>(vec.begin() + 1 * max / 4, vec.begin() + 2 * max / 4));
//    printVec(vector<int>(vec.begin() + 2 * max / 4, vec.begin() + 3 * max / 4));
//    printVec(vector<int>(vec.begin() + 3 * max / 4, vec.begin() + 4 * max / 4));
//
//    return 0;
//}