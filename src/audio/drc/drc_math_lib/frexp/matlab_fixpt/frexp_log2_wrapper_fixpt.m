function [F,E] = frexp_log2_wrapper_fixpt(x)
    fm = get_fimath();
    x_in = fi( x, 0, 32, 30, fm );
    [F_out,E_out] = frexp_log2_fixpt( x_in );
    F = double( F_out );
    E = double( E_out );
end

function fm = get_fimath()
	fm = fimath('RoundingMethod', 'Convergent',...
	     'OverflowAction', 'Wrap',...
	     'ProductMode','FullPrecision',...
	     'SumMode','FullPrecision');
end
