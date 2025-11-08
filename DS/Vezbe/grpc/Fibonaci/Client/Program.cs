
using Grpc.Net.Client;
using Grpc.Core;
using FibonacciProtoNamespace;
int main () {

    using var channel = GrpcChannel.ForAddress("https://localhost:5208");
    var client = new Fibonacci


    return 0;

}