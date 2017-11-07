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

    private GridLayout layout;
    private int[][] matriceModel;
    private Bloc[][] matriceButton;
    private int width;
    private int height;
    private JButton ecriture;
    private int modeEdition;

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
        System.out.println("coucou");
        if(keyEvent.getKeyChar() == 'd'){
            if(modeEdition == EDITION_BLOC)
                modeEdition = EDITION_SUPER_DOT;
            else modeEdition = EDITION_BLOC;
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
                out.write("\t<tilemap-width value=\""+width+"\"></tilemap-width>\n" +
                        "\t<tilemap-height value=\""+height+"\"></tilemap-height>\n");

                out.write("\t\t<layer id=\"background\">\n");
                for (int i = 0; i < width; i++) {
                    out.write("\t\t\t<row id=\""+i+"\">\n");
                    for (int j = 0; j < height; j++) {
                        out.write("\t\t\t\t<tile col=\""+i+"\" row=\""+j+"\" value=\""+this.matriceButton[i][j].getEtat()+"\"></tile>\n");
                    }
                    out.write("\t\t\t</row>\n");
                }
                out.write("\t\t</layer>\n");

                out.write("\t\t<layer id=\"collectibles\">\n");
                for (int i = 0; i < width; i++) {
                    out.write("\t\t\t<row id=\""+i+"\">\n");
                    for (int j = 0; j < height; j++) {
                        if(matriceButton[i][j].isBigGum)
                            collectible = 2;
                        else collectible = matriceButton[i][j].getEtat();
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
