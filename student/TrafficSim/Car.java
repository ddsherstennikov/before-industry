
package TrafficSim;

import java.util.ArrayList;


public class Car {

    final int BLOCKSIZE = 28;
    private char direction; // H or V
    private int positionx;
    private int positiony;
    private int aniPosX; //For animation
    private int aniPosY; //For animation
    private int lane; //Left-most lane is lane 1
    private int carType; //1-Red, 2-Green, 3-Yellow
    private int nextAction; //0-wait, 1- move forward, 2-overtake left, 3-overtake right
    public int speed;
    /**
     *
     * @return the direction of this car, either H or V
     */
    public char getdir() {
        return direction;
    }

    /**
     *
     * @return the x position of this car
     */
    public int getx() {
        return positionx;
    }

    /**
     *
     * @return the y position of this car
     */
    public int gety() {
        return positiony;
    }

    /**
     * A complex function to attempt to move cars. The function will determine the best way to advance forward, by checking where empty spaces are and overtaking if possible.
     * @param traffic - An ArrayList of Cars, so that the function can check positions of cars relative to this car. (This car will be part of the ArrayList)
     * @param numHLanes - number of Horizontal lanes, used for overtaking
     * @param numVLanes - number of Vertical lanes, used for overtaking
     * @param lights - Traffic lights, to see what state they are in.
     * @param index - the index of this car inside the ArrayList
     * @param count - the current cycle count, used to simulate amber lights
     */
    public void move(ArrayList<Car> traffic, int numHLanes, int numVLanes, TrafficLight lights, int index, int count) {
        switch (direction) {
            case 'H':
                if (positionx == 18) { //At traffic lights stop line
                    if (lights.getGreen() && (count % 20) > numHLanes) { //If the lights are green. The second part allows the cars time to get off the intersection (amber lights).
                        if (!this.carEast(traffic)) { //If there is no car infront (X-axis)
                            positionx ++; // move east
                        }
                    }
                } else { //Not at traffic Lights
                    if (!this.carEast(traffic)) { //If there is no car infront (X-axis)
                        positionx ++; // move east
                    } else { //OVERTAKING
                        if (positiony == 10 && numHLanes > 1) { //lane 1 with more than 1 lane
                            if (!this.carSouth(traffic) && !this.carSouthEast(traffic)) { // check for an opening to the south
                                positiony++;
                                lane = 2;
                            }
                        }
                        if (positiony == 11 && numHLanes >= 2) { //lane 2 with at least 2 lanes
                            if (!this.carNorth(traffic) && !this.carNorthEast(traffic)) { // check for an opening to the north
                                positiony--;
                                lane = 1;
                            } else {
                                if (!this.carSouth(traffic) && !this.carSouthEast(traffic) && numHLanes == 3) { // check for an opening to the south
                                    positiony++;
                                    lane = 3;
                                }
                            }
                        }
                        if (positiony == 12 && numHLanes == 3) { //lane 3 with 3 lanes
                            if (!this.carNorth(traffic) && !this.carNorthEast(traffic)) { // check for an opening to the north
                                positiony--;
                                lane = 2;
                            }
                        }
                    }
                }
                break;
            case 'V':
                if (positiony == (10 + numHLanes)) { // At the traffic lights
                    if (!lights.getGreen() && (count % 20) > numVLanes) { // If the lights are green for vertical traffic (not green for horizontal traffic). The second part allows the cars time to get off the intersection.
                        if (!this.carNorth(traffic)) { //If there is no car infront
                            positiony--; //move north
                        }
                    }
                } else { //Not at traffic lights
                    if (!this.carNorth(traffic)) { //If there is no car infront
                        positiony--; //move north
                    } //OVERTAKING
                    else {
                        if (positionx == 10 && numVLanes > 1) { //Lane 1 with more than one lane.
                            if (!this.carEast(traffic) && !this.carNorthEast(traffic)) { //If there is an opening
                                positionx++; // move east
                                lane = 2; //update lane
                            }
                        } //Check 1
                        if (positionx == 11 && numVLanes >= 2) { //Lane 2 with at least 2 lanes.
                            if (!this.carWest(traffic) && !this.carNorthWest(traffic)) { //If there is an opening
                                positionx--; // move west
                                lane = 1; //update lane
                            } else {
                                if (numVLanes >= 3 && !this.carEast(traffic) && !this.carNorthEast(traffic)) { //If there is an opening
                                    positionx++; // move east
                                    lane = 3; //update lane
                                }
                            }
                        } //Check 2
                        if (positionx == 12 && numVLanes >= 3) { //Lane 3 with at least 3 lanes.
                            if (!this.carWest(traffic) && !this.carNorthWest(traffic)) { //If there is an opening
                                positionx--; // move west
                                lane = 2; //update lane
                            } else {
                                if (numVLanes == 4 && !this.carEast(traffic) && !this.carNorthEast(traffic)) { //If there is an opening
                                    positionx++; // move east
                                    lane = 4; //update lane
                                }
                            }
                        } //Check 3
                        if (positionx == 13 && numVLanes == 4) {//Lane 4 with 4 lanes
                            if (!this.carWest(traffic) && !this.carNorthWest(traffic)) { //If there is an opening
                                positionx--; // move west
                                lane = 3; //update lane
                            }
                        }
                    }
                } //OVERTAKING
                break;
        }
    }

