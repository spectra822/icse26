
function checkRegularFlights(i, ns, N, cnt) {
    if (cnt <= 2) {
        var dests = (i in ns) ? ns[i] : [];
        for (var i = 0; i < dests.length; i++) {
            var dest = dests[i];
            if (dest == N)
                return true;
            if (checkRegularFlights(dest, ns, N, cnt + 1))
                return true;
        }
    }
    return false;
}
function Main(input) {
    var lines = input.split("\n");
    var ns = [];
    var N = -1;
    for (var i = 0; i < lines.length; i++) {
        var line = lines[i];
        var mc = lines[i].match(/(\d+) (\d+)/);
        if (mc) {
            var n = parseInt(mc[1]);
            var m = parseInt(mc[2]);
            if (!(n in ns))
                ns[n] = [];
            ns[n].push(m);
            if (n > N)
                N = n;
        }
    }
    var result = checkRegularFlights(1, ns, N, 1)
        ? "POSSIBLE"
        : "IMPOSSIBLE";
    console.log(result);
}

// ※この行以降は編集しない (標準入力から一度に読み込みMainを呼び出します)
Main(require("fs").readFileSync("/dev/stdin", "utf8"));
