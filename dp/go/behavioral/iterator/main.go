package main

import "fmt"

/*
	Conceptual Example:

	The main idea behind the Iterator pattern is to extract the iteration logic of a
	collection into a different object called iterator. This iterator provides a generic
	method of iterating over a collection independent of its type.
*/

func main() {

    user1 := &User{
        name: "a",
        age:  30,
    }
    user2 := &User{
        name: "b",
        age:  20,
    }

    userCollection := &UserCollection{
        users: []*User{user1, user2},
    }

    iterator := userCollection.createIterator()

    for iterator.hasNext() {
        user := iterator.getNext()
        fmt.Printf("User is %+v\n", user)
    }
}
