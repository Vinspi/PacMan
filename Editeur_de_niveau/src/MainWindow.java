import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.*;

/**
 * Created by vinspi on 07/11/17.
 */
public class MainWindow extends JFrame implements ActionListener, KeyListener{

    public static final int EDITION_BLOC = 0;
    public static final int EDITION_SUPER_DOT = 1;
    public static final int EDITION_BLINKY = 2;
    public static final int EDITION_PINKY = 3;
    public static final int EDITION_INKY = 4;
    public static final int EDITION_CLYDE = 5;
    public static final int EDITION_PACMAN = 6;


    private GridLayout layout;
    private int[][] matriceModel;
    private Bloc[][] matriceButton;
    private int width;
    private int height;
    private JButton ecriture;
    private int modeEdition;
    private int[] pos_pacman = new int[2];
    private int[] pos_blinky = new int[2];
    private int[] pos_pinky = new int[2];
    private int[] pos_inky = new int[2];
    private int[] pos_clyde = new int[2];

    public MainWindow(int width, int height) throws HeadlessException {

        this.matriceButton = new Bloc[width][height];
        this.width = width;
        this.height = height;
        layout = new GridLayout(width,height);

        this.getContentPane().setLayout(new BorderLayout());

        JPanel p = new JPanel();
        p.setLayout(layout);

        ecriture = new JButton("ecrire le niveau");
        ecriture.addActionListener(this);


        for (int i=0;i<width;i++){
            for(int j=0;j<height;j++){
                this.matriceButton[i][j] = new Bloc("bloc");
                this.matriceButton[i][j].setSize(32,32);
                this.matriceButton[i][j].addActionListener(this);
                this.matriceButton[i][j].addKeyListener(this);
                p.add(matriceButton[i][j],i,j);

            }
        }

        this.add(p,BorderLayout.CENTER);
        this.add(ecriture,BorderLayout.SOUTH);

        this.setVisible(true);
        this.setSize(this.width*32,this.height*32);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setResizable(false);
    }

    @Override
    public void keyTyped(KeyEvent keyEvent) {

    }

    @Override
    public void keyPressed(KeyEvent keyEvent) {


        if(keyEvent.getKeyChar() == 'n'){

            modeEdition = EDITION_BLOC;

        }
        if(keyEvent.getKeyChar() == 'd'){

                modeEdition = EDITION_SUPER_DOT;

        }
        if(keyEvent.getKeyChar() == 'i'){

                modeEdition = EDITION_INKY;

        }
        if(keyEvent.getKeyChar() == 'b'){

                modeEdition = EDITION_BLINKY;

        }
        if(keyEvent.getKeyChar() == 'p'){

                modeEdition = EDITION_PINKY;

        }
        if(keyEvent.getKeyChar() == 'c'){

                modeEdition = EDITION_CLYDE;

        }
        if(keyEvent.getKeyChar() == 'j'){

                modeEdition = EDITION_PACMAN;

        }
    }

    @Override
    public void keyReleased(KeyEvent keyEvent) {

    }

