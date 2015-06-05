function foo() {
	return bar();
}

function bar() {
	return "bar";
}

console.log(foo());