console.log(require('fs').readFileSync('/dev/stdin', 'utf8').split(' ').map(Number).sort().join(' '))
