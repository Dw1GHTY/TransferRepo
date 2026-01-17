
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;

public class Server {

    private FibonacciGenerator fibonacciGenerator;

    public Server() throws RemoteException {
        try {
            this.fibonacciGenerator = new FibonacciGenerator();
            LocateRegistry.createRegistry(1099);
            Naming.rebind("rmi://localhost:1099/fibonacci", fibonacciGenerator);

        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public static void main(String[] args) throws RemoteException {
        try {
            new Server();
            System.out.println("Server listening on port :1099");
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}
