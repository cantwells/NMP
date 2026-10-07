#include <stdio.h>

int main() {
    //user input
    double z0;
    printf("Enter starting altitude (m): ");
    scanf("%lf", &z0); //this reads the value and stores it into variable
    double v0;
    printf("Enter starting velocity (m/s): ");
    scanf("%lf", &v0);
    int fuel;
    printf("Enter initial fuel (steps): ");
    scanf("%d", &fuel);
    double a_thrust;
    printf("Enter thrust acceleration (m/s^2): ");
    scanf("%lf", &a_thrust);
    double delta_T;
    printf("Enter time step (s): ");
    scanf("%lf", &delta_T);
    int safety_cap;
    printf("Enter max steps: ");
    scanf("%d", &safety_cap);
    
    //loop stuff
    double g = 9.81;
    int step = 0;
    double v = v0;
    double z = z0;
    double max_altitude = z0;
    double altitudes[safety_cap];
    
    
    double a;
    while (step < safety_cap) {
        if(fuel>0){
            a =a_thrust-g;
            fuel = fuel-1;
        }
        else{
            a =-g;
        }

        v = v + a*delta_T;
        z = z + v*delta_T;
        altitudes[step] = z;

        if(z > max_altitude){
            max_altitude = z;
        }

        step++;

        if (z <= 0 && v <= 0) {
            break;
        }
    }
    
    int total_steps = step;
    double total_time = total_steps * delta_T;
      
    double z_final;
    if(z<0){
        z_final=0;
    }

    //flightLog Print statements
    printf("Flight Log: \n");
    printf("Steps: %d Total Time : %.2f s\n", total_steps, total_time);
    printf("Max Altitude: %.2f m\n", max_altitude);
  
    printf("Final Altitude: %.2f m\n", z_final);
    printf("Final Velocity: %.2f m/s\n", v);
    printf("Fuel Remaining: %d steps \n", fuel);
    printf("Altitude history (every ten steps):");
    for(int i = 0; i < total_steps; i+=10){
        printf("%.2f m\n", altitudes[i]);
    }

return 0;
}


//cout << "Hello, World!"; 