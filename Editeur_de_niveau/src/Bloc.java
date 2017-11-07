import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

/**
 * Created by vinspi on 07/11/17.
 */
public class Bloc extends JButton implements MouseListener{

    public static final int E_BLOC = 0;
    public static final int E_PATH = 1;

    private boolean survol = false;
    private int etat;

    public int getEtat() {
        return etat;
    }

    public void setEtat(int etat) {
        this.etat = etat;
    }

    public Bloc(String s) {
        super(s);
        this.etat = E_BLOC;
        this.addMouseListener(this);
    }

    @Override
    public void paint(Graphics graphics) {

        super.paint(graphics);

        if(etat == E_BLOC) {
            graphics.setColor(new Color(27, 59, 145));
            graphics.fillRect(0, 0, this.getWidth(), this.getHeight());
            graphics.setColor(new Color(209, 214, 229));
            graphics.drawRect(0, 0, this.getWidth(), this.getHeight());
            if(survol){
                graphics.setColor(new Color(209, 214, 229));
                graphics.fillRect(0, 0, this.getWidth(), this.getHeight());
            }
        }
        else {
            graphics.setColor(new Color(10, 20, 52));
            graphics.fillRect(0, 0, this.getWidth(), this.getHeight());
            if(survol){
                    graphics.setColor(new Color(209, 214, 229));
                    graphics.fillRect(0, 0, this.getWidth(), this.getHeight());
            }
        }
    }

    @Override
    public void mouseClicked(MouseEvent mouseEvent) {

    }

    @Override
    public void mousePressed(MouseEvent mouseEvent) {

    }

    @Override
    public void mouseReleased(MouseEvent mouseEvent) {

    }

    @Override
    public void mouseEntered(MouseEvent mouseEvent) {
       survol = true;
       repaint();
    }

    @Override
    public void mouseExited(MouseEvent mouseEvent) {
        survol = false;
        repaint();
    }
}
