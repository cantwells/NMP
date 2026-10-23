For this project, I split the rocket simulation into a few different functions to make the code
more organized and easier to follow, which also makes it easier to debug.

update_sensor_sample() handles the acceleration and fuel. If there's fuel left, the
acceleration is the thrust minus gravity and one unit of fuel gets burned, otherwise it's
just gravity. I used a static step counter inside the function so it remembers how many
steps have happened between calls, which I use to calculate the timestamp.

update_telemetry_state() updates the rocket's velocity and altitude using v = v + a*dt and
then z = z + v*dt. I update velocity first so altitude uses the newest velocity. The sensor
pointer is const because this function only reads the sensor data and shouldn't change it.

run_rocket_state() keeps track of what part of the flight the rocket is in using a switch
case. It goes from ascent to coast when fuel runs out, coast to descent when velocity hits
zero (apogee), and descent to landed when altitude reaches zero. The state is a static
global so main can see when it changes, but no other file can modify it.

In main(), I initialize everything using the macros and keep running the simulation until
the rocket lands. Each loop I pass the structs by pointer so the functions update the real
data instead of copies, and I print every step so I can check the calculations are working.
The final altitude ends up slightly negative because the rocket passes zero partway through
a time step before the check catches it.