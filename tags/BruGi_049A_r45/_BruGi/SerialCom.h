void transmitUseACC()
{
  Serial.println(config.useACC);
}

void toggleACCOutput()
{
  int temp = atoi(sCmd.next());
  if(temp==1)
    config.accOutput = true;
  else
    config.accOutput = false;
}

void toggleDMPOutput()
{
  int temp = atoi(sCmd.next());
  if(temp==1)
    config.dmpOutput = true;
  else
    config.dmpOutput = false;
}

void setUseACC()
{
  int temp = atoi(sCmd.next());
  if(temp==1)
    config.useACC = true;
  else
    config.useACC = false;
}

void transmitRCConfig()
{
  Serial.println(config.minRCPitch);
  Serial.println(config.maxRCPitch);
  Serial.println(config.minRCRoll);
  Serial.println(config.maxRCRoll);
}

void transmitRCAbsolute()
{
  Serial.println(config.rcAbsolute);
}

void setRCGain()
{
    config.rcGain = atoi(sCmd.next());
}

void transmitRCGain()
{
  Serial.println(config.rcGain);
}

void setRCAbsolute()
{
  int temp = atoi(sCmd.next());
  if(temp==1)
  {
    config.rcAbsolute = true;
    pitchRCSetpoint = 0.0;
    rollRCSetpoint = 0.0;
  }
  else
  {
    config.rcAbsolute = false;
    pitchRCSetpoint = 0;
    rollRCSetpoint = 0;
  }
  pitchRCSpeed = 0;
  rollRCSpeed = 0;
}

void setRCConfig()
{
  config.minRCPitch = atoi(sCmd.next());
  config.maxRCPitch = atoi(sCmd.next());
  config.minRCRoll = atoi(sCmd.next());
  config.maxRCRoll = atoi(sCmd.next());
}

void transmitSensorOrientation()
{
  Serial.println(config.axisReverseZ);
  Serial.println(config.axisSwapXY);
}

void writeEEPROM()
{
  EEPROM_writeAnything(0, config); 
}

void readEEPROM()
{
  EEPROM_readAnything(0, config); 
  recalcMotorStuff();
  initPIDs();
}

void transmitActiveConfig()
{
  Serial.println(config.vers);
  Serial.println(config.gyroPitchKp);
  Serial.println(config.gyroPitchKi);
  Serial.println(config.gyroPitchKd);
  Serial.println(config.gyroRollKp);
  Serial.println(config.gyroRollKi);
  Serial.println(config.gyroRollKd);
  Serial.println(config.accComplTC);
  Serial.println(config.nPolesMotorPitch);
  Serial.println(config.nPolesMotorRoll);
  Serial.println(config.dirMotorPitch);
  Serial.println(config.dirMotorRoll);
  Serial.println(config.motorNumberPitch);
  Serial.println(config.motorNumberRoll);
  Serial.println(config.maxPWMmotorPitch);
  Serial.println(config.maxPWMmotorRoll);
}

