const input = require("fs").readFileSync("/dev/stdin", "utf8")

;(input => {
  
  const lines = input.split('\n')
  
  const map = []
  for (let i = 0; i < 3; i++) {
    map[i] = lines[i].split(' ').map(Number)
  }
  
  let diff1 = 0
  let diff2 = 0

  diff1 = map[0][0] - map[0][1]
  diff2 = map[0][1] - map[0][2]

  
  for (var i = 1; i < 3; i++) {
      if (diff1 !== map[i][0] - map[i][1]) break
      if (diff2 !== map[i][1] - map[i][2]) break
  }
  
  console.log(i === 3 ? 'Yes' : 'No')
 
})(input)
