package main

import "fmt"

/*
	Conceptual Example:

	Let’s consider the example of One Time Password (OTP) functionality. There are
	different ways that the OTP can be delivered to a user (SMS, email, etc.). But
	irrespective whether it’s an SMS or email OTP, the entire OTP process is the same:

    Generate a random n digit number.
    Save this number in the cache for later verification.
    Prepare the content.
    Send the notification.

	Any new OTP types that will be introduced in the future most likely still go through
	the above steps.

	So, we have a scenario where the steps of a particular operation are the same, but
	these steps’ implementation may differ. This is an appropriate situation to consider
	using the Template Method pattern.

	First, we define a base template algorithm that consists of a fixed number of methods.
	That’ll be our template method. We will then implement each of the step methods, but
	leave the template method unchanged.
*/

func main() {
    // otp := otp{}

    // smsOTP := &sms{
    //  otp: otp,
    // }

    // smsOTP.genAndSendOTP(smsOTP, 4)

    // emailOTP := &email{
    //  otp: otp,
    // }
    // emailOTP.genAndSendOTP(emailOTP, 4)
    // fmt.Scanln()

    smsOTP := &Sms{}
    o := Otp{
        iOtp: smsOTP,
    }
    o.genAndSendOTP(4)

    fmt.Println("")
    emailOTP := &Email{}
    o = Otp{
        iOtp: emailOTP,
    }
    o.genAndSendOTP(4)
}
