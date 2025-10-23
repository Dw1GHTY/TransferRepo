import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
public class Calculator extends UnicastRemoteObject implements ICalculator{


    public Calculator() throws RemoteException {super();}

    public int add(int a, int b) throws RemoteException {
        return a+b;
    }

    public int sub(int a, int b) throws RemoteException {
        return a-b;
    }
    public int mul(int a, int b) throws RemoteException {
        return a*b;
    }
    
}
