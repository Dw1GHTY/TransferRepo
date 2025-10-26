import java.io.Serializable;

public class Student implements Serializable{
    private String indeks;
    private String ime;
    private String email;


    public Student(String indeks, String ime, String email){
        super();
        this.indeks = indeks;
        this.ime = ime;
        this.email = email;
    }
    public String getIndeks() {
        return indeks;
    }
    public String getIme(){
        return this.ime;
    }
    public String getEmail() {
        return email;
    }
}