    @Override
    public void actionPerformed(ActionEvent actionEvent) {
        Object source = actionEvent.getSource();
        int collectible;

        for(int i=0;i<this.width;i++){
            for(int j=0;j<this.height;j++){
                if(source.equals(this.matriceButton[i][j])){
                    if(modeEdition == EDITION_BLOC) {
                        if (this.matriceButton[i][j].getEtat() == Bloc.E_BLOC)
                            this.matriceButton[i][j].setEtat(Bloc.E_PATH);
                        else this.matriceButton[i][j].setEtat(Bloc.E_BLOC);
                    }
                    if(modeEdition == EDITION_SUPER_DOT){
                        this.matriceButton[i][j].isBigGum = !this.matriceButton[i][j].isBigGum;
                        this.matriceButton[i][j].repaint();

                    }
                    if(modeEdition == EDITION_PACMAN){
                        this.matriceButton[i][j].isPacman = !this.matriceButton[i][j].isPacman;
                        this.matriceButton[i][j].repaint();
                        this.pos_pacman[0] = i;
                        this.pos_pacman[1] = j;
                    }
                    if(modeEdition == EDITION_BLINKY){
                        this.matriceButton[i][j].isBlinky = !this.matriceButton[i][j].isBlinky;
                        this.matriceButton[i][j].repaint();
                        this.pos_blinky[0] = i;
                        this.pos_blinky[1] = j;
                    }
                    if(modeEdition == EDITION_INKY){
                        this.matriceButton[i][j].isInky = !this.matriceButton[i][j].isInky;
                        this.matriceButton[i][j].repaint();
                        this.pos_inky[0] = i;
                        this.pos_inky[1] = j;
                    }
                    if(modeEdition == EDITION_PINKY){
                        this.matriceButton[i][j].isPinky = !this.matriceButton[i][j].isPinky;
                        this.matriceButton[i][j].repaint();
                        this.pos_pinky[0] = i;
                        this.pos_pinky[1] = j;
                    }
                    if(modeEdition == EDITION_CLYDE){
                        this.matriceButton[i][j].isClyde = !this.matriceButton[i][j].isClyde;
                        this.matriceButton[i][j].repaint();
                        this.pos_clyde[0] = i;
                        this.pos_clyde[1] = j;
                    }
                }
            }
        }
        if(source.equals(ecriture)){
            try {

                File file = new File("xml_level.xml");

                if(!file.exists()){
                    file.createNewFile();
                }

                BufferedWriter br = new BufferedWriter(new FileWriter(file));
                PrintWriter out = new PrintWriter(br);
                out.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");



                out.write("<tilemap>\n");
                /* ici inserer pos pacman et fantômes */

                out.write("<blinky-init col=\""+pos_blinky[1]+"\" row=\""+(23-pos_blinky[0])+"\"></blinky-init>\n");
                out.write("<inky-init col=\""+pos_inky[1]+"\" row=\""+(23-pos_inky[0])+"\"></inky-init>\n");
                out.write("<pinky-init col=\""+pos_pinky[1]+"\" row=\""+(23-pos_pinky[0])+"\"></pinky-init>\n");
                out.write("<clyde-init col=\""+pos_clyde[1]+"\" row=\""+(23-pos_clyde[0])+"\"></clyde-init>\n");
                out.write("<pacman-init col=\""+pos_pacman[1]+"\" row=\""+(23-pos_pacman[0])+"\"></pacman-init>\n");

                /* *************************************** */
                out.write("\t<tilemap-width value=\""+width+"\"></tilemap-width>\n" +
                        "\t<tilemap-height value=\""+height+"\"></tilemap-height>\n");

                out.write("\t\t<layer id=\"background\">\n");
                for (int i = 0; i < width; i++) {
                    out.write("\t\t\t<row id=\""+i+"\">\n");
                    for (int j = 0; j < height; j++) {
                        out.write("\t\t\t\t<tile col=\""+i+"\" row=\""+j+"\" value=\""+this.matriceButton[23-j][i].getEtat()+"\"></tile>\n");
                    }
                    out.write("\t\t\t</row>\n");
                }
                out.write("\t\t</layer>\n");

                out.write("\t\t<layer id=\"collectibles\">\n");
                for (int i = 0; i < width; i++) {
                    out.write("\t\t\t<row id=\""+i+"\">\n");
                    for (int j = 0; j < height; j++) {
                        if(matriceButton[23-j][i].isBigGum)
                            collectible = 2;
                        else collectible = matriceButton[23-j][i].getEtat();
                        out.write("\t\t\t\t<tile col=\""+i+"\" row=\""+j+"\" value=\""+collectible+"\"></tile>\n");
                    }
                    out.write("\t\t\t</row>\n");
                }
                out.write("\t\t</layer>\n");

                out.write("</tilemap>\n");
                out.flush();
                out.close();
            }
            catch (IOException e){
                e.printStackTrace();
            }
        }
        this.repaint();
    }
}
