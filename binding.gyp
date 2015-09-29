{
	"targets": [
		{
			"target_name": "hll_native",
			"dependencies": [
				"libhyperloglog.a"
			],
			"sources": ["src/hll-native.cpp"],
			"libraries": ["../deps/hll/lib/libhyperloglog.a"],
			"include_dirs" : [
			   "<!(node -e \"require('nan')\")"
			]
		},
		{
			"target_name": "libhyperloglog.a",
			"type": "none",
			"actions": [
				{
					"action_name": "make",
					"inputs": [],
					"outputs": ["lib/libhyperloglog.a"],
					"action": ["make", "-C", "deps/hll", "lib/libhyperloglog.a"],
					"message": "Build libhyperloglog.a"
				}
			]
		}
	]
}
