#include <stdio.h>
#include <math.h>
#include <unistd.h>

#define NUM_PLANETS 5

typedef struct {
    double positionx;
    double positiony;
    double velocityx;
    double velocityy;
    double mass;
    char *symbol;
} Planet;

void update_planets(Planet planets[], int n, double dt);
void calculate_force(Planet *p1, Planet *p2, double *fx, double *fy);

int main(void) {
    //printf("\n\n");

    int n = 5;
    //Time elapsed
    double dt = 0.08;

    char *star = "  ***\n *****\n*******\n *****\n  ***\n";
    char *star2 = "\033[%9;%40H***\033[%10;%39H*****";

    Planet planets[NUM_PLANETS] = {


            //v = sqrt(gravity * mass / distance to star)          

          // x , y ,vx, vy, m,   symbol
            {40, 12, 0, 0, 1000, "*"},
            {55, 12, 0, -2.581988897, 2, "o"},
            {35, 12, 0, 4.472135955, 1, "@"},
            {40, 22, 3.16227766, 0, 1, "+"},
            {40, 4.5, -3.651483717, 0, 1, "O"}
        };


    while(1) {
        //Clears the screen
        printf("\033[2J\033[H");
        printf("\e[?25l");


        //Prints the start in the center
//        printf("\033[%d;%dH***", cy, cx);
//        printf("\033[%d;%dH*****", cy + 1, cx - 1);
//        printf("\033[%d;%dH*******", cy + 2, cx - 2);
//        printf("\033[%d;%dH*******", cy + 3, cx - 2);
//        printf("\033[%d;%dH*****", cy + 4, cx - 1);
//        printf("\033[%d;%dH***", cy + 5, cx);
//        printf("\n\n");

        
        for(int i = 0; i < n; i++) {
            int px = (int)planets[i].positionx;
            int py = (int)planets[i].positiony;

            printf("\033[%d;%dH%s", py + 10, px, planets[i].symbol);
        }

        fflush(stdout);
        usleep(40000);

        update_planets(planets, n, dt);
    }
    
    return 0;
}


void calculate_force(Planet *p1, Planet *p2, double *fx, double *fy) {
    double dx = p2->positionx - p1->positionx;
    double dy = p2->positiony - p1->positiony;
    double dist = sqrt(dx * dx + dy * dy);

    //Stops division by 0
    if(dist < 0.5) {
        dist = 0.5;
    }

    double G = 0.1;
    double force = G * p1->mass * p2->mass / (dist * dist);
    
    //Force direction    
    double ux = dx / dist;
    double uy = dy / dist;

    *fx = force * ux;
    *fy = force * uy;
    
}

void update_planets(Planet planets[], int n, double dt) {
    for(int i = 0; i < n; i++) {
        double total_fx = 0;
        double total_fy = 0;

        for(int j = 0; j < n; j++) {
            if(i == j) {
                continue;
            }
            double fx;
            double fy;
            calculate_force(&planets[i], &planets[j], &fx, &fy);
            total_fx += fx;
            total_fy += fy;
        }

        //Update velocity. v=v+(F/m) * dt
        double accelerationx = total_fx / planets[i].mass;
        double accelerationy = total_fy / planets[i].mass;
        planets[i].velocityx += accelerationx * dt;
        planets[i].velocityy += accelerationy * dt;
    }

    //finally update each planet's position once the velocity is calculated
    for(int i = 0; i < n; i++) {
        planets[i].positionx += planets[i].velocityx * dt;
        planets[i].positiony += planets[i].velocityy * dt;
    }
}
