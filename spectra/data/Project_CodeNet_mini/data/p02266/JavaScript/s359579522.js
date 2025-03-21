(function(input) {
    var p = input.replace(/\n$/, '').split('');
    var stack = [];
    var areaStack = [];
    //console.log(p);
    var sum = 0;
    for (var i = 0; i < p.length; i++) {
        var str = p[i];
        switch (str) {
            case '\\':
                stack.push(i);
                break;
            case '/':
                if (!stack.length) {
                    continue;
                }
                var begin = stack.pop()
                var sumArea = i - begin;
                sum += sumArea;
                while (true) {
                    if (!areaStack.length) {
                        break;
                    }
                    var a = areaStack.pop();
                    if (a.i >= begin) {
                        sumArea += a.area;
                    } else {
                        areaStack.push(a);
                        break;
                    }
                }
                areaStack.push({
                    i: begin,
                    area: sumArea
                });
        }
   //     console.log(stack);
    }
    //console.log(areaStack);
    console.log(sum);
    var msg = areaStack.length;
    var areaJoin = areaStack.map(function(e) { return e.area; }).join(' ');
    if (areaJoin) {
        msg += ' ' + areaJoin;
    }
    console.log(msg);
})(require('fs').readFileSync('/dev/stdin', 'utf8'));