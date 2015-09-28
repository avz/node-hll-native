# Native HyperLogLog for node.js

See http://en.wikipedia.org/wiki/HyperLogLog

Example
==

```js
var HLL = require('hll-native').HLL;

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
```
```
[1 / 5] Approximated set size: 10000341. Elapsed time: 2142 ms
[2 / 5] Approximated set size: 10000341. Elapsed time: 2133 ms
[3 / 5] Approximated set size: 10000341. Elapsed time: 2142 ms
[4 / 5] Approximated set size: 10000341. Elapsed time: 2121 ms
[5 / 5] Approximated set size: 10000341. Elapsed time: 2118 ms
```

Memory Usage
==

|bits|size (bytes) | standard error  |
|----|---------|--------|
|  4 |      16 | 26.00% |
|  5 |      32 | 18.38% |
|  6 |      64 | 13.00% |
|  7 |     128 |  9.19% |
|  8 |     256 |  6.50% |
|  9 |     512 |  4.60% |
| 10 |    1024 |  3.25% |
| 11 |    2048 |  2.30% |
| 12 |    4096 |  1.62% |
| 13 |    8192 |  1.15% |
| 14 |   16384 |  0.81% |
| 15 |   32768 |  0.57% |
| 16 |   65536 |  0.41% |
| 17 |  131072 |  0.29% |
| 18 |  262144 |  0.20% |
| 19 |  524288 |  0.14% |
| 20 | 1048576 |  0.10% |

Prototype
==
```js
/**
 * Create new HyperLogLog storage with specified size and standard error.
 *
 * Memory usage for storage calculated as (1 << bits) bytes.
 * Standard error described in table above
 *
 * @param {number} bits
 */
var HLL = function(bits) {};

/**
 * Add key to storage
 * @param {string} key
 */
HLL.prototype.add = function(key) {};

/**
 * Get approximated set size with selected standard error
 * @returns {number}
 */
HLL.prototype.count = function() {};
```
