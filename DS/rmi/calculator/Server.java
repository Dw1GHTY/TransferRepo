import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;

public class Server {

    public Server() throws RemoteException{
        try {
            
            ICalculator c = new Calculator();
            LocateRegistry.createRegistry(1099);
            Naming.rebind("rmi://localhost:1099/service", c);
            System.out.println("*****Server initialized*****");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static void main(String[] args){
        try {
            new Server();   
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        System.console().readLine();
    }
    
}