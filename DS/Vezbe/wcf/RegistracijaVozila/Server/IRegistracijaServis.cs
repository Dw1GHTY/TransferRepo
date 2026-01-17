using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace Server
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the interface name "IService1" in both code and config file together.
    [ServiceContract]
    public interface IRegistracijaServis
    {
        [OperationContract(IsOneWay = true)]
        void RegistrujVozilo(Vlasnik vlasnik, Vozilo vozilo, DateTime datumKrajaRegistracije);
        
        [OperationContract(IsOneWay = false)]
        List<Vozilo> vratiVozilaVlasnika(Vlasnik vlasnik);

        [OperationContract(IsOneWay = false)]
        List<Registracija> sveRegistracije();
     
    }


    // Use a data contract as illustrated in the sample below to add composite types to service operations.
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
    public class Vozilo 
    {
        string marka, model, boja;
        int brojSasije;


        [DataMember]
        public string Marko { get; set; }
        [DataMember]
        public string Model { get; set; }
        [DataMember]
        public string Boja { get; set; }

        [DataMember]
        public int BrojSasije { get; set; }
    }

    [DataContract]
    public class Registracija 
    {
        //prosledjuje korisnik
        Vozilo vozilo;
        Vlasnik vlasnik1;
        DateTime datumKrajaRegistracije;

        //dodeljuje servis
        DateTime datumPocetkaRegistracije;
        int brojRegistracije;

        [DataMember]
        public Vozilo Vozilo { get; set; }

        [DataMember]
        public Vlasnik Vlasnik { get; set; }

        [DataMember]
        public DateTime DatumKrajaRegistracije { get; set; }

        [DataMember]
        public DateTime DatumPocetkaRegistracije { get; set; }
        
        [DataMember]
        public int BrojRegistracije { get; set; }
    }
}
