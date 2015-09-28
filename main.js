// test.js
var HLL = require('./build/Release/hll_native').HLL;

exports.HLL = function(bits) {
	this.hll = new HLL(bits);
};

exports.HLL.prototype.add = function(key) {
	this.hll.add(key);
};

exports.HLL.prototype.count = function() {
	return this.hll.count();
};
