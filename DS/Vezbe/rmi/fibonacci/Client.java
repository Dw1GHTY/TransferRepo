
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class Client {

    private IFibonacciGenerator fib;
    private ICallback clientCallback;

    public Client() throws RemoteException {
        try {
            clientCallback = new Callback();
            fib = (IFibonacciGenerator) Naming.lookup("rmi://localhost:1099/fibonacci");

        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public static void main(String[] args) {
        try {
            Client client = new Client();
            System.out.println("Generate for number 10");
            client.executeFibonacci(10, client.clientCallback);
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public void executeFibonacci(int number, ICallback cb) throws RemoteException {
        fib.generateFibonacciForNumber(number, cb);
    }

    public static class Callback extends UnicastRemoteObject implements ICallback {

        public Callback() throws RemoteException {
            super();
        }

        public void printGeneratedNumber(int number) throws RemoteException {
            System.out.println("Element: " + number);
        }
    }

}
