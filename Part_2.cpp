#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
using namespace std;

class CongestionControl
{
      public:
	CongestionControl( double loss_probability, int slow_start_threshold )
	    : _congestion_window( 1 ), loss_probability_( loss_probability ),
	      slow_start_threshold_( slow_start_threshold )
	{
		// Seed for random number generation
		srand( static_cast< unsigned >( time( 0 ) ) );
	}

	void simulate_transmission( int num_packets, string _application_message )
	{
		int i    = 1;
		int flag = 0;
		while( i <= num_packets && slow_start_threshold_ > 0 )
		{
			if( slow_start_threshold_ < _congestion_window )
			{
				cout << "Since, Slow Start Threshold > Congestion Window, STOPPING ALGORITHM \n";
				break;
			}

			if( flag == 0 )
			{
				// Slow Start phase
				if( _congestion_window * 2 <= slow_start_threshold_ )
				{
					cout << ":::::::::: Slow Start Phase - 1 ::::::::::\n";
					cout << "Congestion Window is : " << _congestion_window << endl;
					cout << "Sending " << _congestion_window << " packets. \n" << endl;
					for( int j = 1; ( j <= _congestion_window ) && ( i < num_packets + 1 );
					     ++j, i++ )
					{
						cout << "Packet " << i << "\n";
						string data( 1, _application_message[i - 1] );
						send_data( data );
						data          = data + " : ";
						string packet = make_packet( data + to_string( 1 ) );
						send_packet( packet );
						receive_ack();
					}
					_congestion_window *= 2;
				}
				else if( _congestion_window * 2 > slow_start_threshold_ )
				{
					cout << ":::::::::: Slow Start Phase - 2 ::::::::::\n";
					cout << "Congestion Window is : " << _congestion_window << endl;
					cout << "Slow Start Threshold is : " << slow_start_threshold_ << endl;
					cout << "Sending " << slow_start_threshold_ - _congestion_window + 1
					     << " packets. \n"
					     << endl;
					for( int j = 1; j <= ( slow_start_threshold_ - _congestion_window + 1 ) &&
					                ( i < num_packets + 1 );
					     ++j, i++ )
					{
						cout << "Packet " << i << "\n";
						string data( 1, _application_message[i - 1] );
						send_data( data );
						data          = data + " : ";
						string packet = make_packet( data + to_string( 1 ) );
						send_packet( packet );
						receive_ack();
						flag = 1;
					}
				}
			}
			else
			{
				// AIMD phase
				cout << "XXXXXXXXXX AIMD XXXXXXXXXX\n";
				while( ( rand() % 100 > loss_probability_ * 100 ) && ( i < 101 ) )
				{
					cout << "----------------------------------\n";
					cout << "Congestion Window is : " << _congestion_window << endl;
					cout << "Linear Increase Phase \n";
					// Here I have to linearly increase the MSS (which means the congestion window
					// size).
					_congestion_window += 1;
					cout << "Congestion Window is : " << _congestion_window << endl;
					for( int j = 1; j <= _congestion_window && i < ( num_packets + 1 ); ++j, i++ )
					{
						cout << "Packet " << i << "\n";
						string data( 1, _application_message[i - 1] );
						send_data( data );
						data          = data + " : ";
						string packet = make_packet( data + to_string( 1 ) );
						send_packet( packet );
						receive_ack();
					}
				}

				if( i == num_packets + 1 )
				{
					cout << "Since, All Packets trasmitted successfully, STOPPING ALGORITHM \n";
					break;
				}
				else
				{ // Packet loss
					cout << "(Packet Loss) " << endl;
					slow_start_threshold_ = _congestion_window / 2;
					cout << "New Slow Start Threshold is : " << slow_start_threshold_ << endl;
					_congestion_window = 1;
					cout << "New Congestion Window is : " << _congestion_window << endl;

					flag = 0;
				}
			}
		}
	}

	void send_data( const string& data )
	{
		// Implementation for sending data
		cout << "Sending Data : " << data << endl;
	}

	void send_packet( const string& packet )
	{
		// Send packet over the network
		// Implementation for sending the packet over the network
		cout << "Sending Packet along with Data and Size : " << packet << endl;
	}

	string make_packet( const string& data )
	{
		// Construct packet with data and size
		// Implementation for creating a packet
		return data;
	}

	void receive_ack()
	{
		// Receive acknowledgement from the receiver
		// Implementation for receiving an acknowledgement
		cout << "Received Acknowledgment. \n" << endl;
	}

      private:
	int _congestion_window;
	int packet_size;
	double loss_probability_;
	int slow_start_threshold_;
};

int main()
{
	string application_message =
	          "In the heart of a bustling city, where the rhythmic pulse of urban life never falters, a small cafe "
	          "stands as a haven for those seeking solace amid the chaos. With its warm ambiance and aromatic "
	          "coffee wafting through the air, it becomes a sanctuary for dreamers, writers, and lovers of quiet "
	          "moments. The walls adorned with local art tell stories of a community's vibrant tapestry. Outside, "
	          "the cityscape hums with energy, while inside, conversations ebb and flow like the tide. In this "
	          "eclectic space, each cup of coffee holds the promise of inspiration, and every shared smile becomes "
	          "a chapter in the collective novel of life.";

	// Create CongestionControl object with loss probability of 0.1 and slow start threshold of 16
	CongestionControl congestion_control( 0.3, 20 );

	// Simulate the transmission of 100 data packets
	congestion_control.simulate_transmission( 100, application_message );

	return 0;
}
