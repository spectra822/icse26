(function(input) {
    var p = input.split('\n');
    var n = Number(p.shift());
    var A = p.shift().split(' ').map(Number);

    var B = coutingSort(A, 10000);
    console.log(B.join(' '));
})(require('fs').readFileSync('/dev/stdin', 'utf8'));

function coutingSort(A, k) {
    var C = [];
    for (var i = 0; i <= k; i++) {
        C[i] = 0;
    }
    for (var i = 0; i < A.length; i++) {
        C[A[i]]++;
    }
    //console.log(C);
    for (var i = 1; i <= k; i++) {
        C[i] = C[i] + C[i - 1];
    }
    //console.log(C);
    var B = [];
    for (var i = A.length - 1; i >= 0; i--) {
        //console.log(B);
        B[C[A[i]]] = A[i];
        C[A[i]]--;
        //console.log(B);
    }
    var D = [];
    for (var i = 0; i < B.length; i++) {
        var n = B[i];
        if (typeof(n) !== 'undefined') {
            D.push(n);
        }
    }
    return D;
}