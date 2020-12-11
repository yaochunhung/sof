function x = init_struc_fixpt ()
fm = get_fimath();

x     = fi(2.3, 0, 32, 30, fm);
end


function fm = get_fimath()
	fm = fimath('RoundingMethod', 'Convergent',...
	     'OverflowAction', 'Wrap',...
	     'ProductMode','FullPrecision',...
	     'SumMode','FullPrecision');
end
