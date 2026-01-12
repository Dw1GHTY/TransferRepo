
import java.rmi.Naming;
import java.rmi.RemoteException;

public class Client {

    private IEcho client;

    public Client() throws RemoteException {
        try {
            this.client = (IEcho) Naming.lookup("rmi://localhost:1099");
            client.getEcho("ECHO");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static void main(String[] args) {
        try {
            new Client();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
