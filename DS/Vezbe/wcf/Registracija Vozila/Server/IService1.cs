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
    interface IRegistracijaService 
    {
        [OperationContract(IsOneWay = true)]
        void RegistrujVozilo(Vlasnik vl, Vozilo voz, DateTime datumKrajaReg);

        [OperationContract(IsOneWay = false)]
        List<Vozilo> vratiVozilaVlasnika(Vlasnik v);

        [OperationContract(IsOneWay = false)]
        List<Registracija> vratiRegistracijeVozila(Vozilo v);

        [OperationContract(IsOneWay = false)]
        List<Registracija> vratiVozilaIRegistracije();

    }

    [DataContract]
    class Vlasnik 
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
    class Vozilo 
    {
        string marka, model, boja;
        int brojSasije;

        [DataMember]
        public string Marka { get; set; }

        [DataMember]
        public string Model { get; set; }

        [DataMember]
        public string Boja { get; set; }

        [DataMember]
        public int BrojSasije { get; set; }
    }


    [DataContract]
    class Registracija 
    {
        Vlasnik vl;
        Vozilo voz;
        DateTime datumPocetkaRegistracije, datumKrajaRegistracije;
        int brojRegistracije;


        [DataMember]
        public Vlasnik Vlasnik { get; set; }

        [DataMember]
        public Vozilo Vozilo { get; set; }

        [DataMember]
        public DateTime DatumPocetkaRegistracije { get; set; }

        [DataMember]
        public DateTime DatumKrajaRegistracije { get; set; }

        [DataMember]
        public int BrojRegistracije { get; set; }

    }

}
