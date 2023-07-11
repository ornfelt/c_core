package main

import "fmt"

/*
	Conceptual Example:

	The Memento pattern lets us save snapshots for an object’s state. You can use these
	snapshots to revert the object to the previous state. It’s handy when you need to
	implement undo-redo operations on an object.
*/

func main() {

    caretaker := &Caretaker{
        mementoArray: make([]*Memento, 0),
    }

    originator := &Originator{
        state: "A",
    }

    fmt.Printf("Originator Current State: %s\n", originator.getState())
    caretaker.addMemento(originator.createMemento())

    originator.setState("B")
    fmt.Printf("Originator Current State: %s\n", originator.getState())
    caretaker.addMemento(originator.createMemento())

    originator.setState("C")
    fmt.Printf("Originator Current State: %s\n", originator.getState())
    caretaker.addMemento(originator.createMemento())

    originator.restoreMemento(caretaker.getMemento(1))
    fmt.Printf("Restored to State: %s\n", originator.getState())

    originator.restoreMemento(caretaker.getMemento(0))
    fmt.Printf("Restored to State: %s\n", originator.getState())
}
