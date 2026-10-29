#include <bits/stdc++.h>
using namespace std;

// ai <= 114514 < 2^17，因此只需要考虑第 0～16 位。
constexpr int BITS = 17;

struct XorBasis {
    array<int, BITS> base{};
    bool hasZero = false; // 是否存在非空子集异或为 0

    void insert(int x) {
        for (int bit = BITS - 1; bit >= 0; --bit) {
            if (((x >> bit) & 1) == 0) continue;

            if (base[bit] == 0) {
                base[bit] = x;
                return;
            }
            x ^= base[bit];
        }

        // 新元素可由此前元素异或得到。
        // 将新元素与此前的对应子集放在一起，就得到非空异或 0。
        hasZero = true;
    }

    int minimumNonemptyXor() const {
        if (hasZero) return 0;

        // 无线性相关时，取最高位最低的那个基向量。
        for (int bit = 0; bit < BITS; ++bit) {
            if (base[bit] != 0) return base[bit];
        }

        // 每次询问至少有一个元素，因此正常情况下不会到这里。
        return 0;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    while (q--) {
        int l, r;
        cin >> l >> r;

        // 17 位向量空间中，任意 18 个向量必线性相关。
        if (r - l + 1 >= BITS + 1) {
            cout << 0 << '\n';
            continue;
        }

        XorBasis basis;
        for (int i = l; i <= r; ++i) {
            basis.insert(a[i]);
        }
        cout << basis.minimumNonemptyXor() << '\n';
    }
    return 0;
}
