/*
 *  A datagram client to send and receive UDP packets in Java.
 *
 *  Instructions to run:
 *  Pass the port as command line arguments.
 *  Eg: >>javac UDPClient portNo
 */
 
import java.net.* ;
public class UDPServer
{
   //Give a standard packet size
   private final static int packetsize = 100 ;

   public static void main( String args[] )
   {
      // Check the whether the arguments are given
      if( args.length != 1 )
      {
         System.out.println( "usage: DatagramServer port" ) ;
         return ;
      }

	   DatagramSocket socket=null;	
		
      try
      {
         // Convert the argument to ensure that is it valid
         int port = Integer.parseInt( args[0] ) ;

         // Construct the socket
         socket = new DatagramSocket( port ) ;

         System.out.println( "The server is ready..." ) ;
		
		 // Create a packet
         DatagramPacket packet = new DatagramPacket( new byte[packetsize], packetsize ) ;


         for( ;; )
         {
         	try{
		        // Receive a packet (blocking)
		        socket.receive( packet ) ;

		        // Print the packet
		        System.out.println( packet.getAddress() + " " + packet.getPort() + ": " + new String(packet.getData()) ) ;

		        // Return the packet to the sender
		        socket.send( packet ) ;
         	}catch(Exception e){
         		System.out.println(e);
         	}
            
        }  
     }
     catch( Exception e )
     {
        System.out.println( e ) ;
		
     }finally{
     	socket.close();
     }
  }
}
