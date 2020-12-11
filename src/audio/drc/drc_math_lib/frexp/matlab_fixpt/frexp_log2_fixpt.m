function [F,E ] = frexp_log2_fixpt(x)
fm = get_fimath();

[fmo_1,fmo_2] = log2(double(x));
F = fi(fmo_1, 0, 32, 32, fm);
E = fi(fmo_2, 0, 2, 0, fm);

% [yVal]  = log(x)/log(2); % log2(x) yval= log(val)/log(2)
end


function fm = get_fimath()
	fm = fimath('RoundingMethod', 'Convergent',...
	     'OverflowAction', 'Wrap',...
	     'ProductMode','FullPrecision',...
	     'SumMode','FullPrecision');
end
