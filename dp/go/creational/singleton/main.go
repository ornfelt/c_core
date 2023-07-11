package main

import (
    "fmt"
)

/*
	Conceptual Example:

	Usually, a singleton instance is created when the struct is first initialized. To make
	this happen, we define the getInstance method on the struct. This method will be
	responsible for creating and returning the singleton instance. Once created, the same
	singleton instance will be returned every time the getInstance is called.

	How about goroutines? The singleton struct must return the same instance whenever
	multiple goroutines are trying to access that instance. Because of this, it’s very
	easy to get the singleton design pattern implemented wrong. The example below
	illustrates the right way to create a singleton.

	Some points worth noting:

	There is a nil-check at the start for making sure singleInstance is empty first time
	around. This is to prevent expensive lock operations every time the getinstance method
	is called. If this check fails, then it means that the singleInstance field is already
	populated.

	The singleInstance struct is created within the lock.

	There is another nil-check after the lock is acquired. This is to ensure that if more
	than one goroutine bypasses the first check, only one goroutine can create the
	singleton instance. Otherwise, all goroutines will create their own instances of the
	singleton struct.

	Also see other version from sync folder.
*/

func main() {

    for i := 0; i < 30; i++ {
        go getInstance()
    }

    // Scanln is similar to Scan, but stops scanning at a newline and
    // after the final item there must be a newline or EOF.
    fmt.Scanln()
}
