package main

/*
	Conceptual Example:

	An excellent example of the Mediator pattern is a railway station traffic system. Two
	trains never communicate between themselves for the availability of the platform. The
	stationManager acts as a mediator and makes the platform available to only one of the
	arriving trains while keeping the rest in a queue. A departing train notifies the
	stations, which lets the next train in the queue to arrive.
*/

func main() {
    stationManager := newStationManger()

    passengerTrain := &PassengerTrain{
        mediator: stationManager,
    }
    freightTrain := &FreightTrain{
        mediator: stationManager,
    }

    passengerTrain.arrive()
    freightTrain.arrive()
    passengerTrain.depart()
}
