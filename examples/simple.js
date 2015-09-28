var HLL = require('../main.js').HLL;

for(var n = 0; n < 100000; n++) {
	var start = Date.now();

	var obj = new HLL(20);

	for(var i = 0; i < 100000; i++)
		obj.add(i);

	console.log('Approximated set size:', obj.count(), Date.now() - start);
}