function Main(s){
  s = s.split("\n");
  var n = +s[0];
  var a = s[1].split(" ").map(a=>+a);
  var b = [];
  b[n-1] = a.reduce((a,z,i)=>{b[i-1]=a;return a+z;});
  var ans = 9e9;
  for(var i = 2; i < n - 1; i++){
    var sl = b[i-1] / 2, sr = (b[n-1] + b[i-1]) / 2;
    var l = lower_bound(b,1,i-1,sl);
    var r = lower_bound(b,i+1,n-1,sr);
    var m = [b[l-1],b[i-1]-b[l-1],b[r-1]-b[i-1],b[n-1]-b[r-1]];
    ans = Math.min(ans, Math.max(...m) - Math.min(...m));
    if(i - l > 1){
      m = [b[l],b[i-1]-b[l],b[r-1]-b[i-1],b[n-1]-b[r-1]];
      ans = Math.min(ans, Math.max(...m) - Math.min(...m));
      if(n - r > 1){
        m = [b[l],b[i-1]-b[l],b[r]-b[i-1],b[n-1]-b[r]];
        ans = Math.min(ans, Math.max(...m) - Math.min(...m));
      }
    }
    if(n - r > 1){
      m = [b[l-1],b[i-1]-b[l-1],b[r]-b[i-1],b[n-1]-b[r]];
      ans = Math.min(ans, Math.max(...m) - Math.min(...m));
    }
  }
  console.log(ans);
}
function lower_bound(d,a,b,e){for(var c;1<b-a;)d[c=0|(a+b)/2]<e?a=c:b=c;return d[a]<e?b:a};
Main(require("fs").readFileSync("/dev/stdin","utf8"));
