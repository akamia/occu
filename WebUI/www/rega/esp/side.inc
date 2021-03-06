<%
  string hm_ouled16 =  "HM-OU-LED16";
  string hm_oucfm = "HM-OU-CFM-Pl";
  string hm_oucmpcb = "HM-OU-CM-PCB";
  string hm_partyDialog = "HM-CC-RT-DN HM-TC-IT-WM-W-EU HM-CC-VG-1";
  string hm_statusDisplay = "HM-Dis-WM55";
  string hm_rgbw_controller = "HM-LC-RGBW-WM";

  string excludePARTY = "PARTY_";
  string includePARTY = "PARTY_MODE_SUBMIT";

  integer iDP = oSD.DestinationDP();
  integer iCH = oSD.DestinationChannel();
  integer iP = oSD.DestinationParam();
  integer iV = oSD.DestinationValue();
  integer iVT = oSD.DestinationValueType();
  integer iVP = oSD.DestinationValueParam();
  integer iVPT = oSD.DestinationValueParamType();
  string sSelected = "";
  Write( '<select class="SelectBox" onchange="DestinationParamSelectChange(this.selectedIndex,'#oSD.ID()#');">' );
  if( iP == ivtEmpty ) { sSelected = " selected"; } else { sSelected = ""; }
  Write( '<option'#sSelected#'></option>' );
  if( iP == ivtObjectId ) { sSelected = " selected"; } else { sSelected = ""; }
  !Write( '<option'#sSelected#'>Ger&auml;teauswahl</option>' );
  Write( '<option'#sSelected#'>${ruleActivitySelectDeviceList}</option>' );
  if( iP == ivtSystemId ) { sSelected = " selected"; } else { sSelected = ""; }
  !Write( '<option'#sSelected#'>Systemzustand</option>' );
  Write( '<option'#sSelected#'>${ruleActivitySelectSystemState}</option>' );
  if( iP == ivtString ) { sSelected = " selected"; } else { sSelected = ""; }
  !Write( '<option'#sSelected#'>Skript</option>' );
  Write( '<option'#sSelected#'>${ruleActivitySelectScript}</option>' );
  Write( '</select>' );
  
  if( (iP == ivtObjectId) || ( iP == ivtSystemId ) )
  {
    if( iP == ivtObjectId )
    {
      object oCH = dom.GetObject( iCH );
      if( oCH )
      {
      Write( ' <b class="CLASS02400" onclick="ShowDestinationChannelChooser2('#oSD.ID()#');">'#oCH.Name()#'</b> ' );
      }
      else
      {
        !Write( ' <input type="button" class="SelectBox" value="Ger&auml;teauswahl" onclick="ShowDestinationChannelChooser2('#oSD.ID()#');" /> ' );
        Write( ' <input type="button" class="SelectBox" value="Ger&auml;teauswahl" name="ruleActivityButtonDeviceList" onclick="ShowDestinationChannelChooser2('#oSD.ID()#');" /> ' );
      }
    }
    if( iP == ivtSystemId )
    {
      object oDP = dom.GetObject( iDP );
      if( oDP )
      {
        Write( ' <b class="CLASS02400" onclick="ShowDestinationSysVarChooser('#oSD.ID()#');">'#oDP.Name()#'</b> ' );
      }
      else
      {
        Write( ' <input type="button" class="SelectBox" value="Systemvariablenauswahl" name="ruleActivityButtonSystemState" onclick="ShowDestinationSysVarChooser('#oSD.ID()#');" /> ' );
      }
    }
  }
  if( iP == ivtString )
  {
    if( iVT == ivtString )
    {
      string sScript = iV.Substr(0,60);
      sScript = sScript#"...";
      Write( ' <b class="CLASS02400" onclick="EditScript('#oSD.ID()#');">'#sScript#'</b> ' );
    }
    else
    {
      Write( ' <input type="button" class="SelectBox" value="Skript erstellen" name="ruleActivityButtonCreateScript" onclick="EditScript('#oSD.ID()#');" /> ' );
    }
  }
  if( (iP==ivtString) || (iP==ivtObjectId) || (iP==ivtSystemId) )
  {
    Write( '<select onchange="iseSingleDestination.SetValueParamType('#oSD.ID()#',this.value);" class="SelectBox">' );
    string sSelected = "";
    if( iVPT == ivtEmpty ) { sSelected = " selected"; } else { sSelected = ""; }
    !Write( '<option value="'#ivtEmpty#'"'#sSelected#'>sofort</option>' );
    Write( '<option value="'#ivtEmpty#'"'#sSelected#'>${ruleActivitySelectImmediately}</option>' );
    if( iVPT == ivtDelay ) { sSelected = " selected"; } else { sSelected = ""; }
    !Write( '<option value="'#ivtDelay#'"'#sSelected#'>verzögert um</option>' );
    Write( '<option value="'#ivtDelay#'"'#sSelected#'>${ruleActivitySelectDelayed}</option>' );
    Write( '</select>' );
    if( iVPT == ivtDelay )
    {
      integer iHours = iVP.ToString().Substr(11,2).ToInteger();
      integer iMinutes = iVP.ToString().Substr(14,2).ToInteger();
      integer iSeconds = iVP.ToString().Substr(17,2).ToInteger();
      integer iVal = 0;
      if( iSeconds > 0 ) { iVal = iSeconds + (iMinutes*60) + (iHours*3600); iMinutes = 0; iHours = 0; }
      if( iMinutes > 0 ) { iVal = iMinutes + (iHours*60); iHours = 0; }
      if( iHours > 0 ) { iVal = iHours; }
      Write( ' <input type="text" size="10" class="SelectBox" value="'#iVal#'" id="delay'#oSD.ID()#'" onchange="SetDelay('#oSD.ID()#',this.value);" /> ' );
      Write( '<select id="tm'#oSD.ID()#'unit" class="SelectBox" onchange="ChangeDelayUnit('#oSD.ID()#');">' );
      string sSelected = "";
      if( iSeconds > 0 ) { sSelected = " selected"; } else { sSelected = ""; }
      !Write( '<option'#sSelected#'>Sekunden</option>' );
      Write( '<option'#sSelected#'>${ruleActivitySelectSeconds}</option>' );
      if( iMinutes > 0 ) { sSelected = " selected"; } else { sSelected = ""; }
      !Write( '<option'#sSelected#'>Minuten</option>' );
      Write( '<option'#sSelected#'>${ruleActivitySelectMinutes}</option>' );
      if( iHours > 0 ) { sSelected = " selected"; } else { sSelected = ""; }
      !Write( '<option'#sSelected#'>Stunden</option>' );
      Write( '<option'#sSelected#'>${ruleActivitySelectHours}</option>' );
      Write( '</select>' );
    }
  }
  if( iP == ivtObjectId )
  {
    object oCH = dom.GetObject( iCH );
    if( oCH )
    {
      Write( ' <select onchange="SetDestinationDPSelectChange('#oSD.ID()#',this);" class="SelectBox">' );
      boolean bFound = false;
      integer iFirstID = ID_ERROR;
      string sDP;
      foreach( sDP, oCH.DPs().EnumEnabledVisibleIDs() )
      {
        object oDP = dom.GetObject( sDP );
        if( oDP )
        {
          boolean bSetDefault = false;
          if( !iV )
          {
            if( iDP == ID_ERROR )
            {
              bSetDefault = true;
            }
          }
          if( oDP.Operations() & OPERATION_WRITE )
          {
            integer iDPvt = oDP.ValueType();
            integer iDPst = oDP.ValueSubType();
            if( iFirstID == ID_ERROR ) { iFirstID = oDP.ID(); }
            string sSelected = "";
            if( oDP.ID() == iDP ) { sSelected = " selected"; bFound = true; } else { sSelected = ""; }
            string sIdx = "";
            if( (iDPvt == ivtInteger) && (iDPst == istEnum) )
            {
              integer iVLCount = web.webGetValueListCount( oDP.ValueList() );
              iVLCount = iVLCount - 1;
              string sVLKey;
              foreach( sVLKey, system.GenerateEnum(0,iVLCount) )
              {
                string sVLValue = web.webGetValueFromList( oDP.ValueList(), sVLKey );
                if( sVLValue.Length() )
                {
                  if( (oDP.ID() == iDP) && (iV == sVLKey) ) { sSelected = " selected"; } else { sSelected = ""; }
                  Write( '<option value="'#oDP.ID()#':'#sVLKey#'"'#sSelected#'>' );
                  string sValue = oDP.Name()#": "#sVLValue;
                  if( (!oDP.IsTypeOf(OT_VARDP)) && (!oDP.IsTypeOf(OT_ALARMDP)) )
                  {
                    string sLongKey = oCH.ChnLabel()#"|"#oDP.HSSID()#"="#sVLValue;
                    string sShortKey = oDP.HSSID()#"="#sVLValue;
                    sValue = web.webKeyFromStringTable(sLongKey);
                    if( !sValue.Length() )
                    {
                      sValue = web.webKeyFromStringTable(sShortKey);
                      if( !sValue.Length() )
                      {
                        sValue = sShortKey;
                      }
                    }
                  }
                  Write( sValue );
                  Write( '</option>' );
                }
              }
            }
            else
            {
              if( (iDPvt == ivtBinary) && (iDPst != istAction) )
              {
                if( (oDP.ID() == iDP) && (iV == 1) ) { sSelected = " selected"; } else { sSelected = ""; }
                Write( '<option value="'#oDP.ID()#':1"'#sSelected#'>' );
                string sValue = oDP.Name()#": "#oDP.ValueName1();
                if( (!oDP.IsTypeOf(OT_VARDP)) && (!oDP.IsTypeOf(OT_ALARMDP)) )
                {
                  string sLongKey = oCH.ChnLabel()#"|"#oDP.HSSID()#"=TRUE";
                  string sShortKey = oDP.HSSID()#"=TRUE";
                  sValue = web.webKeyFromStringTable(sLongKey);
                  if( !sValue.Length() )
                  {
                    sValue = web.webKeyFromStringTable(sShortKey);
                    if( !sValue.Length() )
                    {
                      sValue = sShortKey;
                    }
                  }
                }
                Write( sValue );
                Write( '</option>' );
                if( (oDP.ID() == iDP) && (iV == 0) ) { sSelected = " selected"; } else { sSelected = ""; }
                Write( '<option value="'#oDP.ID()#':0"'#sSelected#'>' );
                string sValue = oDP.Name()#": "#oDP.ValueName0();
                if( (!oDP.IsTypeOf(OT_VARDP)) && (!oDP.IsTypeOf(OT_ALARMDP)) )
                {
                  string sLongKey = oCH.ChnLabel()#"|"#oDP.HSSID()#"=FALSE";
                  string sShortKey = oDP.HSSID()#"=FALSE";
                  sValue = web.webKeyFromStringTable(sLongKey);
                  if( !sValue.Length() )
                  {
                    sValue = web.webKeyFromStringTable(sShortKey);
                    if( !sValue.Length() )
                    {
                      sValue = sShortKey;
                    }
                  }
                }
                Write( sValue );
                Write( '</option>' );
              }
              else
              {
                ! Party mode params of the heating thermostats should not be visible
                ! For this params exists an own param type so that we are able to use a nice dialog
                if( (oDP.HSSID().Find(excludePARTY) == -1) || (oDP.HSSID().Find(includePARTY) != -1) ) {
                  Write( '<option value="'#oDP.ID()#':0|'#oDP.Name()#'"'#sSelected#'>' );
                  string sValue = oDP.Name();
                  if( (!oDP.IsTypeOf(OT_VARDP)) && (!oDP.IsTypeOf(OT_ALARMDP)) )
                  {
                    string sLongKey = oCH.ChnLabel()#"|"#oDP.HSSID();
                    string sShortKey = oDP.HSSID();
                    sValue = web.webKeyFromStringTable(sLongKey);
                    if( !sValue.Length() )
                    {
                      sValue = web.webKeyFromStringTable(sShortKey);
                      if( !sValue.Length() )
                      {
                        sValue = sShortKey;
                        if( !sValue.Length() )
                        {
                          sValue = oDP.Name();
                        }
                      }
                    }
                  }
                  Write( sValue );
                  Write( '</option>' );
                }
              }
            }
          }
          string sEnumSpecial = oDP.EnumSpecialIDs().ToString();
          if( sEnumSpecial == "65535" ) { sEnumSpecial = ""; }
          string s;
          foreach(s,sEnumSpecial)
          {
            if( (oDP.ID()==iDP) && (s==iV.ToString()) && (iVT == ivtSpecialValue) ) { sSelected = " selected"; } else { sSelected = ""; }
            Write( '<option value="'#oDP.ID()#':[SV]'#s#'"'#sSelected#'>' );
            string sKey = oCH.ChnLabel()#"|"#oDP.HSSID()#"="#s;
            string sValue = web.webKeyFromStringTable(sKey);
            if( !sValue.Length() )
            {
              sValue = sKey;
            }
            Write( sValue );
            Write( '</option>' );
          }
        }
      }
      Write( '</select> ' );
      if( (!bFound) && (iFirstID != ID_ERROR) )
      {
        oSD.DestinationDP( iFirstID );
        oSD.DestinationValue( 1 );
        iDP = oSD.DestinationDP();
        iCH = oSD.DestinationChannel();
        iP = oSD.DestinationParam();
        iV = oSD.DestinationValue();
        iVT = oSD.DestinationValueType();
        iVP = oSD.DestinationValueParam();
        iVPT = oSD.DestinationValueParamType();
      }
      
      object oDP = dom.GetObject( iDP );
      if( oDP )
      {
        if( oDP.Operations() & OPERATION_WRITE )
        {
          !Write( "SD:["#oSD.ID()#"] " );
          !Write( "DP:["#oDP.ID()#"] " );
          
          integer iDPvt = oDP.ValueType();
          integer iDPst = oDP.ValueSubType();
          
          !Write( "VT:["#iDPvt#"] " );
          !Write( "ST:["#iDPst#"] " );
          
          if( ((iVT == ivtInteger) && (iDPst == istEnum)) || (iVT == ivtBinary) )
          {
            !Write( "i" );
          }
          
          if( (iVT == ivtInteger) || (iVT == ivtFloat) || (iVT == ivtScaling) || (iVT == ivtRelScaling) || (iVT == ivtBitMask) || (iVT == ivtWord) || (iVT == ivtDWord) )
          {
            if( iDPst != istEnum )
            {
              Write( ' <i>${ruleDescrSetValueA}</i> ' );
              string sUnit = oDP.ValueUnit().ToString();
            
              real rMin = oDP.ValueMin();
              real rMax = oDP.ValueMax();
              
              integer iPercentPos = sUnit.Find("%");

              if( iPercentPos != -1 )
              {
                iV = 100.0 * iV;
                sUnit = sUnit.Substr(iPercentPos,1);
              }

              if( iV.Type() == "real" )
              {
                if( iV < rMin) 
                { 
                  iV = rMin.ToInteger().ToString() + rMin.ToString().Substr(rMin.Find("."),3);
                }
                iV = iV.ToString(2);
              }
      
              string sRange = " (" + rMin.ToInteger().ToString() + rMin.ToString().Substr(rMin.Find("."),3) + " - " + rMax.ToInteger().ToString() + rMax.ToString().Substr(rMax.Find("."),3) + ")"; 
              
              Write( '<input id="valSD_'#oSD.ID()#'" type="text" class="SelectBox" size="6" value="'#iV#'" onchange="iseSingleDestination.SetValueMinMax('#oSD.ID()#',this.value,\''#sUnit#'\','#oDP.ValueMin()#','#oDP.ValueMax()#');" />' );
              Write( sUnit );
              Write( '<span class="CLASS02401" onclick="ChangeDestinationValue('#oSD.ID()#');"><img src="/ise/img/notepad.png" /></span>' );
            }
          }        
          
          if( iVT == ivtString )
          {
            ! Label() presents the type id of the channel, e.g. HM-OU-LED16 or  HM-OU-CFM-Pl
            string chLabel = oCH.Label();

            integer x1 = chLabel.Find(hm_ouled16);
            integer x2 = chLabel.Find(hm_oucfm);
            integer x3 = chLabel.Find(hm_oucmpcb);
            integer x4 = hm_partyDialog.Find(chLabel);
            integer x5 = hm_statusDisplay.Find(chLabel);
            integer x6 = chLabel.Find(hm_rgbw_controller);

            if ((x5 != -1) || (x6 != -1)){
              if (x5 != -1) {
                if(iV == "0") {
                  ! This is the correct string for 'all channels not used'
                  iV = "0x02,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x03";
                }
                Write( '<input id="prgStringOptionValue'#oSD.ID()#'" onfocus="SetStatusDisplay('#oSD.ID()#');" type="text" class="SelectBox" size="10" value="'#iV#'" onchange="iseSingleDestination.SetValue('#oSD.ID()#',this.value,\'STRING\');" /> ' );
              }
              if (x6 != -1) {

                if (iV == "0") {
                  iV = "0,200,0.5,0,0,199"; ! default

                  if (oCH.HSSID() == "COLOR") {
                    iV = "0,200,0.5,0";
                  }

                  if (oCH.HSSID() == "AUTOMATIC") {
                    iV = "0,200,0.5,0,0,199";
                  }
                }
                Write( '<input id="prgStringOptionValue'#oSD.ID()#'" onfocus="SetRGBWController('#oSD.ID()#',\''#oCH.HSSID()#'\');" type="text" class="SelectBox" size="10" value="'#iV#'" onchange="iseSingleDestination.SetValue('#oSD.ID()#',this.value,\'STRING\');" /> ' );
              }
            } else {
              Write( '<input id="prgStringOptionValue'#oSD.ID()#'" type="text" class="SelectBox" size="10" value="'#iV#'" onchange="iseSingleDestination.SetValue('#oSD.ID()#',this.value,\'STRING\');" /> ' );
            }

            if((x1 == -1) && (x2 == -1) && (x3 == -1) && (x4 == -1) && (x5 == -1) && (x6 == -1)) {
              Write( '<span class="CLASS02401" onclick="ChangeDestinationValue('#oSD.ID()#');"><img src="/ise/img/notepad.png" /></span>' );
            } else {
              if(x1 != -1) {      
                Write( '<span class="CLASS02401" onclick="ChangeOULED16Value('#oSD.ID()#');"><img src="/ise/img/notepad.png" /></span>' );
              }
              if((x2 != -1) || (x3 != -1)) {
                Write( '<span class="CLASS02401" onclick="ChangeOUCFMValue('#oSD.ID()#');"><img src="/ise/img/notepad.png" /></span>' );
              }
              if (x4 != -1) {
                Write( '<span id="setPartyMode" class="CLASS02401" onclick="SetPartyMode(this);"><img src="/ise/img/notepad.png" /></span>' );
              }
              if (x5 != -1) {
                Write( '<span id="setStatusDisplay'#oSD.ID()#'" class="CLASS02401" onclick="SetStatusDisplay('#oSD.ID()#');"><img src="/ise/img/notepad.png" /></span>' );
              }
               if (x6 != -1) {
                Write( '<span id="setRGBWController'#oSD.ID()#'" class="CLASS02401" onclick="SetRGBWController('#oSD.ID()#',\''#oCH.HSSID()#'\');"><img src="/ise/img/notepad.png" /></span>' );
              }
            }
          }
          
          if( iVT == ivtObjectId )
          {
            
            Write( ' <i>mit</i> ' );
            object oDPTmp = dom.GetObject( iV );
            if( oDPTmp )
            {
              
              object oCH = dom.GetObject( oDPTmp.Channel() );
              if( oCH )
              {
                Write( ' <span class="CLASS02402" onclick="ChangeDestinationValue('#oSD.ID()#');">'#oCH.Name()#'</span> ' );
                Write( ' <select onchange="iseSingleDestination.SetValue('#oSD.ID()#',this.value);" class="SelectBox">' );
                boolean bFound = false;
                integer iFirstID = ID_ERROR;
                string sDP;
                foreach( sDP, oCH.DPs().EnumEnabledVisibleIDs() )
                {
                  object oDP = dom.GetObject( sDP );
                  if( oDP )
                  {
                    boolean bSetDefault = false;
                    if( !iV )
                    {
                      if( iDP == ID_ERROR )
                      {
                        bSetDefault = true;
                      }
                    }
                    if( oDP.Operations() & OPERATION_READ )
                    {
                      integer iDPvt = oDP.ValueType();
                      integer iDPst = oDP.ValueSubType();
                      if( iFirstID == ID_ERROR ) { iFirstID = oDP.ID(); }         
                      string sSelected = "";
                      if( oDP.ID() == iV ) { sSelected = " selected"; bFound = true; } else { sSelected = ""; }
                      string sIdx = "";
                      Write( '<option value="'#oDP.ID()#'"'#sSelected#'>' );
                      string sValue = oDP.Name();
                      if( (!oDP.IsTypeOf(OT_VARDP)) && (!oDP.IsTypeOf(OT_ALARMDP)) )
                      {
                        string sLongKey = oCH.ChnLabel()#"|"#oDP.HSSID();
                        string sShortKey = oDP.HSSID();
                        sValue = web.webKeyFromStringTable(sLongKey);
                        if( !sValue.Length() )
                        {
                          sValue = web.webKeyFromStringTable(sShortKey);
                          if( !sValue.Length() )
                          {
                            sValue = sShortKey;
                          }
                        }
                      }
                      Write( sValue );
                      Write( '</option>' );
                    }
                  }
                }
                Write( '</select> ' );
              } else { Write("(unbekannter Kanal)"); }
            } else { Write("(unbekannter Datenpunkt)"); }
            Write( ' <span class="CLASS02401" onclick="ChangeDestinationValue('#oSD.ID()#');"><img src="/ise/img/notepad.png" /></span> ' );
          }
          
          if( iVT == ivtSystemId )
          {
            Write( ' <i>mit</i> ' );
            object oDPTmp = dom.GetObject( iV );
            string sNameTmp = "";
            if( oDPTmp ) { sNameTmp = oDPTmp.Name(); }
            Write( ' <span class="CLASS02402" onclick="ChangeDestinationValue('#oSD.ID()#');">'#sNameTmp#'</span> ' );
            Write( ' <span class="CLASS02401" onclick="ChangeDestinationValue('#oSD.ID()#');"><img src="/ise/img/notepad.png" /></span> ' );
          }
        }
      }
    }
  }
  if( iP == ivtSystemId )
  {
    object oDP = dom.GetObject( iDP );
    if( oDP )
    {
      if( oDP.Operations() & OPERATION_WRITE )
      {
        if( oDP.ValueType() == ivtBinary )
        {
          Write( ' <select class="SelectBox" onchange="SetSysVarDestValue('#oSD.ID()#',this.value);">' );
          if( iV == 1 ) { sSelected = "selected"; } else { sSelected = ""; }
          Write( '<option value="'#oDP.ID()#':1"'#sSelected#'>' );
          Write( oDP.ValueName1() );
          Write( '</option>' );
          if( iV == 0 ) { sSelected = "selected"; } else { sSelected = ""; }
          Write( '<option value="'#oDP.ID()#':0"'#sSelected#'>' );
          Write( oDP.ValueName0() );
          Write( '</option>' );
          Write( '</select> ' );
        }
        if (oDP.ValueSubType() == istChar8859)
        {
          Write( ' <input type="text" class="SelectBox" size="32" value="'#oSD.DestinationValue().ToString()#'" onchange="SetSysVarDestStrValue('#oSD.ID()#',this.value);" /> ' );
          Write( oDP.ValueUnit()#" " );
        }
        if( oDP.ValueSubType() == istGeneric )
        {
          Write( ' <input id="dest'#oSD.ID()#'" type="hidden" class="SelectBox" size="6" value="'#oSD.DestinationValue().ToString(2)#'" onchange="SetSysVarDestValue('#oSD.ID()#',this.value,'#oDP.ValueMin()#','#oDP.ValueMax()#',\''#oDP.ValueUnit()#'\');" /> ' );
          real percVal = oSD.DestinationValue();
          if (oDP.ValueUnit() == "%") {
            percVal = oSD.DestinationValue() * 100;
          }
          Write( ' <input id="source'#oSD.ID()#'" type="text" class="SelectBox" size="6" value="'#percVal.ToString(2)#'" onchange="ConvertValueToPercent('#oSD.ID()#');" /> ' );
          Write( oDP.ValueUnit()#" " );
          !Write( '<span class="CLASS02401" onclick="ChangeDestinationValue('#oSD.ID()#');"><img src="/ise/img/notepad.png" /></span>' );
        }
        if( oDP.ValueSubType() == istEnum )
        {
          Write( ' <select class="SelectBox" onchange="SetSysVarDestValue('#oSD.ID()#',this.value);">' );
          integer iVLCount = web.webGetValueListCount( oDP.ValueList() );
          iVLCount = iVLCount - 1;
          string sVLKey;
          foreach( sVLKey, system.GenerateEnum(0,iVLCount) )
          {
            string sVLValue = web.webGetValueFromList( oDP.ValueList(), sVLKey );;
            if( sVLValue.Length() )
            {
              string sSelected = "";
              if( iV == sVLKey.ToInteger() ) { sSelected = "selected"; } else { sSelected = ""; }
              Write( '<option value="'#oDP.ID()#':'#sVLKey#'"'#sSelected#'>' );
              Write( sVLValue );
              Write( '</option>' );
            }
          }
          Write( '</select> ' );
        }
      }
    }       
  }
%>
