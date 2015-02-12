/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package TrafficSim;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.util.ArrayList;
import javax.swing.JPanel;


public class MapPanel extends JPanel {

    /**
     *  Size of square images to be used for map
     */
    final static public int BLOCKSIZE = 28;
    private int width;  //pixels
    private int height; //pixels
    private int x;      //blocks wide
    private int y;      //blocks tall
    private int hLanes;
    private int vLanes;
    private ImageLoader loader;
    /**
     * The simulator program
     */
    public TrafficSim sim;
    Thread trafficThread;

    private int cycleCount;
    private int repaints;

    MapPanel(int vLanes, int hLanes) {
        x = vLanes + 40; //lanes + 10 for each side of intersection
        
        y = hLanes + 20;
        this.hLanes = hLanes;
        this.vLanes = vLanes;
        width = x * BLOCKSIZE ;
        height = y * BLOCKSIZE;
        setSize(width, height);
        loader = new ImageLoader();
        sim = new TrafficSim();
        cycleCount = 0; //For car animations
        trafficThread = new Thread(new Runnable() {

            public void run() {
                sim.cycle();
            }
        });
        trafficThread.start();
        cycleCount = 0;
        repaints = 0;
       
    }

    @Override
    protected void paintComponent(Graphics g) {
        paintMap(g);
        paintLight(g);
        paintCars(g);
        paintCycle(g);
        if (cycleCount < 10) {
            cycleCount++;
        } else {
            cycleCount = 0;
        }
        repaints++;
    }

    private void paintMap(Graphics g) {
        String texture = "";
        for (int x = 0; x < this.x; ++x) {
            for (int y = 0; y < this.y; ++y) {
                if ((x < 19 || x > 18 + vLanes) && (y < 10 || y > 9 + hLanes)) {
                    texture = "grass";
                } else {
                    texture = "road";
                }
                g.drawImage(loader.getImage(texture), x * BLOCKSIZE, y * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE, this);
            }
        }
        g.setColor(Color.LIGHT_GRAY);
        for (int i = 1; i < hLanes; ++i) {
            g.drawLine(0, (10 + i) * BLOCKSIZE, width, (10 + i) * BLOCKSIZE);
        }
        for (int i = 1; i < vLanes; ++i) {
            g.drawLine((19 + i) * BLOCKSIZE, 0, (19 + i) * BLOCKSIZE, height);
        }
    }

    private void paintLight(Graphics g) {
        //Paint Traffic Light
        String hLight = "";
        String vLight = "";
        if (sim.getLights().getGreen()) {
            hLight = "lightg";
            vLight = "lightr";
        } else {
            hLight = "lightr";
            vLight = "lightg";
        }
        g.drawImage(loader.getImage(hLight), 18 * BLOCKSIZE, 8 * BLOCKSIZE, this);
        g.drawImage(loader.getImage(vLight), 17 * BLOCKSIZE, (12 + hLanes) * BLOCKSIZE, this);
    }

    private void paintCars(Graphics g) {
        //Paint Cars
        ArrayList<Car> traffic = sim.getTraffic();
        for (int i = 0; i < traffic.size(); ++i) {
            Car car = traffic.get(i);
            if (car.getx() >= 0 && car.getx() < this.x && car.gety() >= 0 && car.gety() < this.y) {
                g.drawImage(loader.getImage("car" + car.getType() + car.getdir()), car.getx() * BLOCKSIZE , car.gety() * BLOCKSIZE, 16, 16, this);
                //g.drawImage(loader.getImage("car" + car.getType() + car.getdir()), car.getAniX(), car.getAniY(), 16, 16, this);
            }
        }
    }

    private void paintCycle(Graphics g) {
        g.setColor(Color.GRAY);
        g.setFont(new Font("Arial Rounded MT Bold", Font.PLAIN, 24));
        g.drawString("" + sim.getCount(), 4, 24);
    }

    /**
     * Set number of horizontal lanes
     * @param hLanes number of lanes
     */
    public void setHLanes(int hLanes) {
        this.hLanes = hLanes;
        this.y = 20 + hLanes;
        width = x * BLOCKSIZE;
        height = y * BLOCKSIZE;
        sim.setHLanes(hLanes);
    }

    /**
     * Set number of vertical lanes
     * @param vLanes number of lanes
     */
    public void setVLanes(int vLanes) {
        this.vLanes = vLanes;
        this.x = 40 + vLanes;
        width = x * BLOCKSIZE;
        height = y * BLOCKSIZE;
        sim.setVLanes(vLanes);
    }
}
