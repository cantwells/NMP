main.c 
    task_s tasks[]: THe task interval is an array to hold and call the intevrals for each task. 
                    Sensor is faster for this because the sensor is running every 100 ms keeping 
                    it updated while the telemetry log and others are only looking at it every 5 iterations.
    run_scheduler(): It decides a task is due by subtracting the last time it looked versus now, 
                    and comparing it to the intveral_ms. Run is the function pointer used.
    main(): The main function. The loop runs until get_state() retruns FLIGHT_LANDED

timer.c
    get_ms() This is where the real time comes from. It is actively tracking the rocket in very tiny iterations.

sensor.c
    sensor_task(): This updates fuel and helps determine was state it is in (thrusting, just gravitational etc).
                    Fuel is static so that they keep their values betwen task runs.A normal local variable would 
                    reset to 0 every time the task is called.
    sensor_buff_add(): Buffer A overwirtes the oldest when its full so that space can be made for fresh sensor data.
    sensor_buff_remove(): Removes/pops the oldest first, and returns 0 when empty so that it can be read by other functions

telemetry.c
    telemetry_task(): It calculates the velocity and altitude for each sample and adds the result to buffer B.
                        This empties Buffer A in a loop so that it can be read to the log. Instead of Delta t
                        like in the last delieverable, it takes real timestamps for live tracking. Velocity, 
                        Altitude, annd last_t are static because they need to keep their values between task runs.
                        
    telem_buff_add(): Buffer B rejects new item when full to keep logged data complete and in the correct order
    telem_buff_remove(): This is used by print so that it can correctly display the data
    telem_get_latest(): This lets the state task look at the current data without taking it from the print function. 
                        If the state task removed packets from the buffer, print would never see them,
                        and the log would be incorrect. Peeking at latest lets both tasks get the data.

print.c
    print_task(): This empties buffer B and prints the time, altitude and velocity for output

run_state.c
    run_state_task(): This is the same switch case from D2. It determines what state the rocket is in,
                        Ascent, Coast, Descent or Landed, based on the velocity, fuel, and altitude. 
                        It takes this data from telemetrty packet which is constantly being updated.
    get_state(): This returns the rocket state which helps the other functions. 
                State is static in the run_state_c so it needs to be read through a getter so main() can see it.


Also:
The Buffer size is 8 becauase although 5 is the expected between reads, 8 leaves headroom for 
mistakes so that data is not lost.
When this system is run, the landing output ends at 12.5. This is due to the state task only checking every 500 ms. 
This saves CPU while giving up some data integrity


Error statements to check Ring Buffers: These tests were originally run at a buffer size 5, and it was later changed to 8.
buffer A overwrite testing: - This shows how when sensor went over .5, .6-1.0 was popped, and 0.1-.5
were overwritten when the telemetry interval was changed to 1000 instead of 500 for this test.

sensor: pushed t=0.100
sensor: pushed t=0.200
sensor: pushed t=0.300
sensor: pushed t=0.400
sensor: pushed t=0.500
sensor: pushed t=0.600
sensor: pushed t=0.700
sensor: pushed t=0.800
sensor: pushed t=0.900
sensor: pushed t=1.000
  telemetry: popped t=0.600
  telemetry: popped t=0.700
  telemetry: popped t=0.800
  telemetry: popped t=0.900
  telemetry: popped t=1.000


Buffer B reject: - This was when I changed the print interval to 1000, rather than 500. 
Buffer B keeps the oldest packets of .1-.5 and rejects the newest, .6-1.0. 

sensor: t=0.100 a=5.19 fuel=49                                                            
sensor: t=0.200 a=5.19 fuel=48
sensor: t=0.300 a=5.19 fuel=47
sensor: t=0.400 a=5.19 fuel=46
sensor: t=0.500 a=5.19 fuel=45
sensor: t=0.600 a=5.19 fuel=44
sensor: t=0.700 a=5.19 fuel=43
sensor: t=0.800 a=5.19 fuel=42
sensor: t=0.900 a=5.19 fuel=41
sensor: t=1.000 a=5.19 fuel=40
  telemetry: REJECTED t=0.600
  telemetry: REJECTED t=0.700
  telemetry: REJECTED t=0.800
  telemetry: REJECTED t=0.900
  telemetry: REJECTED t=1.000
t=0.10 s  alt=0.05 m  vel=0.52 m/s  fuel=49
t=0.20 s  alt=0.16 m  vel=1.04 m/s  fuel=48
t=0.30 s  alt=0.31 m  vel=1.56 m/s  fuel=47
t=0.40 s  alt=0.52 m  vel=2.08 m/s  fuel=46
t=0.50 s  alt=0.78 m  vel=2.59 m/s  fuel=45