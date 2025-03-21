function Main(input){
	var flag = false;
	input = input.split(" ").map(Number);
	for(var i=0;i<=input[0];i++){
		for(var j=0;j<=input[1];j++){
			if(i*input[1]+j*input[0]-i*j*2==input[2]){
				flag = true;
				break;
			}
		}
	}
	console.log(flag?"Yes":"No");
}Main(require("fs").readFileSync("/dev/stdin", "utf8").trim());