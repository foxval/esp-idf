# Mesh Internal Transceiver Example

This example demonstrates how to use the mesh APIs to set up a mesh network, send and receive messages over the mesh network and etc.

Features Demonstrated

- mesh initialization

- mesh configuration

- mesh start

- mesh event handler

- root send and receive

- other nodes receive

Application Instructions

1. Modify the MESH_ROUTER_CHANNEL / MESH_ROUTER_SSID / MESH_ROUTER_PASSWD router configurations in the mesh_config.h header file to match your router.
If your router is hidden, MESH_ROUTER_BSSID is mandatory.

2. Modify the MESH_MAP_PASSWD / MESH_MAP_CONNECTIONS / MESH_MAP_AUTHMODE mesh softAP configurations in the mesh_config.h header file to match your requirements.

3. Connect Linux PC to serial port of ESP - WROVER - KIT boards, then run run.sh script to realize make and parallel download. After the download is completed,
minicoms will be opened automatically showing you the log. Get more info from [run.sh].
If you are not using ESP - WROVER - KIT boards, try normal ways to realize make and download.

    When the mesh network is established, ESP - WROVER - KIT boards have RGB light indicator to show you the layer devices on. The pink reprents root;
the yellow reprents layer 2; the red reprents layer 3; the blue reprents layer 4; the green reprents layer 5; the write reprents layer greater than 5.
Root continuously sends an On / Off control message to all devices in its routing table. Devices including root self receive this message and do the On / Off.
