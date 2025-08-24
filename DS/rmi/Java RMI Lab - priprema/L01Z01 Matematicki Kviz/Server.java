import java.rmi.Naming;
import java.rmi.registry.LocateRegistry;

public class Server {
    public IKviz k;
    
    public Server(){
        try {
            k = new Kviz();
            LocateRegistry.createRegistry(1099);
            Naming.rebind("rmi://localhost:1099/service", k);
            
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

    }

    public static void main(String[] args) {
        try {
            new Server();
            System.out.println("SERVER INITIALIZED");
            System.console().readLine();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}