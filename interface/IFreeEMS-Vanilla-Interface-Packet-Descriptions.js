{
	/* A formal definition of :		*/
	/* - What data is available		*/
	/* - How it can be accessed		*/
	/* - How it is structured		*/
	/* - How it to interpret it		*/
    "FreeEMSInterfaceDataMap": {
		/* A four part interface versioning scheme consisting of :				*/
		/* - Unique Identifier		Same across all versions of a given fork	*/
		/* - Major Version			Significant jumps in functionality			*/
		/* - Minor Version			Minor features or significant fixes			*/
		/* - Revision Number			Initial dev and minor fixes only			*/
        "InterfaceVersionUniqueIdentifier":	"IFreeEMS Vanilla",
        "InterfaceVersionUniqueMajor":		0,
        "InterfaceVersionUniqueMinor":		0,
        "InterfaceVersionUniqueRevision":	1,
		"Packets": {
			// TODO is this list required or desired? I suspect not, but as a double check maybe (ensure the intended blocks are all defined) ?
			"BlockListByName": ["VE Table Main", "VE Table Secondary", "VE Table Tertiary", "Lambda Table", "etc"],
			"BlockDefinition": {
				"LocationID": 0,
	            "DisplayName": "VE Table Main",
				"Description": "The main volumetric efficiency table as used for normal fuel injection calculations",
				"SizeInBytes": 1024,
				"Chunks": {
	                "Chunk": {
						"PayloadIDs": [6, 8, 20, 24, 53],
						"LocationID": null,
	                    "DisplayName": "VE Table Main",
						"SizeInBytes": 1024,
						"OffsetInBytes": 0,
						"ReplyPacketAttributes": {
							"PacketAttribute": {
								"Name": "Maximum RPM Axis Length",
								"Type": "Unsigned Short",
								"Length": 1,
								"LengthInBytes": 2,
								"OffsetInBytes": 0
							},
							"PacketAttribute": {
								"Name": "Maximum Load Axis Length",
								"Type": "Unsigned Short",
								"Length": 1,
								"LengthInBytes": 2,
								"OffsetInBytes": 2
							},
							"PacketAttribute": {
								"Name": "Maximum Table Length",
								"Type": "Unsigned Short",
								"Length": 1,
								"LengthInBytes": 2,
								"OffsetInBytes": 4
							},
							"PacketAttribute": {
								"Name": "VE Table Main",
								"Type": "Structure",
								"Length": 1024,
								"LengthInBytes": 1024,
								"OffsetInBytes": 6
							}
						},
						"Structure": {
							"Element": {
								"Name": "RPM Axis Length",
								"Type": "Unsigned Short",
								"Length": 1,
								"LengthInBytes": 2,
								"OffsetInBytes": 0
							},
							"Element": {
								"Name": "Load Axis Length",
								"Type": "Unsigned Short",
								"Length": 1,
								"LengthInBytes": 2,
								"OffsetInBytes": 2
							},							
							"Element": {
								"Name": "RPM Axis",
								"Type": "Unsigned Short Array",
								"Length": 27,
								"LengthInBytes": 54,
								"OffsetInBytes": 4
							},							
							"Element": {
								"Name": "Load Axis",
								"Type": "Unsigned Short Array",
								"Length": 21,
								"LengthInBytes": 42,
								"OffsetInBytes": 58
							},							
							"Element": {
								"Name": "Table",
								"Type": "Unsigned Short Array",
								"Length": 462,
								"LengthInBytes": 924,
								"OffsetInBytes": 100
							}
						}
	                }
	            }
			}
        }
    }
}
