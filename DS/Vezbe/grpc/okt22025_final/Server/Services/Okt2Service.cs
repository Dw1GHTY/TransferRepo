using Grpc.Core;
using ProtoNamespace;

namespace Server.Services
{
    public class Okt2Service: ProtoNamespace.Okt2ServiceProto.Okt2ServiceProtoBase
    {
        public Okt2Service() { }

        public override async Task isSquare(
            IAsyncStreamReader<Input> inputStream,
            IServerStreamWriter<ResponseMessage> outputStream,
            ServerCallContext context) 
        {
            await foreach (Input input in inputStream.ReadAllAsync()) 
            {
                if (input.B == Math.Pow(input.A, 2))
                {
                    await outputStream.WriteAsync(new ResponseMessage { Text = "Da" });
                }
                else {
                    await outputStream.WriteAsync(new ResponseMessage { Text = "Ne" });
                }


            }
        }
    }
}
