import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;

/**
 * Created by vinspi on 07/11/17.
 */
public class MainWindow extends JFrame implements ActionListener{

    private GridLayout layout;
    private int[][] matriceModel;
    private Bloc[][] matriceButton;
    private int width;
    private int height;
    private JButton ecriture;

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
    public void actionPerformed(ActionEvent actionEvent) {
        Object source = actionEvent.getSource();
        for(int i=0;i<this.width;i++){
            for(int j=0;j<this.height;j++){
                if(source.equals(this.matriceButton[i][j])){

                    if(this.matriceButton[i][j].getEtat() == Bloc.E_BLOC)
                        this.matriceButton[i][j].setEtat(Bloc.E_PATH);
                    else this.matriceButton[i][j].setEtat(Bloc.E_BLOC);
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

                out.write("\t\t<layer id=\"control\">\n");
                for (int i = 0; i < width; i++) {
                    out.write("\t\t\t<row id=\""+i+"\">\n");
                    for (int j = 0; j < height; j++) {
                        out.write("\t\t\t\t<tile col=\""+i+"\" row=\""+j+"\" value=\""+this.matriceButton[i][j].getEtat()+"\"></tile>\n");
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
