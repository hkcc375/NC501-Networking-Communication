#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

class RDTSender;

class SimulatedChannel
{
      public:
	SimulatedChannel( double loss_rate = 0.3 ) : loss_rate( loss_rate ), packet( nullptr ) {}

	void send( const std::string& packet )
	{
		if( rand() / ( double ) RAND_MAX >= loss_rate ) { this->packet = packet; }
		else { this->packet = ""; }
	}

	std::string receive()
	{
		if( rand() / ( double ) RAND_MAX >= loss_rate ) { return packet; }
		return "";
	}

      private:
	double loss_rate;
	std::string packet;
};

class RDTReceiver;

class RDTSender
{
      public:
	RDTSender( SimulatedChannel& channel ) : channel( channel ), seq_num( 0 ) {}

	void rdt_send( const std::pair< std::string, std::string >& data, RDTReceiver& receiver );

	void send_packet( const std::string& packet ) { channel.send( packet ); }

	std::string make_packet( const std::pair< std::string, std::string >& data );

      private:
	SimulatedChannel& channel;
	int seq_num;
};

class RDTReceiver
{
      public:
	RDTReceiver( SimulatedChannel& channel ) : channel( channel ) {}

	bool rdt_receive( const std::string& sender_packet );

	std::string receive_packet() { return channel.receive(); }

	void send_acknowledgement( int seq_num );

      private:
	SimulatedChannel& channel;
};

void RDTSender::rdt_send( const std::pair< std::string, std::string >& data, RDTReceiver& receiver )
{
	std::string packet = make_packet( data );
	send_packet( packet );
	while( true )
	{
		bool ack_received = receiver.rdt_receive( packet );
		if( ack_received ) { break; }
		else
		{
			std::cout << "SENDER:   Timeout: Resending packet with sequence number "
			          << packet[packet.find( "sequence_number" ) + 17] << std::endl;
			send_packet( packet );
		}
	}
}

std::string RDTSender::make_packet( const std::pair< std::string, std::string >& data )
{
	std::string packet = "{\"sequence_number\":" + std::to_string( seq_num ) + ",\"data\":\"" + data.second + "\"}";
	seq_num            = 1 - seq_num; // Toggle sequence number (0 or 1)
	return packet;
}

bool RDTReceiver::rdt_receive( const std::string& sender_packet )
{
	std::string received_packet = receive_packet();
	if( !received_packet.empty() && received_packet[received_packet.find( "sequence_number" ) + 17] ==
	                                          sender_packet[sender_packet.find( "sequence_number" ) + 17] )
	{
		std::cout << "RECEIVER:   Received " << received_packet[received_packet.find( "data" ) + 7]
		          << " with sequence number " << received_packet[received_packet.find( "sequence_number" ) + 17]
		          << std::endl;
		send_acknowledgement( received_packet[received_packet.find( "sequence_number" ) + 17] - '0' );
		return true; // Acknowledgment received successfully
	}
	else
	{
		return false; // Acknowledgment not received
	}
}

void RDTReceiver::send_acknowledgement( int seq_num )
{
	std::cout << "RECEIVER:   Sending ACK" << seq_num << std::endl;
	channel.send( "{\"acknowledgement\":" + std::to_string( seq_num ) + "}" );
}

int main()
{
	srand( time( nullptr ) ); // Initialize random seed

	SimulatedChannel channel;
	RDTSender sender( channel );
	RDTReceiver receiver( channel );

	std::ifstream file( "test_rdt.txt" );
	if( file.is_open() )
	{
		std::string line;
		while( std::getline( file, line ) )
		{
			std::istringstream iss( line );
			std::pair< std::string, std::string > data;
			iss >> data.first >> std::ws;
			std::getline( iss, data.second );
			sender.rdt_send( data, receiver );
		}
		file.close();
	}
	else { std::cerr << "Unable to open file" << std::endl; }

	return 0;
}
