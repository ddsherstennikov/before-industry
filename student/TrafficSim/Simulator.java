
package TrafficSim;

import javax.swing.JOptionPane;


public class Simulator {

    GUI gui;

    public Simulator() {
        gui = new GUI();
        gui.repaint();
    }

    /**
     * Starts program in either Command line or GUI
     * @param args
     */
    public static void main(String[] args) {
        Simulator sim = new Simulator();
    }
}
