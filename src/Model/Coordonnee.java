package Model;

/**
 * Created by Fabien on 06/04/2017.
 */
public class Coordonnee {

    private int abscisse;
    private int ordonee;

    public Coordonnee(){
        this.abscisse = 0;
        this.ordonee = 0;
    }

    public Coordonnee(int abscisse, int ordonee) {
        this.abscisse = abscisse;
        this.ordonee = ordonee;
    }

    public int getAbscisse() {
        return abscisse;
    }

    public int getOrdonee() {
        return ordonee;
    }

    public void setAbscisse(int abscisse) {
        this.abscisse = abscisse;
    }

    public void setOrdonee(int ordonee) {
        this.ordonee = ordonee;
    }
}
