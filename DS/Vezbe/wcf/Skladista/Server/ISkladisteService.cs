using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace Server
{
    [ServiceContract]
    public interface ISkladisteService
    {
        [OperationContract(IsOneWay = true)]
        void zakupiSkladiste(Vlasnik vlasnik, Skladiste skladiste);

        [OperationContract(IsOneWay = false)]
        List<Skladiste> vratiAktivnaSkladista(Vlasnik vlasnik);

        [OperationContract(IsOneWay = false)]
        List<Vlasnik> vratiVlasnikeSkladista();

    }

    [DataContract]
    public class Vlasnik
    {
        string ime, prezime, jmbg;
        [DataMember]
        public string Ime { get; set; }
        [DataMember]
        public string Prezime { get; set; }
        [DataMember]
        public string Jmbg { get; set; }
    }


    [DataContract]
    public class Skladiste
    {
        int id, cena;
        DateTime pocetakZakupa, krajZakupa;

        [DataMember]
        public int Id { get; set; }
        [DataMember]
        public int Cena { get; set; }
        [DataMember]
        public DateTime PocetakZakupa { get; set; }
        [DataMember]
        public DateTime KrajZakupa { get; set; }
    }
}
