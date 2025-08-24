import java.io.Serializable;

public class Message implements Serializable {
    private String naslov;  //naslov ce biti topic, a ukoliko vec postoji dodace se na topic Hmapu
    private String sadrzaj;

    public Message(String naslov, String sadrzaj) {
        this.naslov = naslov;
        this.sadrzaj = sadrzaj;
    }


    
    public String getNaslov() {
        return naslov;
    }
    public void setNaslov(String naslov) {
        this.naslov = naslov;
    }
    public String getSadrzaj() {
        return sadrzaj;
    }
    public void setSadrzaj(String sadrzaj) {
        this.sadrzaj = sadrzaj;
    }
}
