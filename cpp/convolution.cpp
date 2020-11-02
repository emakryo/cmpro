#include"mod_comb.cpp"

constexpr long long pow_mod(long long x, long long n, int m) {
    if(m==1) return 0;
    unsigned int um = m;
    long long y = ((x%um)+um)%um;
    unsigned long long r = 1;
    while(n){
        if(n&1) r = r*y%um;
        y = y*y%um;
        n >>= 1;
    }
    return r;
}

constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
    a = (a%b+b)%b;
    if (a == 0) return {b, 0};

    // Contracts:
    // [1] s - m0 * a = 0 (mod b)
    // [2] t - m1 * a = 0 (mod b)
    // [3] s * |m1| + t * |m0| <= b
    long long s = b, t = a;
    long long m0 = 0, m1 = 1;

    while (t) {
        long long u = s / t;
        s -= t * u;
        m0 -= m1 * u;  // |m1 * u| <= |m1| * s <= b

        // [3]:
        // (s - t * u) * |m1| + t * |m0 - m1 * u|
        // <= s * |m1| - t * u * |m1| + t * (|m0| + |m1| * u)
        // = s * |m1| + t * |m0| <= b

        auto tmp = s;
        s = t;
        t = tmp;
        tmp = m0;
        m0 = m1;
        m1 = tmp;
    }
    // by [3]: |m0| <= b/g
    // by g != b: |m0| < b/g
    if (m0 < 0) m0 += b / s;
    return {s, m0};
}

