/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package TrafficSim;

import java.awt.Image;
import java.io.File;
import java.io.IOException;
import java.net.URL;
import javax.imageio.ImageIO;


public class ImageLoader {

    private Image[] images;
    /**
     * Image names
     */
    public final String[] fileNames = {"grass", "road", "car1H", "car2H", "car3H", "car1V", "car2V", "car3V", "lighta", "lightr", "lightg"};

    public ImageLoader() {
        images = new Image[fileNames.length];
        loadImages();
    }

    private void loadImages() {
        for (int i = 0; i < fileNames.length; ++i) {
            try {
                images[i] = ImageIO.read(new File("images/" + fileNames[i] + ".png"));
            } catch (IOException ex) {
                System.out.println("Could not load image: " + fileNames[i]);
            }
        }
    }

    /**
     * Get a loaded image based on it's name
     * @param imgName the name of the image you want to retrieve
     * @return the Image object based on the name supplied
     */
    public Image getImage(String imgName) {
        for (int i = 0; i < images.length; ++i) {
            if (imgName.equals(fileNames[i])) return images[i];
        }
        return images[0];
    }

    /**
     * Get a loaded image based of it's index
     * @param imgIndex the index of an image
     * @return the image stored at that index
     */
    public Image getImage(int imgIndex) {
        return images[imgIndex];
    }
}
