import random

class SimulatedChannel:
    def __init__(self, loss_rate=0.3):
        self.loss_rate = loss_rate
        self.packet=None
    
    def send(self, packet):
        if random.random() >= self.loss_rate:
            self.packet = packet
        else:
            self.packet=None
    
    def receive(self):
        if random.random() >= self.loss_rate:
            return self.packet
        return None


class RDTSender:
    def __init__(self, channel):
        pass

    def rdt_send(self, data, receiver):
        # Send the data over the Simulated Channel
        # print "Sending <data item> with sequence number<x>"
        receiver.rdt_receive() # call the receiver function to read the data from the channel and add suitable ACK to the channel
        # Depending on the ACK received retransmit data if required
        # print "received ACK <0/1>/None. Transmission successful/Unsuccessful"
        pass

    def send_packet(self, packet):
        # Send packet over the network
        pass

    def make_packet(self, data):
        # Construct packet with sequence number and data
        pass


class RDTReceiver:
    def __init__(self, channel):
        pass

    def rdt_receive(self):
        #Called by sender, receives packet from channel and sends suitable ACK back to channel 
        #print Received <data item> with <content> and sequence number<x>/ Transfer unsuccessful
        #print Sending ACK<0/1>
        pass

    def receive_packet(self):
        # Receive packet from the network
        pass

    def send_acknowledgement(self, seq_num):
        # Send acknowledgement to the sender
        pass


class CongestionControl:
    def __init__(self):
        pass

    def send_data(self, data):
        pass

    def send_packet(self, packet):
        # Send packet over the network
        pass

    def make_packet(self, data):
        # Construct packet with data and size
        pass

    def receive_ack(self):
        # Receive acknowledgement from the receiver
        pass


class LinkStateAlgorithm:
    def __init__(self):
        pass

    def build_topology(self, file_name):
        # Read from the testfile each link in the form (source, destination, cost) and build the topology
        pass

    def add_link(self, source, destination, cost):
        #Used by the above function to add a link
        pass

    def calculate_shortest_path(self, source, destination):
        # Find the shortest path from A to I. For the given testcase, the output must be A -> B -> D -> F -> H -> I
        pass