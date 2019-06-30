function func = sfunc(t)
st = t/10000;
n = -9;
if 0.5 < st && st <= 2
    n = -5;
 if st <= 1
    n = -7;
 end
end

f = 440 * 2^(n/12);
func = sin(2*pi*f*st);
