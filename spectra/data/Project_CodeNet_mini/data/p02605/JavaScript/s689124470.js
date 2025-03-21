function Main(input) {
	input = input.trim().split("\n").map(function(x) { return x.split(" ")});
	let N = parseInt(input[0][0], 10);
	let arr_XYU = [];
	for (let i = 0; i < N; i++){
		arr_XYU.push([parseInt(input[i + 1][0],10), parseInt(input[i + 1][1],10), input[i + 1][2]]);
	}

	arr_XYU.sort(function(a, b){
		if ((a[0] + a[1]) < (b[0] + b[1])) return -1;
		if ((a[0] + a[1]) > (b[0] + b[1])) return 1;
        if (a[0] < b[0]) return -1;
        if (a[0] > b[0]) return 1;
        return 0;
	});
	let tmp1 = -1;
	let tmp2;
	let tmp3 = Infinity;
	let tmpAngle = 'U';
	for (let i = 0; i < arr_XYU.length; i++){
		if (tmp1 === (arr_XYU[i][0] + arr_XYU[i][1])){
			if (tmpAngle === 'R'){
				if (arr_XYU[i][2] === 'U') {
					tmpAngle = 'U';
					tmp3 = Math.min(tmp3, Math.abs(arr_XYU[i][0] - tmp2) * 10);
				} else if (arr_XYU[i][2] === 'R'){
					tmp2 = arr_XYU[i][0];
				}
			} else {
				if (arr_XYU[i][2] === 'R') {
					tmpAngle = 'R';
					tmp2 = arr_XYU[i][0];
				}
			}
		} else {
			tmp1 = arr_XYU[i][0] + arr_XYU[i][1];
			if (arr_XYU[i][2] === 'R') {
				tmpAngle = 'R';
				tmp2 = arr_XYU[i][0];
			} else {
				tmpAngle = 'U';
			}
		}
	}
	// console.log(arr_XYU, tmp3);

	tmp1 = -1;
	tmpAngle = 'L';
	for (let i = 0; i < arr_XYU.length; i++){
		if (tmp1 === (arr_XYU[i][0] + arr_XYU[i][1])){
			if (tmpAngle === 'D'){
				if (arr_XYU[i][2] === 'L') {
					tmpAngle = 'L';
					tmp3 = Math.min(tmp3, Math.abs(arr_XYU[i][0] - tmp2) * 10);
				} else if (arr_XYU[i][2] === 'D'){
					tmp2 = arr_XYU[i][0];
				}
			} else {
				if (arr_XYU[i][2] === 'D') {
					tmpAngle = 'D';
					tmp2 = arr_XYU[i][0];
				}
			}
		} else {
			tmp1 = arr_XYU[i][0] + arr_XYU[i][1];
			if (arr_XYU[i][2] === 'D') {
				tmpAngle = 'D';
				tmp2 = arr_XYU[i][0];
			} else {
				tmpAngle = 'L';
			}
		}
	}
	// console.log(arr_XYU, tmp3);

	arr_XYU.sort(function(a, b){
		if ((a[1] - a[0]) < (b[1] - b[0])) return -1;
		if ((a[1] - a[0]) > (b[1] - b[0])) return 1;
        if (a[0] < b[0]) return -1;
        if (a[0] > b[0]) return 1;
        return 0;
	});

	tmp1 = Infinity;
	tmpAngle = 'D';
	for (let i = 0; i < arr_XYU.length; i++){
		if (tmp1 === (arr_XYU[i][1] - arr_XYU[i][0])){
			if (tmpAngle === 'R'){
				if (arr_XYU[i][2] === 'D') {
					tmpAngle = 'D';
					tmp3 = Math.min(tmp3, Math.abs(arr_XYU[i][0] - tmp2) * 10);
				} else if (arr_XYU[i][2] === 'R'){
					tmp2 = arr_XYU[i][0];
				}
			} else {
				if (arr_XYU[i][2] === 'R') {
					tmpAngle = 'R';
					tmp2 = arr_XYU[i][0];
				}
			}
		} else {
			tmp1 = arr_XYU[i][1] - arr_XYU[i][0];
			if (arr_XYU[i][2] === 'R') {
				tmpAngle = 'R';
				tmp2 = arr_XYU[i][0];
			} else {
				tmpAngle = 'D';
			}
		}
	}
	// console.log(arr_XYU, tmp3);

	tmp1 = Infinity;
	tmpAngle = 'L';
	for (let i = 0; i < arr_XYU.length; i++){
		if (tmp1 === (arr_XYU[i][1] - arr_XYU[i][0])){
			if (tmpAngle === 'U'){
				if (arr_XYU[i][2] === 'L') {
					tmpAngle = 'L';
					tmp3 = Math.min(tmp3, Math.abs(arr_XYU[i][0] - tmp2) * 10);
				} else if (arr_XYU[i][2] === 'U'){
					tmp2 = arr_XYU[i][0];
				}
			} else {
				if (arr_XYU[i][2] === 'U') {
					tmpAngle = 'U';
					tmp2 = arr_XYU[i][0];
				}
			}
		} else {
			tmp1 = arr_XYU[i][1] - arr_XYU[i][0];
			if (arr_XYU[i][2] === 'U') {
				tmpAngle = 'U';
				tmp2 = arr_XYU[i][0];
			} else {
				tmpAngle = 'L';
			}
		}
	}
	// console.log(arr_XYU, tmp3);

	arr_XYU.sort(function(a, b){
		if (a[0] < b[0]) return -1;
        if (a[0] > b[0]) return 1;
		if (a[1] < b[1]) return -1;
        if (a[1] > b[1]) return 1;
        return 0;
	});
	tmp1 = -1;
	tmpAngle = 'D';
	for (let i = 0; i < arr_XYU.length; i++){
		if (tmp1 === (arr_XYU[i][0])){
			if (tmpAngle === 'U'){
				if (arr_XYU[i][2] === 'D') {
					tmpAngle = 'D';
					tmp3 = Math.min(tmp3, Math.abs(arr_XYU[i][1] - tmp2) * 5);
				} else if (arr_XYU[i][2] === 'U'){ 
					tmp2 = arr_XYU[i][1]; 
				}
			} else {
				if (arr_XYU[i][2] === 'U') {
					tmpAngle = 'U';
					tmp2 = arr_XYU[i][1];
				}
			}
		} else {
			tmp1 = arr_XYU[i][0];
			if (arr_XYU[i][2] === 'U') {
				tmpAngle = 'U';
				tmp2 = arr_XYU[i][1];
			} else {
				tmpAngle = 'D';
			}
		}
	}
	// console.log(arr_XYU, tmp3);

	arr_XYU.sort(function(a, b){
		if (a[1] < b[1]) return -1;
        if (a[1] > b[1]) return 1;
		if (a[0] < b[0]) return -1;
        if (a[0] > b[0]) return 1;
        return 0;
	});

	tmp1 = -1;
	tmpAngle = 'L';
	for (let i = 0; i < arr_XYU.length; i++){
		if (tmp1 === (arr_XYU[i][1])){
			if (tmpAngle === 'R'){
				if (arr_XYU[i][2] === 'L') {
					tmpAngle = 'L';
					tmp3 = Math.min(tmp3, Math.abs(arr_XYU[i][0] - tmp2) * 5);
				} else if (arr_XYU[i][2] === 'R'){ 
					tmp2 = arr_XYU[i][0]; 
				}
			} else {
				if (arr_XYU[i][2] === 'R') {
					tmpAngle = 'R';
					tmp2 = arr_XYU[i][0];
				}
			}
		} else {
			tmp1 = arr_XYU[i][1];
			if (arr_XYU[i][2] === 'R') {
				tmpAngle = 'R';
				tmp2 = arr_XYU[i][0];
			} else {
				tmpAngle = 'L';
			}
		}
	}
	ans = tmp3 === Infinity ? "SAFE" : tmp3;
	console.log(ans);
}


Main(require("fs").readFileSync("/dev/stdin", "utf8"));
