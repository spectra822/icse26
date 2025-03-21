let input = ''

process.stdin.resume()
process.stdin.setEncoding('utf8')
process.stdin.on('data', function(chunk) {
  input += chunk
})
process.stdin.on('end', function() {
  input = input.trim().split('\n')
  main()
})

function main() {
    for(i=0; i<input.length; i++) {
        input_line = input[i].split(' ')
        let sort_input_line = input_line.slice()
        sort_input_line.sort(compareNumbers)
        if (input_line[0] > 1000 || input_line[0] < -1000) {
          return
        }

        let a = input_line[0]
        let b = input_line[1]
        let c = input_line[2]
        let d = input_line[3]
        let e = input_line[4]
        let f = input_line[5]

        let x = (b*f - e*c)/(d*b - a*e)
        let y = (c-a*x)/b
        console.log(x.toFixed(3), y.toFixed(3))
    }
}

function compareNumbers(a, b) {
  return b - a;
}
