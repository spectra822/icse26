"use strict";
function I(s,f){this._s=s.split("\n");this._c=0;this._l=0;this._f=f||Number}I.prototype.a=function(){var l=this._s[this._l];if(!l)return;var t=l.trim().split(" ");var a=t[this._c];this._c++;if(t.length===this._c){this._c=0;this._l++}return this._f(a)};I.prototype.l=function(){var l=this._s[this._l];if(!l)return;this._c=0;this._l++;return l.split(" ").map(this._f)};
// function build2DArray(r,u,a){for(var f=a||0,n=[],o=0;o<r;o++){for(var h=[],i=0;i<u;i++)h.push(f);n.push(h)}return n}
 
const mod = 998244353;
function main(input) {
  var o = new I(input);
 
  var n = o.a();
  var a = [];
  for (var i = 0; i<n; i++) {
    a.push(o.a());
  }
 
  var sum = a.reduce((acc, cur) => acc + cur, 0);
 
  var total = 1;
  for (var i = 0; i < n; i++) {
    total = (total * 3) % mod;
  }
 
  var ans1 = 0; // R >= S/2

  var dp1 = [1];
  var dp3 = [1];
 
  for (var i = 1; i <= n; i++) {
    var dp2 = Array(dp1.length+a[i-1]).fill(0);
    var dp4 = Array(dp3.length+a[i-1]).fill(0);

    for (var j = 0; j < dp1.length; j++) {
      dp2[j] += dp1[j] * 2;
      dp2[j] %= mod;
      dp4[j] += dp3[j];
      dp4[j] %= mod;

      var next = j + a[i - 1];
      if (next <= sum) {
        dp2[next] += dp1[j];
        dp4[next] += dp3[j];
      }
    }
    dp1 = dp2;
    dp3 = dp4;
  }

  for (var j = Math.ceil(sum/2); j <= sum; j++) {
    ans1 += dp1[j];
  }
 
  var ans2 = 0;
  if (sum % 2 === 0) {
    ans2 = dp3[sum/2];
  }
 
  let ans = (total - ans1 * 3 + ans2 * 3) % mod;
  ans = (ans + mod) % mod;
 
  console.log(ans);
}
 
 
main(require("fs").readFileSync("/dev/stdin", "utf8"));