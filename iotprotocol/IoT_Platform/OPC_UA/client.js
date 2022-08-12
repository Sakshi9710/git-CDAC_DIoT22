/*---------------------------------------------------------------------------
 * Demo OPC UA Client Program for DIoT Session
 * Date: Jun 2022
 * Description: A client to connect OPC UA server and request Temp variable
 * --------------------------------------------------------------------------*/
const nodeOPCUA = require("node-opcua");
const OPC_UA_ENDPOINT_URL = "opc.tcp://localhost:26683";

// Client connection Options
const options = {
    applicationName: "DIoTClient",
    securityMode: nodeOPCUA.MessageSecurityMode.None,
    securityPolicy: nodeOPCUA.SecurityPolicy.None,
    endpointMustExist: false
}

const opcClient = nodeOPCUA.OPCUAClient.create(options);

async function start() {
    try {
        // Connect to the Server
        await opcClient.connect(OPC_UA_ENDPOINT_URL);
        console.log("Connected to the server. Creating a session now...")
        
        // Create a Session with Server
        const session = await opcClient.createSession();
        console.log("Done, a session is created. Referencing the RootFolder for variables...");

        const result = await session.browse("RootFolder");
        console.log(JSON.stringify(result,null,2));
        const nodeToRead = {
        nodeId: "ns=1;s=Temperature",
        attributeId: nodeOPCUA.AttributeIds.Value
        };
        const dataValue = await session.read(nodeToRead);
        console.log(" value ", dataValue.toString());

        
    }catch(error) {
        console.log("Some error occured. Error "+ error)
    }
}

start();

