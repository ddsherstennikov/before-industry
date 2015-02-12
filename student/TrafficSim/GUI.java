//Author: Luke Atkins
package TrafficSim;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.*;

public class GUI extends JFrame {

    final int MAX_WIDTH = 24 * MapPanel.BLOCKSIZE + 200;
    final int MAX_HEIGHT = 23 * MapPanel.BLOCKSIZE + 128;
    private MapPanel map;
    private boolean running;
    private JButton playStop;
    private JComboBox vLaneList;
    private JComboBox hLaneList;
    private JSlider vProbInput;
    private JSlider hProbInput;
    private JPanel buttons;
    private JPanel lanes;
    private JPanel probs;
    private JPanel topBar;
    private JButton quit;

    GUI() {
        setSize(MAX_WIDTH, MAX_HEIGHT);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        JPanel spacerWest = new JPanel();
        spacerWest.setPreferredSize(new Dimension(50, 300));
        map = new MapPanel(2, 2);
        setupButtons();
        addListeners();
        getContentPane().add(BorderLayout.WEST, spacerWest);
        getContentPane().add(BorderLayout.CENTER, map);
        setVisible(true);
        setExtendedState(JFrame.MAXIMIZED_BOTH);
        running = false;
        go();

    }

    private void go() {
        while (true) {
            try {
                Thread.sleep(100);
            } catch (InterruptedException ex) {
                System.out.println("Sleep Interupted");
            }
            map.sim.setHProb((float) hProbInput.getValue());
            map.sim.setVProb((float) vProbInput.getValue());
            repaint();
        }
    }

    private void setupButtons() {
        playStop = new JButton("Play");
        String[] vLaneData = {"1", "2", "3", "4"};
//        vLaneList = new JComboBox(vLaneData);
        String[] hLaneData = {"1", "2", "3"};
//        hLaneList = new JComboBox(hLaneData);
        vProbInput = new JSlider(0, 100, 50);
        hProbInput = new JSlider(0, 100, 50);
        buttons = new JPanel();
        lanes = new JPanel();
        probs = new JPanel();

//        vLaneList.setSelectedIndex(1);
//        hLaneList.setSelectedIndex(1);

//        JLabel vLaneLabel = new JLabel("  Vertical Lanes:    ");
//        JLabel hLaneLabel = new JLabel("  Horizontal Lanes:  ");
        JLabel vProbLabel = new JLabel("  Vertical Probability:  ");
        JLabel hProbLabel = new JLabel("  Horizontal Probability:");

        lanes.setLayout(new GridLayout(2, 2));
//        lanes.add(vLaneLabel);
//        lanes.add(vLaneList);
//        lanes.add(hLaneLabel);
//        lanes.add(hLaneList);

        probs.setLayout(new GridLayout(2, 2));
        probs.add(vProbLabel);
        probs.add(vProbInput);
        probs.add(hProbLabel);
        probs.add(hProbInput);

        buttons.setLayout(new GridLayout(1, 2));
        //buttons.add(playStop);
        buttons.add(lanes);
        buttons.add(probs);

        getContentPane().add(BorderLayout.SOUTH, buttons);
   
        quit = new JButton("Exit");
        topBar = new JPanel();
        topBar.add(playStop);
        topBar.add(quit);
        getContentPane().add(BorderLayout.NORTH, topBar);
    }

    private void addListeners() {
        playStop.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent e) {
                running = !running;
                if (running) {
                    playStop.setText("Stop");
                } else {
                    playStop.setText("Play");
                }
                map.sim.toggleRun();
            }
        });

  /*      hLaneList.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent e) {
                int hLanes = hLaneList.getSelectedIndex() + 1;
                map.setHLanes(hLanes);
                map.sim.resetCars();
            }
        });

        vLaneList.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent e) {
                int vLanes = vLaneList.getSelectedIndex() + 1;
                map.setVLanes(vLanes);
                map.sim.resetCars();
            }
        });

*/
        quit.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent e) {
                System.exit(1);
            }
        });
    }
}
