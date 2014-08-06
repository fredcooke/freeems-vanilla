#elif CONFIG == M2CUPCAR_ID
		perCylinderVolume:  CYLINDER_VOLUME(500),
		injectorFlow:       CC_PER_MINUTE(550), // RX7 "550" flowed at 580cc

#elif CONFIG == M2CUPCAR_ID // M2cupcar Mazda FE3 MX5/Miata, stock sensors, CAS and Coils
		anglesOfTDC: {ANGLE(0), ANGLE(180), ANGLE(360), ANGLE(540), ANGLE(0), ANGLE(180), ANGLE(360), ANGLE(540)},
		outputEventPinNumbers:       {0,1,0,1,2,3,2,3}, // Wasted spark and semi-sequential
		schedulingConfigurationBits: {0,0,0,0,1,1,1,1}, // First four ignition, last four fuel
		decoderEngineOffset:              ANGLE(90.00), // FE-DOHC, 4and1 CAS approximately centre
		numberOfConfiguredOutputEvents:              8, // 
		numberOfInjectionsPerEngineCycle:            2  // semi-sequential

#elif CONFIG == M2CUPCAR_ID
			disableThreshold:  RPM(7100),
			reenableThreshold: RPM(7050)
#elif CONFIG == M2CUPCAR_ID
			disableThreshold:  RPM(7100),
			reenableThreshold: RPM(7000)
