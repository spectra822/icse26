(function(input) {
    var p = input.split('\n');
    var n = Number(p.shift());
    var A = p.slice(0, n);
    var C = [].concat(A);

    partition(A, 0, A.length - 1);
    console.log(check(C, A) ? 'Stable' : 'Not stable');
    console.log(A.join('\n'));
})(require('fs').readFileSync('/dev/stdin', 'utf8'));

function getNumber(a) {
    return Number(a.slice(1, a.length));
}

function getWords(a, n) {
    var r = '';
    for (var i = 0; i < a.length; i++) {
        if (getNumber(a[i]) === n) {
            r += a[i];
        }
    }
    return r;
}

function check(c, a) {
    var i = 0;
    while (i < a.length) {
        var n = getNumber(c[i]);
        if (getWords(c, n) !== getWords(a, n)) {
            return false;
        }

        i++;
    }
    return true;
}

function partition(A, p, r) {
    //console.log(A, p, r);
    if (p >= r || r >= A.length) {
        return;
    }
    var flg = true;
    var minj = p;
    for (var j = p + 1; j <= r; j++) {
        if (getNumber(A[minj]) > getNumber(A[j])) {
            flg = false;
        }
        minj = j;
    }
    if (flg) {
        return;
    }

    //var rnd = Math.floor(Math.random() * (r - p)) + p;
    ////console.log(rnd);
    //var tmp = A[r];
    //A[r] = A[rnd];
    //A[rnd] = tmp;

    var x = A[r];
    var i = p - 1;
    var flg = false;
    for (var j = p; j <= r - 1; j++) {
        if (getNumber(A[j]) <= getNumber(x)) {
            i++;
            var tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
        }
    }
    var tmp = A[i + 1];
    A[i + 1] = A[r];
    A[r] = tmp;

    //console.log(i + 1);
    partition(A, p, i);
    partition(A, i + 2, r);
}