void transmitActiveConfig2()
{
  Serial.print(F("paramCount ")); Serial.println(F("27"));
  Serial.print(F("vers ")); Serial.println(config.vers);
  Serial.print(F("gyroPitchKp ")); Serial.println(config.gyroPitchKp);
  Serial.print(F("gyroPitchKi ")); Serial.println(config.gyroPitchKi);
  Serial.print(F("gyroPitchKd ")); Serial.println(config.gyroPitchKd);
  Serial.print(F("gyroRollKp ")); Serial.println(config.gyroRollKp);
  Serial.print(F("gyroRollKi ")); Serial.println(config.gyroRollKi);
  Serial.print(F("gyroRollKd ")); Serial.println(config.gyroRollKd);
  Serial.print(F("accComplTC ")); Serial.println(config.accComplTC);
  Serial.print(F("nPolesMotorPitch ")); Serial.println(config.nPolesMotorPitch);
  Serial.print(F("nPolesMotorRoll ")); Serial.println(config.nPolesMotorRoll);
  Serial.print(F("dirMotorPitch ")); Serial.println(config.dirMotorPitch);
  Serial.print(F("dirMotorRoll ")); Serial.println(config.dirMotorRoll);
  Serial.print(F("motorNumberPitch ")); Serial.println(config.motorNumberPitch);
  Serial.print(F("motorNumberRoll ")); Serial.println(config.motorNumberRoll);
  Serial.print(F("maxPWMmotorPitch ")); Serial.println(config.maxPWMmotorPitch);
  Serial.print(F("maxPWMmotorRoll ")); Serial.println(config.maxPWMmotorRoll);
  Serial.print(F("minRCPitch ")); Serial.println(config.minRCPitch);
  Serial.print(F("maxRCPitch ")); Serial.println(config.maxRCPitch);
  Serial.print(F("minRCRoll ")); Serial.println(config.minRCRoll);
  Serial.print(F("maxRCRoll ")); Serial.println(config.maxRCRoll);
  Serial.print(F("rcGain ")); Serial.println(config.rcGain);
  Serial.print(F("rcAbsolute ")); Serial.println(config.rcAbsolute);
  Serial.print(F("accOutput ")); Serial.println(config.accOutput);
  Serial.print(F("enableGyro ")); Serial.println(config.enableGyro);
  Serial.print(F("enableACC ")); Serial.println(config.enableACC);
  Serial.print(F("axisReverseZ ")); Serial.println(config.axisReverseZ);
  Serial.print(F("axisSwapXY ")); Serial.println(config.axisSwapXY);
}


void setPitchPID()
{
  config.gyroPitchKp = atol(sCmd.next());
  config.gyroPitchKi = atol(sCmd.next());
  config.gyroPitchKd = atol(sCmd.next());
  initPIDs();
}

void setRollPID()
{
  config.gyroRollKp = atol(sCmd.next());
  config.gyroRollKi = atol(sCmd.next());
  config.gyroRollKd = atol(sCmd.next());
  initPIDs();
}

void setAccComplementaryTC()
{
  config.accComplTC = atoi(sCmd.next());
  setACCFastMode(false);
}

void setMotorPWM()
{
  config.maxPWMmotorPitch = atoi(sCmd.next());
  config.maxPWMmotorRoll = atoi(sCmd.next());
  recalcMotorStuff();
}

void setMotorParams()
{
  config.nPolesMotorPitch = atoi(sCmd.next());
  config.nPolesMotorRoll = atoi(sCmd.next());
  recalcMotorStuff();
}

void gyroRecalibrate()
{
  gyroOffsetCalibration();
  Serial.println(F("recalibration: done"));
}

void setMotorDirNo()
{
  config.dirMotorPitch = atoi(sCmd.next());
  config.dirMotorRoll = atoi(sCmd.next());
  config.motorNumberPitch = atoi(sCmd.next());
  config.motorNumberRoll = atoi(sCmd.next());
}

void setSensorOrientation()
{
  config.axisReverseZ = atoi(sCmd.next());
  config.axisSwapXY = atoi(sCmd.next());

  initSensorOrientation();
  
}

void setSensorEnable()
{
  config.enableGyro= atoi(sCmd.next());
  config.enableACC= atoi(sCmd.next());
}


