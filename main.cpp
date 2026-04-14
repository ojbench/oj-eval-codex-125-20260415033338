#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU() {}
    explicit DSU(size_t n) { init(n); }
    void init(size_t n) {
        p.resize(n); r.assign(n, 0);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        int a = x;
        while (p[a] != a) a = p[a];
        // Path compression
        while (p[x] != x) { int nx = p[x]; p[x] = a; x = nx; }
        return a;
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
    bool same(int a, int b) { return find(a) == find(b); }
};

static inline bool readInt(int &out) {
    int c = getchar_unlocked();
    while (c != EOF && c <= ' ') c = getchar_unlocked();
    if (c == EOF) return false;
    int x = 0, neg = 0;
    if (c == '-') { neg = 1; c = getchar_unlocked(); }
    for (; c >= '0' && c <= '9'; c = getchar_unlocked()) x = x * 10 + (c - '0');
    out = neg ? -x : x;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Use C IO for maximum speed as advised
    int t;
    if (!readInt(t)) return 0;
    string out;
    out.reserve(t * 4);
    while (t--) {
        int n;
        readInt(n);
        vector<array<int,3>> neq;
        neq.reserve(n);
        // Coordinate compression for variable indices up to 1e9
        vector<pair<int,int>> eq_pairs;
        eq_pairs.reserve(n);
        vector<int> all;
        all.reserve(2u * n);
        for (int k = 0; k < n; ++k) {
            int i, j, e;
            readInt(i); readInt(j); readInt(e);
            all.push_back(i); all.push_back(j);
            if (e == 1) eq_pairs.emplace_back(i, j);
            else neq.push_back({i, j, e});
        }

        sort(all.begin(), all.end());
        all.erase(unique(all.begin(), all.end()), all.end());
        auto getId = [&](int x){ return (int)(lower_bound(all.begin(), all.end(), x) - all.begin()); };
        DSU dsu(all.size());

        for (auto &pr : eq_pairs) {
            int a = getId(pr.first), b = getId(pr.second);
            dsu.unite(a, b);
        }

        bool ok = true;
        for (auto &tr : neq) {
            int a = getId(tr[0]), b = getId(tr[1]);
            if (dsu.same(a, b)) { ok = false; break; }
        }
        if (ok) out += "YES\n"; else out += "NO\n";
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}

