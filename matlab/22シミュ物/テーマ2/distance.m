function dout = distance(z)
zmin = min(z);
zmax = max(z);

zdist = abs( (zmax(1)+zmin(1))/2 - (zmax(2)+zmin(2))/2 );
dout = round(zdist, 3,'significant');