    /**
     * A complex function to determine the next action of a car. The function will determine the best way to advance forward, by checking where empty spaces are and overtaking if possible.
     * @param traffic - An ArrayList of Cars, so that the function can check positions of cars relative to this car. (This car will be part of the ArrayList)
     * @param numHLanes - number of Horizontal lanes, used for overtaking
     * @param numVLanes - number of Vertical lanes, used for overtaking
     * @param lights - Traffic lights, to see what state they are in.
     * @param index - the index of this car inside the ArrayList
     * @param count - the current cycle count, used to simulate amber lights
     */
    public void setNextAction(ArrayList<Car> traffic, int numHLanes, int numVLanes, TrafficLight lights, int index, int count) {
        nextAction = 0;
        switch (direction) {
            case 'H':
                if (positionx == 18) { //At traffic lights stop line
                    if (lights.getGreen() && (count % 20) > numHLanes) { //If the lights are green. The second part allows the cars time to get off the intersection (amber lights).
                        if (!this.carEast(traffic)) { //If there is no car infront (X-axis)
                            nextAction = 1; //move forward
                        }
                    }
                } else { //Not at traffic Lights
                    if (!this.carEast(traffic)) { //If there is no car infront (X-axis)
                        nextAction = 1; //move forward
                    } else { //OVERTAKING
                        if (positiony == 10 && numHLanes > 1) { //lane 1 with more than 1 lane
                            if (!this.carSouth(traffic) && !this.carSouthEast(traffic)) { // check for an opening to the south
                                nextAction = 3; //overtake to the right
                            }
                        }
                        if (positiony == 11 && numHLanes >= 2) { //lane 2 with at least 2 lanes
                            if (!this.carNorth(traffic) && !this.carNorthEast(traffic)) { // check for an opening to the north
                                nextAction = 2; //overtake to the left
                            } else {
                                if (!this.carSouth(traffic) && !this.carSouthEast(traffic) && numHLanes == 3) { // check for an opening to the south
                                    nextAction = 3; //overtake to the right
                                }
                            }
                        }
                        if (positiony == 12 && numHLanes == 3) { //lane 3 with 3 lanes
                            if (!this.carNorth(traffic) && !this.carNorthEast(traffic)) { // check for an opening to the north
                                nextAction = 2; //overtake to the left
                            }
                        }
                    }
                }
                break;
            case 'V':
                if (positiony == (10 + numHLanes)) { // At the traffic lights
                    if (!lights.getGreen() && (count % 20) > numVLanes) { // If the lights are green for vertical traffic (not green for horizontal traffic). The second part allows the cars time to get off the intersection.
                        if (!this.carNorth(traffic)) { //If there is no car infront
                            nextAction = 1; //move forward
                        }
                    }
                } else { //Not at traffic lights
                    if (!this.carNorth(traffic)) { //If there is no car infront
                        nextAction = 1; //move forward
                    } //OVERTAKING
                    else {
                        if (positionx == 19 && numVLanes > 1) { //Lane 1 with more than one lane.
                            if (!this.carEast(traffic) && !this.carNorthEast(traffic)) { //If there is an opening
                                nextAction = 3; //overtake to the right
                            }
                        } //Check 1
                        if (positionx == 20 && numVLanes >= 2) { //Lane 2 with at least 2 lanes.
                            if (!this.carWest(traffic) && !this.carNorthWest(traffic)) { //If there is an opening
                                nextAction = 2; //overtake to the left
                            } else {
                                if (numVLanes >= 3 && !this.carEast(traffic) && !this.carNorthEast(traffic)) { //If there is an opening
                                    nextAction = 3; //overtake to the right
                                }
                            }
                        } //Check 2
                        if (positionx == 21 && numVLanes >= 3) { //Lane 3 with at least 3 lanes.
                            if (!this.carWest(traffic) && !this.carNorthWest(traffic)) { //If there is an opening
                                nextAction = 2; //overtake to the left
                            } else {
                                if (numVLanes == 4 && !this.carEast(traffic) && !this.carNorthEast(traffic)) { //If there is an opening
                                    nextAction = 3; //overtake to the right
                                }
                            }
                        } //Check 3
                        if (positionx == 22 && numVLanes == 4) {//Lane 4 with 4 lanes
                            if (!this.carWest(traffic) && !this.carNorthWest(traffic)) { //If there is an opening
                                nextAction = 2; //overtake to the left
                            }
                        }
                    }
                } //OVERTAKING
                break;
        }
    }

