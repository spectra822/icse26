(function(input) {
    var p = input.replace(/\n$/, '').split('\n');
    var n = Number(p.shift());
    for (var i = 0; i < n; i++) {
        var args = p[i].split(' ').map(Number);
        //console.log(args);
        var x1 = args.shift();
        var y1 = args.shift();
        var x2 = args.shift();
        var y2 = args.shift();
        var x3 = args.shift();
        var y3 = args.shift();
        var x = ((Math.pow(x3, 2) - Math.pow(x2, 2) + Math.pow(y3, 2) - Math.pow(y2, 2)) * (y2 - y1)
            - (Math.pow(x2, 2) - Math.pow(x1, 2) + Math.pow(y2, 2) - Math.pow(y1, 2)) * (y3 - y2))
            / 2 / ((y2 - y1) * (x3 - x2) - (x2 - x1) * (y3 - y2));
        var y = ((Math.pow(y3, 2) - Math.pow(y2, 2) + Math.pow(x3, 2) - Math.pow(x2, 2)) * (x2 - x1)
            - (Math.pow(y2, 2) - Math.pow(y1, 2) + Math.pow(x2, 2) - Math.pow(x1, 2)) * (x3 - x2))
            / 2 / ((x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2));

        console.log(x.toFixed(3), y.toFixed(3), Math.sqrt(Math.pow(x1 - x, 2) + Math.pow(y1 - y, 2)).toFixed(3));
    }
})(require('fs').readFileSync('/dev/stdin', 'utf8'));