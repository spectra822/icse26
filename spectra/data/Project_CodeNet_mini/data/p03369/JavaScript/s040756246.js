function main(input){
  input = input.split('');
  var egg = input[0];
  var meat = input[1];
  var veg = input[2];
  var ndl = 700;
  if(egg === 'o'){
    ndl += 100
  }
  if(meat === 'o'){
    ndl += 100
  }
  if(veg === 'o'){
    ndl += 100
  }
  console.log(ndl);
}
main(require('fs').readFileSync('/dev/stdin', 'utf8'));