    /**
     * move the car based on the determined action in setNextAction
     */
    public void move() {
        switch (nextAction) {
            case 0:
                break;
            case 1:
                if (direction == 'H') {
                    positionx++;
                } else {
                    positiony--;
                }
                break;
            case 2:
                if (direction == 'H') {
                    positiony--;
                    lane--;
                } else {
                    positionx--;
                    lane--;
                }
                break;
            case 3:
                if (direction == 'H') {
                    positiony++;
                    lane++;
                } else {
                    positionx++;
                    lane++;
                }
                break;
        }
    }

    /**
     *
     * @return the next action 0-wait, 1-go forward, 2-overtake left, 3-overtake right
     */
    public int getNextAction() {
        return nextAction;
    }

    Car() {
        direction = 'H';
        positionx = 0; //out of map bounds
        positiony = 10;
        lane = 1;
        carType = TrafficSim.rand.nextInt(3) + 1;
        aniPosX = positionx * BLOCKSIZE;
        aniPosY = positiony * BLOCKSIZE;
    }

    Car(char dir, int hLanes) {
        direction = dir;
        switch (dir) {
            case 'H':
                positionx = 0;
                positiony = 10;
                lane = 1;
                aniPosX = 0;
                aniPosY = 10 * BLOCKSIZE;
                break;
            case 'V':
                positionx = 10;
                positiony = 21 + hLanes;
                lane = 1;
                aniPosX = positionx * BLOCKSIZE;
                aniPosY = positiony * BLOCKSIZE;
                break;
        }
        carType = TrafficSim.rand.nextInt(3) + 1;
    }

    /**
     *
     * @param dir Direction of car (H, V)
     * @param posx x position of car
     * @param posy y position of car
     */
    public Car(char dir, int posx, int posy) {
        direction = dir;
        positionx = posx;
        positiony = posy;
        aniPosX = positionx * BLOCKSIZE;
        aniPosY = positiony * BLOCKSIZE;
        lane = 1;
        carType = TrafficSim.rand.nextInt(3) + 1;
    }

    Car(int laneNum, int hLanes, int dir, int speed) {
        this.speed = speed;
        if (dir == 0) {
            direction = 'H';
        } else {
            direction = 'V';
        }
        lane = laneNum;
        switch (direction) {
            case 'H':
                positionx = 0;
                positiony = 9 + lane;
                aniPosX = positionx * BLOCKSIZE;
                aniPosY = positiony * BLOCKSIZE;
                break;
            case 'V':
                positiony = 21 + hLanes;
                positionx = 18 + lane;
                aniPosX = positionx * BLOCKSIZE;
                aniPosY = positiony * BLOCKSIZE;
        }
        carType = TrafficSim.rand.nextInt(3) + 1;
    }

    Car(int x, int y, char dir, int type, int lane) {
        positionx = x;
        positiony = y;
        direction = dir;
        carType = type;
        this.lane = lane;
    }

