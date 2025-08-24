import java.io.Serializable;
import java.rmi.RemoteException;

public class Pitanje implements IPitanje, Serializable { //! NIJE SERIALIZABLE ZATO STO SE NA KLIJENTU POZIVA NJEGOVA METODA
    
    public String tekst;
    public String a;
    public String b;
    public String c;

    public Pitanje(String t, String a, String b, String c) throws RemoteException{
        this.tekst = t;
        this.a = a;
        this.b = b;
        this.c = c;
    }

    public String vratiTekst() throws RemoteException {
        String tekstZadatka = 
        this.tekst + "\n" + 
        "a)" + this.a + "\n" +
        "b)" + this.b + "\n" +
        "c)" + this.c + "\n"; 

        return tekstZadatka.toString();
    }
    

}
