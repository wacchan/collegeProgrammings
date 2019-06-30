function wout = wide(z)
zmin = min(z);
zmax = max(z);
zwide = abs(zmax-zmin);
zwide = round(zwide, 3,'significant');
wout = zwide;