import java.rmi.Naming;

public class Klijent {

    public Klijent(){
        try {
            
            Naming.lookup("rmi://localhost:1099/service");

        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static void main(String[] args) {
        new Klijent();
        System.console().readLine();
    }

}
