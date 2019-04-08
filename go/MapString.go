package main

import "fmt"

type foo map[string] interface{}

func main() {
	var x = make(foo, 10)
	x["a"] = 1
	x["b"] = 1
	x["c"] = 1
	x["d"] = 1
	x["e"] = 1
	x["f"] = 1
	x["g"] = 1
	x["h"] = 1
	x["i"] = 1
	x["j"] = 1
	x["k"] = 1
	x["l"] = 1
	fmt.Printf("%v", x)
	fmt.Printf("%v", x["a"])
}
