#include <iostream>
#include <cmath>
#include <vector>

typedef long long ll;

using namespace std;

class Solver {
	string s;
    ll m1;
    ll m2;
    ll x;
    vector<ll> h1;
    vector<ll> h2;
    vector<ll> pow1;
    vector<ll> pow2;
public:	
	Solver(string s) : s(s), m1(20000124533), m2(10000127909), x(4), 
      h1(s.size()+1), h2(s.size()+1) {	
      //@log cout << "m1=" << m1 << ", m2=" << m2 << ", x=" << x << "\n";
      fill(h1, m1);
      fill(h2, m2);
      pows();
      //@log cout << "pow1 -> "; print(pow1);
      //@log cout << "pow2 -> "; print(pow2);
      //@log cout << "h1 -> "; print(h1);
      //@log cout << "h2 -> "; print(h2);
	}
	bool ask(int a, int b, int l) {
        //@log cout << "a=" << s.substr(a, l) << ", b=" << s.substr(b, l) << "\n";
        //@log cout << "a=" << hash1(a,l,m1)%m1 << ", b=" << hash1(b,l,m1)%m1 << "\n";
        //@log cout << "a=" << hash2(a,l,m2)%m2 << ", b=" << hash2(b,l,m2)%m2 << "\n";
		return hash1(a,l,m1)%m1 == hash1(b,l,m1)%m1 &&
          hash2(a,l,m2)%m2 == hash2(b,l,m2)%m2;
	}
    void fill(vector<ll> &v, ll mod) {
      v[0] = 0;
      for (size_t i = 1; i < v.size(); ++i)
        v[i] = (((x * v[i-1]) % mod) + (ll)s[i-1]) % mod;
    }
    void print(const vector<ll> &v) {
      for (auto e : v)
        cout << e << " ";
      cout << "\n";
    }
    ll hash1(int i, int j, ll mod) {
      return h1[i+j] - (((pow1[j]*h1[i])%mod+mod)%mod);
    }
    ll hash2(int i, int j, ll mod) {
      return h2[i+j] - (((pow2[j]*h2[i])%mod+mod)%mod);
    }
    void pows() {
      pow1.push_back(1);
      pow2.push_back(1);
      for (size_t i = 1; i <= s.size(); ++i) {
        pow1.push_back(((pow1[i-1]*x)%m1+m1)%m1);
        pow2.push_back(((pow2[i-1]*x)%m2+m2)%m2);
      }
  }
};

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	string s;
	int q;
	cin >> s >> q;
	Solver solver(s);
	for (int i = 0; i < q; i++) {
		int a, b, l;
		cin >> a >> b >> l;
		cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
	}
}
