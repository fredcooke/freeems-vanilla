/* A formal definition of how the data objects are structured and how to interpret them */
{ "$schema":{"$ref":"http://www.diyefi.org/InterfaceStructureDescriptions.JSONSchema"},
	/* The four part interface versioning scheme */
	"InterfaceVersionUniqueIdentifier":	"IFreeEMS Vanilla",
	"InterfaceVersionUniqueMajor":		0,
	"InterfaceVersionUniqueMinor":		0,
	"InterfaceVersionUniqueRevision":	1,
	/* For megasquirt use the numeric version is not relevant. */
	"Primitives": [
		{"Key": "Character",		"Length": 1, 		"LabelCount": 1,	"Name": "Character"},
		{"Key": "BitFieldByte",		"Length": 1,		"LabelCount": 8,	"Name": "Boolean Array[8]"},
		{"Key": "BitFieldWord",		"Length": 2,		"LabelCount": 16,	"Name": "Boolean Array[16]"},
		{"Key": "BitFieldLong",		"Length": 4,		"LabelCount": 32,	"Name": "Boolean Array[32]"},
		{"Key": "SignedByte",		"Length": 1, 		"LabelCount": 1,	"Name": "Integer Signed Char"},
		{"Key": "SignedWord",		"Length": 2, 		"LabelCount": 1,	"Name": "Integer Signed Short"},
		{"Key": "SignedLong",		"Length": 4, 		"LabelCount": 1,	"Name": "Integer Signed Long"},
		{"Key": "UnsignedByte",		"Length": 1, 		"LabelCount": 1,	"Name": "Integer Unsigned Char"},
		{"Key": "UnsignedWord",		"Length": 2, 		"LabelCount": 1,	"Name": "Integer Unsigned Short"},
		{"Key": "UnsignedLong",		"Length": 4, 		"LabelCount": 1,	"Name": "Integer Unsigned Long"}
	],
	/* &&&&&&&&&&&&&& Transformation of the raw data stream. &&&&&&&&&&&&&& */
	/*																		*/
	/* Character is just that, an unsigned byte interpreted as per the ISO	*/
	/* standard character encoding for the latin character set, ISO-8859-1.	*/
	/*																		*/
	/* Bitfields are normal unsigned integers interpreted as a series of	*/
	/* bits representing one boolean flag each. As per the C standard zero	*/
	/* is considered 'false' and 1 considered 'true'.						*/
	/*																		*/
	/* Integer types are either signed or unsigned, where the signed		*/
	/* representation is the standard two's complement format.				*/
	/*																		*/
	/* The data transmitted by FreeEMS is sent in as a structured binary	*/
	/* stream in the form of sequential raw values. While some of these can	*/
	/* be read directly at face	value simply by interpretting them as their	*/
	/* basic data type, most require transformation before they can be used	*/
	/* to understand the state of engine and other operating parameters.	*/
	/*																		*/
	/* The first stage is to interpret a piece of the binary stream as a	*/
	/* raw value. There are two examples are given below, one signed and	*/
	/* the other unsigned.													*/
	/*																		*/
	/* If the data type is SignedByte and a single byte is received, 0xAC	*/
	/* it must be converted from two's complement :							*/
	/*																		*/
	/* 0xAC - 1 = 0xAB														*/
	/* 0xAB ^ 0xFF = 0x54													*/
	/* 0x54 * -1 = -84														*/
	/*																		*/
	/* If the data type is UnsignedWord and two bytes are received, 0x76	*/
	/* first and 0x3F second giving us 0x01CE then :						*/
	/*																		*/
	/* 0x763F = 30271														*/
	/*																		*/
	/* Now suppose this is supposed to be a Lambda value, clearly it isn't	*/																		*/
	/* correct as it stands.												*/
	/*																		*/
	/* A human readable value can be calculated using the offset and ratio	*/
	/* in the following way :												*/
	/*																		*/
	/* ratio = between the raw value after offset is applied human value	*/
	/* offset = between the value sent and one that is scalable				*/
	/* raw value = numeric value of the data interpretted as its basic type	*/
	/* human value = a meaningful figure representing the quantity involved	*/
	/*																		*/
	/* [human value] = ( [raw value] + [offset] ) * [ratio]					*/
	/*																		*/
	/* Using our previous example we can assume it was a temperature with	*/
	/* the following attributes :											*/
	/*																		*/
	/* unit = °C															*/
	/* ratio = 0.01															*/
	/* offset = -27315														*/
	/* raw value = 30271													*/
	/*																		*/
	/* human value = (30271 - 27315) * 0.01									*/
	/* human value = 2956 * 0.01											*/
	/* human value = 29.56													*/
	/*																		*/
	/* temperature = 29.56 °C												*/
	/*																		*/
	/* Twenty nine and a half degrees celcius is fairly typical for a turbo	*/
	/* application assuming a reasonable ambient air temperature and fairly	*/
	/* efficient intercooler setup.											*/
	"Structures": [
		{
			"Key": "MainTable",
			"Name": "Main Table",
			"Description": "Large variable size, three dimensional table (typically RPM, Load, VE/Lambda/Timing/etc).",
			"SizeInBytes": 1024,
			"Components": [
				{
					"Name": "RPM Axis Length",
					"Description": "How many RPM axis cells this table has.",
					"Primitive": "UnsignedShort",
					"Unit": "Cells",
					"Count": 1
				},
				{
					"Name": "Load Axis Length",
					"Description": "How many Load axis cells this table has.",
					"Primitive": "UnsignedShort",
					"Unit": "Cells",
					"Count": 1
				},
				{
					"Name": "RPM Axis",
					"Description": "The RPM axis values.",
					"Primitive": "UnsignedShort",
					"TransformDivisor": 2, /* 0 - 32767.5, 0.5 */
					"Count": 27
					"Unit": "RPM",
				},
				{
					"Name": "Load Axis",
					"Description": "The Load axis values.",
					"Primitive": "UnsignedShort",
					"TransformDivisor": 100, /* 0 - 655.35, 0.01 */
					"Count": 21
					"Unit": "%",
				},
				{
					"Name": "VE Table",
					"Description": "The Volumetric Efficiency table values.",
					"Primitive": "UnsignedShort",
					"TransformDivisor": 500, /* 0 - 131.07, 0.002 */
					"Count": 462,
					"Unit": "%",
				}
		    ]
		},
		{
			"Key": "LambdaTable",
			"Name": "Lambda Table",
			"Description": "Large variable size, three dimensional table (RPM, Load, Lambda).",
			"SizeInBytes": 1024,
			"Components": [
				{
					"Name": "RPM Axis Length",
					"Description": "How many RPM axis cells this table has.",
					"Primitive": "UnsignedShort",
					"Unit": "Cells",
					"Count": 1
				},
				{
					"Name": "Load Axis Length",
					"Description": "How many Load axis cells this table has.",
					"Primitive": "UnsignedShort",
					"Unit": "Cells",
					"Count": 1
				},							
				{
					"Name": "RPM Axis",
					"Description": "The RPM axis values.",
					"Primitive": "UnsignedShort",
					"TransformDivisor": 2, /* 0 - 32767.5, 0.5 */
	    	    	"Count": 27
	    	    	"Unit": "RPM",
	    	    },							
	    	    {
	    	    	"Name": "Load Axis",
	    	    	"Description": "The Load axis values.",
	    	    	"Primitive": "UnsignedShort",
	    	    	"TransformDivisor": 100, /* 0 - 655.35, 0.01 */
	    	    	"Count": 21
	    	    	"Unit": "%",
	    	    },							
	    	    {
	    	    	"Name": "Lambda Table",
	    	    	"Description": "The Lambda table values.",
	    	    	"Primitive": "UnsignedShort",
	    	    	"TransformDivisor": 32768, /* 0 - 2.0, 0.00003 */
	    	    	"Count": 462,
	    	    	"Unit": "%",
	    	    }
	    	]
		}
    ]
}
