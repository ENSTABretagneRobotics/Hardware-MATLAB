function [methodinfo,structs,enuminfo,ThunkLibName]=hardwarex_proto
%HARDWAREX_PROTO Create structures to define interfaces found in 'hardwarex'.

%This function was generated by loadlibrary.m parser version  on Fri Jan  5 01:32:08 2018
%perl options:'hardwarex.i -outfile=hardwarex_proto.m -thunkfile=hardwarex_thunk_pcwin64.c -header=hardwarex.h'
ival={cell(1,0)}; % change 0 to the actual number of functions to preallocate the data.
structs=[];enuminfo=[];fcnNum=1;
fcns=struct('name',ival,'calltype',ival,'LHS',ival,'RHS',ival,'alias',ival,'thunkname', ival);
MfilePath=fileparts(mfilename('fullpath'));
ThunkLibName=fullfile(MfilePath,'hardwarex_thunk_pcwin64');
%  MT * CreateMTx ( void ); 
fcns.thunkname{fcnNum}='voidPtrvoidThunk';fcns.name{fcnNum}='CreateMTx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='MTPtr'; fcns.RHS{fcnNum}=[];fcnNum=fcnNum+1;
%  void DestroyMTx ( MT * pMT ); 
fcns.thunkname{fcnNum}='voidvoidPtrThunk';fcns.name{fcnNum}='DestroyMTx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}=[]; fcns.RHS{fcnNum}={'MTPtr'};fcnNum=fcnNum+1;
%  MTDATA * CreateMTDatax ( void ); 
fcns.thunkname{fcnNum}='voidPtrvoidThunk';fcns.name{fcnNum}='CreateMTDatax'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='MTDATAPtr'; fcns.RHS{fcnNum}=[];fcnNum=fcnNum+1;
%  void DestroyMTDatax ( MTDATA * pMTData ); 
fcns.thunkname{fcnNum}='voidvoidPtrThunk';fcns.name{fcnNum}='DestroyMTDatax'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}=[]; fcns.RHS{fcnNum}={'MTDATAPtr'};fcnNum=fcnNum+1;
%  int GetLatestDataMTx ( MT * pMT , MTDATA * pMTData ); 
fcns.thunkname{fcnNum}='int32voidPtrvoidPtrThunk';fcns.name{fcnNum}='GetLatestDataMTx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'MTPtr', 'MTDATAPtr'};fcnNum=fcnNum+1;
%  int ConnectMTx ( MT * pMT , char * szCfgFilePath ); 
fcns.thunkname{fcnNum}='int32voidPtrcstringThunk';fcns.name{fcnNum}='ConnectMTx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'MTPtr', 'cstring'};fcnNum=fcnNum+1;
%  int DisconnectMTx ( MT * pMT ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='DisconnectMTx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'MTPtr'};fcnNum=fcnNum+1;
%  int GetLatestDataFromThreadMTx ( MT * pMT , MTDATA * pMTData ); 
fcns.thunkname{fcnNum}='int32voidPtrvoidPtrThunk';fcns.name{fcnNum}='GetLatestDataFromThreadMTx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'MTPtr', 'MTDATAPtr'};fcnNum=fcnNum+1;
%  int StartThreadMTx ( MT * pMT ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='StartThreadMTx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'MTPtr'};fcnNum=fcnNum+1;
%  int StopThreadMTx ( MT * pMT ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='StopThreadMTx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'MTPtr'};fcnNum=fcnNum+1;
%  RAZORAHRS * CreateRazorAHRSx ( void ); 
fcns.thunkname{fcnNum}='voidPtrvoidThunk';fcns.name{fcnNum}='CreateRazorAHRSx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='RAZORAHRSPtr'; fcns.RHS{fcnNum}=[];fcnNum=fcnNum+1;
%  void DestroyRazorAHRSx ( RAZORAHRS * pRazorAHRS ); 
fcns.thunkname{fcnNum}='voidvoidPtrThunk';fcns.name{fcnNum}='DestroyRazorAHRSx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}=[]; fcns.RHS{fcnNum}={'RAZORAHRSPtr'};fcnNum=fcnNum+1;
%  RAZORAHRSDATA * CreateRazorAHRSDatax ( void ); 
fcns.thunkname{fcnNum}='voidPtrvoidThunk';fcns.name{fcnNum}='CreateRazorAHRSDatax'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='RAZORAHRSDATAPtr'; fcns.RHS{fcnNum}=[];fcnNum=fcnNum+1;
%  void DestroyRazorAHRSDatax ( RAZORAHRSDATA * pRazorAHRSData ); 
fcns.thunkname{fcnNum}='voidvoidPtrThunk';fcns.name{fcnNum}='DestroyRazorAHRSDatax'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}=[]; fcns.RHS{fcnNum}={'RAZORAHRSDATAPtr'};fcnNum=fcnNum+1;
%  int GetLatestDataRazorAHRSx ( RAZORAHRS * pRazorAHRS , RAZORAHRSDATA * pRazorAHRSData ); 
fcns.thunkname{fcnNum}='int32voidPtrvoidPtrThunk';fcns.name{fcnNum}='GetLatestDataRazorAHRSx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'RAZORAHRSPtr', 'RAZORAHRSDATAPtr'};fcnNum=fcnNum+1;
%  int ConnectRazorAHRSx ( RAZORAHRS * pRazorAHRS , char * szCfgFilePath ); 
fcns.thunkname{fcnNum}='int32voidPtrcstringThunk';fcns.name{fcnNum}='ConnectRazorAHRSx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'RAZORAHRSPtr', 'cstring'};fcnNum=fcnNum+1;
%  int DisconnectRazorAHRSx ( RAZORAHRS * pRazorAHRS ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='DisconnectRazorAHRSx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'RAZORAHRSPtr'};fcnNum=fcnNum+1;
%  int GetLatestDataFromThreadRazorAHRSx ( RAZORAHRS * pRazorAHRS , RAZORAHRSDATA * pRazorAHRSData ); 
fcns.thunkname{fcnNum}='int32voidPtrvoidPtrThunk';fcns.name{fcnNum}='GetLatestDataFromThreadRazorAHRSx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'RAZORAHRSPtr', 'RAZORAHRSDATAPtr'};fcnNum=fcnNum+1;
%  int StartThreadRazorAHRSx ( RAZORAHRS * pRazorAHRS ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='StartThreadRazorAHRSx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'RAZORAHRSPtr'};fcnNum=fcnNum+1;
%  int StopThreadRazorAHRSx ( RAZORAHRS * pRazorAHRS ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='StopThreadRazorAHRSx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'RAZORAHRSPtr'};fcnNum=fcnNum+1;
%  NMEADEVICE * CreateNMEADevicex ( void ); 
fcns.thunkname{fcnNum}='voidPtrvoidThunk';fcns.name{fcnNum}='CreateNMEADevicex'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='NMEADEVICEPtr'; fcns.RHS{fcnNum}=[];fcnNum=fcnNum+1;
%  void DestroyNMEADevicex ( NMEADEVICE * pNMEADevice ); 
fcns.thunkname{fcnNum}='voidvoidPtrThunk';fcns.name{fcnNum}='DestroyNMEADevicex'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}=[]; fcns.RHS{fcnNum}={'NMEADEVICEPtr'};fcnNum=fcnNum+1;
%  NMEADATA * CreateNMEADatax ( void ); 
fcns.thunkname{fcnNum}='voidPtrvoidThunk';fcns.name{fcnNum}='CreateNMEADatax'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='NMEADATAPtr'; fcns.RHS{fcnNum}=[];fcnNum=fcnNum+1;
%  void DestroyNMEADatax ( NMEADATA * pNMEAData ); 
fcns.thunkname{fcnNum}='voidvoidPtrThunk';fcns.name{fcnNum}='DestroyNMEADatax'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}=[]; fcns.RHS{fcnNum}={'NMEADATAPtr'};fcnNum=fcnNum+1;
%  int GetLatestDataNMEADevicex ( NMEADEVICE * pNMEADevice , NMEADATA * pNMEAData ); 
fcns.thunkname{fcnNum}='int32voidPtrvoidPtrThunk';fcns.name{fcnNum}='GetLatestDataNMEADevicex'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'NMEADEVICEPtr', 'NMEADATAPtr'};fcnNum=fcnNum+1;
%  int ConnectNMEADevicex ( NMEADEVICE * pNMEADevice , char * szCfgFilePath ); 
fcns.thunkname{fcnNum}='int32voidPtrcstringThunk';fcns.name{fcnNum}='ConnectNMEADevicex'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'NMEADEVICEPtr', 'cstring'};fcnNum=fcnNum+1;
%  int DisconnectNMEADevicex ( NMEADEVICE * pNMEADevice ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='DisconnectNMEADevicex'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'NMEADEVICEPtr'};fcnNum=fcnNum+1;
%  int GetLatestDataFromThreadNMEADevicex ( NMEADEVICE * pNMEADevice , NMEADATA * pNMEAData ); 
fcns.thunkname{fcnNum}='int32voidPtrvoidPtrThunk';fcns.name{fcnNum}='GetLatestDataFromThreadNMEADevicex'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'NMEADEVICEPtr', 'NMEADATAPtr'};fcnNum=fcnNum+1;
%  int StartThreadNMEADevicex ( NMEADEVICE * pNMEADevice ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='StartThreadNMEADevicex'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'NMEADEVICEPtr'};fcnNum=fcnNum+1;
%  int StopThreadNMEADevicex ( NMEADEVICE * pNMEADevice ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='StopThreadNMEADevicex'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'NMEADEVICEPtr'};fcnNum=fcnNum+1;
%  UBLOX * Createubloxx ( void ); 
fcns.thunkname{fcnNum}='voidPtrvoidThunk';fcns.name{fcnNum}='Createubloxx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='UBLOXPtr'; fcns.RHS{fcnNum}=[];fcnNum=fcnNum+1;
%  void Destroyubloxx ( UBLOX * publox ); 
fcns.thunkname{fcnNum}='voidvoidPtrThunk';fcns.name{fcnNum}='Destroyubloxx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}=[]; fcns.RHS{fcnNum}={'UBLOXPtr'};fcnNum=fcnNum+1;
%  UBXDATA * CreateUBXDatax ( void ); 
fcns.thunkname{fcnNum}='voidPtrvoidThunk';fcns.name{fcnNum}='CreateUBXDatax'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='UBXDATAPtr'; fcns.RHS{fcnNum}=[];fcnNum=fcnNum+1;
%  void DestroyUBXDatax ( UBXDATA * pUBXData ); 
fcns.thunkname{fcnNum}='voidvoidPtrThunk';fcns.name{fcnNum}='DestroyUBXDatax'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}=[]; fcns.RHS{fcnNum}={'UBXDATAPtr'};fcnNum=fcnNum+1;
%  int GetNMEASentenceubloxx ( UBLOX * publox , NMEADATA * pNMEAData ); 
fcns.thunkname{fcnNum}='int32voidPtrvoidPtrThunk';fcns.name{fcnNum}='GetNMEASentenceubloxx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'UBLOXPtr', 'NMEADATAPtr'};fcnNum=fcnNum+1;
%  int GetUBXPacketubloxx ( UBLOX * publox , UBXDATA * pUBXData ); 
fcns.thunkname{fcnNum}='int32voidPtrvoidPtrThunk';fcns.name{fcnNum}='GetUBXPacketubloxx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'UBLOXPtr', 'UBXDATAPtr'};fcnNum=fcnNum+1;
%  int Connectubloxx ( UBLOX * publox , char * szCfgFilePath ); 
fcns.thunkname{fcnNum}='int32voidPtrcstringThunk';fcns.name{fcnNum}='Connectubloxx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'UBLOXPtr', 'cstring'};fcnNum=fcnNum+1;
%  int Disconnectubloxx ( UBLOX * publox ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='Disconnectubloxx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'UBLOXPtr'};fcnNum=fcnNum+1;
%  int GetNMEASentenceFromThreadubloxx ( UBLOX * publox , NMEADATA * pNMEAData ); 
fcns.thunkname{fcnNum}='int32voidPtrvoidPtrThunk';fcns.name{fcnNum}='GetNMEASentenceFromThreadubloxx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'UBLOXPtr', 'NMEADATAPtr'};fcnNum=fcnNum+1;
%  int GetUBXPacketFromThreadubloxx ( UBLOX * publox , UBXDATA * pUBXData ); 
fcns.thunkname{fcnNum}='int32voidPtrvoidPtrThunk';fcns.name{fcnNum}='GetUBXPacketFromThreadubloxx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'UBLOXPtr', 'UBXDATAPtr'};fcnNum=fcnNum+1;
%  int StartNMEAThreadubloxx ( UBLOX * publox ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='StartNMEAThreadubloxx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'UBLOXPtr'};fcnNum=fcnNum+1;
%  int StopNMEAThreadubloxx ( UBLOX * publox ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='StopNMEAThreadubloxx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'UBLOXPtr'};fcnNum=fcnNum+1;
%  int StartUBXThreadubloxx ( UBLOX * publox ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='StartUBXThreadubloxx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'UBLOXPtr'};fcnNum=fcnNum+1;
%  int StopUBXThreadubloxx ( UBLOX * publox ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='StopUBXThreadubloxx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'UBLOXPtr'};fcnNum=fcnNum+1;
%  SSC32 * CreateSSC32x ( void ); 
fcns.thunkname{fcnNum}='voidPtrvoidThunk';fcns.name{fcnNum}='CreateSSC32x'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='SSC32Ptr'; fcns.RHS{fcnNum}=[];fcnNum=fcnNum+1;
%  void DestroySSC32x ( SSC32 * pSSC32 ); 
fcns.thunkname{fcnNum}='voidvoidPtrThunk';fcns.name{fcnNum}='DestroySSC32x'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}=[]; fcns.RHS{fcnNum}={'SSC32Ptr'};fcnNum=fcnNum+1;
%  int SetPWMSSC32x ( SSC32 * pSSC32 , int channel , int pw ); 
fcns.thunkname{fcnNum}='int32voidPtrint32int32Thunk';fcns.name{fcnNum}='SetPWMSSC32x'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'SSC32Ptr', 'int32', 'int32'};fcnNum=fcnNum+1;
%  int SetAllPWMsSSC32x ( SSC32 * pSSC32 , int * selectedchannels , int * pws ); 
fcns.thunkname{fcnNum}='int32voidPtrvoidPtrvoidPtrThunk';fcns.name{fcnNum}='SetAllPWMsSSC32x'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'SSC32Ptr', 'int32Ptr', 'int32Ptr'};fcnNum=fcnNum+1;
%  int ConnectSSC32x ( SSC32 * pSSC32 , char * szCfgFilePath ); 
fcns.thunkname{fcnNum}='int32voidPtrcstringThunk';fcns.name{fcnNum}='ConnectSSC32x'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'SSC32Ptr', 'cstring'};fcnNum=fcnNum+1;
%  int DisconnectSSC32x ( SSC32 * pSSC32 ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='DisconnectSSC32x'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'SSC32Ptr'};fcnNum=fcnNum+1;
%  int SetAllPWMsFromThreadSSC32x ( SSC32 * pSSC32 , int * selectedchannels , int * pws ); 
fcns.thunkname{fcnNum}='int32voidPtrvoidPtrvoidPtrThunk';fcns.name{fcnNum}='SetAllPWMsFromThreadSSC32x'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'SSC32Ptr', 'int32Ptr', 'int32Ptr'};fcnNum=fcnNum+1;
%  int StartThreadSSC32x ( SSC32 * pSSC32 ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='StartThreadSSC32x'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'SSC32Ptr'};fcnNum=fcnNum+1;
%  int StopThreadSSC32x ( SSC32 * pSSC32 ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='StopThreadSSC32x'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'SSC32Ptr'};fcnNum=fcnNum+1;
%  MAESTRO * CreateMaestrox ( void ); 
fcns.thunkname{fcnNum}='voidPtrvoidThunk';fcns.name{fcnNum}='CreateMaestrox'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='MAESTROPtr'; fcns.RHS{fcnNum}=[];fcnNum=fcnNum+1;
%  void DestroyMaestrox ( MAESTRO * pMaestro ); 
fcns.thunkname{fcnNum}='voidvoidPtrThunk';fcns.name{fcnNum}='DestroyMaestrox'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}=[]; fcns.RHS{fcnNum}={'MAESTROPtr'};fcnNum=fcnNum+1;
%  int GetValueMaestrox ( MAESTRO * pMaestro , int channel , int * pValue ); 
fcns.thunkname{fcnNum}='int32voidPtrint32voidPtrThunk';fcns.name{fcnNum}='GetValueMaestrox'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'MAESTROPtr', 'int32', 'int32Ptr'};fcnNum=fcnNum+1;
%  int SetPWMMaestrox ( MAESTRO * pMaestro , int channel , int pw ); 
fcns.thunkname{fcnNum}='int32voidPtrint32int32Thunk';fcns.name{fcnNum}='SetPWMMaestrox'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'MAESTROPtr', 'int32', 'int32'};fcnNum=fcnNum+1;
%  int SetAllPWMsMaestrox ( MAESTRO * pMaestro , int * selectedchannels , int * pws ); 
fcns.thunkname{fcnNum}='int32voidPtrvoidPtrvoidPtrThunk';fcns.name{fcnNum}='SetAllPWMsMaestrox'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'MAESTROPtr', 'int32Ptr', 'int32Ptr'};fcnNum=fcnNum+1;
%  int ConnectMaestrox ( MAESTRO * pMaestro , char * szCfgFilePath ); 
fcns.thunkname{fcnNum}='int32voidPtrcstringThunk';fcns.name{fcnNum}='ConnectMaestrox'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'MAESTROPtr', 'cstring'};fcnNum=fcnNum+1;
%  int DisconnectMaestrox ( MAESTRO * pMaestro ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='DisconnectMaestrox'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'MAESTROPtr'};fcnNum=fcnNum+1;
%  int SetAllPWMsFromThreadMaestrox ( MAESTRO * pMaestro , int * selectedchannels , int * pws ); 
fcns.thunkname{fcnNum}='int32voidPtrvoidPtrvoidPtrThunk';fcns.name{fcnNum}='SetAllPWMsFromThreadMaestrox'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'MAESTROPtr', 'int32Ptr', 'int32Ptr'};fcnNum=fcnNum+1;
%  int GetValueFromThreadMaestrox ( MAESTRO * pMaestro , int channel , int * pValue ); 
fcns.thunkname{fcnNum}='int32voidPtrint32voidPtrThunk';fcns.name{fcnNum}='GetValueFromThreadMaestrox'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'MAESTROPtr', 'int32', 'int32Ptr'};fcnNum=fcnNum+1;
%  int StartThreadMaestrox ( MAESTRO * pMaestro ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='StartThreadMaestrox'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'MAESTROPtr'};fcnNum=fcnNum+1;
%  int StopThreadMaestrox ( MAESTRO * pMaestro ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='StopThreadMaestrox'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'MAESTROPtr'};fcnNum=fcnNum+1;
%  HOKUYO * CreateHokuyox ( void ); 
fcns.thunkname{fcnNum}='voidPtrvoidThunk';fcns.name{fcnNum}='CreateHokuyox'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='HOKUYOPtr'; fcns.RHS{fcnNum}=[];fcnNum=fcnNum+1;
%  void DestroyHokuyox ( HOKUYO * pHokuyo ); 
fcns.thunkname{fcnNum}='voidvoidPtrThunk';fcns.name{fcnNum}='DestroyHokuyox'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}=[]; fcns.RHS{fcnNum}={'HOKUYOPtr'};fcnNum=fcnNum+1;
%  double k2angleHokuyox ( HOKUYO * pHokuyo , int k ); 
fcns.thunkname{fcnNum}='doublevoidPtrint32Thunk';fcns.name{fcnNum}='k2angleHokuyox'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='double'; fcns.RHS{fcnNum}={'HOKUYOPtr', 'int32'};fcnNum=fcnNum+1;
%  int angle2kHokuyox ( HOKUYO * pHokuyo , double angle ); 
fcns.thunkname{fcnNum}='int32voidPtrdoubleThunk';fcns.name{fcnNum}='angle2kHokuyox'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'HOKUYOPtr', 'double'};fcnNum=fcnNum+1;
%  int GetLatestDataHokuyox ( HOKUYO * pHokuyo , double * pDistances , double * pAngles ); 
fcns.thunkname{fcnNum}='int32voidPtrvoidPtrvoidPtrThunk';fcns.name{fcnNum}='GetLatestDataHokuyox'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'HOKUYOPtr', 'doublePtr', 'doublePtr'};fcnNum=fcnNum+1;
%  int ConnectHokuyox ( HOKUYO * pHokuyo , char * szCfgFilePath ); 
fcns.thunkname{fcnNum}='int32voidPtrcstringThunk';fcns.name{fcnNum}='ConnectHokuyox'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'HOKUYOPtr', 'cstring'};fcnNum=fcnNum+1;
%  int DisconnectHokuyox ( HOKUYO * pHokuyo ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='DisconnectHokuyox'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'HOKUYOPtr'};fcnNum=fcnNum+1;
%  int GetLatestDataFromThreadHokuyox ( HOKUYO * pHokuyo , double * pDistances , double * pAngles ); 
fcns.thunkname{fcnNum}='int32voidPtrvoidPtrvoidPtrThunk';fcns.name{fcnNum}='GetLatestDataFromThreadHokuyox'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'HOKUYOPtr', 'doublePtr', 'doublePtr'};fcnNum=fcnNum+1;
%  int StartThreadHokuyox ( HOKUYO * pHokuyo ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='StartThreadHokuyox'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'HOKUYOPtr'};fcnNum=fcnNum+1;
%  int StopThreadHokuyox ( HOKUYO * pHokuyo ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='StopThreadHokuyox'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'HOKUYOPtr'};fcnNum=fcnNum+1;
%  RPLIDAR * CreateRPLIDARx ( void ); 
fcns.thunkname{fcnNum}='voidPtrvoidThunk';fcns.name{fcnNum}='CreateRPLIDARx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='RPLIDARPtr'; fcns.RHS{fcnNum}=[];fcnNum=fcnNum+1;
%  void DestroyRPLIDARx ( RPLIDAR * pRPLIDAR ); 
fcns.thunkname{fcnNum}='voidvoidPtrThunk';fcns.name{fcnNum}='DestroyRPLIDARx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}=[]; fcns.RHS{fcnNum}={'RPLIDARPtr'};fcnNum=fcnNum+1;
%  int GetExpressScanDataResponseRPLIDARx ( RPLIDAR * pRPLIDAR , double * pDistances , double * pAngles , BOOL * pbNewScan ); 
fcns.thunkname{fcnNum}='int32voidPtrvoidPtrvoidPtrvoidPtrThunk';fcns.name{fcnNum}='GetExpressScanDataResponseRPLIDARx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'RPLIDARPtr', 'doublePtr', 'doublePtr', 'int32Ptr'};fcnNum=fcnNum+1;
%  int ConnectRPLIDARx ( RPLIDAR * pRPLIDAR , char * szCfgFilePath ); 
fcns.thunkname{fcnNum}='int32voidPtrcstringThunk';fcns.name{fcnNum}='ConnectRPLIDARx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'RPLIDARPtr', 'cstring'};fcnNum=fcnNum+1;
%  int DisconnectRPLIDARx ( RPLIDAR * pRPLIDAR ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='DisconnectRPLIDARx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'RPLIDARPtr'};fcnNum=fcnNum+1;
%  int GetExpressScanDataResponseFromThreadRPLIDARx ( RPLIDAR * pRPLIDAR , double * pDistances , double * pAngles , BOOL * pbNewScan ); 
fcns.thunkname{fcnNum}='int32voidPtrvoidPtrvoidPtrvoidPtrThunk';fcns.name{fcnNum}='GetExpressScanDataResponseFromThreadRPLIDARx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'RPLIDARPtr', 'doublePtr', 'doublePtr', 'int32Ptr'};fcnNum=fcnNum+1;
%  int StartThreadRPLIDARx ( RPLIDAR * pRPLIDAR ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='StartThreadRPLIDARx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'RPLIDARPtr'};fcnNum=fcnNum+1;
%  int StopThreadRPLIDARx ( RPLIDAR * pRPLIDAR ); 
fcns.thunkname{fcnNum}='int32voidPtrThunk';fcns.name{fcnNum}='StopThreadRPLIDARx'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'RPLIDARPtr'};fcnNum=fcnNum+1;
structs.s_iobuf.packing=8;
structs.s_iobuf.members=struct('m_ptr', 'cstring', 'm_cnt', 'int32', 'm_base', 'cstring', 'm_flag', 'int32', 'm_file', 'int32', 'm_charbuf', 'int32', 'm_bufsiz', 'int32', 'm_tmpfname', 'cstring');
structs.RS232PORT.members=struct('hDev', 'voidPtr', 's', 'uint64', 's_srv', 'uint64', 'szDevPath', 'int8#256', 'address', 'int8#256', 'port', 'int8#256', 'DevType', 'int32');
structs.UTC_Time_MT.members=struct('Nanoseconds', 'uint32', 'Year', 'uint16', 'Month', 'uint8', 'Day', 'uint8', 'Hour', 'uint8', 'Minute', 'uint8', 'Seconds', 'uint8', 'Valid', 'uint8');
structs.MTDATA.members=struct('temp', 'double', 'accX', 'double', 'accY', 'double', 'accZ', 'double', 'gyrX', 'double', 'gyrY', 'double', 'gyrZ', 'double', 'magX', 'double', 'magY', 'double', 'magZ', 'double', 'q0', 'double', 'q1', 'double', 'q2', 'double', 'q3', 'double', 'roll', 'double', 'pitch', 'double', 'yaw', 'double', 'a', 'double', 'b', 'double', 'c', 'double', 'd', 'double', 'e', 'double', 'f', 'double', 'g', 'double', 'h', 'double', 'i', 'double', 'Ain_1', 'uint16', 'Ain_2', 'uint16', 'Lat', 'double', 'Long', 'double', 'Alt', 'double', 'Vel_X', 'double', 'Vel_Y', 'double', 'Vel_Z', 'double', 'Status', 'uint8', 'TS', 'uint16', 'UTCTime', 'UTC_Time_MT', 'Roll', 'double', 'Pitch', 'double', 'Yaw', 'double');
structs.MT.members=struct('RS232Port', 'RS232PORT', 'OutputMode', 'int32', 'OutputSettings', 'int32', 'pfSaveFile', 's_iobufPtr', 'LastMTData', 'MTDATA', 'szCfgFilePath', 'int8#256', 'szDevPath', 'int8#256', 'BaudRate', 'int32', 'timeout', 'int32', 'bSaveRawData', 'int32', 'bLegacyMode', 'int32', 'rollorientation', 'double', 'rollp1', 'double', 'rollp2', 'double', 'pitchorientation', 'double', 'pitchp1', 'double', 'pitchp2', 'double', 'yaworientation', 'double', 'yawp1', 'double', 'yawp2', 'double');
structs.RAZORAHRSDATA.members=struct('yaw', 'double', 'pitch', 'double', 'roll', 'double', 'accx', 'double', 'accy', 'double', 'accz', 'double', 'gyrx', 'double', 'gyry', 'double', 'gyrz', 'double', 'Roll', 'double', 'Pitch', 'double', 'Yaw', 'double');
structs.RAZORAHRS.members=struct('RS232Port', 'RS232PORT', 'pfSaveFile', 's_iobufPtr', 'LastRazorAHRSData', 'RAZORAHRSDATA', 'szCfgFilePath', 'int8#256', 'szDevPath', 'int8#256', 'BaudRate', 'int32', 'timeout', 'int32', 'bSaveRawData', 'int32', 'bROSMode', 'int32', 'rollorientation', 'double', 'rollp1', 'double', 'rollp2', 'double', 'pitchorientation', 'double', 'pitchp1', 'double', 'pitchp2', 'double', 'yaworientation', 'double', 'yawp1', 'double', 'yawp2', 'double');
structs.NMEADATA.members=struct('utc', 'double', 'date', 'double', 'pressure', 'double', 'temperature', 'double', 'cpressure', 'int8', 'ctemperature', 'int8', 'winddir', 'double', 'windspeed', 'double', 'cwinddir', 'int8', 'cwindspeed', 'int8', 'awinddir', 'double', 'awindspeed', 'double', 'cawinddir', 'int8', 'cawindspeed', 'int8', 'latdeg', 'int32', 'longdeg', 'int32', 'latmin', 'double', 'longmin', 'double', 'szlatdeg', 'int8#3', 'szlongdeg', 'int8#4', 'north', 'int8', 'east', 'int8', 'GPS_quality_indicator', 'int32', 'nbsat', 'int32', 'hdop', 'double', 'height_geoid', 'double', 'status', 'int8', 'posMode', 'int8', 'sog', 'double', 'kph', 'double', 'cog', 'double', 'mag_cog', 'double', 'heading', 'double', 'deviation', 'double', 'variation', 'double', 'dev_east', 'int8', 'var_east', 'int8', 'nbsentences', 'int32', 'sentence_number', 'int32', 'seqmsgid', 'int32', 'AIS_channel', 'int8', 'nbfillbits', 'int32', 'roll', 'double', 'pitch', 'double', 'salinity', 'double', 'depth', 'double', 'speedofsound', 'double', 'vx_dvl', 'double', 'vy_dvl', 'double', 'vz_dvl', 'double', 'verr_dvl', 'double', 'vt_ship', 'double', 'vl_ship', 'double', 'vn_ship', 'double', 'v_east', 'double', 'v_north', 'double', 'v_up', 'double', 'vstatus_dvl', 'int8', 'vstatus_ship', 'int8', 'vstatus_earth', 'int8', 'd_east', 'double', 'd_north', 'double', 'd_up', 'double', 'rangetobottom', 'double', 'timesincelastgood', 'double', 'Latitude', 'double', 'Longitude', 'double', 'Altitude', 'double', 'Altitude_AGL', 'double', 'SOG', 'double', 'COG', 'double', 'year', 'int32', 'month', 'int32', 'day', 'int32', 'hour', 'int32', 'minute', 'int32', 'second', 'double', 'Roll', 'double', 'Pitch', 'double', 'Heading', 'double', 'WindDir', 'double', 'WindSpeed', 'double', 'ApparentWindDir', 'double', 'ApparentWindSpeed', 'double', 'AIS_Latitude', 'double', 'AIS_Longitude', 'double', 'AIS_SOG', 'double', 'AIS_COG', 'double');
structs.NMEADEVICE.members=struct('RS232Port', 'RS232PORT', 'pfSaveFile', 's_iobufPtr', 'LastNMEAData', 'NMEADATA', 'szCfgFilePath', 'int8#256', 'szDevPath', 'int8#256', 'BaudRate', 'int32', 'timeout', 'int32', 'bSaveRawData', 'int32', 'bEnableGPGGA', 'int32', 'bEnableGPRMC', 'int32', 'bEnableGPGLL', 'int32', 'bEnableGPVTG', 'int32', 'bEnableHCHDG', 'int32', 'bEnableIIMWV', 'int32', 'bEnableWIMWV', 'int32', 'bEnableWIMWD', 'int32', 'bEnableWIMDA', 'int32', 'bEnableAIVDM', 'int32');
structs.NAV_POSLLH_PL_UBX.packing=1;
structs.NAV_POSLLH_PL_UBX.members=struct('iTOW', 'uint32', 'lon', 'int32', 'lat', 'int32', 'height', 'int32', 'hMSL', 'int32', 'hAcc', 'uint32', 'vAcc', 'uint32');
structs.NAV_PVT_PL_UBX.packing=1;
structs.NAV_PVT_PL_UBX.members=struct('iTOW', 'uint32', 'year', 'uint16', 'month', 'uint8', 'day', 'uint8', 'hour', 'uint8', 'minute', 'uint8', 'sec', 'uint8', 'valid', 'error', 'tAcc', 'uint32', 'nano', 'int32', 'fixType', 'uint8', 'flags', 'error', 'flags2', 'error', 'numSV', 'uint8', 'lon', 'int32', 'lat', 'int32', 'height', 'int32', 'hMSL', 'int32', 'hAcc', 'uint32', 'vAcc', 'uint32', 'velN', 'int32', 'velE', 'int32', 'velD', 'int32', 'gSpeed', 'int32', 'headMot', 'int32', 'sAcc', 'uint32', 'headAcc', 'uint32', 'pDOP', 'uint16', 'reserved1', 'uint8#6', 'headVeh', 'int32', 'reserved2', 'uint8#4');
structs.NAV_SOL_PL_UBX.packing=1;
structs.NAV_SOL_PL_UBX.members=struct('iTOW', 'uint32', 'fTOW', 'int32', 'week', 'int16', 'gpsFix', 'uint8', 'flags', 'error', 'ecefX', 'int32', 'ecefY', 'int32', 'ecefZ', 'int32', 'pAcc', 'uint32', 'ecefVX', 'int32', 'ecefVY', 'int32', 'ecefVZ', 'int32', 'sAcc', 'uint32', 'pDOP', 'uint16', 'reserved1', 'uint8', 'numSV', 'uint8', 'reserved2', 'uint8#4');
structs.NAV_STATUS_PL_UBX.packing=1;
structs.NAV_STATUS_PL_UBX.members=struct('iTOW', 'uint32', 'gpsFix', 'uint8', 'flags', 'error', 'fixStat', 'error', 'flags2', 'error', 'ttff', 'uint32', 'msss', 'uint32');
structs.NAV_SVIN_PL_UBX.packing=1;
structs.NAV_SVIN_PL_UBX.members=struct('version', 'uint8', 'reserved1', 'uint8#3', 'iTOW', 'uint32', 'dur', 'uint32', 'meanX', 'int32', 'meanY', 'int32', 'meanZ', 'int32', 'meanXHP', 'int8', 'meanYHP', 'int8', 'meanZHP', 'int8', 'reserved2', 'uint8', 'meanAcc', 'uint32', 'obs', 'uint32', 'valid', 'uint8', 'active', 'uint8', 'reserved3', 'uint8#2');
structs.NAV_VELNED_PL_UBX.packing=1;
structs.NAV_VELNED_PL_UBX.members=struct('iTOW', 'uint32', 'velN', 'int32', 'velE', 'int32', 'velD', 'int32', 'speed', 'uint32', 'gSpeed', 'uint32', 'heading', 'int32', 'sAcc', 'uint32', 'cAcc', 'uint32');
structs.UBXDATA.packing=1;
structs.UBXDATA.members=struct('nav_posllh_pl', 'NAV_POSLLH_PL_UBX', 'nav_pvt_pl', 'NAV_PVT_PL_UBX', 'nav_sol_pl', 'NAV_SOL_PL_UBX', 'nav_status_pl', 'NAV_STATUS_PL_UBX', 'nav_svin_pl', 'NAV_SVIN_PL_UBX', 'nav_velned_pl', 'NAV_VELNED_PL_UBX', 'Latitude', 'double', 'Longitude', 'double', 'Altitude', 'double', 'SOG', 'double', 'COG', 'double', 'year', 'int32', 'month', 'int32', 'day', 'int32', 'hour', 'int32', 'minute', 'int32', 'second', 'double', 'Heading', 'double');
structs.UBLOX.packing=1;
structs.UBLOX.members=struct('RS232Port', 'RS232PORT', 'pfSaveFile', 's_iobufPtr', 'LastUBXData', 'UBXDATA', 'szCfgFilePath', 'int8#256', 'szDevPath', 'int8#256', 'BaudRate', 'int32', 'timeout', 'int32', 'bSaveRawData', 'int32', 'bRevertToDefaultCfg', 'int32', 'SetCfg', 'int32', 'SurveyMode', 'int32', 'svinMinDur', 'double', 'svinAccLimit', 'double', 'fixedLat', 'double', 'fixedLon', 'double', 'fixedAlt', 'double', 'fixedPosAcc', 'double', 'bEnable_NMEA_GGA', 'int32', 'bEnable_NMEA_RMC', 'int32', 'bEnable_NMEA_GLL', 'int32', 'bEnable_NMEA_VTG', 'int32', 'bEnable_NMEA_HDG', 'int32', 'bEnable_NMEA_MWV', 'int32', 'bEnable_NMEA_MWD', 'int32', 'bEnable_NMEA_MDA', 'int32', 'bEnable_NMEA_VDM', 'int32', 'bEnable_NMEA_PD6_SA', 'int32', 'bEnable_NMEA_PD6_TS', 'int32', 'bEnable_NMEA_PD6_BI', 'int32', 'bEnable_NMEA_PD6_BS', 'int32', 'bEnable_NMEA_PD6_BE', 'int32', 'bEnable_NMEA_PD6_BD', 'int32', 'bEnable_UBX_NAV_POSLLH', 'int32', 'bEnable_UBX_NAV_PVT', 'int32', 'bEnable_UBX_NAV_SOL', 'int32', 'bEnable_UBX_NAV_STATUS', 'int32', 'bEnable_UBX_NAV_SVIN', 'int32', 'bEnable_UBX_NAV_VELNED', 'int32');
structs.SSC32.members=struct('RS232Port', 'RS232PORT', 'pfSaveFile', 's_iobufPtr', 'LastPWs', 'int32#5', 'szCfgFilePath', 'int8#256', 'szDevPath', 'int8#256', 'BaudRate', 'int32', 'timeout', 'int32', 'bSaveRawData', 'int32', 'MinPWs', 'int32#5', 'MidPWs', 'int32#5', 'MaxPWs', 'int32#5', 'InitPWs', 'int32#5', 'ThresholdPWs', 'int32#5', 'CoefPWs', 'double#5', 'bProportionalPWs', 'int32#5', 'rudderchan', 'int32', 'rightthrusterchan', 'int32', 'leftthrusterchan', 'int32', 'rightfluxchan', 'int32', 'leftfluxchan', 'int32', 'MinAngle', 'double', 'MidAngle', 'double', 'MaxAngle', 'double');
structs.MAESTRO.members=struct('RS232Port', 'RS232PORT', 'pfSaveFile', 's_iobufPtr', 'LastPWs', 'int32#5', 'szCfgFilePath', 'int8#256', 'szDevPath', 'int8#256', 'BaudRate', 'int32', 'timeout', 'int32', 'bSaveRawData', 'int32', 'DeviceNumber', 'int32', 'MinPWs', 'int32#5', 'MidPWs', 'int32#5', 'MaxPWs', 'int32#5', 'InitPWs', 'int32#5', 'ThresholdPWs', 'int32#5', 'CoefPWs', 'double#5', 'bProportionalPWs', 'int32#5', 'rudderchan', 'int32', 'rightthrusterchan', 'int32', 'leftthrusterchan', 'int32', 'rightfluxchan', 'int32', 'leftfluxchan', 'int32', 'winddiranaloginputchan', 'int32', 'winddiranaloginputvalueoffset', 'double', 'winddiranaloginputvaluethreshold', 'double', 'winddiranaloginputvaluecoef', 'double', 'windspeedanaloginputchan', 'int32', 'windspeedanaloginputvalueoffset', 'double', 'windspeedanaloginputvaluethreshold', 'double', 'windspeedanaloginputvaluecoef', 'double', 'bat1analoginputchan', 'int32', 'bat1analoginputvalueoffset', 'double', 'bat1analoginputvaluethreshold', 'double', 'bat1analoginputvaluecoef', 'double', 'bat2analoginputchan', 'int32', 'bat2analoginputvalueoffset', 'double', 'bat2analoginputvaluethreshold', 'double', 'bat2analoginputvaluecoef', 'double', 'switchanaloginputchan', 'int32', 'switchanaloginputvalueoffset', 'double', 'switchanaloginputvaluethreshold', 'double', 'switchanaloginputvaluecoef', 'double', 'MinAngle', 'double', 'MidAngle', 'double', 'MaxAngle', 'double', 'bEnableSetMultipleTargets', 'int32');
structs.HOKUYO.members=struct('RS232Port', 'RS232PORT', 'StepAngleSize', 'double', 'StepCount', 'int32', 'pfSaveFile', 's_iobufPtr', 'szCfgFilePath', 'int8#256', 'szDevPath', 'int8#256', 'BaudRate', 'int32', 'timeout', 'int32', 'bSaveRawData', 'int32', 'bForceSCIP20', 'int32', 'bHS', 'int32', 'SlitDivision', 'int32', 'StartingStep', 'int32', 'FrontStep', 'int32', 'EndStep', 'int32', 'ClusterCount', 'int32', 'ScanInterval', 'int32', 'bContinuousNumberOfScans', 'int32', 'alpha_max_err', 'double', 'd_max_err', 'double');
structs.RPLIDAR.members=struct('RS232Port', 'RS232PORT', 'model', 'int32', 'hardware', 'int32', 'firmware_major', 'int32', 'firmware_minor', 'int32', 'SerialNumber', 'int8#33', 'Tstandard', 'int32', 'Texpress', 'int32', 'esdata_prev', 'uint8#84', 'pfSaveFile', 's_iobufPtr', 'szCfgFilePath', 'int8#256', 'szDevPath', 'int8#256', 'BaudRate', 'int32', 'timeout', 'int32', 'bSaveRawData', 'int32', 'ScanMode', 'int32', 'motordelay', 'int32', 'maxhist', 'int32', 'alpha_max_err', 'double', 'd_max_err', 'double');
methodinfo=fcns;