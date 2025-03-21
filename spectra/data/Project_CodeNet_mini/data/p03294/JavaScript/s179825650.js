const Main = (input) => {
  const tmp = input.trim().split('\n')
  const N = parseInt(tmp[0])
  const aArr = tmp[1].split(' ').map(Number)

  var result = aArr.reduce((a, x) => a += x, 0) - N

  console.log(result)
  return result
}

Main(require('fs').readFileSync('/dev/stdin', 'utf8'))