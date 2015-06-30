function [result] = StopThreadMaestro(pMaestro)
result = calllib('hardwarex', 'StopThreadMaestrox', pMaestro);
