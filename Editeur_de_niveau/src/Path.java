import javax.swing.*;
import java.awt.*;

/**
 * Created by vinspi on 07/11/17.
 */
public class Path extends JButton {

    public Path(String s) {
        super(s);
    }

    @Override
    public void paint(Graphics graphics) {
        super.paint(graphics);
        graphics.setColor(new Color(27,59,145));
        graphics.fillRect(0,0,this.getWidth(),this.getHeight());
    }
}
