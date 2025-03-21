"use strict";
var input=require("fs").readFileSync("/dev/stdin","utf8");
var cin=input.split(/ |\n/),cid=0;
function next(){return +cin[cid++];}
function nextstr(){return cin[cid++];}
function nextbig(){return BigInt(cin[cid++]);}
function nexts(n,a){return a?cin.slice(cid,cid+=n):cin.slice(cid,cid+=n).map(a=>+a);}
function nextssort(n,a){return a?cin.slice(cid,cid+=n).map(a=>+a).sort((a,b)=>b-a):cin.slice(cid,cid+=n).map(a=>+a).sort((a,b)=>a-b);}
function nextm(h,w,a){var r=[],i=0;if(a)for(;i<h;i++)r.push(cin.slice(cid,cid+=w));else for(;i<h;i++)r.push(cin.slice(cid,cid+=w).map(a=>+a));return r;}
function xArray(v){var a=arguments,l=a.length,r="Array(a["+--l+"]).fill().map(x=>{return "+v+";})";while(--l)r="Array(a["+l+"]).fill().map(x=>"+r+")";return eval(r);}
var streams=[];function print(s){streams.push(s);}

var priorityQueue=(function(){
  function f(){return new PriorityQueue();}
  function PriorityQueue(){
    this.heap=[];
  }
  PriorityQueue.prototype.push=function(x){
    var h=this.heap,i=h.length++,j;
    while(i){
      j=i-1>>1;
      if(h[j][0]<=x[0])break;
      h[i]=h[j],i=j;
    }
    h[i]=x;
  };
  PriorityQueue.prototype.pop=function(){
    var h=this.heap,r=h[0],x=h.pop(),l=h.length,i=0,j;
    if(l===0)return r;
    var k=l>>1;l--;
    while(i<k){
      j=(i<<1)+1;
      if(j<l&&h[j+1][0]<h[j][0])j++;
      if(x[0]<=h[j][0])break;
      h[i]=h[j],i=j;
    }
    h[i]=x;
    return r;
  };
  return f;
})();


//頂点数nで初期化
//add(from,to,流せる量,コスト)で辺追加
//minCostFlow(start,goal,流量)でコストの最小値、-1で流せない
var MinCostFlow=(function(){
  var e,INF=1e15;
  function f(n){return new PrimalDual(n);}
  function PrimalDual(n){
    e=this.edge=Array(n).fill(0).map(a=>[]);
  }
  
  PrimalDual.prototype.add=function(from,to,cap,cost){
    e[from].push([to,cap,cost,e[to].length]);
    e[to].push([from,0,-cost,e[from].length-1]);
  }
  
  PrimalDual.prototype.minCostFlow=function(start,goal,flow){
    var s=start,g=goal,f=flow;
    var v=e.length,r=0,pq=priorityQueue();
    var potential=Array(v).fill(0);
    var preve=Array(v).fill(-1);
    var prevv=Array(v).fill(-1);
    while(f){
      var minCost=Array(v).fill(INF);
      minCost[s]=0;
      pq.push([0,s]);
      while(pq.heap.length){
        var p=pq.pop();
        if(minCost[p[1]]<p[0])continue;
        for(var i=0;i<e[p[1]].length;i++){
          var ei=e[p[1]][i];
          if(ei[1]<=0)continue;
          var nextCost=minCost[p[1]]+ei[2]+potential[p[1]]-potential[ei[0]];
          if(nextCost<minCost[ei[0]]){
            minCost[ei[0]]=nextCost;
            prevv[ei[0]]=p[1],preve[ei[0]]=i;
            pq.push([nextCost,ei[0]]);
          }
        }
      }
      if(minCost[g]===INF)return -1;
      for(var i=0;i<v;i++)potential[i]+=minCost[i];
      var addFlow=f;
      for(var i=g;i!==s;i=prevv[i]){
        if(e[prevv[i]][preve[i]][1]<addFlow)addFlow=e[prevv[i]][preve[i]][1];
      }
      f-=addFlow;
      r+=addFlow*potential[g];
      for(var i=g;i!=s;i=prevv[i]){
        var ei=e[prevv[i]][preve[i]];
        ei[1]-=addFlow;
        e[i][ei[3]][1]+=addFlow;
      }
    }
    return r;
  }
  return f;
})();


var myOut = main();
if(myOut !== undefined)console.log(String(myOut));
if(streams.length)console.log(streams.join("\n"));

function main(){
  var inf = 1e9;
  var [n,m] = nexts(2);
  var s = nexts(n,1);
  var g = m*n+1;
  var mf = new MinCostFlow(g+1);
  var cnt = 0;
  for(var y = 0; y < n; y++){
    for(var x = 0; x < m; x++){
      var z = y*m+x+1;
      if(s[y][x] === "#")continue;
      if(s[y][x] === "o")mf.add(0,z,1,0),cnt++;
      mf.add(z,g,1,0);
      if(x+1 < m && s[y][x+1] !== "#")mf.add(z,z+1,inf,-1);
      if(y+1 < n && s[y+1][x] !== "#")mf.add(z,z+m,inf,-1);
    }
  }
  return -mf.minCostFlow(0,g,cnt);
}