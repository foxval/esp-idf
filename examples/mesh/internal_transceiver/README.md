# Mesh Internal Transceiver Example

This example demonstrates how to use the mesh APIs to set up a mesh network, send and receive messages over the mesh network and etc.

Features Demonstrated

- mesh initialization

- mesh configuration

- mesh start

- mesh event handler

- root send and receive

- other nodes receive

Run `make menuconfig` to configure the mesh network channel, router SSID, router password and mesh softAP settings.

When the mesh network is established, if you happen to run this example on ESP-WROVER-KIT boards which have RGB light indicator to show you the layer devices on.
The pink reprents root; the yellow reprents layer 2; the red reprents layer 3; the blue reprents layer 4; the green reprents layer 5; the write reprents layer greater than 5.
Root continuously sends an On / Off control message to all devices in its routing table. Devices including root itself receive this message and do the On / Off.
