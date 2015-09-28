// test.js
var HLL = require('./build/Release/hll_native').HLL;

/**
 * Create new HyperLogLog storage with specified size and standard error.
 *
 * Memory usage for storage calculated as (1 << bits) bytes.
 *
 * Standard error described below
 *
 * |bits|size (bytes)| error  |
 * |----|------------|--------|
 * |  4 |         16 | 26.00% |
 * |  5 |         32 | 18.38% |
 * |  6 |         64 | 13.00% |
 * |  7 |        128 |  9.19% |
 * |  8 |        256 |  6.50% |
 * |  9 |        512 |  4.60% |
 * | 10 |       1024 |  3.25% |
 * | 11 |       2048 |  2.30% |
 * | 12 |       4096 |  1.62% |
 * | 13 |       8192 |  1.15% |
 * | 14 |      16384 |  0.81% |
 * | 15 |      32768 |  0.57% |
 * | 16 |      65536 |  0.41% |
 * | 17 |     131072 |  0.29% |
 * | 18 |     262144 |  0.20% |
 * | 19 |     524288 |  0.14% |
 * | 20 |    1048576 |  0.10% |
 *
 * @param {number} bits
 */
exports.HLL = function(bits) {
	this.hll = new HLL(bits);
};

/**
 * Add key to storage
 * @param {string} key
 */
exports.HLL.prototype.add = function(key) {
	this.hll.add(key);
};

/**
 * Get approximated set size with selected standard error, depends on `bits` value
 * @returns {number}
 */
exports.HLL.prototype.count = function() {
	return this.hll.count();
};
