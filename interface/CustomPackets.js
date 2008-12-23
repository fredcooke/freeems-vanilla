{
	/* For optional stuff, if flags say yes and not there, exception, if flags say no and is there, ignore */
	/* If length requested, generate it, it will not be provided */
	"FreeEMSCustomPackets": {
		{ /* EXAMPLE PACKET ONLY */
			/* compulsory */
			"MenuName":	"ExamplePacketDoesNothing", /* display as is */
			"Flags":		"0xAB", /* hex */
			"PayloadID":	65534,  /* dec */
			"Payload": [0, "0xaa", 85, 23, 0, "0xFF", 255], /* mixed */

			/* optional, both are always decimal */
			"Ack": 255,
			"Addresses": {"Source": 236, "Destination": 183}
		},
		{
			"MenuName":	"EraseAllSectorsInLoop",
			"Flags":		"0x00",
			"PayloadID":	10,
			"Payload": []
		},
		{
			"MenuName":	"WriteAllSectorsInLoop",
			"Flags":		"0x00",
			"PayloadID":	12,
			"Payload": []
		}
	}
}
