package main

import (
	"fmt"
)

func main() {
	// Slices and arrays - https://blog.golang.org/go-slices-usage-and-internals
	b := [2]string{"Penn", "Teller"}
	var b2 = [10]byte{1, 2, 3, 4, 5, 6, 7, 8, 9, 0}
	b3 := [2]byte{'a', 'b'}
	var b4 [2]byte
	fmt.Println(b)
	fmt.Println(b2)
	fmt.Println(b3)
	fmt.Println(b4)

	var s1 []int
	fmt.Println(s1)
	var s2 []byte = nil
	fmt.Println(s2, cap(s2), len(s2))

	s3 := []byte{'g', 'o', 'l', 'a', 'n', 'g'}
	s4 := s3[1:4]
	fmt.Println(s3, s4)
	s3[1] = 't'
	fmt.Println(s3, s4)

	// Strings - https://blog.golang.org/strings
	const sample = "\xbd\xb2\x3d\xbc\x20\xe2\x8c\x98"
	byteSample := []byte(sample)

	fmt.Println("Println:")
	fmt.Println(sample)

	fmt.Println("Byte loop:")
	for i := 0; i < len(sample); i++ {
		fmt.Printf("%x ", sample[i])
	}
	fmt.Printf("\n")

	fmt.Println("Printf with %x:")
	fmt.Printf("%x\n", sample)

	fmt.Println("Printf with % x:")
	fmt.Printf("% x\n", sample)

	fmt.Println("Printf with %q:")
	fmt.Printf("%q\n", sample)

	fmt.Println("Printf with %+q:")
	fmt.Printf("%+q\n", sample)

	fmt.Println("Byte array sample")
	for i := 0; i < len(byteSample); i++ {
		fmt.Printf("%q ", byteSample[i])
	}
	heartBytes := []byte{0xe2, 0x9d, 0xa4}
	fmt.Printf("\n-%s-\n", string(heartBytes))

	heart := "\u2764"
	fmt.Println(heart)
	for i := 0; i < len(heart); i++ {
		fmt.Printf("% x", heart[i])
	}

	var bs = []byte{0xEE, 0x88, 0x8C}
	fmt.Printf("\n%s", bs)
}
