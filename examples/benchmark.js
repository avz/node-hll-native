var HLL = require('../main.js').HLL;

var tries = 5;

for(var n = 0; n < tries; n++) {
	var start = Date.now();
	var o = {};

	var obj = new HLL(20);

	for(var i = 0; i < 10000000; i++) {
		obj.add('hello_' + i);
	}

	console.log(
		'[' + (n + 1) + ' / ' + tries + ']',
		'Approximated set size:', obj.count() + '.',
		'Elapsed time:', Date.now() - start, 'ms'
	);
}
