import java.rmi.Naming;
import java.rmi.registry.LocateRegistry;

public class Server {

    public IBroker b;


    public Server(){
        try {
            b = new Broker();     
            LocateRegistry.createRegistry(1099);
            Naming.rebind("rmi://localhost:1099/service", b);

        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }


    public static void main(String[] args) {
        new Server();
        System.out.println("Server initialized");
        System.console().readLine();
    }

}