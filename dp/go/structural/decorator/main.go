package main

import "fmt"

// https://refactoring.guru/design-patterns/decorator/go/example#example-0

func main() {

    pizza := &VeggeMania{}

    //Add cheese topping
    pizzaWithCheese := &CheeseTopping{
        pizza: pizza,
    }

    //Add tomato topping
    pizzaWithCheeseAndTomato := &TomatoTopping{
        pizza: pizzaWithCheese,
    }

    fmt.Printf("Price of veggeMania with tomato and cheese topping is %d\n", pizzaWithCheeseAndTomato.getPrice())
}