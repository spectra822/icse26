function spilitInput(input) {
  var splited = [];
  var rows = input.split('\n');
  for (var i = 0; i < rows.length; i += 1) {
    splited.push(rows[i].split(' '));
  }
  return splited;
}
function Main(input) {
  var splited = spilitInput(input);
  var n = splited[0][0];
  var a = splited[0][1];
  var b = splited[0][2];
  var s_total = 0;
  for (var i = 1; i <= n; i += 1) {
    var sum = 0;
    String(i).split('').forEach(function(i_n){ sum += parseInt(i_n,10); });
    if (a <= sum && sum <= b) {
      s_total+=i;
    }
  }
  
  console.log(s_total);
}
Main(require("fs").readFileSync("/dev/stdin", "utf8"));