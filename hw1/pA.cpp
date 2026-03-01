#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <iterator>
#include <ranges>

using namespace std;

class Solution {
private:
    template <typename T>
    static void printVector(const vector<T> &vec) {
        if (vec.size() == 0) {
            cerr << "empty vector" << endl;
            return;
        }
        for (size_t i = 0; i < vec.size(); ++i) {
            cout << vec[i];
            i != vec.size()-1 ? cout << " " : cout << endl;
        }
    }
public:
    static std::vector<int> nearestSmaller(const vector<int>& arr) {
        stack<int> st;
        vector<int> distance (arr.size(), 0);
        for (int i = static_cast<int>(arr.size() -1); i >= 0; i--) {
            while (!st.empty() && arr.at(i) < arr.at(st.top())) {
                distance.at(st.top()) = st.top() - i;
                st.pop();
            }
            st.push(i);
        }
        while (!st.empty()) {
            distance.at(st.top()) = -1;
            st.pop();
        }
        return distance;
    }
    [[nodiscard]] static std::queue<int> enqueueDistance(const vector<int> &arr) {
        std::queue<int> que;
        for (auto num : arr) {
            if (num != -1) que.push(num);
        }
        return que;
    }
};

int main() {
    while (true) {
        int N;
        if (!(cin >> N)) break;
        cin.ignore();
        vector <int> arr (N);
        {
            string buffer;
            getline(cin, buffer);
            istringstream iss(buffer);
            arr.assign(std::istream_iterator<int>(iss), std::istream_iterator<int>());
        }
        auto distance = Solution::nearestSmaller(arr);
        std::ostream_iterator<int> out(cout, " ");
        std::copy(distance.cbegin(), distance.cend(), out);
        std::cout << std::endl;

        if (auto my_queue = Solution::enqueueDistance(distance); !my_queue.empty()) {
             while (!my_queue.empty()) {
            cout << my_queue.front() << " ";
            my_queue.pop();
            }
            cout << "\n";
        } else {
            cout << "EMPTY" << endl;
        }
    }

    return 0;
}