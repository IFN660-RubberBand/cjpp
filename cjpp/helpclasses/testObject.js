function myobject() {
  this.containedValue = 0;
  this.othercontainedValue = 0;
  this.anothercontainedValue = 0;
}

function yourobject() {
  this.containedValue = 0;
  this.othercontainedValue = 0;
  this.anothercontainedValue = 0;
}

var mything = new myobject();
var yourthing = new yourobject();

var i1 = yourthing - 1;
var i2 = 1 + yourthing;

var x = mything + yourthing;

console.log(i1);
console.log(i2);
console.log(x);
