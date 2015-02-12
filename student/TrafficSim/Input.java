package TrafficSim;

import java.io.*;

public class Input {
   /**
    * Get input from user in command line. Very handy
    * @param query The question to be asked before getting input.
    * @return the String entered by the user
    */
   public String prompt(String query) {
        System.out.println();
        String inputLine = null;
        System.out.print(query + " ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            inputLine = is.readLine();
            if (inputLine.length() == 0) return null;
        } catch (IOException e) {
            System.out.println("IOException: " + e);
        }

        return inputLine;
    }
}
