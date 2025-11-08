
using FibonacciProtoNamespace;
using Grpc.Core;

namespace Server.Services
{
    public class FibonacciService : FibonacciProtoNamespace.FibonacciService.FibonacciServiceBase
    {
        public override async Task GetFibonacciSequence(Number number, IServerStreamWriter<Number> outputStream, ServerCallContext context) 
        {
            int a = 1;
            int b = 1;
            int max = number.N;

            do
            {
                int tmp = a + b;
                if (tmp > max) break;
                a = b;
                b = tmp;

                await outputStream.WriteAsync(new Number() { N = tmp });
            } while (true);
        }
    }
}
