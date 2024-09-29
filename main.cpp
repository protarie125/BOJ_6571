#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = int64_t;
using vl = vector<ll>;
using vs = vector<string>;

string NumAdd(const string& x, const string& y) {
  auto cx = x;
  auto cy = y;

  reverse(cx.begin(), cx.end());
  reverse(cy.begin(), cy.end());

  auto oss = ostringstream{};
  auto carry = 0;
  ll i = 0;
  while (i < cx.length() && i < cy.length()) {
    const auto& vx = cx[i] - '0';
    const auto& vy = cy[i] - '0';
    auto val = vx + vy + carry;
    if (val >= 10) {
      carry = 1;
      val -= 10;
    } else {
      carry = 0;
    }
    oss << val;
    ++i;
  }

  while (i < cx.length()) {
    const auto& vx = cx[i] - '0';
    auto val = vx + carry;
    if (val >= 10) {
      carry = 1;
      val -= 10;
    } else {
      carry = 0;
    }
    oss << val;
    ++i;
  }

  while (i < cy.length()) {
    const auto& vy = cy[i] - '0';
    auto val = vy + carry;
    if (val >= 10) {
      carry = 1;
      val -= 10;
    } else {
      carry = 0;
    }
    oss << val;
    ++i;
  }

  if (carry > 0) {
    oss << carry;
  }

  auto ret = oss.str();
  if (ret.length() == 0) {
    return "0";
  }

  reverse(ret.begin(), ret.end());
  return ret;
}

bool NumComp(const string& x, const string& y) {
  if (x.length() != y.length()) {
    return x.length() > y.length();
  }

  for (ll i = 0; i < x.length(); ++i) {
    if (x[i] != y[i]) {
      return x[i] > y[i];
    }
  }

  return false;
}

vs dp;
void memo() {
  for (ll i = 3; i < dp.size(); ++i) {
    dp[i] = NumAdd(dp[i - 1], dp[i - 2]);
  }
}

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  dp = vs(1000, "0");
  dp[1] = "1";
  dp[2] = "2";
  memo();

  string a, b;
  while (true) {
    cin >> a >> b;
    if (a == "0" && b == "0") break;

    ll ans = 0;
    for (auto i = 1; i < dp.size(); ++i) {
      if (!NumComp(a, dp[i]) && !NumComp(dp[i], b)) {
        ++ans;
      }
    }

    cout << ans << '\n';
  }

  return 0;
}