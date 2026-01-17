using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace Server
{
    [ServiceContract(CallbackContract = typeof(ICallback))]
    interface IKalkulatorService 
    {
        [OperationContract(IsOneWay = true)]
        void obrisiRacunanje();

        [OperationContract(IsOneWay = false)]
        void dodajBroj(int broj);

        [OperationContract(IsOneWay = false)]
        void oduzmiBroj(int broj);

        [OperationContract(IsOneWay = false)]
        void pomnoziBrojem(int broj);

        [OperationContract(IsOneWay = false)]
        void podeliBrojem(int broj);
    }


    [DataContract]
    class Rezultat 
    {
        int rezultatOperacije;
        string operacija;

        [DataMember]
        public int RezultatOperacije { get; set; }

        [DataMember]
        public string Operacija { get; set; }
    }


    [ServiceContract]
    interface ICallback 
    {
        [OperationContract(IsOneWay = true, Name = "CallbackObavestiKlijenta")]
        void obavestiKlijenta(Rezultat rez);
    }
}
