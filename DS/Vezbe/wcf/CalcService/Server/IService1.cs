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
    [ServiceContract(CallbackContract = typeof(ICalcCallback))]
    public interface ICalculatorService 
    {
        [OperationContract(IsOneWay = false)]
        void clearState();

        [OperationContract(IsOneWay = false)]
        void add(float number);

        [OperationContract(IsOneWay = false)]
        void subtract(float number);

        [OperationContract(IsOneWay = false)]
        void multiply(float number);

        [OperationContract(IsOneWay = false)]
        void divide(float number);
    }


    [ServiceContract()]
    public interface ICalcCallback 
    {
        [OperationContract(IsOneWay = true)]
        void notifyUser(float result, string currentState);
    }

}
