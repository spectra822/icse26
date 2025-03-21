function main(input) {
    input = input.split(" ");
    var a = parseInt(input[0]);
    var b = parseInt(input[1]);
    if((a * b) % 2 == 0) {
        console.log("Even");
    } else {
        console.log("Odd");
    }
}
main(require('fs').readFileSync('/dev/stdin', 'utf8'));