{
	"FreeEMSErrorCodes": [
		/* Unconfigured options */
		{"IAT_NOT_CONFIGURED_CODE":				"0x1000"},
		{"CHT_NOT_CONFIGURED_CODE":				"0x1001"},
		{"TPS_NOT_CONFIGURED_CODE":				"0x1002"},
		{"EGO_NOT_CONFIGURED_CODE":				"0x1003"},
		{"BRV_NOT_CONFIGURED_CODE":				"0x1004"},
		{"MAP_NOT_CONFIGURED_CODE":				"0x1005"},
		{"AAP_NOT_CONFIGURED_CODE":				"0x1006"},
		{"MAT_NOT_CONFIGURED_CODE":				"0x1007"},
		{"EGO2_NOT_CONFIGURED_CODE":			"0x1008"},
		{"IAP_NOT_CONFIGURED_CODE":				"0x1009"},
		{"LOAD_NOT_CONFIGURED_CODE":			"0x100A"},
		{"AIRFLOW_NOT_CONFIGURED_CODE":			"0x100B"},
		{"BPW_NOT_CONFIGURED_CODE":				"0x100C"},
		/* Badly configured options */
		{"VE_TABLE_MAIN_LOAD_LENGTH_TOO_LONG":	"0x2000"},
		{"VE_TABLE_MAIN_RPM_LENGTH_TOO_LONG":	"0x2001"},
		{"VE_TABLE_MAIN_MAIN_LENGTH_TOO_LONG":	"0x2002"},
		{"BRV_MAX_TOO_LARGE":					"0x2003"},
		/* Flash burning error codes */
		{"sizeNotMultipleOfSectorSize":			"0x3000"},
		{"addressNotSectorAligned":				"0x3001"},
		{"addressNotWordAligned":				"0x3002"},
		{"flashEraseFailed":					"0x3003"},
		{"flashAccessError":					"0x3004"},
		{"flashProtectionError":				"0x3005"},
		/* Communications error codes */
		{"unimplementedFunction":				"0x4000"},
		{"packetChecksumMismatch":				"0x4001"},
		{"sourceAddressIsBroadcast":			"0x4002"},
		{"sourceAddressIsDuplicate":			"0x4003"},
		{"payloadLengthTypeMismatch":			"0x4004"},
		{"payloadLengthHeaderMismatch":			"0x4005"},
		{"unrecognisedProtocolPayloadID":		"0x4006"},
		{"unrecognisedFirmwarePayloadID":		"0x4007"},
		{"invalidProtocolPayloadID":			"0x4008"},
		{"invalidFirmwarePayloadID":			"0x4009"},
		{"invalidMemoryActionForID":			"0x400A"},
		/* Main table validation errors */
		{"invalidMainTableRPMOrder":			"0x5000"},
		{"invalidMainTableRPMIndex":			"0x5001"},
		{"invalidMainTableRPMLength":			"0x5002"},
		{"invalidMainTableLoadOrder":			"0x5003"},
		{"invalidMainTableLoadIndex":			"0x5004"},
		{"invalidMainTableLoadLength":			"0x5005"},
		{"invalidMainTableMainLength":			"0x5006"},
		/* 2d unsigned char table validation errors */
		{"invalidTwoDTableAxisOrder":			"0x5010"}
		]
}