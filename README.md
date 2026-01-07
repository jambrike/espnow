So this is the code for a hardware project for hackathon in vienna called midnight with hackclub

It is based on the game red light green light from squid game where when it is red light you can have to stop and when it is green light you can go. if u move during red light then
your esp pack your wearing will start flashing showing that you have been killed

The cpp is arduino code for esp32s that speak over esp-now the transmitter sends the request that you have been hit to the other esp that you have been wearing and then it starts flashing.
the node server that is being ran locally takes footage from webcam and using tensor flow lightning model and uses the average displacement of the points on your body during the red stage to choose if you have moved enough to be noticed.

to run on your own:
you have to put in your own mac address of your reciever esp into the transmitter
then put in the port that your esp is connected on this is possible to see through the arduino application
then run the server has to be locally

if from midnight then vote for us
