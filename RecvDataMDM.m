function [result, buf_p, ReceivedBytes] = RecvDataMDM(pMDM, buf, buflen)

pbuf_p = libpointer('uint8Ptr', buf);
ReceivedBytes = 0;
pReceivedBytes = libpointer('int32Ptr', ReceivedBytes);

result = calllib('hardwarex', 'RecvDataMDMx', pMDM, pbuf_p, buflen, pReceivedBytes);

buf_p = pbuf_p.value;
ReceivedBytes = pReceivedBytes.value;
