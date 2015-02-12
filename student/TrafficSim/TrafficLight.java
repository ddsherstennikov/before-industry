package TrafficSim;


public class TrafficLight {

    private boolean green; //As seen by horisontal. True for vertical direction cars means stop.
    private int state; //0-Red, 1-Green, 2-Amber

    public TrafficLight() {
        green = false;
        state = 0;
    }

    /**
     * Switch color of lights
     */
    public void changeColour() {
        if (green) {
            green = false;
            state = 0;
        } else {
            green = true;
            state = 1;
        }
    }

    /**
     *
     */
    public void changeState() {
        if (state == 2) {
            state = 0;
        } else {
            ++state;
        }
    }

    /**
     * Set the state of lights
     * @param state 0-red, 1- green, 2-amber
     */
    public void setState(int state) {
        this.state = state;
    }

    /**
     * Make the lights green for Horizontal traffic
     */
    public void makeGreen() { //if I need to set traffic lights to green
        green = true;
        state = 1;
    }

    /**
     * set the lights green (true) or red (false) for horizontal traffic
     * @param color true or false
     */
    public void setColor(boolean color) {
        green = color;
    }

    /**
     * Check if lights are green
     * @return the boolean true false if the light is green for Horizontal traffic
     */
    public boolean getGreen() {
        return green;
    }

    /**
     * Get state of lights
     * @return current state 0-red, 1- green, 2-amber
     */
    public int getState() {
        return state;
    }

    /**
     * Get state in boolean form
     * @return current state as a boolean red or amber - false, green - true
     */
    public boolean getStateBoolean() {
        switch (state) {
            case 0:
                return false;
            case 1:
                return true;
            case 2:
                return false;
            default:
                return false;
        }
    }
}
