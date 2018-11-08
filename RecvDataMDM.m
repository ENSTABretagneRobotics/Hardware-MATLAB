function [result, ReceivedBytes] = RecvDataMDM(pMDM, buf, buflen)

pbuf_p = libpointer('int32Ptr', buf);
ReceivedBytes = 0;
pReceivedBytes = libpointer('int32Ptr', ReceivedBytes);

result = calllib('hardwarex', 'RecvDataMDMx', pMDM, pbuf_p, buflen, pReceivedBytes);

ReceivedBytes = pReceivedBytes.value;
