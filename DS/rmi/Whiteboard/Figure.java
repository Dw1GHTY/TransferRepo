import java.io.Serializable;

public class Figure implements Serializable{
    private String name;
    private int version;

    public Figure() {}
    public Figure(String name){
        this.name = name;
        setVersion(0);
    }

    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }
    
    public int getVersion() {
        return version;
    }
    public void setVersion(int version) {
        this.version = version;
    }
}