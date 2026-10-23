For this project, I split the rocket simulation into a few different functions to make the code
more organized and easier to follow which makes it easier to debig
update_sensor_sample() handles the acceleration and fuel,
update_telemetry_state() updates the rocket's velocity and altitude,
and run_rocket_state() keeps track of what part of the flight the rocket is in. 
In main(), I initialize everything and keep running the simulation until
the rocket lands so I can check that everything is working.