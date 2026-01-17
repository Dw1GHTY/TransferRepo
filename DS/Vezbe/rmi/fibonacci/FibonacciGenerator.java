
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class FibonacciGenerator extends UnicastRemoteObject implements IFibonacciGenerator {

    public FibonacciGenerator() throws RemoteException {
        super();
        try {

        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public void generateFibonacciForNumber(int number, ICallback cb) throws RemoteException {
        try {
            int prev = 0;
            int current = 1;
            for (int i = 0; i < number; i++) {
                cb.printGeneratedNumber(current);
                int next = prev + current;
                prev = current;
                current = next;
            }
        } catch (Exception e) {
            System.out.println(e);
        }
    }

}
