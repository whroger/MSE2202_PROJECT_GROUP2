unsigned int ul_Echo_Time;

int Ping(int ci_Ultrasonic_Ping;int ci_Ultrasonic_Data)
{
	//Ping Ultrasonic
	//Send the Ultrasonic Range Finder a 10 microsecond pulse per tech spec
	digitalWrite(ci_Ultrasonic_Ping, HIGH);
	delayMicroseconds(10);  //The 10 microsecond pause where the pulse in "high"
	digitalWrite(ci_Ultrasonic_Ping, LOW);
	//use command pulseIn to listen to Ultrasonic_Data pin to record the
	//time that it takes from when the Pin goes HIGH until it goes LOW 
	ul_Echo_Time = pulseIn(ci_Ultrasonic_Data, HIGH, 10000);

	/*test module
	// Print Sensor Readings
	//#ifdef DEBUG_ULTRASONIC
	Serial.print("Time (microseconds): ");
	Serial.print(ul_Echo_Time, DEC);
	Serial.print(", Inches: ");
	Serial.print(ul_Echo_Time/148); //divide time by 148 to get distance in inches
	Serial.print(", cm: ");
	Serial.println(ul_Echo_Time/58); //divide time by 58 to get distance in cm 
	Serial.print(", mm: ");
	Serial.println(ul_Echo_Time*10/58); //divded by ten and derive mm
	//divide time by 58 to get distance in cm 
	//#endif
	*/
	return (ul_Echo_Time*10/58);
}