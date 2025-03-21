'use strict';
(function(input){
  input=input.trim().split(/\s+/).map(x=>x-0);
  const N=input.shift();
  
  function Node(id){
    var t=this;
    t.index=id;
    t.connected=[];
    t.depth='not yet scanned';
    t.depth2='not yet scanned';
  }
  
  const nodes=new Array(N+1).fill(0).map((x,i)=>new Node(i));
  nodes[0]='zero';
  
  for(let i=0;i<N-1;i++){
    let u=nodes[input[2*i]];
    let v=nodes[input[2*i+1]];
    u.connected.push(v);
    v.connected.push(u);
  }
  
  const stack=[1];
  var parentsDepth=-1;
  var deepest=nodes[1];
  
  while(stack.length>0){
    let i=stack[stack.length-1];
    //console.log(i);
    let n=nodes[i];
    if(n.depth==='not yet scanned')
      n.depth=parentsDepth+1;
    parentsDepth=n.depth;
    if(n.depth>deepest.depth)
      deepest=n;
    if(n.connected.length>0){
      let c=n.connected[n.connected.length-1];
      if(c.depth==='not yet scanned'){
        stack.push(c.index);
        n.connected.pop();
        continue;
      }else{
        n.connected.pop();
        continue;
      }
    }else stack.pop();
  }
  //console.log(deepest);
  
  for(let i=0;i<N-1;i++){
    let u=nodes[input[2*i]];
    let v=nodes[input[2*i+1]];
    u.connected.push(v);
    v.connected.push(u);
  }
  
  stack.push(deepest.index);
  
  parentsDepth=-1;
  
  while(stack.length>0){
    let i=stack[stack.length-1];
    let n=nodes[i];
    if(n.depth2==='not yet scanned')
      n.depth2=parentsDepth+1;
    parentsDepth=n.depth2;
    if(n.depth2>deepest.depth2)
      deepest=n;
    if(n.connected.length>0){
      let c=n.connected[n.connected.length-1];
      if(c.depth2!=='not yet scanned'){
        n.connected.pop();
        continue;
      }else{
        stack.push(c.index);
        continue;
      }
    }else stack.pop();
  }
  //console.log(deepest);
  
  if(deepest.depth2%3===1)
    console.log('Second');
  else console.log('First');
})(require('fs').readFileSync('/dev/stdin','utf8'));
