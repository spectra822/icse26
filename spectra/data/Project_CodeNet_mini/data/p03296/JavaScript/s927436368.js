function Main(input){
	input = input.split("\n");
	var sum = 0;
	var now = 1;
	var arr = input[1].split(" ");
	arr.push("#");
	for(var i=1;i<arr.length;i++){
		if(arr[i]==arr[i-1]) now++;
		else{
			sum += Math.ceil((now-1)/2);
			now = 1;
		}
	}
	console.log(sum)
}Main(require("fs").readFileSync("/dev/stdin", "utf8").trim());