
'use strict'
const multiply = (a, b) => {

  //2**53-1以上の整数を安全に扱うため、a * b をstringとして実現、出力

  let aa = a
    .toString()
    .split('')
    .reverse()
    .map(v => ~~v)
  let bb = b
    .toString()
    .split('')
    .reverse()
    .map(v => ~~v)
  let cc = Array.apply(null, {
    length: aa.length + bb.length
  }).map(a => 0)

  let ary1 = aa.length >= bb.length ? aa : bb //length（桁）の長い方
  let ary2 = aa.length < bb.length ? aa : bb

  //描く桁ごとに計算　代入する配列の桁は i+j
  //筆算のように扱う

  for (let i = 0; i < ary1.length; i++) {
    for (let j = 0; j < ary2.length; j++) {
      let tmp = ary1[i] * ary2[j]
      cc[i + j] += tmp
    }
  }

  //桁上がり
  for (let i = 0; i < cc.length; i++) {
    let tmp = cc[i]
      .toString()
      .split('')
      .reverse()
      .map(v => ~~v)
    cc[i] = tmp[0]
    for (let j = 1; j < tmp.length; j++) {
      cc[i + j] += tmp[j]
    }
    // console.log(tmp)
  }

  //並び替え、stringに変換、先頭の0を削除
  let tmp = cc.reverse().join('')
  tmp = tmp.replace(/^0+/, '')

  return tmp
}


function main(input) {
  input = input.split(/\r?\n/)
  input = input[1]
    .split(' ')
    .map(v => ~~v)
    .sort((a, b) => b - a)

  let ans = 0
  let sticks = [] // 2本ずつ、2本ずつ、
  let prev = input[0]
  for (let i = 1; i < input.length; i++) {
    if (prev == input[i]) {
      // sticks.push(prev)
      sticks.push(input[i])
      prev = 0
    } else {
      prev = input[i]
    }
  }
  if (sticks.length >= 2) {
    ans = multiply(sticks[0], sticks[1])
    console.log(ans)
  } else {
    console.log(0)
  }
}
main(require("fs").readFileSync("/dev/stdin", "utf8"));