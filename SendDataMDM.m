function [result, SentBytes] = SendDataMDM(pMDM, buf, buflen)

pbuf_p = libpointer('int32Ptr', buf);
SentBytes = 0;
pSentBytes = libpointer('int32Ptr', SentBytes);

result = calllib('hardwarex', 'SendDataMDMx', pMDM, pbuf_p, buflen, pSentBytes);

SentBytes = pSentBytes.value;
