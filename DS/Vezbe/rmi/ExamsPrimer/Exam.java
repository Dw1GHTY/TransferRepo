import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.List;
import java.rmi.RemoteException;

public class Exam extends UnicastRemoteObject implements IExam  {
    private int idIspita;
    private String nazivIspita;
    private int brojPrijavljenih;
    private List<Student> prijavljeniStudenti;


    public Exam(int idIspita, String nazivIspita) throws RemoteException {
        try {
            this.idIspita = idIspita;
            this.nazivIspita = nazivIspita;
            this.brojPrijavljenih = 0;
            this.prijavljeniStudenti = new ArrayList<Student>();
        } catch (Exception e) {
            throw new RemoteException(e.getMessage());
        }
    }

    public void prijaviIspit(Student s) throws RemoteException{
        try {
            this.prijavljeniStudenti.add(s);
            this.brojPrijavljenih++;
        } catch (Exception e) {
            System.out.println(e.getMessage());
            throw new RemoteException(e.getMessage());
        }
    }

    public int brojPrijavljenih(int idIspita) throws RemoteException {
        try {
            return this.brojPrijavljenih;
            
        } catch (Exception e) {
            throw new RemoteException(e.getMessage());
        }
    }

}
