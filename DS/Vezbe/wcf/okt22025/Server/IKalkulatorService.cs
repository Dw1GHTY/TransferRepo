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
    [ServiceContract(CallbackContract = typeof(ICallback))]
    public interface IKalkulatorService
    {
        [OperationContract(IsOneWay = true)]
        void obrisiRacunanje();

        [OperationContract(IsOneWay = false)]
        float saberi(float broj);

        [OperationContract(IsOneWay = false)]
        float oduzmi(float broj);

        [OperationContract(IsOneWay = false)]
        float pomnozi(float broj);

        [OperationContract(IsOneWay = false)]
        float podeli(float broj);

    }

    [DataContract]
    public class Rezultat 
    {
        [DataMember]
        public string TrenutniIzraz { get; set; }

        [DataMember]
        public float NumerickiRezultat { get; set; }
    }


    [ServiceContract]
    public interface ICallback 
    {
        [OperationContract(IsOneWay = true, Name = "CallbackPrikaziRacunanje")]
        void prikaziRacunanje(string rez);
    }


}
