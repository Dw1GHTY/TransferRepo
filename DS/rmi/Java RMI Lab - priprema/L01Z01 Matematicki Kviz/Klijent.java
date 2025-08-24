import java.rmi.Naming;

public class Klijent {
    public IKviz kviz;
    public Pitanje p;

    public Klijent(){
        try {
            kviz = (IKviz)Naming.lookup("rmi://localhost:1099/service");
            
            kviz.pocetak(); //! brPoena = 0, trenutnoPitanje = 1

            String unos = null;
            for(int i = 1; i <= 3; i++){
                p = kviz.vratiPitanje();   //! vraca trenutno pitanje klijentu   
                System.out.println(p.vratiTekst());          //! ispisuje tekst pitanja sa ponudjenim odgovorima

                System.out.println("Unesi odgovor, a b ili c: ");
                unos = System.console().readLine();
                kviz.odgovori(unos);

                System.out.println("*********Sledece pitanje:*********");
            }

            System.out.println("\n Tvoj broj poena je: " + kviz.vratiBrojPoena());
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }


    public static void main(String[] args) {
        try {
            new Klijent();
            System.console().readLine();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

}
