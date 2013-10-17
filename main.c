/*******************************************
 * Author: C2C Jennae Steinmiller
 * Created: 15 Oct 2013
 * Description: This program is made to simulate a ball bouncing
 * off of the walls of a square (the window frame). The window is specified
 * by constants. When the ball hits an edge, it will bounce back so that it
 * does not go out of bounds. The ball is made up of a center position, or the
 * ball location, a velocity, and the radius.
 * Documentation: I received help from C2C Ryan Hub to try to troubleshoot my code.
 *******************************************/
#include <msp430.h> 
#define HEIGHT = 300;
#define WIDTH = 300;

//Create structs for position, velocity, and radius

struct point {
	signed int x, y;
};

struct circle {
	struct point center;
	int radius;
	struct point velocity;
};

struct circle update(struct circle);
int collisionUp(struct point velocity);
int collisionDown(struct point velocity);
int collisionRight(struct point velocity);
int collisionLeft(struct point velocity);

/*
 * main.c
 */
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	struct point center = { 20, 285 };
	struct point velocity = { -1, -2 };
	struct circle myCircle;
	myCircle.center = center;
	myCircle.velocity = velocity;
	myCircle.radius = 5;

	while (1) {
		myCircle = update(myCircle);
	}

	return 0;
}

struct circle update(struct circle myCircle) {
	myCircle.center.x += myCircle.velocity.x;
	myCircle.center.y += myCircle.velocity.y;

	if (myCircle.center.y - myCircle.radius <= 0) {
		myCircle.velocity.y = collisionUp(myCircle.velocity);
		myCircle.center.y += myCircle.velocity.y;
	}

	if (myCircle.center.y + myCircle.radius >= 300) {
		myCircle.velocity.y = collisionDown(myCircle.velocity);
		myCircle.center.y += myCircle.velocity.y;
	}

	if (myCircle.center.x + myCircle.radius >= 300) {
		myCircle.velocity.x = collisionRight(myCircle.velocity);
		myCircle.center.x += myCircle.velocity.x;
	}

	if ((myCircle.center.x - myCircle.radius) <= 0) {
		myCircle.velocity.x = collisionLeft(myCircle.velocity);
		myCircle.center.x += myCircle.velocity.x;
	}
	//struct circle myCircle = { center, 5, velocity };
	return myCircle;
}

int collisionUp(struct point velocity) {
	velocity.y = -velocity.y;
	return velocity.y;
}

int collisionDown(struct point velocity) {
	velocity.y = -velocity.y;
	return velocity.y;
}

int collisionRight(struct point velocity) {
	velocity.x = -velocity.x;
	return velocity.x;
}

int collisionLeft(struct point velocity) {
	velocity.x = -velocity.x;
	return velocity.x;
}
