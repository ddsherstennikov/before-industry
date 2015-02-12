package TrafficSim;

import java.util.ArrayList;
import java.util.Random;

public class TrafficSim {

    static Random rand = new Random();
    private int hLanes;
    private int vLanes;
    private float hProb;
    private float vProb;
    private ArrayList<Car> traffic;
    private TrafficLight lights;
    private int count;
    private boolean running;
    private int cycleCount;

    TrafficSim() {
        lights = new TrafficLight();
        traffic = new ArrayList();
        count = 1;
        hLanes = 2;
        vLanes = 2;
        hProb = 0.5f;
        vProb = 0.5f;
        running = false;
        cycleCount = 0;
    }

    TrafficSim(int hLanes, int vLanes, float vProb, float hProb) {
        lights = new TrafficLight();
        traffic = new ArrayList();
        count = 1;
        this.hLanes = hLanes;
        this.vLanes = vLanes;
        this.hProb = hProb;
        this.vProb = vProb;
        running = false;
        cycleCount = 0;
    }

    /**
     * Play or Pause simulation
     */
    public void toggleRun() {
        running = !running;
    }

    /**
     * get the arraylist of traffic for calculations
     * @return traffic arraylist
     */
    public ArrayList<Car> getTraffic() {
        return traffic;
    }

    /**
     * get the traffic light object for calculations
     * @return traffic light
     */
    public TrafficLight getLights() {
        return lights;
    }

    private int rand1(int lo, int hi) {
        int n = hi - lo + 1;
        int i = rand.nextInt() % n;
        if (i < 0) {
            i = -i;
        }
        return lo + i;
    }

    /**
     * main event loop
     */
    public synchronized void cycle() {
        while (true) {
            if (running) {
                //Add a new car
                if (coinFlip(hProb)) {
                    Car newCar = new Car(rand.nextInt(hLanes) + 1, hLanes, 0, rand1(1, 3));
                    newCar.setNextAction(traffic, hLanes, vLanes, lights, traffic.size(), count);
                    traffic.add(newCar);
                }
                //Add a new car
                if (coinFlip(vProb)) {
                    Car newCar = new Car(rand.nextInt(vLanes) + 1, hLanes, 1, rand1(1, 3));
                    newCar.setNextAction(traffic, hLanes, vLanes, lights, traffic.size(), count);
                    traffic.add(newCar);
                }
                //Switch traffic Lights
                if (count % 20 == 0) {
                    lights.changeColour();
                }
                int maxLanes = hLanes;
                if (vLanes > hLanes) {
                    maxLanes = vLanes;
                }
                if (count % 20 == maxLanes) {
                    lights.setState(2);
                }
                count++;

                //Wait
                for (int i = 0; i < 10; ++i) {
                    try {
                        Thread.sleep(50);
                        for (int k = 0; k < traffic.size(); ++k) {
                            int sp = traffic.get(k).speed;
                            for (int cr = 0; cr < sp; cr++) {
                                traffic.get(k).move();
                                traffic.get(k).setNextAction(traffic, hLanes, vLanes, lights, k, count);
                                traffic.get(k).animate(cycleCount);
                            }
                        }
                        if (cycleCount < 10) {
                            cycleCount++;
                        } else {
                            cycleCount = 0;
                        }
                    } catch (InterruptedException ex) {
                        System.out.println("Sleep Interupted");
                    }
                }
            }
        }
    }

    /**
     * depreciated
     * @return get current part of cycle
     */
    public int getCycleCount() {
        return cycleCount;
    }

    /**
     * Probability coin flip
     * @param prob percentage as a float
     * @return true or false
     */
    public boolean coinFlip(float prob) {
        if ((Math.random() * 100) < prob) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Get horizontal lanes
     * @return lanes
     */
    public int getHLanes() {
        return hLanes;
    }

    /**
     * Get vertical lanes
     * @return lanes
     */
    public int getVLanes() {
        return vLanes;
    }

    /**
     * Get probability of a car entering the horizontal street
     * @return probability as a float
     */
    public float getHProb() {
        return vProb;
    }

    /**
     * Get probability of a car entering the vertical street
     * @return probability as a float
     */
    public float getVProb() {
        return hProb;
    }

    /**
     * Set Horizontal lanes
     * @param hLanes
     */
    public void setHLanes(int hLanes) {
        this.hLanes = hLanes;
    }

    /**
     * Set vertical lanes
     * @param vLanes
     */
    public void setVLanes(int vLanes) {
        this.vLanes = vLanes;
    }

    /**
     * Set Horizontal Probability
     * @param hProb
     */
    public void setHProb(float hProb) {
        this.hProb = hProb;
    }

    /**
     * Set vertical Probability
     * @param vProb
     */
    public void setVProb(float vProb) {
        this.vProb = vProb;
    }

    /**
     * Clear arrayList of cars
     */
    public void resetCars() {
        count = 1;
        traffic.clear();
    }

    /**
     * get the the current cycle count
     * @return count
     */
    public int getCount() {
        return count - 1;
    }

    /**
     * Load state of traffic (used with open file)
     * @param count
     * @param hLanes
     * @param vLanes
     * @param hProb
     * @param vProb
     */
    public void loadState(int count, int hLanes, int vLanes, float hProb, float vProb) {
        this.count = count;
        this.hLanes = hLanes;
        this.vLanes = vLanes;
        this.hProb = hProb;
        this.vProb = vProb;
    }
}
