# NC501-Networking-Communication
This repository contains homeworks and coding assignments done as part of NC 501 - Networking &amp; Communication

Q1.) Reliable Data Transfer (RDT)
Implement a simple stop-and-wait Reliable Data Transfer 2.2 protocol. A simulated data channel can be used for data transfer which has an associated packet
loss probability as given in the baseline.py file. Implementation should cover sending data and displaying the received data, receiving ACK for successful
transmission, and retransmission in case the packet is not received/ suitable ACK is not received. Print statements must be given as mentioned in the baseline.py
file and the output must be documented in the report.

Q2.) Congestion Control
Implement a simple congestion control algorithm, such as Additive Increase Multiplicative Decrease (AIMD), to handle congestion in a network. Do print the 
congestion window size in order to verify the working of AIMD. To introduce congestion into the network, you can add ‘loss probability’ while sending and
receiving packets. Try different variations of the slow start threshold to see what works best.

Q3.) Link State Algorithm
Implement the Link State Algorithm to determine the shortest path between nodes in a
network. Your implementation should include the following functions:

a) build_topology(): This function constructs the network topology by reading the connectivity information from a file.
b) calculate_shortest_path(source, destination): This function calculates the shortest path between the given source and destination nodes using the Link State Algorithm.
