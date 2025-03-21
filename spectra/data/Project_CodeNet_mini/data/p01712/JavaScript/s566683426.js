function main(){
	var n = scan();
	var w = scan();
	var h = scan();

	var x = [];
	rep(w + 1, function(i){
		x[i] = 0;
	});
	var y = [];
	rep(h + 1, function(i){
		y[i] = 0;
	});
	
	rep(n, function(){
		var a = scan();
		var b = scan();
		var c = scan();
		++x[Math.max(a - c, 0)];
		--x[Math.min(a + c, w)];
		++y[Math.max(b - c, 0)];
		--y[Math.min(b + c, h)];
	});

	rep(w, function(i){
		x[i + 1] += x[i];
	});
	rep(h, function(i){
		y[i + 1] += y[i];
	});

	var s = true;
	rep(w, function(i){
		s = x[i] > 0 && s;
	});
	var t = true;
	rep(h, function(i){
		t = y[i] > 0 && t;
	});

	print(s || t ? 'Yes' : 'No');
}
 
function rep(a, b, c){
	if(c == null){
		c = b;
		b = a;
		a = 0;
	}
	for(var i = a; i < b; ++i){
		if(c(i) === false){
			break;
		}
	}
}
 
process.stdin.resume();
process.stdin.setEncoding('utf8');
 
var input = '';
var input_index = 0;
 
function scan(type){
	if(type === 'string'){
		return input[input_index++];
	}
	else{
		return +input[input_index++];
	}
}
 
function print(val){
	console.log(val);
}
 
process.stdin.on('data', function(chunk){
	input += chunk;
});
process.stdin.on('end', function(){
	input = input.split(/\s+/);
	main();
});