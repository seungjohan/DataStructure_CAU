import java.awt.*;
import java.awt.event.*;
import java.awt.geom.Rectangle2D;
import java.awt.image.BufferedImage;
import javax.swing.*;

/**
 * This class provides a GUI for displaying fractals.
 * It also houses a main function that runs the application.
 */
public class FractalExplorer {
    /** Side-length of our square display area. **/
    private int dispSize;
    /** Image area for our fractal. **/
    private JImageDisplay img;
    /** Used to generate fractals of a specified kind. **/
    private FractalGenerator fGen;
    /** The current viewing area in our image. **/
    private Rectangle2D.Double range;

    /** Initializes the display image, fractal generator, and initial viewing area.
     */
    public FractalExplorer(int dispSize) {
        this.dispSize = dispSize;
        this.fGen = new Mandelbrot();
        this.range = new Rectangle2D.Double(0, 0, 0, 0);
        fGen.getInitialRange(this.range);
    }

    /**
     * Sets up and displays the GUI.
     */
    public void createAndShowGUI() {

        /** We have to set the component constructor. so we have to consider type. That's all **/
        /** Create the GUI components. **/
        JFrame frame = new JFrame("Fractal Explorer");
        img = new JImageDisplay(dispSize, dispSize);
        JButton button = new JButton("Reset Display");

        /** We have to set component and then add listener with GUI component
         *  so First, create the handler and then connect with actionlistener to button.
         *  Second, create the mousehandler and then connect with mouselistener to img.
         *  and last set the setaction reset button for making it clear that the button "reset display" is
         *  the button that I intend to show image back to the origin one. **/
        /** Add listeners to components. **/
        ActionHandler handler = new ActionHandler();
        button.addActionListener(handler);
        MouseHandler mouseHandler = new MouseHandler();
        img.addMouseListener(mouseHandler);
        button.setActionCommand("Reset");

        /** set the frame and then place img on the center side and button on the south side with borderlayout
         * only we have to think is just api and use borderlayout for not using from the default layout.  **/
        /** Put all of the components into the Frame. **/
        frame.setLayout( new BorderLayout());

        frame.add(img, BorderLayout.CENTER);
        frame.add(button, BorderLayout.SOUTH);

        /** Display the frame and components within **/
        frame.pack();
        frame.setVisible(true);
        frame.setResizable(false);
    }

    /** Draw the fractal pixel by pixel. **/
    public void drawFractal() {
        for (int i = 0; i < dispSize; i++) {
            for (int j = 0; j < dispSize; j++) {
                double x = FractalGenerator.getCoord(range.x, range.x+range.width, dispSize, i);
                double y = FractalGenerator.getCoord(range.y, range.y+range.width, dispSize, j);
                double numIters = fGen.numIterations(x, y);
                if (numIters == -1) {
                    /** The pixel is not in the set. Color it black. **/
                    img.drawPixel(i, j, 0);
                }
                else {
                    /** The pixel is in the fractal set.
                     *  Color the pixel based on the number of iterations
                     *  it took to escape.
                     */
                    float hue = 0.7f + (float) numIters / 200f;
                    int rgbColor = Color.HSBtoRGB(hue, 1f, 1f);
                    img.drawPixel(i, j, rgbColor);
                }
            }
        }
        img.repaint();
    }

    /** Simple handler to reset the zoom level. **/
    private class ActionHandler implements ActionListener {

        /** We have to make method because ActionHandler class is abstract class
         *  and We need to set the if grammer because we have to make clear that the button "Reset Display" is the right
         *  button for showing back to the original image.
         *  and we need to call the getinitialrange with fGen for showing the original one. and the range is already set
         *  so the thing only we have to do is just call the range that already existed. and then draw the Fractal.**/
        @Override
        public void actionPerformed(ActionEvent e) {
            if(e.getActionCommand() == "Reset") {
                fGen.getInitialRange(range);
                drawFractal();
            }
        }
    }

    /** Simple handler to zoom in on the clicked pixel. **/
    private class MouseHandler extends MouseAdapter {
        public void mouseClicked(MouseEvent e) {
            double x = FractalGenerator.getCoord(range.x, range.x+range.width, dispSize, e.getX());
            double y = FractalGenerator.getCoord(range.y, range.y+range.width, dispSize, e.getY());
            fGen.recenterAndZoomRange(range, x, y, 0.5);
            drawFractal();
        }
    }

    /** Run the application. **/
    public static void main(String[] args) {
        FractalExplorer fracExp = new FractalExplorer(500);
        fracExp.createAndShowGUI();
        fracExp.drawFractal();
    }
}