constexpr int find_primitive_root(int m){
    if(m==2) return 1;
    if(m==167772161) return 3;
    if(m==469762049) return 3;
    if(m==754974721) return 11;
    if(m==998244353) return 3;

    int divs[20] = {};
    divs[0] = 2;
    int cnt = 1;
    int x = (m-1)/2;
    while(x%2==0) x /= 2;
    for(int i=3; (long long)(i)*i<=x; i+=2){
        if(x%i==0){
            divs[cnt++] = i;
            while(x%i==0){
                x /= i;
            }
        }
    }
    if(x>1){
        divs[cnt++] = x;
    }
    for(int g=2;; g++){
        bool ok = true;
        for(int i=0; i<cnt; i++){
            if (pow_mod(g, (m - 1) / divs[i], m) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
}

template<long long m>
constexpr mint<m> primitive_root = mint<m>(find_primitive_root(m));

int bsf(unsigned long long x){
    return __builtin_ctz(x);
}

int ceil_log2(unsigned long long x){
    int n = 0;
    while((1ULL<<n)<x) n++;
    return n;
}

template<typename mint>
void fft(std::vector<mint> &f) {
    static constexpr mint g = primitive_root<mint::mod()>;
    int n = f.size();
    int h = ceil_log2(n);
    assert(1<<h == n);

    static bool init = false;
    static mint sum_e[30];
    if(!init){
        init = true;
        mint es[30], ies[30];
        int cnt2 = bsf(mint::mod() - 1);
        assert(cnt2 >= h);
        mint e = mint(g).pow((mint::mod() - 1) >> cnt2), ie = e.inv();
        for (int i = cnt2; i >= 2; i--) {
            // e^(2^i) == 1
            es[i - 2] = e;
            ies[i - 2] = ie;
            e *= e;
            ie *= ie;
        }
        mint now = 1;
        for (int i = 0; i <= cnt2 - 2; i++) {
            sum_e[i] = es[i] * now;
            now *= ies[i];
        }
    }
    for (int ph = 1; ph <= h; ph++) {
        int w = 1 << (ph - 1), p = 1 << (h - ph);
        mint now = 1;
        for (int s = 0; s < w; s++) {
            int offset = s << (h - ph + 1);
            for (int i = 0; i < p; i++) {
                auto l = f[i + offset];
                auto r = f[i + offset + p] * now;
                f[i + offset] = l + r;
                f[i + offset + p] = l - r;
            }
            now *= sum_e[bsf(~(unsigned int)(s))];
        }
    }
}

template <typename mint>
void ifft(std::vector<mint> &f) {
    static constexpr mint g = primitive_root<mint::mod()>;
    int n = int(f.size());
    int h = ceil_log2(n);
    assert(1<<h == n);

    static bool init = false;
    static mint sum_ie[30];  // sum_ie[i] = es[0] * ... * es[i - 1] * ies[i]
    if (!init) {
        init = true;
        mint es[30], ies[30];  // es[i]^(2^(2+i)) == 1
        int cnt2 = bsf(mint::mod() - 1);
        mint e = mint(g).pow((mint::mod() - 1) >> cnt2), ie = e.inv();
        for (int i = cnt2; i >= 2; i--) {
            // e^(2^i) == 1
            es[i - 2] = e;
            ies[i - 2] = ie;
            e *= e;
            ie *= ie;
        }
        mint now = 1;
        for (int i = 0; i <= cnt2 - 2; i++) {
            sum_ie[i] = ies[i] * now;
            now *= es[i];
        }
    }

    for (int ph = h; ph >= 1; ph--) {
        int w = 1 << (ph - 1), p = 1 << (h - ph);
        mint inow = 1;
        for (int s = 0; s < w; s++) {
            int offset = s << (h - ph + 1);
            for (int i = 0; i < p; i++) {
                auto l = f[i + offset];
                auto r = f[i + offset + p];
                f[i + offset] = l + r;
                f[i + offset + p] =
                    (unsigned long long)(mint::mod() + l.x - r.x) *
                    inow.x;
            }
            inow *= sum_ie[bsf(~(unsigned int)(s))];
        }
    }

    mint z = mint(1<<h).inv();
    for(int i=0; i<f.size(); i++){
        f[i] *= z;
    }
}

template<typename mint>
std::vector<mint> convolution(std::vector<mint> a, std::vector<mint> b){
    int n = a.size(), m = b.size();
    if(std::min(n, m)<=60){
        if(n<m){
            std::swap(n, m);
            std::swap(a, b);
        }
        std::vector<mint> ans(n+m-1);
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                ans[i+j] += a[i] * b[j];
            }
        }
        return ans;
    }

    int z = 1 << ceil_log2(n+m-1);
    a.resize(z);
    b.resize(z);
    fft(a);
    fft(b);
    for(int i=0; i<z; i++) a[i] *= b[i];
    ifft(a);
    a.resize(n+m-1);
    return a;
}

template<long long mod = 998244353>
std::vector<long long> convolution(std::vector<long long> a, std::vector<long long> b){
    using mi = mint<mod>;
    std::vector<mi> a2(a.size()), b2(b.size());
    for(int i=0; i<a.size(); i++) a2[i] = mi(a[i]);
    for(int i=0; i<b.size(); i++) b2[i] = mi(b[i]);

    auto c2 = convolution(move(a2), move(b2));
    int n = a.size() + b.size() - 1;
    std::vector<long long> c(n);
    for(int i=0; i<n; i++){
        c[i] = c2[i].x;
    }
    return c;
}

std::vector<long long> convolution_ll(const std::vector<long long>& a,
                                      const std::vector<long long>& b) {
    int n = a.size(), m = b.size();
    if (!n || !m) return {};

    static constexpr unsigned long long MOD1 = 754974721;  // 2^24
    static constexpr unsigned long long MOD2 = 167772161;  // 2^25
    static constexpr unsigned long long MOD3 = 469762049;  // 2^26
    static constexpr unsigned long long M2M3 = MOD2 * MOD3;
    static constexpr unsigned long long M1M3 = MOD1 * MOD3;
    static constexpr unsigned long long M1M2 = MOD1 * MOD2;
    static constexpr unsigned long long M1M2M3 = MOD1 * MOD2 * MOD3;

    static constexpr unsigned long long i1 = inv_gcd(MOD2 * MOD3, MOD1).second;
    static constexpr unsigned long long i2 = inv_gcd(MOD1 * MOD3, MOD2).second;
    static constexpr unsigned long long i3 = inv_gcd(MOD1 * MOD2, MOD3).second;

    auto c1 = convolution<MOD1>(a, b);
    auto c2 = convolution<MOD2>(a, b);
    auto c3 = convolution<MOD3>(a, b);

    std::vector<long long> c(n + m - 1);
    for (int i = 0; i < n + m - 1; i++) {
        unsigned long long x = 0;
        x += (c1[i] * i1) % MOD1 * M2M3;
        x += (c2[i] * i2) % MOD2 * M1M3;
        x += (c3[i] * i3) % MOD3 * M1M2;
        // B = 2^63, -B <= x, r(real value) < B
        // (x, x - M, x - 2M, or x - 3M) = r (mod 2B)
        // r = c1[i] (mod MOD1)
        // focus on MOD1
        // r = x, x - M', x - 2M', x - 3M' (M' = M % 2^64) (mod 2B)
        // r = x,
        //     x - M' + (0 or 2B),
        //     x - 2M' + (0, 2B or 4B),
        //     x - 3M' + (0, 2B, 4B or 6B) (without mod!)
        // (r - x) = 0, (0)
        //           - M' + (0 or 2B), (1)
        //           -2M' + (0 or 2B or 4B), (2)
        //           -3M' + (0 or 2B or 4B or 6B) (3) (mod MOD1)
        // we checked that
        //   ((1) mod MOD1) mod 5 = 2
        //   ((2) mod MOD1) mod 5 = 3
        //   ((3) mod MOD1) mod 5 = 4
        long long M1 = MOD1;
        long long diff =
            c1[i] - ((long long)(x)%M1+M1)%M1;
        if (diff < 0) diff += MOD1;
        static constexpr unsigned long long offset[5] = {
            0, 0, M1M2M3, 2 * M1M2M3, 3 * M1M2M3};
        x -= offset[diff % 5];
        c[i] = x;
    }

    return c;
}