void helpMe()
{
  Serial.println(F("This gives you a list of all commands with usage:"));
  Serial.println(F("Explanation in brackets(), use Integers only !"));
  Serial.println(F(""));
  Serial.println(F("WE    (Writes active config to eeprom)"));
  Serial.println(F("RE    (Restores values from eeprom to active config)"));  
  Serial.println(F("TC    (transmits all config values in eeprom save order)"));     
  Serial.println(F("TC2   (transmits all config value pairs)"));     
  Serial.println(F("SD    (Set Defaults)"));
  Serial.println(F("SP gyroPitchKp gyroPitchKi gyroPitchKd    (Set PID for Pitch)"));
  Serial.println(F("SR gyroRollKp gyroRollKi gyroRollKd    (Set PID for Roll)"));
  Serial.println(F("SA accLowPassTC   (Set LP time constant of complementary filter, sec)"));
  Serial.println(F("SF nPolesMotorPitch nPolesMotorRoll"));
  Serial.println(F("SE maxPWMmotorPitch maxPWMmotorRoll     (Used for Power limitiation on each motor 255=high, 1=low)"));
  Serial.println(F("SM dirMotorPitch dirMotorRoll motorNumberPitch motorNumberRoll"));
  Serial.println(F("SSO reverseZ swapXY (set sensor orientation)"));
  Serial.println(F("TSO   (Transmit sensor orientation)"));
  Serial.println(F("SSE enableGyro enableACC (set sensor enable)"));  
  Serial.println(F("GC    (Recalibrates the Gyro Offsets)"));
  Serial.println(F("TRC   (transmitts RC Config)"));
  Serial.println(F("SRC minRCPitch maxRCPitch minRCRoll maxRCRoll (angles -90..90)"));
  Serial.println(F("SCA rcAbsolute (1 = true, RC control is absolute; 0 = false, RC control is proportional)"));
  Serial.println(F("SRG rcGain (set RC gain)"));
  Serial.println(F("TCA   (Transmit RC control absolute or not)"));
  Serial.println(F("TRG   (Transmit RC gain)"));
  Serial.println(F("UAC useACC (1 = true, ACC; 0 = false, DMP)"));
  Serial.println(F("TAC   (Transmit ACC status)"));
  Serial.println(F("OAC accOutput (Toggle Angle output in ACC mode: 1 = true, 0 = false)"));
  Serial.println(F("ODM dmpOutput (Toggle Angle output in DMP mode: 1 = true, 0 = false)"));
  Serial.println(F("HE    (This output)"));
}

void unrecognized(const char *command) 
{
  Serial.println(F("What? type in HE for Help ..."));
}


void setSerialProtocol()
{
  // Setup callbacks for SerialCommand commands
  sCmd.addCommand("WE", writeEEPROM);   
  sCmd.addCommand("RE", readEEPROM); 
  sCmd.addCommand("TC", transmitActiveConfig);
  sCmd.addCommand("TC2", transmitActiveConfig2);
  sCmd.addCommand("SD", setDefaultParameters);   
  sCmd.addCommand("SP", setPitchPID);
  sCmd.addCommand("SR", setRollPID);
  sCmd.addCommand("SA", setAccComplementaryTC);
  sCmd.addCommand("SF", setMotorParams);
  sCmd.addCommand("SE", setMotorPWM);
  sCmd.addCommand("SM", setMotorDirNo);
  sCmd.addCommand("SSO", setSensorOrientation);
  sCmd.addCommand("TSO", transmitSensorOrientation);
  sCmd.addCommand("SSE", setSensorEnable);
  sCmd.addCommand("GC", gyroRecalibrate);
  sCmd.addCommand("TRC", transmitRCConfig);
  sCmd.addCommand("SRC", setRCConfig);
  sCmd.addCommand("SRG", setRCGain);
  sCmd.addCommand("SCA", setRCAbsolute);
  sCmd.addCommand("TCA", transmitRCAbsolute);
  sCmd.addCommand("TRG", transmitRCGain);
  sCmd.addCommand("UAC", setUseACC);
  sCmd.addCommand("TAC", transmitUseACC);
  sCmd.addCommand("OAC", toggleACCOutput);
  sCmd.addCommand("ODM", toggleDMPOutput);
  sCmd.addCommand("HE", helpMe);
  sCmd.setDefaultHandler(unrecognized);      // Handler for command that isn't matched  (says "What?")
}