(function(input) {
    var p = input.split('\n');
    var n = Number(p.shift());
    var A = p.shift().split(' ').map(Number);

    var i = partition(A, 0, A.length - 1);
    console.log(A.map(function(e, index) {
        if (index === i) {
            return '[' + e + ']';
        }
        return e;
    }).join(' '));
})(require('fs').readFileSync('/dev/stdin', 'utf8'));

function partition(A, p, r) {
    var x = A[r];
    var i = p - 1;
    for (var j = p; j <= r - 1; j++) {
        if (A[j] <= x) {
            i++;
            var tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
        }
    }
    var tmp = A[i + 1];
    A[i + 1] = A[r];
    A[r] = tmp;

    return i + 1;
}