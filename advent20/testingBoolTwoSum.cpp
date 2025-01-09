bool twoSumExists(deque <int> dq, int target) {
    unordered_map <int, int> m;
    int ct = 0;
    for (auto x : dq) {
        if (m.find(target-x) != m.end()) {
            return true;
        } else {
            m[ct] = x;
        }
    }
    return false;
}

