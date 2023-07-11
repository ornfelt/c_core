package main

import (
    "fmt"
)

/*
	There are other methods of creating a singleton instance in Go:
    init function

	We can create a single instance inside the init function. This is only applicable if
	the early initialization of the instance is ok. The init function is only called once
	per file in a package, so we can be sure that only a single instance will be created.

    sync.Once

	The sync.Once will only perform the operation once. See the code below:
*/

func main() {

    for i := 0; i < 30; i++ {
        go getInstance()
    }

    // Scanln is similar to Scan, but stops scanning at a newline and
    // after the final item there must be a newline or EOF.
    fmt.Scanln()
}
