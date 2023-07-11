package main

/*
	Conceptual Example:
	We have a client code that expects some features of an object (Lightning port), but we
	have another object called adaptee (Windows laptop) which offers the same
	functionality but through a different interface (USB port)

	This is where the Adapter pattern comes into the picture. We create a struct type
	known as adapter that will:

    Adhere to the same interface which the client expects (Lightning port).

	Translate the request from the client to the adaptee in the form that the adaptee
	expects. The adapter accepts a Lightning connector and then translates its signals
	into a USB format and passes them to the USB port in windows laptop.
*/

func main() {

    client := &Client{}
    mac := &Mac{}

    client.InsertLightningConnectorIntoComputer(mac)

    windowsMachine := &Windows{}
    windowsMachineAdapter := &WindowsAdapter{
        windowMachine: windowsMachine,
    }

    client.InsertLightningConnectorIntoComputer(windowsMachineAdapter)
}