    //Several functions to test if there is a car in 9 directions (including the same space as the car)
    /**
     * Check if there is a Car in this spot
     * @param tempCar - Pass in a car to compare with this Car.
     * @return true or false
     */
    public boolean equals(Car tempCar) {
        if (tempCar.direction == direction && tempCar.lane == lane && tempCar.positionx == positionx && tempCar.positiony == positiony) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Check if there is a car to the North
     * @param traffic ArrayList of Cars
     * @return true or false
     */
    public boolean carNorth(ArrayList<Car> traffic) {
        boolean carExists = false;
        for (int i = 0; i < traffic.size(); ++i) {
            if (traffic.get(i).getdir() == direction && traffic.get(i).getx() == positionx && traffic.get(i).gety() == positiony - 1) {
                carExists = true;
            }
        }
        if (carExists) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Check if there is a car to the South
     * @param traffic ArrayList of Cars
     * @return true or false
     */
    public boolean carSouth(ArrayList<Car> traffic) {
        boolean carExists = false;
        for (int i = 0; i < traffic.size(); ++i) {
            if (traffic.get(i).getdir() == direction && traffic.get(i).getx() == positionx && traffic.get(i).gety() == positiony + 1) {
                carExists = true;
            }
        }
        if (carExists) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Check if there is a car to the East
     * @param traffic ArrayList of Cars
     * @return true or false
     */
    public boolean carEast(ArrayList<Car> traffic) {
        boolean carExists = false;
        for (int i = 0; i < traffic.size(); ++i) {
            if (traffic.get(i).getdir() == direction && traffic.get(i).getx() == positionx + 1 && traffic.get(i).gety() == positiony) {
                carExists = true;
            }
        }
        if (carExists) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Check if there is a car to the West
     * @param traffic ArrayList of Cars
     * @return true or false
     */
    public boolean carWest(ArrayList<Car> traffic) {
        boolean carExists = false;
        for (int i = 0; i < traffic.size(); ++i) {
            if (traffic.get(i).getdir() == direction && traffic.get(i).getx() == positionx - 1 && traffic.get(i).gety() == positiony) {
                carExists = true;
            }
        }
        if (carExists) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Check if there is a car to the North East.
     * @param traffic ArrayList of Cars
     * @return true or false
     */
    public boolean carNorthEast(ArrayList<Car> traffic) {
        boolean carExists = false;
        for (int i = 0; i < traffic.size(); ++i) {
            if (traffic.get(i).getdir() == direction && traffic.get(i).getx() == positionx + 1 && traffic.get(i).gety() == positiony - 1) {
                carExists = true;
            }
        }
        if (carExists) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Check if there is a car to the South East
     * @param traffic ArrayList of Cars
     * @return true or false
     */
    public boolean carSouthEast(ArrayList<Car> traffic) {
        boolean carExists = false;
        for (int i = 0; i < traffic.size(); ++i) {
            if (traffic.get(i).getdir() == direction && traffic.get(i).getx() == positionx + 1 && traffic.get(i).gety() == positiony + 1) {
                carExists = true;
            }
        }
        if (carExists) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Check if there is a car to the North West
     * @param traffic ArrayList of Cars
     * @return true or false
     */
    public boolean carNorthWest(ArrayList<Car> traffic) {
        boolean carExists = false;
        for (int i = 0; i < traffic.size(); ++i) {
            if (traffic.get(i).getdir() == direction && traffic.get(i).getx() == positionx - 1 && traffic.get(i).gety() == positiony - 1) {
                carExists = true;
            }
        }
        if (carExists) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Check if there is a car to the South West
     * @param traffic ArrayList of Cars
     * @return true or false
     */
    public boolean carSouthWest(ArrayList<Car> traffic) {
        boolean carExists = false;
        for (int i = 0; i < traffic.size(); ++i) {
            if (traffic.get(i).getdir() == direction && traffic.get(i).getx() == positionx - 1 && traffic.get(i).gety() == positiony + 1) {
                carExists = true;
            }
        }
        if (carExists) {
            return true;
        } else {
            return false;
        }
    }

    /**
     *
     * @return Car type (color)
     */
    public int getType() {
        return carType;
    }

    /**
     * depreciated
     * @param cycleCount change the animation position of car based on the current cycle part
     */
    public void animate(int cycleCount) {
        int dispX = 0;
        int dispY = 0;
        switch (nextAction) {
            case 0:
                dispX = 0;
                dispY = 0;
                break;
            case 1:
                if (direction == 'H') {
                    dispX = (int) ((float) cycleCount / 10f * BLOCKSIZE);
                    dispY = 0;
                } else {
                    dispX = 0;
                    dispY = (int) ((float) cycleCount / -10 * BLOCKSIZE);
                }
                break;
            case 2:
                if (direction == 'H') {
                    dispX = 0;
                    dispY = (int) ((float) cycleCount / -10 * BLOCKSIZE);
                } else {
                    dispX = (int) ((float) cycleCount / -10 * BLOCKSIZE);
                    dispY = 0;
                }
                break;
            case 3:
                if (direction == 'H') {
                    dispX = 0;
                    dispY = (int) ((float) cycleCount / 10 * BLOCKSIZE);
                } else {
                    dispX = (int) ((float) cycleCount / 10 * BLOCKSIZE);
                    dispY = 0;
                }
                break;
        }
        aniPosX = positionx * BLOCKSIZE + dispX;
        aniPosY = positiony * BLOCKSIZE + dispY;
    }

    /**
     * depreciated
     * @return animation position of a car
     */
    public int getAniX() {
        return aniPosX;
    }

    /**
     * depreciated
     * @return animation position of a car
     */
    public int getAniY() {
        return aniPosY;
    }

    /**
     *
     * @return the lane the car is in
     */
    public int getLane() {
        return lane;
    }
}
