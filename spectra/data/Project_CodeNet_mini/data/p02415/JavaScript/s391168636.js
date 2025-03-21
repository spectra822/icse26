var input = require('fs').readFileSync('/dev/stdin', 'utf8');
input=(input.trim()).replace(/([a-z])|([A-Z])/g,function(s,s1,s2){
if(s1)s=s1.toUpperCase();
if(s2)s=s2.toLowerCase();
return s;
});
console.log(input);