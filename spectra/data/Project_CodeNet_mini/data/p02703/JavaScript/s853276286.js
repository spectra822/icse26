"use strict";
var input=require("fs").readFileSync("/dev/stdin","utf8");
var cin=input.split(/ |\n/),cid=0;
function next(a){return a?cin[cid++]:+cin[cid++];}
function nexts(n,a){return a?cin.slice(cid,cid+=n):cin.slice(cid,cid+=n).map(a=>+a);}
function nextm(h,w,a){var r=[],i=0;if(a)for(;i<h;i++)r.push(cin.slice(cid,cid+=w));else for(;i<h;i++)r.push(cin.slice(cid,cid+=w).map(a=>+a));return r;}
function xArray(v){var a=arguments,l=a.length,r="Array(a["+--l+"]).fill().map(x=>{return "+v+";})";while(--l)r="Array(a["+l+"]).fill().map(x=>"+r+")";return eval(r);}

class dijkstra{
  constructor(n){
    this.graph = Array(n).fill().map(a=>[]);
  }
  add(u,v,cost){
    this.graph[u].push(v,cost);
  }
  add2(u,v,cost){
    this.graph[u].push(v,cost);
    this.graph[v].push(u,cost);
  }
  solve(start){
    const INF = 1e18;
    const g = this.graph, pq = new priorityQueue(), dp = Array(g.length).fill(INF);
    pq.push(0,start);
    dp[start] = 0;
    while(pq.size){
      const [t,v] = pq.pop();
      if(dp[v] < t)continue;
      for(var i = 0; i < g[v].length; i+=2){
        const V = g[v][i], c = g[v][i+1] + t;
        if(dp[V] <= c)continue;
        dp[V] = c;
        pq.push(c,V);
      }
    }
    return dp;
  }
}

class priorityQueue{
  constructor(){
    this.a=[];
  }
  push(num,inc){
    const a = this.a;
    for(var i = a.length, j; i; i = j){
      j = i - 1 >> 1;
      if(a[j][0] <= num)break;
      a[i] = a[j];
    }
    a[i] = [num,inc];
  }
  pop(){
    const a = this.a, r = a[0], x = a.pop(), k = a.length >> 1;
    for(var i = 0, j; i < k; i = j){
      j = (i << 1) + 1;
      if(a[j+1] && a[j+1][0] < a[j][0])j++;
      if(x[0] <= a[j][0])break;
      a[i] = a[j];
    }
    if(a.length)a[i] = x;
    return r;
  }
  get size(){
    return this.a.length;
  }
  get top(){
    return this.a[0];
  }
}

const mx = 2500;

var myOut = main();
if(myOut !== undefined)console.log(myOut);

function main(){
  var [n,m,s] = nexts(3);
  var g = new dijkstra(mx * n);
  for(var i = 0; i < m; i++){
    var [u,v,a,b] = nexts(4);
    u--,v--;
    u *= mx, v *= mx;
    for(var j = mx; j-- > a;){
      g.add(u+j,v+j-a,b);
      g.add(v+j,u+j-a,b);
    }
  }
  for(var i = 0; i < n; i++){
    var [c,d] = nexts(2);
    var v = i * mx;
    for(var j = 0; j < mx-1; j++)g.add(v+j,v+Math.min(mx-1,j+c),d);
  }
  var dp = g.solve(Math.min(mx-1,s));
  var ans = xArray(1e18,n);
  for(var i = 1; i < n; i++){
    var v = i*mx;
    for(var j = 0; j < mx; j++){
      ans[i] = Math.min(ans[i],dp[v+j]);
    }
  }
  return ans.slice(1).join("\n");
}