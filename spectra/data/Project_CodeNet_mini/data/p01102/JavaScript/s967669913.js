const input = require('fs').readFileSync('/dev/stdin', 'utf8').trim()
const lines = input.trim().split("\n")
while (lines.length > 2) {
    const s1 = lines.shift().trim(), _s1 = s1.split('"')
    const s2 = lines.shift().trim(), _s2 = s2.split('"')
    if(s1 === s2) {
        console.log('IDENTICAL')
    } else {

        if(_s1.length !== _s2.length) {
            console.log('DIFFERENT')
        } else {
            let rs
            let dif = false
            const l = _s1.length
            for (let i = 0; i < l; i++) {
                if(_s1[i] !== _s2[i]){
                    if(i%2) {
                        if(dif) {
                            rs = 'DIFFERENT'
                        } else {
                            dif = true
                        }
                    } else {
                        rs = 'DIFFERENT'
                        break
                    }
                }
            }
            console.log(rs === 'DIFFERENT'? rs: 'CLOSE')
        }
    }
}
