function [result] = DisconnectMaestro(pMaestro)
result = calllib('hardwarex', 'DisconnectMaestrox', pMaestro);
